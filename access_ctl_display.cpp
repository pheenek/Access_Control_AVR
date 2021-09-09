
#include "access_ctl_display.h"
#include "timing_driver.h"

unsigned long info_screen_timing = 0;

void AccessCtlDisplay::displayLoop(void)
{
  u8g->firstPage();
  
  do{
    updateAccessDisplay();
  } while (u8g->nextPage());
}

Screen_t AccessCtlDisplay::getCurrentScreen(void)
{
  return currentScreen;
}

void AccessCtlDisplay::setCurrentScreen(Screen_t screen, MenuMax_t max)
{
  currentScreen = screen;
  if ((screen == ERROR_SCREEN) || (screen == SUCCESS_SCREEN) || (screen == PIN_ERROR_SCREEN))
  {
    info_screen_timing = get_timing_millis();
  }
}

void AccessCtlDisplay::updateAccessDisplay(void)
{
  switch(currentScreen)
  {
    case MENU_SCREEN:
    case FINGERPRINT_DB_SCREEN:
    case DOOR_SCREEN:
    case DOOR_OPEN_SCREEN:
    case DOOR_CLOSE_SCREEN:
      drawSelectionScreen();
      break;
    case DEFAULT_SCREEN:
    case ERROR_SCREEN:
    case PIN_ERROR_SCREEN:
    case PIN_SUCCESS_SCREEN:
    case SUCCESS_SCREEN:
      drawStatusScreen();
      break;
    case PASS_SCREEN:
      drawPassScreen();
      break;
    case ADD_FINGERPRINT_SCREEN:
      drawAddFingerScreen();
      break;
    case RM_FINGERPRINT_SCREEN:
      drawRmFingerScreen();
      break;
    default:
      break;
  }
}

void AccessCtlDisplay::drawAddFingerScreen(void)
{
  char *display_text[2];
  uint8_t i, h;
  u8g_uint_t w, d;

  h = u8g->getFontAscent() - u8g->getFontDescent();
  w = u8g->getWidth();

  switch (addFingerCurrentStep)
  {
  case INITIAL_CAPTURE_PROMPT:
    display_text[0] = "Place finger";
    display_text[1] = "on scanner";
    break;
  case CAPTURE_SUCCESS:
    display_text[0] = "Fingerprint";
    display_text[1] = "Success!";
    if ((get_timing_millis() - info_screen_timing) > 1000)
    {
      setEnrollFingerStep(REMOVE_FINGER_PROMPT);
    }
    break;
  case CAPTURE_ERROR:
    display_text[0] = "Fingerprint";
    display_text[1] = "Error!";
    if ((get_timing_millis() - info_screen_timing) > 1000)
    {
      setEnrollFingerStep(INITIAL_CAPTURE_PROMPT);
    }
    break;
  case CONVERSION_ERROR:
    display_text[0] = "Conversion";
    display_text[1] = "Error!";
    if ((get_timing_millis() - info_screen_timing) > 1000)
    {
      setEnrollFingerStep(INITIAL_CAPTURE_PROMPT);
    }
    break;
  case REMOVE_FINGER_PROMPT:
    display_text[0] = "Remove finger";
    display_text[1] = "";
    break;
  case REPEAT_CAPTURE_PROMPT:
    display_text[0] = "Place finger";
    display_text[1] = "again";
    break;
  case MATCH_SUCCESS:
    display_text[0] = "Fingerprint";
    display_text[1] = "match!";
    break;
  case MATCH_ERROR:
    display_text[0] = "Fingerprint";
    display_text[1] = "match error!";
    if ((get_timing_millis() - info_screen_timing) > 1000)
    {
      setEnrollFingerStep(INITIAL_CAPTURE_PROMPT);
    }
    break;
  case SAVE_SUCCESS:
    display_text[0] = "Fingerprint";
    display_text[1] = "saved!";
    if ((get_timing_millis() - info_screen_timing) > 1000)
    {
      setEnrollFingerStep(INITIAL_CAPTURE_PROMPT);
    }
    break;
  case SAVE_ERROR:
    display_text[0] = "Save error!";
    display_text[1] = "";
    if ((get_timing_millis() - info_screen_timing) > 1000)
    {
      setEnrollFingerStep(INITIAL_CAPTURE_PROMPT);
    }
    break;

  default:
    break;
  }

  d = (w - u8g->getStrWidth(display_text[0])) / 2;
  u8g->drawStr(d, h*1.5, display_text[0]);

  d = (w - u8g->getStrWidth(display_text[1])) / 2;
  u8g->drawStr(d, h*2.5, display_text[1]);
}

void AccessCtlDisplay::drawRmFingerScreen(void)
{

}

