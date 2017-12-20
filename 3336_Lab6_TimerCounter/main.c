/*
 * 3336_Lab6_TimerCounter.c
 *
 * Created: 10/21/2017 11:20:55 AM
 * Author : Heath McCabe
 * 
 * Description: Toggle the on board LED every 2 seconds
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

// Do the program with interrupts:
unsigned char counter = 0;

int main(void){
	DDRB |= (1<<5);			// Make LED an output
	PORTB &= ~(1<<5);		// Ensure LED is off initially
	
	TCNT0 = 0;				// Set counter to 256-16
	TCCR0A = 0x00;			// Clock in normal mode
	TCCR0B = 0x05;			// No prescaling
	
	TIMSK0 = 0x01;			// Enable timer0 overflow interrupt
	sei();					// Enable global interrupts
	
	while(1){}				
}


ISR (TIMER0_OVF_vect){
	// This ISR gets called every 16.32 ms
	
	TCNT0 = 0;
	counter++;
	// Every 122 calls (2 seconds), the LED should toggle
	if(counter == 122){
		counter = 0;
		PORTB ^= (1<<5);			// Toggle the LED
	}
}
	
	
// Do the program without interrupts	

// ms is the number of ms to delay
/*void delay_ms(int ms){
	for(int num_ms = 0; num_ms < ms; num_ms++){
		TCNT0 = 240;					// Set counter to 256-16
		TCCR0A = 0x00;
		TCCR0B = 0x05;					// CS02:00 = 101 ; clk/1024	
		while( (TIFR0 & 0x01) == 0 );   // Run until the TOV0 flag is set
		TCCR0B = 0;						// Stop the clock running
		TIFR0 = 1<<TOV0;				// Clear TOV0
	}
}

int main(void)
{
	// Initialize LED and Button
	DDRB  |=  (1<<5);	// Make LED an output
	DDRB  &= ~(1<<7);	// Make the Button an input
	
	while(1){
	PORTB |= (1<<5);	// Turn on LED
	delay_ms(1000);		// Delay
	PORTB &= ~(1<<5);	// Turn off LED
	delay_ms(1000);		// Delay	
	}
}*/