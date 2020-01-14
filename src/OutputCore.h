#ifdef _MTE_CORE_H
#ifndef _OUTPUT_CORE_H 
#define _OUTPUT_CORE_H 
#include "Arduino.h"
typedef void(*OutputCore_State_Callback)();
class OutputCore {
    protected:
    private:
        bool firstState;
        OutputCore(const OutputCore&);
        OutputCore& operator=(const OutputCore&);
        const uint8_t debounceDelay = 20;
        unsigned long lastDebounceTime;
        bool lastState=LOW;
        uint8_t _pinIn;
        OutputCore_State_Callback _cba;
        OutputCore_State_Callback _cbna;
        OutputCore_State_Callback _cbc;
    public:
        explicit OutputCore(uint8_t pinIn);
        virtual~OutputCore();
        void onEnable(OutputCore_State_Callback cb);
        void onDisable(OutputCore_State_Callback cb);
        void onChange(OutputCore_State_Callback cb);
        bool isEnable();
        void process(unsigned long now);
        bool enable();
        bool disable();
};
OutputCore::OutputCore(uint8_t pinIn) {
    _pinIn=pinIn;
    pinMode(pinIn,OUTPUT);
    digitalWrite(pinIn,HIGH);
}

OutputCore::~OutputCore() {}

void OutputCore::onEnable(OutputCore_State_Callback cb) {
    _cba=cb;
}
void OutputCore::onDisable(OutputCore_State_Callback cb ){
    _cbna=cb;
}
void OutputCore::onChange(OutputCore_State_Callback cb){
    _cbc=cb;
}
bool OutputCore::isEnable(){
    return !digitalRead(_pinIn);
}
void OutputCore::process(unsigned long now){
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
bool OutputCore::enable(){
    digitalWrite(_pinIn,LOW);
    return digitalRead(_pinIn)==LOW;
}
bool OutputCore::disable(){
    digitalWrite(_pinIn,HIGH);
    return digitalRead(_pinIn)==HIGH;
}
#endif //_OUTPUT_CORE_H
#endif //_MTE_CORE_H