#include <avr/io.h>
#include <util/delay.h>

// great explanation
// https://youtu.be/j4xw8QomkXs?si=MY4-R_DRftDwGGHI
// who needs arduino.h :P

int main()
{
    // pinMode output at pin 7
    DDRH = DDRH | (1 << DDB4);

    while (1)
    {
        // at digtal pin 7, set it to high
        PORTH = PORTH | (1 << PORTH4);

        // delay for 1 second
        _delay_ms(1000);

        // at digtal pin 7, set it to low
        PORTH = PORTH &~ (1 << PORTH4);

        _delay_ms(1000);
    }
}