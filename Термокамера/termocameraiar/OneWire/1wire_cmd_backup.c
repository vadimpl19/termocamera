#include <iom128.h>
#include <inavr.h>

#include "1wire_cmd.h"
#include "1wire.h"
#include "delay.h"
//#include "LED.h"

extern unsigned char flag0;//флаг записи 0 по прерыванию от таймера

unsigned char f_presence;

#pragma vector=INT7_vect
__interrupt void Int7(void)
{
  f_presence &= ~(0x01);
  EIMSK &= ~(1<<INT7);
  EIFR |= (1<<INT7);
}

#pragma vector=INT6_vect
__interrupt void Int6(void)
{
  f_presence &= ~(0x02);
  EIMSK &= ~(1<<INT6);
  EIFR |= (1<<INT6);
}

#pragma vector=INT5_vect
__interrupt void Int5(void)
{
  f_presence &= ~(0x04);
  EIMSK &= ~(1<<INT5);
  EIFR |= (1<<INT5);
}

#pragma vector=INT4_vect
__interrupt void Int4(void)
{
  f_presence &= ~(0x08);
  EIMSK &= ~(1<<INT4);
  EIFR |= (1<<INTF4);
}

/****************************************
w1_reset 
bit0  -channel 1
bit1  -channel 2
bit2  -channel 3
bit3  -channel 4
****************************************/
unsigned char w1_reset(unsigned char chn)
{
  unsigned char err;
  if (chn & 0x01) line1_down;  
  if (chn & 0x02) line2_down;
  if (chn & 0x04) line3_down;
  if (chn & 0x08) line4_down;
        //delay_(15*480);
        //W1_DDR &= ~(1<<W1_PIN); считывание происходит на прерывании INT7 по флагу
  flag0 = 1;
  delay_(15*480);

  f_presence = 0x0f;
  __disable_interrupt();
  EIMSK |= (1<<INT7) | (1<<INT6) | (1<<INT5) | (1<<INT4);
  EIFR |= (1<<INTF7) | (1<<INTF6) | (1<<INTF5) | (1<<INTF4);
  __enable_interrupt();

  delay_(15*66);
  //err = (ch1_in);			// no presence detect
  err = f_presence;
  
  delay_(15 * (480 - 66));
  if (ch1_in == 0) err |= 0x01; // short circuit
  if (ch2_in == 0) err |= 0x02;
  if (ch3_in == 0) err |= 0x04;
  if (ch3_in == 0) err |= 0x08;
    
  return err;
}

#pragma inline=forced
unsigned char w1_bit_io( unsigned char b )
{
  __disable_interrupt();
  line1_down; line2_down; line3_down; line4_down;
  __delay_cycles(15 * 1);
  
  if (b & 0x01) line1_up;
  if (b & 0x02) line2_up;
  if (b & 0x04) line3_up;
  if (b & 0x08) line4_up;
    
  __delay_cycles(15 * (15 - 1));
  
  if (ch1_in == 0) b &= ~(0x01);
  if (ch2_in == 0) b &= ~(0x02);
  if (ch3_in == 0) b &= ~(0x04);
  if (ch4_in == 0) b &= ~(0x08);
  
  __enable_interrupt();//????????????
  flag0 = 1;
  delay_(15 * (60 - 15));

  return b ;
}


void w1_byte_wr( unsigned char byte[4], unsigned char mask )
{
  unsigned char i = 8, b;
  do
  {
    b = (byte[0] & 0x01) | ((byte[1] & 0x01)<<1) \
          | ((byte[2] & 0x01)<<2) | ((byte[3] & 0x01)<<3);
    w1_bit_io( b & 0x0f );
    byte[0] >>= 1;
    byte[1] >>= 1;
    byte[2] >>= 1;
    byte[3] >>= 1;
  }while( --i );
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
    j = w1_bit_io( 1 );
    byte[0] >>= 1;
    byte[1] >>= 1;
    byte[2] >>= 1;
    byte[3] >>= 1;
    if (j & 0x01) byte[0] |= 0x80;
    if (j & 0x02) byte[1] |= 0x80;
    if (j & 0x04) byte[2] |= 0x80;
    if (j & 0x80) byte[3] |= 0x80;
  }while( --i );
}

unsigned char w1_rom_search( unsigned char diff, unsigned char  *id )
{
  unsigned char i, j, next_diff;
  unsigned char b, sbyte[4];
  
  if( w1_reset(0x01) & 0x01)
    return PRESENCE_ERR;			// error, no device found
  sbyte[0] = SEARCH_ROM; sbyte[1] =SEARCH_ROM; 
      sbyte[2] =SEARCH_ROM; sbyte[3] =SEARCH_ROM;
  w1_byte_wr( sbyte, 0);	        // ROM search command
  next_diff = LAST_DEVICE;			// unchanged on last device
  i = 8 * 8;					// 8 bytes
  do{
    j = 8;					// 8 bits
    do{
      b = w1_bit_io( 0x0f ) & 0x01;		// read bit
      if( w1_bit_io( 0x0f ) & 0x01){			// read complement bit
	if( b & 0x01 )					// 11
	  return DATA_ERR;			// data error
      }
      else
      {
	if( ! (b & 0x01) )
	{				// 00 = 2 devices
	  if( diff > i || ((*id & 1) && diff != i) )
	    {
	    b = 0x01;				// now 1
	    next_diff = i;			// next pass 0
	    }
	}
      }
      w1_bit_io( b );     			// write bit
      *id >>= 1;
      if( b & 0x01 )					// store bit
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
  w1_reset(1);
  if( id )
  {
    // to a single device
    sbyte[0] = MATCH_ROM; sbyte[1] =MATCH_ROM;
     sbyte[2] =MATCH_ROM; sbyte[3] =MATCH_ROM;
    w1_byte_wr( sbyte, 1 );	
    i = 8;
    do
    {
      w1_byte_wr( *id, 1 );
      id++;
    }
    while( --i );
  }
  else
  {
    // to all devices
    sbyte[0] = SKIP_ROM; sbyte[1] =SKIP_ROM;
     sbyte[2] =SKIP_ROM; sbyte[3] =SKIP_ROM;
    w1_byte_wr( sbyte, 1 );
  }
  w1_byte_wr( command, 1 );
}
