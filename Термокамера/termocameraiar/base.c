#define base

#include "types.h"
#include "iom128.h"
#include "ina90.h"
#include "base.h"
//#include "led.h"

#define dev_id 12
#define ver 1
#define subver 3
//#define eepromm 0x10

#define wre(address,rg)     *(( unsigned int __eeprom *)(address*2))=rg;
#define wrem(address,rg)     *(( unsigned int __eeprom *)(address*2+eepromm*2))=rg;
#define rde(address,rg)     rg=*(( unsigned int __eeprom *)(address*2));
#define rdem(address,rg)    rg=*(( unsigned int __eeprom *)(address*2+eepromm*2));
#define rde2(address,rg1,rg2)    rg2=*(( unsigned int __eeprom *)(address*2+eepromm*2)); rg1=*(( unsigned int __eeprom *)(address*2));

/*
#define wre(address,rg)     *(( unsigned int __eeprom *)(address))=rg;
#define wrem(address,rg)     *(( unsigned int __eeprom *)(address+eepromm))=rg;
#define rde(address,rg)     rg=*(( unsigned int __eeprom *)(address));
#define rdem(address,rg)    rg=*(( unsigned int __eeprom *)(address+eepromm));
#define rde2(address,rg1,rg2)    rg2=*(( unsigned int __eeprom *)(address+eepromm)); rg1=*(( unsigned int __eeprom *)(address));
*/
//#define _clis sregt=SREG; __disable_interrupt(); �������� � types.h

UINT  hrem[eepromm];
UINT  ramb[ramm];
char getrg(UINT address,UINT * rg){
//unsigned int __eeprom  *pe;
char sregt;
  if ((address<=rammax)&(address>=rammin)) {
   *rg=ramb[address-rammin];
   return 0;
  }
  if (address< eepromm){
  // ���������� �������� �� eeprom
     _clis
//      *rg=*(( unsigned int __eeprom *)(address*2));
     *rg=hrem[address];
     SREG=sregt;
     return 0;
  };
  if ((address>= eepromm)&(address<= eepromm+0x0f)){
     _clis
//      *rg=*(( unsigned int __eeprom *)(address*2));
     *rg=hrem[address-0xa0];
     SREG=sregt;
     return 0;
  }

return 2;
};
//������� setch ������ �� ������ 1���� �� ����������� ������. � ������, ���� ���������� ������ �����������,
//�������������� �������� ���������� 
//#define setch(absad,ch) *(char __eeprom *)absad=ch
setch(int absad,char ch){

//addh(absad);
//addh(ch);
  while(EECR & (1<<EEWE));    /* Wait for completion of previous write */
__disable_interrupt();
/* Set up address and data registers */
EEAR = absad;
EEDR = ch;
/* Write logical one to EEMWE */
EECR |= (1<<EEMWE);
/* Start eeprom write by setting EEWE */
EECR |= (1<<EEWE);   
__enable_interrupt();
//  while(EECR & (1<<EEWE));    
}

UINT rgadt,tmpb[127];
UCHAR cnt,state,maxc;
//������� ������ ���������� ����� �� ����� ���������. ���� ���������� ������ �� ���������- �� �������
void wrblock(){
char sregt,ch;
UINT absad;
//  gron;
  if(maxc==0) return; //����� ���� ������ ������

//  if((EECR & (1<<EEWE))!=0)return; //�����, ���� ������
  if((EECR & 1)!=0){ return;} //�����, ���� ������
  //��������� ����� � ���� ��� ������
  switch (state){
  case 0: //������ �� ������ ������� ���� � �������� �������
      absad=rgadt*2;
      ch=tmpb[cnt]&0xff;
      break;
  case 1: //������ �� ������ ������� ���� � �������� �������
      absad=rgadt*2+1;
      ch=tmpb[cnt]>>8;
      break;
  case 2: //������ �� ������ ������� ���� � ������� �������
      absad=rgadt*2+eepromm*2;
      ch=tmpb[cnt];
      break;
  case 3: //������ �� ������ ������� ���� � ������� �������
      absad=rgadt*2+1+eepromm*2;
      ch=tmpb[cnt]>>8;
      break;
  default: //��������� ���������!!!
      state=0;
      absad=rgadt*2;
      ch=tmpb[cnt]&0xff;
  };
  
  if((EECR & (1<<EEWE))!=0){return;}; //�����, ���� ������
//  if((EECR & 1)!=0){SREG=sregt;return;} 
setch(absad,ch);  

  
  state++;
  if (state==4){//��������� ������� ������� ��������� � eeprom
    _clis
    hrem[rgadt]=tmpb[cnt];//�������� �������� � � ������� RAM- �����.
//�������
//    hrem[0]=rgadt;
//    hrem[1]=cnt;
 //   hrem[2]=tmpb[cnt];
 //   hrem[3]=state;

   SREG=sregt;
    while((cnt<maxc)&&(hrem[rgadt]==tmpb[cnt])){    
        rgadt++;cnt++;state=0;
    }; 
     
    if(cnt==maxc){maxc=0;}//������ �����  ���������
  }
}
//������� ������������� ����� ������ ���������. ��������!!! ����� ��������� ���������� � ������� ��� 
//�������� �� ������� - �������������� ������� � ������ �����
//���� ���������� ������ �� ��������, ������� ������ 6, ����� 0
char wrblock_ini(UINT first,UCHAR count,UINT * registers){
UCHAR i;
char sregt;
   _clis
   if (maxc!=0){SREG=sregt; return 6;} //6 - slave device busy
   maxc=count;
   cnt=0;
   SREG=sregt;

   for(i=0;i<count;i++){
     tmpb[i]= (registers[i]>>8)+(registers[i]<<8);
   }  
   rgadt=first;
   state=0; 
   wrblock();
   return 0;
};

