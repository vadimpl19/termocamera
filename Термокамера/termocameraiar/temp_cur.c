void read_meas( void )
{
  unsigned char sbyte[4];
  static unsigned char  scratchpad[4][9];//???
  static unsigned char n_read[4] = {0, 0, 0, 0};//счетчик числа запросов от датчика
  static unsigned char count[4] ={0,0,0,0};//номера текущего датчика к обработке. 32 - все считаны
  unsigned char i, j;
  unsigned int temp, tmp;
  
while ((count[0]<32) && (count[1]<32) && (count[2]<32) && (count[3]<32))
{
   while(count[0]<32)
   { 
         if (isempty(0x180+4*count[0])==0) break;
         count[0]++;
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
         if (isempty(0x300+4*count[1])==0) break;
         count[3]++;
   }
    //tmp = 0;  обработка ошибок типа кз или отсутствия датчика
    tmp = w1_reset(0x0f);
    ramb[0x18] &= 0xfff0;
    ramb[0x18] |= (tmp & 0x0f);//кз на шлейфах
    //    tmp |= (tmp>> 4);//старший полубайт - ошибка присутствия **

    
    sbyte[0] = sbyte[1] = sbyte[2] = sbyte[3] = MATCH_ROM;
    w1_byte_wr( sbyte );
    
    for (i = 0; i < 4; i ++)
      {
        sbyte[0] = hrem[0x180 + 4*count[0] +i];
        sbyte[1] = hrem[0x200 + 4*count[1] +i];
        sbyte[2] = hrem[0x280 + 4*count[2] +i];
        sbyte[3] = hrem[0x300 + 4*count[3] +i];
        w1_byte_wr( sbyte );
        
        sbyte[0] = hrem[0x180 + 4*count[0] +i]>>8;
        sbyte[1] = hrem[0x200 + 4*count[1] +i]>>8;
        sbyte[2] = hrem[0x280 + 4*count[2] +i]>>8;
        sbyte[3] = hrem[0x300 + 4*count[3] +i]>>8;
        w1_byte_wr( sbyte );
        
      }
    
      sbyte[0] = sbyte[1] = sbyte[2] = sbyte[3] = READ; 
      w1_byte_wr( sbyte);			// read command
      
      for (i= 0; i < 9; i ++)
        {
          w1_byte_rd(sbyte);
          scratchpad[0][i] = sbyte[0];
          scratchpad[1][i] = sbyte[1];
          scratchpad[2][i] = sbyte[2];
          scratchpad[3][i] = sbyte[3];
        }
 
   for (j=0;j<4;j++)
   { 
      if (count[j]<32)
      {char stad;
         stad=0x10+j*2+(count[j]>>1);
      
         if((tmp&(1<<j))==0)
         {
             addh(0x321);
             temp = scratchpad[0][0];
             temp |= (unsigned int) scratchpad[0][1] << 8;
             dowcrc = 0;
             for (i = 0; i < 9; i ++) { CRC(scratchpad[j][i]); }
             if (!(dowcrc)) 
             {char stad;
                addh(0x322);
                
                if (temp==0xaa)
                {  //температура 85град возможен сбой
                   
                   if ( (ramb[stad]&(1<<(count[j] & 0x0f)))==0) 
                   {
                      if (ramb[stad-0x10]&(1<<(count[j] & 0x0f))!=0) goto temp_ok;
                      else ramb[stad-0x10] |=1<<(count[j] & 0x0f); //установили флаг - датчик уже был 1 раз опрошен
                      goto to_first_convert;
                   }   
                }
temp_ok:                   
                ramb[0x20 + count[j]+ 32*j] = temp;
//                if (count[j] < 16) ramb[0x10+j*2] |= (unsigned int)(1<<count[j]);
//                else ramb[0x11+j*2] |= (unsigned int) (1<<(count[j] & 0x0f));
                ramb[stad] |=1<<(count[j] & 0x0f);
                
                i=hrem[0x380+count[j]+j*32];
                if( (int)(temp/2)>=(signed char)i)
                {  int intt;
                    if (count[j] < 16) 
                    {  intt = hrem[0x160+j*2]|(1<<count[j]);
                       if (intt!=hrem[0x160+j*2]) setrg(0x160+j*2,intt);
                    }else 
                    {  intt = hrem[0x161+j*2]|(1<<(count[0]& 0x0f));
                        if (intt!=hrem[0x161+j*2]) setrg(0x161+j*2,intt);
                    };
                }else
                {  int intt; 
                   if (count[j] < 16) 
                   {  intt = hrem[0x160+j*2]&~(1<<count[j]);
                      if ((intt!=hrem[0x160+j*2])&&((hrem[0x17f]&(1<<j))==0))          
                                                 setrg(0x160+j*2,intt); //отключение аларма если не 
                                                                       //включен режим защелки
                   }else
                   {  intt = hrem[0x161+j*2]|(1<<(count[j]& 0x0f));
                      if ((intt!=hrem[0x161+j*2])&&((hrem[0x17f]&(1<<j))==0)) setrg(0x161+j*2,intt);
                   };
                };      

             }else
             {
               n_read[j]++;
               if (n_read[j] > hrem[0x104])
               {    
//                    if (count[j] < 16) ramb[0x10+j*2] &= ~((unsigned int)(1<<count[j]));
//                    else ramb[0x11+j*2] &= ~((unsigned int) (1<<(count[j] & 0x0f)));
                      ramb[stad] &= ~((unsigned int) (1<<(count[j] & 0x0f)));
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
                n_read[j] = 0;
         }     
      }     
to_first_convert:      
   count[j]++;
   }
    __watchdog_reset();
    return;
}//end while
  count[0] = 0;
  count[1] = 0;
  count[2] = 0;
  count[3] = 0;
  f_read = 0;
};




