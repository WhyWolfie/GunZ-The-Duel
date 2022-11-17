Command TeleportHere (/tph charactername)

Open(ZChat_Cmds.cpp)

    void ChatCmd_AdminTeleportHere(const char* line, const int argc, char** const argv);

Part 2

	_CC_AC("tph", &ChatCmd_AdminTeleportHere, CCF_ADMIN, ARGVNoMin, 1, true, "/tph <player>", "");



Part 3


    void ChatCmd_AdminTeleportHere(const char* line, const int argc, char** const argv)
    {
      if (!ZGetMyInfo()->IsAdminGrade()) return;

      if (!ZGetGame())
      {
        ZChatOutput("You are not inside the room.", ZChat::CMT_SYSTEM);
        return;
      }

      if (argc < 2)
      {
        ZChatOutput("Enter a character name!", ZChat::CMT_SYSTEM);
        return;
      }
      ZPOSTCMD2(MC_ADMIN_TELEPORT, MCmdParamStr(""), MCmdParamStr(argv[1]));
    }

Open(MSharedCommandTable.h)

    #define MC_ADMIN_TELEPORT						50065


Open(MMatchServer_OnCommand.cpp)

		case MC_ADMIN_TELEPORT:
		{
			char szAdminName[MAX_CHARNAME_LENGTH] = "";
			char szTargetName[MAX_CHARNAME_LENGTH] = "";

			if (pCommand->GetParameter(szAdminName, 0, MPT_STR, MAX_CHARNAME_LENGTH) == false) break;
			if (pCommand->GetParameter(szTargetName, 1, MPT_STR, MAX_CHARNAME_LENGTH) == false) break;

			MMatchObject* pObj = GetObjectA(pCommand->GetSenderUID());

			if (pObj == NULL) break;
			if (!IsAdminGrade(pObj)) break;


			MMatchObject* pTargetObj = GetPlayerByName(szTargetName);
			if (pTargetObj == NULL)
			{
				NotifyMessage(pObj->GetUID(), MATCHNOTIFY_GENERAL_USER_NOTFOUND);
				break;
			}

			MCommand* pCmd = CreateCommand(MC_ADMIN_TELEPORT, MUID(0, 0));
			pCmd->AddParameter(new MCmdParamStr(pObj->GetName()));
			pCmd->AddParameter(new MCmdParamStr(szTargetName));
			RouteToListener(pTargetObj, pCmd);
		}
		break;

Open(MSharedCommandTable.cpp)

	C(MC_ADMIN_TELEPORT, "Admin.Teleport", "Teleport player to admin position", MCDT_MACHINE2MACHINE)
		P(MPT_STR, "AdminName")
		P(MPT_STR, "TargetName");



Open(ZGameClient_OnCommand.cpp)


		case MC_ADMIN_TELEPORT:
		{
			char szAdminName[128] = "";
			char szTargetName[128] = "";

			if (pCommand->GetSenderUID() != GetServerUID())
				break;

			pCommand->GetParameter(szAdminName, 0, MPT_STR, sizeof(szAdminName));
			pCommand->GetParameter(szTargetName, 1, MPT_STR, sizeof(szTargetName));

			ZCharacterManager *pZCharacterManager = ZGetCharacterManager();

			if (pZCharacterManager != NULL)
			{
				for (ZCharacterManager::iterator itor = pZCharacterManager->begin(); itor != pZCharacterManager->end(); ++itor)
				{
					ZCharacter* pCharacter = (*itor).second;

					if (strcmp(pCharacter->GetProperty()->GetName(), szAdminName) == 0)
						ZGetGame()->m_pMyCharacter->SetPosition(pCharacter->GetPosition());
				}
			}
		}
		break;












