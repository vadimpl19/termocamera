//---------------------------------------------------------------------------

#ifndef frmModuleParamH
#define frmModuleParamH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
enum TypeBaseCtrl {etbcGbDat=0, etbcBtnReset=1, etbcPnlTmax=2, etbcPnlDT=3,
                    etbcPnlTemp=4, etbcLblT=5, etbclblC=6, etbcCount=7};
class TAp01mkObj;
class TfrmModuleParamForm : public TForm
{
__published:	// IDE-managed Components
  TPageControl *pgModuleWrkPage;
  TTabSheet *tbsCfgModule;
  TTabSheet *tbsModuleBase;
  TPanel *pnlCfgClient;
  TPanel *pnlCfgModLeft;
  TPanel *pnlCfgModBtn;
  TButton *btnCfgOpenFromDisk;
  TButton *btnCfgSaveToDisk;
  TButton *btnCfgWriteToModule;
  TButton *btnReadFromModule;
  TPanel *pnlTopReg;
  TPanel *Panel1;
  TGroupBox *gbxTempSpeed;
  TCheckBox *cbTempspeedLine1;
  TCheckBox *cbTempspeedLine2;
  TCheckBox *cbTempspeedLine3;
  TCheckBox *cbTempspeedLine4;
  TGroupBox *gbxTemp;
  TCheckBox *cbTempLine1;
  TCheckBox *cbTempLine2;
  TCheckBox *cbTempLine3;
  TCheckBox *cbTempLine4;
  TPanel *Panel2;
  TLabel *Label1;
  TPanel *pnlCfgMon;
  TRadioGroup *rgWrkLine;
  TPanel *pnlWrkLineClient;
  TPanel *pnlSignalRegStatus0;
  TPanel *pnlSignalRegStatus1;
  TPanel *pnlSignalRegStatus3;
  TPanel *pnlSignalRegStatus2;
  TPanel *pnlSignalRegStatus8;
  TLabel *Label3;
  TLabel *Label4;
  TLabel *Label5;
  TPanel *pnlGetSost;
  TLabel *Label6;
  TLabel *Label8;
  TLabel *Label7;
  TSaveDialog *dlgSave;
  TPanel *pnlCfgMonTop;
  TLabel *Label2;
  TComboBox *cbxLineNumb;
  TPanel *Panel106;
  TLabel *Label73;
  TEdit *edtH104;
  TTimer *TimMicroLan;
  TTimer *timGetStatMode;
  TOpenDialog *dlgOpen;
        TGroupBox *gbDat05;
        TLabel *lblT05;
        TLabel *lblC05;
        TPanel *pnldT05;
        TPanel *pnlTmax05;
        TButton *btnReset05;
        TPanel *pnlTemp05;
        TPanel *Panel4;
        TGroupBox *gbDat01;
        TLabel *lblC01;
        TPanel *pnlTemp01;
        TGroupBox *gbDat03;
        TLabel *lblC03;
        TPanel *pnlTemp03;
        TGroupBox *gbDat04;
        TLabel *lblC04;
        TPanel *pnlTemp04;
        TStringGrid *sgrdDat;
        TGroupBox *gbDat02;
        TLabel *lblC02;
        TPanel *pnlTemp02;
        TPanel *pnlConfigMicrolan;
        TLabel *Label76;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label13;
        TLabel *Label12;
        TLabel *Label14;
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TLabel *pnlStatModRA1;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall btnCfgSaveToDiskClick(TObject *Sender);
  void __fastcall edtH104Exit(TObject *Sender);
  void __fastcall gbxTempExit(TObject *Sender);
  void __fastcall gbxTempSpeedExit(TObject *Sender);
  void __fastcall btnCfgWriteToModuleClick(TObject *Sender);
  void __fastcall btnCfgOpenFromDiskClick(TObject *Sender);
  void __fastcall cbxLineNumbChange(TObject *Sender);
  void __fastcall btnReadFromModuleClick(TObject *Sender);
  void __fastcall pnlConfigMicrolanClick(TObject *Sender);
  void __fastcall TimMicroLanTimer(TObject *Sender);
  void __fastcall pnlGetSostClick(TObject *Sender);
  void __fastcall timGetStatModeTimer(TObject *Sender);
  void __fastcall tbsModuleBaseShow(TObject *Sender);
  void __fastcall rgWrkLineClick(TObject *Sender);
  void __fastcall tbsCfgModuleShow(TObject *Sender);
  void __fastcall sgrdDatDblClick(TObject *Sender);
  void __fastcall btnReset01Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall CSpinEdit1Change(TObject *Sender);
private:	// User declarations
  TAp01mkObj *pWrkObj;
  void SetCfgStatus(bool ab_Mode);
  void InitBaseCtrls(void);
  void SyncIDToGrid(void);
public:		// User declarations
  __fastcall TfrmModuleParamForm(TComponent* Owner, TAp01mkObj *a_pObjIn);
  TControl *ctrlBaseDatCtrl[etbcCount][32];
  void SyncUIToCfg();
  void SyncCfgToUI();
  void SyncToUILineReg();
  void SyncToUILineParam(int a_iLineNumb);
  void SaveLineParamFromUI(int a_iLineNumb);
  void SetStatArr();
  void SetCfgIDArr(void);
  void SetPnlGetSost(bool a_bMode);
  void SetPnlConfigMicrolan(bool a_bMode);
  bool SaveIDToConfig(int a_iLine, int a_IDNumb,WORD *a_pwdValArr);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmModuleParamForm *frmModuleParamForm;
//---------------------------------------------------------------------------
#endif

