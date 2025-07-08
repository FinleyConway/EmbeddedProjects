#pragma once

#include <Arduino.h>
#include <LedControl.h>

class SnakeGame
{
public:
    SnakeGame(LedControl* matrix, uint8_t up_pin, uint8_t down_pin, uint8_t left_pin, uint8_t right_pin) :
        c_up_pin(up_pin),
        c_down_pin(down_pin),
        c_left_pin(left_pin),
        c_right_pin(right_pin),
        m_matrix(matrix)
    {
    }

    void start_game()
    {
        // setup directional controls
        pinMode(c_up_pin, INPUT_PULLUP);
        pinMode(c_down_pin, INPUT_PULLUP);
        pinMode(c_left_pin, INPUT_PULLUP);
        pinMode(c_right_pin, INPUT_PULLUP);

        // setup random seed using analog noise
        srand(analogRead(A0));

        m_snake.init();
        m_apple.place_apple();
        m_matrix->clearDisplay(0);
    }

    void restart_game()
    {
        m_snake.init();
        m_apple.place_apple();
        m_matrix->clearDisplay(0);
    }

    void update()
    {
        handle_input();

        if (m_matrix == nullptr)
        {
            Serial.println("Led control is nullptr!");
            return;
        }

        // update snake every game time duration
        // thanks unity lol, https://docs.unity3d.com/6000.1/Documentation/ScriptReference/Time-time.html
        if (millis() > m_next_update) // uses the duration since the board is running to update periodically 
        {
            m_next_update = millis() + c_game_time;

            m_apple.draw(*m_matrix);

            update_snake_head();

            if (m_snake.has_hit_body())
            {
                return restart_game();
            }

            update_snake_body();
        }
    }

private:
    bool is_button_held(uint8_t button)
    {
        return digitalRead(button) == LOW;
    }

    void handle_input()
    {
        if (is_button_held(c_up_pin))
        {
            m_snake.direction_x = 0;
            m_snake.direction_y = -1;
        }
        if (is_button_held(c_down_pin))
        {
            m_snake.direction_x = 0;
            m_snake.direction_y = 1;
        }
        if (is_button_held(c_left_pin))
        {
            m_snake.direction_y = 0;
            m_snake.direction_x = 1;
        }
        if (is_button_held(c_right_pin))
        {
            m_snake.direction_y = 0;
            m_snake.direction_x = -1;
        }
    }

    void update_snake_head()
    {
        SnakeBody& head = m_snake.body[0];

        // save the current position
        head.prev_x = head.x;
        head.prev_y = head.y;

        // move the snake's head position
        head.x += m_snake.direction_x;
        head.y += m_snake.direction_y;

        // keep the position within the matrix
        head.x %= c_matrix_width;
        head.y %= c_matrix_height;

        head.draw(*m_matrix);

        // append a new body if it ate an apple
        if (m_apple.try_eat(*m_matrix, head.x, head.y))
        {
            m_snake.add_body();
        }
    }

    void update_snake_body()
    {
        // go through each body moving it, based on where the head moved to
        for (uint8_t i = 1; i < m_snake.current_length; i++)
        {
            const SnakeBody& previous_body = m_snake.body[i - 1];
            SnakeBody& current_body = m_snake.body[i];

            // save the current position
            current_body.prev_x = current_body.x;
            current_body.prev_y = current_body.y;

            // move the body to the previous body position
            current_body.x = previous_body.prev_x;
            current_body.y = previous_body.prev_y;

            current_body.draw(*m_matrix);
        }
    }

private:
    const uint8_t c_up_pin;
    const uint8_t c_down_pin;
    const uint8_t c_left_pin;
    const uint8_t c_right_pin;

    static const uint8_t c_matrix_width = 8;
    static const uint8_t c_matrix_height = 8;

private:
    struct SnakeBody
    {
        uint8_t x;
        uint8_t y;
        uint8_t prev_x;
        uint8_t prev_y;

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
        SnakeBody body[c_matrix_width * c_matrix_height];

        void init()
        {
            direction_x = 0;
            direction_y = -1;
            current_length = 1;
            memset(body, 0, c_matrix_width * c_matrix_height);

            body[0] = {
                c_matrix_width / 2,
                c_matrix_height / 2
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
            x = rand() % c_matrix_width;
            y = rand() % c_matrix_height;
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

private:
    const uint64_t c_game_time = 500;
    uint64_t m_next_update = 0;

    Snake m_snake;
    Apple m_apple;

    LedControl* m_matrix;
};