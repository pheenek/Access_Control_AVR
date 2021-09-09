
#include "access_ctl_display.h"
#include "access_ctl_keypad.h"
#include "access_ctl_lock.h"
#include "access_ctl_contact.h"
#include "AccessExitBtn.h"
#include "access_ctl_buzzer.h"
#include "FingerprintSerial.h"
#include "Fingerprint.h"

//#define DEBUG_MAIN
#define DEBUG_KEYPAD
//#define DEBUG_FINGERPRINT
//#define DEBUG_CONTACT
//#define DEBUG_EXIT

AccessCtlDisplay access_display;
AccessCtlKeypad access_keypad;
AccessCtlLock access_lock;
AccessCtlContactSensor contact_sensor;
AccessCtlExitBtn exitTrigger;
AccessCtlBuzzer access_buzzer;

FingerprintSerial fingerprintSerial(8, 9);
Fingerprint fingerprintSensor = Fingerprint(&fingerprintSerial);

volatile bool validateFinger = false;
volatile bool enrollFinger = false;

// Holds the current number of templates saved, 
// helps in allocating new IDs for new templates
uint8_t FINGERPRINT_COUNT = 0;
uint8_t currentFingerprintIndex = 0;
char *currentPIN = "1234";

char pinInputBuffer[5];

unsigned long longPressMillis = millis();
unsigned long doorTimeoutMillis = millis();
unsigned long getFingerprintDebounceMillis = millis();

void setup()
{
  Serial.begin(57600);
  
  // Set baud rate for the fingerprint sensor serial port
  fingerprintSensor.begin(57600);

  // verify that the fingerprint sensor is connected correctly
  while (!fingerprintSensor.verifyPassword())
  {
    #ifdef DEBUG_FINGERPRINT
      Serial.println("Fingerprint sensor not found!");
    #endif
  }
  
  #ifdef DEBUG_FINGERPRINT
    Serial.println("Fingerprint sensor found!");
  #endif
  
  // get the current number of templates saved on the fingerprint sensor
  fingerprintSensor.getTemplateCount();
  FINGERPRINT_COUNT = fingerprintSensor.templateCount;

  #ifdef DEBUG_FINGERPRINT
    Serial.print("Fingerprint templates: ");
    Serial.println(FINGERPRINT_COUNT);
  #endif

  // For fingerprint sensor touch detection
  setupFingerprintTouch();
  fingeprintLEDOn();

  // attach callbacks
//  fingerprintSensor.attachTouchCallback(fingerprintSensorTouchCallback);
  access_keypad.attachKeypadCallback(keypadEventCallback);
//  contact_sensor.attachContactEventCallback(contactSensorCallback);
//  exitTrigger.attachExitCallback(exitTriggerCallback);
  // enable global interrupt flag
  sei();
}

void loop()
{
  #ifdef DEBUG_MAIN
  Serial.println("Running...");
  #endif

  // Display update loop
  access_display.displayLoop();
  // Buzzer update loop
  access_buzzer.buzzerLoop();
  // Fingerprint touch loop
  fingerprintTouchLoop();
  // Fingerprint read loop
  validateFingerprintLoop();
  // Enroll fingerprint loop
  enrollFingerprintLoop();
  // Solenoid lock loop
  lockLoop();
  // Exit btn loop
  exitLoop();
}

void fingeprintLEDOn(void)
{
  fingerprintSensor.LEDcontrol(FINGERPRINT_LED_BREATHING, 100, FINGERPRINT_LED_BLUE);
}

void fingeprintLEDOff(void)
{
  
}

void setupFingerprintTouch(void)
{
  // set touch pin as an input
  DDRB &= ~(1 << DDB2);
}

void fingerprintTouchLoop(void)
{  
  if (bit_is_clear(PINB, PINB2))
  {
    #ifdef DEBUG_FINGERPRINT
      Serial.println("Finger placed");
    #endif
    
    switch (access_display.getCurrentScreen())
    {
      case DEFAULT_SCREEN:
        validateFinger = true;
        break;
      case ADD_FINGERPRINT_SCREEN:
        enrollFinger = true;
//        enrollFingerprint();
        break;

      default:
        break;
    }
  }
  else if (bit_is_set(PINB, PINB2))
  {
    #ifdef DEBUG_FINGERPRINT
      Serial.println("Finger not present");
    #endif
    
    if (access_display.getEnrollFingerStep() == REMOVE_FINGER_PROMPT)
    {
      access_display.setEnrollFingerStep(REPEAT_CAPTURE_PROMPT);
    }
  }
}

