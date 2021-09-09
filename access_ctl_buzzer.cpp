
#include "access_ctl_buzzer.h"

bool beepBuzzer = false;
bool buzzerState = false;
BeepTimes_t beepCount = ZERO_BEEPS;
unsigned long buzzer_timing_millis = 0;

AccessCtlBuzzer::AccessCtlBuzzer(void)
{
  // initialize buzzer pin (PB4)
  // Set buzzer pin as an output
  DDRB |= (1 << DDB4);  
}

void AccessCtlBuzzer::setBeepTimes(BeepTimes_t beep_times)
{
  BEEP_TIMES = beep_times;
}

void AccessCtlBuzzer::setBeepDelay(BeepDelay_t beep_delay)
{
  BEEP_DELAY = beep_delay;
}
  
void AccessCtlBuzzer::alert(BeepTimes_t beep_times, BeepDelay_t beep_delay)
{
  setBeepTimes(beep_times);
  setBeepDelay(beep_delay);
  initBeepCycle();
}

void AccessCtlBuzzer::initBeepCycle(void)
{
  beepBuzzer = true;
  buzzerState = false;
  beepCount = ZERO_BEEPS;
  buzzer_timing_millis = get_timing_millis();
}

void AccessCtlBuzzer::endBeepCycle(void)
{
  beepBuzzer = false;
}

void AccessCtlBuzzer::buzzerLoop(void)
{
  // Return if no buzzer action required
  if (!beepBuzzer) return;

  // Return if delay time has not elapsed
  if ((get_timing_millis() - buzzer_timing_millis) < BEEP_DELAY) return;
  // Update the buzzer timing variable
  buzzer_timing_millis = get_timing_millis();

  // Check current buzzer state
  if (buzzerState == true)
  {
    // Switch buzzer off
    buzzerState = false;
    PORTB &= ~(1 << PORTB4);

    // Increment beep count
    incrementBeeps();
      
    // Check current beep count against set beep count
    if (beepCount == BEEP_TIMES)
    {
      // Buzzer action complete
      endBeepCycle();
    }

  }
  else
  {
    // Switch the buzzer on
    buzzerState = true;
    PORTB |= (1 << PORTB4);
  }
}

void AccessCtlBuzzer::incrementBeeps()
{
  switch (beepCount)
  {
  case ZERO_BEEPS:
    beepCount = ONE_BEEP;
    break;
  case ONE_BEEP:
    beepCount = TWO_BEEPS;
    break;
  case TWO_BEEPS:
    beepCount = THREE_BEEPS;
    break;
  case THREE_BEEPS:
    beepCount = FOUR_BEEPS;
    break;
  case FOUR_BEEPS:
    beepCount = FIVE_BEEPS;
    break;
  
  default:
    break;
  }
}
