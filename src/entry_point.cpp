#include <Arduino.h>

#include "dot_matrix/snake_game.h"
#include "dot_matrix/text_displayer.h"

#define UP_BUTTON_PIN 4
#define DOWN_BUTTON_PIN 5
#define LEFT_BUTTON_PIN 6
#define RIGHT_BUTTON_PIN 7

LedControl matrix = LedControl(12, 10, 11, 1);
SnakeGame snake = SnakeGame(&matrix, 
    UP_BUTTON_PIN,
    DOWN_BUTTON_PIN,
    LEFT_BUTTON_PIN,
    RIGHT_BUTTON_PIN
);

void setup()
{
    matrix.shutdown(0, false);
    matrix.setIntensity(0, 8);
    matrix.clearDisplay(0);

    Serial.begin(9600);

    snake.start_game();
}

void loop()
{
    snake.update();
}