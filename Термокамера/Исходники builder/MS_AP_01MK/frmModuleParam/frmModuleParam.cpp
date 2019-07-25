//---------------------------------------------------------------------------
       
#include <vcl.h>
#pragma hdrstop

#include "frmModuleParam.h"
#include "ms_ap_01mk_obj.h"
#include "frmIDWrk.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TfrmModuleParamForm *frmModuleParamForm;
//---------------------------------------------------------------------------
__fastcall TfrmModuleParamForm::TfrmModuleParamForm(TComponent* Owner, TAp01mkObj *a_pObjIn)
  : TForm(Owner)
{
  pgModuleWrkPage->ActivePageIndex = 0;
  pWrkObj = a_pObjIn;
  pWrkObj->SetModParamForm(this);
  pWrkObj->InitToEmptyCfg();
  InitBaseCtrls();
  
   #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" btnReadFromModuleClick - Start");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif
  if(pWrkObj->ReadCfgFromModule())
  {
    pWrkObj->bIsCfg = true;
    SyncCfgToUI();
   // pnlStatText->Caption = " Конфигурация загружена из модуля!";
  //  Application->MessageBoxA("Конфигурация загружена из модуля", Application->Title.c_str( ),MB_OK|MB_ICONWARNING);

  }

   // pnlStatText->Caption = " ОШИБКА!!! Ошибка загрузки конфигурации из модуля";

  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" btnReadFromModuleClick - End");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif
  }
/////////////////

 /////////////////


void TfrmModuleParamForm::InitBaseCtrls(void)
{
  ctrlBaseDatCtrl[etbcGbDat][0] = (TControl *)gbDat01;      ctrlBaseDatCtrl[etbcBtnReset][0] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][0] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][0] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][0] = (TControl *)pnlTemp01;  ctrlBaseDatCtrl[etbcLblT][0] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][0] = (TControl *)lblC01;

  ctrlBaseDatCtrl[etbcGbDat][1] = (TControl *)gbDat02;      ctrlBaseDatCtrl[etbcBtnReset][1] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][1] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][1] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][1] = (TControl *)pnlTemp02;  ctrlBaseDatCtrl[etbcLblT][1] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][1] = (TControl *)lblC02;

  ctrlBaseDatCtrl[etbcGbDat][2] = (TControl *)gbDat03;      ctrlBaseDatCtrl[etbcBtnReset][2] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][2] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][2] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][2] = (TControl *)pnlTemp03;  ctrlBaseDatCtrl[etbcLblT][2] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][2] = (TControl *)lblC03;

  ctrlBaseDatCtrl[etbcGbDat][3] = (TControl *)gbDat04;      ctrlBaseDatCtrl[etbcBtnReset][3] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][3] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][3] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][3] = (TControl *)pnlTemp04;  ctrlBaseDatCtrl[etbcLblT][3] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][3] = (TControl *)lblC04;

  ctrlBaseDatCtrl[etbcGbDat][4] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][4] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][4] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][4] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][4] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][4] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][4] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][5] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][5] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][5] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][5] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][5] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][5] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][5] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][6] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][6] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][6] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][6] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][6] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][6] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][6] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][7] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][7] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][7] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][7] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][7] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][7] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][7] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][8] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][8] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][8] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][8] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][8] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][8] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][8] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][9] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][9] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][9] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][9] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][9] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][9] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][9] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][10] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][10] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][10] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][10] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][10] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][10] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][10] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][11] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][11] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][11] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][11] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][11] = (TControl *)pnlTemp05; ctrlBaseDatCtrl[etbcLblT][11] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][11] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][12] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][12] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][12] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][12] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][12] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][12] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][12] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][13] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][13] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][13] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][13] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][13] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][13] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][13] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][14] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][14] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][14] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][14] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][14] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][14] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][14] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][15] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][15] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][15] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][15] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][15] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][15] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][15] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][16] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][16] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][16] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][16] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][16] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][16] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][16] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][17] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][17] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][17] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][17] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][17] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][17] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][17] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][18] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][18] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][18] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][18] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][18] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][18] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][18] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][19] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][19] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][19] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][19] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][19] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][19] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][19] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][20] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][20] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][20] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][20] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][20] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][20] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][20] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][21] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][21] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][21] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][21] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][21] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][21] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][21] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][22] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][22] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][22] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][22] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][22] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][22] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][22] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][23] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][23] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][23] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][23] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][23] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][23] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][23] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][24] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][24] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][24] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][24] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][24] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][24] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][24] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][25] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][25] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][25] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][25] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][25] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][25] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][25] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][26] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][26] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][26] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][26] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][26] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][26] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][26] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][27] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][27] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][27] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][27] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][27] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][27] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][27] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][28] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][28] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][28] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][28] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][28] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][28] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][28] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][29] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][29] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][29] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][29] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][29] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][29] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][29] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][30] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][30] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][30] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][30] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][30] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][30] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][30] = (TControl *)lblC05;

  ctrlBaseDatCtrl[etbcGbDat][31] = (TControl *)gbDat05;      ctrlBaseDatCtrl[etbcBtnReset][31] = (TControl *)btnReset05;
  ctrlBaseDatCtrl[etbcPnlTmax][31] = (TControl *)pnlTmax05;  ctrlBaseDatCtrl[etbcPnlDT][31] = (TControl *)pnldT05;
  ctrlBaseDatCtrl[etbcPnlTemp][31] = (TControl *)pnlTemp05;  ctrlBaseDatCtrl[etbcLblT][31] = (TControl *)lblT05;
  ctrlBaseDatCtrl[etbclblC][31] = (TControl *)lblC05;
 // sgrdDat->Cells[2][1]=IntToStr(CSpinEdit1->Value);

}

//---------------------------------------------------------------------------

void __fastcall TfrmModuleParamForm::FormShow(TObject *Sender)
{
//  AnsiString astWrk;
  sgrdDat->Cells[0][0] = "N";
  sgrdDat->Cells[1][0] = "ID";
  sgrdDat->Cells[2][0] = "Tmax";
  sgrdDat->Cells[3][0] = "dT";
  for (int i=1; i<=32;i++)
  {
    sgrdDat->Cells[0][i] = IntToStr(i);
  }
  cbxLineNumb->ItemIndex = 0;
  SyncToUILineParam(cbxLineNumb->ItemIndex);
  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" FormShow");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif
  ////////////////////////////////
  StaticText1->Caption=sgrdDat->Cells[2][1] ;
  StaticText2->Caption=sgrdDat->Cells[3][1] ;
  ///////////////////////////////////////
  pgModuleWrkPage->ActivePageIndex=1;
   pWrkObj->SetBGetStatMode(!pWrkObj->GetBGetStatMode());
}
//---------------------------------------------------------------------------



