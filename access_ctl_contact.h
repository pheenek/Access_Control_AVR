/**
 * @file 		access_ctl_contact.h
 *
 * @author 		Stephen Kairu (kairu@pheenek.com)
 *
 * @brief	    This file contains the definitions for a magnetic contact switch class
 *            to provide feedback as to the state of the door
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
#ifndef ACCESS_CTL_CONTACT_H
#define ACCESS_CTL_CONTACT_H

#include "access_ctl_contact_driver.h"

// TODO: enable contact sensor interrupts

/**
 * @brief   A magnetic contact switch sensor class defining the attributes, behaviours and interfaces
 *        of the peripheral
 */
class AccessCtlContactSensor
{
private:
    bool activated = false;

public:
    /**
     * @brief	Magnetic contact switch sensor constructor
     *        Initializes the low-level driver
     *
     * @param none
     * @return none
     */
    AccessCtlContactSensor(void);
    ~AccessCtlContactSensor(void) {}

    /**
     * @brief	 Queries whether the current status of the door is DOOR_CLOSED
     *
     * @return true
     * @return false
     */
    bool doorClosed(void);

    /**
     * @brief	 Queries whether the current status of the door is DOOR_OPEN
     *
     * @return true
     * @return false
     */
    bool doorOpen(void);

    /**
     * @brief	 Attaches a callback function to be called when an event is detected
     *        by the low-level driver
     *
     * @param callback
     * @return none
     */
    void attachContactEventCallback(void (*callback)(ContactEvent_t));
};

#endif
