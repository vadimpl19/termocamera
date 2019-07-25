#include "iom128.h"
#include <inavr.h>
#include <ina90.h>

#include "1wire.h"

//#include "led.h"
//#include "../led.h"
#include "../types.h"
#include "../base.h"
unsigned char flag=0;
//unsigned char flag0;

/****************************************************
Максимальная задержка определяется разрядностью
таймера и частотой его работы, при fc = 12 МГц
5457 мкс
Максимальное время на обработку функции 172 такта
****************************************************/
void delay_(unsigned long t)
{

  __disable_interrupt();
  if (t < 0x10000)
    {
      TIMSK |= (1<<OCIE1A);
      TCCR1B = (1<<CS10);// /1
      TCNT1 = 0;
      
      OCR1A = (unsigned int) (t - 68);
      flag = 1;
      TIFR = (1<<OCF1A);
      __enable_interrupt();
    }
  else if (t < 0x80000)
    {
      TIMSK |= (1<<OCIE1A);
      TCCR1B = (1<<CS11);// /8
      TCNT1 = 0;
      
      OCR1A = (unsigned int) ((t >> 3) - 20);
      flag = 1;
      TIFR = (1<<OCF1A);
      __enable_interrupt();
    }
  else if (t < 0x400000)
    {
      TIMSK |= (1<<OCIE1A);
      TCCR1B = (1<<CS10) | (1<<CS11);// /64
      TCNT1 = 0;
      
      OCR1A = (unsigned int) ((t >> 6) - 2);
      flag = 1;
      TIFR = (1<<OCF1A);
      __enable_interrupt();
    }
  else if (t < 0x1000000)
    {
      TIMSK |= (1<<OCIE1A);
      TCCR1B = (1<<CS12);// /256
      TCNT1 = 0;
      
      OCR1A = (unsigned int) ((t >> 8) - 1);
      flag = 1;
      TIFR = (1<<OCF1A);
      __enable_interrupt();
    }
  else if (t < 0x4000000)
    {
      TIMSK |= (1<<OCIE1A);
      TCCR1B = (1<<CS10) | (1<<CS12);// /1024
      TCNT1 = 0;
      
      OCR1A = (unsigned int) ((t >> 10) - 0);
      flag = 1;
      TIFR = (1<<OCF1A);
      __enable_interrupt();
    }
    __enable_interrupt();  
  while (flag );//ждем завершения отведенного времени

/*

  if (t < 0x10000)
    {
//      TIMSK |= (1<<OCIE1A);
      TCCR1B = (1<<CS10);// /1
      TCNT1 = 0;
    
      OCR1A = (unsigned int) (t - 68);


    }
  else if (t < 0x80000)
    {

      TCCR1B = (1<<CS11);// /8
      TCNT1 = 0;
      
      OCR1A = (unsigned int) ((t >> 3) - 20);
    }
  else if (t < 0x400000)
    {

      TCCR1B = (1<<CS10) | (1<<CS11);// /64
      TCNT1 = 0;
      
      OCR1A = (unsigned int) ((t >> 6) - 2);
    }
  else if (t < 0x1000000)
    {

      TCCR1B = (1<<CS12);// /256
      TCNT1 = 0;
      
      OCR1A = (unsigned int) ((t >> 8) - 1);
    }
  else if (t < 0x4000000)
    {

      TCCR1B = (1<<CS10) | (1<<CS12);// /1024
      TCNT1 = 0;
      
      OCR1A = (unsigned int) ((t >> 10) - 0);
    }
  while (TCNT1<OCR1A);  //ждем завершения отведенного времени  
  line1_up;line2_up;line3_up;line4_up;
*/  
}

