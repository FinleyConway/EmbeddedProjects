#include "LedControl.h"

LedControl matrix = LedControl(12, 10, 11, 1);

#define WIDTH 8
#define HEIGHT 8

struct moving_char // 10 bytes
{
  uint8_t x;
  uint8_t y;
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
  0, 0,
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
  0, 0,
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

  memcpy(bitset_buffer, char_a.letter_rows, 8);
}

void loop()
{
  delay(250);

  for (int i = 0; i < 8; i++)
  {
    uint8_t value = bitset_buffer[i];

    bitset_buffer[i] = (value >> 1) | (value << (8 - 1));
  }

  for (int i = 0; i < 8; i++)
  {
    matrix.setColumn(0, i, bitset_buffer[i]);
  }
}