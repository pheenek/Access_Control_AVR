
#include "timing_driver.h"

volatile unsigned long timing_millis = 0;

void timer_init(void)
{
  // enable timer2 (prescaler 64)
  TCCR2B |= (1 << CS22);
  // enable timer2 overflow interrupt
  TIMSK2 |= (1 << TOIE2);
}

unsigned long get_timing_millis(void)
{
	return timing_millis;
}

ISR(TIMER2_OVF_vect)
{
  // increment on every overflow (1 ms elapsed)
  timing_millis+= 1;
}
