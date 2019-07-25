//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//--------------------------------------------------------------------- 
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
AnsiString s=Application->ExeName;
DWORD tmp,len=GetFileVersionInfoSize(s.c_str(),&tmp);
void* str=0;
UINT count;
void * ver=new char[len];
GetFileVersionInfo(s.c_str(),0,len,ver);
VerQueryValue(ver,TEXT("\\StringFileInfo\\041904E3\\ProductName"),&str,&count);
//ProductName->Caption=("Название: "+AnsiString((char*)str,count));
VerQueryValue(ver,TEXT("\\StringFileInfo\\041904E3\\FileVersion"),&str,&count);
//Version->Caption=("Версия: "+AnsiString((char*)str,count));
VerQueryValue(ver,TEXT("\\StringFileInfo\\041904E3\\LegalCopyright"),&str,&count);
//Copyright->Caption=("Copyright: "+AnsiString((char*)str,count));
VerQueryValue(ver,TEXT("\\StringFileInfo\\041904E3\\Autor"),&str,&count);
//Autor->Caption=("Автор: "+AnsiString((char*)str,count));
VerQueryValue(ver,TEXT("\\StringFileInfo\\041904E3\\Comments"),&str,&count);

delete[] ver;

}
//---------------------------------------------------------------------

