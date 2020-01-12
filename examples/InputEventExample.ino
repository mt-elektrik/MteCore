#include "MteCore.h"
void callback_onEnable(){
    Serial.println("onEnable");
}
void callback_onDisable(){
    Serial.println("onDisable");
}
void callback_OnChange(){
    Serial.println("onChange");
}
void setup(){
    Serial.begin(9600);
    
    IN11.onEnable(callback_onEnable);
    IN11.onDisable(callback_onDisable);
    IN11.onChange(callback_OnChange);
}
void loop(){
    // process();
    Serial.println(digitalRead(A6));
    delay(1000);
    
}   