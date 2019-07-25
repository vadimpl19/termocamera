#include <iom128.h>
#include "ina90.h"
#include "mbsl0.h"
#include "mbsl1.h"
#include "string.h"
#include "stdio.h"
#include "led.h"
#include "types.h"
#include "base.h"
#include "timeservice.h"
#include "zerodef.h"
#include "hist.h"

#include "OneWire\OW.h"
#include "OneWire\main.h"
extern char res_fl;
extern char chmaskout;
int tmv;
int inn;
int t1;
int t2;
int k;
int t3;
int qwerty;
int t4;
int t5;
int mmm;
UINT get_sp();
      
extern struct isr_cntx u0,u1;
/*
struct isr_cntx {
  char flag35;
  char state;
  unsigned char l;
  char addr;
  char rbuf[8];
//  char tbuf[263];
  char tbuf[128+8];
 };
*/
mbdiagn(){
_ID
hrem[0x110]=u0.flag35+(u1.flag35<<8);
hrem[0x111]=u0.state+(u1.state<<8);
hrem[0x112]=u0.l+(u1.l<<8);
hrem[0x113]=u0.addr+(u1.addr<<8);
hrem[0x114]=u0.rbuf[0]+(u1.rbuf[0]<<8);
hrem[0x115]=u0.rbuf[1]+(u1.rbuf[1]<<8);
hrem[0x116]=u0.rbuf[2]+(u1.rbuf[2]<<8);
hrem[0x117]=u0.rbuf[3]+(u1.rbuf[3]<<8);
hrem[0x118]=u0.rbuf[4]+(u1.rbuf[4]<<8);
hrem[0x119]=u0.rbuf[5]+(u1.rbuf[5]<<8);
hrem[0x11a]=u0.tbuf[1]+(u1.tbuf[1]<<8);
hrem[0x11b]=TIFR;
hrem[0x11c]=UCSR0B;
hrem[0x11d]=UCSR0C;
hrem[0x11d]=TIMSK;
_IE

}
void delayloop(unsigned int d){
unsigned int i,i2;
for (i=0;i<d;i++)
  for (i2=0;i2<1100;i2++) _NOP();
};
//                                                                                                    #pragma inline

