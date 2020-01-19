/*
    19/01/2020 Muara Teknik Elektrik
    PWM Example
    Use F5 as analog input to control pwm on F6
*/

#define _ENABLE_F5_ANALOG //uncomment this line for set pin F5 as Analog
#define _ENABLE_F6_PWM //uncomment this line for set pin F6 as PWM
// #define _PWM_DEBUG //uncomment this line for print pwm activity
#include "MteCore.h"
void setup(){
    Serial.begin(9600);
    F5.onChange(
        [](uint16_t v){
            byte percent = map(v,0,1023,0,100);
            F6.setValue(percent);
            Serial.print("Value ANALOG : ");
            Serial.print(v);
            Serial.print(" = ");
            Serial.print(percent);
            Serial.println("%");
        }
    );
}

void loop(){
    process();
}