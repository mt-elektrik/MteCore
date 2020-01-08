#include "MteCore.h"
void IN1Aktif(){
    Serial.println("Oke");
}
void In1NonAktif(){
    Serial.println("Kaga Aktif");
}
void setup(){
    Serial.begin(9600);
    IN1.onActive(IN1Aktif);
    IN1.onRelease(In1NonAktif);
}
void loop(){
    process();
}   