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
// Define where debug output will be printed.
#define DEBUG_PRINTER Serial
// Setup debug printing macros.
#ifdef MTECORE_DEBUG
  //pin mapping for MTE-miniController V2.0
  String PIN_TO_LABEL(uint8_t pin){
    switch (pin)
    {
    case 2:
      return "IN1";
      break;
    case 3:
      return "IN2";
      break;
    case 4:
      return "IN3";
      break;
    case 5:
      return "IN4";
      break;
    case 11:
      return "IN5";
      break;
    case 12:
      return "IN6";
      break;
    case 13:
      return "IN7";
      break;
    case 10:
      return "IN8";
      break;
    case A7:
      return "IN9";
      break;
    case 9:
      return "IN10";
      break;
    case A6:
      return "IN11";
      break;
    case A4:
      return "IN12";
      break;
      //output
    case A3:
      return "OUT1";
      break;
    case A2:
      return "OUT2";
      break;
    case A1:
      return "OUT3";
      break;
    case A0:
      return "OUT4";
      break;
    case 6:
      return "OUT5";
      break;
    case 7:
      return "OUT6";
      break;
    case 8:
      return "OUT7";
      break;
    
    default:
      break;
    }
  }
	#define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
	#define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
	#define DEBUG_PRINT(...) {}
	#define DEBUG_PRINTLN(...) {}
#endif

#include "util/InputCore.h"
#include "util/OutputCore.h"
#include "util/TimerCore.h"
#include "util/CounterCore.h"
#ifdef _ENABLE_F3_ANALOG || _ENABLE_F4_ANALOG || _ENABLE_F5_ANALOG || _ENABLE_F7_ANALOG
  #include "util/AnalogCore.h"
#endif
      InputCore IN1(2);
      InputCore IN2(3);
      InputCore IN3(4);
      InputCore IN4(5);
      InputCore IN5(11);
      InputCore IN6(12);
      InputCore IN7(13);
      InputCore IN8(10);
//Settings IN9
#ifdef _ENABLE_F7_ANALOG
        AnalogCore F7(A7); //enable F7 as Analog
#else 
        InputCore IN9(A7);
#endif
//end Settings
      InputCore IN10(9);

//Settings IN11
#ifdef _ENABLE_F5_ANALOG
        AnalogCore F5(A6); //enable F5 as Analog
#else
        InputCore IN11(A6);
#endif
//end Settings

//Settings IN12
#ifdef _ENABLE_F3_ANALOG
        AnalogCore F3(A4); //enable F3 as Analog
#elif defined _ENABLE_F3_I2C
  #ifndef _ENABLE_F4_I2C
    #error "Cannot enable F3 when F4 as I2C is disable!"
  #else
    //enable i2c F3
  #endif
#else
        InputCore IN12(A4); //enable IN12
#endif
//end Settings IN12

#ifdef _ENABLE_F4_ANALOG
        AnalogCore F4(A5); //enable F4 as Analog
#elif defined _ENABLE_F4_I2C
  #ifndef _ENABLE_F3_I2C
    #error "Cannot enable F4 when F3 as I2C is disable!"
  #else
    //enable i2c F4
  #endif
#endif
//OUTPUT
      OutputCore OUT1(A3);
      OutputCore OUT2(A2);
      OutputCore OUT3(A1);
      OutputCore OUT4(A0);
      OutputCore OUT5(6);
      OutputCore OUT6(7);
      OutputCore OUT7(8);

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
  #ifndef _ENABLE_F7_ANALOG
    IN9.process(now);
  #else
    F7.process(now); //F7 analog process
  #endif

  IN10.process(now);

  #ifndef _ENABLE_F5_ANALOG
    IN11.process(now);
  #else
    F5.process(now); //F5 analog process
  #endif

  #ifdef _ENABLE_F4_ANALOG
    F4.process(now); //F4 analog process
  #endif

  #ifndef _ENABLE_F3_ANALOG
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