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

// the actual scale device instance
NAU7802 scaleDev;

// not yet known
bool Scale::isAvailable = NULL;

// default values
float Scale::calibrationFactor = -390.26;
long Scale::zeroOffset = 176605;

// Create an array to take average of weights. This helps smooth out jitter.
float avgWeights[SCALE_AVG_WEIGHT_SAMPLES];
byte avgWeightIndex = 0;

// keep the previous average weight to compare against
// before deciding to show a new weight value to the user
float Scale::prevAvgWeight = 0;

/**
 * @brief should be called once, from the main setup() function
 *
 */
void Scale::setup()
{
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
        Scale::isAvailable = false;
        // TODO: show in screen
    }
    else
    {
        Scale::isAvailable = true;
        Scale::setCalibrationFactor();
        // Increase to max sample rate
        scaleDev.setSampleRate(NAU7802_SPS_320);
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
 * @param weight
 * @return float
 */
float Scale::calcAvgWeight(float weight)
{
    avgWeights[avgWeightIndex++] = weight;
    if (avgWeightIndex == SCALE_AVG_WEIGHT_SAMPLES)
        avgWeightIndex = 0;
    float avgWeight = 0;
    for (int x = 0; x < SCALE_AVG_WEIGHT_SAMPLES; x++)
        avgWeight += avgWeights[x];
    avgWeight /= SCALE_AVG_WEIGHT_SAMPLES;

    return avgWeight;
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
long Scale::calculateZeroOffset()
{
    scaleDev.calculateZeroOffset(SCALE_CALCULATE_ZERO_OFFSET_SAMPLES);
    Scale::zeroOffset = scaleDev.getZeroOffset();
#ifdef SERIAL_DEBUG
    Serial.print("New zero offset: ");
    Serial.println(Scale::zeroOffset);
#endif
    return Scale::zeroOffset;
}

/**
 * @brief returns the current weight
 *
 * @return float the current weight
 */
float Scale::getWeight()
{
    return scaleDev.getWeight(SCALE_ALLOW_NEGATIVE_READINGS);
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
        Serial.println(Scale::getWeight(), SCALE_WEIGHT_DECIMALS);

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
    if (Scale::isAvailable == true && scaleDev.available() == true)
    {
        float avgWeight = Scale::calcAvgWeight(Scale::getWeight());
        // TODO: only check the avg weight...
        if (abs(avgWeight - Scale::prevAvgWeight) > SCALE_AVG_WEIGHT_DELTA_THRESHOLD)
        {
            // TODO: show on screen
            Scale::prevAvgWeight = avgWeight;
            Serial.print("\tAvgWeight: ");
            Serial.println(Scale::prevAvgWeight, SCALE_WEIGHT_DECIMALS);
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
    }
}