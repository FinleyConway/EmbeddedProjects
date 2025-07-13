#include <avr/io.h>
#include <util/delay.h>

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

// https://github.com/adgzlanl/atmega2560-Reading-ADC-example/blob/master/Serial_ADC.c
void init_adc()
{
    // Select Vref=AVcc
    ADMUX |= (1<<REFS0);
    //set prescaller to 128 and enable ADC 
    ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);    
}

uint16_t read_adc(uint8_t ADCchannel)
{
    //select ADC channel with safety mask
    ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
    //single conversion mode
    ADCSRA |= (1<<ADSC);
    // wait until ADC conversion is complete
    while( ADCSRA & (1<<ADSC) );

    return ADC;
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

    // send 51 pwm pulses
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

    init_adc();

    move_pulse(0);

    while (true)
    {
        uint16_t value = read_adc(0);

        if (value <= 695)
        {
            set_pin(&PORTH, PORTH4);

            move_pulse(70, 0);
        }
        else
        {
            unset_pin(&PORTH, PORTH4);

            move_pulse(90, 0);
        }
    }
}