void __fastcall TfrmModuleParamForm::btnCfgSaveToDiskClick(TObject *Sender)
{
  AnsiString astWrkFile="c:\\testcfg.1mk";
  AnsiString astExt;
  if(dlgSave->Execute())
  { //--- Сохраняем конфигурацию
    astWrkFile = dlgSave->FileName;
    astExt=astWrkFile.SubString(astWrkFile.Length()-3,4);
    if (astExt != ".1mk")
      astWrkFile += ".1mk";
    SyncUIToCfg();
    if (pWrkObj->SaveCfgToFile(astWrkFile))
    {
      SetCfgStatus(false);
    }
    else
      Application->MessageBoxA("Error to save", Application->Title.c_str( ),MB_OK|MB_ICONERROR);
  }


}
//---------------------------------------------------------------------------

void __fastcall TfrmModuleParamForm::edtH104Exit(TObject *Sender)
{
  //--- Сохраняем значение в образе конфигурации.
  //----- Проверяем значение на валидность
  int iWrk;
  bool bError;
  AnsiString astError;
  astError = "Ошибка!!! Неправильное значение.\nЗначение должно быть в диапазоне 1-127.";
  bError = false;
  try
  {
    iWrk = edtH104->Text.ToInt();
  }
  catch(EConvertError &e)
  {
    bError = true;
  }

  if (!bError)
  {
    if (iWrk < 1 || iWrk>255)
    {
      bError = true;
    }
    else
    {//--- Сохраняем в образе.
      if (pWrkObj->SetWordDataInfo(etdiQryRetry, 0x0104, (WORD) iWrk) == false)
      {
        astError = "Ошибка!!! Ошибка сохранения значения по адресу 0x0104";
        bError = true;
      }
      else
      {
        SetCfgStatus(true);
      }

    }
  }

  if (bError)
  {
    Application->MessageBoxA(astError.c_str(), Application->Title.c_str( ),MB_OK|MB_ICONERROR);
    edtH104->Text = "2";
    edtH104->SetFocus();
    return;
  }

}

void TfrmModuleParamForm::SetCfgStatus(bool ab_Mode)
{
  if (pWrkObj->bCfgChanged != ab_Mode)
  {
    if (ab_Mode)
    {
      this->Caption = "Параметры.  Конфигурация изменена.";
      pWrkObj->bIsCfg = true;
    }
    else
      this->Caption = "Параметры.";
    pWrkObj->bCfgChanged = ab_Mode;
  }

}
//---------------------------------------------------------------------------

void __fastcall TfrmModuleParamForm::gbxTempExit(TObject *Sender)
{
  BYTE btWrk;
  bool bError;
  AnsiString astError;
  //--- Сохраняем параметры температуры
  bError = false;
  if (cbTempLine1->Checked == true)
    btWrk = 1;
  else
    btWrk = 0;

  if (pWrkObj->SetBitDataInfo(etdiLineCfg, 0x017f, btWrk, 0) == false)
  {
    astError = "Ошибка!!! Ошибка сохранения значения по адресу 0x017f бит 0";
    bError = true;
  }

  if (!bError)
  {
    if (cbTempLine2->Checked == true)
      btWrk = 1;
    else
      btWrk = 0;

    if (pWrkObj->SetBitDataInfo(etdiLineCfg, 0x017f, btWrk, 1) == false)
    {
      astError = "Ошибка!!! Ошибка сохранения значения по адресу 0x017f бит 1";
      bError = true;
    }
  }

  if (!bError)
  {
    if (cbTempLine3->Checked == true)
      btWrk = 1;
    else
      btWrk = 0;

    if (pWrkObj->SetBitDataInfo(etdiLineCfg, 0x017f, btWrk, 2) == false)
    {
      astError = "Ошибка!!! Ошибка сохранения значения по адресу 0x017f бит 2";
      bError = true;
    }
  }

  if (!bError)
  {
    if (cbTempLine4->Checked == true)
      btWrk = 1;
    else
      btWrk = 0;

    if (pWrkObj->SetBitDataInfo(etdiLineCfg, 0x017f, btWrk, 3) == false)
    {
      astError = "Ошибка!!! Ошибка сохранения значения по адресу 0x017f бит 3";
      bError = true;
    }
  }
  if (bError)
  {
    Application->MessageBoxA(astError.c_str(), Application->Title.c_str( ),MB_OK|MB_ICONERROR);
    return;
  }

}
//---------------------------------------------------------------------------

void __fastcall TfrmModuleParamForm::gbxTempSpeedExit(TObject *Sender)
{
  BYTE btWrk;
  bool bError;
  AnsiString astError;
  //--- Сохраняем параметры температуры
  bError = false;
  if (cbTempspeedLine1->Checked == true)
    btWrk = 1;
  else
    btWrk = 0;

  if (pWrkObj->SetBitDataInfo(etdiLineCfg, 0x017f, btWrk, 8) == false)
  {
    astError = "Ошибка!!! Ошибка сохранения значения по адресу 0x017f бит 8";
    bError = true;
  }

  if (!bError)
  {
    if (cbTempspeedLine2->Checked == true)
      btWrk = 1;
    else
      btWrk = 0;

    if (pWrkObj->SetBitDataInfo(etdiLineCfg, 0x017f, btWrk, 9) == false)
    {
      astError = "Ошибка!!! Ошибка сохранения значения по адресу 0x017f бит 9";
      bError = true;
    }
  }

  if (!bError)
  {
    if (cbTempspeedLine3->Checked == true)
      btWrk = 1;
    else
      btWrk = 0;

    if (pWrkObj->SetBitDataInfo(etdiLineCfg, 0x017f, btWrk, 10) == false)
    {
      astError = "Ошибка!!! Ошибка сохранения значения по адресу 0x017f бит 10";
      bError = true;
    }
  }

  if (!bError)
  {
    if (cbTempspeedLine4->Checked == true)
      btWrk = 1;
    else
      btWrk = 0;

    if (pWrkObj->SetBitDataInfo(etdiLineCfg, 0x017f, btWrk, 11) == false)
    {
      astError = "Ошибка!!! Ошибка сохранения значения по адресу 0x017f бит 11";
      bError = true;
    }
  }
  if (bError)
  {
    Application->MessageBoxA(astError.c_str(), Application->Title.c_str( ),MB_OK|MB_ICONERROR);
    return;
  }

}
//---------------------------------------------------------------------------
void __fastcall TfrmModuleParamForm::btnCfgWriteToModuleClick(
      TObject *Sender)
{


///////////////////////////////
 TfrmIDWrkForm *pfrmIDWrkForm;
  pfrmIDWrkForm = new TfrmIDWrkForm(NULL, pWrkObj, cbxLineNumb->ItemIndex,2,1);
  pfrmIDWrkForm->ShowModal();
  delete  pfrmIDWrkForm;



SyncUIToCfg();
   //  AnsiString astWrk;
  sgrdDat->Cells[0][0] = "N";
  sgrdDat->Cells[1][0] = "ID";
  sgrdDat->Cells[2][0] = "Tmax";
  sgrdDat->Cells[3][0] = "dT";
  for (int i=1; i<=32;i++)
  {
    sgrdDat->Cells[0][i] = IntToStr(i);
  }
  cbxLineNumb->ItemIndex = 0;
  SyncToUILineParam(cbxLineNumb->ItemIndex);
  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" FormShow");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif
    /////////////////////
    StaticText1->Caption=sgrdDat->Cells[2][1] ;
  StaticText2->Caption=sgrdDat->Cells[3][1] ;
   SyncUIToCfg();
  
  if (pWrkObj->WriteCfgToModule()){}
  
    
    /////////////////////



}
//---------------------------------------------------------------------------
void TfrmModuleParamForm::SyncUIToCfg()
{
  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" SyncUIToCfg - start");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif

  if (pgModuleWrkPage->ActivePageIndex == 0)
  {
    gbxTempSpeedExit(NULL);
    gbxTempExit(NULL);
    edtH104Exit(NULL);
  }
  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" SyncUIToCfg - End");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif
}

