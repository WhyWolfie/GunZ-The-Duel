Open(ZChat_Cmds.cpp) <br>

    void ChatCmd_AdminRevive(const char* line, const int argc, char **const argv);

Part 2

	_CC_AC("revive", &ChatCmd_AdminRevive, CCF_ADMIN, ARGVNoMin, 1, true, "/revive <charname>", "");

Part 3

    void ChatCmd_AdminRevive(const char* line, const int argc, char **const argv)
    {
      if (argc < 2) {
        OutputCmdWrongArgument(argv[0]);
        return;
      }
      char* pszPlayerName = argv[1];



    if (ZGetGame() && ZGetCombatInterface() && ZGetCombatInterface()->GetTargetCharacter())
      ZPostAdminRevive(pszPlayerName, rvector(ZGetCombatInterface()->GetTargetCharacter()->GetPosition().x, ZGetCombatInterface()->GetTargetCharacter()->GetPosition().y, ZGetCombatInterface()->GetTargetCharacter()->GetPosition().z));
    }


Open(ZPost.h)

    inline void ZPostAdminRevive(char* pszTargetPlayerName, rvector& vPos)
    {
      ZPOSTCMD2(MC_ADMIN_REQUEST_REVIVE, MCmdParamStr(pszTargetPlayerName), MCmdParamPos(vPos.x, vPos.y, vPos.z));
    }

Open(MSharedCommandTable.h)

    #define MC_ADMIN_REQUEST_REVIVE				XXXXX


Open(MMatchServer_OnCommand.cpp)

    case MC_ADMIN_REQUEST_REVIVE:
    {
      MUID uidPlayer = pCommand->GetSenderUID();
      char szPlayer[512];
      rvector pos;
      float nDropDelayTime = 0.f;

      pCommand->GetParameter(szPlayer, 0, MPT_STR, sizeof(szPlayer));
      pCommand->GetParameter(&pos, 1, MPT_POS);

      if (pos && szPlayer)
        OnAdminRequestRevive(uidPlayer, szPlayer, MVector(pos.x, pos.y, pos.z));
    }
    break;


Open(MSharedCommandTable.cpp)

			C(MC_ADMIN_REQUEST_REVIVE, "Admin.RequestRev", "Request Revive", MCDT_MACHINE2MACHINE)
				P(MPT_STR, "uidTarget")
				P(MPT_POS, "vPos");

Open(MMatchServer.h)

	void OnAdminRequestRevive(const MUID& uidAdmin, const char* szPlayer, MVector& pos);


Open(MMatchServer_Admin.cpp)

    void MMatchServer::OnAdminRequestRevive(const MUID& uidAdmin, const char* szPlayer, MVector& pos)
    {
      MMatchObject* pObj = GetObject(uidAdmin);
      if (pObj == NULL)			return;

      MMatchUserGradeID nGrade = pObj->GetAccountInfo()->m_nUGrade;
      if ((nGrade != MMUG_ADMIN) && (nGrade != MMUG_DEVELOPER) && (nGrade != MMUG_EVENTMASTER)) return;

      if ((strlen(szPlayer)) < 2) return;

      static unsigned long int st_LastRequestTime = 0;
      unsigned long int nNowTime = timeGetTime();
      if ((nNowTime - st_LastRequestTime) < 1000) return;

      st_LastRequestTime = nNowTime;

      FILE* pFile = fopen("GM_LOGS.txt", "a");
      if (pFile != NULL){
        char szDateRun[128] = "";
        char szTimeRun[128] = "";
        _strdate(szDateRun);
        _strtime(szTimeRun);
        fprintf_s(pFile, "[%s %s](REVIVE) %s has been revived by %s\n", szDateRun, szTimeRun, szPlayer, pObj->GetCharInfo()->m_szName);
        fclose(pFile);
      }

      int nRet = MOK;
      MMatchObject* pTargetObj = GetPlayerByName(szPlayer);
      if (!IsEnabledObject(pTargetObj)) return;
      pTargetObj->ResetCustomItemUseCount();
      pTargetObj->SetAlive(true);

      MCommand* pCmd = CreateCommand(MC_MATCH_GAME_RESPONSE_SPAWN, MUID(0, 0));
      pCmd->AddParameter(new MCmdParamUID(pTargetObj->GetUID()));
      pCmd->AddParameter(new MCmdParamShortVector(pos.x, pos.y, pos.z));
      pCmd->AddParameter(new MCmdParamShortVector((short)0, (short)0, (short)0));
      RouteToBattle(pObj->GetStageUID(), pCmd);

    }








