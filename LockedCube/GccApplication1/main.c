/*
 * Cube lock project
 *
 * Created: 10.05.2020 09:12:22
 * Author : Przemyslaw Grobecki & Jakub Legutko
 */ 
#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

int failure_counter = 0;
int last_pos = 0;


int main()
{
    DDRD = 0b00000000;
	PORTD ^= 0b11111100;
	
	DDRB = 0b00111100;
	PORTB ^= 0b00000011;		// Declaring In's and Out's
	
	DDRC = 0b00001110;
	PORTC ^= 0b00011110;						// Pulling up by inside resistors
	
	unsigned char position_one_D = 0b10010100;
	unsigned char position_one_B = 0b00000010;
	
	unsigned char position_two_D = 0b01101000;
	unsigned char position_two_B = 0b00000001;
	
	unsigned char position_three_D = 0b10100100;
	unsigned char position_three_B = 0b00000001;
	
	unsigned char position_four_D = 0b01010000;
	unsigned char position_four_B = 0b00000010;
	
	unsigned char position_five_D = 0b01100100;
	unsigned char position_five_B = 0b00000010;
	
	unsigned char position_six_D = 0b10010000;
	unsigned char position_six_B = 0b00000001;
	
	unsigned char position_D_mask = 0b11111100;
	unsigned char position_B_mask = 0b00000011; //giving each position its own name and associating them with binary mercury switch equivalents
		//just not to mess with unimportant (for this project) pins of arduino nano like RX we use masks to exclude them from overall consideration
								
	
	while (1) 
    {	
		
		while(1){
		
		
		_delay_ms(3000);
	if((bit_is_clear(PINC, 4)) && (last_pos == 0)) { // check if switch is pressed (located at bit 4 of PINC) and if we are in the correct position
		if (((PIND & position_D_mask) == (position_one_D & position_D_mask)) && ((PINB & position_B_mask) == (position_one_B & position_B_mask))) {
			last_pos = 1; // switch position so that if can check if we are in the next step
			shortbuzz();
			
			} else {
				fail();
				break;
			}
			
	} else if ((bit_is_clear(PINC, 4)) && (last_pos == 1)) { 
		if(((PIND & position_D_mask) == (position_two_D & position_D_mask)) && ((PINB & position_B_mask) == (position_two_B & position_B_mask))) {
			last_pos = 2;
			shortbuzz();
			} else {
				fail();
				break;
			}
	
	} else if ((bit_is_clear(PINC, 4)) && (last_pos == 2)) {
		if(((PIND & position_D_mask) == (position_three_D & position_D_mask)) && ((PINB & position_B_mask) == (position_three_B & position_B_mask))) {
			last_pos = 3;
			shortbuzz();
		} else {
			fail();
			break;
		}
	} else if ((bit_is_clear(PINC, 4)) && (last_pos == 3)) {
		if(((PIND & position_D_mask) == (position_four_D & position_D_mask)) && ((PINB & position_B_mask) == (position_four_B & position_B_mask))) {
			last_pos = 4;
			shortbuzz();
		} else {
			fail();
			break;
		}
		
		} else if ((bit_is_clear(PINC, 4)) && (last_pos == 4)) {
			if(((PIND & position_D_mask) == (position_five_D & position_D_mask)) && ((PINB & position_B_mask) == (position_five_B & position_B_mask))) {
				last_pos = 5;
				shortbuzz();
			} else {
				fail();
				break;
			}
		} else if ((bit_is_clear(PINC, 4)) && (last_pos == 5)) {
			if(((PIND & position_D_mask) == (position_six_D & position_D_mask)) && ((PINB & position_B_mask) == (position_six_B & position_B_mask))) {
				last_pos = 6;
				victory(failure_counter);
			} else {
				fail();
				break;
			}
		} else break;
	}
	
	}
			}

void shortbuzz(){
	PORTB ^= 0b00000100;
	_delay_ms(100);
	PORTB &= 0b11111011;
	_delay_ms(100);
}
void green_LED(){
	PORTC &= 0b00001000; // common Cathode used thus need for reversal of usual code
	
	_delay_ms(1000);
	PORTC ^= 0b11110111;
	_delay_ms(1000);
}
void victory(int failure_counter) {
	last_pos = 0;
	green_LED();
	shortbuzz();
	_delay_ms(5000);
	for(int i = 1;i < (failure_counter +1) ; i++) {
		shortbuzz();
		red_LED();
	}
	_delay_ms(1000);
	failure_counter = 0;
}



void fail() {
	last_pos = 0;
	failure_counter++;
	for (int i =0; i < 3 ;i++) {
		shortbuzz();
		red_LED();
	}
}
void red_LED(){ // same as green_LED
	PORTC &= 0b00000100;
	
	_delay_ms(1000);
	PORTC ^= 0b11111011;
	_delay_ms(1000);
}