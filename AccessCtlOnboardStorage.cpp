/**
 * @file 		AccessCtlOnboardStorage.cpp
 *
 * @author 		Stephen Kairu (kairu@pheenek.com)
 *
 * @brief	    This file contains the implementations for the on-chip EEPROM interface
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
#include "AccessCtlOnboardStorage.h"

/**
 * @brief	 Attempts to recover the pin (security code) from the EEPROM storage
 * 
 * @param pinBuf 
 * @return none
 */
void AccessCtlOnboardStorage::retrievePIN(char *pinBuf)
{
    /*
     * Read from EEPROM addresses 16 - 19
     * If the data in the addresses is 255, the device is being used for the first time
     * And the PIN has no PIN stored
     */
    for (int i = 0; i < PIN_SIZE; i++)
    {
        pinBuf[i] = EEPROM.read(pinStorageAddress + i);
    }
}

/**
 * @brief	Constructor for storage interface
 *          Initilizes the storage hardware interface
 * 
 * @param none
 * @return none
 */
AccessCtlOnboardStorage::AccessCtlOnboardStorage(void)
{
    char pinData[5];
    memset(pinData, '\0', sizeof(pinData));

    // Read 4 bytes with the pin data and store them in the buffer
    retrievePIN(pinData);

    if (pinData[0] == 255)
    {
        // First time use. Has no PIN written to the EEPROM
        savePIN(defaultPIN);

        memset(devicePIN, '\0', sizeof(devicePIN));
        strcpy(devicePIN, defaultPIN);
    }
    else
    {
        // Has pin stored. Save PIN
        memset(devicePIN, '\0', sizeof(devicePIN));
        strcpy(devicePIN, (char *)pinData);
    }
}

/**
 * @brief	 Saves the PIN (security code) into the EEPROM
 * 
 * @param pinBuf 
 * @return none
 */
void AccessCtlOnboardStorage::savePIN(char *pinBuf)
{
    for (int i = 0; i < PIN_SIZE; i++)
    {
        EEPROM.write((pinStorageAddress + i), pinBuf[i]);
    }
}

/**
 * @brief	 Reads the device PIN (security code) into the buffer provided
 * 
 * @param pinBuf 
 * @return none
 */
void AccessCtlOnboardStorage::getPIN(char *pinBuf)
{
    strcpy(pinBuf, devicePIN);
}
