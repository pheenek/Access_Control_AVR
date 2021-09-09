
#include "access_exit_btn_driver.h"

void (*exit_event_callback)(void);

void exit_btn_init(void)
{
  // Set exit button pin as an input
  DDRD &= ~(1 << DDD3);
  // any logical change generates an interrupt
  EICRA |= (1 << ISC10);
  // enable interrupt on contact sensor pin INT1
  EIMSK |= (1 << INT1);
}

ExitBtnStatus_t exit_btn_status(void)
{
  if (bit_is_clear(PIND, PIND3))
  {
    return EXIT_ACTIVATED;
  }

  return EXIT_DEACTIVATED;
}

void attach_exit_event_callback(void (*callback)(void))
{
  exit_event_callback = callback;
}

ISR(INT1_vect)
{
  if (!exit_event_callback) return;
  
  if (bit_is_clear(PIND, PIND3))
  {
    exit_event_callback();
  }
}
 
