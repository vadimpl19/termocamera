//---------------------------------------------------------------------------

#ifndef CalibH
#define CalibH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TCalibr1 : public TForm
{
__published:	// IDE-managed Components
        TButton *btCancel;
        TButton *btNext;
        TLabel *lbTip;
        TButton *btPrev;
        TEdit *edT;
        void __fastcall btPrevClick(TObject *Sender);
        void __fastcall btNextClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
        int num;
        void Display(int num);
public:		// User declarations
        __fastcall TCalibr1(TComponent* Owner);
       
};
//---------------------------------------------------------------------------
extern PACKAGE TCalibr1 *Calibr1;
//---------------------------------------------------------------------------
#endif
