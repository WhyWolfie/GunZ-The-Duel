Command: admin_killall (/killall)
Open(ZChat_Cmds.cpp)

    void ChatCmd_Killall(const char* line, const int argc, char **const argv);

Part 2

	_CC_AC("killall", &ChatCmd_Killall, CCF_ADMIN | CCF_GAME, ARGVNoMin, 1, true, "/killall", "");

Part 3

    void ChatCmd_Killall(const char* line, const int argc, char **const argv)
    {
      if (!ZGetGame())
      {
        ZChatOutput("You're not in game.", ZChat::CMT_SYSTEM);
        return;
      }
      if (!ZGetMyInfo()->IsAdminGrade())
      {
        return;
      }
      char szAdminName[100] = "";
      char szBuffer[128] = "";


      if (argc > 2){
        OutputCmdWrongArgument(argv[0]);


        return;
      }
      else if (argc < 2){
        strcpy(szAdminName, "");
        strcpy(szBuffer, "Room killed.");
      }
      else{
        strcpy(szAdminName, argv[1]);
        sprintf(szBuffer, "Room killed.", szAdminName);
      }


      ZPOSTCMD1(MC_KILL_ALL, MCmdParamStr(szAdminName));
      ZChatOutput(szBuffer, ZChat::CMT_SYSTEM);
    }

Open(MSharedCommandTable.h)

    #define MC_KILL_ALL                             50068

Open(MMatchServer_OnCommand.cpp)

		case MC_KILL_ALL:
		{
			char szAdminName[1024] = "";
			if (!pCommand->GetParameter(szAdminName, 0, MPT_STR, 32)) break;
			MMatchObject* pObj = GetObjectA(pCommand->GetSenderUID());
			if (pObj == NULL) break;
			if (!IsAdminGrade(pObj)) break;
			MCommand* pCmd = CreateCommand(MC_KILL_ALL, MUID(0, 0));
			pCmd->AddParameter(new MCmdParamStr(szAdminName));
			RouteToStage(pObj->GetStageUID(), pCmd);
		}
		break;

Open(MSharedCommandTable.cpp)

	C(MC_KILL_ALL, "Admin.KillAll", "", MCDT_MACHINE2MACHINE)
		P(MPT_STR, "AdminName")

Open(ZGameClient_OnCommand.cpp)

		case MC_KILL_ALL:
		{
			char szAdminName[128] = "";
			pCommand->GetParameter(szAdminName, 0, MPT_STR, sizeof(szAdminName));
			ZCharacterManager *pZCharacterManager = ZGetCharacterManager();

			if (pZCharacterManager != NULL)
			{
				for (ZCharacterManager::iterator itor = pZCharacterManager->begin(); itor != pZCharacterManager->end(); ++itor)
				{
					ZCharacter* pCharacter = (*itor).second;
					if (strcmp(pCharacter->GetProperty()->GetName(), szAdminName) == 0)
						ZGetGame()->m_pMyCharacter->SetAP(ZGetGame()->m_pMyCharacter->GetMaxAP());
					pCharacter->SetHP(0);
					pCharacter->SetAP(0);
					ZGetGameInterface()->ShowMessage("Room has been killed by staff.");
				}
			}
		}
		break;
