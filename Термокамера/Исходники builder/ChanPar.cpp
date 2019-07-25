//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ChanPar.h"
#include "func.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TChanPars *ChanPars;
//---------------------------------------------------------------------------
__fastcall TChanPars::TChanPars(TComponent* Owner)
        : TForm(Owner)
{
sgRange->Cells[0][0]="    Пороги каналов (мА)";
sgRange->Cells[0][1]="Обрыв линии";
sgRange->Cells[0][2]="Сработал один ПИ";
sgRange->Cells[0][3]="Cработало более одного ПИ";
sgRange->Cells[0][4]="Короткое замыкание";
sgRange->Cells[1][0]="    1  ";
sgRange->Cells[2][0]="    2  ";
sgRange->Cells[3][0]="    3  ";
sgRange->Cells[4][0]="    4  ";

sgModes->Cells[0][0]="    Режимы каналов";
sgModes->Cells[0][1]="Тип шлейфа (0 - No, 1 - Nc)";
sgModes->Cells[0][2]="Длительность сброса (сек)";
sgModes->Cells[0][3]="Время интегрирования (мс)";
sgModes->Cells[0][4]="Время восстановления (сек)";
sgModes->Cells[1][0]="    1  ";
sgModes->Cells[2][0]="    2  ";
sgModes->Cells[3][0]="    3  ";
sgModes->Cells[4][0]="    4  ";

}
//---------------------------------------------------------------------------
void __fastcall TChanPars::btWriteClick(TObject *Sender)
{
USHORT regs[16];
 for(int j=0;j<4;j++)
 {
  for(int i=0;i<4;i++)
  {
  regs[i]=sgRange->Cells[j+1][i+1].ToDouble()*10;
  }
  WriteRegs(range+j*4,4,regs);
  Sleep(200);
 }
 for(int i=0;i<4;i++)
 {
 regs[0]=sgModes->Cells[i+1][1].ToInt();
 regs[1]=sgModes->Cells[i+1][2].ToInt();
 regs[2]=sgModes->Cells[i+1][3].ToInt()/20;
 regs[3]=sgModes->Cells[i+1][4].ToInt();
 WriteRegs(modes+i*4,4,regs);
 Sleep(200);
 }
 regs[0]=edRep->Text.ToInt();
 regs[2]=edTimeOut->Text.ToInt();
 union
 {
 USHORT reg;
 struct
 {
 char chan1:4;
 char chan2:4;
 char chan3:4;
 char chan4:4;
 };
 }latch;
 latch.chan1=chbFire1->Checked?3:0;
 latch.chan2=chbFire2->Checked?3:0;
 latch.chan3=chbFire3->Checked?3:0;
 latch.chan4=chbFire4->Checked?3:0;

 latch.chan1=chbPI1->Checked?2:latch.chan1;
 latch.chan2=chbPI2->Checked?2:latch.chan2;
 latch.chan3=chbPI3->Checked?2:latch.chan3;
 latch.chan4=chbPI4->Checked?2:latch.chan4;
 regs[1]=latch.reg;
 WriteRegs(mode,3,regs);
 Sleep(200);
}
//---------------------------------------------------------------------------
void __fastcall TChanPars::btReadClick(TObject *Sender)
{
short regs[4];
 for(int j=0;j<4;j++)
 {
  ReadRegs(range+j*4,4,regs);
  for(int i=0;i<4;i++)
  {
  sgRange->Cells[j+1][i+1]=((float)regs[i])/10;
  }//for(int i=0;i<4;i++)
 }//for(int j=0;j<4;j++)

 for(int j=0;j<4;j++)
 {
  ReadRegs(modes+j*4,4,regs);
  sgModes->Cells[j+1][1]=regs[0];
  sgModes->Cells[j+1][2]=regs[1];
  sgModes->Cells[j+1][3]=regs[2]*20;
  sgModes->Cells[j+1][4]=regs[3];
 }//for(int j=0;j<4;j++)
 ReadRegs(mode,3,regs);
 edRep->Text=regs[0];
 edTimeOut->Text=regs[2];
 chbAll->Checked=false;
 chbFire1->Checked=(regs[1]&0xf)==0x3;
 chbFire2->Checked=(regs[1]&0xf0)==0x30;
 chbFire3->Checked=(regs[1]&0xf00)==0x300;
 chbFire4->Checked=(regs[1]&0xf000)==0x3000;

 chbPI1->Checked=(regs[1]&0xf)==0x2;
 chbPIClick(chbPI1);
 chbPI2->Checked=(regs[1]&0xf0)==0x20;
 chbPIClick(chbPI2);
 chbPI3->Checked=(regs[1]&0xf00)==0x200;
 chbPIClick(chbPI3);
 chbPI4->Checked=(regs[1]&0xf000)==0x2000;
 chbPIClick(chbPI4);
}
//---------------------------------------------------------------------------
void __fastcall TChanPars::btDefClick(TObject *Sender)
{

 for(int i=1;i<=4;i++)
 {
 sgRange->Cells[i][1]=2;
 sgRange->Cells[i][2]=20;
 sgRange->Cells[i][3]=40;
 sgRange->Cells[i][4]=50;

 sgModes->Cells[i][1]=0;
 sgModes->Cells[i][2]=2;
 sgModes->Cells[i][3]=20;
 sgModes->Cells[i][4]=2;
 }

 edRep->Text=1;
 edTimeOut->Text=15;
 chbAll->Checked=true;
 chbPI1->Checked=false;
 chbFire1->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TChanPars::sgSetEditText(TObject *Sender, int ACol,
      int ARow, const AnsiString Value)
{
 TStringGrid& sg=*((TStringGrid*)Sender);
 if(chbAll->Checked)
 {

  {
 for(int i=1;i<5;i++)
  if(i!=ACol) sg.Cells[i][ARow]=Value;
  }
 }
}
//---------------------------------------------------------------------------
void __fastcall TChanPars::chbAllClick(TObject *Sender)
{
 if(chbAll->Checked)
 {
  for(int i=1;i<5;i++) for(int j=2;j<5;j++)
   {
   sgRange->Cells[j][i]=sgRange->Cells[1][i];
   sgModes->Cells[j][i]=sgModes->Cells[1][i];
   }//for(int i=1;i<5;i++) for(int j=2;j<5;j++)
  chbFireClick(chbFire1);
  chbPIClick(chbPI1);
 }//if(chbAll->Checked)
}
//---------------------------------------------------------------------------



void __fastcall TChanPars::chbFireClick(TObject *Sender)
{
if(chbAll->Checked)
{
for(int i=1;i<=4;i++)
 {
 TCheckBox* chb;
 chb=(TCheckBox*)FindChildControl(AnsiString("chbFire")+i);
 chb->OnClick=0;
 chb->Checked=((TCheckBox*)Sender)->Checked;
 chb->OnClick=chbFireClick;
 }//for(int i=1;i<=4;i++)
}//if(chbAll->Checked)
}
//---------------------------------------------------------------------------

void __fastcall TChanPars::chbPIClick(TObject *Sender)
{
TCheckBox *chb,*chb1;
chb=(TCheckBox*)Sender;
chb1=(TCheckBox*)FindChildControl(AnsiString("chbFire")+chb->Tag);
if(chb->Checked)
{
chb1->Checked=true;
chb1->Enabled=false;
}//if(chb->Checked)
else chb1->Enabled=true;
if(chbAll->Checked)
{
for(int i=1;i<=4;i++)
 {
 chb=(TCheckBox*)FindChildControl(AnsiString("chbPI")+i);
 if(chb!=Sender)
 {
 chb->Checked=((TCheckBox*)Sender)->Checked;
 }
 }//for(int i=1;i<=4;i++)
}//if(chbAll->Checked)
}
//---------------------------------------------------------------------------

