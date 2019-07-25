#include <iom128.h>
#include <inavr.h>
//#include <stdio.h>
#define NULL 0

#include "1wire.h"
#include "1wire_cmd.h"
#include "ow_crc.h"
//#include "LED.h"
#include "delay.h"

#include "..\types.h"
#include "..\led.h"
#include "..\base.h"
#include "..\timeservice.h"
//#include "..\hist.h"
//#define Var_1
int dtime;
char chmaskout;
void set_time(){ // функция фиксации текущего времени и вычисления дельты от предидущей фиксации (в переменной dtime);

static unsigned int oldtime=0;
int newt;
  __disable_interrupt();
   newt=time;  
  __enable_interrupt();
  dtime=newt-oldtime;
  if (dtime<=0){dtime +=0x8000;}
  oldtime=newt;
  return;
}

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
//    pwrf=1;
    w1_command( com, NULL );
//    if (tmp & 0x01) pwr1_on; 
//    if (tmp & 0x02) pwr2_on; 
//    if (tmp & 0x04) pwr3_on; 
//    if (tmp & 0x08) pwr4_on;// parasite power on
    set_time();// засечем время преобразования 
    
//    delay__(15*800000); !!!!!!!!!!!!!
    if (flag) return 0;
    pwr1_off; pwr2_off; pwr3_off; pwr4_off;// parasite power off
  }
  else
  {
    //uputsnl( "Short Circuit !" );
    
  }
  return tmp;
}


