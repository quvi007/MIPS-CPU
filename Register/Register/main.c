/*
 * PC.c
 *
 * Created: 8/25/2022 7:09:59 PM
 * Author : Sohaib
 */ 

#include <avr/io.h>


int main(void)
{
	// Input PC(8), Output PC(8), CLK(1) Pin, JMP Address(8), Branch Address(4), Zero, BranchFlag JMP(4)
	DDRD = 0x00;
	DDRB = 0x00;
	DDRA = 0xFF;
	DDRC = 0x00;
	
	PORTA = 0;
	
    /* Replace with your application code */
	int reg[8];
	int prev_clock = 0;
    while (1) 
    {
		unsigned char reg1 = (PINB) & 0x0F;
		unsigned char reg2 = (PINB>>4);
		unsigned char reg3 = (PIND) & 0x0F;
		unsigned char write_data = (PINC) & 0x0F;
		
		unsigned char regwrite = (PIND >> 5) & 1;
		unsigned char regdst = (PIND >> 6) & 1;
		unsigned char clk = (PIND >> 7) & 1;
		
		unsigned char read_data1,read_data2;
		
		read_data1=reg[reg1];
		read_data2=reg[reg2];
		
		PORTA = (read_data2<<4)|read_data1;
		if (prev_clock == 0 && clk == 1) {
			if(regwrite){
				if(regdst==0) {
					reg[reg2]=write_data;
				}
				else {
					reg[reg3]=write_data;
				}
			}
		}
		prev_clock = clk;
    }
}

