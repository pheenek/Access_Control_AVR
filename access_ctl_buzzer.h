
#ifndef ACCESS_CTL_BUZZER_H
#define ACCESS_CTL_BUZZER_H

#include <stdint.h>
#include "timing_driver.h"

typedef enum : uint8_t {
  ZERO_BEEPS = 0,
  ONE_BEEP,
  TWO_BEEPS,
  THREE_BEEPS,
  FOUR_BEEPS,
  FIVE_BEEPS
}BeepTimes_t;

typedef enum : uint16_t {
  SHORT_BEEP = 50,
  MEDIUM_BEEP = 100,
  LONG_BEEP = 300
}BeepDelay_t;

class AccessCtlBuzzer
{
  private:
    BeepTimes_t BEEP_TIMES;
    BeepDelay_t BEEP_DELAY;

    // Tracking variables
    bool beepBuzzer;
    bool buzzerState;
    BeepTimes_t beepCount;
    unsigned long buzzer_timing_millis;

    void setBeepTimes(BeepTimes_t beep_times);
    void setBeepDelay(BeepDelay_t beep_delay);
    void incrementBeeps(void);

    void initBeepCycle(void);
    void endBeepCycle(void);

  public:
    AccessCtlBuzzer(void);
    ~AccessCtlBuzzer(void){}
  
    void alert(BeepTimes_t beep_times, BeepDelay_t beep_delay = SHORT_BEEP);
    void buzzerLoop(void);
};

#endif
