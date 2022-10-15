Open(ZChat_Cmds.cpp)

    void ChatCmd_AdminTeleport(const char* line, const int argc, char** const argv);
    
Part 2

	_CC_AC("teleport", &ChatCmd_AdminTeleport, CCF_ADMIN, ARGVNoMin, 1, true, "/teleport <name>", "");
  
Part 3

    void ChatCmd_AdminTeleport(const char* line, const int argc, char** const argv)
    {
      if (!ZGetMyInfo()->IsAdminGrade()) {
        return;
      }

      if (!ZGetGame())
      {
        ZChatOutput("You need to be in-game!", ZChat::CMT_SYSTEM);
        return;
      }

      if (argc < 2)
      {
        ZChatOutput("Enter a character name!", ZChat::CMT_SYSTEM);
        return;
      }

      ZCharacterManager* pZCharacterManager = ZGetCharacterManager();

      if (pZCharacterManager != NULL)
      {
        for (ZCharacterManager::iterator itor = pZCharacterManager->begin(); itor != pZCharacterManager->end(); ++itor)
        {
          ZCharacter* pCharacter = (*itor).second;

          if (strcmp(pCharacter->GetProperty()->GetName(), argv[1]) == 0)
            ZGetGame()->m_pMyCharacter->SetPosition(pCharacter->GetPosition());
        }
      }
    }
