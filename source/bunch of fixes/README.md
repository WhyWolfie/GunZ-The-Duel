Open(realsound\include\stdafx.h) <br>
Place <br>

	#if _MSC_VER > 1000
	#pragma once
	//<Define POINTER_64>
	#define POINTER_64 __ptr64
	#endif // _MSC_VER > 1000


Open (ZOptionInterface.cpp)

Fix: Iterator crash fix, in case resolution isn't supported

Find

    map< int, D3DDISPLAYMODE>::iterator iter = find_if( gDisplayMode.begin(), gDisplayMode.end(), value_equals<int, D3DDISPLAYMODE>(ddm));
    
Place under

			if (iter != gDisplayMode.end())
				pWidget->SetSelIndex(iter->first);
			else
				pWidget->SetSelIndex(0);
    
Open (RVisualMesh.cpp)

Find

	DEL(m_pCloth);
    
Replace

	 SAFE_DELETE_ARRAY(m_pCloth);
    
    
Open (MCommandBuilder.h)

Changed buffer size to fix shop list issues.

Find

	#define COMMAND_BUFFER_LEN	16384
    
Replace

	#define COMMAND_BUFFER_LEN	65535 
	
Open(MMatchConfig.h)

Find

	#define SERVER_CONFIG_DEFAULT_NJ_DBAGENT_IP ""
	
Replace

	#define SERVER_CONFIG_DEFAULT_NJ_DBAGENT_IP "YOUR IP"

Open(MAsyncDBJob_GetLoginInfo.cpp) <br>
It's an SQLi pretty much. It allows for remote execution of queries on the server machine. Any and all queries can be run through it as long as the user account has access.
Find

    // ¿ø·¡ °èÁ¤Àº ³Ý¸¶ºí¿¡ ÀÖÀ¸¹Ç·Î ÇØ´ç °èÁ¤ÀÌ ¾øÀ¸¸é »õ·Î »ý¼ºÇÑ´Ù. 
    if (!pDBMgr->GetLoginInfo(m_szUserID, &m_nAID, m_szDBPassword))
    {
        int nGunzSex;    // °ÇÁîµðºñÀÇ ¼ºº°°ªÀº ³Ý¸¶ºí ¼ºº°°ª°ú ¹Ý´ëÀÌ´Ù.
        if (m_nSex == 0) nGunzSex = 1; else nGunzSex = 0;

        int nCert = 0;
        if (strlen(m_szCertificate) > 0)
        {
            if (m_szCertificate[0] == '1') nCert =1;
        }

        pDBMgr->CreateAccount(m_szUserID, m_szUniqueID, nCert, m_szName, m_nAge, nGunzSex);
        pDBMgr->GetLoginInfo(m_szUserID, &m_nAID, m_szDBPassword);
    } 

Replace

    // ¿ø·¡ °èÁ¤Àº ³Ý¸¶ºí¿¡ ÀÖÀ¸¹Ç·Î ÇØ´ç °èÁ¤ÀÌ ¾øÀ¸¸é »õ·Î »ý¼ºÇÑ´Ù. 
    if (!pDBMgr->GetLoginInfo(m_szUserID, &m_nAID, m_szDBPassword))
    {
        /*int nGunzSex;    // °ÇÁîµðºñÀÇ ¼ºº°°ªÀº ³Ý¸¶ºí ¼ºº°°ª°ú ¹Ý´ëÀÌ´Ù.
        if (m_nSex == 0) nGunzSex = 1; else nGunzSex = 0;

        int nCert = 0;
        if (strlen(m_szCertificate) > 0)
        {
            if (m_szCertificate[0] == '1') nCert =1;
        }

        pDBMgr->CreateAccount(m_szUserID, m_szUniqueID, nCert, m_szName, m_nAge, nGunzSex);
        pDBMgr->GetLoginInfo(m_szUserID, &m_nAID, m_szDBPassword);*/
        
        SetResult(MASYNC_RESULT_FAILED);
        return;        
    } 

Open(ZGameInterface.cpp) <br>
Find

	char* pszAgentIP = "";

