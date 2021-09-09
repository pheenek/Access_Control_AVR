
#include "AccessExitBtn.h"

AccessCtlExitBtn::AccessCtlExitBtn(void)
{
  exit_btn_init();
}

bool AccessCtlExitBtn::isActivated(void)
{
  return (exit_btn_status() == EXIT_ACTIVATED);
}

bool AccessCtlExitBtn::isNotActivated(void)
{
  return (exit_btn_status() == EXIT_DEACTIVATED);
}

void AccessCtlExitBtn::attachExitCallback(void (*callback)(void))
{
  attach_exit_event_callback(callback);
}
 
