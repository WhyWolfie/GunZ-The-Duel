Command: /exit <br>
Open(ZChat_Cmds.cpp) <br>

    void ChatCmd_Exit(const char* line, const int argc, char **const argv);
Part 2

	_CC_AC("exit",						&ChatCmd_Exit,				CCF_ALL, ARGVNoMin, ARGVNoMax, true, "/exit", "");

Part 3

    void ChatCmd_Exit(const char* line, const int argc, char** const argv)
    {
      PostQuitMessage(0);
    }
