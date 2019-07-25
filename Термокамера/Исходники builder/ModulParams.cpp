//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop
#include "ms_ap_01mk_obj.h"
#include"moduls_codes.h"
#include "ModulParams.h"
#include "func.h"
#include "passw.h"
#include "Init_Modb.h"
#include <inifiles.hpp>
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TModPars *ModPars;
//---------------------------------------------------------------------------
__fastcall TModPars::TModPars(TComponent* Owner, TAp01mkObj *a_pObjIn)
        : TForm(Owner)
{
  int res=Password->ShowModal();
  if(res==mrNo)
  {
    edNumber->Enabled=false;
    edNumber->Color=clGray;
    edManuf->Enabled=false;
    edManuf->Color=clGray;
    cbAlpha->Enabled=false;
    cbAlpha->Color=clGray;
  }//if(res==mrNo)
  else
  {
    char tmp=alpha.UpperCase()[1];
    if(tmp<'A'||tmp>'Z') tmp=-1;
    else tmp-='A';
    cbAlpha->ItemIndex=tmp;
  }
  pWrkObj = a_pObjIn;
  cbSpeed->Items->Clear();
  if (!pWrkObj->GetWrkMode())
  {
    cbSpeed->Items->Add("2400");
  }

  cbSpeed->Items->Add("4800");
  cbSpeed->Items->Add("9600");
  cbSpeed->Items->Add("19200");
  cbSpeed->Items->Add("38400");
  cbSpeed->Items->Add("57600");
  cbSpeed->Items->Add("115200");

}
//---------------------------------------------------------------------------
void __fastcall TModPars::btWriteClick(TObject *Sender)
{
  int tmp;
  if(cbSpeed->ItemIndex==-1) throw Exception("Выберите скорость!");
  if(cbParity->ItemIndex==-1) throw Exception("Выберите паритет!");
  if(!edAdress->Text.Length()||(tmp=edAdress->Text.Trim().ToInt())>240)throw Exception("Введите корректное значение адреса!");
  if(!pWrkObj->MBWriteReg(adr,tmp)) return;
  Sleep(100);

  tmp=cbSpeed->Text.ToInt()/100;
  if(!pWrkObj->MBWriteReg(speed,tmp)) return;
  Sleep(100);

  tmp=cbParity->ItemIndex;
  if(!pWrkObj->MBWriteReg(parity_stopbits,tmp)) return;
  Sleep(100);

  if(edNumber->Enabled)
  {
    if(!edNumber->Text.Length()||cbAlpha->ItemIndex==-1) throw Exception("Введите  номер модуля!");

    tmp=((cbAlpha->ItemIndex+1)<<11)+edNumber->Text.ToInt(); //старшие 5 бит -номер англ. буквы(A==1),
                  //младшие 11 - цифровая часть номера модуля
    WriteSafeReg(num,tmp);
    Sleep(100);
    USHORT year,month,day;
    TDateTime(edManuf->Text).DecodeDate(&year,&month,&day);

    tmp=day;
    tmp|=0x20;//взводим флаг нового формата
    tmp|=month<<6;
    tmp|=(year%100)<<10;
    WriteSafeReg(manuf,tmp);
    Sleep(100);
  }//if(edNumber->Enabled)
  WORD data=key;
  invoke_modb(slave,16,res,1,&data);

  TIniFile* ini=new TIniFile(ChangeFileExt(Application->ExeName,".ini"));
  port =ini->ReadString("Port","Name","COM1");
  delete ini;

  if(cbAlpha->ItemIndex!=-1)
     alpha=cbAlpha->Text;

  if(IniPort(port,cbSpeed->Text.ToInt(),cbParity->ItemIndex))
  {
    baud=cbSpeed->Text.ToInt();
    parity=cbParity->ItemIndex;
    slave=edAdress->Text.Trim().ToInt();
    TIniFile* ini=new TIniFile(ChangeFileExt(Application->ExeName,".ini"));
    ini->WriteString("Port","Name",port);
    ini->WriteInteger("Port","Baud",baud);
    ini->WriteInteger("Port","Parity",parity);
    ini->WriteInteger("Station","Address",slave);
    ini->WriteString("Alpha","Alpha",alpha);
    delete ini;
    Form1->IniStatusBar(true);
    MessageBox(Handle,"Запись успешно завершена!\n Настройки COM порта изменены.","",MB_OK|MB_ICONEXCLAMATION);
  }

}
//---------------------------------------------------------------------------

void __fastcall TModPars::btReadClick(TObject *Sender)
{
  USHORT tmp;
  int iSpeed;
if(!pWrkObj->MBReadReg(adr,tmp)) return;
edAdress->Text=tmp;
if(!pWrkObj->MBReadReg(speed,tmp)) return;
switch(tmp)
 {
  case 24:
          iSpeed =0;
          break;
  case 48:
          iSpeed=1;
          break;
  case 96:
          iSpeed=2;
          break;
  case 192:
          iSpeed=3;
          break;
  case 384:
          iSpeed=4;
          break;
  case 576:
          iSpeed=5;
          break;
  case 1152:
          iSpeed=6;
          break;
  default: iSpeed = -1;
 }
  if (pWrkObj->GetWrkMode() && iSpeed >=0)
  {
    cbSpeed->ItemIndex = iSpeed - 1;
  }
  else
    cbSpeed->ItemIndex = iSpeed;

if(!pWrkObj->MBReadReg(parity_stopbits,tmp)) return;
cbParity->ItemIndex=LOBYTE(tmp);
if(!pWrkObj->MBReadReg(type,tmp)) return;
if(tmp<=NUM_MODULS) edName->Text=NamesModuls[tmp-1];
else edName->Text="UNKNOWN";

if(!pWrkObj->MBReadReg(num,tmp)) return;
char buf[56];
//старшие 5 бит -номер англ. буквы(A==1),
sprintf(buf,"%04d",tmp&0x7FF);
edNumber->Text=buf;
//младшие 11 - цифровая часть номера модуля
cbAlpha->ItemIndex=((tmp&0xF800)>>11)-1;
if(!pWrkObj->MBReadReg(ver,tmp)) return;

sprintf(buf,"%02hd.%02hd",(tmp>>8)&0xFF,tmp&0xFF);
edVer->Text=buf;


if(!pWrkObj->MBReadReg(manuf,tmp)) return;
USHORT year,month,day;

if(tmp&0x20)//новый формат
 {
 day=tmp&0x1F;
 month=(tmp>>6)&0xF;
 year=(tmp>>10)&0x3F;
 }
else//старый формат
 {
 day=tmp&0x1F;
 month=(tmp>>8)&0xF;
 year=(tmp>>12)&0x3F;
 }
edManuf->Text=TDateTime(year,month,day).DateString();
}
//---------------------------------------------------------------------------

void __fastcall TModPars::btDefClick(TObject *Sender)
{
edAdress->Text="1";
if (!pWrkObj->GetWrkMode())
  cbSpeed->ItemIndex=3;
else
  cbSpeed->ItemIndex=2;
cbParity->ItemIndex=2;
if(edManuf->Enabled) edManuf->Text=Date().DateString();
}
//---------------------------------------------------------------------------


