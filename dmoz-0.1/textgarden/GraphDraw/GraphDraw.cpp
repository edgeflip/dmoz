//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("GraphDraw.res");
USEFORM("GraphDrawM.cpp", GraphDrawF);
USEUNIT("..\..\GLib\base.cpp");
USEUNIT("..\..\GLib\graph.cpp");
USEUNIT("..\..\GLib\gks.cpp");
USEUNIT("..\..\GLib\gksvcl.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TGraphDrawF), &GraphDrawF);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
