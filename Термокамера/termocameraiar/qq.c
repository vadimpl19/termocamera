#include "ina90.h"
#include "mbsl0.h"
#include "led.h"
#include "types.h" 
#include "base.h"
#include <iom128.h>
#define ENABLE_BIT_DEFINITIONS 1

/* USART0 Control and Status Register B - UCSR0B */
/*
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
#define    UCSZ01   2
#define    CSZ00   1

#define    TXC0     6
#define    UDRE0    5
#define    FE0      4

*/


//#define    SEND0ON    PORTE_Bit2=1
//#define    SEND0OFF   PORTE_Bit2=0
#define    SEND0ON    PORTA_Bit0=1;PORTC=PORTC|0X1; //gron1
#define    SEND0OFF   PORTA_Bit0=0;PORTC=PORTC&0Xfc;


struct isr_cntx u0;
extern UINT getcrc(UCHAR *puchMsg, UINT usDataLen);


unsigned char t25,t35,t45;
char len;
char *txf;


void initmb0(unsigned int speed,char par,char ad){
//DDRE_Bit2=1; //���������� ��� ���������� ������������ �� �����
DDRA_Bit0=1;
SEND0OFF;
 UCSR0A=2; //���������� ���  U2X
 UCSR0B = (1<<RXEN0)|(1<<TXEN0);
 UCSR0C=((1<<1)|(1<<2));//���������� 8��� ������ � 1 ����
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
/* ������� tccr0
 7 =1 - �� ����� PWM
 6,3 = 0 - ������� ����
 5,4 =0 - �� ������������ ����� ���������
 2,1,0 - ������������
*/
  switch (speed){
    case 48:{
      TCCR0=0X8f;// CTC ���� ������������ 1024;
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
      TCCR0=0X8f; // CTC ���� ������������ 1024;
      t45=OCR0=74;
      UBRR0H = 0;
      UBRR0L = 191;
      
      break;
    }case 192:{
      t25=82;
      t35=116;
      TCCR0=0X8E; // CTC ���� ������������ 256;
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
      TCCR0=0X8E; // �������� �� ��������� 19200
      UBRR0H = 149;
      UBRR0L = 0;
      OCR0=149;
   };                 
  };
  TIMSK|=2;//��������� ���������� �� COMP !!!!!!
  UCSR0B|=(1<<RXCIE0); //��������� ���������� �� ���������
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
enum tstates {sync,wait1,rx,senpr,senbody,senpost}  ;
#pragma vector=USART0_RXC_vect
__interrupt void rx0_isr() {
char b;
  redon3
  b=UDR0;
  if((u0.state==sync)||((UCSR0A&0x10)!=0)){TCNT0=0;u0.state=sync;goto erx;};//���� �������� �� ������������ ����� -���� ��� �  �������
//  if((u0.state==sync)){TCNT0=0;u0.state=sync;return;};//���� �������� �� ������������ ����� -���� ��� �  �������
  if (u0.state==wait1){
    u0.state=rx;
//    u0.rbuf[u0.l++]=UDR0;
    u0.rbuf[u0.l++]=b;
    TCNT0=0;
    TIFR_Bit1=1; //�������� ���� ���������� �� �������, ���� �� ���
    TIMSK_Bit1=1; //��������� ���������� �� �������
  }else  //�������� ��������� ������ ���� �����. ��� ��������� ���������� ���� �� ������
  if(TCNT0<t45){
//    TCNT0=0; u0.rbuf[u0.l++]=UDR0;}
   TCNT0=0; u0.rbuf[u0.l++]=b;}
  else   {TCNT0=0;u0.state=sync;u0.l=0;goto erx;}
erx:
 off3  
};   
///////////////////////////////////////////////////////////////////////////////////////////////////////
void sen0(char *outbuf,char l){
  __disable_interrupt();
  TCNT0=0;
  SEND0ON;   
  //OCR0=t35;
  OCR0=t35;
  u0.state=senpr;
  TIMSK_Bit1=1; //!!!! ��������� ���������� �� �������

  txf=outbuf;len=l;
  __enable_interrupt();

}
///////////////////////////////////////////////////////////////////////////////////////////////////
extern UCHAR maxc;
extern UINT  ramb[ramm];
char fc16handl0(){ //������� ��������� fc=16 ���������� 0 ��� Exeption
char i;
UINT rg;
  if ((u0.rbuf[4]!=0)|((u0.rbuf[5]*2)!=u0.rbuf[6])) return 3;//illegal data value
  rg=(u0.rbuf[2]<<8)+u0.rbuf[3];
  if ((rg+u0.rbuf[5])>rammax)   return 2;//illegal data address;
  if ((rg>eepromm)&&(rg<rammin))return 7;
  if (rg>=rammin){
    UINT * intp; 
    intp=&(ramb[rg-rammin]);//inp - ��������� �� ������� ������������ �������; 
    for(i=0;i<u0.rbuf[5];i++){ //������ � ���� ������ RAM
      __disable_interrupt();
      *intp=(u0.rbuf[7+i]<<8)+u0.rbuf[7+i+1];
      __enable_interrupt();
      rg++;
    }; 
    return 0; 
  }
  //��������� ������ � EEPROM
//  _clis
//  if (maxc!=0){SREG=sregt; return 6;};//slave device busy ��� ���� ��������� ������ � eeprom c �������
//  if 
   return wrblock_ini(rg,u0.rbuf[5],(UINT*)&(u0.rbuf[7]));
//  return 0;
}
char reinitu0(){
char b;
  u0.l=0;
  u0.state=wait1;
  b=UDR0;
  b=UDR0;
  b=UDR0;
  UCSR0B|=(1<<RXCIE0); //��������� ���������� �� ���������};
//  TIMSK_Bit1=0; //!!!! ������ ���������� �� �������
  return b;
}  
////////////////////////////////////////////////////////////////////////////////////////////////////
//���������� �� �������� exeption code
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
// ������� ���������� �������� �������� � �������� ������� � ���������� RG � 0 � ������ ��������� ����������
// � ������ ������������� ������ �������� ������� ���������� �xeption ��� �������� ������������
extern char getrg(UINT address,UINT * rg);
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma vector=TIMER0_COMP_vect
__interrupt void t0_comp_isr(){
unsigned char b;
UINT first,rg;
char *ptr;
  gronw
  UCSR0B&=~(1<<RXCIE0);//��������� ���������� �� ���������
  TIMSK_Bit1=0; //!!!! ��������� ���������� �� ������� OCIE0=0
  if (u0.state==sync){reinitu0();goto end_isr;}
  _SEI();//������� ���������� - ��������� ��������
  if (u0.state==rx){

   //��������� ������������ ��������� �����
//   b=u0.l;
      if ((u0.l<8)|(u0.addr!=u0.rbuf[0])){reinitu0();goto end_isr;};
 

   if(getcrc((UCHAR *)&u0.rbuf,u0.l)!=0){reinitu0();goto end_isr;};
   
      if (u0.rbuf[1]==3){//��������� �������� ������ �������-���������

//      if (u0.rbuf[0]==0)goto end_isr; //broadcast
              // ����� ��������
   	  first=u0.rbuf[2]<<8;
	  first += u0.rbuf[3];

          // ���������� ���������
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
     if (u0.rbuf[1]==16){//��������� ������� ������ ���������
        b=fc16handl0();
        if (b!=0) {sendexept0(b);goto end_isr;}
        else {
          u0.tbuf[0]=u0.addr;
	  u0.tbuf[1]=16;//fc
	  u0.tbuf[2]=u0.rbuf[2]; 
	  u0.tbuf[3]=u0.rbuf[3]; 
	  u0.tbuf[4]=u0.rbuf[4]; 
	  u0.tbuf[5]=u0.rbuf[5]; 
          {UINT crc;
             crc=getcrc((UCHAR *)&u0.tbuf,6);
             u0.tbuf[6]=crc >> 8;
             u0.tbuf[7]=crc & 0xFF;
          };
          sen0((char *)&u0.tbuf,8);
          goto end_isr;
        }
     }
     if (u0.rbuf[1]==8){
     //��������� ������� �����������
       sen0((char *)&u0.rbuf,u0.l);
       goto end_isr;
     }
     sendexept0(5);//ILLEGAL FUNCTION ������ ������� �� ��������������
     goto end_isr;
  };  
  if(u0.state==senpr){ // ���������� ���������
       u0.state=senbody;    
       UCSR0B|=(1<<UDRIE0)|(1<<TXEN0);  //������� ���������� (������ ��������)

//       delayloop(50); 
       goto end_isr;
       
//       return;
   }
   if(u0.state==senpost){ // ���������� ����������
       u0.state=1;    
       SEND0OFF;   
       reinitu0();  
//       return;
//       redon
          
       goto end_isr; 
   }
   u0.state=sync;
end_isr:;
//   redoff();   
 offw
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma vector=USART0_UDRE_vect
__interrupt void tx0_isr()
{

  if (len!=0){
    len=len-1;
    UDR0=*txf++;

  }
  else {
     //��������� ���������� �� �����������,
//     UCSR0B&=~(1<<5);
    UCSR0B&=~(1<<UDRIE0);
    u0.state=senpost;//��������� � ��������� �������� ����������.
//    OCR0=t35;
    OCR0=t35;
    TCNT0=0;
    TIFR_Bit1=1; //�������� ���� ���������� �� �������, ���� �� ���
    TIMSK_Bit1=1; //��������� ���������� �� �������

  }
 

// redoff(); 
};

char sendstart0(char *outbuf,char l){
    UCSR0A&=~(1<<TXC0);  
    UDR0=*outbuf++;
    len=--l;  
    txf=outbuf;
    UCSR0B|=(1<<UDRIE0)|(1<<TXEN0); 
    return 0;
};
