#include <Arduino.h>
#include "utils.h"

/**
 * @brief rounds the value provided to the decimal points
 *
 * @param value
 * @param decimalPoints
 * @return float
 */
float Utils::roundFloat(float value, int decimalPoints)
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
int Utils::numberLength(float number)
{
    return floor(log10(abs(number))) + 1;
}