# ELC_3336
MicroProcessors course at Baylor University

Implemented a motion-detecting light using an Atmega328p and a COTS LED strip.

## Board Features Used:
1. Timer Counter  
2. Timer Counter Interrupt
3. DIO Interrupt
4. Turning things on/off using the data direction registers (DDR) and ports

## Workaround for max timer val:
I used a 'counter' variable to enable keeping the light on for any desired time period, despite it being driven by an 8-bit timer overflow interrupt.
- Given the board runs on a 16 MHz oscillator, an 8-bit timer overflow occurs every 16 microseconds.
- Using the prescaler value of 1024 gets us to an 8-bit timer overflow every 16.348 milliseconds.
- Using the counter variable to only call the real callback every 306 calls to the timer overflow interrupt means the callback is only called every 5.013 seconds.
