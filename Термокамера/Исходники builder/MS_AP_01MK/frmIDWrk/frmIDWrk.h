//---------------------------------------------------------------------------

#ifndef frmIDWrkH
#define frmIDWrkH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TAp01mkObj;
class TfrmIDWrkForm : public TForm
{
__published:	// IDE-managed Components
  TGroupBox *gbIDAddr;
  TEdit *edtAddr07;
  TEdit *edtAddr06;
  TEdit *edtAddr05;
  TEdit *edtAddr04;
  TEdit *edtAddr03;
  TEdit *edtAddr02;
  TEdit *edtAddr01;
  TEdit *edtAddr00;
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Label3;
  TLabel *Label4;
  TLabel *Label5;
  TLabel *Label6;
  TLabel *Label7;
  TLabel *Label8;
  TButton *btnSave;
  TButton *btnCancel;
        TCSpinEdit *edtTmax;
        TPanel *Panel1;
        TCSpinEdit *edtdT;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall btnSaveClick(TObject *Sender);
  void __fastcall btnCancelClick(TObject *Sender);
  void __fastcall btnDeleteIDClick(TObject *Sender);
private:	// User declarations
  TAp01mkObj *pWrkObj;
  int iLine;
  int iColl;
  int iRow;
  BYTE btAddr[8];
  BYTE btTmax, btdT;
  void SyncToUI(void);
  bool SyncFromUI(void);
  bool CheckT(void);
  bool CheckAddr(void);
  bool CheckAddrPart(TEdit *a_pedtWrk, int a_idx);
public:		// User declarations
  __fastcall TfrmIDWrkForm(TComponent* Owner, TAp01mkObj *a_pObjIn, int a_iLine,int a_iWrkCol, int a_iWrkRow);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmIDWrkForm *frmIDWrkForm;
//---------------------------------------------------------------------------
#endif
