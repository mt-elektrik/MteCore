// #ifdef _MTE_CORE_H
#ifndef _OUTPUT_EVENT_H 
#define _OUTPUT_EVENT_H 
#include "Arduino.h"


typedef void(*OutputEvent_State_Callback)();

class OutputEvent {
    protected:
    private:
        bool firstState;
        OutputEvent(const OutputEvent&);
        OutputEvent& operator=(const OutputEvent&);
        const uint8_t debounceDelay = 20;
        unsigned long lastDebounceTime;
        bool lastState=LOW;
        uint8_t _pinIn;
        OutputEvent_State_Callback _cba;
        OutputEvent_State_Callback _cbna;
        OutputEvent_State_Callback _cbc;
    public:
        explicit OutputEvent(uint8_t pinIn);
        virtual~OutputEvent();
        void onEnable(OutputEvent_State_Callback cb);
        void onDisable(OutputEvent_State_Callback cb);
        void onChange(OutputEvent_State_Callback cb);
        bool isEnable();
        void process();
        bool enable();
        bool disable();
};
OutputEvent::OutputEvent(uint8_t pinIn) {
    _pinIn=pinIn;
    pinMode(pinIn,OUTPUT);
}

OutputEvent::~OutputEvent() {}

void OutputEvent::onEnable(OutputEvent_State_Callback cb) {
    _cba=cb;
}
void OutputEvent::onDisable(OutputEvent_State_Callback cb ){
    _cbna=cb;
}
void OutputEvent::onChange(OutputEvent_State_Callback cb){
    _cbc=cb;
}
bool OutputEvent::isEnable(){
    return !digitalRead(_pinIn);
}
void OutputEvent::process(){
  int reading = digitalRead(_pinIn);
  if (millis() - lastDebounceTime > debounceDelay) {
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
    lastDebounceTime = millis();  
  }
}
bool OutputEvent::enable(){
    digitalWrite(_pinIn,HIGH);
}
bool OutputEvent::disable(){
    digitalWrite(_pinIn,LOW);
}
#endif //_OUTPUT_EVENT_H
// #endif //_MTE_CORE_H