/* example output
    IN1 = push button for enable OUT1
    IN2 = push button for disable OUT1
    IN3 = push button for toggle timer pulse OUT1 by 1 sec
*/
#include "MteCore.h"
Timer t(1000); //interval 1000 ms = 1 sec
void setup(){
    // t.setInterval(1000) //to set interval
    Serial.begin(9600);
    IN1.onEnable(enableOUT1);
    IN2.onEnable(disableOUT1);
    IN3.onEnable(handleTimer);
    t.onTimeout(pulseOUT1);
}
void loop(){
    unsigned long now = millis();
    process();
    t.process(now);
}
void enableOUT1(){
    OUT1.enable();
}
void disableOUT1(){
    OUT1.disable();
}
void handleTimer(){
    if (t.isStarted()){
        t.stop();
    }else{
        t.start();
    }
}
void pulseOUT1(){
    if(OUT1.isEnable()){
        OUT1.disable();
    }else{
        OUT1.enable();
    }
}