Change

	char* pszAgentIP = "YOUR IP";

Open(MPdb.cpp) <br>
Find <br>

	if (!g_pfnEnumerateLoadedModules(hProcess, EnumLoadedModulesCallback, (PVOID)hProcess))

Change

	if (!EnumerateLoadedModules(hProcess, (PENUMLOADED_MODULES_CALLBACK)EnumLoadedModulesCallback, (PVOID)hProcess))
	
Open(Gunz/stdafx.h) <br>
Add <br>

	#pragma comment(lib, "legacy_stdio_definitions.lib");


Open(ZGame.cpp) <br>
Find <br>

	void ZGame::OnPeerHPInfo(MCommand *pCommand)
	{
		MUID uid = pCommand->GetSenderUID();
		ZCharacter* pCharacter = m_CharacterManager.Find(uid);
		if (!pCharacter) return;

		float fHP=0.0f;
		pCommand->GetParameter(&fHP, 0, MPT_FLOAT);

		if(ZGetGameInterface()->GetCombatInterface()->GetObserverMode()) {
			pCharacter->SetHP(fHP);
		}
	}

Replace

	void ZGame::OnPeerHPInfo(MCommand *pCommand)
	{
		MUID uid = pCommand->GetSenderUID();
		ZCharacter* pCharacter = m_CharacterManager.Find(uid);
		if (!pCharacter) return;

		float fHP = 0.0f;
		pCommand->GetParameter(&fHP, 0, MPT_FLOAT);
		//<Lógica de HP>
		if (!IsReplay() && pCharacter->GetUID() != ZGetMyUID() && uid != ZGetMyUID())
			pCharacter->SetHP(fHP);
		else if (IsReplay() || ZGetGameInterface()->GetCombatInterface()->GetObserverMode())
			pCharacter->SetHP(fHP);
	}

Find <br>

	void ZGame::OnPeerHPAPInfo(MCommand *pCommand)
	{
		MUID uid = pCommand->GetSenderUID();
		ZCharacter* pCharacter = m_CharacterManager.Find(uid);
		if (!pCharacter) return;

		float fHP=0.0f;
		pCommand->GetParameter(&fHP, 0, MPT_FLOAT);
		float fAP=0.0f;
		pCommand->GetParameter(&fAP, 1, MPT_FLOAT);

		if(ZGetGameInterface()->GetCombatInterface()->GetObserverMode()) {
			pCharacter->SetHP(fHP);
			pCharacter->SetAP(fAP);
		}
	}
	
Change <br>

	void ZGame::OnPeerHPAPInfo(MCommand *pCommand)
	{
		MUID uid = pCommand->GetSenderUID();
		ZCharacter* pCharacter = m_CharacterManager.Find(uid);
		if (!pCharacter) return;

		float fHP = 0.0f;
		pCommand->GetParameter(&fHP, 0, MPT_FLOAT);
		float fAP = 0.0f;
		pCommand->GetParameter(&fAP, 1, MPT_FLOAT);

		//<Lógica de HP/AP>
		if (!IsReplay() && pCharacter->GetUID() != ZGetMyUID() && uid != ZGetMyUID())
		{
			pCharacter->SetHP(fHP);
			pCharacter->SetAP(fAP);
		}
		else if (IsReplay() || ZGetGameInterface()->GetCombatInterface()->GetObserverMode())
		{
			pCharacter->SetHP(fHP);
			pCharacter->SetAP(fAP);
		}
	}

Find <br>

	void ZGame::OnPeerDuelTournamentHPAPInfo(MCommand *pCommand)
	{
		MUID uid = pCommand->GetSenderUID();
		ZCharacter* pCharacter = m_CharacterManager.Find(uid);
		if (!pCharacter) return;

		BYTE MaxHP = 0;
		BYTE MaxAP = 0;
		BYTE HP = 0;
		BYTE AP = 0;

		pCommand->GetParameter(&MaxHP, 0, MPT_UCHAR);	
		pCommand->GetParameter(&MaxAP, 1, MPT_UCHAR);

		pCommand->GetParameter(&HP, 2, MPT_UCHAR);	
		pCommand->GetParameter(&AP, 3, MPT_UCHAR);

		if(ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_DUELTOURNAMENT) {
			((ZRuleDuelTournament*)m_Match.GetRule())->SetPlayerHpApForUI(uid, (float)MaxHP, (float)MaxAP, (float)HP, (float)AP);
		}

		if(ZGetGameInterface()->GetCombatInterface()->GetObserverMode()) {
			pCharacter->SetMaxHP((float)MaxHP);
			pCharacter->SetMaxAP((float)MaxAP);
			pCharacter->SetHP((float)HP);
			pCharacter->SetAP((float)AP);
		}
	}
	
