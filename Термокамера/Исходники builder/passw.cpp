//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "passw.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPassword *Password;
#define PASSWORD "�����"

//---------------------------------------------------------------------------
__fastcall TPassword::TPassword(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPassword::btOKClick(TObject *Sender)
{
/*  ModalResult=mrOk;
  return; */ 
 if(!edPass->Text.Length()) ModalResult=mrNo;
 else
  {
  CheckPassword(edPass->Text);
  ModalResult=mrOk;
  }
}
//---------------------------------------------------------------------------

void TPassword::CheckPassword(AnsiString& s)
{
 int pass[]={'�'*'�','�'*'�','�'*'�','�'*'�','�'*'�'};
 char* tmp=s.c_str();
 for(int i=0;*tmp;tmp++,i++)
 {
  if((*tmp)*(*tmp)!=pass[i])
  {
   edPass->Clear();
   ActiveControl=edPass;
   throw Exception("������������ ������!");
  }
 }
}
