
#include "access_ctl_contact.h"

AccessCtlContactSensor::AccessCtlContactSensor(void)
{
  contact_sensor_init();
}

bool AccessCtlContactSensor::doorClosed(void)
{
  return (door_status() == DOOR_CLOSED);
}

bool AccessCtlContactSensor::doorOpen(void)
{
  return (door_status() == DOOR_OPEN);
}

void AccessCtlContactSensor::attachContactEventCallback(void (*callback)(ContactEvent_t))
{
  attach_contact_event_callback(callback);
}
 
