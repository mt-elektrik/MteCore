#include "MteCore.h"
void callback_OnActive(){
    Serial.println("onActive");
}
void callback_OnNotActive(){
    Serial.println("onNotActive");
}
void callback_OnChange(){
    Serial.println("onChange");
}
void setup(){
    Serial.begin(9600);
    
    IN11.onActive(callback_OnActive);
    IN11.onNotActive(callback_OnNotActive);
    IN11.onChange(callback_OnChange);

}
void loop(){
    // process();
    Serial.println(digitalRead(A6));
    delay(1000);
    
}   