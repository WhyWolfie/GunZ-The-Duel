Open(ZChat_Cmds.cpp) <br>

    void ChatCmd_ColorList(const char* line, const int argc, char** const argv);

Part 2


	_CC_AC("colors", &ChatCmd_ColorList, CCF_ALL, ARGVNoMin, ARGVNoMax, true, "/colors", "Lists all colors");


Part 3


    void ChatCmd_ColorList(const char* line, const int argc, char** const argv)
    {
      ZChatOutput("^00 ^11 ^22 ^33 ^44 ^55 ^66 ^77 ^88 ^99");
      ZChatOutput("^AA ^BB ^CC ^DD ^EE ^FF ^GG");
    }


![img](https://i.imgur.com/dZ5nksV.png)