///////////////////////////////////////////////////////////////////////////
// Инициируем порты ввода вывода для чтения перемычек и зажигания лампочек
void iniports(){
//  DDRB=0XFF;
//  DDRA=0XFF;
  
  DDRC = 0xff; //Лампочки на вывод
  DDRG = 0x03;
  PORTC = 0x00;
  PORTG = 0x00;
  redonw

  PORTG_Bit3=1; //Включить PULUP на перемычки
  PORTG_Bit4=1;
  PORTD_Bit6=1;
  PORTD_Bit7=1;
  
}
/*******************************************************************************
 процесс индикации
*******************************************************************************/ 
#define nt 1000
char ledstate;
extern char lineflags; // бит 0-3 подключен датчик 4-7 - более одного нового датчика
void ledpr(){
    if ((ramb[0x18]&0x7f00)!=0) {//поломка сигнализатора
            if ((time&1024)==0){grw=1;redw=0; }
            else {grw=0;redw=1;}
            return;
    }

   if ((ramb[0x18]&0x8000)!=0){ //режим конфигурирования микролан)
      if (ledstate!= 2){ //только что перешли в режим конфигурирования микролан
         offw; off1;  off2; off3; off4; 
         ledstate=2;
         settout(0,nt);
         return;
      }else if (gettout(0)==0) {
                if (lineflags==0) {
                   { settout(0,nt);grw^=1;gr1^=1;gr2^=1;gr3^=1;gr4 ^=1; return;}
                }else {  settout(0,nt);
                        if ((lineflags&0xf0)!=0)  {  grw=0; redw=1;}
                        else {grw^=1;redw=0;} 
                            //проверяем флаги по каждой линии  на ошибочное подключение
                         // if ((lineflags&0x10)!=0) {gr1=0;red1^=1;}  
                          if ((lineflags&0x20)!=0) {gr2=0;red2^=1;}
                          if ((lineflags&0x40)!=0) {gr3=0;red3^=1;}                          
                          if ((lineflags&0x80)!=0) {gr4=0;}//red4^=1;}
                            //проверяем флаги на каждой линии на появление нового датчика  
                       //   if ((lineflags&1)!=0) {gr1=0;red1^=1;if (red1==0)lineflags&=~1;}  
                        if ((lineflags&2)!=0) {gr2=0;red2^=1;if (red2==0)lineflags&=~2;}
                          if ((lineflags&4)!=0) {gr3=0;red3^=1;if (red3==0)lineflags&=~4;}                          
                          if ((lineflags&8)!=0) {gr4=0;if (red4==0)lineflags&=~8;}
                        return;  
                };
      };
      }
  else{ // индикация в режиме Работа

      if ((ledstate&0x0f)!= 3){ //только что перешли в режим работа
         off1;  off2; off3; off4; 
         redw=0;
         grw=1; //зажгли зеленую;
         ledstate=3;
         settout(0,nt);
         return;
      }else {
         if ((SEND0!=0)||SEND1!=0){ //идет передача по модбасу
             redw=0; 
             if ((ledstate&0xf0)==0){//до этого передачи не было
                 grw=0;settout(0,nt);
                 ledstate=0x83;
             } else { //до этого уже был режим передачи 
                 if(gettout(0)!=0) goto lineled;
                 if (grw==0){// зеленая не горела слишком долго
                  grw=1;settout(0,200);//зажгли зеленую на 200мс
                  goto lineled;
                 }else { //тушим зеленую и взводим таймаут
                  grw=0; settout(0,nt);
                  goto lineled;
                 } 
             }  
         }else if ((ledstate&0xf0)==0){ //до этого передачи не было
                   grw=1; goto lineled;
               } else if (grw!=0){ //была передача но горел зеленый, значит до этого он слишком долго 
                                   //не горел. Остаемся в том же состоянии пока не истечет таймаут на зеленый
                         if (gettout(0)!=0) {goto lineled;}
                         else ledstate=3; // сбросили флаг отработки автомата индикации приема   
                      }else { //зеленый не горел - просто зажжем его и сбросим автомат
                          ledstate=3; grw=1;
                          goto lineled;
                      }                   
         
lineled:  // обработка индикации шлейфа
/*  
          if ((ramb[0x018]&1)!=0) { //неисправность шлейфа 1
              if ((time&1024)==0){gr1=1;red1=0;}
            else {gr1=0;red1=1;}
          }else if((hrem[0x160]!=0)||(hrem[0x161]!=0)) {gr1=0;red1=1;}//тревога шлейфа 
                else {gr1=1;red1=0;}; //шлейф в норме
                
          }
          if ((ramb[0x018]&2)!=0) { //неисправность шлейфа 2
              if ((time&1024)==0){gr2=1;red2=0;}
            else {gr2=0;red2=1;}
          }else if((hrem[0x162]!=0)||(hrem[0x163]!=0)) {gr2=0;red2=1;}//тревога шлейфа 
                else {gr2=1;red2=0;}; //шлейф в норме
           
          if ((ramb[0x018]&4)!=0) { //неисправность шлейфа 3
              if ((time&1024)==0){gr3=1;red3=0;}
            else {gr3=0;red3=1;}
          }else if((hrem[0x164]!=0)||(hrem[0x165]!=0)) {gr3=0;red3=1;}//тревога шлейфа 
                else {gr3=1;red3=0;}; //шлейф в норме
           
          if ((ramb[0x018]&8)!=0) { //неисправность шлейфа 4
              if ((time&1024)==0){gr4=1;red4=0;}
            else {gr4=0;red4=1;}
          }else if((hrem[0x166]!=0)||(hrem[0x167]!=0)) {gr4=0;red4=1;}//тревога шлейфа 
                else {gr4=1;red4=0;}; //шлейф в норме
*/
          
      //if((hrem[0x160]!=0)||(hrem[0x161]!=0)) {gr1=0;red1=1;}//тревога шлейфа 
              // else 
                 if (((ramb[0x018]&1)!=0)||((chmaskout&1)!=0) ){ //неисправность шлейфа 1
                      if ((time&1024)==0){gr1=1;red1=0;}
                      else {gr1=0;red1=1;};
             }//else {gr1=1;red1=0;}; //шлейф в норме
          

        if((hrem[0x162]!=0)||(hrem[0x163]!=0)) {gr2=0;red2=1;}//тревога шлейфа 
              else 
                  if (((ramb[0x018]&2)!=0)||((chmaskout&2)!=0) ){ //неисправность шлейфа 2
                       if ((time&1024)==0){gr2=1;red2=0;}
                       else {gr2=0;red2=1;}
                  }else {gr2=1;red2=0;}; //шлейф в норме
          
          if((hrem[0x164]!=0)||(hrem[0x165]!=0)) {gr3=0;red3=1;}//тревога шлейфа 
                else 
                   if (((ramb[0x018]&4)!=0)||((chmaskout&4)!=0) ){ //неисправность шлейфа 3
                        if ((time&1024)==0){gr3=1;red3=0;}
                        else {gr3=0;red3=1;}
                   }else {gr3=1;red3=0;}; //шлейф в норме
          
        //  if((hrem[0x166]!=0)||(hrem[0x167]!=0)) {gr1=0;red1=1;}//тревога шлейфа 
             //   else 
             //      if (((ramb[0x018]&8)!=0)||((chmaskout&8)!=0) ){ //неисправность шлейфа 4
                    //    if ((time&1024)==0){gr4=1;}//red4=0;}
                    //    else {gr4=0;}//red4=1;}
               //    }else {gr4=1;}//red4=0;}; //шлейф в норме
          


         }  
 }  
}
chtime(){
static int timeold=0;
int time2;
_ID
  time2=time;
_IE
if  (hrem[0x178]==0xffff) hrem[0x178]=0;
if (timeold<time2){
  if ((time2-timeold)>1) hrem[0x177]=time2-timeold;
  if (hrem[0x177]>hrem[0x178]) hrem[0x178]=hrem[0x177];
  }
timeold=time2;  
}
void resalarm(){
UINT adr,tmp;
if (ramb[0x0f]==0)return;
/*
adr=((ramb[0x0f]&0x0300)>>7)+((ramb[0x0f]&0x1f)>>4);
tmp=hrem[adr+0x160]&~(1<<(ramb[0x0f]&0x0f)-1);
setrg(adr+0x160,tmp);
tmp=hrem[adr+0x168]&~(1<<(ramb[0x0f]&0x0f)-1);
setrg(adr+0x168,tmp);
*/
adr=((ramb[0x0f]&0x0300)>>7)+(((ramb[0x0f]-1)&0x1f)>>4);
tmp=hrem[adr+0x160]&~(1<<((ramb[0x0f]-1)&0x0f));
setrg(adr+0x160,tmp);
tmp=hrem[adr+0x168]&~(1<<((ramb[0x0f]-1)&0x0f));
setrg(adr+0x168,tmp);
/*
addh(0x5555);
addh(ramb[0x0f]);
addh(adr);
addh(tmp);
*/

ramb[0x0f]=0;

};
//функция проверки работоспособности модбаса
#define maxcnt 10 //20c 
check_mb(){
static char cnt0=0,cnt1=0; //счетчики таймаутов на запросы
char mbstate_copy; //st0,st1;

_ID
 mbstate_copy=mbstate;
 mbstate=0;
// st0=u0.state;
// st1=u1.state;
 _IE 
 
  if (mbstate_copy&(1<<mbst0) ){// был запрос по мб
      cnt0=0;    
 }else  if (cnt0>maxcnt) {
   initmb0(b_speed,b_parity,b_addr);cnt0=0;
//   redon1;
//   hrem[0x176]=cnt0;
 }
 
 if (dev_ver_r==0){
     if (mbstate_copy&(1<<mbst1)){// был запрос по мб
      cnt1=0;    
     }else  if (cnt1>maxcnt) {
     initmb1(b_speed,b_parity,b_addr);cnt1=0;
//     redon2
//     hrem[0x177]=cnt1;
     }
 }
 if(gettout(5)==0){
  cnt0++;cnt1++; settout(5,1000); //red3^=1;
 }
 
 }
