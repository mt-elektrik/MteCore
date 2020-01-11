#ifdef _MTE_CORE_H
#ifndef _INPUT_CORE_H 
#define _INPUT_CORE_H 
#include "Arduino.h"


typedef void(*inputCore_State_Callback)();

class InputCore {
    protected:
    private:
        bool firstState;
        InputCore(const InputCore&);
        InputCore& operator=(const InputCore&);
        const uint8_t debounceDelay = 20;
        unsigned long lastDebounceTime;
        bool lastState=HIGH;
        bool lastStateOnChange=HIGH;
        uint8_t _pinIn;
        inputCore_State_Callback _cba;
        inputCore_State_Callback _cbna;
        inputCore_State_Callback _cbc;
    public:
        explicit InputCore(uint8_t pinIn);
        virtual~InputCore();
        void onEnable(inputCore_State_Callback cb);
        void onDisable(inputCore_State_Callback cb);
        void onChange(inputCore_State_Callback cb);
        bool onEnable();
        void process(unsigned long now);
};
InputCore::InputCore(uint8_t pinIn) {
    _pinIn=pinIn;
    pinMode(pinIn,INPUT_PULLUP);
}

InputCore::~InputCore() {}

void InputCore::onEnable(inputCore_State_Callback cb) {
    _cba=cb;
}
void InputCore::onDisable(inputCore_State_Callback cb ){
    _cbna=cb;
}
void InputCore::onChange(inputCore_State_Callback cb){
    _cbc=cb;
}
bool InputCore::onEnable(){
    return !digitalRead(_pinIn);
}
void InputCore::process(unsigned long now){
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

#endif //_INPUT_CORE_H
#endif //_MTE_CORE_H