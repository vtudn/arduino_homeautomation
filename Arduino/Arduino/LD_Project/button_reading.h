#ifndef BUTTON_READING_H_
#define BUTTON_READING_H_

#ifdef __cplusplus
extern "C" {
#endif

#define N0_OF_BUTTONS                 1
#define DURATION_FOR_AUTO_INCREASING  100
#define BUTTON_IS_PRESSED             0
#define BUTTON_IS_RELEASED            1

#define BUTTON_IDX                    0

void button_reading(void);
unsigned char is_button_pressed(unsigned char index);
unsigned char is_button_pressed_1s(unsigned char index);

#ifdef __cplusplus
}
#endif

#endif
