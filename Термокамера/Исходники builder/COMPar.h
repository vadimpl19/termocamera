//---------------------------------------------------------------------------

#ifndef COMParH
#define COMParH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TAp01mkObj;
class TParCOM : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TButton *btOk;
        TButton *btCancel;
        TComboBox *cbPort;
        TComboBox *cbSpeed;
        TComboBox *cbParity;
        TEdit *edAddress;
        TLabel *Label4;
        TButton *Button1;
        TGroupBox *GroupBox1;
        TEdit *edNumber;
        TLabel *Label6;
        TButton *btAuto;
        TComboBox *cbSerNumAlpha;
        void __fastcall btOkClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall btAutoClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        TAp01mkObj *pWrkObj;
        __fastcall TParCOM(TComponent* Owner,TAp01mkObj *a_pObjIn);
};
//---------------------------------------------------------------------------
extern PACKAGE TParCOM *ParCOM;
//---------------------------------------------------------------------------
#endif
