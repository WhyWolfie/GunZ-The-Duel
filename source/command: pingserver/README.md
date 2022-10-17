Not done yet...

Open(ZChat_Cmds.cpp) <br>

    void ChatCmd_PingServer(const char* line, const int argc, char **const argv);

Part 2

	_CC_AC("serverping",				&ChatCmd_PingServer,		CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/serverping", "");

Part 3

    void ChatCmd_PingServer(const char* line, const int argc, char **const argv) 
    {
      ZPostServerPing(timeGetTime(), 0);
    }


Open(ZPost.h) <br>

    inline void ZPostServerPing(const unsigned int nTimeStamp, int nType)
    {
      ZPOSTCMD2(MC_SERVER_PING, MCommandParameterUInt(nTimeStamp), MCommandParameterInt(nType));
    }

Open(MSharedCommandTable.h) <br>

    #define MC_SERVER_PING								50014

Open(MServer.cpp) <br>

	case MC_SERVER_PING:
		{
			unsigned int nTimeStamp;
			int nType = 0;
			if (pCommand->GetParameter(&nTimeStamp, 0, MPT_UINT)==false) break;
			if (pCommand->GetParameter(&nType, 1, MPT_INT)==false) break;

			MCommand* pNew = new MCommand(m_CommandManager.GetCommandDescByID(MC_SERVER_PING), pCommand->m_Sender, m_This);
			pNew->AddParameter(new MCommandParameterUInt(nTimeStamp));
			pNew->AddParameter(new MCommandParameterInt(nType));
			Post(pNew);
			return true;
		}
		break;

Open(MSharedCommandTable.cpp) <br>

	C(MC_SERVER_PING, "Server.Ping", "Ping", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED)
		P(MPT_UINT, "TimeStamp")
		P(MPT_INT, "TYPE")


Open(ZCommandUDPHackShield.cpp) <br>

	AddDeniedCommand(MC_SERVER_PING);


Open(ZGameClient_OnCommand.cpp) <br>
		
    case MC_SERVER_PING:
			{
				int nTimeStamp, nType = 0;
				pCommand->GetParameter(&nTimeStamp, 0, MPT_UINT);
				pCommand->GetParameter(&nType, 1, MPT_INT);
				switch (nType)
				{
				case 0:
					MClient::OutputMessage(MZMOM_LOCALREPLY, "[SERVER]Ping: %d", timeGetTime()-nTimeStamp);
					break;
				}
			}
			break;