void TfrmModuleParamForm::SyncCfgToUI()
{
  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" SyncCfgToUI - start");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif
  if (pgModuleWrkPage->ActivePageIndex == 0)
  {
    SyncToUILineReg();
    SyncToUILineParam(cbxLineNumb->ItemIndex);
  }
  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" SyncCfgToUI - End");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif
}

void TfrmModuleParamForm::SyncToUILineReg()
{
  AnsiString astError, astWrk;
  bool bError;
  WORD wdWrk;
  BYTE btWrk;
//iWrk = edtH104->Text.ToInt();
  bError = false;

  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" SyncToUILineReg - start");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif

  if (pWrkObj->GetWordDataInfo(etdiQryRetry, 0x0104, &wdWrk) == false)
  {
    astError = "Ошибка!!! Ошибка чтения значения по адресу 0x0104";
    bError = true;
  }
  if (!bError)
  { //--- Нет ошибки, запоминаем в контроле
    astWrk.printf("%d", wdWrk);
    edtH104->Text = astWrk;
  }

  if (!bError)
  {
    if (pWrkObj->GetBitDataInfo(etdiLineCfg, 0x017f, &btWrk, 0) == false)
    {
      astError = "Ошибка!!! Ошибка чнения значения по адресу 0x017f бит 0";
      bError = true;
    }
  }
  if (!bError)
  {
    if (btWrk == 1)
      cbTempLine1->Checked = true;
    else
      cbTempLine1->Checked = false;
  }
  if (!bError)
  {
    if (pWrkObj->GetBitDataInfo(etdiLineCfg, 0x017f, &btWrk, 1) == false)
    {
      astError = "Ошибка!!! Ошибка чнения значения по адресу 0x017f бит 1";
      bError = true;
    }
  }
  if (!bError)
  {
    if (btWrk == 1)
      cbTempLine2->Checked = true;
    else
      cbTempLine2->Checked = false;
  }

  if (!bError)
  {
    if (pWrkObj->GetBitDataInfo(etdiLineCfg, 0x017f, &btWrk, 2) == false)
    {
      astError = "Ошибка!!! Ошибка чнения значения по адресу 0x017f бит 2";
      bError = true;
    }
  }
  if (!bError)
  {
    if (btWrk == 1)
      cbTempLine3->Checked = true;
    else
      cbTempLine3->Checked = false;
  }

  if (!bError)
  {
    if (pWrkObj->GetBitDataInfo(etdiLineCfg, 0x017f, &btWrk, 3) == false)
    {
      astError = "Ошибка!!! Ошибка чнения значения по адресу 0x017f бит 3";
      bError = true;
    }
  }
  if (!bError)
  {
    if (btWrk == 1)
      cbTempLine4->Checked = true;
    else
      cbTempLine4->Checked = false;
  }

  if (!bError)
  {
    if (pWrkObj->GetBitDataInfo(etdiLineCfg, 0x017f, &btWrk, 8) == false)
    {
      astError = "Ошибка!!! Ошибка чтения значения по адресу 0x017f бит 8";
      bError = true;
    }
  }
  if (!bError)
  {
    if (btWrk == 1)
      cbTempspeedLine1->Checked = true;
    else
      cbTempspeedLine1->Checked = false;
  }

  if (!bError)
  {
    if (pWrkObj->GetBitDataInfo(etdiLineCfg, 0x017f, &btWrk, 9) == false)
    {
      astError = "Ошибка!!! Ошибка чтения значения по адресу 0x017f бит 9";
      bError = true;
    }
  }
  if (!bError)
  {
    if (btWrk == 1)
      cbTempspeedLine2->Checked = true;
    else
      cbTempspeedLine2->Checked = false;
  }

  if (!bError)
  {
    if (pWrkObj->GetBitDataInfo(etdiLineCfg, 0x017f, &btWrk, 10) == false)
    {
      astError = "Ошибка!!! Ошибка чтения значения по адресу 0x017f бит 10";
      bError = true;
    }
  }
  if (!bError)
  {
    if (btWrk == 1)
      cbTempspeedLine3->Checked = true;
    else
      cbTempspeedLine3->Checked = false;
  }

  if (!bError)
  {
    if (pWrkObj->GetBitDataInfo(etdiLineCfg, 0x017f, &btWrk, 10) == false)
    {
      astError = "Ошибка!!! Ошибка чтения значения по адресу 0x017f бит 10";
      bError = true;
    }
  }
  if (!bError)
  {
    if (btWrk == 1)
      cbTempspeedLine3->Checked = true;
    else
      cbTempspeedLine3->Checked = false;
  }

  if (!bError)
  {
    if (pWrkObj->GetBitDataInfo(etdiLineCfg, 0x017f, &btWrk, 11) == false)
    {
      astError = "Ошибка!!! Ошибка чтения значения по адресу 0x017f бит 11";
      bError = true;
    }
  }
  if (!bError)
  {
    if (btWrk == 1)
      cbTempspeedLine4->Checked = true;
    else
      cbTempspeedLine4->Checked = false;
  }
  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" SyncToUILineReg - end");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif

}

