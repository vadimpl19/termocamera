//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mdata.h"
#include "func.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TModData *ModData;
//---------------------------------------------------------------------------
__fastcall TModData::TModData(TComponent* Owner)
        : TForm(Owner)
{
lbWire1->Caption="";
lbWire2->Caption="";
lbWire3->Caption="";
lbWire4->Caption="";
lbCurrent1->Caption="Ток:";
lbCurrent2->Caption="Ток:";
lbCurrent3->Caption="Ток:";
lbCurrent4->Caption="Ток:";
lbSt0->Font->Color=clGray;
lbSt1->Font->Color=clGray;
lbSt2->Font->Color=clGray;
lbSt3->Font->Color=clGray;
lbSt4->Font->Color=clGray;
}
//---------------------------------------------------------------------------
void __fastcall TModData::tmReadTimer(TObject *Sender)
{
try{
 AnsiString status[8];
 status[0]="Обрыв";
 status[1]="Дежурный режим";
 status[2]="Сработал один ПИ";
 status[3]="Сработало более одного ПИ";
 status[4]="Короткое замыкание";
 status[5]="Отсутствие напряжения";
 status[6]="Сброс";
 status[7]="";

 union
  {
  USHORT reg;
  struct
   {
   UCHAR wire1:4;
   UCHAR wire2:4;
   UCHAR wire3:4;
   UCHAR wire4:4;
   };
  }wires;
 short regs[9];//={9,0x0243,0,0,400,600,200,602,20};
 ReadRegs(wire_status,9,regs);
 wires.reg=regs[1];
 if(wires.wire1>6) wires.wire1=7;
 if(wires.wire2>6) wires.wire2=7;
 if(wires.wire3>6) wires.wire3=7;
 if(wires.wire4>6) wires.wire4=7;
 lbWire1->Caption=status[wires.wire1];
 lbWire2->Caption=status[wires.wire2];
 lbWire3->Caption=status[wires.wire3];
 lbWire4->Caption=status[wires.wire4];

 lbCurrent1->Caption=AnsiString("Ток: ")+regs[4]/10+','+regs[4]%10+" мА";
 lbCurrent2->Caption=AnsiString("Ток: ")+regs[5]/10+','+regs[5]%10+" мА";
 lbCurrent3->Caption=AnsiString("Ток: ")+regs[6]/10+','+regs[6]%10+" мА";
 lbCurrent4->Caption=AnsiString("Ток: ")+regs[7]/10+','+regs[7]%10+" мА";
 lbSt0->Font->Color=(regs[0]&0x1)?clRed:clGray;
 lbSt1->Font->Color=(regs[0]&0x2)?clRed:clGray;
 lbSt2->Font->Color=(regs[0]&0x4)?clRed:clGray;
 lbSt3->Font->Color=(regs[0]&0x8)?clRed:clGray;
 lbSt4->Font->Color=(regs[0]&0x10)?clRed:clGray;

 ReadRegs(latch,1,regs);
 chbLatch1->Checked=(regs[0]&0xf)==0x3;
 chbLatch2->Checked=(regs[0]&0xf0)==0x30;
 chbLatch3->Checked=(regs[0]&0xf00)==0x300;
 chbLatch4->Checked=(regs[0]&0xf000)==0x3000;
 if((regs[0]&0xf)==0x2)
 {
 chbPI1->Checked=true;
 chbLatch1->Checked=true;
 }//if((regs[0]&0xf)==0x2)
 else
 {
 chbPI1->Checked=false;
 }//if((regs[0]&0xf)==0x2) else

 if((regs[0]&0xf0)==0x20)
 {
 chbPI2->Checked=true;
 chbLatch2->Checked=true;
 }//if((regs[0]&0xfo)==0x20)
 else
 {
 chbPI2->Checked=false;
 }//if((regs[0]&0xfo)==0x20) else
 if((regs[0]&0xf00)==0x200)
 {
 chbPI3->Checked=true;
 chbLatch3->Checked=true;
 }//if((regs[0]&0xf00)==0x200)
 else
 {
 chbPI3->Checked=false;
 }// if((regs[0]&0xf00)==0x200) else
 if((regs[0]&0xf000)==0x2000)
 {
 chbPI4->Checked=true;
 chbLatch4->Checked=true;
 }//if((regs[0]&0xf000)==0x2000)
 else
 {
 chbPI4->Checked=false;
 }//if((regs[0]&0xf000)==0x2000) else
}//try
catch(ECommError&)
{
 CheckBox1->Checked=false;
 throw;
}
}
//---------------------------------------------------------------------------
void __fastcall TModData::CheckBox1Click(TObject *Sender)
{
tmRead->Enabled=CheckBox1->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TModData::btResClick(TObject *Sender)
{
WriteReg(res_md,1<<((TControl*)Sender)->Tag);
}
//-------

