#include <iom128.h>
#include <inavr.h>
//#include <stdio.h>
#define NULL 0

#include "1wire.h"
#include "1wire_cmd.h"
#include "ow_crc.h"
#include "LED.h"
#include "delay.h"

#include "..\types.h"
#include "..\base.h"

//#define Var_1

extern unsigned char dowcrc;
extern unsigned char flag0;
extern unsigned char flag;

#ifdef  Var_1
unsigned char start_meas( void )
{
  unsigned char com[4] = {CONVERT_T,CONVERT_T,CONVERT_T,CONVERT_T};
  unsigned char tmp =0, sbyte[4], i, b;
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
    //подт€жка должна быть включена не позднее чем через 10 мкс после команды
    //****************?? после окончани€ записи 0 ?
      //****w1_command( com, NULL );
    w1_reset(1);
    sbyte[0] = SKIP_ROM; sbyte[1] =SKIP_ROM;
     sbyte[2] =SKIP_ROM; sbyte[3] =SKIP_ROM;
    w1_byte_wr( sbyte );
    //*****w1_byte_wr( com );****//
    /*
    void w1_byte_wr( unsigned char byte[4])
      {
        unsigned char i = 8, b;
    */
        i = 7;
        do
        {
          b = (com[0] & 0x01) | ((com[1] << 1) & 0x02) \
                | ((com[2] << 2) & 0x04) | ((com[3] << 3) & 0x08);
          //****w1_bit_io( b );****//
          /*
          unsigned char w1_bit_io( unsigned char b )
            {
          */
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
          /*
              return b ;
            }
          */
          
          com[0] >>= 1;
          com[1] >>= 1;
          com[2] >>= 1;
          com[3] >>= 1;
        }while( --i );
            __disable_interrupt();
              line1_down; line2_down; line3_down; line4_down;
              __delay_cycles(15 * 2);
  
              if (b & 0x01) line1_up;
              if (b & 0x02) line2_up;
              if (b & 0x04) line3_up;
              if (b & 0x08) line4_up;
          /*    
              __delay_cycles(15 * (15 - 1));
          
              if (ch1_in == 0) b &= ~(0x01);
              if (ch2_in == 0) b &= ~(0x02);
              if (ch3_in == 0) b &= ~(0x04);
              if (ch4_in == 0) b &= ~(0x08);
          
              __enable_interrupt();//????????????
          
              flag0 = 1;
              delay_(15 * (60 - 15));
          */
/***************************************************************/
    /*
    if (tmp & 0x01) pwr1_on; 
    if (tmp & 0x02) pwr2_on; 
    if (tmp & 0x04) pwr3_on; 
    if (tmp & 0x08) pwr4_on;// parasite power on
    */
    pwr1_on; pwr2_on; pwr3_on; pwr4_on;
    __enable_interrupt();//
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

#else

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
    //подт€жка должна быть включена не позднее чем через 10 мкс после команды
    //****************?? после окончани€ записи 0 ?
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

#endif


extern __flash unsigned char id_board[4][8];
/*
void read_meas( void )
{
  unsigned char sbyte[4];
  static unsigned char  scratchpad[4][9];
  unsigned char i, j;
  unsigned int temp;

    w1_reset(0x0f);
    // to a single device
    sbyte[0] = MATCH_ROM; sbyte[1] = MATCH_ROM;
     sbyte[2] = MATCH_ROM; sbyte[3] = MATCH_ROM;
    w1_byte_wr( sbyte );	
    i = 8;
    do
    {
      sbyte[0] = id_board[1][8-i];
      sbyte[1] = id_board[2][8-i];
      sbyte[2] = id_board[3][8-i];
      sbyte[3] = id_board[0][8-i];
      
      w1_byte_wr( sbyte );
    }
    while( --i );

      
  
      sbyte[0] = READ; sbyte[1] = READ; sbyte[2] = READ; sbyte[3] = READ;
      w1_byte_wr( sbyte);			// read command
      //w1_command(sbyte,0);
      
      for (i= 0; i < 9; i ++)
        {
          w1_byte_rd(sbyte);
          scratchpad[0][i] = sbyte[0];
          scratchpad[1][i] = sbyte[1];
          scratchpad[2][i] = sbyte[2];
          scratchpad[3][i] = sbyte[3];
        }
  for (j = 0; j < 4; j ++)      
    {
      dowcrc = 0;
      for (i = 0; i < 9; i ++)
        {
          CRC(scratchpad[0][i]);
        }
      if (dowcrc) gr =1; else gr = 0;
    }
      
      temp = scratchpad[0][0];
      temp |= (unsigned int) scratchpad[0][1] << 8;
//      if( id[0] == 0x10 )			// 9 -> 12 bit
        temp <<= 3;
/*
            if ((temp >> 4) & 1) red1 = 1; else red1 = 0;
      if ((temp >> 5) & 1) red2 = 1; else red2 = 0;
      if ((temp >> 6) & 1) red3 = 1; else red3 = 0;
      if ((temp >> 7) & 1) red4 = 1; else red4 = 0;
      if ((temp >> 8) & 1) red = 1; else red = 0;
      
      
      ramb[0x20] = temp>>4;
      ramb[0x10] = 1;
      
      temp = scratchpad[1][0];
      temp |= (unsigned int) scratchpad[1][1] << 8;
      ramb[0x21] = temp >> 1;
      
      temp = scratchpad[2][0];
      temp |= (unsigned int) scratchpad[2][1] << 8;
      ramb[0x22] = temp >> 1;
      
      temp = scratchpad[3][0];
      temp |= (unsigned int) scratchpad[3][1] << 8;
      ramb[0x23] = temp >> 1;
}
*/

void search_rom(void)
{
  unsigned char id[8], diff, i;
  unsigned char j = 0;
  for( diff = SEARCH_FIRST; diff != LAST_DEVICE; )
  {
    diff = w1_rom_search( diff, id , 1);
    if( diff == PRESENCE_ERR )
    {
      //uputsnl( "No Sensor found" );
      //ramb[0x30] = 0;
      break;
    }
    if( diff == DATA_ERR )
    {
      //uputsnl( "Bus Error" );
      //ramb[0x30] = 0xf0f0;
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
    }
    else dowcrc = 255;
    ramb[0x00 +j] = id[1];
    ramb[0x00 +j] |= (unsigned int) (id[0] <<8);
    ramb[0x01 +j] =  id[3];
    ramb[0x01 +j] |= (unsigned int) (id[2] <<8);
    ramb[0x02 +j] = id[5];
    ramb[0x02 +j] |= (unsigned int) (id[4] <<8);
    ramb[0x03 +j] = id[7];
    ramb[0x03 +j] |= (unsigned int) (id[6] <<8);
    ramb[0x04 +j] = dowcrc;
    j += 5;
  }
}

extern unsigned char lineflags;
/***************************************************
биты 0...3 -подключен новый датчик
биты 4...7 -подключено более одного нового датчика
***************************************************/

void search(unsigned char *line_mask, unsigned char id[8])
{
  unsigned char i;
  static unsigned char diff;
  if (*line_mask & 0x80) //запустить новый поиск если установлен флаг
    {
      diff = SEARCH_FIRST;
      *line_mask &= ~(0x80);
    }
  //for( diff = SEARCH_FIRST; diff != LAST_DEVICE; )
  if (diff != LAST_DEVICE)
  {
    diff = w1_rom_search( diff, id , *line_mask & 0x0f);
    if( diff == PRESENCE_ERR )
    {
      //uputsnl( "No Sensor found" );
      //ramb[0x30] = 0;
      *line_mask = 0xa0;//0b10100000
    }
    if( diff == DATA_ERR )
    {
      //uputsnl( "Bus Error" );
      //ramb[0x30] = 0xf0f0;
      *line_mask = 0x90;//0b10010000
    }
    
      dowcrc = 0;
      for( i = 0; i < 8; i++ )
      {
	CRC(id[i]);
	//view(dowcrc, 40, 5);
      }
      if (dowcrc) *line_mask = 0xc0;//
    
  }
  else (*line_mask |= 0x80);//поиск завершен

}

/*************************************************
поиск адреса свободной €чейки пам€ти дл€ записи
данных нового датчика
возвращает адрес свободной €чейки ID или 0 если все €чейки на шлейфе заполнены
*************************************************/
unsigned int search_free(unsigned char line_mask)
{
  unsigned int adr, adr_end;
  switch (line_mask)
    {
      case 1 : adr = 0x180; adr_end = 0x200; break;
      case 2 : adr = 0x200; adr_end = 0x280; break;
      case 4 : adr = 0x280; adr_end = 0x300; break;
      case 8 : adr = 0x300; adr_end = 0x380; break;      
    }
//  addh(0x1111);  
  while (adr < adr_end)
    {
//      if ((hrem[adr] >> 8) != 0x10) return adr;
//        addh(0x2222);
//        addh(adr);
        if((hrem[adr]==0xffff)&&(hrem[adr+1]==0xffff)&&(hrem[adr+2]==0xffff)
            &&(hrem[adr+3]==0xffff)) return adr;
        adr +=4;
    }
//    addh(0x3333);
  return 0;//все €чейки пам€ти заполнены
}


#define adr_id_board 0x170
unsigned char comp(unsigned char id[8], unsigned int adr_s, unsigned int adr_end)
{
  unsigned char c;
  unsigned int tmp, i;
  if (adr_s == 0x17c)//шлейф 1 имеет датчик на плате
    {
      c = 0;
      for (i = 0; i < 4; i ++)
        {
          tmp = (unsigned int) id[1 +2*i] <<8 | id[2*i];
          if (tmp == hrem[adr_id_board + i]) c ++;
        }
      if (c == 4) return 0;
      adr_s +=4;
    }
  while (adr_s < adr_end)
    {
      c = 0;
      for (i = 0; i < 4; i ++)
        {
          //tmp = id[1 + 2*i];
          //tmp |= (unsigned int) id[2*i]<<8;
          tmp = (unsigned int) id[1 +2*i] <<8 | id[2*i];
//          hrem[0x188] = tmp;
//          hrem[0x18a] = adr_s + i;
//          hrem[0x189] = hrem[adr_s + i]; return;
          if (tmp == hrem[adr_s + i]) c ++;
        }
      if (c == 4)//датчик есть в базе
        {
          //*res ++;
//          addh(0x1111);
//          addh(adr_s);
          return 0;
        }
      adr_s += 4;
    }
  return 1;
}
