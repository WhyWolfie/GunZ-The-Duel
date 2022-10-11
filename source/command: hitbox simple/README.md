<b>Hitbox Simple Command</b><br>
ZGlobal.cpp

    float HIT_VALUE_HEAD = 15.f;

ZGlobal.h

    extern float HIT_VALUE_HEAD;

ZCharacter.cpp | Search (HitTest)
Line 4543

    fDist < HIT_VALUE_HEAD

ZChatCmds.cpp

    void ChatCmd_HitTest(const char* line, const int argc, char** const argv);

    _CC_AC("hittest", &ChatCmd_HitTest, CCF_ADMIN, ARGVNoMin, 1, true, "/hittest", "");


    void ChatCmd_HitTest(const char* line, const int argc, char** const argv)
    {
        if (argc < 2)
        {
            OutputCmdWrongArgument(argv[0]);
            return;
        }

        char szText[128];
        HIT_VALUE_HEAD = static_cast<float>(atof(argv[1]));
        sprintf(szText, "Set HitBox to %f",HIT_VALUE_16);
        ZChatOutput(szText, ZChat::CMT_SYSTEM);
    }

Remember, it is not a safe code. 

