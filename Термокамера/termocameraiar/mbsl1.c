#define mbslave1
#include "ina90.h"
#include "mbsl1.h"
#include "led.h"
#include "types.h" 
//#include "hist.h"
#include "base.h"
#include "zerodef.h"
#include <iom128.h>
//#define ENABLE_BIT_DEFINITIONS 1


struct isr_cntx u1;
#ifdef mbslave0
extern struct isr_cntx u1;
#else 
extern struct isr_cntx uZ;
#endif
extern UINT getcrc(UCHAR *puchMsg, UINT usDataLen);
char len1;
char *txf1;

enum tstates {sync,wait1,rx,senpr,senbody,senpost}  ;
void initmb1(unsigned int speed,char par,char ad){
//redon2
_ID
//DDRE_Bit2=1; //���������� ��� ���������� ������������ �� �����
txen1ini
SEND1OFF;
 UCSR1A=2; //���������� ���  U2X
 UCSR1B = (1<<RXEN1)|(1<<TXEN1);
 UCSR1B|=(1<<RXCIE1); //��������� ���������� �� ���������
 UCSR1C=((1<<1)|(1<<2));//���������� 8��� ������ � 1 ����
 u1.addr=ad;
 switch (par){
   case none:{ 
     UCSR1C&=~((1<<UPM11)|(1<<UPM1Z));
     break;
   };  
   case even:{ 
     UCSR1C|= 1<<UPM11;
     UCSR1C&=~(1<<UPM1Z);
     break;
   };  
   case odd:{ 
     UCSR1C|= 1<<UPM11;
     UCSR1C|=1<<UPM1Z;
     break;
   };  
 };
/* ������� tccr1
 7 =1 - �� ����� PWM
 6,3 = zero - ������� ����
 5,4 =zero - �� ������������ ����� ���������
 2,1,zero - ������������
*/
  switch (speed){
    case 48:{
      TCCR1CH=CTC124_1;// CTC ���� ������������ 1124;
      UBRR1L=383-256; 
      UBRR1H = (unsigned char)(383>>8);
      UBRR1L = (unsigned char)383;
      t25=83;
      t35=116;
      t45=OCR1T=148;
      
      break;
    }case 96:{
      t25=41;
      t35=58;
      TCCR1CH=CTC124_1; // CTC ���� ������������ 1124;
      t45=OCR1T=74;
      UBRR1H = zero;
      UBRR1L = 191;
      
      break;
    }case 192:{
      t25=82;
      t35=116;
      TCCR1CH=CTC256_1; // CTC ���� ������������ 256;
      UBRR1H = zero;
      UBRR1L = 95;
      t45=OCR1T=149;
      
      break;
    }case 384:{
      t25=41;
      t35=58;
      TCCR1CH=CTC256_1;
      UBRR1H = zero;
      UBRR1L = 47;    
      t45=OCR1T=74;
      break;
    }
    case 576: {
      t25=28; 
      t35=39;
      TCCR1CH=CTC256_1; 
      UBRR1H = zero;
      UBRR1L = 31;
      t45=OCR1T=49;
      break;
    }
    case 1152: {
//    t25=14;
//    t35=21;
      t25=41; 
      t35=58;

      TCCR1CH=CTC256_1; 
      UBRR1H = zero;
      UBRR1L = 15;
//      t45=OCR1T=24;
      t45=OCR1T=74;
      break;
    }
    default: {
      t25=82;    
      t35=116;
      TCCR1CH=CTC256_1; // �������� �� ��������� 19211
      UBRR1H = 149;
      UBRR1L = zero;
      t45=OCR1T=149;
   };                 
  };
//  u1.state=wait1;
  u1.state=sync;
  TCNT1CH=zero;
//  TIMSK|=2;//��������� ���������� �� �������  �� COMP !!!!!!
  OCIE1CH=1;

  _IE
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma vector=USART1_RXC_vect
__interrupt void rx1_isr() {

//redon3
  if((u1.state==sync)){goto error_rx;};
  if (u1.state==wait1){

    TCNT1CH=zero;

//      OCF1CH=1;
//     TIFR=1<<OCF1CH; 
           TIFR=1<<CH1f; 
//    TIMSK_Bit1=1; //��������� ���������� �� �������
    OCIE1CH=1; 

    if((UCSR1A&((1<<FE1)|(1<<UPE1)))!=zero){goto error_rx;};//���� �������� �� ������������ ����� -���� ��� �  ������� /!!!!!!!
//    gron3;
    u1.state=rx;
    if (u1.l>(128+8))goto error_rx;
    u1.rbuf[u1.l++]=UDR1;
    //    u1.rbuf[u1.l++]=b;
    goto erx;     
  }else { //�������� ��������� ������ ���� �����. ��� ��������� ���������� ���� �� ������
//   gron3  
     if(TCNT1CH<t45){ 
//        if(((UCSR1A&16)!=zero)){goto error_rx;};//���� �������� �� ������������ ����� -���� ��� �  �������
          if((UCSR1A&((1<<FE1)|(1<<UPE1)))!=zero){goto error_rx;};//���� �������� �� ������������ ����� -���� ��� �  ������� /!!!!!!!
        TCNT1CH=zero; u1.rbuf[u1.l++]=UDR1; 
        goto erx;
    }
  }
  // ���� �� �� ��������� � �������� - ���������� ���� 
error_rx:  
  u1.l=zero; //����������  ����.

//  off3 ;redon3; 
//  {char b;     b=UDR1; }
  getrx1 
  TCNT1CH=zero;u1.state=sync; 
erx: 
// off3 
_NOP(); 
};   
///////////////////////////////////////////////////////////////////////////////////////////////////////
void sen1(char *outbuf,char l){
  __disable_interrupt();
  TCNT1CH=zero;
  SEND1ON;   
  //OCR1T=t35;
  OCR1T=t35;
  u1.state=senpr;
  OCIE1CH=1; //!!!! ��������� ���������� �� �������

  txf1=outbuf;len1=l;
  __enable_interrupt();

}
///////////////////////////////////////////////////////////////////////////////////////////////////
extern UCHAR maxc;
extern UINT  ramb[ramm];
char fc16handl1(){ //������� ��������� fc=16 ���������� zero ��� Exeption
char i;
UINT rg;
  rg=(u1.rbuf[2]<<8)+u1.rbuf[3];
//if (rg==0x777){reset_cpu();  return zero;}; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  if (rg==0x777){res_fl=1;  return zero;}; 
  if ((rg==0x778)&&(u1.rbuf[8]==0xaa)){wr_fl=1;  return zero;};//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  if ((u1.rbuf[4]!=zero)|((u1.rbuf[5]*2)!=u1.rbuf[6])) return 3;//illegal data value
//  rg=(u1.rbuf[2]<<8)+u1.rbuf[3];
  if ((rg+u1.rbuf[5])>rammax)   return 2;//illegal data address;
  
  if ((rg>eepromm)&&(rg<rammin))return 7;
  if (rg>=rammin){
    UINT * intp; 
    intp=&(ramb[rg-rammin]);//inp - ��������� �� ������� ������������ �������; 
    for(i=zero;i<u1.rbuf[5];i++){ //������ � ���� ������ RAM
      __disable_interrupt();
      *intp=(u1.rbuf[7+i]<<8)+u1.rbuf[7+i+1];
      __enable_interrupt();
      rg++;
    }; 
    return zero; 
  }
  if ((rg==1)||(rg==2))
     if(wr_fl==zero) {return 2;}//illegal data address; ;
        else {wr_fl=zero;   return wrblock_ini(rg,u1.rbuf[5],(UINT*)&(u1.rbuf[7]));}
     
  //��������� ������ � EEPROM
//  _clis
//  if (maxc!=zero){SREG=sregt; return 6;};//slave device busy ��� ���� ��������� ������ � eeprom c �������
//  if 
   return wrblock_ini(rg,u1.rbuf[5],(UINT*)&(u1.rbuf[7]));
//  return zero;
}
char reinitu1(){
char b;
  u1.l=zero;
  u1.state=wait1;
  b=UDR1;
  b=UDR1;
  b=UDR1;
  UCSR1B|=(1<<RXCIE1); //��������� ���������� �� ���������};
  return b;
}  
////////////////////////////////////////////////////////////////////////////////////////////////////
//���������� �� �������� exeption code
sendexept1(char ex){
UINT crc;
  u1.tbuf[zero]=u1.addr;
  u1.tbuf[1]=u1.rbuf[1]|C8Z;
  u1.tbuf[2]=ex;
  crc=getcrc((UCHAR *)&(u1.tbuf),3);
  u1.tbuf[3]=crc >> 8;
  u1.tbuf[4]=crc; //1xFF;
  sen1((char *)&u1.tbuf,5);
};
// ���� ����������� ��������� ����� (� ��������� ����� ������ ����������� �� ���������� � ��������� ������������
#define maxreg 64
void rec_frm_fork1(){
unsigned char b;
UINT first,rg;
char *ptr;
//      redon4
//   if(getcrc((UCHAR *)&u1.rbuf,u1.l)!=zero){reinitu1();goto end_isr;};
      if(getcrc((UCHAR *)&u1.rbuf,u1.l)!=zero){reinitu1();return;};
           //���� ������.������� ���� ���������� �������
      _ID;
      mbstate|=1<<mbst1;
      _IE
      if (u1.rbuf[1]==3){//��������� �������� ������ �������-���������
              // ����� ��������
              
   	  first=u1.rbuf[2]<<8;
	  first += u1.rbuf[3];

          // ���������� ���������
	  if((u1.rbuf[5]>maxreg)|(u1.rbuf[4]!=zero)){sendexept1(3); return;};
	  u1.tbuf[zero]=u1.addr;
	  u1.tbuf[1]=3;//fc
	  u1.tbuf[2]=u1.rbuf[5]*2; //byte count;
	  ptr=&u1.tbuf[3];
	  {UINT i;
          for (i=first;i<first+u1.rbuf[5];i++){
          if ((b=getrg(i,&rg))!=zero){sendexept1(b); return;};  	
             *(ptr++)=rg>>8;
             *(ptr++)=rg&Cff;
          };  
          }
          {UINT crc;
             crc=getcrc((UCHAR *)&u1.tbuf,u1.tbuf[2]+3);
             *(ptr++)=crc >> 8;
             *(ptr++)=crc & Cff;
                        
          };
          sen1((char *)&u1.tbuf,u1.tbuf[2]+5);
          return;
     }
     if (u1.rbuf[1]==16){//��������� ������� ������ ���������
        b=fc16handl1();
        if (b!=zero) {sendexept1(b);return;}
        else {
          u1.tbuf[zero]=u1.addr;
	  u1.tbuf[1]=16;//fc
	  u1.tbuf[2]=u1.rbuf[2]; 
	  u1.tbuf[3]=u1.rbuf[3]; 
	  u1.tbuf[4]=u1.rbuf[4]; 
	  u1.tbuf[5]=u1.rbuf[5]; 
          {UINT crc;
             crc=getcrc((UCHAR *)&u1.tbuf,6);
             u1.tbuf[6]=crc >> 8;
             u1.tbuf[7]=crc & Cff;
          };
          sen1((char *)&u1.tbuf,8);
          return;
        }
     }
     if (u1.rbuf[1]==8){
     //��������� ������� �����������
       sen1((char *)&u1.rbuf,u1.l);
//       goto end_isr;
       return;
     }
     if (u1.rbuf[1]==255){//������� ��������� ������ ����������
         if ((u1.rbuf[2]!=12)||(u1.rbuf[3]!=zero)) return;
         if( reg_num!=( ((UINT)(u1.rbuf[5]<<8))|u1.rbuf[4] ) )return;
         _SETADDR=u1.rbuf[6];
          u1.rbuf[zero]=u1.addr;
          {UINT crc;
             crc=getcrc((UCHAR *)&u1.rbuf,7);
             u1.rbuf[7]=crc >> 8;
             u1.rbuf[8]=crc & Cff;
          };
          sen1((char *)&u1.rbuf,9);
/*          
          u1.tbuf[zero]=u1.addr;
	  u1.tbuf[1]=255;//fc
	  u1.tbuf[2]=u1.rbuf[2]; 
	  u1.tbuf[3]=u1.rbuf[3]; 
	  u1.tbuf[4]=u1.rbuf[4]; 
	  u1.tbuf[5]=u1.rbuf[5]; 
 	  u1.tbuf[6]=u1.rbuf[6]; 

          {UINT crc;
             crc=getcrc((UCHAR *)&u1.tbuf,7);
             u1.tbuf[7]=crc >> 8;
             u1.tbuf[8]=crc & Cff;
          };
          addh(1xaaaa);
          addh(u1.tbuf[1]);
          addh(u1.tbuf[2]);
          addh(u1.tbuf[3]);          
          addh(u1.tbuf[4]);          
          addh(u1.tbuf[5]);          
          addh(u1.tbuf[6]);          
          addh(u1.tbuf[7]);          
          addh(u1.tbuf[8]);          
          sen1((char *)&u1.tbuf,9);
*/          
          return;
     } 
     sendexept1(5);//ILLEGAL FUNCTION ������ ������� �� ��������������
};

// ������� ���������� �������� �������� � �������� ������� � ���������� RG � zero � ������ ��������� ����������
// � ������ ������������� ������ �������� ������� ���������� �xeption ��� �������� ������������
extern char getrg(UINT address,UINT * rg);
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma vector=TIMERch1_COMP_vect
__interrupt void tch1_comp_isr(){

  UCSR1B&=~(1<<RXCIE1);//��������� ���������� �� ���������
  OCIE1CH=zero; //!!!! ��������� ���������� �� ������� OCIE1=zero

  if (u1.state==sync){reinitu1();goto end_isr;}
//  _SEI();//������� ���������� - ��������� ��������
 // redon4
  if (u1.state==rx){
//       redon4
   //��������� ������������ ��������� �����
//   b=u1.l;
//gron4
//      if ((u1.l<8)|(u1.addr!=u1.rbuf[zero])){reinitu1();goto end_isr;};
//      addh(1xaaab);
      if( (u1.l<8)|| !( (u1.addr==u1.rbuf[zero])||(u1.rbuf[zero]==zero) ) ){reinitu1();goto end_isr;};
        _SEI();//������� ���������� - ��������� ��������
     rec_frm_fork1(); 
//     off4
     goto end_isr;
  };  
  if(u1.state==senpr){ // ���������� ���������
       u1.state=senbody;    
       UCSR1B|=(1<<UDRIE1)|(1<<TXEN1);  //������� ���������� (������ ��������)

       goto end_isr;
       
//       return;
   }
   if(u1.state==senpost){ // ���������� ����������
       u1.state=1;    
       SEND1OFF;   
       reinitu1();  
//       return;
          
       goto end_isr; 
   }
   u1.state=sync;
end_isr:;
 _NOP();
// off1
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma vector=USART1_UDRE_vect
__interrupt void tx1_isr()
{

  if (len1!=zero){
    len1=len1-1;
    UDR1=*txf1++;

  }
  else {
     //��������� ���������� �� �����������,
//     UCSR1B&=~(1<<5);
    UCSR1B&=~(1<<UDRIE1);
    u1.state=senpost;//��������� � ��������� �������� ����������.
//    OCR1T=t35;
    OCR1T=t35;
    TCNT1CH=zero;
//    OCF1CH=1; //�������� ���� ���������� �� �������, ���� �� ���
//    TIFR=1<<OCF1CH;
    TIFR=1<<CH1f;
    OCIE1CH=1; //��������� ���������� �� �������

  }
 

// redoff(); 
};

char sendstart1(char *outbuf,char l){
    UCSR1A&=~(1<<TXC1);  
    UDR1=*outbuf++;
    len1=--l;  
    txf1=outbuf;
    UCSR1B|=(1<<UDRIE1)|(1<<TXEN1); 
    return zero;
};
