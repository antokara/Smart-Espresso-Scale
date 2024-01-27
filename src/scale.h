#ifndef SCALE
#define SCALE
#include <Arduino.h>
#include <Wire.h>
#include <SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h>

// I2C pins
#define SCALE_SDA_PIN D2
#define SCALE_SCL_PIN D3

// enums
#define SCALE_IS_AVAILABLE_UNKNOWN 0
#define SCALE_IS_AVAILABLE_YES 1
#define SCALE_IS_AVAILABLE_NO 2

// enums
#define SCALE_FIRST_AVAILABILITY_UNKNOWN 0
#define SCALE_FIRST_AVAILABILITY_YES 1
#define SCALE_FIRST_AVAILABILITY_NO 2

// we can increase I2C clock speed to 400kHz, the NAU7802 supports it
#define SCALE_I2C_CLOCK_HZ 400000

// some sensors provide negative readings as well
#define SCALE_ALLOW_NEGATIVE_READINGS true

// uncomment to calibrate the scale sensor
// should only be needed once
// in the serial, send "c" to calibrate and "t" to tare
#define SCALE_CALIBRATE

/**
 * @brief the number of samples to get for the tare
 * @see scaleDev.calculateZeroOffset()
 * should be Called when scale is setup, level, at running temperature, with nothing on it
 */
#define SCALE_CALCULATE_ZERO_OFFSET_SAMPLES 64

/**
 * @brief the samples to collect for the moving average window
 *
 */
#define SCALE_AVG_WEIGHT_SAMPLES 4

/**
 * @brief the delta threshold between two average weight values
 * that indicates a new weight to show to the user.
 *
 * must be greather than, to show
 *
 */
#define SCALE_AVG_WEIGHT_DELTA_THRESHOLD 2

/**
 * @brief the number of weight decimals accurancy, to show to the user
 *
 */
#define SCALE_WEIGHT_DECIMALS 2

/**
 * @brief maximum weight value to show to the user (in grams)
 *
 */
#define SCALE_WEIGHT_MAX 1000

/**
 * @brief scale unit suffixes
 *
 */
#define SCALE_UNIT_SUFFIX_GRAMS "gr."
#define SCALE_UNIT_SUFFIX_POUNDS "lb."

// TODO: add unit prefix/switch;

class Scale
{
public:
    // properties
    static byte isAvailable;
    static byte firstAvailability;
    static long zeroOffset;
    static float calibrationFactor;
    static float prevAvgWeight;

    // methods
    static void setup();
    static void loop();
    static float calcAvgWeight(float weight);
    static float getWeight();
    static void calculateZeroOffset();
    static void calibrate();
    static void setCalibrationFactor();
    static void tare();
    static String formatWeight(float weight);
    static float roundFloat(float value, int decimalPoints);
    static int numberLength(float number);
};

#endif // SCALE