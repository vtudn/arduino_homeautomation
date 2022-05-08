#include "LD_Project.h"
#include "soil_sensor.h"
#include <Arduino.h>
#include "LD_Project.h"

void soil_init(void){
  pinMode(SOIL, INPUT);
  pinMode(SOIL_IN1, OUTPUT);
  pinMode(SOIL_IN2, OUTPUT);
}
uint8_t  soil_val=0;
void soil_run( int soil_read){
    if (soil_read <= 70) {
      digitalWrite(SOIL_IN1, HIGH);
      digitalWrite(SOIL_IN2, LOW);
    }
    else {
      digitalWrite(SOIL_IN1, LOW);
      digitalWrite(SOIL_IN2, LOW);
    }

}
