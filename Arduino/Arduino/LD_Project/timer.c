#include "LD_Project.h"
#include "timer.h"

void timer_init(void){
  // stop interrupts
  cli();
  // timer1 at 100Hz, prescaler 64
  // init entire reg
  TCCR1A = 0;
  TCCR1B = 0;
  // init counter
  TCNT1  = 0;
  // compare match reg
  OCR1A = (CLOCK_SPEED/(TIM1_PSC*TIM1_FREQ)) - 1;
  // CTC mode on (ATMEL 328/168)
  TCCR1B |= (1 << WGM12);
  // CS01 and CS00 bits for 64 prescaler
  TCCR1B |= (1 << CS01) | (1 << CS00);
  // enable interrupt
  TIMSK1 |= (1 << OCIE1A);
  // allow interrupts
  sei();
  
//  // timer0 at 2kHz, prescaler 64
//  TCCR0A = 0;
//  TCCR0B = 0;
//  TCNT0  = 0;
//  OCR0A = (CLOCK_SPEED/(TIM0_PSC*TIM0_FREQ)) - 1;
//  TCCR0A |= (1 << WGM01);
//  TCCR0B |= (1 << CS01) | (1 << CS00);
//  TIMSK0 |= (1 << OCIE0A);
//  // timer2 at 8kHz, prescaler 8
//  TCCR2A = 0;
//  TCCR2B = 0;
//  TCNT2  = 0;
//  OCR2A = (CLOCK_SPEED/(TIM2_PSC*TIM2_FREQ)) - 1;
//  TCCR2A |= (1 << WGM21);
//  TCCR2B |= (1 << CS21);
//  TIMSK2 |= (1 << OCIE2A);
}

void timer_set(uint8_t idx, uint32_t duration){
  if (idx >= NUM_OF_TIM) return;
  timer_counter[idx] = duration/TIM_CYCLE;
  timer_flag[idx] = 0;
}

void timer_run(void){
  for (uint8_t i = 0; i < NUM_OF_TIM; i++){
    if (timer_counter[i] > 0){
      timer_counter[i]--;
      if (timer_counter[i] == 0) timer_flag[i] = 1;
    }
  }
}
