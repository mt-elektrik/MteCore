#ifdef _MTE_CORE_H
    #ifndef _TIMER_CORE_H 
    #define _TIMER_CORE_H 
    #include "Arduino.h"
    typedef void(*Timer_cb)();
    class Timer
    {
    private:
        Timer_cb _cb_timeout;
        Timer_cb _cb_started;
        Timer_cb _cb_stoped;
        unsigned long _interval;
        bool _isStarted = false;
        unsigned long _timestamp;
    public:
        Timer(unsigned long interval=-1);
        ~Timer();
        void start();
        void stop();
        void onTimeout(Timer_cb cb);
        void onStarted(Timer_cb cb);
        void onStoped(Timer_cb cb);
        void process(unsigned long now);
        bool isStarted();
        void setInterval(unsigned long interval);
    };
    
    Timer::Timer(unsigned long interval=-1)
    {
        _interval = interval;
    }
    
    Timer::~Timer()
    {
    }
    void Timer::start(){
        _timestamp=millis();
        _isStarted=true;
        if(_cb_started)_cb_started();
    }
    void Timer::stop(){
        _isStarted=false;
        if(_cb_stoped)_cb_stoped();
    }
    void Timer::onTimeout(Timer_cb cb){
        _cb_timeout = cb;
    }
    void Timer::onStarted(Timer_cb cb){
        _cb_started = cb;
    }
    void Timer::onStoped(Timer_cb cb){
        _cb_stoped = cb;
    }
    void Timer::process(unsigned long now){
        if (_isStarted){
            if(now - _timestamp > _interval){
                if(_cb_timeout)_cb_timeout();
                _timestamp=now;
            }
        }
    }
    bool Timer::isStarted(){
        return _isStarted;
        
    }
    void Timer::setInterval(unsigned long interval){
        _interval = interval;
    }
    #endif //_TIMER_CORE_H
#endif //_MTE_CORE_H