Open(ZChat_Cmds.cpp) <br>
Add <br>

    void ChatCmd_AdminNat(const char* line, const int argc, char** const argv);

Part 2

	_CC_AC("force_nat", &ChatCmd_AdminNat, CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/force_nat", "");

Part 3

    void ChatCmd_AdminNat(const char* line, const int argc, char **const argv)
    {
      if (!ZGetMyInfo()->IsAdminGrade()) {
        return;
      }
      ZGetGameClient()->ToggleNat = !ZGetGameClient()->ToggleNat;
      ZChatOutput((ZGetGameClient()->ToggleNat ? "Force Nat Enabled." : "Force Nat Disabled."), ZChat::CMT_SYSTEM);
    }


Open(MMatchClient.h) <br>
Find <br>

    static bool UDPSocketRecvEvent

Add <br>

    bool ToggleNat;

Find <br>

    MMatchClient::MMatchClient()
    {
      g_pMatchClient = this;
      SetServerAddr("", 6000);
      SetServerPeerPort(7777);
      m_uidAgentServer = MUID(0,0);
      m_uidAgentClient = MUID(0,0);


Add under <br>

	ToggleNat = false;

Find <br>

    void MMatchClient::OnUDPTest(const MUID& uidChar)
    {
      MMatchPeerInfo* pPeer = FindPeer(uidChar);
      if (pPeer) {

    #ifdef _DEBUG
        if ( //(strcmp("¹ß·»Å¸ÀÎ", pPeer->CharInfo.szName)==0) ||
          (strcmp("¹öµå", pPeer->CharInfo.szName)==0) ||
          (strcmp("dddd", pPeer->CharInfo.szName)==0) ||
          (strcmp("¶ó¿ÂÇÏÁ¦5", pPeer->CharInfo.szName)==0) ||
          (strcmp("¶ó¿ÂÇÏÁ¦6", pPeer->CharInfo.szName)==0) )
        {
          return;
        }
    #endif

        MCommand* pCmd = CreateCommand(MC_PEER_UDPTEST_REPLY, uidChar);
        SendCommandByUDP(pCmd, pPeer->szIP, pPeer->nPort);
        delete pCmd;
      }
    }

    void MMatchClient::OnUDPTestReply(const MUID& uidChar)
    {
    //// UDPTEST LOG ////////////////////////////////
    #ifdef _DEBUG
    char szLog[64];
    sprintf(szLog, "[%d:%d] UDP_TEST_REPLY: from (%d:%d) \n", 
        GetPlayerUID().High, GetPlayerUID().Low, uidChar.High, uidChar.Low);
    mlog(szLog);
    #endif
    /////////////////////////////////////////////////
      MMatchPeerInfo* pPeer = FindPeer(uidChar);
      if (pPeer) {
        pPeer->SetUDPTestResult(true);
        pPeer->StopUDPTest();
      }
    }

Replace <br>

    void MMatchClient::OnUDPTest(const MUID& uidChar)
    {
      if (ToggleNat == true) return;
      MMatchPeerInfo* pPeer = FindPeer(uidChar);
      if (pPeer) {

    #ifdef _DEBUG
        if ( //(strcmp("¹ß·»Å¸ÀÎ", pPeer->CharInfo.szName)==0) ||
          (strcmp("¹öµå", pPeer->CharInfo.szName)==0) ||
          (strcmp("dddd", pPeer->CharInfo.szName)==0) ||
          (strcmp("¶ó¿ÂÇÏÁ¦5", pPeer->CharInfo.szName)==0) ||
          (strcmp("¶ó¿ÂÇÏÁ¦6", pPeer->CharInfo.szName)==0) )
        {
          return;
        }
    #endif

        MCommand* pCmd = CreateCommand(MC_PEER_UDPTEST_REPLY, uidChar);
        SendCommandByUDP(pCmd, pPeer->szIP, pPeer->nPort);
        delete pCmd;
      }
    }

    void MMatchClient::OnUDPTestReply(const MUID& uidChar)
    {
      if(ToggleNat == true) return;
    //// UDPTEST LOG ////////////////////////////////
    #ifdef _DEBUG
    char szLog[64];
    sprintf(szLog, "[%d:%d] UDP_TEST_REPLY: from (%d:%d) \n", 
        GetPlayerUID().High, GetPlayerUID().Low, uidChar.High, uidChar.Low);
    mlog(szLog);
    #endif
    /////////////////////////////////////////////////
      MMatchPeerInfo* pPeer = FindPeer(uidChar);
      if (pPeer) {
        pPeer->SetUDPTestResult(true);
        pPeer->StopUDPTest();
      }
    }

Open(ZGameClient.cpp) <br>
Find <br>

    ZGameClient::ZGameClient() : MMatchClient() , m_pUPnP(NULL)
    {

Add under <br>

    ToggleNat = false;











