
#include "access_ctl_lock_driver.h"

void lock_init(void)
{
  // set the lock pin as an output
  DDRB |= (1 << DDB5);
}

void open_lock(void)
{
  PORTB |= (1 << PORTB5);
}

void close_lock(void)
{
  PORTB &= ~(1 << PORTB5);
}