/*
char setrg(UINT address,UINT rg){
char sregt;


  if (address< eepromm){
  // ������ �������� � eeprom � ��������� �����������
     _clis
     *(( unsigned int __eeprom *)(address*2))=rg;
     *(( unsigned int __eeprom *)(address*2+eepromm*2))=rg;
//     *(( unsigned int __eeprom *)(address))=rg;
//     *(( unsigned int __eeprom *)(address+eepromm))=rg;
     hrem[address]=rg;
     SREG=sregt;
     
     return 0;
  };
return 0;
};
*/
//������ �������� ������ � ��prom, ��� ������ ����� � ������� � ���
char setrg(UINT address,UINT rg){
//char sregt;


  while(EECR & (1<<EEWE));    /* Wait for completion of previous write */
  setch(address*2,rg&0xff);
   while(EECR & (1<<EEWE));    /* Wait for completion of previous write */
  setch(address*2+1,rg>>8);
  while(EECR & (1<<EEWE));    /* Wait for completion of previous write */
  setch(address*2+eepromm*2,rg&0xff);
  while(EECR & (1<<EEWE));    /* Wait for completion of previous write */
  setch(address*2+1+eepromm*2,rg>>8);

  hrem[address]=rg;
  return 0;
};

///////////////////////////////////////////////////////////////////////////
// ������� �������������� ���������� ����� �� ���������
void inicomm(){
  setrg(0x101,1); //����� 1
  setrg(0x102,192); //�������� 19200
//  setrg(0x102,1152); //�������� 115200
  setrg(0x103,2); //even 
  hrem[0x101]=1;
  hrem[0x102]=192;
  hrem[0x103]=2;   
}
void inibase(){
int i,im;
    rde2(0,i,im);
   if((i!=0xffff)||(im!=0xffff)) goto copymirr;
    rde2(0x102,i,im);
    if((i!=0xffff)||(im!=0xffff)) goto copymirr;
    rde2(0x103,i,im);
    if((i!=0xffff)||(im!=0xffff)) goto copymirr;
    //������ ��������������,������ ��������� 
    //���������� ��� ��������     
    setrg(0,dev_id);
    inicomm();  
   
//    setch(0x101*2+eepromm*2,0xaa); //���������� �������� ������ � ��������� ���� ��� ������������ !!!
    setrg(0x104,2); //���������� ����������� ��������
    setrg(0x17f,0); //������� ���������
     __watchdog_reset();
    for (i=0x160;i<=0x16f;i++)setrg(i,0);//����� ������� �������
    for (i=0x380;i<=0x3ff;i++){ __watchdog_reset();setrg(i,85+0x100);}//������� 30 �������� � 1 ������ � �������
copymirr:  
    setrg(0x0a,i);
    setrg(0x0b,im);      
    rde(3,i);
    if(i!=(ver<<8|subver)){
       wre(3,ver<<8|subver);
       wrem(3,ver<<8|subver);
    }
//copymirr:    
    for(i=0;i<eepromm;i++){ //����������� ������� �� ��prom
       rde(i,hrem[i]) 
    }
   check_cfg_change(); 
   //��������� RAM- ����� ����
   for(i=0;i<0x40;i++)ramb[i]=0;
};

char isempty(int offset){
int i;
for (i=0;i<4;i++) if (hrem[offset+i]!=0xffff) return 0;
return 1;
}
void check_cfg_change(){

char i,j;
/*
    for (i=0;i<=7;i++) {
       if (hrem[0x160+i]!=0) for (j=0;j<=16;j++) {
          if ( ((hrem[0x160+i])&(1<<j))!=0) 
             if (isempty(0x180+i*16+j)) setrg(0x160+i,hrem[0x160+i]&~(1<<j));
          
       }
       if (hrem[0x168+i]!=0) for (j=0;j<=16;j++) {
          if ( ((hrem[0x168+i])&(1<<j))!=0) 
             if (isempty(0x180+i*16+j)) setrg(0x160+i,hrem[0x168+i]&~(1<<j));
          
       }
    }
*/
    for (i=0;i<=7;i++) {
       if (hrem[0x160+i]!=0) for (j=0;j<=15;j++) {
          if ( ((hrem[0x160+i])&(1<<j))!=0) 
             if (isempty(0x180+i*16*4+j*4))   setrg(0x160+i,hrem[0x160+i]&~(1<<j));
          
       }
       if (hrem[0x168+i]!=0) for (j=0;j<=15;j++) {
          if ( ((hrem[0x168+i])&(1<<j))!=0) 
             if (isempty(0x180+i*16*4+j*4)) setrg(0x160+i,hrem[0x168+i]&~(1<<j));
          
       }
    }
}
UINT basechk(){
int i,rg,rg2;
// if (hre[0]!=hrem[0])return 0; 
 for(i=1;i<eepromm;i++){
     rde(i,rg) 
     rdem(i,rg2) 
   if (rg!=rg2)return i;
 }
 return 0;
}
