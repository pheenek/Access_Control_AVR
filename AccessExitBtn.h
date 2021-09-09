
#ifndef ACCESS_CTL_EXIT_BTN_H
#define ACCESS_CTL_EXIT_BTN_H

#include "access_exit_btn_driver.h"

class AccessCtlExitBtn
{
  private:

  public:
    AccessCtlExitBtn(void);
    ~AccessCtlExitBtn(void) {}

    void attachExitCallback(void (*callback)(void));
    bool isActivated(void);
    bool isNotActivated(void);
};

#endif
 
