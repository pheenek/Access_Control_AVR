/**
 * @file 		AccessCtlOnboardStorage.h
 *
 * @author 		Stephen Kairu (kairu@pheenek.com)
 *
 * @brief	    This file contains the definitions for the on-chip EEPROM interface
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
// Write the EEPROM in block of 24 bytes
// Byte 0 in the block indicates the number of the record
// Bytes 1 - 23 are a null-terminated character string for the name
// Max number of data blocks in ATMega328P is 42

#ifndef ACCESS_CTL_STORAGE_H
#define ACCESS_CTL_STORAGE_H

#include <EEPROM.h>
#include <string.h>

/**
 * A storage class containing the attributes, behaviour and interface to the on-chip EEPROM storage
 */
class AccessCtlOnboardStorage
{
private:
    const int PIN_SIZE = 4;                /*< Length of the security code (PIN)*/
    const uint16_t pinStorageAddress = 16; /*< Address to which the security code is stored on the EEPROM*/
    const char *defaultPIN = "1234";       /*< Default security code (PIN) */
    char devicePIN[5];                     /*< PIN (security code) buffer. Stores the current PIN (security code) in RAM */

    /**
     * @brief	 Attempts to recover the pin (security code) from the EEPROM storage
     *
     * @param pinBuf
     * @return none
     */
    void retrievePIN(char *pinBuf);

public:
    /**
     * @brief	Constructor for storage interface
     *          Initilizes the storage hardware interface
     *
     * @param none
     * @return none
     */
    AccessCtlOnboardStorage(void);

    /**
     * @brief	Destroy the Access Ctl Onboard Storage object
     *
     *
     */
    ~AccessCtlOnboardStorage(void) {}

    /**
     * @brief	 Reads the device PIN (security code) into the buffer provided
     *
     * @param pinBuf
     * @return none
     */
    void getPIN(char *pinBuf);

    /**
     * @brief	 Saves the PIN (security code) into the EEPROM
     *
     * @param pinBuf
     * @return none
     */
    void savePIN(char *pinBuf);
};

#endif
