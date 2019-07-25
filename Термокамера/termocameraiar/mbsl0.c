#define mbslave0
#include "ina90.h"
#include "mbsl0.h"
#include "led.h"
#include "types.h" 
//#include "hist.h"
#include "base.h"
#include "zerodef.h"
#include <iom128.h>
//#define ENABLE_BIT_DEFINITIONS 1


struct isr_cntx u0;
#ifdef mbslave0
extern struct isr_cntx u1;
#else 
extern struct isr_cntx uZ;
#endif
extern UINT getcrc(UCHAR *puchMsg, UINT usDataLen);
char len0;
char *txf0;

enum tstates {sync,wait1,rx,senpr,senbody,senpost}  ;
void initmb0(unsigned int speed,char par,char ad){
_ID
//redon1
//DDRE_Bit2=1; //���������� ��� ���������� ������������ �� �����
txen0ini
SEND0OFF;
 UCSR0A=2; //���������� ���  U2X
 UCSR0B = (1<<RXEN0)|(1<<TXEN0);
 UCSR0C=((1<<1)|(1<<2));//���������� 8��� ������ � 1 ����
 u0.addr=ad;
 switch (par){
   case none:{ 
     UCSR0C&=~((1<<UPM01)|(1<<UPM0Z));
     break;
   };  
   case even:{ 
     UCSR0C|= 1<<UPM01;
     UCSR0C&=~(1<<UPM0Z);
     break;
   };  
   case odd:{ 
     UCSR0C|= 1<<UPM01;
     UCSR0C|=1<<UPM0Z;
     break;
   };  
 };
/* ������� tccr0
 7 =1 - �� ����� PWM
 6,3 = zero - ������� ����
 5,4 =zero - �� ������������ ����� ���������
 2,1,zero - ������������
*/
  switch (speed){
    case 48:{
      TCCR0CH=CTC124_0;// CTC ���� ������������ 1024;
      UBRR0L=383-256; 
      UBRR0H = (unsigned char)(383>>8);
      UBRR0L = (unsigned char)383;
      t25=83;
      t35=116;
      t45=OCR0T=148;
      
      break;
    }case 96:{
      t25=41;
      t35=58;
      TCCR0CH=CTC124_0; // CTC ���� ������������ 1024;
      t45=OCR0T=74;
      UBRR0H = zero;
      UBRR0L = 191;
      
      break;
    }case 192:{
      t25=82;
      t35=116;
      TCCR0CH=CTC256_0; // CTC ���� ������������ 256;
      UBRR0H = zero;
      UBRR0L = 95;
      t45=OCR0T=149;
      
      break;
    }case 384:{
      t25=41;
      t35=58;
      TCCR0CH=CTC256_0;
      UBRR0H = zero;
      UBRR0L = 47;    
      t45=OCR0T=74;
      break;
    }
    case 576: {
      t25=28; 
      t35=39;
      TCCR0CH=CTC256_0; 
      UBRR0H = zero;
      UBRR0L = 31;
      t45=OCR0T=49;
      break;
    }
    case 1152: {
//    t25=14;
//    t35=20;
      t25=41; 
      t35=58;

      TCCR0CH=CTC256_0; 
      UBRR0H = zero;
      UBRR0L = 15;
//      t45=OCR0T=24;
      t45=OCR0T=74;
      break;
    }
    default: {
      t25=82;    
      t35=116;
      TCCR0CH=CTC256_0; // �������� �� ��������� 19200
      UBRR0H = 149;
      UBRR0L = zero;
      t45=OCR0T=149;
   };                 
  };
//  u0.state=wait1;

  u0.state=sync;
  TCNT0CH=zero;
//  TIMSK|=2;
  OCIE0CH=1;//��������� ���������� �� �������  �� COMP !!!!!!
  UCSR0B|=(1<<RXCIE0); //��������� ���������� �� ���������
_IE  
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma vector=USART0_RXC_vect
__interrupt void rx0_isr() {

//red4^=1;
  if((u0.state==sync)){goto error_rx;};
  if (u0.state==wait1){

    TCNT0CH=zero;

//      OCF0CH=1;
//     TIFR=1<<OCF0CH; 
      TIFR=1<<CH0f; 
//    TIMSK_Bit1=1; //��������� ���������� �� �������
    OCIE0CH=1; 

    if((UCSR0A&((1<<FE0)|(1<<UPE0)))!=zero){goto error_rx;};//���� �������� �� ������������ ����� -���� ��� �  ������� /!!!!!!!
//    gron3;
    u0.state=rx;
    if (u0.l>(128+8))goto error_rx;
    u0.rbuf[u0.l++]=UDR0;
    //    u0.rbuf[u0.l++]=b;
    goto erx;     
  }else { //�������� ��������� ������ ���� �����. ��� ��������� ���������� ���� �� ������
//   gron3  
     if(TCNT0CH<t45){ 
//        if(((UCSR0A&16)!=zero)){goto error_rx;};//���� �������� �� ������������ ����� -���� ��� �  �������
          if((UCSR0A&((1<<FE0)|(1<<UPE0)))!=zero){goto error_rx;};//���� �������� �� ������������ ����� -���� ��� �  ������� /!!!!!!!
        TCNT0CH=zero; u0.rbuf[u0.l++]=UDR0; 
        goto erx;
    }
  }
  // ���� �� �� ��������� � �������� - ���������� ���� 
error_rx:  
  u0.l=zero; //����������  ����.

//  off3 ;redon3; 
//  {char b;     b=UDR0; }
  getrx0 
  TCNT0CH=zero;u0.state=sync; 
erx: 
// off3 
_NOP(); 
};   
///////////////////////////////////////////////////////////////////////////////////////////////////////
void sen0(char *outbuf,char l){
  __disable_interrupt();
  TCNT0CH=zero;
  SEND0ON;   
  //OCR0T=t35;
  OCR0T=t35;
  u0.state=senpr;
  OCIE0CH=1; //!!!! ��������� ���������� �� �������

  txf0=outbuf;len0=l;
  __enable_interrupt();

}
///////////////////////////////////////////////////////////////////////////////////////////////////
extern UCHAR maxc;
extern UINT  ramb[ramm];
char fc16handl0(){ //������� ��������� fc=16 ���������� zero ��� Exeption
char i;
UINT rg;
  rg=(u0.rbuf[2]<<8)+u0.rbuf[3];
  if (rg==0x777){reset_cpu();  return zero;}; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  if ((rg==0x778)&&(u0.rbuf[8]==0xaa)){wr_fl=1;  return zero;};//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  if ((u0.rbuf[4]!=zero)|((u0.rbuf[5]*2)!=u0.rbuf[6])) return 3;//illegal data value
//  rg=(u0.rbuf[2]<<8)+u0.rbuf[3];
  if ((rg+u0.rbuf[5])>rammax)   return 2;//illegal data address;
  
  if ((rg>eepromm)&&(rg<rammin))return 7;
  if (rg>=rammin){
    UINT * intp; 
    intp=&(ramb[rg-rammin]);//inp - ��������� �� ������� ������������ �������; 
    for(i=zero;i<u0.rbuf[5];i++){ //������ � ���� ������ RAM
      __disable_interrupt();
      *intp=(u0.rbuf[7+i]<<8)+u0.rbuf[7+i+1];
      __enable_interrupt();
      rg++;
    }; 
    return zero; 
  }
  if ((rg==1)||(rg==2))
     if(wr_fl==zero) {return 2;}//illegal data address; ;
        else {wr_fl=zero;   return wrblock_ini(rg,u0.rbuf[5],(UINT*)&(u0.rbuf[7]));}
     
  //��������� ������ � EEPROM
//  _clis
//  if (maxc!=zero){SREG=sregt; return 6;};//slave device busy ��� ���� ��������� ������ � eeprom c �������
//  if 
   return wrblock_ini(rg,u0.rbuf[5],(UINT*)&(u0.rbuf[7]));
//  return zero;
}
char reinitu0(){
char b;
  u0.l=zero;
  u0.state=wait1;
  b=UDR0;
  b=UDR0;
  b=UDR0;
  UCSR0B|=(1<<RXCIE0); //��������� ���������� �� ���������};
  return b;
}  
////////////////////////////////////////////////////////////////////////////////////////////////////
//���������� �� �������� exeption code
sendexept0(char ex){
UINT crc;
  u0.tbuf[zero]=u0.addr;
  u0.tbuf[1]=u0.rbuf[1]|C8Z;
  u0.tbuf[2]=ex;
  crc=getcrc((UCHAR *)&(u0.tbuf),3);
  u0.tbuf[3]=crc >> 8;
  u0.tbuf[4]=crc; //0xFF;
  sen0((char *)&u0.tbuf,5);
};
// ���� ����������� ��������� ����� (� ��������� ����� ������ ����������� �� ���������� � ��������� ������������
#define maxreg 64
void rec_frm_fork0(){
unsigned char b;
UINT first,rg;
char *ptr;
//      redon4
//   if(getcrc((UCHAR *)&u0.rbuf,u0.l)!=zero){reinitu0();goto end_isr;};
      if(getcrc((UCHAR *)&u0.rbuf,u0.l)!=zero){reinitu0();return;};
      //���� ������.������� ���� ���������� �������
      _ID;
    mbstate|=1<<mbst0;
      _IE;
      
      if (u0.rbuf[1]==3){//��������� �������� ������ �������-���������
              // ����� ��������
              
   	  first=u0.rbuf[2]<<8;
	  first += u0.rbuf[3];

          // ���������� ���������
	  if((u0.rbuf[5]>maxreg)|(u0.rbuf[4]!=zero)){sendexept0(3); return;};
	  u0.tbuf[zero]=u0.addr;
	  u0.tbuf[1]=3;//fc
	  u0.tbuf[2]=u0.rbuf[5]*2; //byte count;
	  ptr=&u0.tbuf[3];
	  {UINT i;
          for (i=first;i<first+u0.rbuf[5];i++){
          if ((b=getrg(i,&rg))!=zero){sendexept0(b); return;};  	
             *(ptr++)=rg>>8;
             *(ptr++)=rg&Cff;
          };  
          }
          {UINT crc;
             crc=getcrc((UCHAR *)&u0.tbuf,u0.tbuf[2]+3);
             *(ptr++)=crc >> 8;
             *(ptr++)=crc & Cff;
                        
          };
          sen0((char *)&u0.tbuf,u0.tbuf[2]+5);
          return;
     }
     if (u0.rbuf[1]==16){//��������� ������� ������ ���������
        b=fc16handl0();
        if (b!=zero) {sendexept0(b);return;}
        else {
          u0.tbuf[zero]=u0.addr;
	  u0.tbuf[1]=16;//fc
	  u0.tbuf[2]=u0.rbuf[2]; 
	  u0.tbuf[3]=u0.rbuf[3]; 
	  u0.tbuf[4]=u0.rbuf[4]; 
	  u0.tbuf[5]=u0.rbuf[5]; 
          {UINT crc;
             crc=getcrc((UCHAR *)&u0.tbuf,6);
             u0.tbuf[6]=crc >> 8;
             u0.tbuf[7]=crc & Cff;
          };
          sen0((char *)&u0.tbuf,8);
          return;
        }
     }
     if (u0.rbuf[1]==8){
     //��������� ������� �����������
       sen0((char *)&u0.rbuf,u0.l);
//       goto end_isr;
       return;
     }
     if (u0.rbuf[1]==255){//������� ��������� ������ ����������
         if ((u0.rbuf[2]!=12)||(u0.rbuf[3]!=zero)) return;
         if( reg_num!=( ((UINT)(u0.rbuf[5]<<8))|u0.rbuf[4] ) )return;
         _SETADDR=u0.rbuf[6];
          u0.rbuf[zero]=u0.addr;
          {UINT crc;
             crc=getcrc((UCHAR *)&u0.rbuf,7);
             u0.rbuf[7]=crc >> 8;
             u0.rbuf[8]=crc & Cff;
          };
          sen0((char *)&u0.rbuf,9);
/*          
          u0.tbuf[zero]=u0.addr;
	  u0.tbuf[1]=255;//fc
	  u0.tbuf[2]=u0.rbuf[2]; 
	  u0.tbuf[3]=u0.rbuf[3]; 
	  u0.tbuf[4]=u0.rbuf[4]; 
	  u0.tbuf[5]=u0.rbuf[5]; 
 	  u0.tbuf[6]=u0.rbuf[6]; 

          {UINT crc;
             crc=getcrc((UCHAR *)&u0.tbuf,7);
             u0.tbuf[7]=crc >> 8;
             u0.tbuf[8]=crc & Cff;
          };
          addh(0xaaaa);
          addh(u0.tbuf[1]);
          addh(u0.tbuf[2]);
          addh(u0.tbuf[3]);          
          addh(u0.tbuf[4]);          
          addh(u0.tbuf[5]);          
          addh(u0.tbuf[6]);          
          addh(u0.tbuf[7]);          
          addh(u0.tbuf[8]);          
          sen0((char *)&u0.tbuf,9);
*/          
          return;
     } 
     sendexept0(5);//ILLEGAL FUNCTION ������ ������� �� ��������������
};

// ������� ���������� �������� �������� � �������� ������� � ���������� RG � zero � ������ ��������� ����������
// � ������ ������������� ������ �������� ������� ���������� �xeption ��� �������� ������������
extern char getrg(UINT address,UINT * rg);
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma vector=TIMERch0_COMP_vect
__interrupt void tch0_comp_isr(){

  UCSR0B&=~(1<<RXCIE0);//��������� ���������� �� ���������
  OCIE0CH=zero; //!!!! ��������� ���������� �� ������� OCIE0=zero
 
  if (u0.state==sync){reinitu0();goto end_isr;}
//  _SEI();//������� ���������� - ��������� ��������
 // redon4
  if (u0.state==rx){
//  red4^=1;
//       redon4
   //��������� ������������ ��������� �����
//   b=u0.l;
//gron4
//      if ((u0.l<8)|(u0.addr!=u0.rbuf[zero])){reinitu0();goto end_isr;};
//      addh(0xaaab);
      if( (u0.l<8)|| !( (u0.addr==u0.rbuf[zero])||(u0.rbuf[zero]==zero) ) ){reinitu0();goto end_isr;};
// redon4
//     addh(0xaabb);
//      redw^=1;
     _SEI();//������� ���������� - ��������� ��������
      
     rec_frm_fork0(); 
//     off4
     goto end_isr;
  };  
  if(u0.state==senpr){ // ���������� ���������
       u0.state=senbody;    
       UCSR0B|=(1<<UDRIE0)|(1<<TXEN0);  //������� ���������� (������ ��������)

       goto end_isr;
       
//       return;
   }
   if(u0.state==senpost){ // ���������� ����������
       u0.state=1;    
       SEND0OFF;   
       reinitu0();  
//       return;
          
       goto end_isr; 
   }
   u0.state=sync;
end_isr:;
 _NOP();
// off1
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma vector=USART0_UDRE_vect
__interrupt void tx0_isr()
{

  if (len0!=zero){
    len0=len0-1;
    UDR0=*txf0++;

  }
  else {
     //��������� ���������� �� �����������,
//     UCSR0B&=~(1<<5);
    UCSR0B&=~(1<<UDRIE0);
    u0.state=senpost;//��������� � ��������� �������� ����������.
//    OCR0T=t35;
    OCR0T=t35;
    TCNT0CH=zero;
//    OCF0CH=1; //�������� ���� ���������� �� �������, ���� �� ���
//    TIFR=1<<OCF0CH;
        TIFR=1<<CH0f;
    OCIE0CH=1; //��������� ���������� �� �������

  }
 

// redoff(); 
};

char sendstart0(char *outbuf,char l){
    UCSR0A&=~(1<<TXC0);  
    UDR0=*outbuf++;
    len0=--l;  
    txf0=outbuf;
    UCSR0B|=(1<<UDRIE0)|(1<<TXEN0); 
    return zero;
};
