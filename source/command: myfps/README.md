Open(ZChat_Cmds.cpp) <br>
Find <br>

    void ChatCmd_Myfps(const char* line, const int argc, char **const argv);

Part 2

    _CC_AC("myfps", &ChatCmd_Myfps, CCF_ALL, ARGVNoMin, ARGVNoMax, true,"/myfps", "");


Part 3

    void ChatCmd_Myfps(const char* line, const int argc, char **const argv)
    {
      char szName[128];
      float fMs = 1000.f/g_fFPS;
      float fScore = 100-(fMs-(1000.f/60.f))*2;
      sprintf(szName, "^2My FPS is currently : %3.3f",g_fFPS,fScore,fMs);
      ZApplication::GetGameInterface()->GetChat()->Input(szName);
    }


Credits To sahar042.
