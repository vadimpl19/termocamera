

#define gron4  PORTG=PORTG|0X1;
#define redon4 PORTG=PORTG|0X2;

#define off4   PORTG=PORTG&0Xfe;PORTG=PORTG&0Xfd;
#define gr4  PORTG_Bit0
#define red4  PORTG_Bit1

#define gron3 PORTC=PORTC|0X1;
#define redon3 PORTC=PORTC|0X2;
#define off3   PORTC=PORTC&0Xfc;
#define gr3  PORTC_Bit0
#define red3  PORTC_Bit1


#define gron2  PORTC=PORTC|0X4;
#define redon2 PORTC=PORTC|0X8;
#define off2   PORTC=PORTC&0Xf3;
#define gr2  PORTC_Bit2
#define red2  PORTC_Bit3


#define gron1  PORTC=PORTC|0X10;
#define redon1 PORTC=PORTC|0X20;
#define off1   PORTC=PORTC&0Xcf;
#define gr1  PORTC_Bit4
#define red1  PORTC_Bit5


#define gronw PORTC=PORTC|0X40;
#define redonw PORTC=PORTC|0X80;
#define offw   PORTC=PORTC&0X3f;
#define grw  PORTC_Bit6
#define redw  PORTC_Bit7

#define heaton  PORTE_Bit2=1;
#define heatoff  PORTE_Bit2=0;

#define xk1 PING_Bit3
#define xk2 PING_Bit4
#define dev_ver_r PIND_Bit7
#define dev_ver_heat PIND_Bit6

