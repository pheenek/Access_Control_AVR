
#ifndef ACCESS_CTL_KEYPAD_DRIVER_H
#define ACCESS_CTL_KEYPAD_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "global_inc.h"
#include "timing_driver.h"

#define NUM_ROWS   4
#define NUM_COLS   4
 
typedef enum ROWS {
  ROW_1 = 0,
  ROW_2,
  ROW_3,
  ROW_4,
  ROW_NONE,
}Row_t;

typedef enum COLS {
  COL_1 = 0,
  COL_2,
  COL_3,
  COL_4,
  COL_NONE,
}Col_t;

typedef enum KEY_PRESS {
  SHORT_PRESS,
  LONG_PRESS
}KeyPress_t;

typedef enum KEY_EDGE {
  FALLING_EDGE,
  RISING_EDGE,
  EDGE_NONE
}KeyEdge_t;

void keypad_setup(void);
void attach_event_callback(void (*callback)(char, KeyEdge_t));

#ifdef __cplusplus
}
#endif

#endif
