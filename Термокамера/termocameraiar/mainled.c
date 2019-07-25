#include "iom64.h"
//#include "ina90.h"
void delayloop(unsigned int d){
unsigned int i,i2,i3;
for (i=0;i<d;i++)
  for (i2=0;i2<1100;i2++) _NOP();
};
main(){
for (;;){
//  asm("LDI R16,0\n out 05,r16\n");
  DDRB=0XFF;
  PORTB=0x80;
  delayloop(500);
  PORTB=0x40;
  delayloop(500);
}
};

