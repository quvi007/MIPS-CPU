/*
 * PC.c
 *
 * Created: 8/25/2022 7:09:59 PM
 * Author : Sohaib
 */ 

#include <avr/io.h>


int main(void)
{
	MCUCSR = (1<<JTD);
	MCUCSR = (1<<JTD) ;
	// Input PC(8), Output PC(8), CLK(1) Pin, JMP Address(8), Branch Address(4), Zero, BranchFlag JMP(4)
	DDRD = 0x00;
	DDRB = 0x00;
	DDRA = 0xFF;
	DDRC = 0x00;
	
	PORTA = 0;
	
    /* Replace with your application code */
	int prev_clock = 0;
    while (1) 
    {
		unsigned char pc_in = PINB;
		unsigned char jmp_address = PINC;
		unsigned char branch_address = (PIND & 0x0F);
		unsigned char clk = ((PIND >> 7) & 1);
		unsigned char jmp = (PIND >> 6) & 1;
		unsigned char branch = (PIND >> 5) & 1;
		unsigned char branch_not = (PIND >> 4) & 1;
		
		unsigned char pc_out;
		
		if (jmp) {
			pc_out = jmp_address;
		}
		else if (branch || branch_not) {
			if (branch_address > 7) {
				pc_out = pc_in - (16 - branch_address) + 1;
			} else {
				pc_out = pc_in + branch_address + 1;
			}
		}
		else {
			pc_out = pc_in + 1;
		}
		
		if (prev_clock == 0 && clk == 1) {
			PORTA = pc_out;
		}
		prev_clock = clk;
    }
}

