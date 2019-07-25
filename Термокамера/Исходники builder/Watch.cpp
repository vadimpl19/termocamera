//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Watch.res");
USEFORM("main.cpp", Form1);
USEFORM("passw.cpp", Password);
USEFORM("COMPar.cpp", ParCOM);
USEFORM("ModulParams.cpp", ModPars);
USEFORM("Calib.cpp", Calibr1);
USEFORM("About.cpp", AboutBox);
USEUNIT("func.cpp");
USEFORM("mdata.cpp", ModData);
USEFORM("ChanPar.cpp", ChanPars);
USEUNIT("MS_AP_01MK\ms_ap_01mk_obj.cpp");
USEFORM("MS_AP_01MK\frmModuleParam\frmModuleParam.cpp", frmModuleParamForm);
USEFORM("MS_AP_01MK\frmIDWrk\frmIDWrk.cpp", frmIDWrkForm);
USEFORM("MESS.CPP", fMess);
USEUNIT("Init_Modb.cpp");
//---------------------------------------------------------------------------
bool LoadModb();
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        if(!LoadModb()) return 1;
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TPassword), &Password);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
