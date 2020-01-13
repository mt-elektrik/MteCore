/*
  MteCore - Library For MTE Controller

  Muara Teknik Elektrik
  https://github.com/mt-elektrik/MteCore


  Copyright 2020 Muara Teknik Elektrik

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef _MTE_CORE_H
#define _MTE_CORE_H
#include "Arduino.h"
#include "src/InputCore.h"
#include "src/OutputCore.h"
#include "src/TimerCore.h"
#include "src/CounterCore.h"
#ifdef _ENABLE_F3_ANALOG || _ENABLE_F4_ANALOG || _ENABLE_F5_ANALOG || _ENABLE_F7_ANALOG
  #include "src/AnalogCore.h"
#endif
static InputCore IN1(2);
static InputCore IN2(3);
static InputCore IN3(4);
static InputCore IN4(5);
static InputCore IN5(11);
static InputCore IN6(12);
static InputCore IN7(13);
static InputCore IN8(10);
//Settings IN9
#ifdef _ENABLE_F7_ANALOG
  static AnalogCore F7(A7); //enable F7 as Analog
#else 
  static InputCore IN9(A7);
#endif
//end Settings
static InputCore IN10(9);

//Settings IN11
#ifdef _ENABLE_F5_ANALOG
  static AnalogCore F5(A6); //enable F5 as Analog
#else
  static InputCore IN11(A6);
#endif
//end Settings

//Settings IN12
#ifdef _ENABLE_F3_ANALOG
  static AnalogCore F3(A4); //enable F3 as Analog
#elif defined _ENABLE_F3_I2C
  #ifndef _ENABLE_F4_I2C
    #error "Cannot enable F3 when F4 as I2C is disable!"
  #else
    //enable i2c F3
  #endif
#else
  static InputCore IN12(A4); //enable IN12
#endif
//end Settings IN12

#ifdef _ENABLE_F4_ANALOG
  static AnalogCore F4(A5); //enable F4 as Analog
#elif defined _ENABLE_F4_I2C
  #ifndef _ENABLE_F3_I2C
    #error "Cannot enable F4 when F3 as I2C is disable!"
  #else
    //enable i2c F4
  #endif
#endif
//OUTPUT
static OutputCore OUT1(A3);
static OutputCore OUT2(A2);
static OutputCore OUT3(A1);
static OutputCore OUT4(A0);
static OutputCore OUT5(6);
static OutputCore OUT6(7);
static OutputCore OUT7(8);

void process(){
  unsigned long now = millis();
  IN1.process(now);
  IN2.process(now);
  IN3.process(now);
  IN4.process(now);
  IN5.process(now);
  IN6.process(now);
  IN7.process(now);
  IN8.process(now);
  #ifdef IN9
    IN9.process(now);
  #else
    F7.process(now); //F7 analog process
  #endif
  IN10.process(now);
  #ifdef IN11
    IN11.process(now);
  #else
    F5.process(now); //F5 analog process
  #endif
  #ifdef _ENABLE_F4_ANALOG
    F4.process(now); //F4 analog process
  #endif
  #ifdef IN12
    IN12.process(now);
  #else
    F3.process(now); //F3 Analog process
  #endif
  OUT1.process(now);
  OUT2.process(now);
  OUT3.process(now);
  OUT4.process(now);
  OUT5.process(now);
  OUT6.process(now);
  OUT7.process(now);
}
#endif