void exitLoop(void)
{
  if (exitTrigger.isActivated())
  {
    #ifdef DEBUG_EXIT
      Serial.println("Exit button pressed");
    #endif
    
    unsigned long exitTriggerTiming = millis();
    while ((millis() - exitTriggerTiming) < 500);

    while (exitTrigger.isActivated());
    
    #ifdef DEBUG_EXIT
      Serial.println("Exit activated!");
    #endif
    
    access_buzzer.alert(ONE_BEEP, LONG_BEEP);
    access_lock.openLock();
    doorTimeoutMillis = millis();
  }
}

void lockLoop(void)
{
  if (access_lock.isOpened() && contact_sensor.doorClosed())
  {
    if ((millis() - doorTimeoutMillis) > 10000)
    {
      access_lock.closeLock();
    }
  }
  
}

void validateMenuAccessLoop(void)
{
  if (access_keypad.getCurrentKeypadState() == DEFAULT_STATE)
  {
    // if potential menu access
    // sound buzzer when wait time elapsed
  }
}

void validateFingerprintLoop(void)
{
  if (validateFinger)
  {
    // Wait for the finger to settle on the sensor
    getFingerprintDebounceMillis = millis();
    while ((millis() - getFingerprintDebounceMillis) < 500);
    
    if (getFingerprint())
    {
      // Fingerprint match found
      // sound buzzer, open door
      #ifdef DEBUG_FINGERPRINT
        Serial.println("Showing success screen");
      #endif
      access_display.setCurrentScreen(SUCCESS_SCREEN);
      #ifdef DEBUG_FINGERPRINT
        Serial.println("Success buzzer alert");
      #endif
      access_buzzer.alert(ONE_BEEP, LONG_BEEP);
      #ifdef DEBUG_FINGERPRINT
        Serial.println("Opening lock");
      #endif
      access_lock.openLock();
      doorTimeoutMillis = millis();
    }
    else
    {
      access_display.setCurrentScreen(ERROR_SCREEN);
      access_buzzer.alert(THREE_BEEPS, SHORT_BEEP);
    }
    fingeprintLEDOn();
    validateFinger = false;
  }
  
}

void enrollFingerprintLoop(void)
{
  if (enrollFinger)
  {
    enrollFingerprint();
    fingeprintLEDOn();
    enrollFinger = false;
  }
}

bool getFingerprint(void)
{
  #ifdef DEBUG_FINGERPRINT
    Serial.println("Fingerprint image capture");
  #endif
  
  // log image capture started
  uint8_t p = fingerprintSensor.getImage();
  // log image capture error
  if (p != FINGERPRINT_OK)  return false;
  // log image capture successful

  #ifdef DEBUG_FINGERPRINT
    Serial.println("Fingerprint image capture success");
  #endif

  #ifdef DEBUG_FINGERPRINT
    Serial.println("Fingerprint image conversion");
  #endif
  
  // log image to feature template conversion started
  p = fingerprintSensor.image2Tz();  
  //log image to feature template conversion error
  if (p != FINGERPRINT_OK)  return false;
  // log image to feature template conversion success

  #ifdef DEBUG_FINGERPRINT
    Serial.println("Fingerprint image conversion success");
  #endif

  #ifdef DEBUG_FINGERPRINT
    Serial.println("Fingerprint search");
  #endif

  // log fingerprint search started
//  return fingerprintSensor.fingerFastSearch();
  p = fingerprintSensor.fingerSearch();
  // log fingerprint search error
  if (p != FINGERPRINT_OK) return false;
  if (p == FINGERPRINT_NOTFOUND) return false;
  // log fingerprint search success

  #ifdef DEBUG_FINGERPRINT
    Serial.println("Fingerprint search match found");
  #endif
  
  return true;
}

