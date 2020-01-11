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
/*
#define pinIN1 2
#define pinIN2 3
#define pinIN3 4
#define pinIN4 5
#define pinIN5 11
#define pinIN6 12
#define pinIN7 13
#define pinIN8 10
#define pinIN9 A7
#define pinIN10 9
#define pinIN11 A6
#define pinIN12 A4
*/
#ifndef _MTE_CORE_H
#define _MTE_CORE_H
#include "Arduino.h"
#include "src/InputEvent.h"
#include "src/OutputEvent.h"
static InputEvent IN1(2);
static InputEvent IN2(3);
static InputEvent IN3(4);
static InputEvent IN4(5);
static InputEvent IN5(11);
static InputEvent IN6(12);
static InputEvent IN7(13);
// #ifndef _MTE_FCORE_H
static InputEvent IN8(10);
static InputEvent IN9(A7);
static InputEvent IN10(9);
static InputEvent IN11(A6);
static InputEvent IN12(A4);
// #endif //_MTE_FCORE_H
//OUTPUT
static OutputEvent OUT1(A3);
static OutputEvent OUT2(A2);
static OutputEvent OUT3(A1);
static OutputEvent OUT4(A0);
static OutputEvent OUT5(6);
static OutputEvent OUT6(7);
static OutputEvent OUT7(8);

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