void TfrmModuleParamForm::SyncToUILineParam(int a_iLineNumb)
{
  WORD wdIDStartAddr, wdTempStartAddr, wdWrk;
  int iOff, iCntAddr, iIdxLine, iAddrNotNull;
  BYTE btWrk1, btWrk2;
  bool bError;
  AnsiString astWrk1, astWrk2, astError;

  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" SyncToUILineParam - start LineNumb: %d", a_iLineNumb);
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif

  switch(a_iLineNumb)
  {
    case 0: wdIDStartAddr = 0x180; wdTempStartAddr = 0x380; break;
    case 1: wdIDStartAddr = 0x200; wdTempStartAddr = 0x3a0; break;
    case 2: wdIDStartAddr = 0x280; wdTempStartAddr = 0x3c0; break;
    case 3: wdIDStartAddr = 0x300; wdTempStartAddr = 0x3e0; break;
  };

  iOff = 0;
  for ( iIdxLine = 1; iIdxLine < 33; iIdxLine++)
  {
    //--- Адрес датчика
    astWrk1 = "";
    iAddrNotNull = 1;
    for (iCntAddr = 0; iCntAddr < 4; iCntAddr++)
    {

      if (pWrkObj->GetWordDataInfo(etdiLineCfg, wdIDStartAddr, &wdWrk) == false)
      {
        astError.printf("Ошибка!!! Ошибка чтения значения по адресу 0x%X",wdIDStartAddr);
        #ifdef DEBUG_WRITE_LOG
          pWrkObj->astLog.printf(" SyncToUILineParam - err LineNumb: %d Err: %s", a_iLineNumb, astError);
          pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
        #endif

        bError = true;
      }
      if (wdWrk >0 && iAddrNotNull == 0)
        iAddrNotNull = 2;
      pWrkObj->Word2TwoByte(wdWrk, &btWrk1, &btWrk2);
      astWrk2.printf("0x%0X 0x%0X", btWrk2, btWrk1);
      astWrk1 = astWrk2 + " "+astWrk1;
      wdIDStartAddr++;
    }
    sgrdDat->Cells[1][iIdxLine] = astWrk1;
    sgrdDat->Objects[0][iIdxLine] = (TObject *)iAddrNotNull;
    //--- Значения температуры и дельты
    if (pWrkObj->GetWordDataInfo(etdiLineCfg, wdTempStartAddr, &wdWrk) == false)
    {
      astError.printf("Ошибка!!! Ошибка чтения значения по адресу 0x%X",wdTempStartAddr);

      #ifdef DEBUG_WRITE_LOG
        pWrkObj->astLog.printf(" SyncToUILineParam - err LineNumb: %d Err: %s", a_iLineNumb, astError);
        pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
      #endif

      bError = true;
    }
    pWrkObj->Word2TwoByte(wdWrk, &btWrk1, &btWrk2);
    astWrk1.printf("%d", (signed char)btWrk1);
    astWrk2.printf("%d", (signed char)btWrk2);
    sgrdDat->Cells[2][iIdxLine] = astWrk1;
    sgrdDat->Cells[3][iIdxLine] = astWrk2;
    wdTempStartAddr++;
  }
  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" SyncToUILineParam - End ok LineNumb: %d ", a_iLineNumb);
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif


}

void TfrmModuleParamForm::SyncIDToGrid(void)
{
  WORD wdIDStartAddr, wdTempStartAddr, wdWrk;
  int iOff, iCntAddr, iIdxLine, iAddrNotNull;
  BYTE btWrk1, btWrk2;
  bool bError;
  AnsiString astWrk1, astWrk2, astError;

  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" SyncIDToGrid - Start");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif
  switch(cbxLineNumb->ItemIndex)
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
    if (pWrkObj->GetWordDataInfo(etdiLineCfg, wdIDStartAddr+iCntAddr+(sgrdDat->Row-1)*4, &wdWrk) == false)
    {
      astError.printf("Ошибка!!! Ошибка чтения значения по адресу 0x%X",wdIDStartAddr+iCntAddr+sgrdDat->Row-1);
      bError = true;
    }
      pWrkObj->Word2TwoByte(wdWrk, &btWrk1, &btWrk2);
      astWrk2.printf("0x%0X 0x%0X", btWrk2, btWrk1);

      astWrk1 = astWrk2 + " "+astWrk1;

  }
  sgrdDat->Cells[1][sgrdDat->Row] = astWrk1;

  //--- Значения температуры и дельты
  if (pWrkObj->GetWordDataInfo(etdiLineCfg, wdTempStartAddr+sgrdDat->Row-1, &wdWrk) == false)
  {
    astError.printf("Ошибка!!! Ошибка чтения значения по адресу 0x%X",wdTempStartAddr+sgrdDat->Row-1);
    bError = true;
  }
  pWrkObj->Word2TwoByte(wdWrk, &btWrk1, &btWrk2);
  astWrk1.printf("%d", (signed char)btWrk1);
  astWrk2.printf("%d", (signed char)btWrk2);
  sgrdDat->Cells[2][sgrdDat->Row] = astWrk1;
  sgrdDat->Cells[3][sgrdDat->Row] = astWrk2;

  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" SyncIDToGrid - End");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif

}

void __fastcall TfrmModuleParamForm::btnCfgOpenFromDiskClick(
      TObject *Sender)
{
  AnsiString astWrkFile="c:\\testcfg.1mk";

  if(dlgOpen->Execute())
  { //--- Сохраняем конфигурацию
    astWrkFile = dlgOpen->FileName;
    if (pWrkObj->LoadCfgFromFile(astWrkFile))
    {
      SyncCfgToUI();
      pWrkObj->bIsCfg = true;
    }
    else
      Application->MessageBoxA("ОШИБКА!!! Ошибка загрузки файла", Application->Title.c_str( ),MB_OK|MB_ICONERROR);
  }

}
//---------------------------------------------------------------------------




void TfrmModuleParamForm::SaveLineParamFromUI(int a_iLineNumb)
{
/*
  WORD wdIDStartAddr, wdTempStartAddr, wdWrk;
  int iIdxLine, iWrk, iAddrNotNull;
  BYTE btWrk1, btWrk2;
  bool bError;
  AnsiString astWrk1, astWrk2, astError;
  bError = false;
  switch(a_iLineNumb)
  {
    case 0: wdIDStartAddr = 0x180; wdTempStartAddr = 0x380; break;
    case 1: wdIDStartAddr = 0x200; wdTempStartAddr = 0x3a0; break;
    case 2: wdIDStartAddr = 0x280; wdTempStartAddr = 0x3c0; break;
    case 3: wdIDStartAddr = 0x300; wdTempStartAddr = 0x3e0; break;
  };

  for ( iIdxLine = 1; iIdxLine < 33; iIdxLine++)
  {
    //--- Tmax
    astWrk1 = sgrdDat->Cells[2][iIdxLine];
    iAddrNotNull = (WORD)sgrdDat->Objects[0][iIdxLine];
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
      astError.printf("Ошибка!!! Ошибка значения Tmax (-127..128) для датчика N: %d", iIdxLine);
      Application->MessageBox(astError.c_str(), NULL, MB_OK);
      if (iAddrNotNull == 2)
      {
        sgrdDat->Row = iIdxLine;
        sgrdDat->Col = 2;
        sgrdDat->SetFocus();
        return;
      }
    }

    btWrk1 = (BYTE)iWrk;

    //--- dT
    astWrk1 = sgrdDat->Cells[3][iIdxLine];
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
      astError.printf("Ошибка!!! Ошибка значения dT (1..100) для датчика N: %d", iIdxLine);
      Application->MessageBox(astError.c_str(), NULL, MB_OK);
      if (iAddrNotNull == 2)
      {
        sgrdDat->Row = iIdxLine;
        sgrdDat->Col = 3;
        sgrdDat->SetFocus();
        return;
      }
    }

    btWrk2 = (BYTE)iWrk;

    pWrkObj->TwoByte2Word(btWrk1, btWrk2, &wdWrk);

    //--- Запись температуры и дельты
    if (pWrkObj->SetWordDataInfo(etdiLineCfg, wdTempStartAddr, wdWrk) == false)
    {
      astError.printf("Ошибка!!! Ошибка записи значения по адресу 0x%X",wdTempStartAddr);
      bError = true;
      Application->MessageBox(astError.c_str(), NULL, MB_OK);
      return;
    }

    wdTempStartAddr++;
  }
  */
}

