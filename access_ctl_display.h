
#ifndef ACCESS_CTL_DISPLAY_H
#define ACCESS_CTL_DISPLAY_H

#include "U8glib.h"

typedef enum SCREENS : int8_t {
  DEFAULT_SCREEN = 0,
  ERROR_SCREEN,
  PIN_ERROR_SCREEN,
  PIN_SUCCESS_SCREEN,
  SUCCESS_SCREEN,
  PASS_SCREEN,
  MENU_SCREEN,
  FINGERPRINT_DB_SCREEN,
  ADD_FINGERPRINT_SCREEN,
  RM_FINGERPRINT_SCREEN,
  DOOR_SCREEN,
  DOOR_OPEN_SCREEN,
  DOOR_CLOSE_SCREEN,
  CHANGE_PIN_SCREEN,
  CHANGE_PIN_ERROR_SCREEN,
  CHANGE_PIN_SUCCESS_SCREEN
} Screen_t;

typedef enum MENU_MAX : int8_t {
  DEFAULT_MAX = 0,
  MAIN_MENU_MAX = 3,
  FINGERPRINT_DB_MENU_MAX = 3,
  DOOR_MENU_MAX = 3,
  DOOR_OPEN_MAX = 2,
  DOOR_CLOSE_MAX = 2
}MenuMax_t;

typedef enum PIN_SCREENS: int8_t {
  PIN_SCREEN,
  CURRENT_PIN_SCREEN,
  CHANGE_PIN_1,
  CHANGE_PIN_2
}PinScreens_t;

typedef enum PIN_CHARS: int8_t {
  ZERO_CHARS = 0,
  ONE_CHAR,
  TWO_CHARS,
  THREE_CHARS,
  FOUR_CHARS
}PinChars_t;

typedef enum ADD_FINGER_STEPS: uint8_t {
  STEPS_NONE,
  INITIAL_CAPTURE_PROMPT,
  CAPTURE_SUCCESS,
  CAPTURE_ERROR,
  CONVERSION_ERROR,
  REMOVE_FINGER_PROMPT,
  REPEAT_CAPTURE_PROMPT,
  MATCH_SUCCESS,
  MATCH_ERROR,
  SAVE_SUCCESS,
  SAVE_ERROR
}AddFingerSteps_t;

class AccessCtlDisplay
{
  private:
    U8GLIB_SH1106_128X64* u8g;
  
    int8_t SELECTED_MENU_ITEM = 0;
    Screen_t currentScreen = DEFAULT_SCREEN;
    MenuMax_t currentMenuMax = DEFAULT_MAX;
    PinChars_t numPinCharsInput = ZERO_CHARS;
    PinScreens_t currentPinScreen = PIN_SCREEN;
    AddFingerSteps_t addFingerCurrentStep = STEPS_NONE;

    void clearScreen(void);
    
    void drawSelectionScreen(void);
    void drawPassScreen(void);
    void drawStatusScreen(void);
    void drawAddFingerScreen(void);
    void drawRmFingerScreen(void);

  public:
    AccessCtlDisplay(void)
    {
      u8g = new U8GLIB_SH1106_128X64(U8G_I2C_OPT_NONE);
      u8g->setFont(u8g_font_gdr12);
      u8g->setFontRefHeightText();
      u8g->setFontPosTop();
      u8g->setRot180();
    }
    
    ~AccessCtlDisplay(void) {}
    
    void displayLoop(void);
    void updateAccessDisplay(void);
    void scrollDown(void);
    void scrollUp(void);
    void selectItem(void);
    int8_t getSelectedMenuItem(void);
    void openMainMenu(void);
    void openPassScreen(void);
    Screen_t getCurrentScreen(void);
    void setCurrentScreen(Screen_t screen, MenuMax_t max = DEFAULT_MAX);
    PinChars_t getNumCharsInput(void);
    PinScreens_t getCurrentPinScreen(void);
    void setCurrentPinScreen(PinScreens_t pinScreen);
    void addPinCharInput(void);
    void resetPinChars(void);

    AddFingerSteps_t getEnrollFingerStep(void);
    void setEnrollFingerStep(AddFingerSteps_t step);
};

#endif
 
