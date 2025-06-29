#include "LedControl.h"

LedControl matrix = LedControl(12, 10, 11, 1);

#define WIDTH 8
#define HEIGHT 8
#define GRID_SIZE WIDTH * HEIGHT

struct moving_char // 66 bytes
{
  uint8_t x;
  uint8_t y;
  uint8_t letter[GRID_SIZE];
};


moving_char char_a = {
  0, 0,
  0, 0,
  {
    0, 1, 1, 1, 0, 0, 0, 0,
    1, 0, 0, 0, 1, 0, 0, 0,
    1, 0, 0, 0, 1, 0, 0, 0,
    1, 1, 1, 1, 1, 0, 0, 0,
    1, 0, 0, 0, 1, 0, 0, 0,
    1, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
  }
};

bool buffer[GRID_SIZE] = { 0 };

void setup()
{
  matrix.shutdown(0, false);
  matrix.setIntensity(0, 8);
  matrix.clearDisplay(0);

  Serial.begin(9600);
}

void loop()
{
  delay(50);

  char_a.x++;

  if (char_a.x > WIDTH)
  {
    char_a.x = 0;
    char_a.y++;
  } 

  if (char_a.y > HEIGHT) 
  {
    char_a.y = 0;
  }

  // update to buffer
  for (uint8_t x = 0; x < WIDTH; x++)
  {
    for (uint8_t y = 0; y < HEIGHT; y++)
    {
      uint8_t offset_x = (x + char_a.x) % WIDTH;
      uint8_t offset_y = (y + char_a.y) % HEIGHT;

      buffer[offset_x + offset_y * WIDTH] = char_a.letter[x + y * WIDTH];
    }
  }

  // render matrix based on buffer
  for (uint8_t x = 0; x < WIDTH; x++)
  {
    for (uint8_t y = 0; y < HEIGHT; y++)
    {
      matrix.setLed(0, x, y, buffer[x + y * WIDTH]);
    }
  }

  memset(buffer, 0, sizeof(buffer));
}