void __fastcall TfrmModuleParamForm::cbxLineNumbChange(TObject *Sender)
{
  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" cbxLineNumbChange - Start");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif
  
//  if (pgModuleWrkPage->ActivePageIndex == 0)
//  {
    if (pWrkObj->GetBMicrolanMode())
      pWrkObj->SetBMicrolanMode(false);
    SyncToUILineParam(cbxLineNumb->ItemIndex);
    rgWrkLine->ItemIndex = cbxLineNumb->ItemIndex;
//  }
  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" cbxLineNumbChange - End");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif

}
//---------------------------------------------------------------------------

void __fastcall TfrmModuleParamForm::btnReadFromModuleClick(TObject *Sender)
{
  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" btnReadFromModuleClick - Start");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif
  if(pWrkObj->ReadCfgFromModule())
  {
    pWrkObj->bIsCfg = true;
    SyncCfgToUI();
   // pnlStatText->Caption = " Конфигурация загружена из модуля!";
    Application->MessageBoxA("Конфигурация загружена из модуля", Application->Title.c_str( ),MB_OK|MB_ICONWARNING);

  }
 // else
   // pnlStatText->Caption = " ОШИБКА!!! Ошибка загрузки конфигурации из модуля";

  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" btnReadFromModuleClick - End");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif

}
//---------------------------------------------------------------------------

void __fastcall TfrmModuleParamForm::pnlConfigMicrolanClick(
      TObject *Sender)
{
sgrdDat->Visible=true;
  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" pnlConfigMicrolanClick - Start");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif
  pWrkObj->SetBMicrolanMode(!pWrkObj->GetBMicrolanMode());

  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" pnlConfigMicrolanClick - End");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif

}
//---------------------------------------------------------------------------

void __fastcall TfrmModuleParamForm::TimMicroLanTimer(TObject *Sender)
{
  WORD wdID_1[4], wdID_2[4];
  int iFreeID, iLineNumb;
  AnsiString astWrk;
  bool bTwoPass, bIsFind, bExit, bID_OK;

  TimMicroLan->Enabled = false;

  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" TimMicroLanTimer - Start");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif
  for (iLineNumb = 0; iLineNumb < 4; iLineNumb++)
  {
    if( pWrkObj->bCfgLineFull[0] &&  pWrkObj->bCfgLineFull[1] &&
           pWrkObj->bCfgLineFull[2] &&  pWrkObj->bCfgLineFull[3])
    {
      //--- Нет ниодного датчика свободного
        #ifdef DEBUG_WRITE_LOG
          pWrkObj->astLog.printf(" TimMicroLanTimer - pWrkObj->SetBMicrolanMode(false) - #1");
          pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
        #endif
        pWrkObj->SetBMicrolanMode(false);
        astWrk.printf("Все шлейфы заполнены датчиками. Режим конфигурирования закончен", iLineNumb+1, iFreeID+1);
        Application->MessageBoxA(astWrk.c_str(), Application->Title.c_str( ),MB_OK|MB_ICONWARNING);

        return;
    }
    if ( pWrkObj->bCfgLineFull[iLineNumb])
      continue;
    if (pWrkObj->GetBMicrolanMode())
    { //--- Пока находимся в режиме конфигурирования
      //--- Первоначально у нас есть информация о всех датчиках на шлейфе.
      iFreeID = -1;
      for(int i=0; i<32; i++)
      { //--- находим первый свободный датчик
        if(pWrkObj->etpsCfgID[iLineNumb][i] == etpsFalse)
        {
          iFreeID = i;
          break;
        }
      }

      if (iFreeID == -1)
      { //--- Нет ниодного датчика свободного, на данном шлейфе
        pWrkObj->bCfgLineFull[iLineNumb]=true;
        continue;
      }

      #ifdef DEBUG_WRITE_LOG
        pWrkObj->astLog.printf(" TimMicroLanTimer - iFreeID - #2", iFreeID);
        pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
      #endif

      //--- С этого ID начинаем опрос. После нахождения ID запускаем таймер заново
      pWrkObj->iMBPassPoll=0;
      bTwoPass = false;
      bExit = false;
      bID_OK = false;
      pWrkObj->iMBPassPoll = 0;
      while(pWrkObj->iMBPassPoll < 2)
      {
        #ifdef DEBUG_WRITE_LOG
          pWrkObj->astLog.printf(" TimMicroLanTimer - iFreeID - #3", iFreeID);
          pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
        #endif

        if(!pWrkObj->GetBMicrolanMode())
          return;
        //--- Выводим ID.
        pWrkObj->iMBPassPoll++;
        astWrk.printf(" Find ID №%02d - %02d - %d",iLineNumb+1, iFreeID+1, pWrkObj->iMBPassPoll);
      // pnlStatModRA->Caption = astWrk;
        Application->ProcessMessages();
        //--- Считываем ID из модуля.
        #ifdef DEBUG_WRITE_LOG
          pWrkObj->astLog.printf(" TimMicroLanTimer - iFreeID - #4", iFreeID);
          pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
        #endif
        if (!pWrkObj->ReadIDFromModuleToWDArr(iLineNumb, iFreeID, &wdID_1[0]))
        {
          pWrkObj->SetBMicrolanMode(false);
          return;
        }
        //--- Проверяем ID на номер
        #ifdef DEBUG_WRITE_LOG
          pWrkObj->astLog.printf(" TimMicroLanTimer - iFreeID - #5", iFreeID);
          pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
        #endif
        bIsFind = false;
        for(int i=0; i<4; i++)
        {
          if ((wdID_1[i] >0x0000)&&(wdID_1[i] < 0xFFFF))
          {
            bIsFind = true;
            break;
          }
        }
        #ifdef DEBUG_WRITE_LOG
          pWrkObj->astLog.printf(" TimMicroLanTimer - iFreeID - #6", iFreeID);
          pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
        #endif

        if (bIsFind)
        {
          #ifdef DEBUG_WRITE_LOG
            pWrkObj->astLog.printf(" TimMicroLanTimer - iFreeID - #4 bIsFind true", iFreeID);
            pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
          #endif
          if(!bTwoPass)
          { //--- Первый найден. копируем во второй массив
            for (int i=0; i<4;i++)
            {
              wdID_2[i] = wdID_1[i];
            }
            bTwoPass = true;
          }
          else
          { //--- Проверяем массивы и если ок, то будем искать следующий ID.
            //--- В любом случае выходим.
            #ifdef DEBUG_WRITE_LOG
              pWrkObj->astLog.printf(" TimMicroLanTimer - iFreeID - #4 bIsFind false", iFreeID);
              pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
            #endif

            bID_OK = true;
            bExit = true;
            for (int i=0; i<4; i++)
            {
              if( wdID_2[i] != wdID_1[i])
              {
                bID_OK = false;
                break;
              }
            }
          }
        }
      }
      //--- Вышли, смотрим каков результат
      if (bID_OK)
      { //--- Нашли, помечаем в масиве, и сохраняем в конфигурации.
        #ifdef DEBUG_WRITE_LOG
          pWrkObj->astLog.printf(" TimMicroLanTimer - iFreeID - #5 bID_OK true", iFreeID);
          pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
        #endif

        pWrkObj->etpsCfgID[iLineNumb][iFreeID] = etpsTrue;
        SaveIDToConfig(iLineNumb, iFreeID, &wdID_1[0]);
        if (iLineNumb == cbxLineNumb->ItemIndex)
        {
          SyncToUILineParam(cbxLineNumb->ItemIndex);
        }
        else
        {
          astWrk.printf("На шлейфе №%02d Найден датчик №%02d", iLineNumb+1, iFreeID+1);
          Application->MessageBoxA(astWrk.c_str(), Application->Title.c_str( ),MB_OK|MB_ICONWARNING);
        }
      }
    }
  }
  TimMicroLan->Interval = 100;
  TimMicroLan->Enabled = true;

  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf(" TimMicroLanTimer - End ok");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif

}
//---------------------------------------------------------------------------

