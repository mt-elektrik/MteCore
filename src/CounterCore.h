// #ifdef _MTE_CORE_H
    #ifndef _COUNTER_CORE_H 
    #define _COUNTER_CORE_H 
    #include "Arduino.h"
    typedef void(*counter_core_callback)(); 
    class CounterCore
    {
    private:
        unsigned long _counterValue;
        unsigned long _valueMax;
        int _increaseValue;
        counter_core_callback _cb_onChange;
        counter_core_callback _cb_onReset;
        counter_core_callback _cb_onTriggered;
    public:
        CounterCore(/* args */);
        ~CounterCore();
        unsigned long getCounterValue();
        void setValueMax(unsigned long value);
        void setIncreaseValue(int value = 1);
        void reset();
        void trigger();
        void onChange(counter_core_callback cb);
        void onReset(counter_core_callback cb);
        void onTriggered(counter_core_callback cb);
    };
    
    CounterCore::CounterCore(/* args */)
    {
        _counterValue=0;
        _increaseValue=1;
        _valueMax=0;
    }
    
    CounterCore::~CounterCore()
    {
    }
    unsigned long CounterCore::getCounterValue(){
        return _counterValue;
    }
    void CounterCore::setValueMax(unsigned long value){
        _valueMax = value;
    }
    void CounterCore::setIncreaseValue(int value=1){
        _increaseValue = value;
    }
    void CounterCore::reset(){
        _counterValue=0;
        if(_cb_onChange)_cb_onChange();
        if(_cb_onReset)_cb_onReset();
    }
    void CounterCore::trigger(){
        _counterValue = _counterValue + _increaseValue;
        if(_cb_onTriggered)_cb_onTriggered();
        if(_counterValue >= _valueMax){
            reset();
        }else{
            if(_cb_onChange)_cb_onChange();
        }
    }
    void CounterCore::onChange(counter_core_callback cb){
        _cb_onChange = cb;
    }
    void CounterCore::onReset(counter_core_callback cb){
        _cb_onReset = cb;
    }
    void CounterCore::onTriggered(counter_core_callback cb){
        _cb_onTriggered = cb;
    }
    #endif // _COUNTER_CORE_H
// #endif _MTE_CORE_H