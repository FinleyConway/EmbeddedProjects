#include <avr/io.h>
#include <util/delay.h>

#include <Arduino.h>

void set_pin(volatile uint8_t* port, uint8_t pin)
{
    *port |= (1 << pin);
}

void unset_pin(volatile uint8_t* port, uint8_t pin)
{
    *port &= ~(1 << pin);
}

bool read_pin(volatile uint8_t* port, uint8_t pin)
{
    return *port & (1 << pin);
}

void delay_micro(int ms)
{
  while (0 < ms)
  {  
    _delay_us(1);
    --ms;
  }
}

void delay_milli(int ms)
{
  while (0 < ms)
  {  
    _delay_ms(1);
    --ms;
  }
}

// rotation range: 180
// pulse width range: 500-2400
// pulse cycle: 20
// https://datasheet4u.com/datasheet-pdf/TowerPro/SG90/pdf.php?id=791970
// https://stackoverflow.com/questions/49056510/arduino-servo-without-library 
// https://en.wikipedia.org/wiki/Servo_control
void move_pulse(uint8_t degrees, const uint8_t pulse_cycle = 20)
{
    const uint16_t min_degrees = 0;
    const uint16_t max_degrees = 180;
    const uint16_t low_range = 500;
    const uint16_t high_range = 1700; // tho i find this is the max range for my servo

    uint32_t pulse_width = ((uint32_t)(degrees - min_degrees) * (high_range - low_range)) /
                            (max_degrees - min_degrees) + low_range;

    // send 50 pwm pulses
    for (uint8_t pc = 0; pc <= 50; pc++)
    {
        set_pin(&PORTB, PORTB7);
        delay_micro(pulse_width);

        unset_pin(&PORTB, PORTB7);                                                     
        delay_milli(pulse_cycle);
    }
}        

int main()
{
    set_pin(&DDRB, DDB7); // pin 13
    set_pin(&DDRH, DDB4); // pin 7

    // input pullup
    unset_pin(&DDRB, DDB6);
    set_pin(&PORTB, PB6);

    move_pulse(0);

    while (true)
    {
        bool pin_state = read_pin(&PINB, PB6);

        if (pin_state)
        {
            set_pin(&PORTH, PORTH4);

            move_pulse(0, 0);
        }
        else
        {
            unset_pin(&PORTH, PORTH4);

            move_pulse(90, 0);
        }
    }
}