// #ifdef _MTE_CORE_H
#ifndef _INPUT_EVENT_H
#define _INPUT_EVENT_H

#include "Arduino.h"
typedef void (*inputevent_callback_active);
class InputEvent
{
private:
    int8_t _pinIn;
    inputevent_callback_active _cb_Active;
public:
    InputEvent(int8_t pinIn);
    // ~InputEvent();
    bool isActive();
    void onActive(inputevent_callback_active cb);
    void onActiveDuration(unsigned long timerMS);

    void process();
};
#endif //_INPUT_EVENT_H
// #endif //_MTE_CORE_H

InputEvent::InputEvent(int8_t pinIn)
{
    _pinIn = pinIn;
    pinMode(pinIn,INPUT_PULLUP);
}

// InputEvent::~InputEvent()
// {
// }
InputEvent::isActive(){
    return digitalRead(_pinIn);
}
InputEvent::onActive(inputevent_callback_active cb){
    _cb_Active = cb;
}
InputEvent::onActiveDuration(unsigned long timerMS){

}
InputEvent::process(){
    unsigned long now = millis();
    
}