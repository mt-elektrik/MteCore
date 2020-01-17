/*
    17/01/2020 Muara Teknik Elektrik
    Input Event setDebounceDelay Example

    Default Debounce Delay is 50 ms
*/


#define MTECORE_DEBUG //uncomment this line for debug
#include "MteCore.h"
void setup(){
    Serial.begin(9600);
    IN1.setDebounceDelay(500); //set Debounce Delay 500 ms
    IN1.onChange(
        [](){
            Serial.println("IN1 onChange");
        }
    );
    IN1.onEnable(
        [](){
            Serial.println("IN1 onEnable");
        }
    );
    IN1.onDisable(
        [](){
            Serial.println("IN1 onDisable");
        }
    );
    //--------------------------
    IN2.setDebounceDelay(2000); //set Debounce Delay 2000 ms
    IN2.onChange(
        [](){
            Serial.println("IN2 onChange");
        }
    );
    IN2.onEnable(
        [](){
            Serial.println("IN2 onEnable");
        }
    );
    IN2.onDisable(
        [](){
            Serial.println("IN2 onDisable");
        }
    );
    //---------------------------------
    IN3.setDebounceDelay(1); //set Debounce Delay 1 ms
    IN3.onChange(
        [](){
            Serial.println("IN3 onChange");
        }
    );
    IN3.onEnable(
        [](){
            Serial.println("IN3 onEnable");
        }
    );
    IN3.onDisable(
        [](){
            Serial.println("IN3 onDisable");
        }
    );
}
void loop(){
    process();
}