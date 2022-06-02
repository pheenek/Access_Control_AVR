
#include "AccessCtlOnboardStorage.h"

/*
 * Read from EEPROM addresses 16 - 19
 * If the data in the addresses is 255, the device is being used for the first time
 * And the PIN has no PIN stored
 */

void AccessCtlOnboardStorage::retrievePIN(char *pinBuf)
{
  for (int i = 0; i < PIN_SIZE; i++)
  {
    pinBuf[i] = EEPROM.read(pinStorageAddress + i);
  }
}

AccessCtlOnboardStorage::AccessCtlOnboardStorage(void)
{
  uint8_t pinData[5];
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
    strcpy(devicePIN, (char*)pinData);
  }
  
}

void AccessCtlOnboardStorage::savePIN(char *pinBuf)
{
  for (int i = 0; i < PIN_SIZE; i++)
  {
    EEPROM.write((pinStorageAddress + i), pinBuf[i]);
  }
}

void AccessCtlOnboardStorage::getPIN(char *pinBuf)
{
  strcpy(pinBuf, devicePIN);
}
