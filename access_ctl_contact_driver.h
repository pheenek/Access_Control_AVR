
#ifndef ACCESS_CTL_CONTACT_DRIVER_H
#define ACCESS_CTL_CONTACT_DRIVER_H

#include "global_inc.h"
#include "timing_driver.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum CONTACT_EVENT{
  DOOR_CLOSED,
  DOOR_OPEN
}ContactEvent_t;

void contact_sensor_init(void);
ContactEvent_t door_status(void);
void attach_contact_event_callback(void (*callback)(ContactEvent_t));

#ifdef __cplusplus
}
#endif

#endif
 
