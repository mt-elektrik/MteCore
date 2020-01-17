/*
    14/01/2020 Muara Teknik Elektrik
    Timer Event Example
    IN1 = toggle timer1
    IN2 = toggle timer2
*/
// #define TIMER_DEBUG //uncomment this line for debug
#include "MteCore.h";
Timer timer1; //for OUT1
Timer timer2; //for trigger counter1
Timer timer3; //for pulse OUT2
Timer timer4(500); //for pulse OUT3 by 500 ms
Counter counter1;
void setup(){
    Serial.begin(9600);
    //setup timer
    timer1.onStarted(
        [](){
            Serial.println("timer1 Started");
        }
    );
    timer1.onStoped(
        [](){
            Serial.println("timer1 Stoped");
        }
    );
    timer1.onTimeout(
        [](){
            Serial.println("timer1 timeout");
            if (OUT1.isEnable()){
                OUT1.disable();
            }else{
                OUT1.enable();
            }
        }
    );
    timer2.onStarted(
        [](){
            Serial.println("timer2 Started");
        }
    );
    timer2.onStoped(
        [](){
            Serial.println("timer2 Stoped");
        }
    );
    timer2.onTimeout(
        [](){
            counter1.trigger();
        }
    );
    timer3.onTimeout(
        [](){
            // Serial.println("timer3 timeout");
            if (OUT2.isEnable()){
                OUT2.disable();
            }else{
                OUT2.enable();
            }
        }
    );
    timer4.onTimeout(
        [](){
            if (OUT3.isEnable()){
                OUT3.disable();
            }else{
                OUT3.enable();
            }
        }
    );
    timer4.start();
    //set counter
    counter1.setValueMax(50); //max value 100 to reset
    counter1.onTriggered(
        [](){
            //set interval timer 3
            timer3.setInterval(10*counter1.getCounterValue());
        }
    );
    //setup input
    IN1.onEnable(
        [](){
            if(timer1.isStarted()){
                timer1.stop();
            }else{
                timer1.setInterval(500);//setInterval 500 ms = 0.5 sec (1000 ms = 1 sec)
                timer1.start();
            }
            
        }
    );
    IN2.onEnable(
        [](){
            if(timer2.isStarted()){
                timer2.stop();
                timer3.stop();
            }else{
                timer2.setInterval(1000);//setInterval 1000 ms = 1 sec (1000 ms = 1 sec)
                timer2.start();
                timer3.setInterval(10);
                timer3.start();
            }
            
        }
    );
}
void loop(){
    //process main input & output
    process();
    unsigned long now = millis();
    //process the timer
    timer1.process(now);
    timer2.process(now);
    timer3.process(now);
    timer4.process(now);
}