void delay__(unsigned long t)
{

  if (t < 0x10000)
    {
        __disable_interrupt();
      TIMSK |= (1<<OCIE1A);
      TCCR1B = (1<<CS10);// /1
      TCNT1 = 0;
      
      OCR1A = (unsigned int) (t - 68);
      flag = 1;
      TIFR = (1<<OCF1A);
      __enable_interrupt();
    }
  else if (t < 0x80000)
    {
        __disable_interrupt();
      TIMSK |= (1<<OCIE1A);
      TCCR1B = (1<<CS11);// /8
      TCNT1 = 0;
      
      OCR1A = (unsigned int) ((t >> 3) - 20);
      flag = 1;
      TIFR = (1<<OCF1A);
      __enable_interrupt();
    }
  else if (t < 0x400000)
    {
      __disable_interrupt();
      TIMSK |= (1<<OCIE1A);
      TCCR1B = (1<<CS10) | (1<<CS11);// /64
      TCNT1 = 0;
      
      OCR1A = (unsigned int) ((t >> 6) - 2);
      flag = 1;
      TIFR = (1<<OCF1A);
      __enable_interrupt();
    }
  else if (t < 0x1000000)
    {
        __disable_interrupt();
      TIMSK |= (1<<OCIE1A);
      TCCR1B = (1<<CS12);// /256
      TCNT1 = 0;
      
      OCR1A = (unsigned int) ((t >> 8) - 1);
      flag = 1;
      TIFR = (1<<OCF1A);
      __enable_interrupt();
    }
  else if (t < 0x4000000)
    {
        __disable_interrupt();
      TIMSK |= (1<<OCIE1A);
      TCCR1B = (1<<CS10) | (1<<CS12);// /1024
      TCNT1 = 0;
      
      OCR1A = (unsigned int) ((t >> 10) - 0);
      flag = 1;
      TIFR = (1<<OCF1A);
      __enable_interrupt();
    }
  //while (flag );//ждем завершения отведенного времени
}
#define chperiod 100
UINT count;
extern unsigned char f_presence;
#pragma vector=TIMER1_COMPA_vect
__interrupt void T1_comp(void)
{

  if (flag==1) 
    {
      line1_up; line2_up; line3_up; line4_up;
      flag = 0;
      return;
    }
/*    
  if (flag==2) 
    {ch1_down =0;ch2_down =0;ch3_down =0;ch4_down =0;
//      pwr1_on;pwr2_on;      pwr3_on;pwr4_on;
      if (!(ramb[0x18] & 0x01)) ch1_up =0;
      if (!(ramb[0x18] & 0x02)) {ch2_up =0;}
      if (!(ramb[0x18] & 0x04)) {ch3_up =0;}
      if (!(ramb[0x18] & 0x08)) ch4_up =0;
    
      flag = 0;

      return;
    }
*/    
  if (flag==2){ 
     ch1_down =0;ch2_down =0;ch3_down =0;ch4_down =0;
      if (!(ramb[0x18] & 0x01)||(ramb[0x1a]&1)) ch1_up =0;
      if (!(ramb[0x18] & 0x02)||(ramb[0x1a]&2)) {ch2_up =0;}
      if (!(ramb[0x18] & 0x04)||(ramb[0x1a]&4)) {ch3_up =0;}
      if (!(ramb[0x18] & 0x08)||(ramb[0x1a]&8)) ch4_up =0;
    
      flag = 3;
//      count=800 000/ chperiod ;
      count=20000; 
//      ramb[0x0d]=count;
      TCNT1=0;
      //      OCR1A=chperiod*15;
      OCR1A=600; //40мкс
      TCCR1B = (1<<CS10);// /1
      f_presence = 0x0f;
      
      EIFR = (1<<INTF7) | (1<<INTF6) | (1<<INTF5) | (1<<INTF4);
      EIMSK |= (1<<INT7) | (1<<INT6) | (1<<INT5) | (1<<INT4);
      
//      addh(0x4400);
      return;
  }    
  if (flag==3){
//    ch1_up=1;ch2_up=1;ch3_up=1; ch4_up=1;   
//      addh(0x4401);
//      addh(count);
      count--;
//      ramb[0x0c]=TCNT1;
//    ramb[0x0e]=count;
      if (count==0){flag=0; return;} 
      TCNT1=TCNT1-600;
/*      
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
     
      if (ch1_in == 0) f_presence &= ~0x01; // short circuit
      if (ch2_in == 0) f_presence &= ~ 0x02;
      if (ch3_in == 0) f_presence &= ~0x04;
      if (ch4_in == 0) f_presence &= ~0x08;
      
   
      if (!(ramb[0x18] & 0x01)) ch1_up =0;
      if (!(ramb[0x18] & 0x02)) {ch2_up =0;}
      if (!(ramb[0x18] & 0x04)) {ch3_up =0;}
      if (!(ramb[0x18] & 0x08)) ch4_up =0;
  */    
      return;
      
   };
//e_isr:    
  line1_up; line2_up; line3_up; line4_up;
  flag=0;
  return;
  
}
