/**
 * @file 		access_ctl_buzzer.h
 *
 * @author 		Stephen Kairu (kairu@pheenek.com)
 *
 * @brief	    This file contains the definitions for a buzzer class, to manage a buzzer
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
#ifndef ACCESS_CTL_BUZZER_H
#define ACCESS_CTL_BUZZER_H

#include <stdint.h>
#include "timing_driver.h"

/**
 * Enumeration defining the possible beep-times (number of beeps) configurations available to the interface
 */
typedef enum : uint8_t
{
    ZERO_BEEPS = 0,
    ONE_BEEP,
    TWO_BEEPS,
    THREE_BEEPS,
    FOUR_BEEPS,
    FIVE_BEEPS
} BeepTimes_t;

/**
 * Enumeration defining the possible beep on-off delay configrations available to the interface
 */
typedef enum : uint16_t
{
    SHORT_BEEP = 50,
    MEDIUM_BEEP = 100,
    LONG_BEEP = 300
} BeepDelay_t;

/**
 * @brief	 A buzzer class defining the attributes, behaviours and interfaces
 *        of the buzzer peripheral
 */
class AccessCtlBuzzer
{
private:
    BeepTimes_t BEEP_TIMES; /*< Variable to hold the current buzzer beep times configuration */
    BeepDelay_t BEEP_DELAY; /*< Variable to hold teh current buzzer on-off delay configuration */

    // Tracking variables
    bool beepBuzzer; /*< Variable to track whether a buzzer sequence is currently active */
    bool buzzerState; /*< Variable to track the current buzzer state (on/off) */
    BeepTimes_t beepCount; /*< Variable to track the keep track of the number of times the buzzer has been turned on */
    unsigned long buzzer_timing_millis; /*< Variable to track the on-off delay on buzzer cycles */

    /**
     * @brief	 Sets the number of times the buzzer is to beep
     *         A different number of beeps is used to indicate a different system status to the user
     *
     * @param beep_times
     * @return none
     */
    void setBeepTimes(BeepTimes_t beep_times);

    /**
     * @brief	 Sets the on-off buzzer delay (on-time, and interval between beeps)
     *         A different on-off delay is used to indicate a different system status to the user
     *
     * @param beep_delay
     * @return none
     */
    void setBeepDelay(BeepDelay_t beep_delay);

    /**
     * @brief	 Increments the beep-counter from the current to the next state.
     *        The number of possible beeps is limited by the BeepTimes_t enumeration
     *
     * @param none
     * @return none
     */
    void incrementBeeps(void);

    /**
     * @brief	 Initiates the beeping cycle for the current buzzer alert configuration
     *
     * @param none
     * @return none
     */
    void initBeepCycle(void);

    /**
     * @brief	 End the beeping cycle for the current buzzer alert configuration
     *
     * @param none
     * @return none
     */
    void endBeepCycle(void);

public:
    /**
     * @brief	Buzzer constructor
     *        Sets up the buzzer hardware interface
     *
     * @param none
     * @return none
     */
    AccessCtlBuzzer(void);
    ~AccessCtlBuzzer(void) {}

    /**
     * @brief	 Interface to initiate a buzzer alert with the defined number of beeps and on-off delay
     *
     * @param beep_times
     * @param beep_delay
     * @return none
     */
    void alert(BeepTimes_t beep_times, BeepDelay_t beep_delay = SHORT_BEEP);

    /**
     * @brief	 Main loop for the buzzer object instance.
     *        Should be called periodically to execute buzzer alert sequences
     *
     * @param none
     * @return none
     */
    void buzzerLoop(void);
};

#endif
