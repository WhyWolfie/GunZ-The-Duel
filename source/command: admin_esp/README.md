Open(ZChat_Cmds.cpp) <br>

    void ChatCmd_AdminEsp(const char* line, const int argc, char** const argv);
    

Part 2

	_CC_AC("esp", &ChatCmd_AdminEsp, CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/esp", "");


Part 3

    void ChatCmd_AdminEsp(const char* line, const int argc, char** const argv)
    {
      char szMsg[256];
      if (!ZGetMyInfo()->IsAdminGrade())
      {
        return;
      }
      if (ZGetGame()->m_pMyCharacter->GetStatus().Ref().isESP == 0)
      {
        ZGetGame()->m_pMyCharacter->GetStatus().CheckCrc();
        ZGetGame()->m_pMyCharacter->GetStatus().Ref().isESP = 1;
        ZGetGame()->m_pMyCharacter->GetStatus().MakeCrc();
        sprintf(szMsg, "ESP has been enabled!");
      }
      else if (ZGetGame()->m_pMyCharacter->GetStatus().Ref().isESP == 1)
      {
        ZGetGame()->m_pMyCharacter->GetStatus().CheckCrc();
        ZGetGame()->m_pMyCharacter->GetStatus().Ref().isESP = 0;
        ZGetGame()->m_pMyCharacter->GetStatus().MakeCrc();
        sprintf(szMsg, "ESP has been disabled!");
      }
      ZChatOutput(szMsg);
    }


Open(ZCharacter.h) <br>

	int			isESP;

Part 2

    isESP(0),


Open(ZCombatInterface.cpp) <br>
Find <br>

	if(ZGetGame()->m_pMyCharacter->IsAdminHide()
		&& MEvent::GetAltState() && ZGetCamera()->GetLookMode()!=ZCAMERA_MINIMAP)
		bDrawAllPlayerName = true;

Add Under <br>

	if (ZGetGame()->m_pMyCharacter->GetStatus().Ref().isESP == 1)
		bDrawAllPlayerName = true;



