#include <ina90.h>
#include <iom128.h>
#include "led.h"
#include "types.h"
#include "base.h"
#include "timeservice.h"
int time;
int touttable[maxtout];
void initime(){
char i;
  time=0;
  for(i=0;i<maxtout;i++)touttable[i]=0;
  TCCR3A=0;
  TCCR3B=0x0b; //prescaler=64 CTC Moda c перезагрузкой по 1-му
//  OCR3A=115; //прерывания каждую миллисекунду
  OCR3A=115*2;
  ETIMSK_OCIE3A=1; //разрешили прерывания 
}


#pragma vector=TIMER3_COMPA_vect
__interrupt void t3_comp_isr(){
   time++;
   time &=0x7fff;
/*   off4;
   if ((time&0xff)>100 ) {redon4}
   else gron4
   */
};

int touttable[maxtout];
void settout(char num, int tout){
int tt;

   _CLI();
   tt=time;
  _SEI();
   touttable[num]=tt+tout;
};
char gettout(char num){
int tt;
   _CLI();
   tt=time;
   _SEI();
/*
   if ((touttable[num]<0)&&(tt<0x4000))
      touttable[num] += 0x8000; //коррекция значения времени при переполнении таймера
   if (touttable[num]>tt) return 1; //таймаут не истек;
   else return 0;   
*/   
   if (touttable[num]<0) {
       if(tt<0x4000) {
           touttable[num] += 0x8000; //коррекция значения времени при переполнении таймера
           if (touttable[num]>tt) return 1; //таймаут не истек;
           else return 0;   
       }else return 1;    //таймаут не истек;
   };    
   //корректировка не нужна просто сравниваем значения
   if (touttable[num]>tt) return 1; //таймаут не истек;
           else return 0;   

}
char red;
void tsttime(){
//  redonw 

  if (red==0){red=1; settout(0,1);offw 
                                    redonw
                                    return;}
  if (red==1)if (gettout(0)==0){red=2; offw 
                                      settout(0,3000);
                                  redonw
                                  return;};
  if (red==2)if (gettout(0)==0){red=1; offw
                                   settout(0,3000);
                                   gronw
                                  return;}
  if (red>2) red=0;
  
};
