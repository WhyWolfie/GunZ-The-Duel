Command: /s {text} <br>
Command: $hello <br>

Follow this part first: [Follow this part first](https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/source/hide%20administrator%20level)

Open(ZChat_cmds.cpp) <br>

    void ChatCmd_StaffChat(const char* line, const int argc, char** const argv);
    
Part 2

    _CC_AC("s", &ChatCmd_StaffChat, CCF_ADMIN, ARGVNoMin, 1, true, "/s <Msg>", "");
    
Part 3

    void ChatCmd_StaffChat(const char* line, const int argc, char** const argv)
    {
      if (argc < 2)
      {
        OutputCmdWrongArgument(argv[0]);
        return;
      }

      char szMsg[256];

      strcpy(szMsg, argv[1]);
      ZPostStaffChat(szMsg);
    }
    
    

Open(ZPost.h) <br>

    inline void ZPostStaffChat( char* szMsg)
    {
      ZPOSTCMD3(MC_STAFF_CHAT, MCommandParameterString(szMsg), MCommandParameterString(""), MCommandParameterInt(0));
    }

    
Open(MSharedCommandTable.h) <br>


    #define MC_STAFF_CHAT							50048
    
Open(MMatchServer.cpp - OnUserWhisper - Add) <br>

    void MMatchServer::OnStaffChat(const MUID& uid, const char* szChat)
    {
      MMatchObject* pObj = GetObject(uid);
      if (pObj == NULL) return;
      MCommand* pCmd = CreateCommand(MC_STAFF_CHAT, uid);
      pCmd->AddParameter(new MCmdParamStr(szChat));
      pCmd->AddParameter(new MCmdParamStr(pObj->GetCharInfo()->m_szName));
      pCmd->AddParameter(new MCmdParamInt(pObj->GetAccountInfo()->m_nUGrade));
      RouteToStaff(pCmd);
    }
    
    void MMatchServer::RouteToStaff(MCommand* pCommand)
    {
      for (MMatchObjectList::iterator i = m_Objects.begin(); i != m_Objects.end(); i++) {
        MMatchObject* pObj = (MMatchObject*)((*i).second);
        if (pObj->GetUID() < MUID(0, 3)) continue;
        MCommand* pSendCmd = pCommand->Clone();
        pSendCmd->m_Receiver = pObj->GetUID();
        Post(pSendCmd);
      }
      delete pCommand;
    }
    
Open(MMatchServer_OnCommand.cpp - MC_ADMIN_TERMINAL - Add) <br>

		case MC_STAFF_CHAT:
			{
				static char szChat[ 340 ];
				pCommand->GetParameter(szChat, 0, MPT_STR, sizeof(szChat) );
				OnStaffChat(pCommand->GetSenderUID(), szChat);
			}
			break;
      
      
Open(ZCommandUDPHackShield.cpp) <br>

    AddDeniedCommand(MC_STAFF_CHAT);


Open(ZGameClient_OnCommand.cpp - MC_ADMIN_ANNOUNCE - Add) <br>


		case MC_STAFF_CHAT:
			{
				char szChat[340];
				char szName[120];
				int UGradeID;
				pCommand->GetParameter(szChat, 0, MPT_STR, sizeof(szChat));
				pCommand->GetParameter(szName, 1, MPT_STR, sizeof(szName));
				pCommand->GetParameter(&UGradeID, 2, MPT_INT);
				OnStaffHelp(szChat, szName, UGradeID);
			}
			break;
      
Open(ZGameClient.cpp)

	void ZGameClient::OnStaffHelp(const char* szMsg, const char* szUsr, const int UgradeID)
	{
		if (ZApplication::GetGameInterface()->GetState() == GUNZ_GAME)
		{
			{
				MCOLOR Col;
				ZGetGame()->GetUserGradeIDColor((MMatchUserGradeID)UgradeID, Col, "");
				char Chat[420];
				sprintf(Chat, "[STAFF]%s:%s", szUsr, szMsg);
				ZGetGameInterface()->GetCombatInterface()->m_AdminMsg.OutputChatMsg(Col, Chat);
			}
		}
		else
		{
			{
				MCOLOR Col;
				ZGetGame()->GetUserGradeIDColor((MMatchUserGradeID)UgradeID, Col, "");
				char Chat[420];
				sprintf(Chat, "[STAFF]%s:%s", szUsr, szMsg);
				ZChatOutput(Col, Chat);
			}
		}
	}

Open(ZGameClient.h - OnAdminAnnounce - Add) <br>

      void OnStaffHelp(const char* szMsg, const char* szUsr, const int UgradeID);


Open(MMatchServer.h - RouteToAllClient - Add) <br>

	void OnStaffChat(const MUID& uid, const char* szChat);
	void RouteToStaff(MCommand* pCommand);


Open(ZChat.cpp) <br>
Find <br>

	bool bTeamChat = false;

Replace <br>

	bool bTeamChat = false;
	if (szMsg[0] == '!') 
	{	// Team Chat
		bTeamChat = true;
	} 
	else if (szMsg[0] == '@') 
	{	// ChatRoom
		ZPostChatRoomChat(&szMsg[1]);
		return true;
	} 
	else if (szMsg[0] == '#') 
	{	// Clan Chat
		ZPostClanMsg(ZGetGameClient()->GetPlayerUID(), &szMsg[1]);
		return true;
	}
	else if (szMsg[0] == '$')
	{	// Staff Chat
		ZPostStaffChat(&szMsg[1]);
		return true;
	}



Preview <br>
![img](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/command%3A%20staffchat/image.png)
