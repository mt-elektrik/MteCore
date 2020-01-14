#ifdef _MTE_CORE_H
    #ifndef _ANALOG_CORE_H 
    #define _ANALOG_CORE_H 
    #include "Arduino.h"
    typedef void(*analog_core_callback)(uint8_t value); 
    class AnalogCore
    {
    private:
        uint8_t _pinIn;
        analog_core_callback _cb_onChange;
        analog_core_callback _cb_onChangePrecision;
        unsigned long _timeStamp;
        uint16_t _temp_val; 
        uint8_t _temp_counter;
    public:
        AnalogCore(uint8_t pinIn);
        ~AnalogCore();
        void onChange(analog_core_callback cb);
        void onChangePrecision(analog_core_callback cb);
        void process(unsigned long now);
    };
    
    AnalogCore::AnalogCore(uint8_t pinIn)
    {
        _pinIn = pinIn;
        pinMode(pinIn,INPUT);
    }
    
    AnalogCore::~AnalogCore()
    {
    }
    void AnalogCore::onChange(analog_core_callback cb){
        _cb_onChange = cb;
    }
    void AnalogCore::onChangePrecision(analog_core_callback cb){
        _cb_onChangePrecision = cb;
    }
    void AnalogCore::process(unsigned long now){
        uint8_t v = analogRead(_pinIn);
        if(_cb_onChange)_cb_onChange(v);
        if(_cb_onChangePrecision){
            if(now - _timeStamp > 50 ){
                _temp_val += v;
                _timeStamp = now;
                _temp_counter++;
                if(_temp_counter==10){
                    _temp_counter=0;
                    _cb_onChangePrecision(_temp_val/10);
                }
            }
        }

    }
    
    #endif //_ANALOG_CORE_H
#endif // _MTE_CORE_H