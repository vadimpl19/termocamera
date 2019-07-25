#include "iom64.h"
#include "ina90.h"
#include "string.h"
#include "stdio.h"
#define ENABLE_BIT_DEFINITIONS 1

/* USART0 Control and Status Register B - UCSR0B */
#define    RXCIE0   7
#define    TXCIE0   6
#define    UDRIE0   5
#define    RXEN0    4
#define    TXEN0    3
#define    UCSZ02   2
#define    RXB80    1
#define    TXB80    0


#define    UPM01    5
#define    UPM00    4



#define    SON    1
#define    SOFF   0
#define    SEND0ON    PORTE_Bit2=1
#define    SEND0OFF   PORTE_Bit2=0
typedef unsigned char UCHAR;
typedef unsigned int UINT;
extern UINT getcrc(UCHAR *puchMsg, UINT usDataLen);

void delayloop(unsigned int d){
unsigned int i,i2;
for (i=0;i<d;i++)
  for (i2=0;i2<1100;i2++) _NOP();
};
//                                                                                                    #pragma inline
//#pragma inline=forced
void redon(){
PORTB=PORTB&0X7f;
};
//#pragma inline = forced;
redoff(){
PORTB=PORTB|0X80;
}
gron(){
PORTB=PORTB&0Xbf;
};
groff(){
PORTB=PORTB|0X40;
};
enum tpar {none,even,odd};
#define    UCSZ01   2
#define    UCSZ00   1
unsigned char t25,t35,t45;
char len;
char *txf;

struct isr_cntx {
  char flag35;
  char state;
  unsigned char l;
//  char t15;
  char addr;
//  char rbuf[256];
  char rbuf[8];
  char tbuf[263];
//  char rdy;
 } u0,u1;
initmb(unsigned int speed,char par,char ad){
DDRE_Bit2=1; //установили бит управления передатчиком на вывод
UCSR0A=2; //установили бит  U2X
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
UCSR0C=((1<<1)|(1<<2));//УСТАНОВИЛИ 8БИТ ДАННЫХ И 1 СТОП
u0.addr=ad;
switch (par){
  case none:{ 
    UCSR0C&=~((1<<UPM01)|(1<<UPM00));
    break;
  };  
  case even:{ 
    UCSR0C|= 1<<UPM01;
    UCSR0C&=~(1<<UPM00);
    break;
  };  
  case odd:{ 
    UCSR0C|= 1<<UPM01;
    UCSR0C|=1<<UPM00;
    break;
  };  
};
/* регистр tccr0
 7 =1 - не нужен PWM
 6,3 = 0 - обычная мода
 5,4 =0 - не используется выход модуляции
 2,1,0 - предделитель
*/
  switch (speed){
    case 48:{
      TCCR0=0X8f;// CTC мода предделитель 1024;
      UBRR0L=383-256; 
      UBRR0H = (unsigned char)(383>>8);
      UBRR0L = (unsigned char)383;
      t25=83;
      t35=116;
      t45=OCR0=148;
      
      break;
    }case 96:{
      t25=41;
      t35=58;
      TCCR0=0X8f; // CTC мода предделитель 1024;
      t45=OCR0=74;
      UBRR0H = 0;
      UBRR0L = 191;
      
      break;
    }case 192:{
      t25=82;
      t35=116;
      TCCR0=0X8E; // CTC мода предделитель 256;
      UBRR0H = 0;
      UBRR0L = 95;
      t45=OCR0=149;
      
      break;
    }case 384:{
      t25=41;
      t35=58;
      TCCR0=0X8E;
      UBRR0H = 0;
      UBRR0L = 47;    
      t45=OCR0=74;
      break;
    }
    case 576: {
      t25=28; 
      t35=39;
      TCCR0=0X8E; 
      UBRR0H = 0;
      UBRR0L = 31;
      t45=OCR0=49;
      break;
    }
    case 1152: {
      t25=14;
      t35=20;
      TCCR0=0X8E; 
      UBRR0H = 0;
      UBRR0L = 15;
      t45=OCR0=24;
      break;
    }
    default: {
      t25=82;    
      t35=116;
      TCCR0=0X8E; // скорость по умолчанию 19200
      UBRR0H = 149;
      UBRR0L = 0;
      OCR0=149;
   };                 
  };
//TIMSK=TIMSK|1; //РАЗРЕШИЛ ПРЕРЫВАНИЯ ПО ПЕРЕПОЛНЕНИЮ ТАЙМЕРА  
  TIMSK|=2;//разрешили прерывание по COMP
  UCSR0B|=(1<<RXCIE0); //разрешили прерывания от приемника
};
char t0;
#pragma vector=TIMER0_OVF_vect
__interrupt void t0_isr()
{
  t0++;
  t0=t0&0x7f;
  if(t0>100)gron();
  else groff();
};
#define UPE=
enum tstates {sync,wait1,rx,senpr,senbody,senpost}  ;
#pragma vector=USART0_RXC_vect
__interrupt void rx0_isr() //33 команды
{
//char inb;

//  gron();
  
  if((u0.state==sync)||((UCSR0A&0x10)!=0)){TCNT0=0;u0.state=sync;return;};//была проверка на корректность кадра -стоп бит и  паритет
//  if((u0.state==sync)){TCNT0=0;u0.state=sync;return;};//была проверка на корректность кадра -стоп бит и  паритет
  if (u0.state==wait1){
  u0.state=rx;
  u0.rbuf[u0.l++]=UDR0;
  TCNT0=0;
  TIFR_Bit1=1; //сбросили флаг прерывания от таймера, если он был
  TIMSK_Bit1=1; //разрешили прерывания от таймера
  
    
  }
  else  //осталось состояние приема тела кадра. При остальных прерываний быть не должно
  if(TCNT0<t45){
    gron();
    TCNT0=0; u0.rbuf[u0.l++]=UDR0;}
  else   {TCNT0=0;u0.state=sync;u0.l=0;return;}
};   
#define    TXC0     6
#define    UDRE0    5
#define    FE0      4
sen0(char *outbuf,char l){
__disable_interrupt();
TCNT0=0;
SEND0ON;   
//OCR0=t35;
OCR0=t35;
u0.state=senpr;
TIMSK_Bit1=1; //!!!! разрешаем прерывания от таймера
txf=outbuf;len=l;
__enable_interrupt();
//redon();
}

