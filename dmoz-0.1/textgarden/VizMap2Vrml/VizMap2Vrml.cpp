#include "vizmap.h"

int main(int argc, char* argv[]) {
    Try;
    // create environment
    Env=TEnv(argc, argv, TNotify::StdNotify);

    // command line parameters
    Env.PrepArgs("Vizualization-Map To VRML", 1);
    // input-output files
    TStr VizFNm = Env.GetIfArgPrefixStr("-iviz:", "", "Input-Vizualization-Map-FileName (.VizMap)");
    TStr VrmlFNm = Env.GetIfArgPrefixStr("-ovrml:", "", "Output-VRML-FileName (no file extension)");
    TStr SkyColor = Env.GetIfArgPrefixStr("-skyc:", "0.4 0.4 1.0", "Sky-Color");
    TStr TerrainColor = Env.GetIfArgPrefixStr("-trrc:", "0.1 0.5 0.1", "Terrain-Color");
    TStr KeywordColor = Env.GetIfArgPrefixStr("-kwdc:", "1.0 0.4 0", "Keyword-Color");
    TStr DocNmColor = Env.GetIfArgPrefixStr("-docc:", "0.9 0.9 0.2", "Document-Name-Color");
    bool ShowDocNm = Env.GetIfArgPrefixBool("-showdn:", true, "Show-Document-Name");
    bool ShowDocPt = Env.GetIfArgPrefixBool("-showdp:", true, "Show-Document-Point");
    bool ShowKeywd = Env.GetIfArgPrefixBool("-showkw:", true, "Show-Keywords");
    if (Env.IsEndOfRun()){return 0;}

    // load VizMap
    PVizMap VizMap = TVizMap::LoadBin(VizFNm);
    // save vrml
    if (!VrmlFNm.Empty()) { VizMap->SaveVrml(VrmlFNm); }

    return 0;
    Catch;
    return 1;
}

