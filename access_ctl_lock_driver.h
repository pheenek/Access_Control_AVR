
#ifndef ACCESS_LOCK_DRIVER_H
#define ACCESS_LOCK_DRIVER_H

#include "global_inc.h"

// initialize the lock
void lock_init(void);
// open the lock (set pin high)
void open_lock(void);
// close the lock (set pin low)
void close_lock(void);

#endif
