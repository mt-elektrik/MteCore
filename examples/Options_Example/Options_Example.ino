
/*
    18/01/2020 Muara Teknik Elektrik
    Options Example
*/
// OPTIONS MUST ON TOP

//*********DEBUG MODE*************
//debug mode use serial for print any activity
//you can set serial baudrate on setup void
// #define _INPUT_DEBUG //uncomment this line for print input activity
// #define _OUTPUT_DEBUG //uncomment this line for print output activity
// #define _TIMER_DEBUG //uncomment this line for print timer activity
// #define _COUNTER_DEBUG //uncomment this line for print counter activity
//*********DISABLE PIN************
//use this option to manage pin and save the memory
// #define _DISABLE_{pin name} //uncomment this line for disable pin. 
// #define _DISABLE_IN1 //example to disable pin input IN1
// #define _DISABLE_OUT1 //example to disable pin output OUT1
//*********Function PIN************
/*  function pin use label F# , example F1.F2,...etc.
    you can setup an function pin use this option.
    rou cannot use several functions on each pin.
    note : don't forget to change jumper to F on your board
    --------------------------------
    **pin F mapping on board MTE-miniController V.2.0
    F1 => TX0
    F2 => RX0
    F3 => IN12 / i2c SDA / ANALOG1
    F4 => i2c SCL / ANALOG2
    F5 => IN11 / ANALOG3
    F6 => IN10 / PWM1 / RX1
    F7 => IN9 / ANALOG4
    F8 => IN8 / PWM2 / TX1
    ---------------------------------
    if one of the functions on the pin is active, then other functions on the pin will automatically be deactivated
    example : if F8 set as ANALOG, then IN8 and PWM function will automatically not be active
*/
// #define _ENABLE_F3_ANALOG //uncomment this line for set pin F3 as Analog
// #define _ENABLE_F3_I2C //uncomment this line for set pin F3 as I2C . Note : if use this function F4 must be set to I2C

// #define _ENABLE_F4_ANALOG //uncomment this line for set pin F4 as Analog
// #define _ENABLE_F4_I2C //uncomment this line for set pin F4 as I2C . Note : if use this function F3 must be set to I2C

// #define _ENABLE_F5_ANALOG //uncomment this line for set pin F5 as Analog

// #define _ENABLE_F6_PWM //uncomment this line for set pin F6 as PWM
// #define _ENABLE_F6_UART //uncomment this line for set pin F6 as UART

// #define _ENABLE_F7_ANALOG //uncomment this line for set pin F7 as Analog

// #define _ENABLE_F8_PWM //uncomment this line for set pin F8 as PWM
// #define _ENABLE_F8_UART //uncomment this line for set pin F8 as UART

//*********Options PWM************
// #define _ENABLE_SMOOTH_PWM //uncomment this line to enable smooth PWM function
// #define _DELAY_SMOOTH_PWM 5000 //uncomment this line to set delay smooth pwm 5000ms (if not set,delay smooth PWM by default 1000ms)
#include "MteCore.h"
void setup(){

}
void loop(){

}