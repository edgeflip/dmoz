//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("BowTileViz.res");
USEFORM("BowTileVizM.cpp", BowTileVizF);
USEUNIT("..\..\GLib\base.cpp");
USEUNIT("..\..\GLib\mine.cpp");
USEUNIT("..\..\GLib\graph.cpp");
USEUNIT("..\..\GLib\gksvcl.cpp");
USEUNIT("..\..\GLib\gks.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TBowTileVizF), &BowTileVizF);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
