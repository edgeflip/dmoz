//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Contexter.res");
USEFORM("ContexterM.cpp", ContexterF);
USEUNIT("..\..\GLib\base.cpp");
USEUNIT("..\..\GLib\mine.cpp");
USEUNIT("..\..\GLib\nmobj.cpp");
USEUNIT("..\..\GLib\graph.cpp");
USEUNIT("..\..\GLib\gks.cpp");
USEUNIT("..\..\GLib\gksvcl.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TContexterF), &ContexterF);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
