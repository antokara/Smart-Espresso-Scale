#include <modes/mode_base.h>
#include <lcd.h>

Mode_Base::Mode_Base(){
    // constructor
};

void Mode_Base::setup(){

};

void Mode_Base::loop(){

};

void Mode_Base::test()
{
    Lcd::print("test    ", 0, 1);
};