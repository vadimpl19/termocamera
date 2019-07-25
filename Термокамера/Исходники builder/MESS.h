//---------------------------------------------------------------------------

#ifndef messH
#define messH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfMess : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
private:	// User declarations
public:		// User declarations
        __fastcall TfMess(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfMess *fMess;
//---------------------------------------------------------------------------
#endif
