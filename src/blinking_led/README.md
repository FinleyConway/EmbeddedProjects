# Blinking LED

As much as the Arduino library makes it so much easier to essentially plug and play all the components on to the board, I really want to know how it works under the hood. I'm finding the library quite too high level for my liking and it feels like i'm using python. 

From various research such [such as this video](https://www.youtube.com/watch?v=tBq3sO1Z-7o), I found that Arduino library focuses more on readability rather then performance and for hobbyists and people who want things to just work.
### Component(s) Required In This Example
- A board that uses the `atmega2560` which can be seen from the black chip in the centre of the board.
### How to write and read from the pins?
<img src="assets/Mega 2560 Diagram.png" width="500"></img>

Based on the Arduino diagram of the MEGA 2560, each pin on the board has a microcontroller port assigned to it such as `PB7` for the built in LED.  Consulting this [documentation from microchip](https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/ATmega640-1280-1281-2560-2561-Datasheet-DS40002211A.pdf) you can find the address of the register for the assigned pin which you can use to send information to as seen below.

<img src="assets/Mega 2560 Port B Register.png"></img>

In this case, at `PORTB (0x25)` you can access the B port of the board which provides you a 8 bit bitset where each bit is for each pin for that port. From this example, in order to interact with the built in LED (`PB7 (Port-B 7)`, you must set the 7th bit in `PORTB (0x25)` to active the pin and `DDRB (0x24)` to turn or off the LED:

```c
reg = reg | (1 << n); // set bit at n position
reg = reg &~ (1 << n); // unset bit at n position

// e.g
// set 7th pin to output (all pins are default to input)
PORTB = PORTB | (1 << PORTB7); // 10000000

// turn on LED
DDRB = DDRB | (1 << DDRB7); // 10000000

// turn off LED
DDRB = DDRB &~ (1 << DDRB7); // 00000000
```