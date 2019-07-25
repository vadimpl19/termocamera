//---------------------------------------------------------------------------

#ifndef mdataH
#define mdataH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
const
 DWORD
 latch=0x10B,
 wire_status=0x400,
 wire_status_copy=0x10F,
 res_md=0x402
 ;

//---------------------------------------------------------------------------
class TModData : public TForm
{
__published:	// IDE-managed Components
        TTimer *tmRead;
        TCheckBox *CheckBox1;
        TButton *btRead;
        TGroupBox *GroupBox1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *lbWire1;
        TLabel *lbWire2;
        TLabel *lbWire3;
        TLabel *lbWire4;
        TButton *btRes1;
        TButton *btRes2;
        TButton *btRes3;
        TButton *btRes4;
        TLabel *lbCurrent1;
        TLabel *lbCurrent2;
        TLabel *lbCurrent3;
        TLabel *lbCurrent4;
        TGroupBox *GroupBox2;
        TGroupBox *GroupBox3;
        TLabel *lbSt0;
        TLabel *lbSt1;
        TLabel *lbSt2;
        TLabel *lbSt3;
        TLabel *lbSt4;
        TGroupBox *GroupBox5;
        TLabel *Label8;
        TLabel *Label9;
        TCheckBox *chbLatch2;
        TCheckBox *chbLatch3;
        TCheckBox *chbLatch4;
        TCheckBox *chbLatch1;
        TCheckBox *chbPI1;
        TCheckBox *chbPI2;
        TCheckBox *chbPI3;
        TCheckBox *chbPI4;
        void __fastcall tmReadTimer(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall btResClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TModData(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TModData *ModData;
//---------------------------------------------------------------------------
#endif
