#include <Arduino.h>

#include "dot_matrix/text_displayer.h"

LedControl matrix = LedControl(12, 10, 11, 1);
TextDisplayer td = TextDisplayer(&matrix, true);

void setup()
{
  matrix.shutdown(0, false);
  matrix.setIntensity(0, 8);
  matrix.clearDisplay(0);

  Serial.begin(9600);

  td.apply_text("mr gus how you doin");
}

void loop()
{
  delay(50);

  td.display_text();
}