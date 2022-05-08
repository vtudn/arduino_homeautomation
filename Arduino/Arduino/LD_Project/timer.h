#ifndef TIMER_H_
#define TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define CLOCK_SPEED 16000000

// system timer
// tim1 16-bit
#define TIM1_PSC    64
#define TIM1_FREQ   100 // Hz (tick every 10ms)

// virtual timer
#define NUM_OF_TIM  2
#define TIM_CYCLE   10

uint32_t  timer_counter [NUM_OF_TIM];
uint8_t   timer_flag    [NUM_OF_TIM];

void timer_init(void);
void timer_set(uint8_t idx, uint32_t duration);
void timer_run(void);

#ifdef __cplusplus
}
#endif

#endif
