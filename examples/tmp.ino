#include "MteCore.h"
#include "Wire.h";
#define addr 0x27
#define BB B11111111
TwoWire *_wire;
Timer t(1000);
void setup(){
    _wire = &Wire;
    _wire->begin();
    _wire->beginTransmission(addr);
    _wire->write(BB);
    _wire->endTransmission();
    Serial.begin(9600);
    t.onTimeout(readAll);
    t.start();
}
void loop(){
    process();
    t.process(millis());
}

void readAll(){
    _wire->requestFrom(addr,8);
    if(_wire->available()){
        byte iInput = _wire->read();
        Serial.println(iInput,BIN);
    }
}