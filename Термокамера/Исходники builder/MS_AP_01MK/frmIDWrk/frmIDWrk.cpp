//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmIDWrk.h"
#include "ms_ap_01mk_obj.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TfrmIDWrkForm *frmIDWrkForm;
//---------------------------------------------------------------------------
__fastcall TfrmIDWrkForm::TfrmIDWrkForm(TComponent* Owner, TAp01mkObj *a_pObjIn, int a_iLine, int a_iWrkCol, int a_iWrkRow)
  : TForm(Owner)
{
  pWrkObj = a_pObjIn;
  iLine = a_iLine;
  iColl = a_iWrkCol;
  iRow = a_iWrkRow;
 /* int iFileHandle;
  int iFileLength;
  int iBytesRead;
  char *pszBuffer;
iFileHandle = FileOpen("D:/1.txt", fmOpenRead);
      iFileLength = FileSeek(iFileHandle,0,2);
      FileSeek(iFileHandle,0,0);
      pszBuffer = new char[iFileLength+1];
      iBytesRead = FileRead(iFileHandle, pszBuffer, iFileLength);
      FileClose(iFileHandle);



      Edit1->Text = IntToStr((int)pszBuffer);

      delete [] pszBuffer;       */

}
//---------------------------------------------------------------------------
bool TfrmIDWrkForm::SyncFromUI(void)
{
  WORD wdIDStartAddr, wdTempStartAddr, wdWrk;
  int iOff, iCntAddr, iIdxLine, iAddrNotNull;
  BYTE btWrk1, btWrk2;
  bool bError;
  AnsiString astWrk1, astWrk2, astError;
  switch(iLine)
  {
    case 0: wdIDStartAddr = 0x180; wdTempStartAddr = 0x380; break;
    case 1: wdIDStartAddr = 0x200; wdTempStartAddr = 0x3a0; break;
    case 2: wdIDStartAddr = 0x280; wdTempStartAddr = 0x3c0; break;
    case 3: wdIDStartAddr = 0x300; wdTempStartAddr = 0x3e0; break;
  };
  iOff = 0;
  for (iCntAddr = 0; iCntAddr < 4; iCntAddr++)
  {
    pWrkObj->TwoByte2Word(btAddr[iOff], btAddr[iOff+1], &wdWrk);
    iOff +=2;
    if (pWrkObj->SetWordDataInfo(etdiLineCfg, wdIDStartAddr+iCntAddr+(iRow-1)*4, wdWrk) == false)
    {
      astError.printf("Ошибка!!! Ошибка чтения значения по адресу 0x%X",wdIDStartAddr+iCntAddr+iRow-1);
      bError = true;
      return false;
    }
  }
  pWrkObj->TwoByte2Word(btTmax, btdT, &wdWrk);
  if (pWrkObj->SetWordDataInfo(etdiLineCfg, wdTempStartAddr+(iRow-1), wdWrk) == false)
  {
    astError.printf("Ошибка!!! Ошибка чтения значения по адресу 0x%X",wdTempStartAddr);
    bError = true;
    return false;
  }
  return true;
}
void TfrmIDWrkForm::SyncToUI(void)
{
  WORD wdIDStartAddr, wdTempStartAddr, wdWrk;
  int iOff, iCntAddr, iIdxLine, iAddrNotNull;
  BYTE btWrk1, btWrk2;
  bool bError;
  AnsiString astWrk1, astWrk2, astError;
  switch(iLine)
  {
    case 0: wdIDStartAddr = 0x180; wdTempStartAddr = 0x380; break;
    case 1: wdIDStartAddr = 0x200; wdTempStartAddr = 0x3a0; break;
    case 2: wdIDStartAddr = 0x280; wdTempStartAddr = 0x3c0; break;
    case 3: wdIDStartAddr = 0x300; wdTempStartAddr = 0x3e0; break;
  };

  iOff = 0;
  //--- Адрес датчика
  astWrk1 = "";
  for (iCntAddr = 0; iCntAddr < 4; iCntAddr++)
  {
    if (pWrkObj->GetWordDataInfo(etdiLineCfg, wdIDStartAddr+iCntAddr+(iRow-1)*4, &wdWrk) == false)
    {
      astError.printf("Ошибка!!! Ошибка чтения значения по адресу 0x%X",wdIDStartAddr+iCntAddr+iRow-1);
      bError = true;
    }
    pWrkObj->Word2TwoByte(wdWrk, &btAddr[iOff], &btAddr[iOff+1]);
    iOff +=2;
  }
  astWrk1.printf("0x%0X", btAddr[0]); edtAddr00->Text = astWrk1;
  astWrk1.printf("0x%0X", btAddr[1]); edtAddr01->Text = astWrk1;
  astWrk1.printf("0x%0X", btAddr[2]); edtAddr02->Text = astWrk1;
  astWrk1.printf("0x%0X", btAddr[3]); edtAddr03->Text = astWrk1;
  astWrk1.printf("0x%0X", btAddr[4]); edtAddr04->Text = astWrk1;
  astWrk1.printf("0x%0X", btAddr[5]); edtAddr05->Text = astWrk1;
  astWrk1.printf("0x%0X", btAddr[6]); edtAddr06->Text = astWrk1;
  astWrk1.printf("0x%0X", btAddr[7]); edtAddr07->Text = astWrk1;

  //--- Значения температуры и дельты
  if (pWrkObj->GetWordDataInfo(etdiLineCfg, wdTempStartAddr+iRow-1, &wdWrk) == false)
  {
    astError.printf("Ошибка!!! Ошибка чтения значения по адресу 0x%X",wdTempStartAddr+iRow-1);
    bError = true;
  }
  pWrkObj->Word2TwoByte(wdWrk, &btWrk1, &btWrk2);
  astWrk1.printf("%d", (signed char)btWrk1);
  astWrk2.printf("%d", (signed char)btWrk2);
  btTmax = btWrk1; btdT = btWrk2;
  edtTmax->Text = astWrk1;
  edtdT->Text = astWrk2;

}
void __fastcall TfrmIDWrkForm::FormShow(TObject *Sender)
{
  SyncToUI();
  if (iColl == 1)
  {
    edtAddr00->SetFocus();
  }
  else if (iColl == 2)
  {
    edtTmax->SetFocus();
  }
  else if (iColl == 3)
  {
    edtdT->SetFocus();
  }

}
//---------------------------------------------------------------------------

