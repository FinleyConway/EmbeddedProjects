#include <Arduino.h>

#include "dot_matrix/text_displayer.h"

LedControl matrix = LedControl(12, 10, 11, 1);

#define MATRIX_WIDTH 8
#define MATRIX_HEIGHT 8

#define UP_BUTTON_PIN 4
#define DOWN_BUTTON_PIN 5
#define LEFT_BUTTON_PIN 6
#define RIGHT_BUTTON_PIN 7

struct SnakeBody
{
    uint8_t x;
    uint8_t y;
    uint8_t prev_x;
    uint8_t prev_y;

    void save_position()
    {
        prev_x = x;
        prev_y = y;
    }

    void draw(LedControl& matrix)
    {
        matrix.setLed(0, x, y, true);
            
        if (x != prev_x || y != prev_y)
        {
            matrix.setLed(0, prev_x, prev_y, false);
        }
    }
};

struct Snake
{
    int8_t direction_x;
    int8_t direction_y;
    uint8_t current_length;
    SnakeBody body[MATRIX_WIDTH * MATRIX_HEIGHT];

    void init()
    {
        direction_x = 0;
        direction_y = -1;
        current_length = 1;
        memset(body, 0, MATRIX_WIDTH * MATRIX_HEIGHT);

        body[0] = {
            MATRIX_WIDTH / 2,
            MATRIX_HEIGHT / 2
        };
    }

    void add_body()
    {
        const SnakeBody& last_body = body[current_length - 1];

        body[current_length] = {
            last_body.prev_x, last_body.prev_y,
            last_body.prev_x, last_body.prev_y,
        };

        current_length++;
    }

    bool has_hit_body()
    {
        const SnakeBody& head = body[0];

        for (uint8_t i = 1; i < current_length; i++)
        {
            const SnakeBody& current_body = body[i];

            if (head.x == current_body.x && head.y == current_body.y)
            {
                return true;
            }
        }

        return false;
    }
};

struct Apple
{   
    uint8_t x;
    uint8_t y;

    void place_apple()
    {
        x = random(0, MATRIX_WIDTH);
        y = random(0, MATRIX_HEIGHT);
    }

    bool try_eat(LedControl& matrix, uint8_t pos_x, uint8_t pos_y)
    {
        if (pos_x == x && pos_y == y)
        {
            matrix.setLed(0, x, y, false);

            place_apple();

            return true;
        }

        return false;
    }

    void draw(LedControl& matrix)
    {
        matrix.setLed(0, x, y, true);
    }
};

Snake snake;
Apple apple;

unsigned long game_time = 500;
unsigned long next_update = 0;

bool is_button_held(uint8_t button)
{
    return digitalRead(button) == LOW;
}

void setup()
{
    matrix.shutdown(0, false);
    matrix.setIntensity(0, 8);
    matrix.clearDisplay(0);

    Serial.begin(9600);

    // set up button controls
    pinMode(UP_BUTTON_PIN, INPUT_PULLUP);
    pinMode(DOWN_BUTTON_PIN, INPUT_PULLUP);
    pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);

    randomSeed(analogRead(A0));

    snake.init();
    apple.place_apple();
}

void loop()
{
    if (is_button_held(UP_BUTTON_PIN))
    {
        snake.direction_x = 0;
        snake.direction_y = -1;
    }
    if (is_button_held(DOWN_BUTTON_PIN))
    {
        snake.direction_x = 0;
        snake.direction_y = 1;
    }
    if (is_button_held(LEFT_BUTTON_PIN))
    {
        snake.direction_y = 0;
        snake.direction_x = 1;
    }
    if (is_button_held(RIGHT_BUTTON_PIN))
    {
        snake.direction_y = 0;
        snake.direction_x = -1;
    }

    // update snake every game time duration
    // thanks unity lol, https://docs.unity3d.com/6000.1/Documentation/ScriptReference/Time-time.html
    if (millis() > next_update) // uses the duration since the board is running to update periodically 
    {
        next_update = millis() + game_time;

        apple.draw(matrix);

        SnakeBody& head = snake.body[0];

        head.save_position();

        head.x += snake.direction_x;
        head.y += snake.direction_y;

        head.x %= MATRIX_WIDTH;
        head.y %= MATRIX_HEIGHT;

        head.draw(matrix);

        if (apple.try_eat(matrix, head.x, head.y))
        {
            snake.add_body();
        }

        if (snake.has_hit_body())
        {
            snake.init();
            apple.place_apple();
            matrix.clearDisplay(0);

            return;
        }

        for (uint8_t i = 1; i < snake.current_length; i++)
        {
            const SnakeBody& previous_body = snake.body[i - 1];
            SnakeBody& current_body = snake.body[i];

            current_body.save_position();

            current_body.x = previous_body.prev_x;
            current_body.y = previous_body.prev_y;

            current_body.draw(matrix);
        }
    }
}