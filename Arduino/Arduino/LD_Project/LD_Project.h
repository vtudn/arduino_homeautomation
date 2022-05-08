#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Arduino.h"

#define LED_OPEN    13
#define LED_CLOSE   12
#define LED_NOR     11
#define BUTTON_PIN  8
#define SOIL_IN1    7
#define SOIL_IN2    6
#define PIR_IN1     5
#define PIR_IN2     4
#define GAS_RED     3
#define DHTPIN      2
#define GAS_YEL     1
#define GAS_GRE     0
#define DHTTYPE     DHT11
#define SOIL        A0
#define PIR         A1
#define GAS         A2
#define GAS_DENSITY A3

void setup();
void SPrint(const char *msg);
void SPrints(const char *msg);
#ifdef __cplusplus
}
#endif

#endif
