#include "LD_Project.h"
#include "pir_sensor.h"
void pir_init(void){
  pinMode(PIR, INPUT);
  pinMode(LED_CLOSE, OUTPUT);
  pinMode(LED_OPEN, OUTPUT);
  pinMode(PIR_IN1, OUTPUT); 
  pinMode(PIR_IN2, OUTPUT); 
}
int Pir1=0;
int Pir2=0;
void pir_run(void){
  read_pir = digitalRead(PIR);
  if(read_pir == 1){
    Pir2=0;
    Pir1++;
    if(Pir1==1){
      SPrint("!PIR:DETECTED#");
    }   
    if(Pir1==10){
      Pir1=2;
    }
    digitalWrite(LED_OPEN, HIGH);
    digitalWrite(LED_CLOSE, LOW);
    digitalWrite(PIR_IN1, HIGH);
    digitalWrite(PIR_IN2, LOW);
  } else{
    Pir1=0;  
    Pir2++;
    if(Pir2==1){
      SPrint("!PIR:UNDETECTED#");
    }
    if(Pir2==10){
      Pir2=2;
    }
    digitalWrite(LED_OPEN, LOW);
    digitalWrite(LED_CLOSE, HIGH);
    digitalWrite(PIR_IN1, LOW);
    digitalWrite(PIR_IN2, HIGH);
  }
}
