
// Write the EEPROM in block of 24 bytes
// Byte 0 in the block indicates the number of the record
// Bytes 1 - 23 are a null-terminated character string for the name
// Max number of data blocks in ATMega328P is 42

#ifndef ACCESS_CTL_STORAGE_H
#define ACCESS_CTL_STORAGE_H

#include <EEPROM.h>
#include <string.h>

class AccessCtlOnboardStorage
{
  private:
    const int PIN_SIZE = 4;
    const uint16_t pinStorageAddress = 16;
    const char *defaultPIN = "1234";
    char devicePIN[5];
    
    void retrievePIN(char *pinBuf);
    
  public:
    AccessCtlOnboardStorage(void);
    ~AccessCtlOnboardStorage(void) {}

    void getPIN(char *pinBuf);
    void savePIN(char *pinBuf);
};

#endif
