#include <avr/io.h>

int main(void)
{
	MCUCSR = (1<<JTD);
	MCUCSR = (1<<JTD) ;
	DDRB = 0x00; // B4-7 = address
	// B0-3 = write_data
	DDRD = 0x00 ; // D0 = MEM_READ
	// D1 = MEM_WRITE
	// D2 = MEM_TO_REG
	DDRA = 0xFF ;
	DDRC = 0xFE ;
	PORTA=0x01;
	const int N = 1<<8;
	unsigned char data[N] ;
	for (int i=0; i<N; i++)
		data[i] = 0;
	//data[0] = 0b0000000000000000;
	//data[1] = 0b1100101101001010;
	//data[2] = 0b1111111100000000;
	//data[3] = 0b0000000011111111;
	//data[4] = 0b0000111100001111;
	
	unsigned char in,location,write_data,mem_to_reg,memwrite,read_data,memory_data=0;
	int prevclk = 0, clk;
	while (1)
	{
		in = PINB;
		write_data = (unsigned char)(in & 0x0F) ;
		location = (unsigned char)( (in >> 4 ) & 0x0F );
		
		memwrite = (PIND >> 1) & 1;
		mem_to_reg = (PIND >> 2) & 1;
		clk = (PIND>>7) & 1;
		
		if(memwrite==1)
		{
			if (prevclk == 0 && clk == 1){
				data[location]=write_data;
			}
		}
		
		memory_data=data[location];
		
		if(mem_to_reg==1)
		{
			read_data=memory_data;
		}
		else
		{
			read_data=location;
		}
		PORTA = read_data;
		prevclk = clk;
	}
}