Change <br>

	void ZGame::OnPeerDuelTournamentHPAPInfo(MCommand *pCommand)
	{
		MUID uid = pCommand->GetSenderUID();
		ZCharacter* pCharacter = m_CharacterManager.Find(uid);
		if (!pCharacter) return;

		BYTE MaxHP = 0;
		BYTE MaxAP = 0;
		BYTE HP = 0;
		BYTE AP = 0;

		pCommand->GetParameter(&MaxHP, 0, MPT_UCHAR);
		pCommand->GetParameter(&MaxAP, 1, MPT_UCHAR);

		pCommand->GetParameter(&HP, 2, MPT_UCHAR);
		pCommand->GetParameter(&AP, 3, MPT_UCHAR);

		if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_DUELTOURNAMENT) {
			((ZRuleDuelTournament*)m_Match.GetRule())->SetPlayerHpApForUI(uid, (float)MaxHP, (float)MaxAP, (float)HP, (float)AP);
		}

		//<Logic of de HP/AP>
		if (pCharacter->GetUID() != ZGetMyUID() && uid != ZGetMyUID())
		{
			pCharacter->SetMaxHP((float)MaxHP);
			pCharacter->SetMaxAP((float)MaxAP);
			pCharacter->SetHP((float)HP);
			pCharacter->SetAP((float)AP);
		}
		if (ZGetGameInterface()->GetCombatInterface()->GetObserverMode())
		{
			pCharacter->SetMaxHP((float)MaxHP);
			pCharacter->SetMaxAP((float)MaxAP);
			pCharacter->SetHP((float)HP);
			pCharacter->SetAP((float)AP);
		}
	}

Open (ZOptionInterface.cpp) <br>
Find <br>

	static int heights[]={ 480,600,768,960,1200,800,900, 1050, 1200, 1600};
	
Change <br>

	static int widths[] = { 800, 1024, 1280, 1280, 1366, 1600, 1280, 1440, 1600, 1650, 1920, 1920, 2560 };
	static int heights[] = { 600, 768, 720, 960, 768, 1200, 800, 900, 900, 1050, 1080, 1200, 1600 };

Open(RBspObject.cpp) <br>
Find <br>

	for(int j=0;j<3;j++) {
		BSPVERTEX *pv = &m_pOcVertices[indices[j]] + pNode->m_nBaseVertexIndex;
		v[j].coord = *pv->Coord();
		v[j].tu2 = pv->tu1;
		v[j].tv2 = pv->tv1;
	}
	
Change <br>

	for(int j=0;j<3;j++) {
	//<Dynamic light fix>
		BSPVERTEX *pv = &m_pOcVertices[indices[j]] + pNode->m_nBaseVertexIndex;;
		v[j].coord = *pv->Coord();
		v[j].tu2 = pv->tu1;
		v[j].tv2 = pv->tv1;
	}
	
Open(RealSpace2.h) <br>
Find <br>

	void RSetFrameLimitPerSeceond(unsigned short nFrameLimit)
	{
		g_nFrameLimitValue = nFrameLimit;
	}
	
Change <br>

	void RSetFrameLimitPerSeceond(unsigned short nFrameLimit)
	{
		switch (nFrameLimit)
		{
		case 0:	{	g_nFrameLimitValue = 0;		}	break;
		case 1:	{	g_nFrameLimitValue = 60;	}	break;
		case 2:	{	g_nFrameLimitValue = 120;	}	break;
		case 3:	{	g_nFrameLimitValue = 240;	}	break;
		default:{	g_nFrameLimitValue = 0;		}	break;
		}
	}
	
