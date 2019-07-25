
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
if(u0.state!=1){return;};
sen0((char *)&buf,len*3+7);
while(u0.state!=1){_NOP();};

};
sentst(){
buf[0]=0;
buf[1]=0x55;
buf[2]=0xaa;
buf[3]=0xab;
buf[4]=0xac;

if(u0.state!=1){return;};
sen0((char *)&buf,4);
while(u0.state!=1){_NOP();};

};