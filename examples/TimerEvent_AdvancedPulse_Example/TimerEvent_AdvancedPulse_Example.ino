/*
    14/01/2020 Muara Teknik Elektrik
    advanced pulse with timer
    OUT1 = output pulse 1000 ms enable & 100 ms disable
*/
// #define TIMER_DEBUG //uncomment this line for debug
#include "MteCore.h"
Timer t(1000); //first start 1000 ms
void setup(){
    Serial.begin(9600);
    t.onTimeout(
        [](){
            if(!OUT1.isEnable()){
                //enable
                OUT1.enable();
                t.setInterval(1000);
            }else{
                //disable
                OUT1.disable();
                t.setInterval(100);
            }
        }
    );
    t.start();
    OUT1.enable();
}
void loop(){
    t.process(millis());
}