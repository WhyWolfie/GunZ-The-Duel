Open(ZChat_Cmds.cpp) <br>
Add <br>

    void ChatCmd_ServerTime(const char* line, const int argc, char **const argv);

Part 2 <br>

	_CC_AC("time", &ChatCmd_ServerTime, CCF_ALL, ARGVNoMin, ARGVNoMax, true, "/time", "");

Part 3 <br>

    void ChatCmd_ServerTime(const char* line, const int argc, char **const argv)
    {
      ZPostServerTime();
    }

Open(ZPost.h) <br>
Find <br>

    inline void ZPostRequestUseSpendableBuffItem(const MUID& uid)
    {
      ZPOSTCMD1(MC_MATCH_REQUEST_USE_SPENDABLE_BUFF_ITEM, MCmdParamUID(uid));
    }


Add <br>


    inline void ZPostServerTime()
    {
      ZPOSTCMD0(MC_SERVER_GET_TIME);
    }


Open(MServer.cpp) <br>
Find <br>

    case MC_NET_PONG:

Add <br>

	case MC_SERVER_GET_TIME:
	{
		MCommand* pNew = new MCommand(m_CommandManager.GetCommandDescByID(MC_SERVER_GET_TIME_RESPONSE), pCommand->m_Sender, m_This);
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[120];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, 80, "%m/%d/%Y - %H:%M:%S", timeinfo);
		pNew->AddParameter(new MCommandParameterString(buffer));
		Post(pNew);
		return true;
	}
	break;

Open(MSharedCommandTable.cpp) <br>
Find <br>

    END_CMD_DESC();

Add above <br>

	C(MC_SERVER_GET_TIME, "Server.Time", "Time", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED)

	C(MC_SERVER_GET_TIME_RESPONSE, "Server.Time.Response", "Time.Response", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED)
		P(MPT_STR, "Time")


Open(ZGameClient_OnCommand.cpp) <br>
Find <br>

		case MC_ADMIN_RESPONSE_MUTE_PLAYER:
			{
				int nResult;
				pCommand->GetParameter( &nResult, 0, MPT_INT );
				OnAdminResponseMutePlayer(nResult);
			}
			break;

Replace <br>

		case MC_SERVER_GET_TIME_RESPONSE:
		{
			char buffer[120];
			pCommand->GetParameter(&buffer, 0, MPT_STR);
			char buffer2[255];
			time_t rawtime;
			struct tm * timeinfo;
			char buffer1[120];
			time(&rawtime);
			timeinfo = localtime(&rawtime);
			strftime(buffer1, 80, "%m/%d/%Y - %H:%M:%S", timeinfo);
			sprintf(buffer2, "[SERVER]Time: %s  -  [MY]Time: %s", buffer, buffer1);
			MClient::OutputMessage(MZMOM_LOCALREPLY, buffer2);
		}
		break;


Open(MSharedCommandTable.h) <br>
Add <br>

    #define MC_SERVER_GET_TIME						50071
    #define MC_SERVER_GET_TIME_RESPONSE				50072








