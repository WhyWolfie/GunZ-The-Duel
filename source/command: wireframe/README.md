Open (ZChat_Cmds.cpp) - Wireframe command<br>
Find

    void ChatCmd_AdminAssasin( const char* line, const int argc, char **const argv );

Place under

    void ChatCmd_Framed(const char* line, const int argc, char** const argv);

Find

    _CC_AC("admin_commander",				&ChatCmd_AdminAssasin,

Place under

    _CC_AC("wireframe", &ChatCmd_Framed, CCF_ADMIN | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/wireframe", "");

Find

    void OutputCmdWrongArgument(const char* cmd)

Place under

    void ChatCmd_Framed(const char* line, const int argc, char** const argv)
    {
      char szMsg[256];

      GunzState state = ZApplication::GetGameInterface()->GetState();

      if (state == GUNZ_GAME)
      {
        if (!ZGetGame()->m_bShowWireframe)
        {
          ZGetGame()->m_bShowWireframe = true;
          sprintf(szMsg, "^1Wireframe mode activated!");
          ZChatOutput(szMsg);
        }
        else if (ZGetGame()->m_bShowWireframe)
        {
          ZGetGame()->m_bShowWireframe = false;
          sprintf(szMsg, "^1Wireframe mode deactivated!");
          ZChatOutput(szMsg);
        }
      }
      else
      {
        sprintf(szMsg, "^1Wireframe can only be activated in-game!");
        ZChatOutput(szMsg);
        return;
      }
    }


![img](https://i.imgur.com/cT1Cr9D.jpg)
