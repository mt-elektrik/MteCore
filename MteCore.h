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
static InputCore IN1(2);
static InputCore IN2(3);
static InputCore IN3(4);
static InputCore IN4(5);
static InputCore IN5(11);
static InputCore IN6(12);
static InputCore IN7(13);
// #ifndef _MTE_FCORE_H
static InputCore IN8(10);
static InputCore IN9(A7);
static InputCore IN10(9);
static InputCore IN11(A6);
static InputCore IN12(A4);
// #endif //_MTE_FCORE_H
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
  IN9.process(now);
  IN10.process(now);
  IN11.process(now);
  IN12.process(now);

  OUT1.process(now);
  OUT2.process(now);
  OUT3.process(now);
  OUT4.process(now);
  OUT5.process(now);
  OUT6.process(now);
  OUT7.process(now);
}
#endif