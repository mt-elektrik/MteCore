/*
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
*/

//Change the jumper to F5 on the SELECTOR PIN to activate F5,
#define _ENABLE_F5_ANALOG //Enable F5 as Analog Function
// #define _ANALOG_DEBUG //uncomment this line for debug
#include "MteCore.h"
void setup(){
    Serial.begin(9600);
    F5.onChange(
        [](uint16_t val){
             Serial.println(val);
        }
    );
}

void loop(){
    process();
}