void AccessCtlDisplay::drawSelectionScreen(void)
{
  char *title;
  char *options[3] = {};
  uint8_t numOptions = 0;

  switch (currentScreen)
  {
    case MENU_SCREEN:
      title = "MENU";
      options[0] = "Back";
      options[1] = "Fingerprint DB";
      options[2] = "Door Ctl";
      numOptions = 3;
      break;
    case FINGERPRINT_DB_SCREEN:
      title = "FINGERPRINT";
      options[0] = "Back";
      options[1] = "Add Finger";
      options[2] = "Remove Finger";
      numOptions = 3;
      break;
    case DOOR_SCREEN:
      title = "DOOR CTL";
      options[0] = "Back";
      options[1] = "Open Door";
      options[2] = "Close Door";
      numOptions = 3;
      break;
    case DOOR_OPEN_SCREEN:
      title = "Open Door?";
      options[0] = "Yes";
      options[1] = "No";
      numOptions = 2;
      break;
    case DOOR_CLOSE_SCREEN:
      title = "Close Door?";
      options[0] = "Yes";
      options[1] = "No";
      numOptions = 2;
      break;
    default:
      break;
  }

  uint8_t i, h;
  u8g_uint_t w, d;

  h = u8g->getFontAscent() - u8g->getFontDescent();
  w = u8g->getWidth();

  for (i = 0; i < numOptions ; i++) {
    d = (w - u8g->getStrWidth(options[i])) / 2;
    u8g->setDefaultForegroundColor();
    if (i == SELECTED_MENU_ITEM) {
      u8g->drawBox(0, (i + 1)*h, w, h);
      u8g->setDefaultBackgroundColor();
    }
    u8g->drawStr(d, (i + 1)*h, options[i]);
  }
  d = (w - u8g->getStrWidth(title)) / 2;
  u8g->drawStr(d, 0, title);
  
}

int8_t AccessCtlDisplay::getSelectedMenuItem(void)
{
  return SELECTED_MENU_ITEM;
}

void AccessCtlDisplay::scrollDown(void)
{
  SELECTED_MENU_ITEM = ((SELECTED_MENU_ITEM + 1) < currentMenuMax) ? SELECTED_MENU_ITEM + 1 : SELECTED_MENU_ITEM;
}

void AccessCtlDisplay::scrollUp(void)
{
  SELECTED_MENU_ITEM = ((SELECTED_MENU_ITEM - 1) >= 0) ? SELECTED_MENU_ITEM - 1 : SELECTED_MENU_ITEM;
}

void AccessCtlDisplay::openMainMenu(void)
{
  currentScreen = MENU_SCREEN;
  currentMenuMax = MAIN_MENU_MAX;
}

void AccessCtlDisplay::openPassScreen(void)
{
  currentScreen = PASS_SCREEN;
}

void AccessCtlDisplay::drawStatusScreen(void)
{
  char *display_text[2];
  uint8_t i, h;
  u8g_uint_t w, d;

  h = u8g->getFontAscent() - u8g->getFontDescent();
  w = u8g->getWidth();
  
  switch (currentScreen)
  {
    case DEFAULT_SCREEN:
      display_text[0] = "Place finger";
      display_text[1] = "on scanner";
      break;
    case PIN_ERROR_SCREEN:
      if ((get_timing_millis() - info_screen_timing) > 1000)
      {
        setCurrentScreen(PASS_SCREEN);
      }
      display_text[0] = "ACCESS DENIED!";
      display_text[1] = "";
      break;
    case ERROR_SCREEN:
      if ((get_timing_millis() - info_screen_timing) > 1000)
      {
        setCurrentScreen(DEFAULT_SCREEN);
      }
      display_text[0] = "ACCESS DENIED!";
      display_text[1] = "";
      break;
    case PIN_SUCCESS_SCREEN:
      if ((get_timing_millis() - info_screen_timing) > 1000)
      {
        openMainMenu();
      }
      display_text[0] = "ACCESS GRANTED!";
      display_text[1] = "";
      break;
    case SUCCESS_SCREEN:
      if ((get_timing_millis() - info_screen_timing) > 1000)
      {
        setCurrentScreen(DEFAULT_SCREEN);
      }
      display_text[0] = "ACCESS GRANTED!";
      display_text[1] = "";
      break;
    default:
      break;
  }

  d = (w - u8g->getStrWidth(display_text[0])) / 2;
  u8g->drawStr(d, h*1.5, display_text[0]);

  d = (w - u8g->getStrWidth(display_text[1])) / 2;
  u8g->drawStr(d, h*2.5, display_text[1]);
}

void AccessCtlDisplay::addPinCharInput(void)
{
  switch(numPinCharsInput)
  {
    case ZERO_CHARS:
      numPinCharsInput = ONE_CHAR;
      break;
    case ONE_CHAR:
      numPinCharsInput = TWO_CHARS;
      break;
    case TWO_CHARS:
      numPinCharsInput = THREE_CHARS;
      break;
    case THREE_CHARS:
      numPinCharsInput = FOUR_CHARS;
      break;
  }
}

void AccessCtlDisplay::resetPinChars(void)
{
  numPinCharsInput = ZERO_CHARS;
}

