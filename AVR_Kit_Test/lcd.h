#include "hunget_adc.h"
#include "hunget_lcd.h"


void INIT();
unsigned char check_btn();
void display();
void DELAY_MS(unsigned int mili_count);


void INIT()
{
    // C?u h?nh ch�n I/O
    DDRD |= 0xFF;    // C?u h?nh to�n b? ch�n PORTD l� �?u ra
    PORTD |= 0x00;   // �?t t?t c? c�c ch�n c?a PORTD l�n m?c cao
    
    DDRC |= 0xFF;    // C?u h?nh to�n b? ch�n PORTC l� �?u ra
    PORTC |= 0xFF;   // �?t t?t c? c�c ch�n c?a PORTC l�n m?c cao

    DDRA = 0x00;     // C?u h?nh to�n b? ch�n PORTA l� �?u v�o
    PORTA = 0x00;    // �?t t?t c? c�c ch�n c?a PORTA xu?ng m?c th?p

	DDRB |= 0x00;
    PORTB |= (1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4) | (1 << PB5);

    // C?u h?nh ADC
    ADC_PRES(128);   // �?t gi� tr? chia t? l? t?n s? l?y m?u ADC v? 128
    ADC_AVCC();      // Ch?n ngu?n tham chi?u ADC l� AVCC (�i?n �p ngu?n)
    ADC_IN(1);        // Ch?n ch�n �?u v�o ADC l� ch�n ADC1
}



void display() 
{
	unsigned char max_temp = 30;
	unsigned char min_temp = 10;

    DDRD |= (1 << PD5);         // C?u h?nh ch�n PD5 l� �?u ra
    PORTD &= ~(1 << PD5);       // �?t ch�n PD5 xu?ng m?c th?p

    PORTC |= 0x0F;              // �?t b?n ch�n th?p nh?t c?a PORTC l�n m?c cao
	
    char btn = 0;               // Bi?n �? l�u tr? gi� tr? n�t nh?n
    float temperature = 0;      // Bi?n �? l�u tr? gi� tr? nhi?t �?

    LCD4_INIT(0, 0);            // Kh?i t?o m�n h?nh LCD
    LCD4_CUR_GOTO(1, 3);         // Di chuy?n con tr? t?i h�ng 1, c?t 0
    LCD4_OUT_STR("TEMP:");      // Xu?t chu?i "TEMP: " l�n m�n h?nh LCD
    LCD4_CUR_GOTO(1, 11);         // Di chuy?n con tr? t?i h�ng 1, c?t 8
    LCD4_OUT_DATA(0xDF);         // Xu?t k? t? �? C (0xDF) l�n m�n h?nh LCD
    LCD4_CUR_GOTO(1, 12);         // Di chuy?n con tr? t?i h�ng 1, c?t 9
    LCD4_OUT_STR("C");           // Xu?t chu?i "C" l�n m�n h?nh LCD
    
	LCD4_CUR_GOTO(2, 0);         // Di chuy?n con tr? t?i h�ng 2, c?t 0
    LCD4_OUT_STR("MIN:");  	 	// Xu?t chu?i "MAX TEMP: " l�n m�n h?nh LCD
    LCD4_CUR_GOTO(2, 5);        // Di chuy?n con tr? t?i h�ng 2, c?t 12
    LCD4_OUT_DEC(min_temp, 2);
	LCD4_CUR_GOTO(2, 9);         
    LCD4_OUT_STR("MAX:");  	
    LCD4_CUR_GOTO(2, 14);       
    LCD4_OUT_DEC(max_temp, 2);

    while(1)
    {
        ADC_STA_CONVERT();        // Chuy?n �?i gi� tr? t? c?m bi?n nhi?t �?
        LCD4_CUR_GOTO(1, 9);      // Di chuy?n con tr? t?i h�ng 1, c?t 6
        temperature = (((float)ADC) * 5 * 100) / 1023; // Chuy?n �?i gi� tr? ADC th�nh nhi?t �?
        LCD4_OUT_DEC((int)temperature, 2);             // Xu?t gi� tr? nhi?t �? l�n m�n h?nh LCD

        if (temperature >= max_temp)
        {
            //DDRD |= 1 << PD1;       // C?u h?nh ch�n PD0 l� �?u ra
            PORTD ^= 1 << PD1;      // �?o tr?ng th�i (b?t/t?t) ch�n PD0
        }
		else if (temperature <= min_temp)
        {
            //DDRD |= 1 << PD0;       // C?u h?nh ch�n PD0 l� �?u ra
            PORTD ^= 1 << PD0;     // T?t ch�n PD0 
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