/*
getstack()
      { char * st; int i;
          st=(char*)hrem[0x10];
          for (i=1;i<0x80;i++){hrem[i+0x10]=*st; st--;}
      };    
*/
char firston;
main(){
         

__disable_interrupt();
WDTCR |= (1<<WDCE);
WDTCR |= (1<<WDP0) | (1<<WDP1) | (1<<WDP2);
__enable_interrupt();

iniports();
redonw 
//redon1 redon2 redon3 redon4;
inibase();
if (basechk()) dev_status|=1<<8;
//v_status|=1<<8;
initime();
inihist(0xa1,0xff);
__disable_interrupt();
WDTCR |= (1<<WDCE);
WDTCR |= (1<<WDP0) | (1<<WDP1) | (1<<WDP2);
__enable_interrupt();

/**************************/
 Init();
/**************************/


if(xk1==0) inicomm(); // при установленной перемычке инициируем связь 
                      //переменными по умолчанию.

DDRE_Bit2 =1; //бит управления печкой на вывод    
PORTE_Bit2 = 0; // отключили печку
initmb0(b_speed,b_parity,b_addr);
if (dev_ver_r==0) initmb1(b_speed,b_parity,b_addr);


__watchdog_reset();
//setrg(0x176,++hrem[0x176]);
if (dev_ver_heat==0) { //исполнение с печкой и датчиком температуры
//    addh(0x333);
    if(isempty(temp_id_adr)){
//          addh(0x444); 
          if (get_temp_id()!=0) {dev_status |=0x200;}//проблемы с получением ID датчика
          else setrg(0x174,-37*2);//setrg(0x174,-35*2);
    }
}             




delayloop(50);    
off4 off3 off2 off1 offw
qwerty=1900;//начальная продолжительность нагрева(2000-1900=100 мс)

if ((hrem[0x380]>>8)>3){qwerty=1900-200*((hrem[0x380]>>8)/3);}//корректировка начальной продолжительности нагрева в периоде в зависимости от скорости нарастания температуры
tmv=0;t5=1;
qwer:
settout(6,qwerty);firston=0;settout(7,2000);//задаем таймауты
for (;;){//int ii;

  __watchdog_reset();
  if(ramb[0x19]==0xffff){
    if(dev_status&0x8000)config_uLan();
    else { dev_status|=0x8000;lineflags=0;config_uLan();}
  }else {dev_status&=~0x8000; GetT();};

__watchdog_reset();
  if (res_fl!=0)for(;;); //отработка сброса
  if (u0.addr!=hrem[0x101]){//отложенная обработка установки адреса устройства
     setrg(0x101,u0.addr);
  } 
// for(ii=0;ii<100;ii++) __delay_cycles(15*1000);
//getstack();
//__watchdog_reset();
//mbdiagn();
  __watchdog_reset();
//chtime();

  check_mb();
  __watchdog_reset();
  ledpr();
   __watchdog_reset();
  wrblock();
  __watchdog_reset();
  resalarm();


if (((ramb[0x20]>>1)>=50)&&(t5==1)) {qwerty=700;t5=0;}
if (((ramb[0x20]>>1)>=60)&&(t5==1)) {qwerty=300;t5=0;}

if (tmv==0){t1=(ramb[0x20]>>1);t3=(hrem[0x380]>>8);}
if ((tmv==5)||(tmv==10)){t2=(ramb[0x20]>>1); t4=(hrem[0x380]>>8); if ((t2-t1)<-2){qwerty=2000;} if ((t4-t3)!=0){qwerty=qwerty-100*(t4-t3);t3=(hrem[0x380]>>8);}//Анализ положения двери
}
if (tmv==10){t2=(ramb[0x20]>>1);if ((t2-t1)>((hrem[0x380]>>8)/3)){qwerty=qwerty+100;}//уменьшаем продолжительность нагрева в периоде
if (((t2-t1)<((hrem[0x380]>>8)/3))&&((ramb[0x20]>>1)!=(hrem[0x380] & 0x00ff))&&((t2-t1)>-2)&&(((ramb[0x20]>>1)-1)!=(hrem[0x380] & 0x00ff))&&(((ramb[0x20]>>1)+1)!=(hrem[0x380] & 0x00ff))){t5=0;if(((hrem[0x380]>>8)/3)-(t2-t1)>1){qwerty=qwerty-200;} else {qwerty=qwerty-100;}}//увеличиваем продолжительность нагрева в периоде
if(qwerty<0){qwerty=0;}
tmv=0;}
gr1=1;
       if ((ramb[0x20]>>1) >= (hrem[0x380] & 0x00ff) ) {
       heaton; red1=0;gr1=1;firston=0;goto qwer;}//выключили печку
       else {
    if (!gettout(6)&&(!firston))  { heatoff;red1=1;gr1=1;}//включили, ШИМ
if (!gettout(7)){ firston=1;heaton; red1=0;gr1=1; tmv=tmv+1;  goto qwer;}      

  }     

}};


