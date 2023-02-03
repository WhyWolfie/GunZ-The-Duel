Open(ZChat_Cmds.cpp) <br>

Part 1 <br>

    void ChatCmd_FPS(const char* line, const int argc, char** const argv);

Part 2 <br>

	_CC_AC("fps", &ChatCmd_FPS, CCF_ALL, ARGVNoMin, 1, true, "/fps <number>", "");

Part 3 <br>

    void ChatCmd_FPS(const char* line, const int argc, char** const argv)
    {
      if (argc < 2)
      {
        ZChatOutput("Enter a FPS value!", ZChat::CMT_SYSTEM);
        return;
      }

      RSetFrameLimitPerSeceond(atoi(argv[1]));
      ZChatOutput("FPS changed successfully!", ZChat::CMT_SYSTEM);
    }














