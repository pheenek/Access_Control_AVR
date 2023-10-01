/**
 * @file 		AccessExitBtn.h
 *
 * @author 		Stephen Kairu (kairu@pheenek.com)
 *
 * @brief	    This file contains the definitions of the exit button interface
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
#ifndef ACCESS_CTL_EXIT_BTN_H
#define ACCESS_CTL_EXIT_BTN_H

#include "access_exit_btn_driver.h"

/**
 * Exit button class defining the attributes, behaviour and interface of the exit button
 */
class AccessCtlExitBtn
{
private:
public:
    /**
     * @brief	Constructor. Initializes the exit button peripheral interface
     *
     * @param none
     * @return none
     */
    AccessCtlExitBtn(void);

    /**
     * @brief	Destroy the Access Ctl Exit Btn object
     *
     *
     */
    ~AccessCtlExitBtn(void) {}

    /**
     * @brief	 Sets the callback function to be called when an exit button event occurs
     *
     * @param callback
     * @return none
     */
    void attachExitCallback(void (*callback)(void));

    /**
     * @brief	 Checks whether the exit button is activated
     *          Returns true if the exit button is activated (pressed)
     *
     * @return true
     * @return false
     */
    bool isActivated(void);

    /**
     * @brief	 Checks whether the exit button is not activated
     *          Returns true if the exit button is deactivated (not pressed)
     *
     * @return true
     * @return false
     */
    bool isNotActivated(void);
};

#endif
