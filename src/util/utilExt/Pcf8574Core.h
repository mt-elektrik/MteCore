#include "Wire.h"
class Pcf8574Core
{
private:
    TwoWire *_wire;
    uint8_t _address;
    byte writeMode 	= 	B00000000;
	byte readMode 	= 	B00000000;
public:
    Pcf8574Core(uint8_t address);
    ~Pcf8574Core();
    void begin();
    void pinMode(uint8_t pin, uint8_t mode);
};

Pcf8574Core::Pcf8574Core(uint8_t address)
{
    _wire = &Wire;
	_address = address;
}

Pcf8574Core::~Pcf8574Core()
{
}
void Pcf8574Core::begin(){
    if (writeMode>0 || readMode>0){
		_wire->beginTransmission(_address);
		byte usedPin = writeMode | readMode;
		_wire->write(~usedPin);
		_wire->endTransmission();
	}
}
void Pcf8574Core::pinMode(uint8_t pin, uint8_t mode){
    if (mode == OUTPUT){
		writeMode = writeMode | bit(pin);
		readMode =  readMode & ~bit(pin);
	}else if (mode == INPUT){
		writeMode = writeMode & ~bit(pin);
		readMode =   readMode | bit(pin);
	}
}
