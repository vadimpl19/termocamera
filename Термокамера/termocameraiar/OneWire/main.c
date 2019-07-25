#include <iom128.h>
#include <inavr.h>

//#include "LED.h"
#include "1wire.h"
#include "temp.h"
#include "delay.h"
#include "OW.h"

void Int_init(void)/***/
{
  EICRB |= (1<<ISC41) | (1<<ISC51) | (1<<ISC61) | (1<<ISC71);
  //EIMSK |= (1<<INT4) | (1<<INT5) | (1<<INT6) | (1<<INT7);
  EIFR |=  (1<<INTF4) | (1<<INTF5) | (1<<INTF6) | (1<<INTF7);
}

void LED_init(void)
{
  DDRC = 0xff;
  DDRG |= 0x03;
}
/*
void LED_test(void)
{
  gr = gr1 = gr2 = gr3 = gr4 = 1;
  __delay_cycles(3000000);
  gr = gr1 = gr2 = gr3 = gr4 = 0;
  red = red1 = red2 = red3 = red4 = 1;
  __delay_cycles(3000000);
  red = red1 = red2 = red3 = red4 = 0;
}
*/
void w1_init_line(void)
{
  DDRF |= 0x03;
  DDRG |= 0x04;
  DDRA |= 0xe6;
}

void w1_test(void)
{
  unsigned int ii;
  for (ii = 0; ii <60000; ii++)
  {
  line1_up; line2_up; line3_up; line4_up;
  __delay_cycles(30000000);
  line1_down; line2_down; line3_down; line4_down;
  __delay_cycles(30000000);
  pwr1_on; pwr2_on; pwr3_on; pwr4_on;
  __delay_cycles(30000000);
  pwr1_off; pwr2_off; pwr3_off; pwr4_off;
  __delay_cycles(30000000);
  }
}
extern unsigned char flag;
extern unsigned char f_presence;
void Init(void)
{
  line1_up; line2_up; line3_up; line4_up;
  Int_init();
  LED_init();
  //LED_test();
  w1_init_line();
  flag=0;
  f_presence=0x0f;
  //w1_test();//тест управления шлейфами
}
/*
void main(void)
{
  Init();
  while (1)
    {
      GetT();
    }
}
*/
