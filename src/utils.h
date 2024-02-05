#ifndef UTILS
#define UTILS
#include <Arduino.h>

class Utils
{
public:
    static float roundFloat(float value, int decimalPoints);
    static int numberLength(float number);
};

#endif // UTILS