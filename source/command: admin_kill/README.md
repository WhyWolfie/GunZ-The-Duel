Command: admin_kill (/kill charactername) <br>
Open(ZChat_Cmds.cpp) <br>

    void ChatCmd_Kill(const char* line, const int argc, char **const argv);

Part 2

    _CC_AC("kill", &ChatCmd_Kill, CCF_ADMIN|CCF_GAME, ARGVNoMin, 1, true, "/kill <charname>", "");

Part 3


    void ChatCmd_Kill(const char* line, const int argc, char **const argv)
    {
      if(argc < 2)
      {
        ZChatOutput("Usage: /kill <charname>", ZChat::CMT_SYSTEM);
        return;
      }
      ZPOSTCMD2(MC_KILL_THIS_PLAYER, MCmdParamStr(""), MCmdParamStr(argv[1]));
    }

Open(MSharedCommandTable.h)

    #define MC_KILL_THIS_PLAYER                     50067


Open(MMatchServer_OnCommand.cpp)

    case MC_KILL_THIS_PLAYER:
    {
      char AdminName[256] = "";
      char TargetName[256] = "";
      char szMsg[256];

      if(!pCommand->GetParameter(AdminName, 0, MPT_STR))
        break;
      MMatchObject* pChar = GetObjectA(pCommand->GetSenderUID());
      pCommand->GetParameter(TargetName, 1, MPT_STR, sizeof(TargetName));

      if(pChar == NULL)
        break;
      if(!IsAdminGrade(pChar))
        break;

      MCommand* pCmd = CreateCommand(MC_KILL_THIS_PLAYER, MUID(0,0));
      pCmd->AddParameter(new MCmdParamStr(pChar->GetName()));
      pCmd->AddParameter(new MCmdParamStr(TargetName));
      RouteToStage(pChar->GetStageUID(), pCmd);
      sprintf(szMsg, "^2You have slained %s", TargetName);
      Announce(pChar->GetUID(), szMsg);
    }
    break;

Open(MSharedCommandTable.cpp)

	C(MC_KILL_THIS_PLAYER, "Admin.KillPlayer", "", MCDT_MACHINE2MACHINE)
        P(MPT_STR, "AdminName")
		    P(MPT_STR, "TargetName")


Open(ZGameClient_OnCommand.cpp)

		case MC_KILL_THIS_PLAYER:
    {
      char AdminName[256] = "";
      char TargetName[256] = "";
      char szMsg[256];

            if(ZGetMyInfo()->IsAdminGrade())
        break;

            pCommand->GetParameter(AdminName, 0, MPT_STR, sizeof(AdminName));
      pCommand->GetParameter(TargetName, 1, MPT_STR, sizeof(TargetName));
            ZCharacterManager *pZCharacterManager = ZGetCharacterManager();
            if (pZCharacterManager != NULL) 
            {
                 for (ZCharacterManager::iterator itor = pZCharacterManager->begin(); itor != pZCharacterManager->end(); ++itor) 
                 {
                      ZCharacter* pCharacter = (*itor).second;
                      if (strcmp(pCharacter->GetProperty()->GetName(), TargetName) == 0)
            pCharacter->SetHP(0);
                 }
            }
      sprintf(szMsg, "^2%s has slained %s", AdminName, TargetName);
      ZChatOutput(szMsg);
    }
    break;













