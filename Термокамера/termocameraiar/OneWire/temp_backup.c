#include <iom128.h>
#include <inavr.h>
//#include <stdio.h>
#define NULL 0

#include "1wire.h"
#include "1wire_cmd.h"
#include "ow_crc.h"
#include "LED.h"
#include "delay.h"

#include "D:\mcap01mk_soft\types.h"
#include "D:\mcap01mk_soft\base.h"


extern unsigned char dowcrc;
extern unsigned char flag0;
extern unsigned char flag;

unsigned char start_meas( void )
{
  unsigned char com[4] = {CONVERT_T,CONVERT_T,CONVERT_T,CONVERT_T};
  unsigned char tmp =0;
  if (ch1_in) 
    {
      tmp =1;
      com[0] = CONVERT_T;
    }
  if (ch2_in) 
    {
      tmp |= 2;
      com[1] = CONVERT_T;
    }
  if (ch3_in) 
    {
      tmp |= 4;
      com[2] = CONVERT_T;
    }
  if (ch4_in) 
    {
      tmp |= 8;
      com[3] = CONVERT_T;
    };
  if (tmp)
  { 
    //подтяжка должна быть включена не позднее чем через 10 мкс после команды
    //****************?? после окончания записи 0 ?
    w1_command( com, NULL );
    if (tmp & 0x01) pwr1_on; 
    if (tmp & 0x02) pwr2_on; 
    if (tmp & 0x04) pwr3_on; 
    if (tmp & 0x08) pwr4_on;// parasite power on
    delay__(15*800000);
    if (flag) return 0;
    pwr1_off; pwr2_off; pwr3_off; pwr4_off;// parasite power off
  }
  else
  {
    //uputsnl( "Short Circuit !" );
    
  }
  return tmp;
}


void read_meas( void )
{
  unsigned char id[8], diff, sbyte[4];
  static unsigned char  scratchpad[9];
  unsigned char i;
  unsigned int temp;
  
  for( diff = SEARCH_FIRST; diff != LAST_DEVICE; )
  {
    diff = w1_rom_search( diff, id );
    if( diff == PRESENCE_ERR )
    {
      //uputsnl( "No Sensor found" );
      break;
    }
    if( diff == DATA_ERR )
    {
      //uputsnl( "Bus Error" );
      break;
    }
    if( (id[0] == 0x28) || (id[0] == 0x10 ))
    {	// temperature sensor
      dowcrc = 0;
      for( i = 0; i < 8; i++ )
      {
	CRC(id[i]);
	//view(dowcrc, 40, 5);
      }

      sbyte[0] = READ; sbyte[1] = READ; sbyte[2] = READ; sbyte[3] = READ;
      //w1_byte_wr( sbyte, 1);			// read command
      w1_command(sbyte,0);
      dowcrc = 0;
      for (i= 0; i < 9; i ++)
        {
          w1_byte_rd(sbyte);
          scratchpad[i] = sbyte[0];
          CRC(scratchpad[i]);
        }
      if (dowcrc) gr =1; else gr = 0;
      temp = scratchpad[0];
      temp |= (unsigned int) scratchpad[1] << 8;
      if( id[0] == 0x10 )			// 9 -> 12 bit
        temp <<= 3;

            if ((temp >> 4) & 1) red1 = 1; else red1 = 0;
      if ((temp >> 5) & 1) red2 = 1; else red2 = 0;
      if ((temp >> 6) & 1) red3 = 1; else red3 = 0;
      if ((temp >> 7) & 1) red4 = 1; else red4 = 0;
      if ((temp >> 8) & 1) red = 1; else red = 0;
      
      
      ramb[0x20] = temp>>4;
      ramb[0x10] = 1;

      ramb[0x21] = (unsigned int) (id[0] << 8) | id[1];
      ramb[0x22] = (unsigned int) (id[2] << 8) | id[3];
      ramb[0x23] = (unsigned int) (id[4] << 8) | id[5];
      ramb[0x24] = (unsigned int) (id[6] << 8) | id[7];


    }
  }

}
