
#include "access_ctl_keypad_driver.h"

char key[NUM_ROWS][NUM_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};

volatile Row_t currentRow = ROW_NONE;
volatile Col_t currentCol = COL_NONE;
volatile KeyEdge_t currentKeyEdge = EDGE_NONE;

volatile uint8_t keyState = 0;
volatile uint8_t previousKeyState = 0;

volatile unsigned long lastKeyPressMillis = 0;
volatile unsigned long pinChangeMillis = 0;

void (*keypad_event_callback)(char, KeyEdge_t);

void keypad_event_listener(void);


void keypad_setup(void)
{
  timer_init();
  // enable pin change interrupts
  PCICR |= (1 << PCIE1);
  
  // set pins to inputs
  DDRC &= ~(1 << DDC0) & ~(1 << DDC1) & ~(1 << DDC2) & ~(1 << DDC3);
  // enable internal pull-ups
  PORTC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3);
  // enable interrupts on pins
  PCMSK1 |= (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10) | (1 << PCINT11);
  // pull all columns low
  DDRD |= (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);
  PORTD &= ~(1 << PORTD4) & ~(1 << PORTD5) & ~(1 << PORTD6) & ~(1 << PORTD7);
}

void keypad_event_listener(void)
{
  // If a callback is not defined, return
  if(!keypad_event_callback) return;

  keypad_event_callback(key[currentRow][currentCol], currentKeyEdge);

  if (currentKeyEdge == RISING_EDGE) currentKeyEdge = EDGE_NONE;
}

void attach_event_callback(void (*callback)(char, KeyEdge_t))
{
  keypad_event_callback = callback;
}

ISR(PCINT1_vect)
{
  // include debounce time
  if ((get_timing_millis() - lastKeyPressMillis) >= 50)
  {
    lastKeyPressMillis = get_timing_millis();
        
    previousKeyState = keyState;
    // shift readings of PC0 - PC4 into the upper 4 bits of the 8-bit value
    keyState = (PINC << 4);
    
    if (previousKeyState != keyState)
    {
      if (keyState ^ 0xF0) // falling edge (check for zero in keyState)
      {
        currentKeyEdge = FALLING_EDGE;
        
        if (bit_is_clear(PINC, PC0)) currentRow = ROW_1;
        if (bit_is_clear(PINC, PC1)) currentRow = ROW_2;
        if (bit_is_clear(PINC, PC2)) currentRow = ROW_3;
        if (bit_is_clear(PINC, PC3)) currentRow = ROW_4;
    
        // pull cols high *verified*
        PORTD |= (1 << PORTD4) | (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7);

        // delay for change to take effect
        asm volatile(
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          ::);
    
        // loop through columns 
        for (int col = 0; col < NUM_COLS; col++)
        {
          // set a single column low at a time *verified*
          PORTD &= ~(1 << (col+4));
    
          // delay for external change to take effect
          asm volatile(
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          "nop" "\n\t"
          ::);
    
          
          if (bit_is_clear(PINC, currentRow))
          {
            currentCol = col;
            break;
          }
          else
          {
            PORTD |= (1 << (col+4));
          }
        }
    
        PORTD &= ~(1 << PORTD4) & ~(1 << PORTD5) & ~(1 << PORTD6) & ~(1 << PORTD7);
  
      }
      else if (keyState == 0xF0) // rising edge
      {
        currentKeyEdge = RISING_EDGE;
      }
      keypad_event_listener();
    }
  }

}
 
