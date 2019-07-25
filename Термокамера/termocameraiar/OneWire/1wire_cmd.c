#include <iom128.h>
#include <inavr.h>
#include <ina90.h>

#include "1wire_cmd.h"
#include "1wire.h"
#include "delay.h"
//#include "../led.h"
#include "../types.h"
#include "../base.h"
#include"../timeservice.h"
//#include"../hist.h"
extern unsigned char flag;//флаг записи 0 по прерыванию от таймера

unsigned char f_presence;

#pragma vector=INT7_vect
__interrupt void Int7(void)
{
  f_presence &= ~(0x01);
  ch1_up=1;
  EIMSK &= ~(1<<INT7);
  EIFR = (1<<INT7);
}

#pragma vector=INT6_vect
__interrupt void Int6(void)
{
  f_presence &= ~(0x02);
  ch2_up=1;
  EIMSK &= ~(1<<INT6);
  EIFR = (1<<INT6);
}

#pragma vector=INT5_vect
__interrupt void Int5(void)
{
  f_presence &= ~(0x04);
    ch3_up=1;
  EIMSK &= ~(1<<INT5);
  EIFR = (1<<INT5);
}

#pragma vector=INT4_vect
__interrupt void Int4(void)
{
  f_presence &= ~(0x08);
    ch4_up=1;
  EIMSK &= ~(1<<INT4);
  EIFR = (1<<INTF4);
}
/****************************************
void  kzhandle(err); 
 функция обработки КЗ на шлейфе
устанавливает бит - линия в порядке только после выдержки таймаута в 3 с
****************************************/
void  kzhandle(char err)
{char i;
//    return;
    err=~err;
    for (i=0;i<4;i++){
//            addh(0x2222);
//            addh(err);
//            addh(i);

          if (err&(1<<i)) {//обнулили статусы датчиков в работе, на шлейфах с КЗ.
//            addh(0x3333);
              ramb[0+i*2]=ramb[1+i*2]=ramb[0x10+i*2]=ramb[0x11+i*2]=0;
              dev_status |=1<<i;
              ramb[0x1a]&=~(1<<i);
          }
          else {  
//           addh(0x4444);
             if (ramb[0x1a]&(1<<i)){// уже было отсутствие КЗ, проверим таймаут
                if (!gettout(1+i)) dev_status &=~(1<<i);  // ==0 - таймаут  истек    
             }else {//КЗ не было, взведем таймаут
                settout(1+i,3000);
                ramb[0x1a]|=1<<i;
             }  
          }    
    }
};    
/****************************************
w1_reset 
bit0  -channel 1
bit1  -channel 2
bit2  -channel 3
bit3  -channel 4
****************************************/
char w1_reset(unsigned char chn)
{
  unsigned char err=0;
//  off2;off3;

//  return 0;
  if (f_presence!=0x0f)kzhandle(f_presence); //была КЗ линии
  if (chn & 0x01) line1_down;  
  if (chn & 0x02) line2_down;
  if (chn & 0x04) line3_down;
  if (chn & 0x08) line4_down;
        //delay_(15*480);
        //W1_DDR &= ~(1<<W1_PIN); считывание происходит на прерывании INT7 по флагу
//  flag0 = 1;
  flag =1;
  delay_(15*480);
/*
  f_presence = 0x0f;
  __disable_interrupt();
  EIMSK |= (1<<INT7) | (1<<INT6) | (1<<INT5) | (1<<INT4);
  EIFR |= (1<<INTF7) | (1<<INTF6) | (1<<INTF5) | (1<<INTF4);
  __enable_interrupt();
*/
  delay_(15*66);
  //err = (ch1_in);			// no presence detect
/*  err = (f_presence << 4); */
  
  delay_(15 * (480 - 66));
  
  if (ch1_in == 0) err |= 0x01; // short circuit
  if (ch2_in == 0) err |= 0x02;
  if (ch3_in == 0) err |= 0x04;
  if (ch4_in == 0) err |= 0x08;
  kzhandle(~err); 
  //ловушка на Козу )))
   f_presence = 0x0f;
  EIFR = (1<<INTF7) | (1<<INTF6) | (1<<INTF5) | (1<<INTF4);
  EIMSK |= (1<<INT7) | (1<<INT6) | (1<<INT5) | (1<<INT4);
  return err;
}
extern unsigned char flag;
//char flagb=0;
#pragma inline=forced
unsigned char w1_bit_io( unsigned char b, char power_need )
{
//  return 0;
//char i;
//  while (flag){};//ожидаем выдержки паузы подпитки после предидущего бита 
  if (f_presence!=0x0f) kzhandle(f_presence);//была КЗ !!! 
   __disable_interrupt();
 
  line1_down; line2_down; line3_down; line4_down;
   TIMSK |= (1<<OCIE1A);
   TCCR1B = (1<<CS10);// /1
   TCNT1 = 3;
   OCR1A=884; //60 мкс
   flag = power_need;
   TIFR = 1<<OCF1A; //примерно 1,5 мкс идет 0   

//  __delay_cycles(15 * 1);
   
//  _NOP();_NOP();_NOP();
  
  if (b & 0x01) line1_up;
  if (b & 0x02) line2_up;
  if (b & 0x04) line3_up;
  if (b & 0x08) line4_up;
    
//  __delay_cycles(15 * (15 - 1));
//  red4=1;
  while (TCNT1<(15*(15-2)));
 
  if (ch1_in == 0) b &= ~(0x01);
  if (ch2_in == 0) b &= ~(0x02);
  if (ch3_in == 0) b &= ~(0x04);
  if (ch4_in == 0) b &= ~(0x08);
  
  __enable_interrupt();
 
   while (flag!=0){//ждем завершения отведенного времени
     if(power_need==2) return b;// это был старт преобразования. выходим
   }
   __disable_interrupt();
//  OCR1A=15*35; //15;
  OCR1A=15*35; //15;
   flag=power_need; 
  TCNT1=0; //задержка на 15 мкс для подпитки датчиков и гарантированного восстановления нормальной единицы в линии после КЗ;
    __enable_interrupt();
  while (flag);
  // далее ставим ловушку на КЗ. 
  /**************************************************************************************
Делаем на открытых прерываниях. манипулирование с масками внешних прерываний в обработчиках других прерываний
!!!!!!!!!!!!!!!!!!!!!!!!!!!!ЗАПРЕЩЕНО!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*****************************************************************************************/
  f_presence = 0x0f;
  EIFR = (1<<INTF7) | (1<<INTF6) | (1<<INTF5) | (1<<INTF4);
  EIMSK |= (1<<INT7) | (1<<INT6) | (1<<INT5) | (1<<INT4);
  return b ;
}


