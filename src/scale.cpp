/**
 * @author Antonios Karagiannis (antokarag@gmail.com)
 * @brief Scale
 * @date 2024-01-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <scale.h>
#include <device.h>
#include <lcd.h>
#include <buzzer.h>

// the actual scale device instance
NAU7802 scaleDev;

/**
 * @brief if false, the scale I2C was not found
 * 0 when unknown (yet)
 * 1 when available
 * 2 when not currently available
 */
byte Scale::isAvailable = SCALE_IS_AVAILABLE_UNKNOWN;

/**
 * @brief 0 when the scale has not become available yet
 *        1, when this is first loop, that it's available
 *        2, on any subsequent loops
 *
 */
byte Scale::firstAvailability = SCALE_FIRST_AVAILABILITY_UNKNOWN;

/**
 * @brief Value used to convert the load cell reading to lbs or kg
 * @see SCALE_CALIBRATE and calibrate()
 *
 */
float Scale::calibrationFactor = -820.18;

/**
 * @brief "Zero" value that is found when scale is tared
 *
 */
long Scale::zeroOffset = 175782;

/**
 * @brief the average weight to compare against.
 * Depending on the execution time, this can be the previous or current avg weight.
 *  - if used prior to calling calcAvgWeight(), it is the previous
 *  - if used after calling calcAvgWeight(), it is the current
 *
 * @see calcAvgWeight()
 */
float Scale::avgWeight = 0;

/**
 * @brief the list of weights,
 * for the average weight calculation
 *
 * This helps smooth out jitter.
 */
float Scale::avgWeights[SCALE_AVG_WEIGHT_SAMPLES_MAX];

/**
 * @brief the current index of the avgWeights list.
 * that's where we will add the next weight...
 */
byte Scale::avgWeightIndex = 0;

/**
 * @brief the current number of sample weights
 * that we are using from the list of weights
 * in order to calculate the average.
 *
 * the smaller the number of samples, the more agressive/faster
 * but also noisier, the avg weight calculation will be.
 */
byte Scale::avgWeightSamples = SCALE_AVG_WEIGHT_SAMPLES_MIN;

/**
 * @brief true if the weight has changed in this loop iteration
 *
 */
byte Scale::hasWeightChanged = false;

/**
 * @brief should be called once, from the main setup() function
 *
 */
void Scale::setup()
{
    // TODO: show on screen status start/end/calibrate
#ifdef SERIAL_DEBUG
    Serial.println("Scale::setup - start");
#endif
    Wire1.setSDA(SCALE_SDA_PIN);
    Wire1.setSCL(SCALE_SCL_PIN);
    Wire1.begin();
    Wire1.setClock(SCALE_I2C_CLOCK_HZ);

    if (scaleDev.begin(Wire1) == false)
    {
#ifdef SERIAL_DEBUG
        Serial.println("Scale::setup - Scale not detected. Please check wiring!");
#endif
        Scale::isAvailable = SCALE_IS_AVAILABLE_NO;
        // TODO: show in screen
    }
    else
    {
        Scale::isAvailable = SCALE_IS_AVAILABLE_YES;
        Scale::setCalibrationFactor();
        // Set gain. The higher, the more sensitive but also more noise/jitter
        // values: 1/2/4/8/16/32/64/128
        scaleDev.setGain(SCALE_GAIN);
        // set the sample rate per second. The higher, the more jitter we may get
        // values: 10/20/40/80/320
        scaleDev.setSampleRate(SCALE_SPS);
        // Re-cal analog front end when we change gain, sample rate, or channel
        scaleDev.calibrateAFE();
    }
#ifdef SERIAL_DEBUG
    Serial.print("Scale Zero offset: ");
    Serial.println(scaleDev.getZeroOffset());
    Serial.print("Scale Calibration factor: ");
    Serial.println(scaleDev.getCalibrationFactor());
    Serial.println("Scale::setup - end");
#endif
}

/**
 * @brief calculates the average weight from the given weight,
 * using a moving window average algorithm, to reduce jitter.
 *
 * @param rawWeight the current raw weight value
 * @see getRawWeight()
 */
