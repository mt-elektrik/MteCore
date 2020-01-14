/* example output
    14/01/2020 Muara Teknik Elektrik
    IN1 = push button for enable OUT1
    IN2 = push button for disable OUT1
    IN3 = push button for toggle timer pulse OUT1 by 1 sec and OUT2 is the opposite of OUT1
    on this example 
*/
#include "MteCore.h"
Timer t(1000); //interval 1000 ms = 1 sec
void setup(){
    Serial.begin(9600);
    IN1.onEnable(enableOUT1);
    IN2.onEnable(disableOUT1);
    IN3.onEnable(handleTimer);
    
    OUT1.onEnable(OUT1_onEnable);
    OUT1.onDisable(OUT1_onDisable);
    OUT1.onChange(OUT1_onChange);
    // t.setInterval(1000) //to set interval
    t.onTimeout(pulseOUT1);
}
void loop(){
    //process main input & output
    process();
    unsigned long now = millis();
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
void OUT1_onEnable(){
    Serial.println("OUT1 is Enable");
}
void OUT1_onDisable(){
    Serial.println("OUT1 is Disable");
}
void OUT1_onChange(){
    Serial.println("OUT1 onChange Event");
    if(OUT1.isEnable()){
        OUT2.disable();
    }else{
        OUT2.enable();
    }
}