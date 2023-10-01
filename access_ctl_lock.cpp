/**
 * @file 		access_ctl_lock.cpp
 *
 * @author 		Stephen Kairu (kairu@pheenek.com)
 *
 * @brief	    This file contains the implementations for the solenoid lock interface
 *
 * @version 	0.1
 *
 * @date 		2023-09-23
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

#include "access_ctl_lock.h"

/**
 * @brief	Constructor
 *        Initializes the solenoid lock interface
 *
 * @param none
 * @return none
 */
AccessCtlLock::AccessCtlLock(void)
{
    lock_init();
}

/**
 * @brief	 Opens the solenoid lock
 *
 * @param none
 * @return none
 */
void AccessCtlLock::openLock(void)
{
    lockState = LOCK_OPENED;
    open_lock();
}

/**
 * @brief	 Closes the solenoid lock
 *
 * @param none
 * @return none
 */
void AccessCtlLock::closeLock(void)
{
    lockState = LOCK_CLOSED;
    close_lock();
}

/**
 * @brief	 Returns true if the lock is currently opened (unlocked)
 *
 * @return true
 * @return false
 */
bool AccessCtlLock::isOpened(void)
{
    return (lockState == LOCK_OPENED);
}

/**
 * @brief	 Returns true if the lock is currently closed (locked)
 *
 * @return true
 * @return false
 */
bool AccessCtlLock::isClosed(void)
{
    return (lockState == LOCK_CLOSED);
}