PinChars_t AccessCtlDisplay::getNumCharsInput(void)
{
  return numPinCharsInput;
}

void AccessCtlDisplay::drawPassScreen(void)
{
  char *title = "Enter PIN";
  char pin_chars[8] = {0};

  uint8_t i, h;
  u8g_uint_t w, d;

  h = u8g->getFontAscent() - u8g->getFontDescent();
  w = u8g->getWidth();

  d = (w - u8g->getStrWidth(pin_chars)) / 2;
  u8g->drawStr(d, (i + 1)*h, pin_chars);

  switch (numPinCharsInput)
  {
    case ZERO_CHARS:
      strcpy(pin_chars, "|_ _ _ _");
      break;
    case ONE_CHAR:
      strcpy(pin_chars, "* |_ _ _");
      break;
    case TWO_CHARS:
      strcpy(pin_chars, "* * |_ _");
      break;
    case THREE_CHARS:
      strcpy(pin_chars, "* * * |_");
      break;
    case FOUR_CHARS:
      strcpy(pin_chars, "* * * *|");
      break;
    default:
      break;
  }
  d = (w - u8g->getStrWidth(pin_chars)) / 2;
  u8g->drawStr(d, h*2, pin_chars);
  
  d = (w - u8g->getStrWidth(title)) / 2;
  u8g->drawStr(d, 0, title);
}

void AccessCtlDisplay::selectItem(void)
{
  switch (currentScreen)
  {
    case MENU_SCREEN:
      switch(SELECTED_MENU_ITEM)
      {
        case 0:
          currentScreen = DEFAULT_SCREEN;
          currentMenuMax = DEFAULT_MAX;
          break;
        case 1:
          currentScreen = FINGERPRINT_DB_SCREEN;
          currentMenuMax = FINGERPRINT_DB_MENU_MAX;
          break;
        case 2:
          currentScreen = DOOR_SCREEN;
          currentMenuMax = DOOR_MENU_MAX;
        default:
          break;
      }
      SELECTED_MENU_ITEM = 0;
      break;
    case FINGERPRINT_DB_SCREEN:
      switch(SELECTED_MENU_ITEM)
      {
        case 0:
          currentScreen = MENU_SCREEN;
          currentMenuMax = MAIN_MENU_MAX;
          break;
        case 1:
          currentScreen = ADD_FINGERPRINT_SCREEN;
          currentMenuMax = DEFAULT_MAX;
          addFingerCurrentStep = INITIAL_CAPTURE_PROMPT;
          break;
        case 2:
          currentScreen = RM_FINGERPRINT_SCREEN;
          currentMenuMax = DEFAULT_MAX;
        default:
          break;
      }
      SELECTED_MENU_ITEM = 0;
      break;
    case DOOR_SCREEN:
      switch(SELECTED_MENU_ITEM)
      {
        case 0:
          currentScreen = MENU_SCREEN;
          currentMenuMax = MAIN_MENU_MAX;
          break;
        case 1:
          currentScreen = DOOR_OPEN_SCREEN;
          currentMenuMax = DOOR_OPEN_MAX;
          break;
        case 2:
          currentScreen = DOOR_CLOSE_SCREEN;
          currentMenuMax = DOOR_CLOSE_MAX;
        default:
          break;
      }
      SELECTED_MENU_ITEM = 0;
      break;
    case DOOR_OPEN_SCREEN:
      switch(SELECTED_MENU_ITEM)
      {
        case 0:
          currentScreen = DOOR_SCREEN;
          currentMenuMax = DOOR_MENU_MAX;
          break;
        case 1:
          currentScreen = DOOR_SCREEN;
          currentMenuMax = DOOR_MENU_MAX;
          break;
        default:
          break;
      }
      SELECTED_MENU_ITEM = 0;
      break;
    case DOOR_CLOSE_SCREEN:
      switch(SELECTED_MENU_ITEM)
      {
        case 0:
          currentScreen = DOOR_SCREEN;
          currentMenuMax = DOOR_MENU_MAX;
          break;
        case 1:
          currentScreen = DOOR_SCREEN;
          currentMenuMax = DOOR_MENU_MAX;
          break;
        default:
          break;
      }
      SELECTED_MENU_ITEM = 0;
      break;
    default:
      break;
  }
}

AddFingerSteps_t AccessCtlDisplay::getEnrollFingerStep(void)
{
  return addFingerCurrentStep;
}

void AccessCtlDisplay::setEnrollFingerStep(AddFingerSteps_t step)
{
  addFingerCurrentStep = step;
  switch (step)
  {
  case CAPTURE_SUCCESS:
  case CAPTURE_ERROR:
  case CONVERSION_ERROR:
  case MATCH_ERROR:
  case SAVE_SUCCESS:
  case SAVE_ERROR:
    info_screen_timing = get_timing_millis();
    break;
  
  default:
    break;
  }
}
