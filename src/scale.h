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
 * @brief the min/max samples to collect for the moving average window
 * the higher, the smoother the result (less jitter) but
 * it also slows down the processing time...
 */
#define SCALE_AVG_WEIGHT_SAMPLES_MIN 4
#define SCALE_AVG_WEIGHT_SAMPLES_MAX 128

/**
 * @brief the delta threshold between two average weight values
 * that indicates a new weight to show to the user.
 *
 * must be greather than, to show
 *
 */
#define SCALE_AVG_WEIGHT_DELTA_THRESHOLD 0.1

/**
 * @brief calculate the zero threshold that when the avg weight
 * has a delta smaller or equal to, will be considered zero,
 * for formatting purposes only
 *
 */
#define SCALE_AVG_WEIGHT_DELTA_ZERO_THRESHOLD SCALE_AVG_WEIGHT_DELTA_THRESHOLD * 0.9 + SCALE_AVG_WEIGHT_DELTA_THRESHOLD

/**
 * @brief the number of weight decimals accurancy, to show to the user
 *
 */
#define SCALE_WEIGHT_DECIMALS 1

/**
 * @brief maximum weight value to show to the user (in grams)
 *
 */
#define SCALE_WEIGHT_MAX 1000

/**
 * @brief the message to show to the user,
 * when the max weight has been reached
 */
#define SCALE_WEIGHT_MAX_MSG "MAX"

/**
 * @brief scale unit suffixes
 *
 */
#define SCALE_UNIT_SUFFIX_GRAMS "gr."
#define SCALE_UNIT_SUFFIX_POUNDS "lb."

/**
 * @brief the sensor gain
 * The higher, the more sensitive and appears to reduce noise actually
 * values: 1/2/4/8/16/32/64/128
 *
 * Important: Changing that, requires a recalibration of the scale sensor
 */
#define SCALE_GAIN NAU7802_GAIN_128

/**
 * @brief set the sample rate per second from the sensor.
 * The higher, the more jitter we may get and
 * we need higher avg samples to compensate
 * values: 10/20/40/80/320
 */
#define SCALE_SPS NAU7802_SPS_80

// TODO: add unit prefix/switch;

class Scale
{
public:
    // properties
    static byte isAvailable;
    static byte firstAvailability;
    static long zeroOffset;
    static float calibrationFactor;

    static float prevWeight;
    static float prevAvgWeight;
    // Create an array to take average of weights. This helps smooth out jitter.
    static float avgWeights[SCALE_AVG_WEIGHT_SAMPLES_MAX];
    static byte avgWeightIndex;
    static byte avgWeightSamples;

    // methods
    static void setup();
    static void loop();
    static bool calcAvgWeight(float weight);
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