void Scale::calcAvgWeight(float rawWeight)
{
    // add the new weight to the list of average weights
    Scale::avgWeights[Scale::avgWeightIndex++] = rawWeight;
    // reset the index to the start,
    // if it has reached the max limit of the list or the current limit
    if (Scale::avgWeightIndex == SCALE_AVG_WEIGHT_SAMPLES_MAX || Scale::avgWeightIndex >= Scale::avgWeightSamples)
        Scale::avgWeightIndex = 0;

    // get the average weight
    float avgWeight = 0;
    for (int x = 0; x < Scale::avgWeightSamples; x++)
        avgWeight += Scale::avgWeights[x];
    avgWeight /= Scale::avgWeightSamples;

    // get the delta between current avg and previous
    float delta = abs(avgWeight - Scale::avgWeight);
    if (delta > 0 && delta <= SCALE_AVG_WEIGHT_DELTA_THRESHOLD && Scale::avgWeightSamples < SCALE_AVG_WEIGHT_SAMPLES_MAX)
    {
        // when there's a delta but it's under the threshold
        // (most likely the item on the scale is stabilizing) and
        // the samples are still under the max. limit
        //
        // increase the samples in an effort to stabilize the weight and
        // set the average weight to the new maximum sample slot
        // to prevent any previous value to affect the next average...
        Scale::avgWeights[++Scale::avgWeightSamples] = avgWeight;
    }
    else if (delta > SCALE_AVG_WEIGHT_DELTA_THRESHOLD && Scale::avgWeightSamples > SCALE_AVG_WEIGHT_SAMPLES_MIN)
    {
        // when there's a delta greater than the threshold
        // (most likely the item on the scale was added or removed) and
        // the samples are above the min. limit
        //
        // reset the samples to the min. limit
        Scale::avgWeightSamples = SCALE_AVG_WEIGHT_SAMPLES_MIN;
        // overwrite all the samples from the min. limit and above
        // with the average weight, to prevent any previous value to affect the next average...
        for (int x = Scale::avgWeightSamples; x < SCALE_AVG_WEIGHT_SAMPLES_MIN; x++)
            Scale::avgWeights[x] = avgWeight;
    }

    if (Scale::avgWeight != avgWeight)
    {
        // keep the prev avg weight
        Scale::avgWeight = avgWeight;
        Scale::hasWeightChanged = true;
    }
    else
    {
        Scale::hasWeightChanged = false;
    }
}

/**
 * @brief rounds the value provided to the decimal points
 *
 * @param value
 * @param decimalPoints
 * @return float
 */
float Scale::roundFloat(float value, int decimalPoints)
{
    float multiplier = pow(10, decimalPoints);
    return round(value * multiplier) / multiplier;
}

/**
 * @brief get the length of characters in a number
 *
 * @param number
 * @return int
 */
int Scale::numberLength(float number)
{
    return floor(log10(abs(number))) + 1;
}

/**
 * @brief formats the weight provided,
 * to a user friendly number.
 *
 * @param weight
 * @return float
 */
String Scale::formatWeight(float weight)
{
    float formattedWeight = weight;

    // when the weight is too close to zero, make it zero
    if (abs(formattedWeight) <= SCALE_AVG_WEIGHT_DELTA_ZERO_THRESHOLD)
    {
        formattedWeight = 0;
    }
    else if (formattedWeight > SCALE_WEIGHT_MAX)
    {
        return SCALE_WEIGHT_MAX_MSG;
    }
    else
    {
        formattedWeight = Scale::roundFloat(formattedWeight, SCALE_WEIGHT_DECIMALS);
    }

    // pad prefix with spaces
    const int totalWidth = Scale::numberLength(SCALE_WEIGHT_DECIMALS + SCALE_WEIGHT_MAX);
    // +1 for the null terminator
    char buffer[totalWidth + 1];
    dtostrf(formattedWeight, totalWidth, SCALE_WEIGHT_DECIMALS, buffer);

    // Find the position of the decimal point
    char *decimalPoint = strchr(buffer, '.');

    // If decimal point is found, move characters to the right to add leading zeros
    if (decimalPoint != NULL)
    {
        int zerosToAdd = totalWidth - (decimalPoint - buffer);
        memmove(buffer + zerosToAdd, buffer, strlen(buffer) + 1);
        memset(buffer, ' ', zerosToAdd);
    }

    return String(buffer) + " " + SCALE_UNIT_SUFFIX_GRAMS;
}

/**
 * @brief sets the initial calibration factor (and zero offset)
 *
 */
void Scale::setCalibrationFactor(void)
{
    scaleDev.setCalibrationFactor(Scale::calibrationFactor);
    scaleDev.setZeroOffset(Scale::zeroOffset);
#ifdef SERIAL_DEBUG
    Serial.print("Scale Zero offset: ");
    Serial.println(scaleDev.getZeroOffset());
    Serial.print("Scale Calibration factor: ");
    Serial.println(scaleDev.getCalibrationFactor());
#endif
}

/**
 * @brief calculates, sets and returns the zeroOffset (tares/zeros the scale)
 * @return long the new zeroOffset
 */
void Scale::calculateZeroOffset()
{
    scaleDev.calculateZeroOffset(SCALE_CALCULATE_ZERO_OFFSET_SAMPLES);
    Scale::zeroOffset = scaleDev.getZeroOffset();
#ifdef SERIAL_DEBUG
    Serial.print("New zero offset: ");
    Serial.println(Scale::zeroOffset);
#endif
}