reinitu0(){
char b;
  u0.l=0;
  u0.state=wait1;
  b=UDR0;
  b=UDR0;
  b=UDR0;
  UCSR0B|=(1<<RXCIE0); //разрешили прерывания от приемника};
//  TIMSK_Bit1=0; //!!!! разреш прерывания от таймера
}  
//постановка на передачу 
sendexept0(char ex){
UINT crc;
  u0.tbuf[0]=u0.addr;
  u0.tbuf[1]=u0.rbuf[1]|0x80;
  u0.tbuf[2]=ex;
  crc=getcrc((UCHAR *)&(u0.tbuf),3);
  u0.tbuf[3]=crc >> 8;
  u0.tbuf[4]=crc & 0xFF;
  sen0((char *)&u0.tbuf,5);
};
// функция возвращает значение регистра с заданным адресом в переменной RG и 0 в случае успешного завершения
// в случае невозможности чтения регистра функция возвращает еxeption для отправки пользователю
char getrg(UINT address,UINT * rg){
*rg=4;
return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma vector=TIMER0_COMP_vect
__interrupt void t0_comp_isr(){
unsigned char b;
UINT first,rg;
char *ptr;


//  redon(); 
//  delayloop(1);
//  redoff();
//  return;
  UCSR0B&=~(1<<RXCIE0);//запрещаем прерывания от приемника
  TIMSK_Bit1=0; //!!!! запрещаем прерывания от таймера
  if (u0.state==sync){reinitu0();goto end_isr;}
  _SEI();//открыли прерывания - остальное работает
  if (u0.state==rx){
     groff();
//  redon();
   //проверяем корректность принятого кадра
//   b=u0.l;
      if ((u0.l<8)|(u0.addr!=u0.rbuf[0])){reinitu0();goto end_isr;};
  
//   if (u0.l==8)redon();
   if(getcrc((UCHAR *)&u0.rbuf,u0.l)!=0){reinitu0();goto end_isr;};
   
      if (u0.rbuf[1]==3){//обработка фукнкции чтения холдинг-регистров
//   redon();
//      if (u0.rbuf[0]==0)goto end_isr; //broadcast
              // адрес регистра
   	  first=u0.rbuf[2]<<8;
	  first <<= 8;
	  first += u0.rbuf[3];

          // количество регистров
	  if((u0.rbuf[5]>127)|(u0.rbuf[4]!=0)){sendexept0(3); goto end_isr;};
	  u0.tbuf[0]=u0.addr;
	  u0.tbuf[1]=3;//fc
	  u0.tbuf[2]=u0.rbuf[5]*2; //byte count;
	  ptr=&u0.tbuf[3];
	  {UINT i;
          for (i=first;i<first+u0.rbuf[5];i++){
             if ((b=getrg(i,&rg))!=0){sendexept0(b); goto end_isr;};  	
             *(ptr++)=rg>>8;
             *(ptr++)=rg&0xff;
          };  
          }
          {UINT crc;
             crc=getcrc((UCHAR *)&u0.tbuf,u0.tbuf[2]+3);
             *(ptr++)=crc >> 8;
             *(ptr++)=crc & 0xFF;
                        
          };
          sen0((char *)&u0.tbuf,u0.tbuf[2]+5);
          goto end_isr;
     }
     if (u0.rbuf[1]==8){
     //обработка функции диагностики
       sen0((char *)&u0.rbuf,u0.l);
       goto end_isr;
     }
  };  
  if(u0.state==senpr){ // передавали преамбулу
       u0.state=senbody;    
       UCSR0B|=(1<<UDRIE0)|(1<<TXEN0);  //открыли прерывания (таймер запрещен)
//       redon();
//       delayloop(50); 
       goto end_isr;
       
//       return;
   }
   if(u0.state==senpost){ // передавали постамбулу
       u0.state=1;    
       SEND0OFF;   
       reinitu0();  
//       return;
       redon();
          
       goto end_isr; 
   }
   u0.state=sync;
end_isr:;
//   redoff();   
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma vector=USART0_UDRE_vect
__interrupt void tx0_isr()
{
// redon(); 
  if (len!=0){
    len=len-1;
    UDR0=*txf++;
//    redon();
  }
  else {
     //запрещаем прерывания от передатчика,
//     UCSR0B&=~(1<<5);
    UCSR0B&=~(1<<UDRIE0);
    u0.state=senpost;//переходим в состояние передачи постамбулы.
//    OCR0=t35;
    OCR0=t35;
    TCNT0=0;
    TIFR_Bit1=1; //сбросили флаг прерывания от таймера, если он был
    TIMSK_Bit1=1; //разрешили прерывания от таймера
//    redon();
  }
 

// redoff(); 
};

char sendstart0(char *outbuf,char l){
    
    
//  if (len!=0)return 1;//предидущая передача не завершена
    UCSR0A&=~(1<<TXC0);  
//    outbuf++;
    UDR0=*outbuf++;
//    UDR0='W';
    len=--l;  
//    len--; 
    txf=outbuf;
//    UCSR0B|=(1<<5)|(1<<3);
    UCSR0B|=(1<<UDRIE0)|(1<<TXEN0); 
    return 0;
};
const char hs[]="Hey stupid\n\r";
char buf[255];
char * cp;
char getx(char c){
switch (c){
case 0: return '0';
case 1: return '1';
case 2: return '2';
case 3: return '3';
case 4: return '4';
case 5: return '5';
case 6: return '6';
case 7: return '7';
case 8: return '8';
case 9: return '9';
case 10: return 'A';
case 11: return 'B';
case 12: return 'C';
case 13: return 'D';
case 14: return 'E';
case 15: return 'F';
}
return 0;
};

sendump(char * d, char len){
char i;
buf[0]=0x0d;
buf[1]=0x0a;
buf[2]='L';
buf[3]='=';
buf[4]='0';
buf[4]=getx(len>>4);
buf[5]=getx(len&0xf);
buf[6]=' ';
for(i=0;i<len;i++) {
  buf[7+i*3]=getx(*d>>4);
  buf[8+i*3]=getx(*d&0x0f);
  buf[9+i*3]=',';
  d++;
};
sen0((char *)&buf,len*3+7);
};
main(){
//char a;
initmb(48,even,1);
groff();
redoff();
_SEI();
TIFR=1;
for (;;){
//  asm("LDI R16,0\n out 05,r16\n");
//  cp=(char *)&hs; 
//SEND0ON;   
//len=0;
//sendstart0((char *)&hs,12);
//USART_Transmit(0);
//  UDR0=0x55;
  delayloop(2000);
//SEND0OFF; 
  delayloop(1); 
  buf[0]=0x0d;
  buf[1]=0x0a;
  buf[2]='l';
  buf[2]='l';
//  u0.l=0;
 {int i1,i2,i3,i4,i5,i6,i7,i8,i9;
  i1=u0.rbuf[0]; 
  i2=u0.rbuf[1];
  i3=u0.rbuf[2];
  i4=u0.rbuf[3];
  i5=u0.rbuf[4];
  i6=u0.rbuf[5];
  i7=u0.rbuf[6];
  i8=u0.rbuf[7];
  i9=u0.tbuf[0];
//i1=u0.rbuf[1];
//sprintf((char *)buf,"\n\r l= %x  ",i1,i2,i3,i4,i5,i6,i7,i8,i9);
//sen0(buf,strlen(buf));
  
// sendump(u0.tbuf,12);
 delayloop(500);
 i1=getcrc((UCHAR *)&(u0.tbuf),5);
// sendump((char *)&i1,2);
  delayloop(500);
 i1=getcrc((UCHAR *)&(u0.tbuf),7);
// sendump((char *)&i1,2);

 }
  DDRB=0XFF;


}
};

