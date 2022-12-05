(not done.)

Open(ZChat_Cmds.cpp) <br>

	void ChatCmd_AdminHwid(const char* line, const int argc, char** const argv);

Part 2

	_CC_AC("hwid", &ChatCmd_AdminHwid, CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/hwid", "");


Part 3

	void ChatCmd_AdminHwid(const char* line, const int argc, char** const argv)
	{

		if (argc > 2)
		{
			ZPOSTCMD2(MC_ADMIN_HWBAN, MCommandParameterString(argv[1]), MCommandParameterString(argv[2]));
		}
		else
		{
			ZChatOutput("/hwid <name> <reason>");
		}
	}
    
Open(MSharedCommandTable.h) <br>

	#define MC_ADMIN_HWBAN							50071


Open(MMatchServer_OnCommand.cpp) <br>

		case MC_ADMIN_HWBAN:
		{
			char szName[64];
			char szReason[64];

			pCommand->GetParameter(szName, 0, MPT_STR, 64);
			pCommand->GetParameter(szReason, 1, MPT_STR, 64);

			OnHwBan(pCommand->GetSenderUID(), szName, szReason);
			break;
		}

Open(MSharedCommandTable.cpp) <br>

	C(MC_ADMIN_HWBAN, "Match.Admin.HardwareBan", "", MCDT_MACHINE2MACHINE)
		P(MPT_STR, "PlayerName");
		P(MPT_STR, "Reason");


Open(MMatchServer.h - void OnResponseMonsterBibleInfo - Add under) <br>

	void OnHwBan(const MUID& uidSender, const char* pName, const char* pReason);


Open(MMatchServer_Admin.cpp - Add all the way under) <br>

	void MMatchServer::OnHwBan(const MUID& uidSender, const char* pName, const char* pReason)
	{
		MMatchObject* pObj = GetObject(uidSender);

		if (pObj && IsAdminGrade(pObj))
		{
			char message[512];
			char razon[500];
			if (strstr(pName, "%") || strstr(pReason, "%")) return;
			if (strlen(pReason) > 500)
				strcpy_s(razon, 500, pReason);
			else
				strcpy(razon, pReason);
			MMatchObject* pTarget = GetPlayerByName(pName);
			if (pTarget)
			{

				m_MatchDBMgr.spBanPC(pTarget->GetAccountInfo()->m_nAID, razon);
				Disconnect(pTarget->GetUID());
				sprintf(message, "%s reason - %s", pTarget->GetAccountName(), pReason);
			}
		}
	}

Open(MMatchDBMgr.h - Under bool GetLoginInfo_Netmarble)

	bool spBanPC(const int AID, const TCHAR* pReason);

Open(MMatchDBMgr.cpp) <br>

	TCHAR g_szDB_Ban_Hwid[] = _T("{CALL spInsertBanPC (%d, '%s')}");
	bool MMatchDBMgr::spBanPC(const int AID, const TCHAR* pReason)
	{
		_STATUS_DB_START;
		if (!CheckOpen()) return false;

		CString strSQL;

		try {
			strSQL.Format(g_szDB_Ban_Hwid, AID, pReason);
			m_DB.ExecuteSQL(strSQL);
		}
		catch (CDBException* e) {
			ExceptionHandler(strSQL, e);
			return false;
		}

		_STATUS_DB_END(1);
		return true;
	}












































