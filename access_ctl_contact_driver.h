/**
 * @file 		access_ctl_contact_driver.h
 *
 * @author 		Stephen Kairu (kairu@pheenek.com)
 *
 * @brief	    This file contains the definitions of a low-level driver for a
 *            magnetic contact switch sensor
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
#ifndef ACCESS_CTL_CONTACT_DRIVER_H
#define ACCESS_CTL_CONTACT_DRIVER_H

#include "global_inc.h"
#include "timing_driver.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * Enumeration that defines all possible events from this driver
     */
    typedef enum CONTACT_EVENT
    {
        DOOR_CLOSED,
        DOOR_OPEN
    } ContactEvent_t;

    /**
     * @brief	 Initializes the magnetic contact sensor hardware
     *
     * @param none
     * @return none
     */
    void contact_sensor_init(void);

    /**
     * @brief	 Returns the current status of the contact sensor, and hence the door
     *        A low level means that the two contacts are in close proximity.
     *
     * @param none
     * @return ContactEvent_t
     */
    ContactEvent_t door_status(void);

    /**
     * @brief	 Attaches a callback to a high-level function to be executed when events occur
     *
     * @param callback
     * @return none
     */
    void attach_contact_event_callback(void (*callback)(ContactEvent_t));

#ifdef __cplusplus
}
#endif

#endif
