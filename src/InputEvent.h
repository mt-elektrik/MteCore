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
        const uint8_t debounceDelay = 20;
        unsigned long lastDebounceTime;
        bool lastState=HIGH;
        bool lastStateOnChange=HIGH;
        uint8_t _pinIn;
        inputEvent_State_Callback _cba;
        inputEvent_State_Callback _cbna;
        inputEvent_State_Callback _cbc;
    public:
        explicit InputEvent(uint8_t pinIn);
        virtual~InputEvent();
        void onEnable(inputEvent_State_Callback cb);
        void onDisable(inputEvent_State_Callback cb);
        void onChange(inputEvent_State_Callback cb);
        bool onEnable();
        void process(unsigned long now);
};
InputEvent::InputEvent(uint8_t pinIn) {
    _pinIn=pinIn;
    pinMode(pinIn,INPUT_PULLUP);
}

InputEvent::~InputEvent() {}

void InputEvent::onEnable(inputEvent_State_Callback cb) {
    _cba=cb;
}
void InputEvent::onDisable(inputEvent_State_Callback cb ){
    _cbna=cb;
}
void InputEvent::onChange(inputEvent_State_Callback cb){
    _cbc=cb;
}
bool InputEvent::onEnable(){
    return !digitalRead(_pinIn);
}
void InputEvent::process(unsigned long now){
  int reading = digitalRead(_pinIn);
  if (now - lastDebounceTime > debounceDelay) {
        if(reading!=lastState){
            firstState=true;
                /* onChange */
                if(_cbc){
                    _cbc();
                }
                /* ------- */
            if(reading==LOW){
                /* onEnable */
                if(_cba){
                    _cba();
                }
                /* ------- */
            }else{
                /* onDisable */
                if(_cbna){
                    _cbna();
                }
                /* --------- */
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
    lastState = reading;
    lastDebounceTime = now;  
  }
}

#endif //_INPUT_EVENT_H
// #endif //_MTE_CORE_H