
#ifndef ACCESS_CTL_CONTACT_H
#define ACCESS_CTL_CONTACT_H

#include "access_ctl_contact_driver.h"

// TODO: enable contact sensor interrupts
class AccessCtlContactSensor
{
  private:
    bool activated = false;

  public:
    AccessCtlContactSensor(void);
    ~AccessCtlContactSensor(void) {}

    bool doorClosed(void);
    bool doorOpen(void);
    void attachContactEventCallback(void (*callback)(ContactEvent_t));
};

#endif
 
