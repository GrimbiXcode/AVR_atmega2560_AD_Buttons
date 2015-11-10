/********************************************************************
* Project:          AD_Buttons.c
* Description:      Im Folgenden sollen die Tasten des LCDKeypad 
                    „Shieds“, welche über ein Widerstandnetzwerk am 
                    Analog-Eingang AN0 des ATmega2560 angeschlossen 
                    sind einlesen und dekodieren.
* Developer:        David Grimbichler
* Organization:     FHNW Brugg-Windisch
* File:             main.c
* Compiler:         avr-gcc
* Date:             08.11.2015
********************************************************************/


/********************************************************************
* Includes and defines
*
********************************************************************/
#include <avr/io.h> 
#include <util/delay.h> 
#include <stdio.h>

#include "lcd_keypad_m2560.h"

  
#define LEDPORT PORTA
#define LEDDDR DDRA
#define HEARTBEAT_LED 0b10
 
#define BTNMASK ((1<<5)|(1<<4)) // buttons on Port A Bit 4..5
 
/********************************************************************
* Variables & Prototypes
*
********************************************************************/


/********************************************************************
* Init-code
*
********************************************************************/
/*===================================================================
* Inititalisation of Ports
* Input: -
* Return: -
===================================================================*/
void initIO(void)
{
  LEDDDR = HEARTBEAT_LED; //identisch mit: DDRD = 0b00000010
  DDRC = 0xff;    // set LED-Port to output
  PORTA = BTNMASK;  // enable pullups on buttons
}
/*===================================================================
* end of function
===================================================================*/


/*===================================================================
* Inititalisation of ADConverter
* Input: -
* Return: -
===================================================================*/
void init_adc(void)
{
  ADMUX = 0b01000000; // VCC ref , Left adj ,Single ended ADC0
  ADCSRA = 0b10000111; // enable Presc:125kHz
}
/*===================================================================
* end of function
===================================================================*/


/********************************************************************
* Routines
*
********************************************************************/

/*===================================================================
* Reading of ADConverter
* Input: -
* Return: -
===================================================================*/
unsigned int read_adc(void)
{
  unsigned int adValue = 0;
  ADCSRA |= 0b01000000; // start convertion
  while(ADCSRA & 0b01000000)
  {
  }
  adValue = ADC;
  return adValue;
}
/*===================================================================
* end of function
===================================================================*/

/********************************************************************
* Main-code
*
********************************************************************/
int main(void)
{
  unsigned int adValue = 0;

  static FILE lcd_fd = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);
  stdout = &lcd_fd; // set stdout to lcd stream initalized above

  initIO();
  init_adc();
  init_lcd();
  
  while (1)
  { 
    adValue = read_adc();
    printf("RAW = %u\rCalc. = %umV\n",adValue,adValue*2560L/1023L); // print both lines of lcd display
    _delay_ms(100); // waiting for display
  }
}

/********************************************************************
* End of code
********************************************************************/




//  char buttons;

//    PORTC=buttons;
//    buttons = (~PINA & BTNMASK) >> 4;   // read buttons ans shift to LSB






/*===================================================================
* Function-Description
* Input: -
* Return: -
===================================================================*/






