/**
 * @brief watches the avgWeight readings until they stabilize and
 * once they do, it zeros/tares the scale.
 *
 * if the readings fail to stabilize within the allowed time-frame,
 * it notifies the user and keeps waiting... it never times out.
 *
 * Should be called once at setup and by user input, on command.
 *
 * @return long the new zeroOffset
 */
void Scale::tare()
{
    // TODO: properly tare with a watch. this basically needs to "start" taring
    Buzzer::on();
    Lcd::print("Tearing...", 0, 0, true);

    // tare
    Scale::calculateZeroOffset();

    // show zero to the screen
    Lcd::print(Scale::formatWeight(0), 0, 0, true);

    // reset all avg weight values
    for (int x = 0; x <= SCALE_AVG_WEIGHT_SAMPLES_MAX; x++)
        Scale::avgWeights[x] = 0;

    Buzzer::off();
}

/**
 * @brief returns the current raw weight, as the sensor returns it,
 * allowing for negavive values and without any average.
 *
 * @return float the current raw weight
 */
float Scale::getRawWeight()
{
    return scaleDev.getWeight(SCALE_ALLOW_NEGATIVE_READINGS, 1);
}

/**
 * @brief the current processed (filtered) weight
 * this should be used in most places (except for calibration)
 *
 * @return float
 * @see calcAvgWeight()
 */
float Scale::getWeight()
{
    return Scale::avgWeight;
}

#ifdef SCALE_CALIBRATE
/**
 * @brief Gives user the ability to set a known weight on the scale and calculate a calibration factor
 * This should be performed once, before "releasing" the scale.
 *
 */
void Scale::calibrate(void)
{
    {
        Serial.println();
        Serial.println();
        Serial.println(F("Scale calibration"));
        Serial.println(F("Setup scale with no weight on it. Press a key when ready."));
        while (Serial.available())
            Serial.read(); // Clear anything in RX buffer
        while (Serial.available() == 0)
            delay(10); // Wait for user to press key

        // zero the scale
        Scale::calculateZeroOffset();

        Serial.println(F("Place known weight on scale. Press a key when weight is in place and stable."));
        while (Serial.available())
            Serial.read(); // Clear anything in RX buffer
        while (Serial.available() == 0)
            delay(10); // Wait for user to press key

        Serial.print(F("Please enter the weight, without units, currently sitting on the scale (for example '4.25'): "));
        while (Serial.available())
            Serial.read(); // Clear anything in RX buffer
        while (Serial.available() == 0)
            delay(10); // Wait for user to press key

        // Read user input
        float weightOnScale = Serial.parseFloat();
        Serial.println();

        // confirm to the user, the input we got
        Serial.print("Calibration Weight On Scale: ");
        Serial.println(weightOnScale);

        // Tell the library how much weight is currently on it
        scaleDev.calculateCalibrationFactor(weightOnScale, SCALE_CALCULATE_ZERO_OFFSET_SAMPLES);
        Scale::calibrationFactor = scaleDev.getCalibrationFactor();

        // confirm to the user, the new weight, which should match
        // the reference weight that was entered previously...
        Serial.print("Scale Reading: ");
        Serial.println(Scale::getRawWeight(), SCALE_WEIGHT_DECIMALS);

        // this value, must be set to the Scale::calibrationFactor constant
        Serial.print("Scale Calibration factor: ");
        Serial.println(scaleDev.getCalibrationFactor());
    }
}
#endif

/**
 * @brief should be called on every iteration of the main loop() function
 *
 */
void Scale::loop()
{
    float lastAvgWeight = 0;
    if (Scale::isAvailable == SCALE_IS_AVAILABLE_YES && scaleDev.available() == true)
    {
        if (Scale::firstAvailability == SCALE_FIRST_AVAILABILITY_UNKNOWN)
        {
            Scale::firstAvailability = SCALE_FIRST_AVAILABILITY_YES;
            Scale::tare();
        }

        // calculate the average weight and set the hasWeightChanged
        Scale::calcAvgWeight(Scale::getRawWeight());

        if (Scale::hasWeightChanged)
        {
            // TODO: debounce the screen updates because the LCD has a very slow refresh rate
            //       the last value, must be retained/shown eventually...
            Lcd::print(Scale::formatWeight(Scale::getWeight()), 0, 0);
        }

#ifdef SCALE_CALIBRATE
        if (Serial.available())
        {
            byte incoming = Serial.read();
            if (incoming == 't')
            {
                // Tare the scale
                scaleDev.calculateZeroOffset();
            }
            else if (incoming == 'c')
            {
                // Calibrate
                Scale::calibrate();
            }
        }
#endif

        if (Scale::firstAvailability == SCALE_FIRST_AVAILABILITY_YES)
        {
            Scale::firstAvailability = SCALE_FIRST_AVAILABILITY_NO;
        }
    }
}