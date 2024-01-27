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
bool Scale::isCalibrated = NULL;

// default values
// float Scale::calibrationFactor = 0;
float Scale::calibrationFactor = -390.26;
// long Scale::zeroOffset = 1000L;
long Scale::zeroOffset = 176605;

long Scale::prevReading = 0;
float Scale::prevWeight = 0;

// Create an array to take average of weights. This helps smooth out jitter.
#define SCALE_AVG_WEIGHT_SAMPLES 4
float avgWeights[SCALE_AVG_WEIGHT_SAMPLES];
byte avgWeightIndex = 0;

/**
 * @brief the number of samples to get for the tare
 * @see scaleDev.calculateZeroOffset()
 * should be Called when scale is setup, level, at running temperature, with nothing on it
 */
#define SCALE_CALCULATE_ZERO_OFFSET_SAMPLES 64

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

        Scale::readSystemSettings();
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

void Scale::readSystemSettings(void)
{
    {
        float settingCalibrationFactor; // Value used to convert the load cell reading to lbs or kg
        long settingZeroOffset;         // Zero value that is found when scale is tared

        settingCalibrationFactor = Scale::calibrationFactor;
        settingZeroOffset = Scale::zeroOffset;
        // Look up the calibration factor
        // EEPROM.get(LOCATION_CALIBRATION_FACTOR, settingCalibrationFactor);
        if (settingCalibrationFactor == 0xFFFFFFFF)
        {
            settingCalibrationFactor = 0; // Default to 0
            // EEPROM.put(LOCATION_CALIBRATION_FACTOR, settingCalibrationFactor);
        }

        // Look up the zero tare point
        // EEPROM.get(LOCATION_ZERO_OFFSET, settingZeroOffset);
        if (settingZeroOffset == 0xFFFFFFFF)
        {
            settingZeroOffset = 1000L; // Default to 1000 so we don't get inf
            // EEPROM.put(LOCATION_ZERO_OFFSET, settingZeroOffset);
        }

        // Pass these values to the library
        scaleDev.setCalibrationFactor(settingCalibrationFactor);
        scaleDev.setZeroOffset(settingZeroOffset);

        Serial.print("Scale Zero offset: ");
        Serial.println(scaleDev.getZeroOffset());
        Serial.print("Scale Calibration factor: ");
        Serial.println(scaleDev.getCalibrationFactor());

        if (settingCalibrationFactor < 0.1 || settingZeroOffset == 1000)
        {
            // Defaults detected. Prompt user to cal scale.
            // TODO:
            // Scale::isCalibrated = false;
        }
        // else
        // {
        Scale::isCalibrated = true;
        // }
    }
}

// Record the current system settings to EEPROM
void Scale::recordSystemSettings(void)
{
    // Get various values from the library and commit them to NVM
    //   EEPROM.put(LOCATION_CALIBRATION_FACTOR, myScale.getCalibrationFactor());
    //   EEPROM.put(LOCATION_ZERO_OFFSET, myScale.getZeroOffset());
    Serial.print("Scale Zero offset: ");
    Serial.println(scaleDev.getZeroOffset());
    Serial.print("Scale Calibration factor: ");
    Serial.println(scaleDev.getCalibrationFactor());
}

/**
 * @brief Gives user the ability to set a known weight on the scale and calculate a calibration factor
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

        scaleDev.calculateZeroOffset(SCALE_CALCULATE_ZERO_OFFSET_SAMPLES); // Zero or Tare the scale. Average over 64 readings.
        Serial.print(F("New zero offset: "));
        Serial.println(scaleDev.getZeroOffset());

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

        Serial.print("Calibration Weight On Scale: ");
        Serial.println(weightOnScale);

        scaleDev.calculateCalibrationFactor(weightOnScale, SCALE_CALCULATE_ZERO_OFFSET_SAMPLES); // Tell the library how much weight is currently on it
        Scale::calibrationFactor = scaleDev.getCalibrationFactor();
        Scale::zeroOffset = scaleDev.getZeroOffset();
        Serial.print(F("New Scale Reading: "));
        Serial.println(scaleDev.getWeight(true), 2);
        Scale::recordSystemSettings();
    }
}

/**
 * @brief should be called on every iteration of the main loop() function
 *
 */
void Scale::loop()
{
    if (Scale::isAvailable == true && scaleDev.available() == true)
    {
        long currentReading = scaleDev.getReading();
        float currentWeight = scaleDev.getWeight(true);
        if (abs(currentWeight - Scale::prevWeight) > 1 || abs(currentReading - Scale::prevReading) > 3000)
        {
            Scale::prevWeight = currentWeight;
            Scale::prevReading = currentReading;
            Serial.print("Reading: ");
            Serial.print(currentReading);
            Serial.print("\tWeight: ");
            Serial.print(currentWeight, 2);
            Serial.print("\tAvgWeight: ");
            Serial.println(Scale::calcAvgWeight(currentWeight), 2);
        }

        if (Scale::isCalibrated == false)
        {
            // TODO: show in screen
            Serial.print("\tScale not calibrated. Press 'c'.");
            Serial.println();
        }

        if (Serial.available())
        {
            byte incoming = Serial.read();
            if (incoming == 't') // Tare the scale
                scaleDev.calculateZeroOffset();
            else if (incoming == 'c') // Calibrate
            {
                Scale::calibrate();
            }
        }
    }
}