Open(RealSpace2.cpp) <br>
Find <br>

	void RAdjustWindow(const RMODEPARAMS *pModeParams)

Change <br>

	if(pModeParams->bFullScreen)
	{
		SetWindowLong( g_hWnd, GWL_STYLE, WS_POPUP | WS_SYSMENU );
	}
	else
		SetWindowLong(g_hWnd, GWL_STYLE, WS_VISIBLE | WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX);

Open(MMatchServer_Stage.cpp)<br>
Find <br>

	if (MMUG_EVENTMASTER == pObj->GetAccountInfo()->m_nUGrade) {
		OnEventChangeMaster(pObj->GetUID());
	}
	
Change <br>

	//Disable auto change master for UGrade 252
	//if (MMUG_EVENTMASTER == pObj->GetAccountInfo()->m_nUGrade) {
	//	OnEventChangeMaster(pObj->GetUID());
	//}

Open(ZCharacter.cpp) <br>
Find <br>

	float fAddedAP = DEFAULT_CHAR_AP;
	for (int i = 0; i < MMCIP_END; i++) {
		if (!m_Items.GetItem(MMatchCharItemParts(i))->IsEmpty()) {

			if(m_Items.GetItem(MMatchCharItemParts(i))->GetDesc()->m_nAP.Ref() > 40) {
				m_Items.GetItem(MMatchCharItemParts(i))->GetDesc()->m_nAP.Ref() = 0; 
			}
			fAddedAP += m_Items.GetItem(MMatchCharItemParts(i))->GetDesc()->m_nAP.Ref();
		}
	}
	
Change <br>

		float fAddedAP = DEFAULT_CHAR_AP;
		for (int i = 0; i < MMCIP_END; i++) {
			if (!m_Items.GetItem(MMatchCharItemParts(i))->IsEmpty()) {

				//Bypass AP limit of 40 (MAIET trap check)
				//if(m_Items.GetItem(MMatchCharItemParts(i))->GetDesc()->m_nAP.Ref() > 40) {
				//	m_Items.GetItem(MMatchCharItemParts(i))->GetDesc()->m_nAP.Ref() = 0; 
				//}
				fAddedAP += m_Items.GetItem(MMatchCharItemParts(i))->GetDesc()->m_nAP.Ref();
			}
		}

Open(MClient.cpp) <br>
Find <br>

		case MC_LOCAL_ECHO:
			if(pCommand->GetParameter(szMessage, 0, MPT_STR, sizeof(szMessage))==false) break;
			OutputMessage(szMessage, MZMOM_LOCALREPLY);
		break;

Change <br>

		case MC_LOCAL_ECHO:
			//Exploit fix (Fake echo from different player)
			//if(pCommand->GetParameter(szMessage, 0, MPT_STR, sizeof(szMessage))==false) break;
			//OutputMessage(szMessage, MZMOM_LOCALREPLY);
		break;

Find <br>

		case MC_NET_DISCONNECT:
			Disconnect(m_Server);
		break;
		
Change <br>

		case MC_NET_DISCONNECT:
			//Exploit fix (Fake disconnect from different player)
			if (pCommand->GetSenderUID() != GetUID())
			{
				break;
			}
			Disconnect(m_Server);
		break;

