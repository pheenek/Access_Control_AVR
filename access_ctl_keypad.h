
#ifndef ACCESS_CTL_KEYPAD_H
#define ACCESS_CTL_KEYPAD_H

#include "access_ctl_keypad_driver.h"

typedef enum {
  IDLE_STATE,
  DEFAULT_STATE,
  PIN_STATE,
  NAVIGATION_STATE
}KeypadStates_t;

class AccessCtlKeypad
{
  private:
    KeypadStates_t currentKeypadState = DEFAULT_STATE;
  public:
    AccessCtlKeypad(void);
    ~AccessCtlKeypad(void) {}

    void attachKeypadCallback(void (*callback)(char, KeyEdge_t));
    KeypadStates_t getCurrentKeypadState(void);
    void changeKeypadToState(KeypadStates_t keypadState);
};

#endif
 
