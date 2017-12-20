/*
 * File: main.c
 * Course: ELC 3336
 * Instructor: Dr. Scott Koziol
 * Author: Heath McCabe
 *         Andrew Holliman
 *
 * Assignment: Final Project
 *
 * Description: Our project looks at a physical space
 *     and detects changes using infrared sensors. If
 *     a change is seen in the field of view, our LED
 *     lights turn on. The lights can be turned off 
 *     manually with the button on the AVR or they 
 *     will turn off automatically after a set time.
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned int counter = 0;
void initialize( void );
void button( void );

int main(void)
{
	initialize();
	sei();							// enable global interrupts
	
    while (1) {
		if( !(PINB & (1<<7)) )  {
			button();
		}
    }
}

void initialize( void ) {
	
	// Setup PD2
	TIMSK0 |= (1<<TOIE0);		// Enable timer0 overflow interrupt
	EIMSK |= 1<<INT0;			// Enable INT0 interrupt flag
	DDRD &= ~(1<<DDD2);			// Set PD2 to input
	MCUCR = (1<<ISC01) | (1<<ISC00);	// Trigger INT0 on rising edge
	
	// Setup on Board Button and LED
	DDRB &= ~(1<<7);		// Make Button an input
	DDRB |= (1<<5);			// Make on board LED output	
	DDRC |= (1<<3);		// PC3 - LED - output
	PORTC |= (1<<3);	// PC3 = 1 --> LED off
	
	
	TCCR0A = 0x00;			// Clock in normal mode
}

ISR( INT0_vect )  {
	PORTB |= (1<<5);	// turn light on (on board LED)
	PORTC &= ~(1<<3);	// Turn on external LED
	DDRC |= (1<<3);		// Make PC3 an output again
	
	TCCR0B = (1<<CS02) | (1<<CS00);		// Turn on clock with 1/1024 prescaling
	TCNT0 = 0;							// Set counter to 0
}

ISR( TIMER0_OVF_vect )  {
	
	TCNT0 = 0;
	counter++;
	
	// Call button function after 45 seconds ( >= 2746 )
	// >= 306 for 5 seconds
	if(counter >= 306){
		button();
	}
}

void button(void) {
	PORTB &= ~(1<<5);	// turn off light
	PORTC |= (1<<3);	// PC3 = 1 --> LED off
	DDRC &= ~(1<<3);	// Make PC3 an input
	
	TCCR0B = 0x00;		// Turn off clock
	counter = 0;		// Reset counter
	TCNT0 = 0;			// Reset counter register
}