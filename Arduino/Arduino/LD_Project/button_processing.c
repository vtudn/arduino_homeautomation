#include "LD_Project.h"
#include "button_reading.h"
#include "button_processing.h"

enum ButtonState {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND};
enum ButtonState buttonState = BUTTON_RELEASED;

void fsm_for_input_processing(void){
  switch (buttonState){
  case BUTTON_RELEASED:
    if (is_button_pressed(BUTTON_IDX)){
      buttonState = BUTTON_PRESSED;
      digitalWrite(LED_NOR, !digitalRead(LED_NOR));
      if(digitalRead(LED_NOR)==HIGH){
        SPrint("!LED:ON#");
      }
      else SPrint("!LED:OFF#");
    }
    break;
       
  case BUTTON_PRESSED:
    if (!is_button_pressed(BUTTON_IDX))
      buttonState = BUTTON_RELEASED;
    else
      if(is_button_pressed_1s(BUTTON_IDX))
        buttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND;
    break;
    
  case BUTTON_PRESSED_MORE_THAN_1_SECOND:
    flag_1s = 1;
    if (!is_button_pressed(BUTTON_IDX)){
      flag_1s = 0; 
      buttonState = BUTTON_RELEASED;
    }
    break;
  }
}

void button_init(void){
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_NOR, OUTPUT); 
}

void button_more_than_1s(void){
  digitalWrite(LED_NOR, !digitalRead(LED_NOR));
}
