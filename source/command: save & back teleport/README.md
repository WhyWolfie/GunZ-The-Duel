Command: /Save & /Back Teleport<br>
Open(ZChat_Cmds.cpp) <br>
Part <br>

    void ChatCmd_Save(const char* line, const int argc, char** const argv);
    void ChatCmd_Back(const char* line, const int argc, char** const argv);

Part 2

	_CC_AC("save", &ChatCmd_Save, CCF_ADMIN, ARGVNoMin, 1, true, "/save", "");
	_CC_AC("back", &ChatCmd_Back, CCF_ADMIN, ARGVNoMin, 1, true, "/back", "");


Part 3

    rvector playerPoss;
    void ChatCmd_Save(const char* line, const int argc, char** const argv)
    {
      playerPoss = ZGetGame()->m_pMyCharacter->GetPosition();
      ZChatOutput(MCOLOR(243, 0, 0), "Positon Saved!");
    }
    void ChatCmd_Back(const char* line, const int argc, char** const argv)
    {
      ZGetGame()->m_pMyCharacter->SetPosition(playerPoss);
      ZChatOutput(MCOLOR(243, 0, 0), "Done!");
    }

