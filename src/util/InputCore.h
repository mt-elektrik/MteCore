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
        uint32_t debounceDelay=50;
        unsigned long lastDebounceTime;
        bool lastState=HIGH;

        unsigned long lastDebounceTimeOnChange;
        bool lastStateOnChange;

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
        bool isEnable();
        void process(unsigned long now);
        void setDebounceDelay(uint32_t delayms);
};
InputCore::InputCore(uint8_t pinIn)
 {
    //  DEBUG_PRINTLN(" : begin use pin " + pinIn);
    _pinIn=pinIn;
    
    if(_pinIn == A6 || _pinIn == A7){
        pinMode(pinIn,INPUT);
        lastStateOnChange= analogRead(_pinIn)>1000 ? 0:1;
        
    }else{
        pinMode(pinIn,INPUT_PULLUP);
        lastStateOnChange= digitalRead(pinIn);
    }
}

InputCore::~InputCore() {}

void InputCore::onEnable(inputCore_State_Callback cb) {
    DEBUG_PRINT(PIN_TO_LABEL(_pinIn));
    DEBUG_PRINTLN(" : Set Callback onEnable");
    _cba=cb;
}
void InputCore::onDisable(inputCore_State_Callback cb ){
    DEBUG_PRINT(PIN_TO_LABEL(_pinIn));
    DEBUG_PRINTLN(" : Set Callback onDisable");
    _cbna=cb;
}
void InputCore::onChange(inputCore_State_Callback cb){
    DEBUG_PRINT(PIN_TO_LABEL(_pinIn));
    DEBUG_PRINTLN(" : Set Callback onChange");
    _cbc=cb;
}
bool InputCore::isEnable(){
    DEBUG_PRINT(PIN_TO_LABEL(_pinIn));
    DEBUG_PRINTLN(" : Hit isEnable !"); 
    if(_pinIn == A6 || _pinIn == A7){
         return analogRead(_pinIn)>1000 ? 0:1;
    }else{
         return !digitalRead(_pinIn);
    }
}
void InputCore::process(unsigned long now){
    int reading;
    if(_pinIn == A6 || _pinIn == A7){
         reading = analogRead(_pinIn)>1000 ? 1:0;
    }else{
         reading = digitalRead(_pinIn);
    }
    if (now - lastDebounceTimeOnChange > 20) {
        if(reading!=lastStateOnChange){
            DEBUG_PRINT(PIN_TO_LABEL(_pinIn));
            DEBUG_PRINT(" : onChange TimeStamp =>"); 
            DEBUG_PRINTLN(now);
        /* onChange */
        if(_cbc){
            DEBUG_PRINT(PIN_TO_LABEL(_pinIn));
            DEBUG_PRINT(" : Hit Callback onChange TimeStamp => "); 
            DEBUG_PRINTLN(now +(now - lastDebounceTimeOnChange));
            _cbc();
        }
        /* ------- */
      }
    lastStateOnChange = reading;
    lastDebounceTimeOnChange = now;  
    }
    if(!firstState){
        firstState=true;
        if(reading==LOW){
            if(_cba){
                DEBUG_PRINT(PIN_TO_LABEL(_pinIn));
                DEBUG_PRINT(" : Hit First State Callback onEnable TimeStamp => ");
                DEBUG_PRINTLN(now +(now - lastDebounceTime));
                _cba();
            }
        }else{
            if(_cbna){
                DEBUG_PRINT(PIN_TO_LABEL(_pinIn));
                DEBUG_PRINT(" : Hit First State Callback onDisable TimeStamp => ");
                DEBUG_PRINTLN(now +(now - lastDebounceTime));
                _cbna();
            }
        }
    }else{
        if (now - lastDebounceTime > debounceDelay) {
            if(reading!=lastState){
                if(reading==LOW){
                    /* onEnable */
                    if(_cba){
                        DEBUG_PRINT(PIN_TO_LABEL(_pinIn));
                        DEBUG_PRINT(" : Hit Callback onEnable TimeStamp => "); 
                        DEBUG_PRINTLN(now +(now - lastDebounceTime));
                        _cba();
                    }
                    /* ------- */
                }else{
                    /* onDisable */
                    if(_cbna){
                        DEBUG_PRINT(PIN_TO_LABEL(_pinIn));
                        DEBUG_PRINT(" : Hit Callback onDisable TimeStamp => ");
                        DEBUG_PRINTLN(now +(now - lastDebounceTime));
                        _cbna();
                    }
                    /* --------- */
                }
            }
        lastState = reading;
        lastDebounceTime = now;  
    }
    }
}
void InputCore::setDebounceDelay(uint32_t delayms){
    DEBUG_PRINT(PIN_TO_LABEL(_pinIn));
    DEBUG_PRINT(" : setDebounceDelay to ");
    DEBUG_PRINT(delayms);
    DEBUG_PRINTLN("ms.");
    debounceDelay = delayms;
}

#endif //_INPUT_CORE_H
#endif //_MTE_CORE_H