void TfrmModuleParamForm::SetStatArr()
{
  AnsiString astWrk;
  int iColor;
  TGroupBox *pgbWrk;
  TPanel *ppnlWrk;
  //--- Читаем статусы и устанавливаем атрибуты
  if (pgModuleWrkPage->ActivePageIndex == 1)
  {
    astWrk.printf("Чтение статусов датчиков для шлейфа %d", rgWrkLine->ItemIndex);
   // pnlStatText->Caption = astWrk;

    #ifdef DEBUG_WRITE_LOG
      pWrkObj->astLog.printf(" SetStatArr - ReadIDSADTFromModuleAndSetBArr Line:%d", rgWrkLine->ItemIndex);
      pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
    #endif

    if (pWrkObj->ReadIDSADTFromModuleAndSetBArr(rgWrkLine->ItemIndex))
    { //--- Выводим  статусы

      for(int i=0; i<32; i++)
      {
        if (pWrkObj->etpsCfgID[rgWrkLine->ItemIndex][i] == etpsFalse)
        {
          continue;
        }

        #ifdef DEBUG_WRITE_LOG
          pWrkObj->astLog.printf(" SetStatArr - StatusOut Line:%d -#1- i: %d", rgWrkLine->ItemIndex, i);
          pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
        #endif

        pgbWrk = (TGroupBox *)ctrlBaseDatCtrl[etbcGbDat][i];
        ctrlBaseDatCtrl[etbcBtnReset][i]->Visible = false;
        if (pWrkObj->etpsStatID[rgWrkLine->ItemIndex][i] == etpsFalse)
        {
          pgbWrk->Font->Color = clRed;
//          continue;
        }
        else
        {
          pgbWrk->Font->Color = clGreen;
        }
        ppnlWrk = (TPanel *)ctrlBaseDatCtrl[etbcPnlTmax][i];
        if (pWrkObj->etpsAlarmID[rgWrkLine->ItemIndex][i] == etpsFalse)
        {
          ppnlWrk->Color = clGreen;
        }
        else
        {
          ppnlWrk->Color = clRed;
          ctrlBaseDatCtrl[etbcBtnReset][i]->Visible = true;
        }

        ppnlWrk = (TPanel *)ctrlBaseDatCtrl[etbcPnlDT][i];
        if (pWrkObj->etpsDeltaID[rgWrkLine->ItemIndex][i] == etpsFalse)
        {
          ppnlWrk->Color = clGreen;
        }
        else
        {
          ppnlWrk->Color = clRed;
          ctrlBaseDatCtrl[etbcBtnReset][i]->Visible = true;
        }
      }
      //--- Регистр статуса сигнализатора
      #ifdef DEBUG_WRITE_LOG
        pWrkObj->astLog.printf("SetStatArr - RegStatSignals Line:%d -#2- ", rgWrkLine->ItemIndex);
        pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
      #endif
      if (pWrkObj->etpsSignalRegStatus[0] == etpsTrue)
        pnlSignalRegStatus0->Font->Color = clRed;
      else
        pnlSignalRegStatus0->Font->Color = clGray;

      if (pWrkObj->etpsSignalRegStatus[1] == etpsTrue)
        pnlSignalRegStatus1->Font->Color = clRed;
      else
        pnlSignalRegStatus1->Font->Color = clGray;

      if (pWrkObj->etpsSignalRegStatus[2] == etpsTrue)
        pnlSignalRegStatus2->Font->Color = clRed;
      else
        pnlSignalRegStatus2->Font->Color = clGray;

      if (pWrkObj->etpsSignalRegStatus[3] == etpsTrue)
        pnlSignalRegStatus3->Font->Color = clRed;
      else
        pnlSignalRegStatus3->Font->Color = clGray;

      if (pWrkObj->etpsSignalRegStatus[8] == etpsTrue)
        pnlSignalRegStatus8->Font->Color = clRed;
      else
        pnlSignalRegStatus8->Font->Color = clGray;
    }
    else //--- Ошибка чтения регистра
    {
      #ifdef DEBUG_WRITE_LOG
        pWrkObj->astLog.printf("SetStatArr - Err read reg Line:%d -#3 - ", rgWrkLine->ItemIndex);
        pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
      #endif

      pWrkObj->SetBGetStatMode(false);
    }
  }
  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf("SetStatArr - End Ok Line:%d -#4- ", rgWrkLine->ItemIndex);
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif

}

void __fastcall TfrmModuleParamForm::pnlGetSostClick(TObject *Sender)
{
  //--- Устанавдиваем Режим опроса на противоположный
  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf("pnlGetSostClick - Start -");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif

  pWrkObj->SetBGetStatMode(!pWrkObj->GetBGetStatMode());

}

