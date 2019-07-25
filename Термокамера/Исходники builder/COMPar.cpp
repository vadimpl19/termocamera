//---------------------------------------------------------------------------

#include <vcl.h>
#include <inifiles.hpp>
#pragma hdrstop
#include "ms_ap_01mk_obj.h"
#include "COMPar.h"
#include "func.h"
#include "responses.h"
#include "Init_Modb.h"
#include "mess.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TParCOM *ParCOM;

//---------------------------------------------------------------------------
__fastcall TParCOM::TParCOM(TComponent* Owner, TAp01mkObj *a_pObjIn)
        : TForm(Owner)
{
  pWrkObj = a_pObjIn;
  int iSpeed;
 TComboBox& Port= *(cbPort);
 TComboBox& Speed= *(cbSpeed);
 if(port=="COM1") Port.ItemIndex=0;
 if(port=="COM2") Port.ItemIndex=1;
 if(port=="COM3") Port.ItemIndex=2;
 if(port=="COM4") Port.ItemIndex=3;
 if(port=="COM5") Port.ItemIndex=4;
 if(port=="COM6") Port.ItemIndex=5;
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

  switch(baud)
  {
    case 2400:
           iSpeed=0;
           break;
    case 4800:
           iSpeed=1;
           break;
    case 9600:
           iSpeed=2;
           break;
    case 19200:
           iSpeed=3;
           break;
    case 38400:
           iSpeed=4;
           break;

    case 57600:
           iSpeed=5;
           break;
    case 115200:
           iSpeed=6;
           break;
  }
  if (pWrkObj->GetWrkMode() && iSpeed >=0)
  {
    cbSpeed->ItemIndex = iSpeed - 1;
  }
  else
    cbSpeed->ItemIndex = iSpeed;

 cbParity->ItemIndex=parity;
 edAddress->Text=slave;

 char tmp=alpha.UpperCase()[1];
 if(tmp<'A'||tmp>'Z') tmp=-1;
 else tmp-='A';
 cbSerNumAlpha->ItemIndex=tmp;


}
//---------------------------------------------------------------------------


void __fastcall TParCOM::btOkClick(TObject *Sender)
{
 TComboBox& Port= *(cbPort);
 TComboBox& Speed= *(cbSpeed);
 TComboBox& Parity= *(cbParity);
 TEdit& Adr=*(edAddress);

  if(IniPort(Port.Text,Speed.Text.ToInt(),Parity.ItemIndex))
  {
  slave=Adr.Text.ToInt();
  port=Port.Text;
  baud=Speed.Text.ToInt();
  parity=Parity.ItemIndex;
  if(cbSerNumAlpha->ItemIndex!=-1)
     alpha=cbSerNumAlpha->Text;
  TIniFile& ini=*(new TIniFile(ChangeFileExt(Application->ExeName,".ini")));
  ini.WriteString("Port","Name",port);
  ini.WriteInteger("Port","Baud",baud);
  ini.WriteInteger("Port","Parity",parity);
  ini.WriteInteger("Station","Address",slave);
  ini.WriteString("Alpha","Alpha",alpha);
  delete &ini;
  ModalResult=mrOk;
  }
}
//---------------------------------------------------------------------------

void __fastcall TParCOM::Button1Click(TObject *Sender)
{
 cbPort->ItemIndex=0;
  if (pWrkObj->GetWrkMode())
    cbSpeed->ItemIndex=2;
  else
    cbSpeed->ItemIndex=3;
 cbParity->ItemIndex=2;
 edAddress->Text="1";
}
//---------------------------------------------------------------------------

void __fastcall TParCOM::btAutoClick(TObject *Sender)
{
UINT baud;
BYTE parity;
WORD tmp;
WORD wTypeOfMod;
int iSpeed;
if(!edNumber->Text.Length()||cbSerNumAlpha->ItemIndex==-1) throw Exception("Введите  номер модуля!");
 tmp=((cbSerNumAlpha->ItemIndex+1)<<11)+edNumber->Text.ToInt();   //старшие 5 бит -номер англ. буквы(A==1),
fMess=new TfMess(this);
fMess->Update();

if (pWrkObj->GetWrkMode())
  wTypeOfMod = TMD101MK;
else
  wTypeOfMod = TMD101;

int success=EnumParameters(cbPort->Text.c_str(),wTypeOfMod,
               tmp,edAddress->Text.ToInt(),&baud,&parity);
if(!success)
 {
    switch(baud)
    {
      case 2400:
             iSpeed=0;
             break;
      case 4800:
             iSpeed=1;
             break;
      case 9600:
             iSpeed=2;
             break;
      case 19200:
             iSpeed=3;
             break;
      case 38400:
             iSpeed=4;
             break;

      case 57600:
             iSpeed=5;
             break;
      case 115200:
             iSpeed=6;
             break;
    }
    if (pWrkObj->GetWrkMode() && iSpeed >=0)
      cbSpeed->ItemIndex = iSpeed - 1;
    else
      cbSpeed->ItemIndex = iSpeed;

    cbParity->ItemIndex=parity;
    delete fMess;
    MessageBox(Handle,"Модуль обнаружен!\nДля установки параметров порта нажмите \"ОК\"","",MB_ICONEXCLAMATION|MB_OK);
  }
 else
 {
  delete fMess;
  if(success==FR_ERR_NOT_RESPOND)  throw Exception("Модуль не найден!");
  else if(success==FR_ERR_CRC_FAILED)
    throw Exception("Ошибка CRC!\n Возможно просто сбой!\nПовторите попытку!");
 }
}
//---------------------------------------------------------------------------

