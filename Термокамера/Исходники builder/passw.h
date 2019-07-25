//---------------------------------------------------------------------------

#ifndef passwH
#define passwH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TPassword : public TForm
{
__published:	// IDE-managed Components
        TEdit *edPass;
        TButton *btOK;
        TLabel *Label1;
        TLabel *Label2;
        void __fastcall btOKClick(TObject *Sender);
private:	// User declarations
         void CheckPassword(AnsiString&);
public:		// User declarations
        __fastcall TPassword(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPassword *Password;
//---------------------------------------------------------------------------
#endif