void keypadEventCallback(char pressed, KeyEdge_t edge)
{
  #ifdef DEBUG_KEYPAD
    Serial.print(pressed);
    Serial.print(" pressed: ");
    Serial.println(edge);
  #endif
  
  switch (access_keypad.getCurrentKeypadState())
  {
    case DEFAULT_STATE:
      // Listen for long-press for key 5
      if (pressed == '5')
      {
        if (edge == FALLING_EDGE)
        {
          // Start long press timer
          longPressMillis = millis();
        }
        else if (edge == RISING_EDGE)
        {
          // End long press timer, 
          if ((millis() - longPressMillis) > 2000)
          {
            // if within long-press threshold, change to PIN screen
            // Change keypad to PIN state
            memset(pinInputBuffer, '\0', sizeof(pinInputBuffer));
            access_display.resetPinChars();
            access_display.openPassScreen();
            access_keypad.changeKeypadToState(PIN_STATE);
          }
        }
      }
      break;
    case PIN_STATE:
      if (edge == RISING_EDGE)
      {
        // Listen for the rising edge for digit keys
        if (pressed == '1' | pressed == '2' | pressed == '3'
             | pressed == '4' | pressed == '5' | pressed == '6'
              | pressed == '7' | pressed == '8' | pressed == '9')
        {
          // concatenate pressed char to buffer
          pinInputBuffer[access_display.getNumCharsInput()] = pressed;
          access_display.addPinCharInput();

          #ifdef DEBUG_KEYPAD
            Serial.print("Num chars: ");
            Serial.print(access_display.getNumCharsInput());
            Serial.print(", PIN: ");
            Serial.println(pinInputBuffer);
          #endif

          // When 4 characters are input, compare against current PIN
          if (access_display.getNumCharsInput() == FOUR_CHARS)
          {
            // Either change to menu or display error screen
            if (strcmp(pinInputBuffer, currentPIN) == 0)
            {
              // correct PIN input
              // access_display.openMainMenu();
              access_display.setCurrentScreen(PIN_SUCCESS_SCREEN);
              access_keypad.changeKeypadToState(NAVIGATION_STATE);
            } else 
            {
              // show the error screen for a while then go back to the PIN screen
              memset(pinInputBuffer, '\0', sizeof(pinInputBuffer));
              access_display.resetPinChars();
              access_display.setCurrentScreen(PIN_ERROR_SCREEN);
            }
          }
        }
        else if (pressed == 'A')
        {
          access_display.setCurrentScreen(DEFAULT_SCREEN);
          access_keypad.changeKeypadToState(DEFAULT_STATE);
        }
        
      }
      break;
    case NAVIGATION_STATE:
      {
        // Listen for the rising edge for nav digits: 2,8,5 (selection)
        if (edge == RISING_EDGE)
        {
          switch (pressed)
          {
            // scroll up
            case '2':
              access_display.scrollUp();
              break;
            // scroll down
            case '8':
              access_display.scrollDown();
              break;
            // select item
            case '5':
            {
              Screen_t prevScreen = access_display.getCurrentScreen();
              int8_t selectedMenuItem = access_display.getSelectedMenuItem();
              
              access_display.selectItem();
              
              switch (access_display.getCurrentScreen())
              {
                case DEFAULT_SCREEN:
                {
                  access_keypad.changeKeypadToState(DEFAULT_STATE);
                  break;
                }
                case ADD_FINGERPRINT_SCREEN:
                {
                  access_keypad.changeKeypadToState(IDLE_STATE);
                  access_display.setEnrollFingerStep(INITIAL_CAPTURE_PROMPT);
                  break;
                }
                case DOOR_SCREEN:
                {
                  if ((prevScreen == DOOR_OPEN_SCREEN) && selectedMenuItem == 0)
                  {
                    access_buzzer.alert(ONE_BEEP, LONG_BEEP);
                    access_lock.openLock();
                    doorTimeoutMillis = millis();
                  }
                  else if ((prevScreen == DOOR_CLOSE_SCREEN) && selectedMenuItem == 0)
                  {
                    access_buzzer.alert(ONE_BEEP, LONG_BEEP);
                    access_lock.closeLock();
                  }
                  break;
                }
              }
              
              break;
            }
            default:
              break;
          }
        }
      }
      break;
    case IDLE_STATE:
      if (pressed == 'A')
      {
        access_display.setCurrentScreen(FINGERPRINT_DB_SCREEN, FINGERPRINT_DB_MENU_MAX);
        access_keypad.changeKeypadToState(NAVIGATION_STATE);
      }
      break;
    default:
      break;
  }
}

void fingerprintSensorTouchCallback(FingerTouchState_t state)
{
  #ifdef DEBUG_FINGERPRINT
    Serial.println("Fingerprint sensor touch callback");
  #endif
  
  if (state == FINGER_PLACED)
  {
    #ifdef DEBUG_FINGERPRINT
      Serial.println("Finger placed");
    #endif
    
    switch (access_display.getCurrentScreen())
    {
      case DEFAULT_SCREEN:
        validateFinger = true;
        break;
      case ADD_FINGERPRINT_SCREEN:
        enrollFinger = true;
//        enrollFingerprint();
        break;

      default:
        break;
    }
  }
  else if (state == FINGER_REMOVED)
  {
    #ifdef DEBUG_FINGERPRINT
      Serial.println("Finger removed");
    #endif
    
    if (access_display.getEnrollFingerStep() == REMOVE_FINGER_PROMPT)
    {
      access_display.setEnrollFingerStep(REPEAT_CAPTURE_PROMPT);
    }
  }
  
}

