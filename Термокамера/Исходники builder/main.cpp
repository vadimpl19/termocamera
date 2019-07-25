//---------------------------------------------------------------------------

#include <vcl.h>
#include <inifiles.hpp>
#pragma hdrstop

#include "main.h"
#include "mdata.h"
#include "COMPar.h"
#include "func.h"
#include "About.h"
#include "ModulParams.h"
#include "passw.h"
#include "Calib.h"
#include "ChanPar.h"
#include "frmModuleParam.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
 TIniFile* ini=new TIniFile(ChangeFileExt(Application->ExeName,".ini"));
 port=ini->ReadString("Port","Name","COM1");
 baud=ini->ReadInteger("Port","Baud",19200);
 parity=ini->ReadInteger("Port","Parity",2);
 slave=ini->ReadInteger("Station","Address",1);
 alpha=ini->ReadString("Alpha","Alpha","A");
 delete ini;
 if(IniPort(port,baud,parity))IniStatusBar(true);
 else IniStatusBar(false);
///

    ///////
}
//---------------------------------------------------------------------------
void __fastcall TForm1::miDataClick(TObject *Sender)
{
Application->CreateForm(__classid(TModData),&ModData);
ModData->ShowModal();
delete  ModData;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::miComParClick(TObject *Sender)
{
/*
    Application->CreateForm(__classid(TParCOM),&ParCOM);
    ParCOM->ShowModal();
    delete  ParCOM; */
  TParCOM *pParCOM;

  pParCOM = new TParCOM(NULL, pAp01mkObj);

  pParCOM->ShowModal();
  delete  pParCOM;
IniStatusBar(true);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::mmAboutClick(TObject *Sender)
{
Application->CreateForm(__classid(TAboutBox),&AboutBox);
AboutBox->ShowModal();
delete  AboutBox;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::miPassportClick(TObject *Sender)
{
/*    Application->CreateForm(__classid(TModPars),&ModPars);*/
  TModPars *pModPars;

  pModPars = new TModPars(NULL, pAp01mkObj);

  pModPars->ShowModal();
  delete  pModPars;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::miModParClick(TObject *Sender)
{
  TfrmModuleParamForm *pfrmModuleParamForm;
  if (pAp01mkObj->GetWrkMode())
  {
    pfrmModuleParamForm = new TfrmModuleParamForm(NULL, pAp01mkObj);
    pfrmModuleParamForm->ShowModal();
    delete  pfrmModuleParamForm;
  }
  else
  {
    Application->CreateForm(__classid(TChanPars),&ChanPars);
    ChanPars->ShowModal();
    delete  ChanPars;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::miCalibClick(TObject *Sender)
{
Application->CreateForm(__classid(TCalibr1),&Calibr1);
if(MessageBox(Handle,
   "Внимание! Даннные в EEPROM будут изменены!\nПродолжить!",
   "",MB_YESNO|MB_ICONWARNING)==ID_YES)
 {
 UCHAR lslave=slave;
 slave=1;
 IniPort(port,19200,2);
 Calibr1->ShowModal();
 delete  Calibr1;
 slave=lslave;
 IniPort(port,baud,parity);
 }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::miTermCalibClick(TObject *Sender)
{
USHORT reg;
if(MessageBox(Handle,"Внимание! Даннные в EEPROM будут изменены!\nПродолжить!","",MB_YESNO|MB_ICONWARNING)==ID_YES)
 {
 ReadReg(term_reg,reg);
 WriteReg(term_down,reg);
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  pAp01mkObj = new TAp01mkObj(this);
  pAp01mkObj->SetWrkMode(true);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
  delete pAp01mkObj;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::miSetModuleClick(TObject *Sender)
{
  pAp01mkObj->SwitchWrkMode();
}
//---------------------------------------------------------------------------

void TForm1::IniStatusBar(bool stat)
{
 char par[3][5]={"None","Odd","Even"};
 AnsiString tmp=port+"  "+baud+" бод "+par[parity]+" Адрес " +slave;
 if(stat)
 {
 StatusBar1->Panels->Items[0]->Text="Открыт "+tmp;
 }
else
 {
 StatusBar1->Panels->Items[0]->Text="Закрыт "+tmp;
 }
}

void __fastcall TForm1::A1Click(TObject *Sender)
{
Application->CreateForm(__classid(TAboutBox),&AboutBox);
AboutBox->ShowModal();
delete  AboutBox;        
}
//---------------------------------------------------------------------------

