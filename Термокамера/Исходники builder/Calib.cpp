//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "Calib.h"
#include "func.h"
#include "ModulParams.h"
#undef CHECK_TEMP
const
 USHORT
 cc_adr=0x8,
 val_adr=0x404;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCalibr1 *Calibr1;
UCHAR lslave;
//---------------------------------------------------------------------------
__fastcall TCalibr1::TCalibr1(TComponent* Owner)
        : TForm(Owner)
{
lslave=slave;
slave=1;
IniPort(port,19200,2);
btPrevClick(0);
}
//---------------------------------------------------------------------------
void __fastcall TCalibr1::btPrevClick(TObject *Sender)
{
num=0;
Caption="Калибровка - шаг 1";
lbTip->Caption="Отсоедините входа модуля";
btPrev->Visible=false;
edT->Text="";
edT->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TCalibr1::btNextClick(TObject *Sender)
{
UINT tmp[2];
static USHORT in0[4],in50[4],inT;
if(num==0)
{
UINT tmp[2]={0x10000,0};

 WriteReg(check,0xFFFF);
 for(int i=0;i<4;i++)
 {
 WriteSafeRegs(cc_adr+i*4,3,tmp);
 Sleep(10);
 }
 tmp[0]=0x3000;
 WriteSafeRegs(cc_adr+16,3,tmp);
 Sleep(1000);
 ReadRegs(val_adr,4,in0);
 for(int i=0;i<4;i++)
  {
   if(in0[i]>0x21)
   {
    char tmp[30];
    sprintf(tmp,"Большой ток нуля - ~%.1f мА по каналу %d",((float)in0[i])/32.76,i+1);
    MessageBox(Handle,tmp,"Ошибка",MB_OK|MB_ICONERROR);
    return;
   }//if(in0[i]>0x21)
  }//for(int i=0;i<4;i++)
 Caption="Калибровка - шаг 2";
 lbTip->Caption="Задайте вытекающий ток 50 мА по каналу 1";
 btPrev->Visible=true;
 num++;
}//if(num==0)
else
{
 switch(num)
 {
 case 1:
 case 2:
 case 3:
   ReadRegs(val_adr+num-1,1,&in50[num-1]);
   if((in50[num-1]<(0x666-0x21))||(in50[num-1]>(0x666+0x21)))
    {
    char tmp[30];
    sprintf(tmp,"Некорректный измеренный ток - ~%.1f мА по каналу %d",((float)in50[num-1])/32.76,num);
    MessageBox(Handle,tmp,"Ошибка",MB_OK|MB_ICONERROR);
    return;
    }
   Display(num);
   num++;
  break;
 case 4:
      ReadRegs(val_adr+num-1,1,&in50[num-1]);
#ifdef CHECK_TEMP
      Display(num);
      num++;
      break;
 case 5:
  ReadRegs(0x408,1,&inT);
  short tmp;
  tmp=edT->Text.ToInt()-inT;
  if(tmp<-400||tmp>-250)
  {
   MessageBox(Handle,"Неправильно введена температура или неисправен датчик!","Ошибка!",MB_OK|MB_ICONERROR);
   return;
  }
  WriteSafeRegs(cc_adr+16+2,1,&tmp);
  Sleep(250);
#endif

  for(int i=0;i<4;i++)
  {
  UINT tmp[2];
  tmp[0]= 32768000/((UINT)(in50[i]-in0[i]));
  tmp[1]=(SHORT)(500-((double)tmp[0]*in50[i])/65536);
  WriteSafeRegs(cc_adr+i*4,3,tmp);
  Sleep(250);
  }//for(int i=0;i<4;i++)
  USHORT year,month,day,reg;

  Date().DecodeDate(&year,&month,&day);
  reg=day;
  reg|=0x20;//взводим флаг нового формата
  reg|=month<<6;
  reg|=(year%100)<<10;
  WriteReg(check,reg);
  if(MessageBox(Handle,"Калибровка проведена успешно!\nКалибровать следующий модуль?","",MB_YESNO|MB_ICONQUESTION)==IDNO)
    {
    ModalResult=mrNo;
    }
  else btPrevClick(0);
 }//switch(num)
}//if(num==0) else

}
//---------------------------------------------------------------------------

void __fastcall TCalibr1::FormClose(TObject *Sender, TCloseAction &Action)
{
slave=lslave;
IniPort(port,baud,parity);
}
//---------------------------------------------------------------------------


void TCalibr1::Display(int num)
{
        //TODO: Add your source code here
 switch(num)
 {
 case 0:

    break;
 case 1:
 case 2:
 case 3:
   Caption= AnsiString("Калибровка - шаг ")+(num+2);
   lbTip->Caption=AnsiString("Задайте вытекающий ток 50 мА по каналу ")+(num+1);
    break;
 case 4:
      Caption= AnsiString("Калибровка - шаг ")+(num+2);
      lbTip->Caption="Ввведите температуру воздуха";
      edT->Visible=true;
      ActiveControl=edT;
    break;
 case 5:
    break;
 }//switch(num)
}
