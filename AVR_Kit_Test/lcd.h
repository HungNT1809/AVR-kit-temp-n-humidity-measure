#include "hunget_adc.h"
#include "hunget_lcd.h"


void INIT();
unsigned char check_btn();
void display();
void DELAY_MS(unsigned int mili_count);


void INIT()
{
    // C?u h?nh chân I/O
    DDRD |= 0xFF;    // C?u h?nh toàn b? chân PORTD là ð?u ra
    PORTD |= 0x00;   // Ð?t t?t c? các chân c?a PORTD lên m?c cao
    
    DDRC |= 0xFF;    // C?u h?nh toàn b? chân PORTC là ð?u ra
    PORTC |= 0xFF;   // Ð?t t?t c? các chân c?a PORTC lên m?c cao

    DDRA = 0x00;     // C?u h?nh toàn b? chân PORTA là ð?u vào
    PORTA = 0x00;    // Ð?t t?t c? các chân c?a PORTA xu?ng m?c th?p

	DDRB |= 0x00;
    PORTB |= (1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4) | (1 << PB5);

    // C?u h?nh ADC
    ADC_PRES(128);   // Ð?t giá tr? chia t? l? t?n s? l?y m?u ADC v? 128
    ADC_AVCC();      // Ch?n ngu?n tham chi?u ADC là AVCC (ði?n áp ngu?n)
    ADC_IN(1);        // Ch?n chân ð?u vào ADC là chân ADC1
}



void display() 
{
	unsigned char max_temp = 30;
	unsigned char min_temp = 10;

    DDRD |= (1 << PD5);         // C?u h?nh chân PD5 là ð?u ra
    PORTD &= ~(1 << PD5);       // Ð?t chân PD5 xu?ng m?c th?p

    PORTC |= 0x0F;              // Ð?t b?n chân th?p nh?t c?a PORTC lên m?c cao
	
    char btn = 0;               // Bi?n ð? lýu tr? giá tr? nút nh?n
    float temperature = 0;      // Bi?n ð? lýu tr? giá tr? nhi?t ð?

    LCD4_INIT(0, 0);            // Kh?i t?o màn h?nh LCD
    LCD4_CUR_GOTO(1, 3);         // Di chuy?n con tr? t?i hàng 1, c?t 0
    LCD4_OUT_STR("TEMP:");      // Xu?t chu?i "TEMP: " lên màn h?nh LCD
    LCD4_CUR_GOTO(1, 11);         // Di chuy?n con tr? t?i hàng 1, c?t 8
    LCD4_OUT_DATA(0xDF);         // Xu?t k? t? ð? C (0xDF) lên màn h?nh LCD
    LCD4_CUR_GOTO(1, 12);         // Di chuy?n con tr? t?i hàng 1, c?t 9
    LCD4_OUT_STR("C");           // Xu?t chu?i "C" lên màn h?nh LCD
    
	LCD4_CUR_GOTO(2, 0);         // Di chuy?n con tr? t?i hàng 2, c?t 0
    LCD4_OUT_STR("MIN:");  	 	// Xu?t chu?i "MAX TEMP: " lên màn h?nh LCD
    LCD4_CUR_GOTO(2, 5);        // Di chuy?n con tr? t?i hàng 2, c?t 12
    LCD4_OUT_DEC(min_temp, 2);
	LCD4_CUR_GOTO(2, 9);         
    LCD4_OUT_STR("MAX:");  	
    LCD4_CUR_GOTO(2, 14);       
    LCD4_OUT_DEC(max_temp, 2);

    while(1)
    {
        ADC_STA_CONVERT();        // Chuy?n ð?i giá tr? t? c?m bi?n nhi?t ð?
        LCD4_CUR_GOTO(1, 9);      // Di chuy?n con tr? t?i hàng 1, c?t 6
        temperature = (((float)ADC) * 5 * 100) / 1023; // Chuy?n ð?i giá tr? ADC thành nhi?t ð?
        LCD4_OUT_DEC((int)temperature, 2);             // Xu?t giá tr? nhi?t ð? lên màn h?nh LCD

        if (temperature >= max_temp)
        {
            //DDRD |= 1 << PD1;       // C?u h?nh chân PD0 là ð?u ra
            PORTD ^= 1 << PD1;      // Ð?o tr?ng thái (b?t/t?t) chân PD0
        }
		else if (temperature <= min_temp)
        {
            //DDRD |= 1 << PD0;       // C?u h?nh chân PD0 là ð?u ra
            PORTD ^= 1 << PD0;     // T?t chân PD0 
        }
		else 
		{
			PORTD = 0x00;
		}


		DELAY_MS(100);
    }
}


void DELAY_MS(unsigned int mili_count)
{
	unsigned int i, j;
	mili_count = mili_count * FRE;
	for(i = 0;i< mili_count; i++)
		for(j = 0; j < 53; j++);
}


