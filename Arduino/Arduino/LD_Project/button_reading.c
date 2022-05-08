#include "LD_Project.h"
#include "button_reading.h"

static uint8_t      buttonBuffer            [N0_OF_BUTTONS];
static uint8_t      debounceButtonBuffer1   [N0_OF_BUTTONS];
static uint8_t      debounceButtonBuffer2   [N0_OF_BUTTONS];
static uint8_t      flagForButtonPress1s    [N0_OF_BUTTONS];
static uint16_t     counterForButtonPress1s [N0_OF_BUTTONS];

void button_reading(void){
  for (char i = 0; i < N0_OF_BUTTONS; i++){
    debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
    debounceButtonBuffer1[i] = digitalRead(BUTTON_PIN);
    if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i]){
      buttonBuffer[i] = debounceButtonBuffer1[i];
      if (buttonBuffer[i] == BUTTON_IS_PRESSED){
        if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING){
          counterForButtonPress1s[i]++;
        }
        else {
          flagForButtonPress1s[i] = 1;
        }
      }
      else {
        counterForButtonPress1s[i] = 0;
        flagForButtonPress1s[i] = 0;
      }
    }
  }
}
 
unsigned char is_button_pressed(uint8_t index){
  if (index >= N0_OF_BUTTONS)
    return 0;
  return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

unsigned char is_button_pressed_1s(unsigned char index){
  if (index >= N0_OF_BUTTONS)
    return 0xff;
  return (flagForButtonPress1s[index] == 1);
}