//---------------------------------------------------------------------------
void __fastcall TfrmModuleParamForm::timGetStatModeTimer(TObject *Sender)
{
  TPanel *ppnlWrk;
  AnsiString astWrk;
  int iLineNumb;
  timGetStatMode->Enabled = false;
  if (pWrkObj->GetBGetStatMode())
  { //--- Режим работы опрос состояния. опрашиваем значение температуры
    #ifdef DEBUG_WRITE_LOG
      pWrkObj->astLog.printf("timGetStatModeTimer - Start -");
      pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
    #endif

    if (!pWrkObj->bIsIDReg[0] && !pWrkObj->bIsIDReg[1])
    {
    #ifdef DEBUG_WRITE_LOG
      pWrkObj->astLog.printf("timGetStatModeTimer - Err #1");
      pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
    #endif
      pWrkObj->SetBGetStatMode(false);
      return;
    }
    if (pWrkObj->iCurrTempID == 0)
    {
      pWrkObj->iMBPassPoll++;
      SetStatArr();
    }
    //--- Проходим все датчики на шлейфе, и потом даем пользователю что-то нажать
    iLineNumb = rgWrkLine->ItemIndex;
    for (; pWrkObj->iCurrTempID < 32; pWrkObj->iCurrTempID++)
    {
      if (!pWrkObj->GetBGetStatMode())
      { //--- Режим работы опрос состояния. опрашиваем значение температуры
        return;
      }
      ppnlWrk = (TPanel *)ctrlBaseDatCtrl[etbcPnlTemp][pWrkObj->iCurrTempID];
      if (pWrkObj->etpsCfgID[iLineNumb][pWrkObj->iCurrTempID] == etpsTrue &&
            pWrkObj->etpsStatID[iLineNumb][pWrkObj->iCurrTempID] == etpsTrue)
      {
        #ifdef DEBUG_WRITE_LOG
          pWrkObj->astLog.printf("timGetStatModeTimer - ID: %d Pass: %d  -", pWrkObj->iCurrTempID+1, pWrkObj->iMBPassPoll);
          pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
        #endif

        astWrk.printf("ID №%02d - %d", pWrkObj->iCurrTempID+1, pWrkObj->iMBPassPoll);
      pnlStatModRA1->Caption = astWrk;
        Application->ProcessMessages();
        if (pWrkObj->ReadIDTempFromModule(rgWrkLine->ItemIndex, pWrkObj->iCurrTempID))
        { //--- Выводим данные
          #ifdef DEBUG_WRITE_LOG
            pWrkObj->astLog.printf("timGetStatModeTimer - Out Data ID: %d Pass: %d  -", pWrkObj->iCurrTempID+1, pWrkObj->iMBPassPoll);
            pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
          #endif

          if (pWrkObj->etpsTemIDCorrect[iLineNumb][pWrkObj->iCurrTempID]== etpsTrue)
          {
            ppnlWrk->Font->Color = clBlack;
            astWrk.printf("%d", (signed char)(pWrkObj->iTempID[iLineNumb][pWrkObj->iCurrTempID]/2));
            ppnlWrk->Caption = astWrk;
          }
          else
            ppnlWrk->Font->Color = clGray;
        }
        else
        {
          #ifdef DEBUG_WRITE_LOG
            pWrkObj->astLog.printf("timGetStatModeTimer - Error Read ID: %d Pass: %d  -", pWrkObj->iCurrTempID+1, pWrkObj->iMBPassPoll);
            pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
          #endif
          ppnlWrk->Font->Color = clGray;
          pWrkObj->iCurrTempID++;
          pWrkObj->SetBGetStatMode(false);
          return;
        }
      }
      else
      {
          astWrk.printf("ID     - %d", pWrkObj->iMBPassPoll);
      //   pnlStatModRA->Caption = astWrk;
          Application->ProcessMessages();

      }
    }
    if (pWrkObj->iCurrTempID > 31)
      pWrkObj->iCurrTempID = 0;
    timGetStatMode->Interval = 100;
    timGetStatMode->Enabled = true;

    #ifdef DEBUG_WRITE_LOG
      pWrkObj->astLog.printf("timGetStatModeTimer - End OK ID: %d Pass: %d  -", pWrkObj->iCurrTempID+1, pWrkObj->iMBPassPoll);
      pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
    #endif
  }
}
//---------------------------------------------------------------------------
void TfrmModuleParamForm::SetCfgIDArr(void)
{
  TGroupBox *pgbWrk;
  TPanel *ppnlWrk;
  if (pWrkObj->SetCfgIDArr(rgWrkLine->ItemIndex))
  {
    pWrkObj->iCurrTempID = 0;
    for(int i=0; i< 32; i++)
    {
      #ifdef DEBUG_WRITE_LOG
        pWrkObj->astLog.printf("SetCfgIDArr - Start ID: %d -", i);
        pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
      #endif
      pgbWrk = (TGroupBox *)ctrlBaseDatCtrl[etbcGbDat][i];
      pgbWrk->Font->Color = clBlack;
      pgbWrk->Visible = true;

      if (pWrkObj->etpsCfgID[rgWrkLine->ItemIndex][i] == etpsFalse)
      {
        ctrlBaseDatCtrl[etbcBtnReset][i]->Visible = false;
        ctrlBaseDatCtrl[etbcPnlTmax][i]->Visible = false;
        ctrlBaseDatCtrl[etbcPnlDT][i]->Visible = false;
        ctrlBaseDatCtrl[etbcPnlTemp][i]->Visible = false;
        ctrlBaseDatCtrl[etbcLblT][i]->Visible = false;
        ctrlBaseDatCtrl[etbclblC][i]->Visible = false;
      }
      else
      {
        ctrlBaseDatCtrl[etbcBtnReset][i]->Visible = true;
        ppnlWrk =(TPanel *)ctrlBaseDatCtrl[etbcPnlTmax][i];
        ppnlWrk->Visible = true;
        ppnlWrk->Color = clBtnFace;

        ppnlWrk =(TPanel *)ctrlBaseDatCtrl[etbcPnlDT][i];
        ppnlWrk->Visible = true;
        ppnlWrk->Color = clBtnFace;

        ppnlWrk =(TPanel *)ctrlBaseDatCtrl[etbcPnlTemp][i];
        ppnlWrk->Visible = true;
        ppnlWrk->Color = clBtnFace;
        ppnlWrk->Caption = "-";
        ppnlWrk->Font->Color = clBlack;

        ctrlBaseDatCtrl[etbcLblT][i]->Visible = true;
        ctrlBaseDatCtrl[etbclblC][i]->Visible = true;

      }
    }
  }
  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf("SetCfgIDArr - End OK -");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif

}

void __fastcall TfrmModuleParamForm::tbsModuleBaseShow(TObject *Sender)
{
  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf("tbsModuleBaseShow - Start -");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif
  rgWrkLine->ItemIndex = cbxLineNumb->ItemIndex;
  if (pWrkObj->GetBMicrolanMode())
  {
     pWrkObj->SetBMicrolanMode(false);
  }
  SetCfgIDArr();

  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf("tbsModuleBaseShow - End -");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif

}
//---------------------------------------------------------------------------

