/*
    19/01/2020 Muara Teknik Elektrik
    PWM SmoothPWM Example
    Use F5 as analog input to control pwm on F6
    Use F8 to blink smooth PWM
*/
#define _ENABLE_F5_ANALOG //uncomment this line to set pin F5 as Analog
#define _ENABLE_F6_PWM //uncomment this line to set pin F6 as PWM
#define _ENABLE_F8_PWM //uncomment this line for set pin F8 as PWM
#define _ENABLE_SMOOTH_PWM //uncomment this line to enable smooth PWM function
#define _DELAY_SMOOTH_PWM 5000 //uncomment this line to set delay smooth pwm 5000ms (if not set,delay smooth PWM by default 1000ms)
// #define _PWM_DEBUG //uncomment this line for print pwm activity
#include "MteCore.h"
    bool isZero=true;
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

    F8.onProcess( //event onProcess only available when PWM Smooth is Enable
        [](uint8_t valuePercent){
            if(valuePercent==100){
                if(!isZero){
                    F8.setValue(0);
                    isZero=true;
                }
            }else if (valuePercent==0){
                if(isZero){
                    F8.setValue(100);
                    isZero=false;
                }
            }
        }
    );
}

void loop(){
    process();
}