ZChat_Cmds: <br>
Part 1 <br> 

    void ChatCmd_AdminSpeed(const char* line, const int argc, char **const argv);

Part 2 <br> 

    _CC_AC("admin_speed",            &ChatCmd_AdminSpeed,            CCF_ADMIN, ARGVNoMin, 1 , true,"/admin_speed", "");

Part 3 <br> 

    void ChatCmd_AdminSpeed(const char* line, const int argc, char **const argv)
    {

      if(!ZGetGame())
      {
        ZChatOutput("This command can only be used in-game!", ZChat::CMT_SYSTEM);
        return;
      }

      if (!ZGetMyInfo()->IsAdminGrade()) 
      {
        return;
      }

      char szMsg[256];

      if(ZGetGame()->m_pMyCharacter->GetStatus().Ref().isSpeed == 0)
      {
                    ZGetGame()->m_pMyCharacter->GetStatus().CheckCrc();
                    ZGetGame()->m_pMyCharacter->GetStatus().Ref().isSpeed = 1;
                    ZGetGame()->m_pMyCharacter->GetStatus().MakeCrc();
                    sprintf(szMsg, "^2Admin Speed Mode: Activated");
      }
                    else if(ZGetGame()->m_pMyCharacter->GetStatus().Ref().isSpeed == 1)
      {
                    ZGetGame()->m_pMyCharacter->GetStatus().CheckCrc();
                    ZGetGame()->m_pMyCharacter->GetStatus().Ref().isSpeed = 0;
                    ZGetGame()->m_pMyCharacter->GetStatus().MakeCrc();
                    sprintf(szMsg, "^1Admin Speed Mode: Deactivated");
      } 
      ZChatOutput(szMsg);

    }
    
ZCharacter.h: <br>
Part 1 
   
    int         isSpeed;

Part 2
    
    isSpeed(0),
    
ZCharacter.cpp: <br>

		if(ZGetGame()->m_pMyCharacter->GetStatus().Ref().isSpeed == 1)
		{
			int nPercent = 130.0f;
			fRatio *= (nPercent/100.0f);
		}

Example Video <br>
https://www.youtube.com/watch?v=7U6yZwPVrx4&ab_channel=GunZDEV

    
