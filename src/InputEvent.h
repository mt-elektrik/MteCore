// #ifdef _MTE_CORE_H
#ifndef _INPUT_EVENT_H 
#define _INPUT_EVENT_H 
#include "Arduino.h"


typedef void(*inputEvent_State_Callback)();

class InputEvent {
    protected:
    private:
        bool firstState;
        InputEvent(const InputEvent&);
        InputEvent& operator=(const InputEvent&);
        const byte _defaultDelay = 20;
        unsigned long lastDebounceTime;
        bool lastButtonState=HIGH;
        uint8_t _pinIn;
        inputEvent_State_Callback _cba;
        inputEvent_State_Callback _cbna;
    public:
        explicit InputEvent(uint8_t pinIn);
        virtual~InputEvent();
        void onActive(inputEvent_State_Callback cb);
        void onRelease(inputEvent_State_Callback cb);
        bool isActive();
        void process();
};
InputEvent::InputEvent(uint8_t pinIn) {
    _pinIn=pinIn;
}

InputEvent::~InputEvent() {}

void InputEvent::onActive(inputEvent_State_Callback cb) {
    _cba=cb;
}
void InputEvent::onRelease(inputEvent_State_Callback cb ){
    _cbna=cb;
}
bool InputEvent::isActive(){
    return !digitalRead(_pinIn);
}
void InputEvent::process(){
  int reading = digitalRead(_pinIn);
  if (millis() - lastDebounceTime > _defaultDelay) {
        if(reading!=lastButtonState){
            firstState=true;
            if(reading==LOW){
                if(_cba){
                    _cba();
                }
            }else{
                if(_cbna){
                    _cbna();
                }
            }
        }else{
            if(!firstState){
                firstState=true;
                if(reading==LOW){
                    if(_cba){
                        _cba();
                    }
                }else{
                    if(_cbna){
                        _cbna();
                    }
                }
            }
        }
    lastButtonState = reading;
    lastDebounceTime = millis();  
  }
//   if (reading != lastButtonState) {
//     lastDebounceTime = millis();
//   }
//   if (millis() - lastDebounceTime > 20) {
//     // if(reading == LOW){
//     //     if(_cba){
//     //         _cba;
//     //     }
//     // }
//     Serial.println(reading);
//   }
//   lastButtonState = reading;
}
#endif //_INPUT_EVENT_H
// #endif //_MTE_CORE_H