Open(MMatchServer_Agent.cpp) <br>
Find <br>

	void MMatchServer::OnRegisterAgent(const MUID& uidComm, char* szIP, int nTCPPort, int nUDPPort)
	{
	
Add under <br>

	//Fix agent invalid ip crash
	if (strstr(szIP, "%") != NULL)
	{
		return;
	}
	
Find <br>

	void MMatchServer::AgentClear()
	{
		MAgentObjectMap::iterator i = m_AgentMap.begin();
		for(;i!=m_AgentMap.end(); i++)
		{
			AgentRemove( i->first, &i);
		}
	}
	
Change <br>

	void MMatchServer::AgentClear()
	{
		MAgentObjectMap::iterator i = m_AgentMap.begin();
		//Iterator dereference fix
		for (; i != m_AgentMap.end();)
		{
			AgentRemove(i->first, &i);
		}
	}
	
Find <br>

	pChar->SetRelayPeer(true);
	LOG(LOG_DEBUG, "%s Request relay peer on %s", pChar->GetName(), pPeer->GetName());
	
Change <br>

	pChar->SetRelayPeer(true);
	//Logfix, added newline
	LOG(LOG_DEBUG, "%s Request relay peer on %s\n", pChar->GetName(), pPeer->GetName());

Open(ZScreenEffectManager.cpp) <br>
Find <br>

	void ZScreenEffectManager::DrawCombo()
	
Add under <br>

	//VMesh NULL and GetFrameInfo fix
	if (m_pComboEffects[i]->GetVMesh() == NULL) continue;
	if (m_pComboEffects[i]->GetVMesh()->GetFrameInfo(ani_mode_lower) == NULL) continue;

Open(RCamera.cpp) <br>
Find <br>

	void RSetProjection(float fFov,float fAspect,float fNearZ,float fFarZ)

Add under <br>

	FLOAT fAspect = (FLOAT)RGetScreenWidth() / (FLOAT)RGetScreenHeight();
	
Open(RealSpace2.cpp) <br>
Find <br>

	if(g_rsnRenderFlags && RRENDER_CLEAR_BACKBUFFER)
	{
		//if(g_bStencilBuffer)
			//g_pd3dDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER |D3DCLEAR_STENCIL ,g_clear_color,1.0f ,0L);
		//else
			g_pd3dDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,g_clear_color,1.0f ,0L);
	}
	else
		g_pd3dDevice->Clear(0,NULL,D3DCLEAR_ZBUFFER ,g_clear_color,1.0f ,0);
		
Change <br>

	//Replaced && to &
	if (g_rsnRenderFlags & RRENDER_CLEAR_BACKBUFFER)
	{
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, g_clear_color, 1.0f, 0L);
	}
	else
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, g_clear_color, 1.0f, 0);

Open(ZInterfaceListener.cpp) <br>
Find <br>

			int nPlayerCnt = (int)ZGetGameClient()->GetMatchStageSetting()->m_CharSettingList.size();
			if(nPlayerCnt > pStageSetting->nMaxPlayers && nPlayerCnt!=0 && pStageSetting->nMaxPlayers!=0)
			{
				char szText[128] = {0,};
				sprintf(szText, "%s\n", ZErrStr(MERR_PERSONNEL_TOO_MUCH));
				ZGetGameInterface()->ShowMessage(szText);
				return false;
			}

Replace <br>

			//Disabled too many players popup client-side
			int nPlayerCnt = (int)ZGetGameClient()->GetMatchStageSetting()->m_CharSettingList.size();
			if (nPlayerCnt > pStageSetting->nMaxPlayers && nPlayerCnt != 0 && pStageSetting->nMaxPlayers != 0 && (ZGetGameTypeManager()->IsQuestDerived(pStageSetting->nGameType)))
			{
				char szText[128] = { 0, };
				sprintf(szText, "%s\n", ZErrStr(MERR_PERSONNEL_TOO_MUCH));
				ZGetGameInterface()->ShowMessage(szText);
				return false;
			}

Open(ZGameInterface_OnCommand.cpp) <br>
Find <br>

	case MC_MATCH_STAGE_RESPONSE_QUICKJOIN:
		{
			if (ZApplication::GetGameInterface()->GetState() == GUNZ_LOBBY)
			{
				int nResult;
				pCommand->GetParameter(&nResult, 0, MPT_INT);
				if (nResult != MOK)
				{
					ZApplication::GetGameInterface()->ShowErrorMessage( nResult );
				}

				MUID uidStage;
				pCommand->GetParameter(&uidStage, 1, MPT_UID);

				ZPostRequestStageJoin(ZGetGameClient()->GetPlayerUID(), uidStage);
			}
		}
		break;
		
