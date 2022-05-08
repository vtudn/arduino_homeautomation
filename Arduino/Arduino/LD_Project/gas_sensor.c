#include "LD_Project.h"
#include "gas_sensor.h"
#include "LD_Project.h"
void gas_init(void){
  pinMode(GAS, INPUT);  
  pinMode(GAS_DENSITY, INPUT);
  pinMode(GAS_RED, OUTPUT);
  pinMode(GAS_YEL, OUTPUT);
  pinMode(GAS_GRE, OUTPUT);
}
int update1=0;
int update2=0;
int update3=0;
void gas_run(void){
  if(digitalRead(GAS) == HIGH && digitalRead(GAS_DENSITY) == HIGH){ 
    digitalWrite(GAS_RED, HIGH);
    digitalWrite(GAS_YEL, LOW);
    digitalWrite(GAS_GRE, LOW);
    update2=0;
    update3=0;
    if(update1==1){
      SPrint("!GAS:HIGH#");
    }
    update1++;
    if(update1==10){
      update1=2;
    } 
  }
  else if(digitalRead(GAS) == HIGH && digitalRead(GAS_DENSITY) == LOW){
    digitalWrite(GAS_RED, LOW);
    digitalWrite(GAS_YEL, HIGH);
    digitalWrite(GAS_GRE, LOW);
    update1=0;
    update3=0;
    if(update2==1){
      SPrint("!GAS:MEDIUM#");
    }
    update2++;
    if(update2==10){
      update2=2;
    }
  }
  else if(digitalRead(GAS) == LOW && digitalRead(GAS_DENSITY) == LOW) {
    digitalWrite(GAS_RED, LOW);
    digitalWrite(GAS_YEL, LOW);
    digitalWrite(GAS_GRE, HIGH);
    update1=0;
    update2=0;
    if(update3==1){
      SPrint("!GAS:LOW#");
    }
    update3++;
    if(update3==10){
      update3=2;
    }   
  }
}
