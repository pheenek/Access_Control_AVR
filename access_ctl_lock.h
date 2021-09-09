
#ifndef ACCESS_CTL_LOCK_H
#define ACCESS_CTL_LOCK_H

typedef enum LOCK_STATE : uint8_t
{
  LOCK_OPENED,
  LOCK_CLOSED
} LockState_t;

class AccessCtlLock
{
  private:
    LockState_t lockState;

  public:
    AccessCtlLock(void);
    ~AccessCtlLock(void) {}

    void openLock(void);
    void closeLock(void);

    bool isOpened(void);
    bool isClosed(void);
};

#endif
 
