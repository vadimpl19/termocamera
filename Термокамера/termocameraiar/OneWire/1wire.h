/****************************************************
Описания выводов и макросы по работе с ними
****************************************************/

#define ch1_in  PINE_Bit7
#define ch2_in  PINE_Bit6
#define ch3_in  PINE_Bit5
#define ch4_in  PINE_Bit4

/** управление буфером инверсное **/
#define ch1_up  PORTA_Bit7
#define ch2_up  PORTA_Bit5
#define ch3_up  PORTA_Bit1
#define ch4_up  PORTF_Bit0

#define ch1_down  PORTG_Bit2
#define ch2_down  PORTA_Bit6
#define ch3_down  PORTA_Bit2
#define ch4_down  PORTF_Bit1

#define pwr1_on     ch1_down =0, ch1_up =0
#define pwr1_off    ch1_up =1
#define line1_up    ch1_down =0, ch1_up =1
#define line1_down  ch1_up =1, ch1_down =1

#define pwr2_on     ch2_down =0, ch2_up =0
#define pwr2_off    ch2_up =1
#define line2_up    ch2_down =0, ch2_up =1
#define line2_down  ch2_up =1, ch2_down =1

#define pwr3_on     ch3_down =0, ch3_up =0
#define pwr3_off    ch3_up =1
#define line3_up    ch3_down =0, ch3_up =1
#define line3_down  ch3_up =1, ch3_down =1

#define pwr4_on     ch4_down =0, ch4_up =0
#define pwr4_off    ch4_up =1
#define line4_up    ch4_down =0, ch4_up =1
#define line4_down  ch4_up =1, ch4_down =1
