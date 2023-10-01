/**
 * @file 		access_ctl_contact.cpp
 *
 * @author 		Stephen Kairu (kairu@pheenek.com)
 *
 * @brief	    This file contains the implementations for a magnetic contact switch class
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
#include "access_ctl_contact.h"

/**
 * @brief	Magnetic contact switch sensor constructor
 *        Initializes the low-level driver
 *
 * @param none
 * @return none
 */
AccessCtlContactSensor::AccessCtlContactSensor(void)
{
    contact_sensor_init();
}

/**
 * @brief	 Queries whether the current status of the door is DOOR_CLOSED
 *
 * @return true
 * @return false
 */
bool AccessCtlContactSensor::doorClosed(void)
{
    return (door_status() == DOOR_CLOSED);
}

/**
 * @brief	 Queries whether the current status of the door is DOOR_OPEN
 *
 * @return true
 * @return false
 */
bool AccessCtlContactSensor::doorOpen(void)
{
    return (door_status() == DOOR_OPEN);
}

/**
 * @brief	 Attaches a callback function to be called when an event is detected
 *        by the low-level driver
 *
 * @param callback
 * @return none
 */
void AccessCtlContactSensor::attachContactEventCallback(void (*callback)(ContactEvent_t))
{
    attach_contact_event_callback(callback);
}
