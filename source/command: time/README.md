Open(ZChat_Cmds.cpp) <br>
Add <br>

Part 1 <br>

    void ChatCmd_Time(const char* line, const int argc, char **const argv);

Part 2 <br>

    _CC_AC("time",   	&ChatCmd_Time,		CCF_ALL, ARGVNoMin, ARGVNoMax, true,"/time", "");

Part 3 <br>

    void ChatCmd_Time(const char* line, const int argc, char **const argv)
    {
        char sztemph[512];
      char sztempd[512];
      time_t currentTime;
      struct tm *timeinfo;
      currentTime= time(NULL);
      timeinfo= localtime(&currentTime);
      strftime (sztemph, 30, "^2Time : %H:%M:%S." , timeinfo);
      ZChatOutput(sztemph);
      strftime (sztempd, 30, "^2Date : %d/%m/%Y." , timeinfo);
      ZChatOutput(sztempd);
      return;
    }
