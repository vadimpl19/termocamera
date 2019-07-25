//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include "ms_ap_01mk_obj.h"
const
 USHORT
  term_reg=0x408,
  term_down=0x109;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *miComPar;
        TMenuItem *miModPar;
        TStatusBar *StatusBar1;
        TMenuItem *A1;
        void __fastcall miDataClick(TObject *Sender);
        void __fastcall miComParClick(TObject *Sender);
        void __fastcall mmAboutClick(TObject *Sender);
        void __fastcall miPassportClick(TObject *Sender);
        void __fastcall miModParClick(TObject *Sender);
        void __fastcall miCalibClick(TObject *Sender);
        void __fastcall miTermCalibClick(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall miSetModuleClick(TObject *Sender);
        void __fastcall A1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void IniStatusBar(bool stat);
        TAp01mkObj *pAp01mkObj;

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
