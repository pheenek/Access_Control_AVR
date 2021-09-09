
#ifndef TIMING_DRIVER_H
#define TIMING_DRIVER_H

#include "global_inc.h"

#ifdef __cplusplus
extern "C" {
#endif

void timer_init(void);
unsigned long get_timing_millis(void);

#ifdef __cplusplus
}
#endif

#endif
