1. Open Gunz solution, CTRL + H (Make sure it says Entire Solution) type into top box "MSM_QUEST" and in bottom box "MSM_TEST"  <br>
2. Replace All,after replacing again CTRL + H (Make sure it says Entire Solution) type into top box "MSM_TEST" and in bottom box "MSM_CLAN"  <br>
3. Move the Matchserver folder back from your Desktop into your source folder  <br>
4. Build the solution, once completed you should then recieve 2 errors, double click the error and it should take you to the line of where to 
the line that the error is produced.  <br>
5. On that line you will see MSM_CLAN, change back to MSM_TEST, and do this for the other error you recieved,you might get MSM_QUEST change it to MSM_TEST. <br>
6. Rebuild and it should build succussful  <br>
7. Open up the Matchserver solution and it should build successfully  <br>
8. Replace your Matchserver.exe and Gunz.exe that you have originally  <br>

[short] <br>
CTRL + Shift + F <br>
Replace -> MSM_QUEST -> MSM_TEST <br>
Replace -> MSM_TEST -> MSM_CLAN <br>
Error -> Change too -> MSM_TEST -> Rebuild <br>

MatchServer/server.ini <br>
change -> mode=clan <br>

Or


Open(MMatchStage.cpp - line 60) <br>

    if((MSM_CLAN != MGetServerConfig()->GetServerMode()) && (MSM_TEST != MGetServerConfig()->GetServerMode()) && (bIsAllowNullChannel == false) ) {

Open(MMatchStage.cpp - line 861) <br>

    if ((MGetServerConfig()->GetServerMode() == MSM_LADDER) || (MGetServerConfig()->GetServerMode() == MSM_CLAN) || (MGetServerConfig()->GetServerMode() == MSM_TEST))

Open(MMatchObject.cpp - line 197) <br>

    if ((pChannel) && (pChannel->GetChannelType() == MCHANNEL_TYPE_CLAN) && (MGetServerConfig()->GetServerMode() == MSM_TEST))

Open(MMatchServer.cpp - line 491)

    if ((MGetServerConfig()->GetServerMode() == MSM_CLAN) || (MGetServerConfig()->GetServerMode() == MSM_TEST))

Open(MMatchServer.cpp - line 1117)

    if ((MGetServerConfig()->GetServerMode() == MSM_CLAN) || (MGetServerConfig()->GetServerMode() == MSM_TEST))

Open(MMatchServer_Channel.cpp - line 162)

    } else if ( (MGetServerConfig()->GetServerMode() == MSM_CLAN) || (MGetServerConfig()->GetServerMode() == MSM_TEST) || (MGetServerConfig()->GetServerMode() == MSM_MATCH)) {

Open(MMatchServer_Char.cpp - line 233)

    if ((MGetServerConfig()->GetServerMode() == MSM_CLAN) || (MGetServerConfig()->GetServerMode() == MSM_TEST))

Open(MMatchServer_Stage.cpp - line 882)

    if ((MGetServerConfig()->GetServerMode() == MSM_TEST) && (pChannel->GetChannelType() == MCHANNEL_TYPE_CLAN)

Open(MMatchServer_Stage.cpp - line 2083)

    if ((MGetServerConfig()->GetServerMode() == MSM_TEST) && (pStage->GetStageType() == MST_LADDER))

Open(MMatchServer_Stage.cpp - line 2504)

    if ((MGetServerConfig()->GetServerMode() == MSM_TEST) && (pChannel->GetChannelType() == MCHANNEL_TYPE_CLAN))

Open(MMatchConfig.cpp - line 133)

    else if (!stricmp(szServerMode, SERVER_CONFIG_SERVERMODE_TEST)) m_nServerMode = MSM_TEST;

Open(MMatchConfig.h - line 201)

    const bool IsClanServer() { return (MSM_CLAN == m_nServerMode || MSM_TEST == m_nServerMode); }

Open(ZGameInterface.cpp - line 2010)

    bool bClanBattleUI = (((ZGetGameClient()->GetServerMode() == MSM_CLAN) || (ZGetGameClient()->GetServerMode() == MSM_TEST)) && (ZGetGameClient()->GetChannelType()==MCHANNEL_TYPE_CLAN));

Open(ZGameInterface.cpp - line 5443)

    bool bClanBattleUI = ((nCurrentServerMode== MSM_CLAN) || (nCurrentServerMode == MSM_TEST)) && (nCurrentChannelType==MCHANNEL_TYPE_CLAN);

Open(ZGameInterface.cpp - line 5790)

    bool bClanServer = (ZGetGameClient()->GetServerMode()==MSM_CLAN || ZGetGameClient()->GetServerMode()==MSM_TEST);


Credits To Ronny786
