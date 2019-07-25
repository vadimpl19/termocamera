#include "iom64.h"
#include "ina90.h"
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
init0(unsigned int speed,char par){
DDRE_Bit2=1; //установили бит управления передатчиком на вывод
UCSR0A=2; //установили бит  U2X
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
UCSR0C=((1<<1)|(1<<2));//УСТАНОВИЛИ 8БИТ ДАННЫХ И 1 СТОП

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
//const char[]=0x81,0x81
//ACCR=0;
  switch (speed){
    case 48:{
      TCCR0=0X87;
      UBRR0L=383-256; 
      UBRR0H = (unsigned char)(383>>8);
      UBRR0L = (unsigned char)383;
      break;
    }case 96:{
      TCCR0=0X87; 
      UBRR0H = 0;
      UBRR0L = 191;
      break;
    }case 192:{
      TCCR0=0X87; 
      UBRR0H = 0;
      UBRR0L = 95;
      break;
    }case 384:{
      TCCR0=0X87;
      UBRR0H = 0;
      UBRR0L = 47;    
      break;
    }
    case 576: {
      TCCR0=0X87; 
      UBRR0H = 0;
      UBRR0L = 31;
      break;
    }
    case 1152: {
      TCCR0=0X87; 
      UBRR0H = 0;
      UBRR0L = 15;
      break;
    }
    default: {
      TCCR0=0X87; // скорость по умолчанию 19200
      UBRR0H = 95;
      UBRR0L = 0;
   };                 
  };
//TIMSK=TIMSK|1; //РАЗРЕШИЛ ПРЕРЫВАНИЯ ПО ПЕРЕПОЛНЕНИЮ ТАЙМЕРА  
  TIMSK=1;
};

// Запуск таймера 0 на заданный таймаут
startt0(int toutc){
  TCNT0=toutc;
};
char t0;
//#pragma vector=17

//#pragma vector=0x0020
#pragma vector=TIMER0_OVF_vect
__interrupt void t0_isr()
{

//gron();
  t0++;
  t0=t0&0x7f;
  if(t0>100)gron();
  else groff();
};
char txfrm[255];

struct isr_cntx {
  char flag35;
  char state;
  char l;
  char t15;
  char addr;
  char rbuf[256];
  char rdy;
 } u0,u1;
enum tstates {sync,infc,insthi,instlo,inrghi,inrglo,incrc1,incrc2,inbody}  ;
#pragma vector=USART0_RXC_vect
__interrupt void rx0_isr()
{
char inb;

  inb=UDR0;
  if(TCNT0>u0.t15) {u0.state=0;}
  else TCNT0=0;
  switch (u0.state){   
  case sync: {//cостояние ожидания синхронизации и первого байта
       if (u0.flag35==0)return;
       u0.rbuf[0]=inb;
       if ((inb==u0.addr)|(inb==0)){u0.state=infc; return;};
       return;
  }
  case infc: { //cостояние ожидания кода функции
    if ((inb==3)|(inb==8)|(inb==16)){
        u0.state=insthi;
        u0.rbuf[1]=inb;
        return;
    }    
    u0.state=sync; return;
  }  
  case insthi: {// 
           u0.rbuf[2]=inb;
           u0.state=instlo;
           return;
  }         
  case instlo: {// 
           u0.rbuf[3]=inb;
           u0.state=inrghi;
           return;
  }         
  case inrghi: {// 
           u0.rbuf[4]=inb;
           u0.state=inrglo;
           return;
  }         
  case inrglo: {// 
           u0.rbuf[5]=inb;
           u0.state=incrc1;
           return;
  }         
  case incrc1: {// 
           u0.rbuf[6]=inb;
           u0.state=incrc2;
           return;
  }         
  case incrc2: {// 
           u0.rbuf[7]=inb;
           if (u0.rbuf[1]!=16){u0.rdy=1;UCSR0B&=~(1<<RXCIE0);return;}
           else {
            u0.l= ++u0.rbuf[7];
            u0.state=inbody;
            return;
           }
  };         
  case inbody:{
           return;  
  }         
  default: {
    u0.state=0;
  }
}
};
char len;
char *txf;

#pragma vector=USART0_UDRE_vect
__interrupt void tx0_isr()
{
 redon(); 
  if (len!=0){
    len=len-1;
    UDR0=*txf++;
//    redon();
  }
  else {
     //запрещаем прерывания от передатчика,
//     UCSR0B&=~(1<<5);
    UCSR0B&=~(1<<UDRIE0);
//   UCSR0B&=0xdf;
//     redoff();  
  }
 

 redoff(); 
};
#define    TXC0     6
#define    UDRE0    5
#define    FE0      4

char sendstart0(char *outbuf,char l){
  if (len!=0)return 1;//предидущая передача не завершена
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
char buf[30];
char * cp;
main(){
//char a;
init0(1152,none);
groff();
redoff();
_SEI();
TIFR=1;
for (;;){
//  asm("LDI R16,0\n out 05,r16\n");
//  cp=(char *)&hs; 
SEND0ON;   
len=0;
sendstart0((char *)&hs,12);
//USART_Transmit(0);
//  UDR0=0x55;
  delayloop(50);
SEND0OFF; 
  delayloop(1); 
  DDRB=0XFF;
//  a=TCNT0;
//  if (a<20)redon();
//  else  redoff();
//  _CLI();

//  a=TIFR;
//  if ((a&1)!=0)gron();
//  delayloop(2000);

}
};

