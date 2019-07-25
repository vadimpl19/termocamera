//---------------------------------------------------------------------------

#ifndef ModulParamsH
#define ModulParamsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
const
USHORT
       check=0x100,
       adr=0x101,
       speed=0x102,
       parity_stopbits=0x103,

       type=0x0,
       num=0x1,
       manuf=0x2,
       ver=0x3
       ;
class TAp01mkObj;
class TModPars : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *gbModbPars;
        TGroupBox *gbPassport;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TComboBox *cbSpeed;
        TComboBox *cbParity;
        TEdit *edName;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TGroupBox *GroupBox3;
        TButton *btWrite;
        TButton *btRead;
        TButton *btDef;
        TMaskEdit *edManuf;
        TMaskEdit *edAdress;
        TEdit *edNumber;
        TEdit *edVer;
        TLabel *Label8;
        TComboBox *cbAlpha;
        void __fastcall btWriteClick(TObject *Sender);
        void __fastcall btReadClick(TObject *Sender);
        void __fastcall btDefClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        TAp01mkObj *pWrkObj;
        __fastcall TModPars(TComponent* Owner, TAp01mkObj *a_pObjIn);

};

//---------------------------------------------------------------------------
extern PACKAGE TModPars *ModPars;
//---------------------------------------------------------------------------
#endif