void enrollFingerprint(void)
{
  // Display "place finger text" (enrolling ID = FINGERPRINT_COUNT + 1)
  // success or error of fingerprint placement
  // if success, remove finger
  // place the same finger a second time
  // success or error of fingerprint placement, and fingerprint match
  // successfully recorded fingerprint
  
  switch (access_display.getEnrollFingerStep())
  {
  case INITIAL_CAPTURE_PROMPT:
    captureFingerprint();
    break;

  case REPEAT_CAPTURE_PROMPT:
    recaptureFingerprint();
    break;
  
  default:
    break;
  }
}

void captureFingerprint(void)
{
  // Wait for the finger to settle on the sensor
  getFingerprintDebounceMillis = millis();
  while ((millis() - getFingerprintDebounceMillis) < 500);
    
  if (fingerprintSensor.getImage() == FINGERPRINT_OK)
  {
    if (fingerprintSensor.image2Tz(1) == FINGERPRINT_OK)
    {
      // Fingerprint capture success
      // Remove finger
      #ifdef DEBUG_FINGERPRINT
        Serial.println("Fingerprint capture success");
      #endif
      access_display.setEnrollFingerStep(CAPTURE_SUCCESS);
    }
    else
    {
      // Fingerprint image conversion error
      #ifdef DEBUG_FINGERPRINT
        Serial.println("Fingerprint conversion error");
      #endif
      access_display.setEnrollFingerStep(CONVERSION_ERROR);
    }
    
  }
  else
  {
    // Fingerprint capture error
    #ifdef DEBUG_FINGERPRINT
      Serial.println("Fingerprint capture error");
    #endif
    access_display.setEnrollFingerStep(CAPTURE_ERROR);
  }
  
}

void recaptureFingerprint(void)
{
  // Wait for the finger to settle on the sensor
  getFingerprintDebounceMillis = millis();
  while ((millis() - getFingerprintDebounceMillis) < 500);
  
  if (fingerprintSensor.getImage() == FINGERPRINT_OK)
  {
    if (fingerprintSensor.image2Tz(2) == FINGERPRINT_OK)
    {
      // Create model
      if (fingerprintSensor.createModel() == FINGERPRINT_OK)
      {
        // save model at index
        if (fingerprintSensor.storeModel(++FINGERPRINT_COUNT) == FINGERPRINT_OK)
        {
          // Save success
          #ifdef DEBUG_FINGERPRINT
            Serial.println("Fingerprint save success");
          #endif
          access_display.setEnrollFingerStep(SAVE_SUCCESS);
        }
        else
        {
          // Save error
          #ifdef DEBUG_FINGERPRINT
            Serial.println("Fingerprint save error");
          #endif
          access_display.setEnrollFingerStep(SAVE_ERROR);
        }
        
      }
      else
      {
        // Fingerprints did not match
        #ifdef DEBUG_FINGERPRINT
          Serial.println("Fingerprint match error");
        #endif
        access_display.setEnrollFingerStep(MATCH_ERROR);
      }
    }
    else
    {
      // Fingerprint image conversion error
      #ifdef DEBUG_FINGERPRINT
        Serial.println("Fingerprint conversion error");
      #endif
      access_display.setEnrollFingerStep(CONVERSION_ERROR);
    }
    
  }
  else
  {
    // Fingerprint capture error
    #ifdef DEBUG_FINGERPRINT
      Serial.println("Fingerprint capture error");
    #endif
    access_display.setEnrollFingerStep(CAPTURE_ERROR);
  }
  
}

void contactSensorCallback(ContactEvent_t event)
{
    if (event == DOOR_CLOSED)
    {
      #ifdef DEBUG_CONTACT
        Serial.println("Door closed!");
      #endif
      access_lock.closeLock();
    }
    else if (event == DOOR_OPEN)
    {
      #ifdef DEBUG_CONTACT
        Serial.println("Door open!");
      #endif
    }
}

void exitTriggerCallback(void)
{
  access_lock.openLock();
  doorTimeoutMillis = millis();
}