Replace <br>

	case MC_MATCH_STAGE_RESPONSE_QUICKJOIN:
		{
			if (ZApplication::GetGameInterface()->GetState() == GUNZ_LOBBY)
			{
				int nResult;
				pCommand->GetParameter(&nResult, 0, MPT_INT);
				if (nResult != MOK)
				{
					ZApplication::GetGameInterface()->ShowErrorMessage( nResult );
				}

				MUID uidStage;
				pCommand->GetParameter(&uidStage, 1, MPT_UID);

				ZPostRequestStageJoin(ZGetGameClient()->GetPlayerUID(), uidStage);
				//Fix quick join glitch (room tags)
				ZApplication::GetGameInterface()->EnableLobbyInterface(true);
			}
		}
		break;

Find <br>

	case MC_MATCH_STAGE_REQUIRE_PASSWORD:
		{
			MUID uidStage = MUID(0,0);
			char szStageName[256];
			pCommand->GetParameter(&uidStage, 0, MPT_UID);
			pCommand->GetParameter(szStageName, 1, MPT_STR, sizeof(szStageName) );

			ZRoomListBox* pRoomList;
			pRoomList = (ZRoomListBox*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "Lobby_StageList" );
			if ( pRoomList != NULL ) pRoomList->SetPrivateStageUID(uidStage);

			ZApplication::GetGameInterface()->ShowPrivateStageJoinFrame(szStageName);
		}
		break;

Replace <br>

	case MC_MATCH_STAGE_REQUIRE_PASSWORD:
		{
			MUID uidStage = MUID(0,0);
			char szStageName[256];
			pCommand->GetParameter(&uidStage, 0, MPT_UID);
			pCommand->GetParameter(szStageName, 1, MPT_STR, sizeof(szStageName) );

			//Event Team join fix
			ZApplication::GetGameInterface()->EnableLobbyInterface(true);

			ZRoomListBox* pRoomList;
			pRoomList = (ZRoomListBox*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "Lobby_StageList" );
			if ( pRoomList != NULL ) pRoomList->SetPrivateStageUID(uidStage);

			ZApplication::GetGameInterface()->ShowPrivateStageJoinFrame(szStageName);
		}
		break;


Open(ZCharacterManager.cpp) <br>
Find <br>

	void ZCharacterManager::Delete(MUID uid)
	{
		iterator itor = find(uid);

		if (itor != end()) {

			ZCharacter* pCharacter = (*itor).second;

			ZGetObjectManager()->Delete((ZObject*)pCharacter);

			ZGetGame()->m_VisualMeshMgr.Del(pCharacter->m_nVMID.Ref());
			delete pCharacter; pCharacter = NULL;
			erase(itor);
		}
	}
	
Replace <br>

	void ZCharacterManager::Delete(MUID uid)
	{
		iterator itor = find(uid);

		if (itor != end()) {

			ZCharacter* pCharacter = (ZCharacter*)(*itor).second;

			ZGetObjectManager()->Delete((ZObject*)pCharacter);

			ZGetGame()->m_VisualMeshMgr.Del(pCharacter->m_nVMID.Ref());

			//Safe delete
			SAFE_DELETE(pCharacter);

			//delete pCharacter; pCharacter = NULL;
			erase(itor);
		}
	}

Open (ZGame.cpp) <br>
Find <br>

	const char *szAnonymous = "?¾Æ¹«°³?";
	
Replace <br>

	const char* szAnonymous = "?Unknown?";

Open(ZinitialLoading.cpp) <br>
Find

			while ((RGetScreenWidth()-70) > (pFont->GetWidth(temp)))
			{
				strcat(temp, "³²");
			}
			
Replace <br>

			while ((RGetScreenWidth()-70) > (pFont->GetWidth(temp)))
			{
				//changed text
				strcat(temp, "..");//"³²");
			}

Open(MMatchRule.cpp) <br>
Find

	void MMatchRule::OnRoundEnd()
	
Replace <br>

	void MMatchRule::OnRoundEnd()
	{
		///Clearsuicide list on each new round if size > 0
		if (GetStage()->GetSuicideList().size() > 0)
			GetStage()->GetSuicideList().clear();
	}
