#ifndef BUTTON_PROCESSING_H_
#define BUTTON_PROCESSING_H_

#ifdef __cplusplus
extern "C" {
#endif

uint8_t flag_1s;

void fsm_for_input_processing(void);
void button_init(void);
void button_more_than_1s(void);

#ifdef __cplusplus
}
#endif

#endif
