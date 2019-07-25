//---------------------------------------------------------------------------

#include <vcl.h>
#include<stdio.h>
#include<math.h>
#pragma hdrstop

#include "func.h"
#include "responses.h"
#include "Init_Modb.h"
#include "main.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)

UCHAR slave;
AnsiString port;
UINT baud;
UCHAR parity;
AnsiString alpha;

HANDLE hPort;

ECommError::ECommError(int n):Exception("")
{
char mess[8][30]={"Недопустимая функция",
                "Недопустимый адрес данных",
                "Недопустимое значение данных",
                "Сбой устройства",
                "Подтверждение",
                "Устройство занято",
                "Отрицательное подтверждение",
                "Ошибка памяти"
                 };
HelpContext = n;                 
switch(n)
 {
 case FR_ERR_NOT_RESPOND:
     Message="Нет ответа!";
     break;
 case FR_ERR_CRC_FAILED:
     Message="Ошибка CRC!";
     break;
 case FR_ERR_FUNC_NOT_SUPPORTED:
     Message="Функция не поддерживается библиотекой!";
     break;
 case FR_ERR_BAD_DATA_BUFF:
     Message="Не хватает буфера данных!";
     break;

 default:
    if(n<=8)
     Message=mess[n-1];
    else Message="Неизвестная ошибка связи!";

 }
}

ECalibError::ECalibError(int value):Exception("")
{
Message=AnsiString("Значение ")+value+" выходит за пределы!\n"+
                   "Проверьте подключение цепей или исправность модуля!";
}

void WriteReg(USHORT adr, USHORT value)
{
WriteRegs(adr,1,&value);
}

void ReadReg(USHORT adr, USHORT& value)
{
USHORT tmp;
ReadRegs(adr,1,&tmp);
value=tmp;
}

void WriteRegs(USHORT adr, USHORT num,void* data)
{
int err;
for(int i=0;i<3;i++)
 {
 err=invoke_modb(slave,16,adr,num,data);
 if(err==FR_SUCCESS) return;
 }
 throw ECommError(err);
}

void WriteSafeRegs(USHORT adr, USHORT num,void* data)
{
WriteReg(0x778,0xAAAA);
WriteRegs(adr,num, data);
}

void WriteSafeReg(USHORT adr,USHORT data)
{
WriteSafeRegs(adr,1,&data);
}

void ReadRegs(USHORT adr,USHORT num ,void* data)
{
int err;
for(int i=0;i<3;i++)
 {
 err=invoke_modb(slave,3,adr,num,data);
 if(err==FR_SUCCESS) return;
 }
 throw ECommError(err);
}

char* WordToStr(USHORT val,tagGnd gnd)
{
AnsiString format;
static char tmp[7];
switch(gnd)
{
 case dec:
     format="%hu";
     break;
 case _dec:
     format="%hd";
     break;
 case hex:
     format="%hX";
     break;

}
 sprintf(tmp,format.c_str(),val);
 return tmp;
}

WORD StrToWord(AnsiString& str,tagGnd gnd)
{
AnsiString format;
int val=0;;
if(gnd==hex)
 {
 format="%X";
 }
else
 {
 format="%d";
 }

sscanf(str.c_str(),format.c_str(),&val);
if(gnd==_dec)
 {
 if((val>32767) || (val<-32768))
  throw Exception("Значение "+str+" выходит за пределы -32768 - 32767!");
 }
else
 {
 if(val>65535||val<0)
  throw Exception("Значение "+str+" выходит за пределы 0 - 65535!");
 }
return val;
}

char* FloatToStr(float val,USHORT ndig=3)
{
static char tmp[20];
AnsiString s("%.");
s=s+ndig+'f';
sprintf(tmp,s.c_str(),val);
*(strchr(tmp,'.'))=',';
return tmp;
}
/*
bool LoadModb()
{
HANDLE hLib;
hLib=LoadLibrary("comm_mb.dll");
if(!hLib)
 {
  MessageBox(0,"Не найдена comm_mb.dll!","Ошибка!",MB_OK|MB_ICONERROR);
  return false;
 }
 init_comm=(int _stdcall (* )(char *,UINT ,UCHAR ))GetProcAddress(hLib,"init_comm");
 if(!init_comm)
 {
  MessageBox(0,"comm_mb.dll не содержит функции init_comm!","Ошибка!",MB_OK|MB_ICONERROR);
  return false;
 }
 invoke_modb=(int _stdcall (*)(UCHAR, UCHAR, USHORT , USHORT , void *))GetProcAddress(hLib,"invoke_modb");
 if(!invoke_modb)
 {
  MessageBox(0,"comm_mb.dll не содержит функции invoke_modb!","Ошибка!",MB_OK|MB_ICONERROR);
  return false;
 }
 EnumParameters=(int _stdcall (*)(char*, WORD, WORD , BYTE , UINT *,BYTE*))GetProcAddress(hLib,"EnumParameters");
 if(!EnumParameters)
 {
  MessageBox(0,"comm_mb.dll не содержит функции EnumParameters!","Ошибка!",MB_OK|MB_ICONERROR);
  return false;
 }
return true; 
}
 */
bool IniPort(const AnsiString& port,UINT baud,UCHAR parity)
{
 char* c=port.c_str();
if(init_comm(c,baud,parity)!=FR_SUCCESS)
 {

  MessageBox(0,("Невозможно открыть "+port).c_str(),"Ошибка",MB_OK|MB_ICONERROR);
 Form1->IniStatusBar(false);
  return false;
 }
 else
 {
  Form1->IniStatusBar(true);
  SetTout(500);
  return true;
 }
}

void SendData(HANDLE hwnd,void* data, DWORD count)
{
COPYDATASTRUCT cd;
cd.lpData=data;
cd.cbData=count;
SendMessage(hwnd,WM_COPYDATA,(WPARAM)hwnd,(LPARAM)&cd);
}



