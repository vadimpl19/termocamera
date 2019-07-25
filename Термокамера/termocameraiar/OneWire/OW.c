//#include "LED.h"
#include "temp.h"
#include "delay.h"
#include <inavr.h>
#include "..\types.h"
#include "..\base.h"
//#include "..\hist.h"
#include "..\timeservice.h"
#include "ow_crc.h"

__flash unsigned char id_board[4][8] = 
    {
      0x10, 0xc6, 0x4e, 0xd3, 0x00, 0x08, 0x00, 0x62,
      0x10, 0xb3, 0xce, 0xc7, 0x00, 0x08, 0x00, 0xec,
      0x10, 0xcb, 0xa8, 0xc7, 0x00, 0x08, 0x00, 0x58,
      0x10, 0xe3, 0xa9, 0xc7, 0x00, 0x08, 0x00, 0x82
    };

extern unsigned char flag;//флаг выполнения задержки
//extern UINT count;
unsigned char f_read = 0;
void GetT(void)
{
  if (flag!=0) return;
//  if (count!=0) return;
  ramb[0x0a]=time;
//  ramb[0x08]=count;  
//  addh(0x4402);
   if (f_read) {read_meas();  return;};
  start_meas();
  f_read =1;
}


extern unsigned char dowcrc;
char lineflags;
/***************************************************
биты 0...3 -подключен новый датчик
биты 4...7 -подключено более одного нового датчика
***************************************************/


void config_uLan(void)
{

  static unsigned char ul_flag = 0x80, id_[8], tmp1 =0, line_mask = 1;
  unsigned char id[8], i;
  unsigned int adr, adr_, tmp;
 if(lineflags&0xf0){//ошибка. Было подключено более одного датчика. Выходим
 return;
 }   
//  line_mask = 2;//**********************
  ul_flag =(ul_flag&0xf0) + line_mask;//добавляем маску линии
  search(&ul_flag, id);
  
  if (ul_flag&0x70)//ошибка CRC, шины или нет датчиков
    {
      ul_flag = 0x80;
      tmp1=0;
      line_mask <<= 1;
      if (line_mask > 0x08) line_mask = 1;
      return;
    }

  
  adr = search_free(line_mask);//ищем свободную ячейку, если их нет, то 0
  if (adr==0)
    {
      line_mask <<= 1;
      if (line_mask > 0x08) line_mask = 1;
      return;  
    }
  
  if (ul_flag & 0x80)
    {
      if (tmp1 > 1)//подключено одновременно больше 1 датчика
        {
          lineflags |= (line_mask <<4);
        }
        else if (tmp1 == 1)//иначе записываем ID в базу
        {
//          addh(0x5557);
//          addh(adr);
          lineflags |= line_mask & 0x0f;
          for (i = 0; i < 4; i ++)
            {
               tmp = (unsigned int) id_[1 +2*i] <<8 | id_[2*i];
//              hrem[adr + i] = tmp;
              setrg(adr + i, tmp);

            }
        }
      tmp1 = 0;
      /**** переключаем шлейф ****/
      line_mask <<= 1;
      if (line_mask > 0x08) line_mask = 1;
    }
  
  switch (line_mask)
    {
      case 1 : adr_ = 0x17c; break;
      case 2 : adr_ = 0x200; break;
      case 4 : adr_ = 0x280; break;
      case 8 : adr_ = 0x300; break;
    }

  if (!(ul_flag & 0x80))
  {
    if ( comp(id, adr_, adr) )//если датчика нет в базе
      {
//      hrem[0x17C] = comp(id, adr_, adr);
//      addh(0x5559);      addh(adr_);addh(adr);
//      addh(( (int)id[0])<<8+id[1]);
//      addh(((int)id[2])<<8+id[3]);
      //hrem[0x17D]++;
        tmp1 ++;
        for (i = 0; i < 8; i ++)
          {
            id_[i] = id[i];
          }
      }
  }
}
/**************************************************************************************
функция определения ID внутреннего датчика температуры устройства 
возвращает 
0 - все нормально, ID добавлен в базу
1 - датчик не найден
2- больше одного датчика на шлейфе
3- ошибка работы со шлейфом
**************************************************************************************/
char get_temp_id(void)
{

  static unsigned char ul_flag = 0x80, id_[8];//, tmp1 =0;
  unsigned char id[8], line_mask, i;
  //unsigned int adr, adr_, tmp;
  
  line_mask = 1;//**********************
  ul_flag |= line_mask;//добавляем маску линии
  search(&ul_flag, id);
  if (ul_flag &0x70) return 3;
        for (i = 0; i < 8; i ++)
        {
          id_[i] = id[i];
        }

  if (ul_flag & 0x80) return 1;
  search(&ul_flag, id);
  if (ul_flag &0x70) return 3;
  if (!(ul_flag & 0x80)) {return 2;}
  setrg(0x170, id_[0]+((int)id_[1]<<8));
  setrg(0x171, id_[2]+((int)id_[3]<<8));
  setrg(0x172, id_[4]+((int)id_[5]<<8));
  setrg(0x173, id_[6]+((int)id_[7]<<8));
  return 0;
}

