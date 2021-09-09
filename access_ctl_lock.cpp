
extern "C"{
  #include "access_ctl_lock_driver.h"
}

#include "access_ctl_lock.h"

AccessCtlLock::AccessCtlLock(void)
{
  lock_init();
}

void AccessCtlLock::openLock(void)
{
  lockState = LOCK_OPENED;
  open_lock();
}

void AccessCtlLock::closeLock(void)
{
  lockState = LOCK_CLOSED;
  close_lock();
}

bool AccessCtlLock::isOpened(void)
{
  return (lockState == LOCK_OPENED);
}

bool AccessCtlLock::isClosed(void)
{
  return (lockState == LOCK_CLOSED);
}
 
