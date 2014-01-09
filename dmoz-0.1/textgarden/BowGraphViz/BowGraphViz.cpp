//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("BowGraphViz.res");
USEFORM("BowGraphVizM.cpp", BowGraphVizF);
USEUNIT("..\..\GLib\base.cpp");
USEUNIT("..\..\GLib\mine.cpp");
USEUNIT("..\..\GLib\graph.cpp");
USEUNIT("..\..\GLib\gks.cpp");
USEUNIT("..\..\GLib\gksvcl.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TBowGraphVizF), &BowGraphVizF);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