void __fastcall TfrmIDWrkForm::btnSaveClick(TObject *Sender)
{
  if(!CheckT())
    return;
  if(!CheckAddr())
    return;

  if(SyncFromUI())
  {
    pWrkObj->bCfgChanged = true;
  }

  Close();

}
//---------------------------------------------------------------------------

void __fastcall TfrmIDWrkForm::btnCancelClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------


bool TfrmIDWrkForm::CheckT(void)
{
  AnsiString astWrk1;
  AnsiString astError;
  int iWrk;
  astWrk1 = edtdT->Text;
  bool bError;
  bError = false;
  try
  {
    iWrk = astWrk1.ToInt();
  }
  catch(EConvertError &e)
  {
    bError = true;
  }

  if (!bError)
  {
    if (iWrk < 1 || iWrk>100)
      bError = true;
  }
  if (bError)
  {
    astError.printf("Ошибка!!! Ошибка значения dT (1..100) для датчика N: %d, Значение: %d(%s) ", iRow, iWrk, astWrk1);
    Application->MessageBox(astError.c_str(), NULL, MB_OK);
    edtdT->SetFocus();
    return false;
  }
  btdT = (BYTE)iWrk;

  astWrk1 = edtTmax->Text;
  try
  {
    iWrk = astWrk1.ToInt();
  }
  catch(EConvertError &e)
  {
    bError = true;
  }

  if (!bError)
  {
    if (iWrk < -127 || iWrk>128)
      bError = true;
  }
  if (bError)
  {
    astError.printf("Ошибка!!! Ошибка значения Tmax (-127..128) для датчика N: %d", iRow);
    Application->MessageBox(astError.c_str(), NULL, MB_OK);
    edtTmax->SetFocus();
    return false;
  }
  btTmax = (BYTE)iWrk;
  return true;
}
//---------------------------------------------------------------------------
bool TfrmIDWrkForm::CheckAddr(void)
{ //---
  if(!CheckAddrPart(edtAddr00, 0)) return false;
  if(!CheckAddrPart(edtAddr01, 1)) return false;
  if(!CheckAddrPart(edtAddr02, 2)) return false;
  if(!CheckAddrPart(edtAddr03, 3)) return false;
  if(!CheckAddrPart(edtAddr04, 4)) return false;
  if(!CheckAddrPart(edtAddr05, 5)) return false;
  if(!CheckAddrPart(edtAddr06, 6)) return false;
  if(!CheckAddrPart(edtAddr07, 7)) return false;
  return true;
}

bool TfrmIDWrkForm::CheckAddrPart(TEdit *a_pedtWrk, int a_idx)
{
  AnsiString astWrk1;
  AnsiString astError;
  int iWrk;
  astWrk1 = a_pedtWrk->Text;
  bool bError;
  bError = false;
  try
  {
    iWrk = astWrk1.ToInt();
  }
  catch(EConvertError &e)
  {
    bError = true;
  }

  if (!bError)
  {
    if (iWrk < 0 || iWrk>255)
      bError = true;
  }
  if (bError)
  {
    astError.printf("Ошибка!!! Ошибка части адреса(0..255) для датчика N: %d", iRow);
    Application->MessageBox(astError.c_str(), NULL, MB_OK);
    a_pedtWrk->SetFocus();
    return false;
  }
  btAddr[a_idx] = (BYTE)iWrk;
  return true;
}

void __fastcall TfrmIDWrkForm::btnDeleteIDClick(TObject *Sender)
{
  for (int i=0; i< 8; i++)
  {
    btAddr[i] = (BYTE)0xFF;
  }
  edtAddr00->Text = "0xFF";
  edtAddr01->Text = "0xFF";
  edtAddr02->Text = "0xFF";
  edtAddr03->Text = "0xFF";
  edtAddr04->Text = "0xFF";
  edtAddr05->Text = "0xFF";
  edtAddr06->Text = "0xFF";
  edtAddr07->Text = "0xFF";
  if(!CheckT())
    return;

  if(SyncFromUI())
  {
    pWrkObj->bCfgChanged = true;
  }

  Close();

}
//---------------------------------------------------------------------------

