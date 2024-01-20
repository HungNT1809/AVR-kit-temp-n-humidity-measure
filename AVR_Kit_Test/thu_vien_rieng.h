#include "lcd.h"

void PORT();
void LED7_OUT(unsigned char num);
void NHAY_LE();
void NHAY_CHAN();
void NHAY_XUOI();
void NHAY_NGUOC();
unsigned char CHECK_BUTTON();
void BUTTON();


void NHAY_XUOI()
{
	unsigned char led_shift = 0B11111111;
	while (1)
	{
		PORTD = led_shift;
		if (led_shift != 0)
		{
			led_shift = led_shift << 1;
		}
		else 
		{
			led_shift = 0B11111111;
		}

		DELAY_MS(500);
	}
}

void NHAY_NGUOC()
{
	unsigned char led_shift = 0B11111111;
	while (1)
	{
		PORTD = led_shift;
		if (led_shift != 0)
		{
			led_shift = led_shift >> 1;
		}
		else 
		{
			led_shift = 0B11111111;
		}

		DELAY_MS(500);
	}
}

void NHAY_LE()
{
	unsigned char led_shift = 0B11111111;
	while (1)
	{
		PORTD = led_shift;
		if (led_shift != 0B10101010)
			{
				led_shift = led_shift << 2;
				led_shift |= 0x02;
			}
		else 
		{
			led_shift = 0B11111111;
		}

		DELAY_MS(500);
	}
}

void NHAY_CHAN()
{
	unsigned char led_shift = 0B11111111;
	while (1)
	{
		PORTD = led_shift;
		if (led_shift != 0B01010101)
			{
				led_shift = led_shift << 2;
				led_shift |= 0x01;
			}
		else 
		{
			led_shift = 0B11111111;
		}

		DELAY_MS(500);
	}
}

unsigned char CHECK_BUTTON()
{
	if ((PINB & 0x1F) != 0x1F)
	{
		if(!(PINB & (1<<PB0)))
			return 1;

		if(!(PINB & (1<<PB1)))
			return 2;

		if(!(PINB & (1<<PB2)))
			return 3;

		if(!(PINB & (1<<PB3)))
			return 4;

		if(!(PINB & (1<<PB4)))
			return 5;
	}
	return 0;
}


void BUTTON()
{
	unsigned char btn = -1;      
	while (1)
	{
		btn = CHECK_BUTTON();
		if (btn == 1)
		{
			NHAY_XUOI();
		}
		else if (btn == 2)
		{
            NHAY_NGUOC();
		}
		else if (btn == 3) 
		{
			NHAY_LE();
		}
		else if (btn == 4)
		{
			NHAY_CHAN();
		}
		else if (btn == 5)
		{
			PORTD = 0xFF;
		}
	}
        
        
}


void PORT()
{
	unsigned char led_shift = 0B11111111;
	unsigned char led_7_count = 9;
	//unsigned char i;

	for (;;)
	{
		PORTD = led_shift;
		if (led_shift != 0B01010101)
			{
				led_shift = led_shift << 2;
				led_shift |= 0x01;
			}
		else 
		{
			led_shift = 255;
		}

		LED7_OUT(led_7_count);
		PORTC ^= 1 << PC3;
		led_7_count = led_7_count - 1;
		if (led_7_count == 255)
		{
			led_7_count = 9;
		}
	
		DELAY_MS(500);
	}	
}

void LED7_OUT(unsigned char num)
{
	unsigned char temp = PORTC;
	temp &= 0B00001000;
	
	switch (num)
	{
		case 0: temp |= 0B10000000; break;
		case 1: temp |= 0B11100011; break;
		case 2: temp |= 0B01000100; break;
		case 3: temp |= 0B01000001; break;
		case 4: temp |= 0B00100011; break;
		case 5: temp |= 0B00010001; break;
		case 6: temp |= 0B00010000; break;
		case 7: temp |= 0B11000011; break;
		case 8: temp |= 0B00000000; break;
		case 9: temp |= 0B00000001; break;
	}
	
	PORTC = temp;
}

