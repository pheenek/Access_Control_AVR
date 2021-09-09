
#ifndef ACCESS_CTL_EXIT_BTN_DRIVER_H
#define ACCESS_CTL_EXIT_BTN_DRIVER_H

#include "global_inc.h"

typedef enum EXIT {
  EXIT_DEACTIVATED,
  EXIT_ACTIVATED
} ExitBtnStatus_t;

#ifdef __cplusplus
extern "C" {
#endif

void exit_btn_init(void);
ExitBtnStatus_t exit_btn_status(void);
void attach_exit_event_callback(void (*callback)(void));

#ifdef __cplusplus
}
#endif

#endif
 
