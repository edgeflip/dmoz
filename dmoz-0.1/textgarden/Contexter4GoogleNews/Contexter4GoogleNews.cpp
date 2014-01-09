//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Contexter4GoogleNews.res");
USEFORM("Contexter4GoogleNewsM.cpp", ContexterF);
USEUNIT("..\..\GLib\base.cpp");
USEUNIT("..\..\GLib\net.cpp");
USEUNIT("..\..\GLib\gks.cpp");
USEUNIT("..\..\GLib\gksvcl.cpp");
USEUNIT("..\..\GLib\google.cpp");
USEUNIT("..\..\GLib\graph.cpp");
USEUNIT("..\..\GLib\nmobj.cpp");
USEUNIT("..\..\GLib\mine.cpp");
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
