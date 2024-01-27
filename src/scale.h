#ifndef SCALE
#define SCALE
#include <Arduino.h>
#include <Wire.h>
#include <SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h>

// I2C pins
#define SCALE_SDA_PIN D2
#define SCALE_SCL_PIN D3

// we can increase I2C clock speed to 400kHz, the NAU7802 supports it
#define SCALE_I2C_CLOCK_HZ 400000

class Scale
{
public:
    // properties
    /**
     * @brief if false, the scale I2C was not found
     * null when unknown (yet)
     */
    static bool isAvailable;
    /**
     * @brief Zero value that is found when scale is tared
     *
     */
    static long zeroOffset;
    /**
     * @brief Value used to convert the load cell reading to lbs or kg
     *
     */
    static float calibrationFactor;

    static long prevReading;
    static float prevWeight;
    static bool isCalibrated;

    // methods
    static void setup();
    static void loop();
    static float calcAvgWeight(float weight);
    static void calibrate();
    static void recordSystemSettings();
    static void readSystemSettings();
};

#endif // SCALE