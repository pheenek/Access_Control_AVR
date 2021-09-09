
#include "access_ctl_contact_driver.h"

void (*contact_event_callback)(ContactEvent_t);

void contact_sensor_init(void)
{
  // Set contact sensor pin as an input
  DDRD &= ~(1 << DDD2);
  // any logical change generates an interrupt
  EICRA |= (1 << ISC00);
  // enable interrupt on contact sensor pin INT0
  EIMSK |= (1 << INT0);
}

void attach_contact_event_callback(void (*callback)(ContactEvent_t event))
{
  contact_event_callback = callback;
}

ContactEvent_t door_status(void)
{
  if (bit_is_clear(PIND, PIND2))
  {
    return DOOR_CLOSED;
  }
  else
  {
    return DOOR_OPEN;
  }
}

ISR(INT0_vect)
{
  if (!contact_event_callback) return;
  
  if (bit_is_clear(PIND, PIND2))
  {
    contact_event_callback(DOOR_CLOSED);
  }
  else
  {
    contact_event_callback(DOOR_OPEN);
  }
}
 