extern unsigned char f_read;
void read_meas( void )
{
  unsigned char sbyte[4];
  static unsigned char  scratchpad[4][9];//???
  static unsigned char n_read[4] = {0, 0, 0, 0};//счетчик числа запросов от датчика
  static unsigned char count[4] ={0,0,0,0};//номера текущего датчика к обработке. 32 - все считаны
  static chmask=0;
  unsigned char i, j;
  unsigned int  tmp;
  int temp;

  
while ((count[0]<33) || (count[1]<32) || (count[2]<32) || (count[3]<32))
{
   while(count[0]<32)
   { 
         if (isempty(0x180+4*count[0])==0) break;
         count[0]++;
   };
   if((dev_ver_heat==0)&(count[0]==32)){//считываем температуру внутреннего датчика
      count[0]=33;//идентифицирует состояние считывания температуры внутреннего датчика
   }
   
   while(count[1]<32)
   { 
         if (isempty(0x200+4*count[1])==0) break;
         count[1]++;
   }
   while(count[2]<32)
   { 
         if (isempty(0x280+4*count[2])==0) break;
         count[2]++;
   }
   while(count[3]<32)
   { 
         if (isempty(0x300+4*count[3])==0) break;
         count[3]++;
   }
   
    //tmp = 0;  обработка ошибок типа кз или отсутствия датчика
    w1_reset(0x0f);
    

    
    sbyte[0] = sbyte[1] = sbyte[2] = sbyte[3] = MATCH_ROM;
    w1_byte_wr( sbyte,0 );
    
    for (i = 0; i < 4; i ++)
      {
        sbyte[0] = hrem[0x180 + 4*count[0] +i];
        sbyte[1] = hrem[0x200 + 4*count[1] +i];
        sbyte[2] = hrem[0x280 + 4*count[2] +i];
        sbyte[3] = hrem[0x300 + 4*count[3] +i];
        if (count[0]==33)sbyte[0]=hrem[0x170+i];  //считываем внутренний датчик
        w1_byte_wr( sbyte,0 );
        
        sbyte[0] = hrem[0x180 + 4*count[0] +i]>>8;
        sbyte[1] = hrem[0x200 + 4*count[1] +i]>>8;
        sbyte[2] = hrem[0x280 + 4*count[2] +i]>>8;
        sbyte[3] = hrem[0x300 + 4*count[3] +i]>>8;
        if (count[0]==33)sbyte[0]=hrem[0x170+i]>>8;  //считываем внутренний датчик
        w1_byte_wr( sbyte,0 );
        
      }
    
      sbyte[0] = sbyte[1] = sbyte[2] = sbyte[3] = READ; 
      w1_byte_wr( sbyte,0);			// read command
      
      for (i= 0; i < 9; i ++)
        {
          w1_byte_rd(sbyte);
          scratchpad[0][i] = sbyte[0];
          scratchpad[1][i] = sbyte[1];
          scratchpad[2][i] = sbyte[2];
          scratchpad[3][i] = sbyte[3];
        }
   if(count[0]==33){ //считываем внутренний датчик температуры
             dowcrc = 0;
             for (i = 0; i < 9; i ++) { CRC(scratchpad[0][i]); }
             if (!(dowcrc)&&(scratchpad[0][7]!=0)){//crc сошлось,(+проверка на нулевые данные ) обработаем внутреннюю температуру
                count[0]=34; //состояние - внутреннюю температуру тоже обработали
                hrem[0x175]= scratchpad[0][0]+(scratchpad[0][1] << 8);
                ramb[dev_status] &=~(1<<eheat); 
                if ((int)hrem[0x175]<(int)hrem[0x174]) {heaton }
                else goto errheat;
             }else {
errheat:
                ramb[dev_status] |=1<<eheat; 
                heatoff; 
             } 
   }
   for (j=0;j<4;j++)
   { 
      if (count[j]<32)
      {char stad; //переменная для адреса регистра статуса, содержащего бит с этим датчиком
       int alad;
//         stad=0x10+j*2+(count[j]>>1);
           stad=0x10+j*2+(count[j]>>4); //вычислили адрес регистра статуса
//         if((tmp&(1<<j))==0)
         if((dev_status&(1<<j))==0) // идем дальше, если статус шлейфа в норме
         {
//             addh(0x321);
//             addh(j);
//             addh(count[j]);
             temp = scratchpad[j][0];
             temp |= (unsigned int) scratchpad[j][1] << 8;

/*
             temp = scratchpad[j][2];
             temp |= (unsigned int) scratchpad[j][3] << 8;             
*/             
             dowcrc = 0;
             for (i = 0; i < 9; i ++) { CRC(scratchpad[j][i]); }
             if ((!(dowcrc))&&(scratchpad[j][7]!=0) ) 
             {int intt,dtemp;
//                 addh(0x322);
                
                 if (temp==0xaa)
                 {  //температура 85град возможен сбой
//                    addh(j);
  //                  addh(count[j]);
    //                addh(0xaa01);
      //              addh(ramb[4]);
        //            addh(ramb[0x14]);
                    if ( scratchpad[j][6]==0x0c){ //было КЗ или обрыв 
                      goto to_first_convert;
                    }
                    if ( (ramb[stad]&(1<<(count[j] & 0x0f)))==0) 
                    {  //addh(0xaa02);
                       if ((ramb[stad-0x10]&(1<<(count[j] & 0x0f)))!=0) { goto temp_ok;}
                       else {ramb[stad-0x10] |=1<<(count[j] & 0x0f); }//установили флаг - датчик уже был 1 раз опрошен
                       goto to_first_convert;
                    }   
                 }
temp_ok:          
//                addh(0x9999);
//                addh(temp);         
//                addh(stad);
                dtemp= temp-ramb[0x20 + count[j]+ 32*j];//вычисляем прирост температуры
                ramb[0x20 + count[j]+ 32*j] = temp;
//                if (count[j] < 16) ramb[0x10+j*2] |= (unsigned int)(1<<count[j]);
//                else ramb[0x11+j*2] |= (unsigned int) (1<<(count[j] & 0x0f));

                
                tmp=hrem[0x380+count[j]+j*32];
                if ( (temp/2)>=(signed char)(tmp&0xff) )
                {  
                    if (count[j] < 16) 
                    {  intt = hrem[0x160+j*2]|(1<<count[j]);
                       if (intt!=hrem[0x160+j*2]) setrg(0x160+j*2,intt);
                    }else 
                    {  intt = hrem[0x161+j*2]|(1<<(count[j]& 0x0f));
                        if (intt!=hrem[0x161+j*2]) setrg(0x161+j*2,intt);
                    };
                }else
                {  
                   if (count[j] < 16) 
                   {  intt = hrem[0x160+j*2]&~(1<<count[j]);
                      if ((intt!=hrem[0x160+j*2])&&((hrem[0x17f]&(1<<j))==0))          
                                                 setrg(0x160+j*2,intt); //отключение аларма если не 
                                                                       //включен режим защелки
                   }else
                   {  intt = hrem[0x161+j*2]&~(1<<(count[j]& 0x0f));
                          if ((intt!=hrem[0x161+j*2])&&((hrem[0x17f]&(1<<j))==0)) setrg(0x161+j*2,intt);
                   };
                };      
                if( (ramb[stad] &(1<< (count[j] & 0x0f) ))==0 ) goto after_speed;//связи с датчиком не было, измерения пропускаем 
                alad=0x168+j*2+(count[j]>>4); // адрес сигналов превышения тмпературы
                if (dtemp>0){ 
                   //вычисляем скорость изменения температуры
//                   dtime=dtime>>2;
                   {int vtemp;
                      vtemp=(dtemp*255)/(dtime>>2);
//                      ramb[0x0e]=vtemp;
//                      addh(0x1111);
//                      addh(vtemp);
//                      addh(dtime);
//                      addh(dtemp);
                      if ((vtemp>>1)>=(tmp>>8))//сработал сигнал превышения порога по скорости нарастания
                      {  int intt; 
//                           addh(0x2222);
                           
                           intt = hrem[alad]|(1<<(count[j]&0x0f));
//                           addh(alad);
//                           addh(intt);
                           if (intt!=hrem[alad]) setrg(alad,intt);
                      }else goto lowspeed;
                    }  
                }else{
lowspeed:
                   intt = hrem[alad]&~(1<<(count[j]&0x0f));
                   if ( (intt!=hrem[alad])&&((hrem[0x17f]&(1<<(j+8)))==0) )          
                                                 setrg(alad,intt); //отключение аларма если не 
                                                                       //включен режим защелки                 
                }
after_speed:                  
                ramb[stad] |=1<<(count[j] & 0x0f);// установили флаг - связь с датчиком установлена
             }else
             { //crc не сошлось;
               n_read[j]++;
               if (n_read[j] > hrem[0x104])
               {    // число попыток истекло
                      chmask|=1<<j;
//                    if (count[j] < 16) ramb[0x10+j*2] &= ~((unsigned int)(1<<count[j]));
//                    else ramb[0x11+j*2] &= ~((unsigned int) (1<<(count[j] & 0x0f)));
                      ramb[stad] &= ~((unsigned int) (1<<(count[j] & 0x0f)));
                      ramb[stad-0x10] &= ~((unsigned int) (1<<(count[j] & 0x0f))); //!!!! обнулили статус - было первое включение
                    n_read[j] = 0;
               }else
               {
                 count[j] --;
               }
             }  
         }else 
         { 
//               if (count[j] < 16) ramb[0x10+j*2] &= ~((unsigned int)(1<<count[j]));
//               else ramb[0x11+j*2] &= ~((unsigned int) (1<<(count[j] & 0x0f)));

               ramb[stad] &= ~((unsigned int) (1<<(count[j] & 0x0f)));               
               ramb[stad-0x10] &= ~((unsigned int) (1<<(count[j] & 0x0f)));  //обнуляем также бит проверки на 1-е включение.             
                n_read[j] = 0;
         }     
      }     
to_first_convert: 
        
   count[j]++;
   } //end for
    __watchdog_reset();
    return;
}//end while
  count[0] = 0;
  count[1] = 0;
  count[2] = 0;
  count[3] = 0;
  f_read = 0;
  chmaskout=chmask;

  chmask=0;
};








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
  else {
      dowcrc = 0;
      for( i = 0; i < 8; i++ )
      {
	CRC(id[i]);
	//view(dowcrc, 40, 5);
      }
      if (dowcrc) *line_mask = 0xc0;//
      else *line_mask |= 0x80;//поиск завершен
   }
}

/*************************************************
поиск адреса свободной ячейки памяти для записи
данных нового датчика
возвращает адрес свободной ячейки ID или 0 если все ячейки на шлейфе заполнены
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
  return 0;//все ячейки памяти заполнены
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
