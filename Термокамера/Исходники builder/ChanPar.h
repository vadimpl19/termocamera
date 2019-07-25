//---------------------------------------------------------------------------

#ifndef ChanParH
#define ChanParH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <ExtCtrls.hpp>
const
USHORT
 mode=0x10A,
 range=0x110,
 modes=0x120;
//---------------------------------------------------------------------------
class TChanPars : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *sgRange;
        TStringGrid *sgModes;
        TButton *btRead;
        TButton *btWrite;
        TButton *btDef;
        TCheckBox *chbAll;
        TGroupBox *GroupBox1;
        TEdit *edRep;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TCheckBox *chbFire1;
        TCheckBox *chbFire2;
        TCheckBox *chbFire3;
        TCheckBox *chbPI4;
        TCheckBox *chbPI1;
        TCheckBox *chbFire4;
        TCheckBox *chbPI3;
        TCheckBox *chbPI2;
        TEdit *edTimeOut;
        TLabel *Label6;
        void __fastcall btWriteClick(TObject *Sender);
        void __fastcall btReadClick(TObject *Sender);
        void __fastcall btDefClick(TObject *Sender);
        void __fastcall sgSetEditText(TObject *Sender, int ACol,
          int ARow, const AnsiString Value);
        void __fastcall chbAllClick(TObject *Sender);
        void __fastcall chbFireClick(TObject *Sender);
        void __fastcall chbPIClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TChanPars(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TChanPars *ChanPars;
//---------------------------------------------------------------------------
#endif
