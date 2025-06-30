#include "LedControl.h"

LedControl matrix = LedControl(12, 10, 11, 1);

#define CHAR_WIDTH 7
#define CHAR_HEIGHT 5
#define CHAR_SPACING 1

struct moving_char // 8 bytes
{
  uint8_t letter_rows[8];
};


/*
NOTE:
This works but rather un-efficient

An array of bits for each and keep track of the offset will be far more better and easy.
OR
Due to bitset limitations, could have a bitset buffer and push and move these bits keeping track of:
  - character distance (probably just 1 cell)
  - size of character
  - 
*/
moving_char char_a = {
  {
    0b01110000,
    0b10001000,
    0b10001000,
    0b11111000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b00000000
  }
};

moving_char char_b = {
  {
    0b01111000,
    0b10001000,
    0b10001000,
    0b01111000,
    0b10001000,
    0b10001000,
    0b01111000,
    0b00000000
  }
};

uint8_t bitset_buffer[8];
bool should_wrap = true;

void setup()
{
  matrix.shutdown(0, false);
  matrix.setIntensity(0, 8);
  matrix.clearDisplay(0);

  Serial.begin(9600);
}

moving_char moving_word[3] = {
  char_b,
  char_a,
  char_b
}; // bab
int current_char = 0;
int current_width = 0;

void loop()
{
  delay(250);

  const moving_char& letter = moving_word[current_char];

  // write to buffer
  for (int i = 0; i < 8; i++)
  {
    // get the current bit from current row
    uint8_t bitset = letter.letter_rows[i];
    uint8_t bit = bitRead(bitset, current_width);

    // assign that bit the last bit in the buffer bitset
    bitset_buffer[i] = bitWrite(bitset_buffer[i], 7, bit);
  }

  current_width++;

  if (current_width > CHAR_WIDTH)
  {
    current_width = 0;
    current_char++;

    if (current_char > 3)
    {
      current_char = 0;
    }
  }

  // moves characters
  for (int i = 0; i < 8; i++)
  {
    bitset_buffer[i] >>= 1;
  }

  // draws dots
  for (int i = 0; i < 8; i++)
  {
    matrix.setColumn(0, i, bitset_buffer[i]);
  }
}