/**
 * @file 		access_ctl_buzzer.cpp 
 * 
 * @author 		Stephen Kairu (kairu@pheenek.com) 
 * 
 * @brief	    This file contains the implementations for a buzzer class, to manage a buzzer
 *            which provides audio feedback to the user
 * 
 * @version 	0.1 
 * 
 * @date 		2023-09-20
 * 
 * ***************************************************************************
 * @copyright Copyright (c) 2023, Stephen Kairu
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the “Software”), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * ***************************************************************************
 * 
 */
#include "access_ctl_buzzer.h"

/**
 * @brief	Buzzer constructor
 *        Sets up the buzzer hardware interface
 * 
 * @param none
 * @return none
 */
AccessCtlBuzzer::AccessCtlBuzzer(void)
{
  // initialize buzzer pin (PB4)
  // Set buzzer pin as an output
  DDRB |= (1 << DDB4);  
}

/**
 * @brief	 Sets the number of times the buzzer is to beep
 *         A different number of beeps is used to indicate a different system status to the user
 * 
 * @param beep_times 
 * @return none
 */
void AccessCtlBuzzer::setBeepTimes(BeepTimes_t beep_times)
{
  BEEP_TIMES = beep_times;
}

/**
 * @brief	 Sets the on-off buzzer delay (on-time, and interval between beeps)
 *         A different on-off delay is used to indicate a different system status to the user
 * 
 * @param beep_delay 
 * @return none
 */
void AccessCtlBuzzer::setBeepDelay(BeepDelay_t beep_delay)
{
  BEEP_DELAY = beep_delay;
}

/**
 * @brief	 Interface to initiate a buzzer alert with the defined number of beeps and on-off delay
 * 
 * @param beep_times 
 * @param beep_delay 
 * @return none
 */
void AccessCtlBuzzer::alert(BeepTimes_t beep_times, BeepDelay_t beep_delay)
{
  setBeepTimes(beep_times);
  setBeepDelay(beep_delay);
  initBeepCycle();
}

/**
 * @brief	 Initiates the beeping cycle for the current buzzer alert configuration
 * 
 * @param none
 * @return none
 */
void AccessCtlBuzzer::initBeepCycle(void)
{
  beepBuzzer = true;
  buzzerState = false;
  beepCount = ZERO_BEEPS;
  buzzer_timing_millis = get_timing_millis();
}

/**
 * @brief	 End the beeping cycle for the current buzzer alert configuration
 * 
 * @param none
 * @return none
 */
void AccessCtlBuzzer::endBeepCycle(void)
{
  beepBuzzer = false;
}

/**
 * @brief	 Main loop for the buzzer object instance.
 *        Should be called periodically to execute buzzer alert sequences
 * 
 * @param none
 * @return none
 */
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

/**
 * @brief	 Increments the beep-counter from the current to the next state.
 *        The number of possible beeps is limited by the BeepTimes_t enumeration
 * 
 * @param none
 * @return none
 */
void AccessCtlBuzzer::incrementBeeps(void)
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