void __fastcall TfrmModuleParamForm::rgWrkLineClick(TObject *Sender)
{
  if (pgModuleWrkPage->ActivePageIndex == 1)
  {
    #ifdef DEBUG_WRITE_LOG
      pWrkObj->astLog.printf("rgWrkLineClick - Start -");
      pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
    #endif
    SetCfgIDArr();
    if (pWrkObj->GetBGetStatMode())
    {
      pnlGetSostClick(NULL);
    }
    cbxLineNumb->ItemIndex = rgWrkLine->ItemIndex;
    #ifdef DEBUG_WRITE_LOG
      pWrkObj->astLog.printf("rgWrkLineClick - End -");
      pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
    #endif
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmModuleParamForm::tbsCfgModuleShow(TObject *Sender)
{
  if (pWrkObj->GetBGetStatMode())
  {
    pnlGetSostClick(NULL);
  }
  cbxLineNumbChange(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmModuleParamForm::sgrdDatDblClick(TObject *Sender)
{
  TfrmIDWrkForm *pfrmIDWrkForm;
  pfrmIDWrkForm = new TfrmIDWrkForm(NULL, pWrkObj, cbxLineNumb->ItemIndex, sgrdDat->Col, sgrdDat->Row);
  pfrmIDWrkForm->ShowModal();
  delete  pfrmIDWrkForm;
  if (pWrkObj->bCfgChanged)
  {
    pWrkObj->bCfgChanged = true;
    SetCfgStatus(true);
    SyncIDToGrid();
  }

}
//---------------------------------------------------------------------------

void __fastcall TfrmModuleParamForm::btnReset01Click(TObject *Sender)
{
  AnsiString astWrk, astWrk2;
  TButton *pbtnWrk;
  WORD wdVal;
  int iNumb;
  pbtnWrk = (TButton *)Sender;
  astWrk = pbtnWrk->Name;
  astWrk2 = astWrk.SubString(astWrk.Length()-1, 2);
  iNumb = astWrk2.ToInt();
  if(pWrkObj->TwoByte2Word((BYTE)iNumb,(BYTE)rgWrkLine->ItemIndex, &wdVal))
  {
    if (!pWrkObj->ResetID(wdVal))
    {
      return;
    }
  }

}
//---------------------------------------------------------------------------
void TfrmModuleParamForm::SetPnlGetSost(bool a_bMode)
{ //--- Эта ф-ция вызавается только из pWrkObj->SetBGetStatMode.
  //--- Эта ф-ция управляет состояние кнопки опроса.
  AnsiString astWrk;

  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf("rgWrkLineClick - Start -");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif
  if (a_bMode)
  { //---
    pnlGetSost->BevelOuter = bvLowered;
    astWrk.printf("Запуск опроса состояния для датчиков шлейфа %d", rgWrkLine->ItemIndex);
    //pnlStatText->Caption = astWrk;

    #ifdef DEBUG_WRITE_LOG
      pWrkObj->astLog.printf("SetPnlGetSost - Mode == true -");
      pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
    #endif

  }
  else
  {
    pnlGetSost->BevelOuter = bvRaised;
    astWrk.printf("Останов опроса состояния для датчиков шлейфа %d", rgWrkLine->ItemIndex);
    //pnlStatText->Caption = astWrk;

    #ifdef DEBUG_WRITE_LOG
      pWrkObj->astLog.printf("SetPnlGetSost - Mode == false -");
      pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
    #endif

  }
}

void TfrmModuleParamForm::SetPnlConfigMicrolan(bool a_bMode)
{
  AnsiString astWrk;
  if (a_bMode)
  { //---
    pnlConfigMicrolan->BevelOuter = bvLowered;
    astWrk.printf("Запуск конфигурирования Microlan для датчиков шлейфа %d",cbxLineNumb->ItemIndex);
   // pnlStatText->Caption = astWrk;

    #ifdef DEBUG_WRITE_LOG
      pWrkObj->astLog.printf("SetPnlConfigMicrolan - Mode == true -");
      pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
    #endif

  }
  else
  {
    pnlConfigMicrolan->BevelOuter = bvRaised;
    astWrk.printf("Останов конфигурирования Microlan для датчиков шлейфа %d", cbxLineNumb->ItemIndex);
   // pnlStatText->Caption = astWrk;

    #ifdef DEBUG_WRITE_LOG
      pWrkObj->astLog.printf("SetPnlConfigMicrolan - Mode == false -");
      pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
    #endif
  }

}

bool TfrmModuleParamForm::SaveIDToConfig(int a_iLine, int a_IDNumb,WORD *a_pwdValArr)
{
  WORD wdIDStartAddr;
  int iOff, iCntAddr, iIdxLine, iAddrNotNull;
  BYTE btWrk1, btWrk2;
  bool bError;
  AnsiString astWrk1, astWrk2, astError;

  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf("SaveIDToConfig - Start a_iLine: %d,  a_IDNumb :%d, a_pwdValArr:%0X",a_iLine, a_IDNumb,*a_pwdValArr);
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif

  switch(a_iLine)
  {
    case 0: wdIDStartAddr = 0x180; break;
    case 1: wdIDStartAddr = 0x200; break;
    case 2: wdIDStartAddr = 0x280; break;
    case 3: wdIDStartAddr = 0x300; break;
  };
  iOff = 0;
  for (iCntAddr = 0; iCntAddr < 4; iCntAddr++)
  {
    if (pWrkObj->SetWordDataInfo(etdiLineCfg, wdIDStartAddr+iCntAddr+(a_IDNumb)*4, a_pwdValArr[iCntAddr]) == false)
    {
      astError.printf("Ошибка!!! Ошибка записи значения по адресу 0x%X",wdIDStartAddr+iCntAddr+(a_IDNumb)*4);
      bError = true;
      return false;
    }
  }
  return true;
}


void __fastcall TfrmModuleParamForm::Button3Click(TObject *Sender)
{
pgModuleWrkPage->ActivePageIndex=1;
//CSpinEdit1->Value=StrToInt(sgrdDat->Cells[2][1]) ;

 //--- Устанавдиваем Режим опроса на противоположный
  #ifdef DEBUG_WRITE_LOG
    pWrkObj->astLog.printf("pnlGetSostClick - Start -");
    pWrkObj->WriteLog("TfrmModuleParamForm",pWrkObj->astLog);
  #endif

  pWrkObj->SetBGetStatMode(!pWrkObj->GetBGetStatMode());

}
//---------------------------------------------------------------------------


void __fastcall TfrmModuleParamForm::CSpinEdit1Change(TObject *Sender)
{ /*char ss;
int _stdcall
init_comm('COM1',19200,2);
    */

}
//---------------------------------------------------------------------------





