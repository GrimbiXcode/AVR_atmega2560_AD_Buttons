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
}

/*===================================================================
* Inititalisation of Ports
* Input: -
* Return: -
===================================================================*/
void init_adc(void)
{
  ADMUX = HEARTBEAT_LED; //identisch mit: DDRD = 0b00000010
}

/********************************************************************
* Routines
*
********************************************************************/
/*===================================================================
* Function-Description
* Input: -
* Return: -
===================================================================*/


/********************************************************************
* Main-code
*
********************************************************************/
int main(void)
{
  char buttons;

  static FILE lcd_fd = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);
  stdout = &lcd_fd; // set stdout to lcd stream initalized above

  init_lcd();

  DDRC = 0xff;    // set LED-Port to output
  PORTA = BTNMASK;  // enable pullups on buttons
  
  while (1)
  { 
    buttons = (~PINA & BTNMASK) >> 4;   // read buttons ans shift to LSB
    printf("* LCD Test *\rButtons = %d\n",buttons); // print both lines of lcd display
    PORTC=buttons;
  _delay_ms(100);
  }
}

/********************************************************************
* End of code
********************************************************************/



