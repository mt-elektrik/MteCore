/*
    17/01/2020 Muara Teknik Elektrik
    Counter Example
    IN1 = trigger Counter
    IN2 = reset Counter
*/
// #define COUNTER_DEBUG //uncomment this line for debug
#include "MteCore.h";
Counter c;
void setup(){
    Serial.begin(9600);
    c.setValueMax(10); //set counter 10
    c.setIncreaseValue(1); //if ot set default value is 1
    c.onChange(
        [](){
            Serial.println(c.getCounterValue());
        }
    );
    c.onReset(
        [](){
            Serial.println("Couter onReset");
        }
    );
    c.onTriggered(
        [](){
            Serial.println("Couter onTriggered");
        }
    );

    //SET input
    IN1.onEnable(
        [](){
            c.trigger();
        }
    );
    IN2.onEnable(
        [](){
            c.reset();
        }
    );
}
void loop(){
    process();
}