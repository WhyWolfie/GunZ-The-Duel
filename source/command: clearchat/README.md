Open(ZChat_Cmds.cpp)

    void ChatCmd_ClearChat(const char* line, const int argc, char** const argv);




Part 2

	_CC_AC("clearchat", &ChatCmd_ClearChat, CCF_ALL, ARGVNoMin, -1, true, "/clearchat", "");




Part 3

    void ChatCmd_ClearChat(const char* line, const int argc, char** const argv)
    {
      ZGetGameInterface()->GetChat()->Clear();
    }
