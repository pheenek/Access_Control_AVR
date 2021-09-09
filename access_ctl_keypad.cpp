
#include "access_ctl_keypad.h"

AccessCtlKeypad::AccessCtlKeypad(void)
{
  keypad_setup();
}

void AccessCtlKeypad::attachKeypadCallback(void (*callback)(char, KeyEdge_t))
{
  attach_event_callback(callback);
}

KeypadStates_t AccessCtlKeypad::getCurrentKeypadState(void)
{
  return currentKeypadState;
}

void AccessCtlKeypad::changeKeypadToState(KeypadStates_t keypadState)
{
  currentKeypadState = keypadState;
}
 