void w1_byte_wr( unsigned char byte[4],char convertf)
{
  unsigned char i, b;
/*  do
  {
    b = (byte[0] & 0x01) | ((byte[1] << 1) & 0x02) \
          | ((byte[2] << 2) & 0x04) | ((byte[3] << 3) & 0x08);
    w1_bit_io( b );
    byte[0] >>= 1;
    byte[1] >>= 1;
    byte[2] >>= 1;
    byte[3] >>= 1;
  }while( --i );
*/
  for(i=0;i<7;i++){
    b = (byte[0] & 0x01) | ((byte[1] << 1) & 0x02) \
          | ((byte[2] << 2) & 0x04) | ((byte[3] << 3) & 0x08);
    w1_bit_io( b,1 );
    byte[0] >>= 1;
    byte[1] >>= 1;
    byte[2] >>= 1;
    byte[3] >>= 1;
  }  
    b = (byte[0] & 0x01) | ((byte[1] << 1) & 0x02) \
          | ((byte[2] << 2) & 0x04) | ((byte[3] << 3) & 0x08);
   if(convertf)    w1_bit_io( b,2 );// после выдачи бита будет включено питание 
   else     w1_bit_io( b,1 );// будет включена только подтяжка       
}
/*****************************************
w1_byte_rd
channel4 : channel3 : channel2 : channel1
*****************************************/
void w1_byte_rd( unsigned char byte[4])
{
  //return w1_byte_wr( 0xFF );
  unsigned char i = 8, j;
  do{
    j = w1_bit_io( 0x0f,1 );
    byte[0] >>= 1;
    byte[1] >>= 1;
    byte[2] >>= 1;
    byte[3] >>= 1;
    if (j & 0x01) byte[0] |= 0x80;
    if (j & 0x02) byte[1] |= 0x80;
    if (j & 0x04) byte[2] |= 0x80;
    if (j & 0x08) byte[3] |= 0x80;
  }while( --i );
}

unsigned char w1_rom_search( unsigned char diff, unsigned char  *id , unsigned char chn)
{
  unsigned char i, j, next_diff;
  unsigned char b, sbyte[4];
  
  //chn = (1<<(chn-1));

  if( w1_reset(chn) & chn)
    return PRESENCE_ERR;			// error, no device found
//    return PRESENCE_ERR;
  sbyte[0] = SEARCH_ROM; sbyte[1] =SEARCH_ROM;sbyte[2] =SEARCH_ROM; sbyte[3] =SEARCH_ROM;
  w1_byte_wr( sbyte,0 );	        // ROM search command
  next_diff = LAST_DEVICE;			// unchanged on last device
  i = 8 * 8;					// 8 bytes
  do{
    j = 8;					// 8 bits
    do{
      b = w1_bit_io( 0x0f,1 ) & chn;		// read bit
      if( w1_bit_io( 0x0f,1 ) & chn){			// read complement bit
	if( b & chn )					// 11
	  return DATA_ERR;			// data error
      }
      else
      {
	if( ! (b & chn) )
	{				// 00 = 2 devices
	  if( diff > i || ((*id & 1) && diff != i) )
	    {
	    b = chn;				// now 1
	    next_diff = i;			// next pass 0
	    }
	}
      }
      w1_bit_io( b,1 );     			// write bit
      *id >>= 1;
      if( b & chn )					// store bit
	*id |= 0x80;
      i--;
    }while( --j );
    id++;					// next byte
  }while( i );
  return next_diff;				// to continue search
}


void w1_command( unsigned char command[4], unsigned char  *id[4] )
{
  unsigned char i, sbyte[4];
  w1_reset(0x0f);
  if( id )
  {
    // to a single device
    sbyte[0] = MATCH_ROM; sbyte[1] =MATCH_ROM;
     sbyte[2] =MATCH_ROM; sbyte[3] =MATCH_ROM;
    w1_byte_wr( sbyte,0 );	
    i = 8;
    do
    {
      w1_byte_wr( *id,0 );
      id++;
    }
    while( --i );
  }
  else
  {
    // to all devices
    sbyte[0] = SKIP_ROM; sbyte[1] =SKIP_ROM;
     sbyte[2] =SKIP_ROM; sbyte[3] =SKIP_ROM;
    w1_byte_wr( sbyte,0 );
  }
  if (command[0]==CONVERT_T) w1_byte_wr( command,1 );
  else w1_byte_wr( command,0 );
}
