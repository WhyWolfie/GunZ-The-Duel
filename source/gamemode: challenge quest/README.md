Gamemode: Challenge Quest <br>

Not Finished! <br>
CSCommon <br>
- MMatchRuleQuestChallenge.cpp <br>
- MMatchRuleQuestChallenge.h <br>
- IMatchRuleNewQuest.h <br>
- IMatchRuleNewQuest.cpp <br>
- MNewQuestScenario.h <br>
- MNewQuestScenario.cpp <br>
- MActorDef.h <br>
- MActorDef.cpp <br>
- MNewQuestPlayerManager.cpp <br>
- MNewQuestPlayerManager.h <br>
- MNewQuestNpcManager.h <br>
- MNewQuestNpcManager.cpp <br>

Gunz <br>
- ZActorWithFSM.h
- ZActorBase.h
- ZActorBase.cpp
- ZFSMCondition.h
- ZFSMStateEnteredTimeStamper.h
- ZFSMFunctionServer.h
- MActorDef.h
- ZFSMGlobal.h
- ZRuleQuestChallenge.cpp
- ZRuleQuestChallenge.h
- ZActorBase.h
- IRuleNewQuest.cpp
- IRuleNewQuest.h
- ZFSMCondition.h
- ZFSMStateEnteredTimeStamper.h
- ZFSMManager.h
- ZActorActionManager.h
- ZActorAction.h
- ZFSMParser.h
- ZFSM.h
- ZFSMState.h
- ZNavigationMesh.h
- ZWorldObject_Navigation.cpp
- ZWorldObject_Navigation.h
- ZWorldObject.cpp
- ZWorldObject.h
- ZWorldObject_Movable.cpp
- ZWorldObject_Movable.h
- ZObjectVMesh.cpp
- ZObjectVMesh.h
- ZActorAction.cpp
- ZFSMState.cpp
- ZFSMState.h
- ZFSMTransition.h
- ZFSMTransition.cpp
- ZFSM.cpp
- ZFSMCondition.cpp
- ZActorActionManager.cpp
- ZFSMFunctionServer.cpp
- ZFSMManager.cpp
- ZFSMParser.cpp

Open(MBaseGameType.h) <br>
Find <br>

    enum MMATCH_GAMETYPE {

Add <br>

    MMATCH_GAMETYPE_QUEST_CHALLENGE		=24,
    
Find <br>

    inline bool MBaseGameTypeCatalogue::IsQuestOnly(MMATCH_GAMETYPE nGameType)
    {
      return nGameType == MMATCH_GAMETYPE_QUEST;
    }

Add <br>

    inline bool MBaseGameTypeCatalogue::IsNewQuestDerived(MMATCH_GAMETYPE nGameType)
    {
      if ((nGameType == MMATCH_GAMETYPE_QUEST_CHALLENGE))
        return true;

      return false;
    }

Find <br>

    inline bool MBaseGameTypeCatalogue::IsWorldItemSpawnEnable(MMATCH_GAMETYPE nGameType)
    {
      if ( (nGameType == MMATCH_GAMETYPE_SURVIVAL) ||(nGameType == MMATCH_GAMETYPE_QUEST))
      {
        return false;
      }

      return true;

    }

Add <br>

    inline bool MBaseGameTypeCatalogue::IsWorldItemSpawnEnable(MMATCH_GAMETYPE nGameType)
    {
      if ( (nGameType == MMATCH_GAMETYPE_SURVIVAL) || (nGameType == MMATCH_GAMETYPE_QUEST) || (nGameType == MMATCH_GAMETYPE_QUEST_CHALLENGE))
      {
        return false;
      }

      return true;

    }

Find <br>

	inline bool IsQuestDerived(MMATCH_GAMETYPE nGameType);	///< ÇØ´ç °ÔÀÓÅ¸ÀÔÀÌ Äù½ºÆ® °ü·Ã(NPC°¡ ³ª¿À´ÂÁö)ÀÎÁö ¿©ºÎ

Add <br>

	inline bool IsNewQuestDerived(MMATCH_GAMETYPE nGameType);

Open(MMatchStage.cpp) <br>
Find <br>

			if ( MGetGameTypeMgr()->IsQuestDerived(pStage->GetStageSetting()->GetGameType()))
			{ // Äù½ºÆ® ¹× ¼­¹ÙÀÌ¹ö¿¡¼­ ÀÚ»ìÇÒ¶§ ÀÚ»ì º»ÀÎ¿Ü¿¡´Â Á×´Â Ã³¸®°¡ ¾ÈµÅÀÖ¾î¼­ Ãß°¡ÇÔ
				// Á×¾ú´Ù´Â ¸Þ¼¼Áö º¸³¿
				MCommand* pCmd = MGetMatchServer()->CreateCommand(MC_MATCH_QUEST_PLAYER_DEAD, MUID(0,0));
				pCmd->AddParameter(new MCommandParameterUID(it->m_uidUser));
				MGetMatchServer()->RouteToBattle(pStage->GetUID(), pCmd);	
			}

Replace <br>

			if ( MGetGameTypeMgr()->IsQuestDerived(pStage->GetStageSetting()->GetGameType()) ||
				MGetGameTypeMgr()->IsNewQuestDerived(pStage->GetStageSetting()->GetGameType()))
			{ // Äù½ºÆ® ¹× ¼­¹ÙÀÌ¹ö¿¡¼­ ÀÚ»ìÇÒ¶§ ÀÚ»ì º»ÀÎ¿Ü¿¡´Â Á×´Â Ã³¸®°¡ ¾ÈµÅÀÖ¾î¼­ Ãß°¡ÇÔ
				// Á×¾ú´Ù´Â ¸Þ¼¼Áö º¸³¿
				MCommand* pCmd = MGetMatchServer()->CreateCommand(MC_MATCH_QUEST_PLAYER_DEAD, MUID(0,0));
				pCmd->AddParameter(new MCommandParameterUID(it->m_uidUser));
				MGetMatchServer()->RouteToBattle(pStage->GetUID(), pCmd);	
			}

Open(ZCharacter.cpp) <br>
Find<br>

	// Äù½ºÆ® °ü·Ã °ÔÀÓÅ¸ÀÔÀÏ °æ¿ì¿¡¸¸ QuestStatus »ý¼º, µî·Ï
	if (ZGetGameTypeManager()->IsQuestDerived(ZGetGameClient()->GetMatchStageSetting()->GetGameType()))
	{
		m_pModule_QuestStatus = new ZModule_QuestStatus();
		AddModule(m_pModule_QuestStatus);
	}

Replace <br>

	// Äù½ºÆ® °ü·Ã °ÔÀÓÅ¸ÀÔÀÏ °æ¿ì¿¡¸¸ QuestStatus »ý¼º, µî·Ï
	if (ZGetGameTypeManager()->IsQuestDerived(ZGetGameClient()->GetMatchStageSetting()->GetGameType())||
		ZGetGameTypeManager()->IsNewQuestDerived(ZGetGameClient()->GetMatchStageSetting()->GetGameType()))
	{
		m_pModule_QuestStatus = new ZModule_QuestStatus();
		AddModule(m_pModule_QuestStatus);
	}

Open(ZCombatInterface.cpp) <br>
Find <br>

	pWidget = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "DuelTournamentResult");
	if ( pWidget)  pWidget->Show( false);

Add <br>

	pWidget = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("ChallengeQuestResult");
	if ( pWidget) pWidget->Show(false);

Find <br>

	else if ( ZGetGameTypeManager()->IsSurvivalOnly(ZGetGame()->GetMatch()->GetMatchType()))	// ¼­¹ÙÀÌ¹úÀÌ¸é...
	{

Add <br>

	else if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_QUEST_CHALLENGE)
	{
		strcpy(szFileName, "interface/loadable/rstbg_challenge.jpg");
		pWidget = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("ChallengeQuestResult");
		if (pWidget)
			pWidget->Show(true);

		ZBmNumLabel* pBmNumLabel = (ZBmNumLabel*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("CQ_Result_Cleard");
		if (pBmNumLabel)
			pBmNumLabel->SetNumber(0, false);

		pBmNumLabel = (ZBmNumLabel*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("CQ_Result_ElapsedTime");
		if (pBmNumLabel)
			pBmNumLabel->SetNumber(0, false);

		pBmNumLabel = (ZBmNumLabel*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("CQ_Result_XP");
		if (pBmNumLabel)
			pBmNumLabel->SetNumber(0, false);

		pBmNumLabel = (ZBmNumLabel*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("CQ_Result_BP");
		if (pBmNumLabel)
			pBmNumLabel->SetNumber(0, false);
	}

Open(ZGame.cpp) <br>
Find <br>

	else if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_DUELTOURNAMENT)
	{

Add <br>

	if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_QUEST_CHALLENGE)
	{
		ZRuleQuestChallenge* pRule = dynamic_cast<ZRuleQuestChallenge*>(ZGetGame()->GetMatch()->GetRule());

		int npcCount = ZGetObjectManager()->GetNPCObjectMap()->size();
		nWritten = zfwrite(&npcCount, sizeof(int), 1, m_pReplayFile);
		if (nWritten == 0)
			goto RECORDING_FAIL;

		for (auto itor = ZGetObjectManager()->GetNPCObjectMap()->begin(); itor != ZGetObjectManager()->GetNPCObjectMap()->end(); ++itor)
		{
			ZActorWithFSM* npcObj = (ZActorWithFSM*)(*itor).second;
			if (!npcObj->Save(m_pReplayFile)) goto RECORDING_FAIL;
		}
	}

Open(ZMap.cpp) <br>
Find <br>

    void ZGetCurrMapPath(char* outPath)
    {
    // ³ªÁß¿¡ ·£´ý¸Ê ±¸ÇöÇÒ¶§±îÁö ±×³É ¸Ê ÇÏ³ª¸¸ »ç¿ë
    #ifdef _QUEST


      if (ZGetGameTypeManager()->IsQuestDerived(ZGetGameClient()->GetMatchStageSetting()->GetGameType()))
      {
        strcpy(outPath, PATH_QUEST_MAPS);
        return;
      }
    #endif

Add <br>

	if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_QUEST_CHALLENGE)
	{
		strcpy(outPath, "challengequest/maps/");
		return;
	}

Find <br>

	MChannelRule* pRule = ZGetChannelRuleMgr()->GetCurrentRule();
	if (pRule == NULL) {
		mlog("Init maps : no Current ChannelRule \n");
		return false;
	}

Add Above <br>

	if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_QUEST_CHALLENGE)
	{
		MNewQuestScenarioManager* pScenarioMgr = ZApplication::GetStageInterface()->GetChallengeQuestScenario();
		_ASSERT(pScenarioMgr);
		if (pScenarioMgr)
		{
			vector<string> vecScenario;
			pScenarioMgr->GetScenarioNameList( vecScenario);

			int numScenario = (int)vecScenario.size();
			for (int i=0; i<numScenario; ++i)
				pCombo->Add(vecScenario[i].c_str());
		}
		return true;
	}

Open(ZStageInterface.cpp) <br>
Find <br>

	m_bRelayMapRegisterComplete = true;
	m_bEnableWidgetByRelayMap = true;

Add <br>

	m_pChallengeQuestScenario = new MNewQuestScenarioManager;

Find <br>

    ZStageInterface::~ZStageInterface( void)
    {
      if ( m_pTopBgImg != NULL)
      {
        delete m_pTopBgImg;
        m_pTopBgImg = NULL;
      }

      if ( m_pStageFrameImg != NULL)
      {
        delete m_pStageFrameImg;
        m_pStageFrameImg = NULL;
      }
    }

Replace <br>

    ZStageInterface::~ZStageInterface( void)
    {
      if ( m_pTopBgImg != NULL)
      {
        delete m_pTopBgImg;
        m_pTopBgImg = NULL;
      }

      if ( m_pStageFrameImg != NULL)
      {
        delete m_pStageFrameImg;
        m_pStageFrameImg = NULL;
      }

      delete m_pChallengeQuestScenario;
    }

Find <br>

	m_SacrificeItem[ SACRIFICEITEM_SLOT0].RemoveItem();
	m_SacrificeItem[ SACRIFICEITEM_SLOT1].RemoveItem();

	ReadSenarioNameXML();


Add <br>

	_ASSERT(m_pChallengeQuestScenario);
	m_pChallengeQuestScenario->ReadXml(ZApplication::GetFileSystem(), "system/scenario2.xml", ZGetQuest()->GetDropTable());

Find <br>

	MAnimation* pAniMapImg = (MAnimation*)pResource->FindWidget( "Stage_MapNameBG");
	bool bQuestUI = false;

Replace <br>

	MAnimation* pAniMapImg = (MAnimation*)pResource->FindWidget( "Stage_MapNameBG");
	bool bQuestUI = false;
	bool bChallengeQuestUI = false;

Find <br>

    bQuestUI = false;

Add <br>

    bChallengeQuestUI = false;

Find <br>

    bQuestUI = false;

Add <br>

    bChallengeQuestUI = false;


Find <br>

    bQuestUI = false;

Add <br>

    bChallengeQuestUI = false;


Find <br>

    bQuestUI = false;

Add <br>

    bChallengeQuestUI = false;


Find <br>

    bQuestUI = false;

Add <br>

    bChallengeQuestUI = false;

Find <br>

    bQuestUI = false;

Add <br>

    bChallengeQuestUI = false;

Find <br>

	if ((pSetting->nGameType == MMATCH_GAMETYPE_SURVIVAL) || (pSetting->nGameType == MMATCH_GAMETYPE_QUEST) || (pSetting->nGameType == MMATCH_GAMETYPE_SPY))
		ZApplication::GetGameInterface()->EnableWidget("StageSettingCaller", false);

Add <br>

	ZApplication::GetGameInterface()->ShowWidget("Stage_SenarioDescription", bChallengeQuestUI);
	ZApplication::GetGameInterface()->ShowWidget("Stage_SenarioTitle", bChallengeQuestUI);
	ZApplication::GetGameInterface()->ShowWidget("Stage_GoodTime", bChallengeQuestUI);

	if (bChallengeQuestUI)
	{
		char szText[256];
		MNewQuestScenarioManager* pNewScenarioMgr = ZApplication::GetStageInterface()->GetChallengeQuestScenario();
		if (pNewScenarioMgr)
		{
			MNewQuestScenario* pNewScenario = pNewScenarioMgr->GetScenario(pSetting->szMapName);
			if (pNewScenario)
			{
				MTextArea* pNewScenarioDesc = (MTextArea*)pResource->FindWidget("Stage_SenarioDescription");
				if (pNewScenarioDesc)
				{
					pNewScenarioDesc->SetText(pNewScenario->GetDesc());
				}

				MLabel* pNewScenarioTitle = (MLabel*)pResource->FindWidget("Stage_SenarioTitle");
				if (pNewScenarioTitle)
				{
					pNewScenarioTitle->SetText(pNewScenario->GetName());
				}

				MLabel* pGoodTime = (MLabel*)pResource->FindWidget("Stage_GoodTime");
				if (pGoodTime)
				{
					sprintf(szText, "Good Time : %d:%02d", pNewScenario->GetGoodTime() / 60, pNewScenario->GetGoodTime() % 60);
					pGoodTime->SetText(szText);
				}
				MPicture* pPicture = 0;
				MBitmap* pBitmap = 0;
				char szMapName[256];
				pPicture = (MPicture*)pResource->FindWidget("Stage_MainBGTop");
				if (pPicture)
				{
					if (((pNewScenario->GetMapID() == 101) || (pNewScenario->GetMapID() == 201) || (pNewScenario->GetMapID() == 301) ||
						(pNewScenario->GetMapID() == 401) || (pNewScenario->GetMapID() == 403)))
						sprintf(szMapName, "interface/default/map_ChallengeQuest_Guerilla.bmp");
					else
						sprintf(szMapName, "interface/default/map_ChallengeQuest_Research.bmp");

					if (m_pTopBgImg != NULL)
					{
						delete m_pTopBgImg;
						m_pTopBgImg = NULL;
					}

					m_pTopBgImg = new MBitmapR2;
					((MBitmapR2*)m_pTopBgImg)->Create("TopBgImg.png", RGetDevice(), szMapName);

					if (m_pTopBgImg != NULL)
						pPicture->SetBitmap(m_pTopBgImg->GetSourceBitmap());
				}
			}
		}
	}

Open(ZStageInterface.h) <br>
Find <br>

    bool			m_bEnableWidgetByRelayMap

Add <br>

    MNewQuestScenarioManager* m_pChallengeQuestScenario;

Open(MMatchServer_Stage.cpp) <br>
Find <br>

	if ( MGetGameTypeMgr()->IsQuestDerived( pStage->GetStageSetting()->GetGameType()))
	{
		MMatchRuleBaseQuest* pQuest = reinterpret_cast< MMatchRuleBaseQuest* >( pStage->GetRule() );
		pQuest->RefreshStageGameInfo();
	}

Add <br>

	if (pStage->GetStageSetting()->GetGameType() == MMATCH_GAMETYPE_QUEST_CHALLENGE)
	{
		MMatchRuleQuestChallenge* challengeQuest = reinterpret_cast<MMatchRuleQuestChallenge*>(pStage->GetRule());
		challengeQuest->RefreshStageGameInfo();
	}

Find <br>

	if (nLastGameType != pSetting->GetGameType())
	{
		char szNewMap[ MAPNAME_LENGTH ] = {0};

Replace <br>

      if (nLastGameType != pSetting->GetGameType())
      {
        char szNewMap[MAPNAME_LENGTH] = { 0 };

        // Æ¯¼öÇÑ ¸ðµåµé (¸Ê ¸ñ·ÏÀÌ À¯º°³­ °Íµé)
        bool bLast_QuestOrSurvival = MGetGameTypeMgr()->IsQuestDerived(nLastGameType);
        bool bCurr_QuestOrSurvival = MGetGameTypeMgr()->IsQuestDerived(pSetting->GetGameType());

        bool bLast_Duel = nLastGameType == MMATCH_GAMETYPE_DUEL;
        bool bCurr_Duel = pSetting->GetGameType() == MMATCH_GAMETYPE_DUEL;

        bool bLast_ChallengeQuest = nLastGameType == MMATCH_GAMETYPE_QUEST_CHALLENGE;
        bool bCurr_ChallengeQuest = pSetting->GetGameType() == MMATCH_GAMETYPE_QUEST_CHALLENGE;

        // ±×¿Ü ÀÏ¹ÝÀûÀÎ ¸ðµåµé (µ¥½º¸ÅÄ¡ µî)
        //bool bLast_Other = !bLast_QuestOrSurvival && !bLast_Duel && !bLast_ChallengeQuest && nLastGameType != MMATCH_GAMETYPE_SKILLMAP;
        //bool bCurr_Other = !bCurr_QuestOrSurvival && !bCurr_Duel && !bCurr_ChallengeQuest && pSetting->GetGameType() != MMATCH_GAMETYPE_SKILLMAP;

        //bool bLast_SkillMap = nLastGameType == MMATCH_GAMETYPE_SKILLMAP;
        //bool bCurr_SkillMap = pSetting->GetGameType() == MMATCH_GAMETYPE_SKILLMAP;

        //bool bLast_BlitzKrieg = nLastGameType == MMATCH_GAMETYPE_BLITZKRIEG;
        //bool bCurr_BlitzKrieg = pSetting->GetGameType() == MMATCH_GAMETYPE_BLITZKRIEG;

        // Äù½ºÆ®³ª ¼­¹ÙÀÌ¹ú¿¡ ¸Â´Â ¸ÊÀ¸·Î º¯°æ
        if (!bLast_QuestOrSurvival && bCurr_QuestOrSurvival)
        {
          OnStageMap(uidStage, MMATCH_DEFAULT_STAGESETTING_MAPNAME, uidPlayer);

          MMatchRuleBaseQuest* pQuest = reinterpret_cast<MMatchRuleBaseQuest*>(pStage->GetRule());
          pQuest->RefreshStageGameInfo();
        }
        // µà¾ó¿¡ ¸Â´Â ¸ÊÀ¸·Î º¯°æ
        else if (!bLast_Duel && bCurr_Duel)
        {
          strcpy_s(szNewMap, MGetMapDescMgr()->GetMapName(MMATCH_MAP_HALL));
          OnStageMap(uidStage, szNewMap, uidPlayer);
        }
        else if (!bLast_ChallengeQuest && bCurr_ChallengeQuest)
        {
          MNewQuestScenarioManager* pScenarioMgr = MMatchRuleQuestChallenge::GetScenarioMgr();
          _ASSERT(pScenarioMgr);
          if (pScenarioMgr)
            OnStageMap(uidStage, (char*)pScenarioMgr->GetDefaultScenarioName(), uidPlayer);
        }
        // À§ÀÇ ¸ðµåµé¿¡¼­ ±âÅ¸ ¸ðµå·Î ¹Ù²ï °æ¿ì MansionÀ¸·Î ¼¼ÆÃ
        //else if (!bLast_Other && bCurr_Other)
        //{
        //	strcpy_s(szNewMap, MGetMapDescMgr()->GetMapName(MMATCH_MAP_MANSION));
        //	OnStageMap(uidStage, szNewMap, uidPlayer);
        //}
        //else if (!bLast_SkillMap && bCurr_SkillMap) {
        //	strcpy_s(szNewMap, MGetMapDescMgr()->GetMapName(MMATCH_MAP_SKILLMAP));
        //	OnStageMap(uidStage, szNewMap, uidPlayer);
        //}
        //else if (!bLast_SkillMap && bCurr_SkillMap) {
        //	strcpy_s(szNewMap, MGetMapDescMgr()->GetMapName(MMATCH_MAP_BLITZKRIEG));
        //	OnStageMap(uidStage, szNewMap, uidPlayer);
        //}

    //		if (MGetGameTypeMgr()->IsQuestDerived( nLastGameType ) == false &&
    //			MGetGameTypeMgr()->IsQuestDerived( pSetting->GetGameType() ) == true)
    //		{
    ////			OnStageMap(uidStage, GetQuest()->GetSurvivalMapInfo(MSURVIVAL_MAP(0))->szName);
    ////			OnStageMap(uidStage, pSetting->GetMapName());
    //			OnStageMap(uidStage, MMATCH_DEFAULT_STAGESETTING_MAPNAME);
    //
    //			MMatchRuleBaseQuest* pQuest = reinterpret_cast< MMatchRuleBaseQuest* >( pStage->GetRule());
    //			pQuest->RefreshStageGameInfo();
    //		}
    //		else if ( (nLastGameType != MMATCH_GAMETYPE_DUEL) && ( pSetting->GetGameType() == MMATCH_GAMETYPE_DUEL))
    //		{
    //			strcpy( szNewMap, MGetMapDescMgr()->GetMapName( MMATCH_MAP_HALL));
    //			OnStageMap(uidStage, szNewMap);
    //		}
    //		else if ( ((nLastGameType == MMATCH_GAMETYPE_QUEST) || (nLastGameType == MMATCH_GAMETYPE_SURVIVAL) || (nLastGameType == MMATCH_GAMETYPE_DUEL)) &&
    //			      ((pSetting->GetGameType() != MMATCH_GAMETYPE_QUEST) && (pSetting->GetGameType() != MMATCH_GAMETYPE_SURVIVAL) && ( pSetting->GetGameType() != MMATCH_GAMETYPE_DUEL)))
    //		{
    //			strcpy( szNewMap, MGetMapDescMgr()->GetMapName( MMATCH_MAP_MANSION));
    //			OnStageMap(uidStage, szNewMap);
    //		}
      }
    }

Open(MMatchServer.h) <br>
Find <br>

    void OnStageMap

Replace <br>

    void OnStageMap(const MUID& uidStage, char* pszMapName, const MUID& uidPlayer);

Open(MMatchServer_Stage.cpp) <br>
Find <br>

    void MMatchServer::OnStageMap(const MUID& uidStage, char* pszMapName)
    {

Add <br>

    void MMatchServer::OnStageMap(const MUID& uidStage, char* pszMapName, const MUID& uidPlayer)
    {

Open(MMatchServer_OnCommand.cpp) <br>
Find <br>

		case MC_MATCH_STAGE_MAP:
			{
				MUID uidStage;
				// Å¬¶óÀÌ¾ðÆ®¿¡¼­ ¸Ê ÀÌ¸§¸¸ Àü¼ÛÀÌ µÇ±â¶§¹®¿¡ _MAX_DIRÀº ÇÊ¿ä ¾øÀ½. - by SungE 2007-04-02
				char szMapName[ MAPNAME_LENGTH ] = {0,};

				pCommand->GetParameter(&uidStage, 0, MPT_UID);
				pCommand->GetParameter(szMapName, 1, MPT_STR, MAPNAME_LENGTH );

				OnStageMap(uidStage, szMapName);
			}
			break;

Replace <br>

		case MC_MATCH_STAGE_MAP:
			{
				MUID uidStage;
				// U?????T???? ?? ????? ?????? ??????? _MAX_DIR?? ??? ????. - by SungE 2007-04-02
				char szMapName[ MAPNAME_LENGTH ] = {0,};

				pCommand->GetParameter(&uidStage, 0, MPT_UID);
				pCommand->GetParameter(szMapName, 1, MPT_STR, MAPNAME_LENGTH );

				OnStageMap(uidStage, szMapName, pCommand->GetSenderUID());
			}
			break;

Open(MMatchServer_Stage.cpp) <br>
Find <br>

    #include "MMatchRuleBerserker.h"
    #include "MMatchRuleDuel.h"
    #include "MCrashDump.h"

Add <br>

    #include "MMatchRuleQuestChallenge.h"

Open(ZStageInterface.h) <br>
Find <br>

    #define SACRIFICEITEM_SLOT0		0
    #define SACRIFICEITEM_SLOT1		1

Add <br>

    #include "../CSCommon/MNewQuestScenario.h"

Open(ZStageInterface.h) <br>
Find <br>

    LIST_SCENARIONAME* GetSenarioDesc()							{ return &m_SenarioDesc;		}

Add <br>

	MNewQuestScenarioManager* GetChallengeQuestScenario() { return m_pChallengeQuestScenario; }

Open(ZGame.cpp) <br>
Find <br>

    #include "ZRuleDuel.h"
    #include "ZRuleDeathMatch.h"
    #include "ZMyCharacter.h"
    #include "MMatchCRC32XORCache.h"
    #include "MMatchObjCache.h"

Add <br>

    #include "ZActorWithFSM.h"
    #include "ZRuleQuestChallenge.h"

Open(ZReplay.h) <br>
Find <br>

    #pragma pack(push, old)
    #pragma pack(1)

Replace <br>

    #pragma pack(push, old)
    #pragma pack(1)

    struct MTD_ZActorWithFSMInfo_v0
    {
      char actorName[256];
      char modelName[256];
      MUID uid;
      float fHP, fAP;
      rvector Position, Direction, Velocity;
      int currAction;
      MMatchTeam teamID;
      bool isDie;
    };

Open(MSharedCommandTable.h) <br>
Find <br>

    #define MC_LOCAL_UPDATE_IP_TO_COUNTRY			50006
    #define MC_LOCAL_UPDATE_BLOCK_COUTRYCODE		50007
    #define MC_LOCAL_UPDATE_CUSTOM_IP				50008
    #define MC_LOCAL_UPDATE_ACCEPT_INVALID_IP		50009

Add <br>

    /// ½Å±ÔÄù½ºÆ®¿ë (Ã§¸°Áö Äù½ºÆ®)
    #define MC_NEWQUEST_NPC_SPAWN				6301	///< NPC ½ºÆù (S -> C)
    #define MC_NEWQUEST_REQUEST_NPC_SPAWN		6304	///< NPC ½ºÆE(C -> S)
    #define MC_NEWQUEST_REQUEST_NPC_DEAD		6302	///< NPC Á×À½ ¿äÃ»(C -> S)
    #define MC_NEWQUEST_NPC_DEAD				6303	///< NPC Á×À½(S -> C)
    #define MC_NEWQUEST_MOVE_TO_NEXT_SECTOR		6341	///< ´ÙÀ½ ¼½ÅÍ·Î ÀÌµ¿ (S -> C)
    #define MC_NEWQUEST_PEER_NPC_BASICINFO		6351	///< Á¤±âÀûÀ¸·Î ¾÷µ¥ÀÌÆ®µÇ´Â NPC ±âº»Á¤º¸
    #define MC_NEWQUEST_PEER_NPC_ACTION_EXECUTE	6404	///< NPC ¾×¼Ç ½ÃÀÛ
    #define MC_NEWQUEST_PEER_NPC_ATTACK_MELEE	6405	///< NPC ±ÙÁ¢°ø°Ý	//todok del ÀÌ°Ç ¾×¼Ç ½ÇÇàÅëÁö¸¦ ¹ÞÀ¸¸é peerµéÀÌ °¢ÀÚ Ã³¸®ÇÏ°Ô µÆ´Ù
    #define MC_NEWQUEST_NEW_CONTROLLER			6406
    #define MC_NEWQUEST_LATE_NPC_SPAWN			6407
    #define MC_NEWQUEST_STAGE_GAME_INFO			6408
    #define MC_MATCH_LATEJOIN_CQ			6409

Open(MSharedCommandTable.cpp) <br>
Find <br>


Add <br>

		C(MC_NEWQUEST_NPC_SPAWN,				"NewQuest.NPC.Spawn",	"NPC Spawn", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidController")
			P(MPT_UID, "uidNpc")
			P(MPT_STR, "szNpcDefName")	//todok ÆÐÅ¶ Àý¾àÀ» À§ÇØ ¹®ÀÚ¿­¸»°í enum°ªÀ» ³Ñ±æ ¼ö ÀÖ°Ô ÇÏÀÚ
			P(MPT_UCHAR, "nSpawnType")			// NPC ½ºÆù Á¾·ù ÀÎµ¦½º
			P(MPT_UCHAR, "PositionIndex")		// NPC ½ºÆù À§Ä¡ ÀÎµ¦½º

		C(MC_NEWQUEST_LATE_NPC_SPAWN, "", "", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidLateJoiner")
			P(MPT_UID, "uidNpc")
			P(MPT_STR, "szNpcDefName")	//todok ÆÐÅ¶ Àý¾àÀ» À§ÇØ ¹®ÀÚ¿­¸»°í enum°ªÀ» ³Ñ±æ ¼ö ÀÖ°Ô ÇÏÀÚ

		C(MC_NEWQUEST_REQUEST_NPC_DEAD,			"NewQuest.Request.NPCDead", "Request Npc Dead", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidKiller")
			P(MPT_UID, "uidNPC")
			P(MPT_SVECTOR, "NpcPosition")

		C(MC_NEWQUEST_NPC_DEAD,					"NewQuest.NPCDead", "Npc Dead", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidKiller")
			P(MPT_UID, "uidNPC")

		C(MC_NEWQUEST_MOVE_TO_NEXT_SECTOR,		"NewQuest.MoveToNextSector", "move to next sector", MCDT_MACHINE2MACHINE)

		C(MC_NEWQUEST_PEER_NPC_BASICINFO,		"NewQuest.Peer.NPC.BasicInfo",		"NPC BasicInfo", MCDT_PEER2PEER)
			P(MPT_BLOB, "Info")

		C(MC_NEWQUEST_PEER_NPC_ACTION_EXECUTE,	"NewQuest.Peer.NPC.Action.Execute",	"NPC Action Execute", MCDT_PEER2PEER)
			P(MPT_UID, "uidOwner")		// NPC
			P(MPT_INT, "ActionIndex")

		C(MC_NEWQUEST_PEER_NPC_ATTACK_MELEE,	"NewQuest.Peer.NPC.Attack.Melee",	"NPC Melee Attack", MCDT_PEER2PEER)
			P(MPT_UID, "uidOwner")		// ¶§¸° NPC
			P(MPT_STR, "szActionName")

		C(MC_NEWQUEST_REQUEST_NPC_SPAWN, "NewQuest.Request.NPCSpawn", "", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidController")
			P(MPT_UID, "uidNpc")
			P(MPT_INT, "nNum")
			P(MPT_STR, "szNpcDefName")	//todok ÆÐÅ¶ Àý¾àÀ» À§ÇØ ¹®ÀÚ¿­¸»°Eenum°ªÀ» ³Ñ±E¼EÀÖ°Ô ÇÏÀÚ
			P(MPT_SVECTOR, "Pos")
			P(MPT_SVECTOR, "Dir")
			P(MPT_INT, "route")

		C(MC_NEWQUEST_NEW_CONTROLLER, "", "", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "controller")
			P(MPT_UID, "npcUID")

		C(MC_NEWQUEST_STAGE_GAME_INFO,"","",MCDT_MACHINE2MACHINE)
			P(MPT_INT,"a")
			P(MPT_INT,"b")


		C(MC_MATCH_LATEJOIN_CQ,"","",MCDT_MACHINE2MACHINE)
			P(MPT_UID, "targetPlayer")
			P(MPT_INT, "currSector")
			P(MPT_UINT, "currTime")

Open(ZGame.cpp) <br>
Find <br>

	case MC_MATCH_DUEL_QUEUEINFO:
	case MC_MATCH_DUELTOURNAMENT_GAME_NEXT_MATCH_PLYAERINFO:
	case MC_MATCH_DUELTOURNAMENT_GAME_INFO:
	case MC_MATCH_DUELTOURNAMENT_GAME_ROUND_RESULT_INFO:
	case MC_MATCH_DUELTOURNAMENT_GAME_MATCH_RESULT_INFO:

Add <br>

	case MC_NEWQUEST_NPC_SPAWN:
	case MC_NEWQUEST_NPC_DEAD:
	case MC_NEWQUEST_PEER_NPC_BASICINFO:
	case MC_NEWQUEST_PEER_NPC_ACTION_EXECUTE:
	case MC_NEWQUEST_REQUEST_NPC_SPAWN:
	case MC_NEWQUEST_LATE_NPC_SPAWN:
	case MC_NEWQUEST_MOVE_TO_NEXT_SECTOR:
	case MC_NEWQUEST_NEW_CONTROLLER:
	case MC_MATCH_LATEJOIN_CQ:

Open(ZCharacter.h) <br>
Find <br>

	int GetDTLastWeekGrade() { return m_MInitialInfo.Ref().nDTLastWeekGrade; }
	MTD_CharInfo* GetCharInfo() const { return (MTD_CharInfo*)&m_MInitialInfo.Ref(); }

Add <br>

	MUID GetLastTarget() { return m_uidLastTarget; }
	void SetLastTarget(MUID uidTarget) { m_uidLastTarget = uidTarget; }

Find <br>

	MProtectValue<MTD_CharInfo>			m_MInitialInfo;

Add <br>

	MUID								m_uidLastTarget;

Open(ZMapDesc.cpp) <br>
Find <br>

	ZMapSpawnManager::ZMapSpawnManager()
	{
		for(int i=0;i>MAX_BACKUP_SPAWN;i++)
			m_nBackUpIndex[i] = -1;
		m_nBackUpIndexCnt = MAX_BACKUP_SPAWN;
	}

Replace <br>

	ZMapSpawnManager::ZMapSpawnManager()
	{
		for (int i = 0; i < 5; ++i)
		{
			m_nBackUpIndex[i] = -1;
		}
		m_nBackUpIndexCnt = MAX_BACKUP_SPAWN;
	}

Find <br>

	void ZMapSpawnManager::Clear()

Replace <br>

	void ZMapSpawnManager::Clear()
	{
		for (ZMapSpawnList::iterator itor = m_Spawns.begin(); itor != m_Spawns.end(); ++itor)
		{
			ZMapSpawnData* pSpawnData = (*itor);
			delete pSpawnData;
		}
		m_Spawns.clear();

		for (int i = 0; i < ZMST_MAX; i++)
		{
			m_SpawnArray[i].clear();
		}
		for (ZMapSpawnNpcCustom::iterator it=m_SpawnNpcCustom.begin(); it!=m_SpawnNpcCustom.end(); ++it)
		{
			delete it->second;
		}
		m_SpawnNpcCustom.clear();

		for (int i = 0; i < 5; ++i)
		{
			m_nBackUpIndex[i] = -1;
		}

		m_nBackUpIndexCnt = 0;
	}

	int ZMapSpawnManager::GetCustomSpawnCount(const char* szSpawnName)
	{
		ZMapSpawnNpcCustom::iterator it = m_SpawnNpcCustom.find(szSpawnName);
		if (it == m_SpawnNpcCustom.end())
			return 0;
		ZMapSpawnList* pSpawnList = it->second;
		return (int)pSpawnList->size();
	}

Find <br>

	//////////////////////////////////////////////////////////////////////////////
	ZMapDesc::ZMapDesc()

Add Above <br>

	rvector ZMapSpawnManager::GetRoutePos(ZMapSpawnType nSpawnType, char* name)
	{
		int nPositionsCount = GetSpawnCount(nSpawnType);
		if (nPositionsCount <= 0)
		{
			// ½ºÆù Æ÷Áö¼ÇÀÌ 1°³µµ ¾ø´Ù.
			//		_ASSERT(0);
			return rvector(0, 0, 0);
		}

		for (int i = 0; i < nPositionsCount; i++)
		{
			if (!_stricmp(m_SpawnArray[nSpawnType][i]->m_szSpawnName, name))
				return m_SpawnArray[nSpawnType][i]->m_Pos;
		}
		return rvector(0, 0, 0);
	}

Find <br>

	ZMapDesc::~ZMapDesc()

Replace <br>

	ZMapDesc::~ZMapDesc()
	{
		m_SmokeDummyMgr.Destroy();
		m_SpawnManager.Clear();
	}

Find <br>

		if (!strnicmp(pDummy->szName.c_str(), ZTOK_SPAWN, nSpawnTokLen))
		{
			char szSpawnName[256];
			strcpy(szSpawnName, szDummyName);

			m_SpawnManager.AddSpawnData(szSpawnName, pDummy->Position, pDummy->Direction);
		}

Replace <br>

		if (!strnicmp(pDummy->szName.c_str(), ZTOK_SPAWN, nSpawnTokLen)||
			!strnicmp(pDummy->szName.c_str(), "route_",(int)strlen("route_")))
		{
			char szSpawnName[256];
			strcpy(szSpawnName, szDummyName);

			m_SpawnManager.AddSpawnData(szSpawnName, pDummy->Position, pDummy->Direction);
		}


Find <br>

	#define ZTOK_SPAWN_NPC_MELEE	"spawn_npc_melee"
	#define ZTOK_SPAWN_NPC_RANGE	"spawn_npc_range"
	#define ZTOK_SPAWN_NPC_BOSS		"spawn_npc_boss"

Add <br>

	#define ZTOK_SPAWN			"spawn"
	#define ZTOK_SPAWN_SOLO		"spawn_solo"
	#define ZTOK_SPAWN_TEAM		"spawn_team"

	#define ZTOK_SPAWN_NPC_MELEE	"spawn_npc_melee"
	#define ZTOK_SPAWN_NPC_RANGE	"spawn_npc_range"
	#define ZTOK_SPAWN_NPC_BOSS		"spawn_npc_boss"
	#define ZTOK_SPAWN_NPC			"spawn_npc_"
	#define ZTOK_SPAWN_BARRICADE	"spawn_blitz_barricade_"
	#define ZTOK_SPAWN_GUARDIAN		"spawn_blitz_guardian"
	#define ZTOK_SPAWN_RADAR		"spawn_blitz_radar_"
	#define ZTOK_SPAWN_TRESURE		"spawn_blitz_honoritem_"

	#define ZTOK_WAIT_CAMERA_POS	"wait_pos"

	#define ZTOK_SMOKE_SS			"smk_ss_"
	#define ZTOK_SMOKE_TS			"smk_ts_"
	#define ZTOK_SMOKE_ST			"smk_st_"

	#define ZTOK_DUMMY_LINK			"link"
	#define ZTOK_DUMMY_ROUTE		"route_"

	#define ZTOK_SPAWN_GROUP "GROUP"
	//todo: determine the usage of this, maiet left no notes on it

Find <br>

	ZMapSpawnData* ZMapSpawnManager::GetSpawnData(ZMapSpawnType nSpawnType, int nIndex)
	{

Add Above <br>

	ZMapSpawnData* ZMapSpawnManager::GetCustomSpawnData(int nCustomSpawnIndex, int nIndex)
	{
		// nCustomSpawnIndex: Ä¿½ºÅÒ½ºÆù ÁöÁ¡µéÀ» ÀÌ¸§À¸·Î Á¤·ÄÇÑ ¸ñ·Ï¿¡¼­ÀÇ ÀÎµ¦½º
		// nIndex: ÇØ¼º Ä¿½ºÅÒ½ºÆù ¸íÀ» °¡Áø ÁöÁ¡µéÀÇ ¹è¿­ ÀÎµ¦½º

		if (nCustomSpawnIndex < 0 || nIndex < 0 ) { _ASSERT(0); return NULL; }

		if ((int)m_SpawnNpcCustom.size() <= nCustomSpawnIndex)
		{
			_ASSERT(0);
			return NULL;
		}

		ZMapSpawnNpcCustom::iterator it = m_SpawnNpcCustom.begin();
		for (int i=0; i<nCustomSpawnIndex; ++i)
			++it;

		ZMapSpawnList* pSpawnList = it->second;
		if ((int)pSpawnList->size() <= nIndex)
		{
			_ASSERT(0);
			return NULL;
		}

		return (*pSpawnList)[nIndex];
	}


Find <br>

	if( !Data.LoadFromMemory(buffer) )
	{
		delete buffer;
		return false;
	}

	delete buffer;
	mzf.Close();

Replace <br>

	if( !Data.LoadFromMemory(buffer) )
	{
		delete[] buffer;
		return false;
	}

	delete[] buffer;
	mzf.Close();

Find <br>

	else if (!strnicmp(pMapSpawnData->m_szSpawnName, ZTOK_SPAWN_NPC_BOSS, strlen(ZTOK_SPAWN_NPC_BOSS)))
	{
		pMapSpawnData->m_nType = ZMST_NPC_BOSS;
		m_SpawnArray[ZMST_NPC_BOSS].push_back(pMapSpawnData);
	}

Add <br>

	else if (!strnicmp(pMapSpawnData->m_szSpawnName, ZTOK_SPAWN_NPC_BOSS, strlen(ZTOK_SPAWN_NPC_BOSS)))
	{
		pMapSpawnData->m_nType = ZMST_NPC_BOSS;
		m_SpawnArray[ZMST_NPC_BOSS].push_back(pMapSpawnData);
	}
	else if (!strnicmp(pMapSpawnData->m_szSpawnName, ZTOK_SPAWN_NPC, strlen(ZTOK_SPAWN_NPC)))
	{
		// spawn_npc_xxxx Ã³·³ ½ºÆù³ëµå ÀÌ¸§À» ÀÓÀÇ·Î Á¤ÇÏ´Â °ÍµéÀ» ÀÌ¸§º°·Î ¸®½ºÆ®¿¡ ³Ö´Â´Ù
		pMapSpawnData->m_nType = ZMST_NPC_CUSTOM;
		ZMapSpawnNpcCustom::iterator it = m_SpawnNpcCustom.find(pMapSpawnData->m_szSpawnName);
		if (it==m_SpawnNpcCustom.end())
			m_SpawnNpcCustom[pMapSpawnData->m_szSpawnName] = new ZMapSpawnList;
		
		m_SpawnNpcCustom[pMapSpawnData->m_szSpawnName]->push_back(pMapSpawnData);
	}

	return true;

Open(ZMapDesc.h) <br>
Find <br>

	int GetTeamCount(int nTeamIndex);
	
Add <br>

	int GetCustomSpawnCount(const char* szSpawnName);

Find <br>

	ZMapSpawnData* GetSpawnData(ZMapSpawnType nSpawnType, int nIndex);

Add <br>

	ZMapSpawnData* GetCustomSpawnData(int nCustomSpawnIndex, int nIndex);
	rvector GetRoutePos(ZMapSpawnType nSpawnType, char* name);

Find <br>

	class ZMapSpawnList : public vector<ZMapSpawnData*> { };

Add <br>

	class ZMapSpawnNpcCustom : public map<string, ZMapSpawnList*> { };

Find <br>

	ZMapSpawnList	m_SpawnArray[ZMST_MAX];

Add <br>

	ZMapSpawnNpcCustom	m_SpawnNpcCustom;

Find <br>

	ZMST_NPC_MELEE,
	ZMST_NPC_RANGE,
	ZMST_NPC_BOSS,

Add <br>

	ZMST_ROUTE,
	ZMST_NPC_CUSTOM,


Open(MMatchServer_Stage.cpp) <br>
Find <br>

	void MMatchServer::SaveGamePlayerLog(MMatchObject* pObj, unsigned int nStageID)
	{	

Add <br>

	void MMatchServer::OnStartCQ(MMatchStage* m_pStage, int nRounds)
	{
		MMatchStageSetting* pSetting = m_pStage->GetStageSetting();
		pSetting->SetRoundMax(nRounds);
		MCommand* pCmd = CreateCmdResponseStageSetting(m_pStage->GetUID());
		RouteToStage(m_pStage->GetUID(), pCmd);
	}

Open(MMatchServer.h) <br>
Find <br>

	void OnQuestSendPing(const MUID& uidStage, unsigned long int t);

Add <br>

	void OnStartCQ(MMatchStage* m_pStage, int nRounds);

Open(ZGame.h) <br>
Find <br>

	#include "ZCharacterManager.h"
	#include "ZObjectManager.h"
	#include "ZWorld.h"

Add <br>

	#include "ZNavigationMesh.h"

Find <br>

	bool Pick(ZObject* pOwnerObject, rvector& origin, rvector& dir, ZPICKINFO* pickinfo, DWORD dwPassFlag = RM_FLAG_ADDITIVE | RM_FLAG_HIDE, bool bMyChar = false);
	bool PickTo(ZObject* pOwnerObject, rvector& origin, rvector& to, ZPICKINFO* pickinfo, DWORD dwPassFlag = RM_FLAG_ADDITIVE | RM_FLAG_HIDE, bool bMyChar = false);
	bool PickHistory(ZObject* pOwnerObject, float fTime, const rvector& origin, const rvector& to, ZPICKINFO* pickinfo, DWORD dwPassFlag, bool bMyChar = false);
	bool ObjectColTest(ZObject* pOwner, rvector& origin, rvector& to, float fRadius, ZObject** poutTarget);

Add <br>

	bool PickWorld(const rvector& pos, const rvector& dir, RBSPPICKINFO* pOut, DWORD dwPassFlag = RM_FLAG_ADDITIVE | RM_FLAG_USEOPACITY | RM_FLAG_HIDE);
	bool CheckWall(rvector& origin, rvector& targetpos, float fRadius, float fHeight = 0.f, RCOLLISIONMETHOD method = RCW_CYLINDER, int nDepth = 0, rplane* pimpactplane = NULL);
	// ¾î¶² ¿ÀºêÁ§Æ®°¡ diff¸¸Å­ ÀÌµ¿ÇÏ·Á ÇÒ¶§ ´Ù¸¥ Ä³¸¯ÅÍ¿ÍÀÇ Ãæµ¹À» °í·ÁÇØ diff¸¦ ¼öÁ¤ÇØÁÖ´Â ÇÔ¼ö
	void AdjustMoveDiff(ZObject* pObject, rvector& diff);

	ZNavigationMesh GetNavigationMesh();	// ´Ü¼ø Æ÷ÀÎÅÍ ·¡ÆÛÀÌ¹Ç·Î ±×³É return by value

Open(ZGame.cpp) <br>
Find <br>

	#include "ZRuleDuel.h"
	#include "ZRuleDeathMatch.h"
	#include "ZMyCharacter.h"
	#include "MMatchCRC32XORCache.h"
	#include "MMatchObjCache.h"

	#include "ZModule_HealOverTime.h"

Add <br>

	#include "ZNavigationMesh.h"

Find <br>

	void ZGame::CheckZoneTrap(MUID uidOwner,rvector pos,MMatchItemDesc* pItemDesc, MMatchTeam nTeamID)
	{

Add <br>

	ZNavigationMesh ZGame::GetNavigationMesh()
	{
		return ZNavigationMesh( GetWorld()->GetBsp()->GetNavigationMesh());
	}

Open(ZGlobal.h) <br>
Find <br>

	#define ZGetWorldManager()		ZApplication::GetInstance()->GetWorldManager()
	#define ZGetWorld()				(ZGetWorldManager()->GetCurrent())

Add <br>

	#define ZGetNavigationMesh() (ZApplication::GetGameInterface()->GetGame()->GetNavigationMesh())

Open(RVisualMesh.h) <br>
Find <br>

	public:
		const rmatrix&	GetWorldMat()			{ return m_WorldMat; }
		RMesh*			GetMesh()				{ return m_pMesh; }
		RMeshNode**		GetTMesh()				{return m_pTMesh;}
		void			SetMesh(RMesh* pMesh)	{ m_pMesh = pMesh; }

	private:

Add <br>

	RMesh*			m_pLowPolyMesh;

Find <br>

	// Light Setting

	void SetLight(int index,D3DLIGHT9* light,bool ShaderOnly) {	m_LightMgr.SetLight(index,light,ShaderOnly);}
	void UpdateLight() { m_LightMgr.UpdateLight(); }

	public:

	//	RQuery			m_RenderQuery;

Replace <br>

	// Light Setting

	RVisualLightMgr* GetLightMgr() { return &m_LightMgr; }
	void SetLight(int index,D3DLIGHT9* light,bool ShaderOnly) {	m_LightMgr.SetLight(index,light,ShaderOnly);}
	void UpdateLight() { m_LightMgr.UpdateLight(); }

	private:

	//	RQuery			m_RenderQuery;

Find <br>

	rvector			m_vPos;
	rvector			m_vDir;
	rvector			m_vUp;
	rmatrix			m_WorldMat;
	rmatrix			m_ScaleMat;
	RMeshNode**		m_pTMesh;
	RMesh*			m_pMesh;
	RMesh*			m_pLowPolyMesh;

Replace <br>

	private:
		rvector			m_vPos;
		rvector			m_vDir;
		rvector			m_vUp;
		rmatrix			m_WorldMat;
		rmatrix			m_ScaleMat;
		RMeshNode**		m_pTMesh;
		RMesh*			m_pMesh;
		RMesh*			m_pLowPolyMesh;

Find <br>

	rvector			m_vTargetPos;
	rvector			m_vRotXYZ;
	RFrameTime		m_FrameTime;

	rmatrix			m_RotMat;

Add <br>

	public:
		bool IsNpc()			{ return m_bIsNpc; }
		bool IsCharacter()		{ return m_bIsCharacter; }

		void SetDrawTracksMotion(int i, bool b) { m_bDrawTracksMotion[i] = b; }

		const rvector& GetScale()		{ return m_vScale; }
		const rvector& GetTargetPos()	{ return m_vTargetPos; }
		const rvector& GetPosition()	{return m_vPos; }

		const rvector& GetRotXYZ()		{ return m_vRotXYZ; }
		void SetRotXYZ(const rvector& v){ m_vRotXYZ = v; }
		void SetRotX(float x)			{ m_vRotXYZ.x = x; }
		void SetRotY(float y)			{ m_vRotXYZ.y = y; }
		void SetRotZ(float z)			{ m_vRotXYZ.z = z; }
		void SetPosition(const rvector& pos) { m_vPos = pos; }
		RFrameTime* GetFrameTime()		{ return &m_FrameTime; }

	public:

Find <br>

		bool			m_bCalcBoxWithScale;
		bool			m_bSkipRenderFaceParts;
	};

Replace <br>

	bool			m_bCalcBoxWithScale;
	bool			m_bSkipRenderFaceParts;

public:

		int GetId()				{ return m_id; }
		void SetId(int id)		{ m_id = id; }

		D3DCOLORVALUE GetNPCBlendColor() { return m_NPCBlendColor; }

		const D3DXVECTOR3& GetBoundMax() { return m_vBMax; }
		const D3DXVECTOR3& GetBoundMin() { return m_vBMin; }

		const D3DXMATRIX& GetWeaponDummyMatrix(WeaponDummyType type) { return m_WeaponDummyMatrix[type]; }
		RWeaponMotionType GetSelectWeaponMotionType() { return m_SelectWeaponMotionType; }

		rmatrix* GetBipMatrixArray()	{ return m_pBipMatrix; }
		const rmatrix& GetUpperRotMat()	{ return m_UpperRotMat; }

		ROcclusionList*	GetTOCCL()		{ return m_pTOCCL; }

		float GetUAniValue() { return m_fUAniValue; }
		float GetVAniValue() { return m_fVAniValue; }
		bool IsUVAni()		 { return m_bUVAni; }

		bool IsRenderMatrix() { return m_bRenderMatrix; }

		bool IsRender()				{ return m_bIsRender; }
		bool IsRenderWeapon()		{ return m_bIsRenderWeapon; }
		bool IsRenderFirst()		{ return m_bIsRenderFirst; }
		bool IsCheckViewFrustum()	{ return m_bCheckViewFrustum; }
		void SetGrenadeFire(bool b)	{ m_bGrenadeFire = b; }
		void SetAddGrenade(bool b)	{ m_bAddGrenade = b; }
		bool IsAddGrenade()			{ return m_bAddGrenade; }
		void SetGrenadeFireTime(DWORD time)		{ m_GrenadeFireTime = time; }

		void SetCalcBoxWithScale(bool b) { m_bCalcBoxWithScale = b; }
		bool IsCalcBoxWithScale() { return m_bCalcBoxWithScale; }

		void SetSkipRenderFaceParts(bool b) { m_bSkipRenderFaceParts = b; }

		//void ShiftFugitiveValues();
	};

	////////////////////////////////////////////////////////
	// ÀÏ¹Ý ÀÌÆåÆ®³ª ¸Ê¿ÀºêÁ§Æ® ¿ë°ú Ä³¸¯ÅÍ¿ëÀ» ±¸ºÐÇÏÀÚ..

	//class RCharacterVisualMesh : public RVisualMesh {
	//public:
	//	RCharacterVisualMesh() {
	//
	//	}
	//	~RCharacterVisualMesh() {
	//
	//	}
	//
	//public:
	//
	//};

	_NAMESPACE_REALSPACE2_END

	#endif//_RVisualMesh


Open(RVisualMeshMgr.cpp) <br>
Find <br>

	RVisualMeshMgr::RVisualMeshMgr() {

		m_id_last = 0;
		m_node_table.reserve(MAX_VMESH_TABLE);//±âº»

		for(int i=0;i<MAX_VMESH_TABLE;i++)
			m_node_table[i] = NULL;

	}

Replace <br>

	RVisualMeshMgr::RVisualMeshMgr() {

		m_id_last = 0;
		m_node_table.reserve(MAX_VMESH_TABLE);//±âº»

		if (m_node_table.size() > 0)
		{
			for (int i = 0; i < MAX_VMESH_TABLE; i++)
				m_node_table[i] = NULL;
		}
	}

Find <br>

	node->m_id = m_id_last;


Replace <br>

	node->SetId(m_id_last);


Find <br>

	node->m_id = m_id_last;

Replace <br>

	node->SetId(m_id_last);

Find <br>

	if((*node)->m_id == id) {

Replace <br>

	if((*node)->GetId() == id) {

Find <br>

	if((*node)->m_id == id) {

Replace <br>

	if((*node)->GetId() == id) {

Open(RBspObject.cpp) <br>
Find <br>

		rboundingbox bb;
		bb.vmax=pInfo->pVisualMesh->m_vBMax;
		bb.vmin=pInfo->pVisualMesh->m_vBMin;

Replace <br>

		rboundingbox bb;
		bb.vmax=pInfo->pVisualMesh->GetBoundMax();
		bb.vmin=pInfo->pVisualMesh->GetBoundMin();

Find <br>

		if( !m_bNotOcclusion ) {
			if(!IsVisible(bb)) {
				m_DebugInfo.nMapObjectOcclusionCulled++;
				continue;
			}
		}else {
			pInfo->pVisualMesh->m_bCheckViewFrustum = false;
		}

Replace <br>

		if( !m_bNotOcclusion ) {
			if(!IsVisible(bb)) {
				m_DebugInfo.nMapObjectOcclusionCulled++;
				continue;
			}
		}else {
			pInfo->pVisualMesh->SetCheckViewFrustum(false);
		}

Find <br>

	rvector center = (pInfo->pVisualMesh->m_vBMax+pInfo->pVisualMesh->m_vBMin)*.5f;

Replace <br>

	rvector center = (pInfo->pVisualMesh->GetBoundMax()+pInfo->pVisualMesh->GetBoundMin())*.5f;

Find <br>

		if(pInfo->pVisualMesh && pInfo->pVisualMesh->m_pMesh)
			bLight = !pInfo->pVisualMesh->m_pMesh->m_LitVertexModel;

Replace <br>

		if(pInfo->pVisualMesh && pInfo->pVisualMesh->GetMesh())
			bLight = !pInfo->pVisualMesh->GetMesh()->m_LitVertexModel;

Find <br>

	if(!pInfo->pVisualMesh->m_bIsRender) m_DebugInfo.nMapObjectFrustumCulled++;

Replace <br>

	if(!pInfo->pVisualMesh->IsRender()) m_DebugInfo.nMapObjectFrustumCulled++;

Find <br>

		if(pInfo) {
			t_vec = rvector(pInfo->pVisualMesh->m_WorldMat._41,
							pInfo->pVisualMesh->m_WorldMat._42,
							pInfo->pVisualMesh->m_WorldMat._43 );
			t_vec = camera_pos - t_vec;
			pInfo->fDist = Magnitude(t_vec);
		}
	}

Replace <br>

		if (pInfo) {
			t_vec = rvector(pInfo->pVisualMesh->GetWorldMat()._41,
				pInfo->pVisualMesh->GetWorldMat()._42,
				pInfo->pVisualMesh->GetWorldMat()._43);
			t_vec = camera_pos - t_vec;
			pInfo->fDist = Magnitude(t_vec);
		}
	}

Open(RMesh_Frame.cpp) <br>
Find <br>

	rvector vTargetPos = pVMesh->m_vTargetPos;
	rmatrix world = pVMesh->m_WorldMat;

Replace <br>

	rvector vTargetPos = pVMesh->GetTargetPos();
	rmatrix world = pVMesh->GetWorldMat();

Find <br>

			mat->_11 = pVisualMesh->m_UpperRotMat._11;
			mat->_12 = pVisualMesh->m_UpperRotMat._12;
			mat->_13 = pVisualMesh->m_UpperRotMat._13;

			mat->_21 = pVisualMesh->m_UpperRotMat._21;
			mat->_22 = pVisualMesh->m_UpperRotMat._22;
			mat->_23 = pVisualMesh->m_UpperRotMat._23;

			mat->_31 = pVisualMesh->m_UpperRotMat._31;
			mat->_32 = pVisualMesh->m_UpperRotMat._32;
			mat->_33 = pVisualMesh->m_UpperRotMat._33;


Replace <br>

			mat->_11 = pVisualMesh->GetUpperRotMat()._11;
			mat->_12 = pVisualMesh->GetUpperRotMat()._12;
			mat->_13 = pVisualMesh->GetUpperRotMat()._13;

			mat->_21 = pVisualMesh->GetUpperRotMat()._21;
			mat->_22 = pVisualMesh->GetUpperRotMat()._22;
			mat->_23 = pVisualMesh->GetUpperRotMat()._23;

			mat->_31 = pVisualMesh->GetUpperRotMat()._31;
			mat->_32 = pVisualMesh->GetUpperRotMat()._32;
			mat->_33 = pVisualMesh->GetUpperRotMat()._33;

Find <br>

		float add_value = pVisualMesh->m_FrameTime.GetValue();
		float add_value_npc = 0.f;

		float rot_x = pVisualMesh->m_vRotXYZ.x;
		float rot_y = pVisualMesh->m_vRotXYZ.y;		// + add_value;

Replace <br>

		float add_value = pVisualMesh->GetFrameTime()->GetValue();
		float add_value_npc = 0.f;

		float rot_x = pVisualMesh->GetRotXYZ().x;
		float rot_y = pVisualMesh->GetRotXYZ().y;		// + add_value;


Open(ZCharacter.cpp) <br>
Find <br>

	if (IsDie()) { //Çã¸® º¯Çü ¾ø´Ù~

		m_pVMesh->m_vRotXYZ.x = 0.f;
		m_pVMesh->m_vRotXYZ.y = 0.f;
		m_pVMesh->m_vRotXYZ.z = 0.f;
		
		return;
	}

Replace <br>

	if (IsDie()) { //Çã¸® º¯Çü ¾ø´Ù~

		m_pVMesh->SetRotXYZ(rvector(0, 0, 0));

		return;
	}

Find <br>

	m_pVMesh->m_vRotXYZ.x = -fAngle*180/pi *.9f;

Replace <br>

	m_pVMesh->SetRotX(-fAngle*180/pi *.9f);

Find <br>

	m_pVMesh->m_vRotXYZ.y = (m_TargetDir.z+0.05f) * 50.f;

Replace <br>

	m_pVMesh->SetRotY((m_TargetDir.z+0.05f) * 50.f);

Find <br>

		m_pVMesh->m_vRotXYZ.x = 0.f;
		m_pVMesh->m_vRotXYZ.y = 0.f;
		m_pVMesh->m_vRotXYZ.z = 0.f;

Replace <br>

		m_pVMesh->SetRotXYZ(rvector(0,0,0));

Find <br>

	m_bRendered = m_pVMesh->m_bIsRender;	// ½ÇÁ¦ ·»´õ¸µ µÇ¾ú´Â°¡

	if(m_pVMesh->m_bIsRenderWeapon && (m_pVMesh->GetVisibility() > 0.05f))
	{
		DrawEnchant(m_AniState_Lower.Ref(), m_bCharged->Ref());	//mmemory proxy
	}
	
Replace <br>

	m_bRendered = m_pVMesh->IsRender();	// ½ÇÁ¦ ·»´õ¸µ µÇ¾ú´Â°¡

	if(m_pVMesh->IsRenderWeapon() && (m_pVMesh->GetVisibility() > 0.05f))
	{
		DrawEnchant(m_AniState_Lower.Ref(), m_bCharged->Ref());	//mmemory proxy
	}

Open(RVisualMesh.h) <br>
Find <br>

	void	SetRotXYZ(rvector v);

Replace <br>

	//void	SetRotXYZ(rvector v);

Open(ZEffectMaanger.cpp) <br>
Find <br>

	if (pObj->GetUID() == ZGetMyUID())
		((ZEffectDash*)pNew)->GetVMesh()->m_bCheckViewFrustum = false;

Replace <br>

	if (pObj->GetUID() == ZGetMyUID())
		((ZEffectDash*)pNew)->GetVMesh()->SetCheckViewFrustum(false);

Find <br>

	if (pObj->GetUID() == ZGetMyUID())
		((ZEffectDash*)pNew)->GetVMesh()->m_bCheckViewFrustum = false;

Replace <br>

	if (pObj->GetUID() == ZGetMyUID())
		((ZEffectDash*)pNew)->GetVMesh()->SetCheckViewFrustum(false);

Find <br>

	if (pObj->GetUID() == ZGetMyUID())
		((ZEffectDash*)pNew)->GetVMesh()->m_bCheckViewFrustum = false;

Replace <br>

	if (pObj->GetUID() == ZGetMyUID())
		((ZEffectDash*)pNew)->GetVMesh()->SetCheckViewFrustum(false);

Find <br>

	if (pObj->GetUID() == ZGetMyUID())
		((ZEffectDash*)pNew)->GetVMesh()->m_bCheckViewFrustum = false;

Replace <br>

	if (pObj->GetUID() == ZGetMyUID())
		((ZEffectDash*)pNew)->GetVMesh()->SetCheckViewFrustum(false);

Open(ZEffectAniMesh.cpp) <br>
Find <br>

	m_VMesh.m_bCalcBoxWithScale = true;

Replace <br>

	m_VMesh.SetCalcBoxWithScale(true);

Open(ZCharacter.cpp) <br>
Find <br>

	if(m_pVMesh->m_bAddGrenade)


Replace <br>

	if(m_pVMesh->IsAddGrenade()) {

Find <br>

	m_pVMesh->m_bAddGrenade = false;

Replace <br>

	m_pVMesh->SetAddGrenade(false);

Open(ZEffectAniMesh.cpp) <br>
Find <br>

	if(m_bRender){
		m_VMesh.Render();
		m_bisRendered = m_VMesh.m_bIsRender;
	} 

Replace <br>

	if(m_bRender){
		m_VMesh.Render();
		m_bisRendered = m_VMesh.IsRender();
	} 

Find <br>

			if(pVMesh)
				if(!pVMesh->m_bIsRender) return false;

Replace <br>

			if(pVMesh)
				if(!pVMesh->IsRender()) return false;


Open(ZEffectBillboardList.cpp) <br>
Find <br>

			pChar = (ZCharacter*)ZGetCharacterManager()->Find(p->CharUID);

			if( pChar ) {
				if( pChar->m_pVMesh ) {
					if( pChar->m_pVMesh->m_bIsRender==false) {//ºÎ¸ð°¡ ¾È±×·ÁÁ³À¸¸é skip...
						itr++;
						continue;
					}
				}
			}

Replace <br>

			pChar = (ZCharacter*) ZGetCharacterManager()->Find(p->CharUID);

			if( pChar ) {
				if( pChar->m_pVMesh ) {
					if( pChar->m_pVMesh->IsRender()==false) {//ºÎ¸ð°¡ ¾È±×·ÁÁ³À¸¸é skip...
						itr++;
						continue;
					}
				}
			}


Open(ZEffectManager.cpp) <br>
Find <br>

	void ZEffectManager::AddCharacterIcon(ZObject* pObj,int nIcon)
	{
		if(!pObj->GetInitialized()) return;
		if(!pObj->GetVisualMesh()->m_bIsRender) return;

		ZEffect* pNew = NULL;
		pNew = new ZEffectIcon(m_pCharacterIcons[nIcon],pObj);
		((ZEffectIcon*)pNew)->SetAlignType(2);
		Add(pNew);
	}

Replace <br>

	void ZEffectManager::AddCharacterIcon(ZObject* pObj,int nIcon)
	{
		if(!pObj->GetInitialized()) return;
		if(!pObj->GetVisualMesh()->IsRender()) return;

		ZEffect* pNew = NULL;
		pNew = new ZEffectIcon(m_pCharacterIcons[nIcon],pObj);
		((ZEffectIcon*)pNew)->SetAlignType(2);
		Add(pNew);
	}

Open(ZEffectStaticMesh.cpp) <br>
Find <br>

	if(m_bRender) {
		m_VMesh.Render();
		m_bisRendered = m_VMesh.m_bIsRender;
	} 

Replace <br>

	if(m_bRender) {
		m_VMesh.Render();
		m_bisRendered = m_VMesh.IsRender();
	} 

Open(ZCharacter.cpp) <br>
Find <br>

	if( pItemID[MMCIP_AVATAR] != 0 ) {
		ChangeEquipAvatarParts(pVMesh, pItemID, nSex, nHair);
		
		// ¾Æ¹ÙÅ¸ Âø¿ë½Ã face¸Þ½¬´Â ¼û±ä´Ù
		pVMesh->m_bSkipRenderFaceParts = true;
	} 
	else {
		ChangeEquipParts(pVMesh, pItemID);		// hair, faceº¸´Ù Àåºñ¸¦ ¸ÕÀú ¹Ù²ã¾ß ÇÑ´Ù.

		// Áö±ÝÀº ¸Ó¸®¾ÆÀÌÅÛ°ú ¸Ó¸®Ä«¶ô ¸Þ½¬¸¦ ¼­·Î °øÀ¯ÇÏ°í ÀÖ´Ù. - ³ªÁß¿¡ ¶¼¾î³õµµ·Ï ÇÏÀÚ
		if (pItemID[MMCIP_HEAD] == 0) {
			ChangeCharHair(pVMesh, nSex, nHair);
		}

		pVMesh->m_bSkipRenderFaceParts = false;

		ChangeCharFace(pVMesh, nSex, nFace);
	}

Replace <br>

	if( pItemID[MMCIP_AVATAR] != 0 ) {
		ChangeEquipAvatarParts(pVMesh, pItemID, nSex, nHair);
		
		// ¾Æ¹ÙÅ¸ Âø¿ë½Ã face¸Þ½¬´Â ¼û±ä´Ù
		pVMesh->SetSkipRenderFaceParts(true);
	} 
	else
	{
		ChangeEquipParts(pVMesh, pItemID);		// hair, faceº¸´Ù Àåºñ¸¦ ¸ÕÀú ¹Ù²ã¾ß ÇÑ´Ù.

		// Áö±ÝÀº ¸Ó¸®¾ÆÀÌÅÛ°ú ¸Ó¸®Ä«¶ô ¸Þ½¬¸¦ ¼­·Î °øÀ¯ÇÏ°í ÀÖ´Ù. - ³ªÁß¿¡ ¶¼¾î³õµµ·Ï ÇÏÀÚ
		if (pItemID[MMCIP_HEAD] == 0) {
			ChangeCharHair(pVMesh, nSex, nHair);
		}

		pVMesh->SetSkipRenderFaceParts(false);

		ChangeCharFace(pVMesh, nSex, nFace);
	}


Find <br>

	if( ( m_pVMesh->m_SelectWeaponMotionType == eq_wd_katana ) || 
		( m_pVMesh->m_SelectWeaponMotionType == eq_wd_sword  ) || 
		( m_pVMesh->m_SelectWeaponMotionType == eq_wd_blade  ) ) 
	{

Replace <br>

	if( ( m_pVMesh->GetSelectWeaponMotionType() == eq_wd_katana ) || 
		( m_pVMesh->GetSelectWeaponMotionType() == eq_wd_sword  ) || 
		( m_pVMesh->GetSelectWeaponMotionType() == eq_wd_blade  ) ) 
	{


Find <br>

	if(m_pVMesh->m_SelectWeaponMotionType == eq_wd_blade) 
	{
			 if( m_AniState_Lower.Ref() == ZC_STATE_LOWER_ATTACK1 ) GetDTM(bDTM,0,bMan);
		else if( m_AniState_Lower.Ref() == ZC_STATE_LOWER_ATTACK2 ) GetDTM(bDTM,1,bMan);
		else if( m_AniState_Lower.Ref() == ZC_STATE_LOWER_ATTACK3 ) GetDTM(bDTM,2,bMan);
		else if( m_AniState_Lower.Ref() == ZC_STATE_LOWER_ATTACK4 ) GetDTM(bDTM,3,bMan);
	}

	m_pVMesh->m_bDrawTracksMotion[0] = bDTM[0];
	m_pVMesh->m_bDrawTracksMotion[1] = bDTM[1];

Replace <br>

	if(m_pVMesh->GetSelectWeaponMotionType() == eq_wd_blade) 
	{
			 if( m_AniState_Lower.Ref() == ZC_STATE_LOWER_ATTACK1 ) GetDTM(bDTM,0,bMan);
		else if( m_AniState_Lower.Ref() == ZC_STATE_LOWER_ATTACK2 ) GetDTM(bDTM,1,bMan);
		else if( m_AniState_Lower.Ref() == ZC_STATE_LOWER_ATTACK3 ) GetDTM(bDTM,2,bMan);
		else if( m_AniState_Lower.Ref() == ZC_STATE_LOWER_ATTACK4 ) GetDTM(bDTM,3,bMan);
	}

	m_pVMesh->SetDrawTracksMotion(0, bDTM[0]);
	m_pVMesh->SetDrawTracksMotion(1, bDTM[1]);


Find <br>

			if( pWVMesh ) {
				if(pWVMesh->m_pMesh) {
					if(strncmp( pWVMesh->m_pMesh->GetName(), "flashbang", 9) == 0) {
						type = ZC_WEAPON_SP_FLASHBANG;
					}
					else if(strncmp( pWVMesh->m_pMesh->GetName(), "smoke", 5) == 0) {
						type = ZC_WEAPON_SP_SMOKE;
					}
					else if(strncmp( pWVMesh->m_pMesh->GetName(), "tear_gas", 8) == 0) {
						type = ZC_WEAPON_SP_TEAR_GAS;	
					} 
					else if(strncmp( pWVMesh->m_pMesh->GetName(), "trap", 4) == 0) {
						type = ZC_WEAPON_SP_TRAP;
					}
					else if(strncmp( pWVMesh->m_pMesh->GetName(), "dynamite", 8) == 0) {
						type = ZC_WEAPON_SP_DYNAMITE;
					}
				}
			}

Replace <br>

			if( pWVMesh ) {
				if(pWVMesh->GetMesh()) {
					if(strncmp( pWVMesh->GetMesh()->GetName(), "flashbang", 9) == 0) {
						type = ZC_WEAPON_SP_FLASHBANG;
					}
					else if(strncmp( pWVMesh->GetMesh()->GetName(), "smoke", 5) == 0) {
						type = ZC_WEAPON_SP_SMOKE;
					}
					else if(strncmp( pWVMesh->GetMesh()->GetName(), "tear_gas", 8) == 0) {
						type = ZC_WEAPON_SP_TEAR_GAS;	
					} 
					else if(strncmp( pWVMesh->GetMesh()->GetName(), "trap", 4) == 0) {
						type = ZC_WEAPON_SP_TRAP;
					}
					else if(strncmp( pWVMesh->GetMesh()->GetName(), "dynamite", 8) == 0) {
						type = ZC_WEAPON_SP_DYNAMITE;
					}
					else if (strncmp(pWVMesh->GetMesh()->GetName(), "spy_stungrenade", 15) == 0) {
						type = ZC_WEAPON_SPY_STUNGRENADE;
					}
				}
			}


Find <br>

	bool ZCharacter::IsMan() 
	{
		if(m_pVMesh) {
			if(m_pVMesh->m_pMesh) {
				if(strcmp(m_pVMesh->m_pMesh->GetName(),"heroman1")==0) {
					return true;
				}
			}
		}
		return false;
	}


Replace <br>


	bool ZCharacter::IsMan() 
	{
		if(m_pVMesh) {
			if(m_pVMesh->GetMesh()) {
				if(strcmp(m_pVMesh->GetMesh()->GetName(),"heroman1")==0) {
					return true;
				}
			}
		}
		return false;
	}


Find <br>

	m_pVMesh->m_vRotXYZ = vRot;

Replace <br>

	m_pVMesh->SetRotXYZ(vRot);

Find <br>

			if(m_pVMesh) {

				AniFrameInfo* pAniLow = m_pVMesh->GetFrameInfo(ani_mode_lower);
				AniFrameInfo* pAniUp = m_pVMesh->GetFrameInfo(ani_mode_upper);
				//m_pVMesh->m_pMesh->SetAnimation( m_pVMesh->m_pAniSet[0],m_pVMesh->m_pAniSet[1] );
				//m_pVMesh->m_pMesh->SetFrame(m_pVMesh->m_nFrame[0],m_pVMesh->m_nFrame[1]);
				m_pVMesh->m_pMesh->SetAnimation( pAniLow->m_pAniSet,pAniUp->m_pAniSet );
				m_pVMesh->m_pMesh->SetFrame( pAniLow->m_nFrame , pAniUp->m_nFrame);
				m_pVMesh->m_pMesh->SetMeshVis(m_pVMesh->m_fVis);
				m_pVMesh->m_pMesh->SetVisualMesh(m_pVMesh);

				m_pVMesh->m_pMesh->RenderFrame();

				RMeshNode* pNode = NULL;

				pNode = m_pVMesh->m_pMesh->FindNode(eq_parts_pos_info_Head);

				if(pNode) { 

					headpos.x = pNode->m_mat_result._41;
					headpos.y = pNode->m_mat_result._42;
					headpos.z = pNode->m_mat_result._43;
				}
			}

Replace <br>

			if(m_pVMesh) {

				AniFrameInfo* pAniLow = m_pVMesh->GetFrameInfo(ani_mode_lower);
				AniFrameInfo* pAniUp = m_pVMesh->GetFrameInfo(ani_mode_upper);
				//m_pVMesh->GetMesh()->SetAnimation( m_pVMesh->m_pAniSet[0],m_pVMesh->m_pAniSet[1] );
				//m_pVMesh->GetMesh()->SetFrame(m_pVMesh->m_nFrame[0],m_pVMesh->m_nFrame[1]);
				m_pVMesh->GetMesh()->SetAnimation( pAniLow->m_pAniSet,pAniUp->m_pAniSet );
				m_pVMesh->GetMesh()->SetFrame( pAniLow->m_nFrame , pAniUp->m_nFrame);
				m_pVMesh->GetMesh()->SetMeshVis(m_pVMesh->GetVisibility());
				m_pVMesh->SetVisualMeshToMesh();

				m_pVMesh->GetMesh()->RenderFrame();

				RMeshNode* pNode = NULL;

				pNode = m_pVMesh->GetMesh()->FindNode(eq_parts_pos_info_Head);

				if(pNode) { 

					headpos.x = pNode->m_mat_result._41;
					headpos.y = pNode->m_mat_result._42;
					headpos.z = pNode->m_mat_result._43;
				}
			}

Find <br>

	rvector _dir=rvector(0,0,1);

	if(pChar) {
		if(pChar->m_pVMesh) {
			rmatrix* mat = &pChar->m_pVMesh->m_WeaponDummyMatrix[weapon_dummy_muzzle_flash];

			_dir.x = mat->_21;
			_dir.y = mat->_22;
			_dir.z = mat->_23;
		}
	}
	
Replace <br>

	rvector _dir=rvector(0,0,1);

	if(pChar) {
		if(pChar->m_pVMesh) {
			const rmatrix* mat = &pChar->m_pVMesh->GetWeaponDummyMatrix(weapon_dummy_muzzle_flash);

			_dir.x = mat->_21;
			_dir.y = mat->_22;
			_dir.z = mat->_23;
		}
	}

Open(ZEffectManager.cpp) <br>
Find <br>

		rvector _dir=rvector(0,0,1);

		if(pObj) {
			if(pObj->m_pVMesh) {
				rmatrix* mat = &pObj->m_pVMesh->m_WeaponDummyMatrix[weapon_dummy_muzzle_flash];
				
				_dir.x = mat->_21;
				_dir.y = mat->_22;
				_dir.z = mat->_23;
			}
		}

Replace <br>

		rvector _dir=rvector(0,0,1);

		if(pObj) {
			if(pObj->m_pVMesh) {
				const rmatrix* mat = &pObj->m_pVMesh->GetWeaponDummyMatrix(weapon_dummy_muzzle_flash);
				
				_dir.x = mat->_21;
				_dir.y = mat->_22;
				_dir.z = mat->_23;
			}
		}

Open(ZMyCharacter.cpp) <br>
Find <br>

	if(m_pVMesh->IsSelectWeaponGrenade()) {	//¸ð¼Ç¸¸ ½ÃÀÛµÈ´Ù..
		// ¼ö·ùÅº ´øÁö´Â Æ¯Á¤ ÇÁ·¹ÀÓ¿¡¼­ ¹ß»ç..
		m_pVMesh->m_bGrenadeFire = true;
		m_pVMesh->m_GrenadeFireTime = timeGetTime();
	}

Replace <br>

	if(m_pVMesh->IsSelectWeaponGrenade()) {	//¸ð¼Ç¸¸ ½ÃÀÛµÈ´Ù..
		// ¼ö·ùÅº ´øÁö´Â Æ¯Á¤ ÇÁ·¹ÀÓ¿¡¼­ ¹ß»ç..
		m_pVMesh->SetGrenadeFire(true);
		m_pVMesh->SetGrenadeFireTime(timeGetTime());
	}

Find <br>

	// ´Ü°Ë
	if( //m_pVMesh->m_SelectWeaponMotionType==eq_wd_dagger ||
		m_pVMesh->m_SelectWeaponMotionType==eq_ws_dagger ) 
	{ // dagger
		if(m_AniState_Upper.Ref()==ZC_STATE_UPPER_SHOT)
			return;

Replace <br>

	// ´Ü°Ë
	if( m_pVMesh->GetSelectWeaponMotionType()==eq_wd_dagger ||
		m_pVMesh->GetSelectWeaponMotionType()==eq_ws_dagger ) 
	{ // dagger
		if(m_AniState_Upper.Ref()==ZC_STATE_UPPER_SHOT)
			return;

Find <br>

	if(GetItems()->GetSelectedWeapon()->GetBulletCurrMagazine() <= 0 ) {
		if( m_pVMesh->m_SelectWeaponMotionType != eq_wd_grenade && 
			m_pVMesh->m_SelectWeaponMotionType != eq_wd_item && 
			m_pVMesh->m_SelectWeaponMotionType != eq_wd_katana && 
			m_pVMesh->m_SelectWeaponMotionType != eq_ws_dagger && 
			m_pVMesh->m_SelectWeaponMotionType != eq_wd_dagger && 
			m_pVMesh->m_SelectWeaponMotionType != eq_wd_sword &&
			m_pVMesh->m_SelectWeaponMotionType != eq_wd_blade )	{
			if( GetItems()->GetSelectedWeapon()->GetBulletSpare() <= 0 ) {
				ZGetSoundEngine()->PlaySEDryFire( GetItems()->GetSelectedWeapon()->GetDesc(), 0, 0, 0, true );
			} else {
				m_dwStatusBitPackingValue.Ref().m_bSpMotion = false;// Æ¯¼ö¸ð¼ÇÀº Ãë¼Ò.. 
				ZPostReload();	
			}
		}
	}

Replace <br>

	if(GetItems()->GetSelectedWeapon()->GetBulletCurrMagazine() <= 0 ) {
		if( m_pVMesh->GetSelectWeaponMotionType() != eq_wd_grenade && 
			m_pVMesh->GetSelectWeaponMotionType() != eq_wd_item && 
			m_pVMesh->GetSelectWeaponMotionType() != eq_wd_katana && 
			m_pVMesh->GetSelectWeaponMotionType() != eq_ws_dagger && 
			m_pVMesh->GetSelectWeaponMotionType() != eq_wd_dagger && 
			m_pVMesh->GetSelectWeaponMotionType() != eq_wd_sword &&
			m_pVMesh->GetSelectWeaponMotionType() != eq_wd_blade &&
			m_pVMesh->GetSelectWeaponMotionType() != eq_wd_spycase )	{
			if( GetItems()->GetSelectedWeapon()->GetBulletSpare() <= 0 ) {
				ZGetSoundEngine()->PlaySEDryFire( GetItems()->GetSelectedWeapon()->GetDesc(), 0, 0, 0, true );
			} else {
				m_dwStatusBitPackingValue.Ref().m_bSpMotion = false;// Æ¯¼ö¸ð¼ÇÀº Ãë¼Ò.. 
				ZPostReload();	
			}
		}
	}

Find <br>

			switch( m_pVMesh->m_SelectWeaponMotionType ) {
				case eq_wd_item :		if (uStatus.m_bLand) OnShotItem(); break; //OnShotItem(uStatus.m_bLand); break;
				case eq_wd_grenade :	OnShotCustom();	break;		
				case eq_wd_rlauncher :	OnShotRocket();	break;
				case eq_wd_katana :
				case eq_ws_dagger :
				case eq_wd_dagger :
				case eq_wd_sword :
				case eq_wd_blade :		OnShotMelee();	break;
				default:				OnShotRange();	break;
			}
		}

		UpdateStylishShoted();
	}

Replace <br>

		switch( m_pVMesh->GetSelectWeaponMotionType() ) {
			case eq_wd_item :		if (uStatus.m_bLand) OnShotItem(); break; //OnShotItem(uStatus.m_bLand); break;
			case eq_wd_grenade :	OnShotCustom();	break;		
			case eq_wd_rlauncher :	OnShotRocket();	break;
			case eq_wd_katana :
			case eq_ws_dagger :
			case eq_wd_dagger :
			case eq_wd_sword :
			case eq_wd_blade :
			case eq_wd_spycase:		OnShotMelee();	break;
			default:				OnShotRange();	break;
		}

		UpdateStylishShoted();
	}


Open(ZGame.cpp) <br>
Find <br>

				if(pChar!=m_pMyCharacter &&
					( pChar->m_pVMesh->m_SelectWeaponMotionType==eq_wd_dagger ||
					pChar->m_pVMesh->m_SelectWeaponMotionType==eq_ws_dagger )) { // dagger
						pChar->SetAnimationUpper(ZC_STATE_UPPER_SHOT);
					}

Replace <br>

				if(pChar!=m_pMyCharacter &&
					( pChar->m_pVMesh->GetSelectWeaponMotionType()==eq_wd_dagger ||
					pChar->m_pVMesh->GetSelectWeaponMotionType()==eq_ws_dagger )) { // dagger
						pChar->SetAnimationUpper(ZC_STATE_UPPER_SHOT);
					}

Find <br>

				if(pChar!=m_pMyCharacter &&
					( pChar->m_pVMesh->m_SelectWeaponMotionType==eq_wd_dagger ||
					pChar->m_pVMesh->m_SelectWeaponMotionType==eq_ws_dagger )) { // dagger
						pChar->SetAnimationUpper(ZC_STATE_UPPER_SHOT);
					}

Replace <br>

				if(pChar!=m_pMyCharacter &&
					( pChar->m_pVMesh->GetSelectWeaponMotionType()==eq_wd_dagger ||
					pChar->m_pVMesh->GetSelectWeaponMotionType()==eq_ws_dagger )) { // dagger
						pChar->SetAnimationUpper(ZC_STATE_UPPER_SHOT);
					}

Open(ZMeshView.cpp) <br>
Find <br>

	RVisualMesh* RTVisualMesh::GetVMesh(bool b)
	{
		if(m_pVisualMesh->m_pMesh==NULL) {
			if( bInit == false ) {
				if(b) {
					mlog("RTVisualMesh::GetVMesh() ÃÊ±âÈ­ µÇÁö ¾ÊÀº »óÅÂ¿¡¼­ »ç¿ëÇÏ·Á ÇÑ´Ù.ÁÖÀÇ.\n");
				}
			}
		}
		return m_pVisualMesh;
	}


Replace <br>

	ZObjectVMesh* RTVisualMesh::GetVMesh(bool b)
	{
		if(m_pVisualMesh->GetMesh()==NULL) {
			if( bInit == false ) {
				if(b) {
					mlog("RTVisualMesh::GetVMesh() ÃÊ±âÈ­ µÇÁö ¾ÊÀº »óÅÂ¿¡¼­ »ç¿ëÇÏ·Á ÇÑ´Ù.ÁÖÀÇ.\n");
				}
			}
		}
		return m_pVisualMesh;
	}

Open(ZMyCharacter.cpp) <br>
Find <br>

	void ZMyCharacter::OnGadget_Hanging()
	{
		switch(m_pVMesh->m_SelectWeaponMotionType)
		{	

Replace <br>

	void ZMyCharacter::OnGadget_Hanging()
	{
		switch(m_pVMesh->GetSelectWeaponMotionType())
		{	


Find <br>

					if(m_nShot.Ref()==3) // sword ´Â ´Ù¸¥ Ä®µé°ú ´Þ¸®..3Å¸±îÁö¸¸ÀÌ°í 3Å¸ ¸®ÅÏÀÌ ¾ø´Ù..
						if( m_pVMesh->m_SelectWeaponMotionType == eq_wd_sword ) {
							m_nShot.Set_CheckCrc(0);
							zStatus.m_bShot=false;
							zStatus.m_bShotReturn = false;
						}

Replace <br>

					if(m_nShot.Ref()==3) // sword ´Â ´Ù¸¥ Ä®µé°ú ´Þ¸®..3Å¸±îÁö¸¸ÀÌ°í 3Å¸ ¸®ÅÏÀÌ ¾ø´Ù..
						if( m_pVMesh->GetSelectWeaponMotionType() == eq_wd_sword ) {
							m_nShot.Set_CheckCrc(0);
							zStatus.m_bShot=false;
							zStatus.m_bShotReturn = false;
						}


Find <br>

					if(m_nShot.Ref()==3) // sword ´Â ´Ù¸¥ Ä®µé°ú ´Þ¸®..3Å¸±îÁö¸¸ÀÌ°í 3Å¸ ¸®ÅÏÀÌ ¾ø´Ù..
						if( m_pVMesh->m_SelectWeaponMotionType == eq_wd_sword ) {
							m_nShot.Set_CheckCrc(0);
							zStatus.m_bShot=false;
							zStatus.m_bShotReturn = false;
						}

Replace <br>

					if(m_nShot.Ref()==3) // sword ´Â ´Ù¸¥ Ä®µé°ú ´Þ¸®..3Å¸±îÁö¸¸ÀÌ°í 3Å¸ ¸®ÅÏÀÌ ¾ø´Ù..
						if( m_pVMesh->GetSelectWeaponMotionType() == eq_wd_sword ) {
							m_nShot.Set_CheckCrc(0);
							zStatus.m_bShot=false;
							zStatus.m_bShotReturn = false;
						}


Find <br>

	void ZObject::Tremble(float fValue, DWORD nMaxTime, DWORD nReturnMaxTime)
	{
		if(m_pVMesh)
		{
			RFrameTime* ft = &m_pVMesh->m_FrameTime;
			if(ft && !ft->m_bActive)
				ft->Start(fValue,nMaxTime,nReturnMaxTime);// °­µµ , ÃÖ´ë½Ã°£ , º¹±Í½Ã°£...
		}

	}

Replace <br>

	void ZObject::Tremble(float fValue, DWORD nMaxTime, DWORD nReturnMaxTime)
	{
		if(m_pVMesh)
		{
			RFrameTime* ft = m_pVMesh->GetFrameTime();
			if(ft && !ft->m_bActive)
				ft->Start(fValue,nMaxTime,nReturnMaxTime);// °­µµ , ÃÖ´ë½Ã°£ , º¹±Í½Ã°£...
		}

	}

Open(RVisualMesh.cpp) <br>
Find <br>

	void RVisualMesh::SetParts(RMeshPartsType parts,char* name)
	{
		if(parts < 0 && parts >= eq_parts_end ) 
			return;

		if(m_pTMesh==NULL) return;

		if(!m_pMesh) return;

		RMeshNode* pNode = m_pMesh->GetPartsNode(name);

		if(pNode) 
		{
	//		if(m_pTMesh[parts] != pNode) 
			{
				m_pTMesh[parts] = pNode;
				m_pMesh->ConnectPhysiqueParent(pNode);
			}
		}
	}

Replace <br>

	//Dynamic resource loading
	void RVisualMesh::SetParts(RMeshPartsType parts,char* name, const char* eluName)
	{
		if(parts < 0 && parts >= eq_parts_end ) 
			return;

		if(m_pTMesh==NULL) return;

		if(!m_pMesh || m_pMesh->m_isMeshLoaded == false) return;

		RMeshNode* pNode = m_pMesh->GetPartsNode(name,eluName);

		if(pNode) 
		{
	//		if(m_pTMesh[parts] != pNode) 
			{
				m_pTMesh[parts] = pNode;
				m_pMesh->ConnectPhysiqueParent(pNode);
			}
		}
	}

Open(ZScreenEffectMaanger.cpp) <br>
Find <br>

	void ZKOEffect::InitFrame()
	{
		m_VMesh.Stop(ani_mode_lower);
		m_VMesh.m_pMesh->SetFrame(0 , 0);
		m_VMesh.Play(ani_mode_lower);
	}

	void ZKOEffect::SetFrame(int nFrame)
	{
		m_VMesh.m_pMesh->SetFrame(nFrame , 0);
	}
	
Replace <br>

	void ZKOEffect::InitFrame()
	{
		m_VMesh.Stop(ani_mode_lower);
		m_VMesh.GetMesh()->SetFrame(0 , 0);
		m_VMesh.Play(ani_mode_lower);
	}

	void ZKOEffect::SetFrame(int nFrame)
	{
		m_VMesh.GetMesh()->SetFrame(nFrame , 0);
	}

Find <br>

		// ¸¸¾à ÀÌ¹Ì ±×¸®°í ÀÖÀ¸¸é ±×¸®Áö ¾Ê´Â´Ù.
		for (iterator itor = begin(); itor != end(); ++itor)
		{
			ZScreenEffect* pEffect = (ZScreenEffect*)(*itor);
			if (pEffect->GetVMesh()->m_pMesh == m_pAlertEffect[nIndex]) return;
		}

Replace <br>

		// ¸¸¾à ÀÌ¹Ì ±×¸®°í ÀÖÀ¸¸é ±×¸®Áö ¾Ê´Â´Ù.
		for (iterator itor = begin(); itor != end(); ++itor)
		{
			ZScreenEffect* pEffect = (ZScreenEffect*)(*itor);
			if (pEffect->GetVMesh()->GetMesh() == m_pAlertEffect[nIndex]) return;
		}

Open(ZShadow.cpp) <br>
Find <br>

	//matrix setup
	float fSize = vmesh.m_vScale.x * size_;
	rmatrix scaleMat = setSize( size_ );

Replace <br>

	//matrix setup
	float fSize = vmesh.GetScale().x * size_;
	rmatrix scaleMat = setSize( size_ );

Open(ZSkyBox.cpp) <br>
Find <br>

	bool ZSkyBox::Create( RVisualMesh* pvMesh_ )
	{
		mpVMesh = pvMesh_;
		mpVMesh->m_pMesh->mbSkyBox	= true;
		return true;
	}
	
Replace <br>

	bool ZSkyBox::Create( RVisualMesh* pvMesh_ )
	{
		mpVMesh = pvMesh_;
		mpVMesh->GetMesh()->mbSkyBox	= true;
		return true;
	}

Open(ZWeapon.cpp) <br>
Find <br>

	void ZWeaponItemKit::Render()
	{
		if(m_bInit) {
			if(m_pVMesh->m_pMesh) {
			// ¹«±â ÆÄÃ÷¸¦ Ä³¸¯ÅÍ¿¡ ºÙ¾îÀÖÀ»°æ¿ì Á¶¸íÀ» ¹Þ°í ¾ÈºÙ¾îÀÖÀ»°æ¿ì Á¶¸íÀ» ¾È¹Þ´Â 2°¡Áö¿ëµµ·Î»ç¿ëÇÏ±â¶§¹®		

			rmatrix mat;
			MakeWorldMatrix(&mat,m_Position,m_Dir,m_Up);
			m_pVMesh->SetWorldMatrix(mat);
	//		m_pVMesh->m_pMesh->m_LitVertexModel = true;
			ZMovingWeapon::Render();
	//		m_pVMesh->m_pMesh->m_LitVertexModel = false;

			}
		}
	}

Replace <br>

	void ZWeaponItemKit::Render()
	{
		if (m_bInit) {
			if (m_pVMesh->GetMesh()) {
				// ¹«±â ÆÄÃ÷¸¦ Ä³¸¯ÅÍ¿¡ ºÙ¾îÀÖÀ»°æ¿ì Á¶¸íÀ» ¹Þ°í ¾ÈºÙ¾îÀÖÀ»°æ¿ì Á¶¸íÀ» ¾È¹Þ´Â 2°¡Áö¿ëµµ·Î»ç¿ëÇÏ±â¶§¹®		

				rmatrix mat;
				MakeWorldMatrix(&mat, m_Position, m_Dir, m_Up);
				m_pVMesh->SetWorldMatrix(mat);
				//		m_pVMesh->m_pMesh->m_LitVertexModel = true;
				ZMovingWeapon::Render();
				//		m_pVMesh->m_pMesh->m_LitVertexModel = false;

			}
		}
	}

Open(ZWorldItem.cpp) <br>
Find <br>

	if(pVMesh->m_bIsRender==false)
		return;

Replace <br>

	if(pVMesh->IsRender()==false)
		return;

Open(ZCharacter.cpp) <br>
Find <br>

	void ZCharacter::TestToggleCharacter()
	{
		if(m_pVMesh->m_pMesh) {

			RMesh* pMesh = NULL;

			if( strcmp(m_pVMesh->m_pMesh->GetName(),"heroman1")==0 ) {
				pMesh = ZGetMeshMgr()->Get("herowoman1");//¿øÇÏ´Â ¸ðµ¨À» ºÙ¿©ÁÖ±â..
				m_pVMesh->m_pMesh = pMesh;
				m_pVMesh->ClearParts();//³²³à°¡ Æ²·Á¼­.
				TestChangePartsAll();
			}
			else {
				pMesh = ZGetMeshMgr()->Get("heroman1");//¿øÇÏ´Â ¸ðµ¨À» ºÙ¿©ÁÖ±â..
				m_pVMesh->m_pMesh = pMesh;
				m_pVMesh->ClearParts();
				TestChangePartsAll();
			}
		}
	}

Replace <br>

	void ZCharacter::TestToggleCharacter()
	{
		if(m_pVMesh->GetMesh()) {

			RMesh* pMesh = NULL;

			if( strcmp(m_pVMesh->GetMesh()->GetName(),"heroman1")==0 ) {
				pMesh = ZGetMeshMgr()->Get("herowoman1");//¿øÇÏ´Â ¸ðµ¨À» ºÙ¿©ÁÖ±â..
				m_pVMesh->SetMesh(pMesh);
				m_pVMesh->ClearParts();//³²³à°¡ Æ²·Á¼­.
				TestChangePartsAll();
			}
			else {
				pMesh = ZGetMeshMgr()->Get("heroman1");//¿øÇÏ´Â ¸ðµ¨À» ºÙ¿©ÁÖ±â..
				m_pVMesh->SetMesh(pMesh);
				m_pVMesh->ClearParts();
				TestChangePartsAll();
			}
		}
	}

Find <br>

	bool ZCharacter::CheckDrawGrenade()
	{
		if(m_Items.GetSelectedWeapon()==NULL) return false;

		if( m_pVMesh ) {
			if( m_pVMesh->m_SelectWeaponMotionType==eq_wd_grenade ) {
				if( m_Items.GetSelectedWeapon()->GetBulletCurrMagazine() ) {
					return true;
				}
			}
		}
		return false;
	}

Replace <br>

	bool ZCharacter::CheckDrawGrenade()
	{
		if(m_Items.GetSelectedWeapon()==NULL) return false;

		if( m_pVMesh ) {
			if( m_pVMesh->GetSelectWeaponMotionType()==eq_wd_grenade ) {
				if( m_Items.GetSelectedWeapon()->GetBulletCurrMagazine() ) {
					return true;
				}
			}
		}
		return false;
	}

Find <br>

	if(pVMesh) {
		if(pVMesh->m_pMesh) {
			if(strcmp(pVMesh->m_pMesh->GetName(),"heroman1")!=0) {
				mode +=6;
			}
		}
	}

Replace <br>

	if(pVMesh) {
		if(pVMesh->GetMesh()) {
			if(strcmp(pVMesh->GetMesh()->GetName(),"heroman1")!=0) {
				mode +=6;
			}
		}
	}

Find <br>

	m_pVMesh->m_bSkipRenderFaceParts = false;


Replace <br>

	m_pVMesh->SetSkipRenderFaceParts(false);

Find <br>

	m_pVMesh->m_bSkipRenderFaceParts = true;

Replace <br>

	m_pVMesh->SetSkipRenderFaceParts(true);

Open(ZCharacterObject.cpp) <br>
Find <br>

	bool ZCharacterObject::IsDoubleGun() { 

		if(m_pVMesh) {
			if(m_pVMesh->m_SelectWeaponMotionType==eq_wd_pistol) {
				return true;
			} else if(m_pVMesh->m_SelectWeaponMotionType==eq_wd_smg) {
				return true;
			}
		}
		return false;
	}


Replace <br>


	bool ZCharacterObject::IsDoubleGun() { 

		if(m_pVMesh) {
			if(m_pVMesh->GetSelectWeaponMotionType()==eq_wd_pistol) {
				return true;
			} else if(m_pVMesh->GetSelectWeaponMotionType()==eq_wd_smg) {
				return true;
			}
		}
		return false;
	}


Find <br>

	bool ZCharacterObject::GetCurrentWeaponDirection(rvector* dir)
	{
		if(m_pVMesh && dir) {

			rmatrix* mat = &m_pVMesh->m_WeaponDummyMatrix[weapon_dummy_muzzle_flash];//ÃÑ±¸

			dir->x = mat->_21;
			dir->y = mat->_22;
			dir->z = mat->_23;

			return true;
		}
		return false;
	}


Replace <br>

	bool ZCharacterObject::GetCurrentWeaponDirection(rvector* dir)
	{
		if(m_pVMesh && dir) {

			const rmatrix* mat = &m_pVMesh->GetWeaponDummyMatrix(weapon_dummy_muzzle_flash);//ÃÑ±¸

			dir->x = mat->_21;
			dir->y = mat->_22;
			dir->z = mat->_23;

			return true;
		}
		return false;
	}

Open(ZCombatInterface.cpp) <br>
Find <br>

	if (pMyChar && pMyChar->m_pVMesh) {

		RWeaponMotionType type = (RWeaponMotionType)pMyChar->m_pVMesh->GetSetectedWeaponMotionID();

		if ((type == eq_wd_katana) || (type == eq_wd_grenade) || (type == eq_ws_dagger) || (type == eq_wd_dagger)
			|| (type == eq_wd_item) || (type == eq_wd_sword) || (type == eq_wd_blade)) {
			bPick = false;
		}

		if (pMyChar->m_pVMesh->m_vRotXYZ.y > -20.f && pMyChar->m_pVMesh->m_vRotXYZ.y < 30.f) {
			bPick = false;
		}

		if (pMyChar->m_pVMesh->m_vRotXYZ.y < -25.f)
			bPick = true;

		if (pMyChar->IsMan()) { // ¸ðµ¨ÀÌ ³²ÀÚ°í
			if (pMyChar->m_pVMesh->m_vRotXYZ.x < -20.f) {//¿À¸¥ÂÊÀ¸·Î ÀÌµ¿Áß¿¡
				if (RCameraDirection.z < -0.2f)
					bPick = true;
			}
		}

Replace <br>

	if(pMyChar && pMyChar->m_pVMesh) {
		
		rvector vRot = pMyChar->m_pVMesh->GetRotXYZ();

		RWeaponMotionType type = (RWeaponMotionType)pMyChar->m_pVMesh->GetSetectedWeaponMotionID();

		if( (type==eq_wd_katana) || (type==eq_wd_grenade) || (type==eq_ws_dagger) || (type==eq_wd_dagger) 
			|| (type==eq_wd_item) || (type==eq_wd_sword) || (type==eq_wd_blade) || (type == eq_wd_spycase)) {
			bPick = false;
		}

		if(vRot.y  > -20.f &&  vRot.y < 30.f) {
			bPick = false;
		}

		if(vRot.y < -25.f)
			bPick = true;

		if( pMyChar->IsMan() ) { // ¸ðµ¨ÀÌ ³²ÀÚ°í
			if( vRot.x < -20.f) {//¿À¸¥ÂÊÀ¸·Î ÀÌµ¿Áß¿¡
				if( RCameraDirection.z < -0.2f)
					bPick = true;
			}
		}

Open(ZMeshView.cpp) <br>
Find <br>

	if(m_pVisualMesh->m_pMesh==NULL) {

Replace <br>

	if(m_pVisualMesh->GetMesh()==NULL) {

Open(ZGame.cpp) <br>
Find <br>

	void ZGame::OnExplosionGrenade(MUID uidOwner,rvector pos,float fDamage,float fRange,float fMinDamage,float fKnockBack,MMatchTeam nTeamID)
	{

Add Above <br>

	bool ZGame::IsWallBlocked(ZObject* pObj1, ZObject* pObj2, bool bCoherentToPeer)
	{
		//### ÀÌ ÇÔ¼ö¸¦ ¼öÁ¤ÇÏ?E¶È°°ÀÌ IsWallBlocked()¿¡µµ Àû?E?ÁÖ¾ûÚß ÇÕ´Ï´Ù. ###

		// ÇÇ¾ûÏ¢¸® ÁÂÇ¥¸¦ º¸³¾¶§ ÇöÀç´Â float->short Ä³½ºÆÃÀÌ ÀÏ¾ûÏ­´Ù (?E¼Ò¼öÁ¡ÀÌÇÏ ¹ö¸²)
		// µû¶ó¼­ Å¬¶óÀÌ¾ðÆ®µéÀÌ °¢ÀÚ ÆÇÁ¤ÇÑ °ªÀÌ ¹Ì¹¦ÇÏ°Ô ´Ù¸¦ ¼ö°¡ ÀÖ´Ù. ÀÌ°ÍÀÌ ±âÁ¸¿¡ ¹®Á¦¸¦ ÀÏÀ¸Å°?E¾Ê¾ÒÀ¸³ª
		// ¼­¹ÙÀÌ¹ú¿¡¼­ ³·Àº È®?E?¹®Á¦°¡ ¹ß»ý: npc°¡ ÇÃ·¹ÀÌ¾ûÔ¦ ±ÙÁ¢°ø°ÝÇÏ·Á?EÇÒ¶§, npc ÄÁÆ®·Ñ·¯´Â °ø°Ý °¡´ÉÇÏ´Ù?EÆÇÁ¤.
		// ÇÇ°Ý´çÇÏ´Â Å¬¶óÀÌ¾ðÆ®´Â °ø°Ý °¡´ÉÇÏ?E¾Ê´Ù?EÆÇÁ¤. ÀÌ·Î?EÇÇ°ÝµÇ´Â À¯Àú°¡ À§Ä¡¸¦ ¹Ù²Ù?E¾Ê´ÂÇÑ ¸ó½ºÅÍ´Â Á¦ÀÚ¸®¿¡¼­ ¹«ÇÑ ?EæÀ?Ä¡°ÔµÊ (¼Ö±ûÔ» ¾Ç?EºÒ°¡¶ó?E»ý°¢ÇÏÁö¸¸ ÆÛºúÔ®¼ÅÀÇ ±Ù¼º¿¡ Á³À½)
		// bCoherentToPeer==true ÀÏ¶§ ÇÇ¾ûÛ¡°Ô º¸³½ °Í?E°°Àº °ªÀ» »ç?E?.

		if ((pObj1 == NULL) || (pObj2 == NULL))
			return false;

		if ((pObj1->GetVisualMesh() == NULL) || (pObj2->GetVisualMesh() == NULL))
			return false;

		// ¿¡´Ï¸ÞÀÌ¼Ç ¶§¹®¿¡ º®À» ¶Õ?Eµé¾ûÌ¡´Â °æ?E?ÀÖ¾ûØ­..
		rvector p1 = pObj1->GetPosition() + rvector(0.f, 0.f, 100.f);
		rvector p2 = pObj2->GetPosition() + rvector(0.f, 0.f, 100.f);

		if (bCoherentToPeer)
		{
			p1.x = short(p1.x);
			p1.y = short(p1.y);
			p1.z = short(p1.z);
			p2.x = short(p2.x);
			p2.y = short(p2.y);
			p2.z = short(p2.z);
			// ¿ÀÂ÷·Î ÀÎÇÑ ¹ö±× Àç?EÅ×½ºÆ®¸¦ ½±°Ô ÇÏ?EÀ§ÇØ 1ÀÇ ÀÚ¸®±û?EÀý»çÇÑ ¹ö?E
			/*p1.x = (short(p1.x * 0.1f)) * 10.f;
			p1.y = (short(p1.y * 0.1f)) * 10.f;
			p1.z = (short(p1.z * 0.1f)) * 10.f;
			p2.x = (short(p2.x * 0.1f)) * 10.f;
			p2.y = (short(p2.y * 0.1f)) * 10.f;
			p2.z = (short(p2.z * 0.1f)) * 10.f;*/
		}

		rvector dir = p2 - p1;

		Normalize(dir);

		ZPICKINFO pickinfo;

		if (Pick(pObj1, p1, dir, &pickinfo)) {//º®ÀÌ¶ó?E
			if (pickinfo.bBspPicked)//¸ÊÀÌ °É¸°°æ?E
				return true;
		}

		return false;
	}
	//jintriple3 µð¹ö±× ·¹Áö½ºÅÍ ÇØÅ·.....ºñ±³¸¦ À§ÇØ¼­
	bool ZGame::IsWallBlocked(ZObject* pObj1, ZObject* pObj2, int & nDebugRegister/*´Ü?Eºñ±³?E*/, bool bCoherentToPeer)
	{	//bCoherentToPeer¿¡ ?EÑ°ÍÀ?¿øº» CheckWall ÁÖ¼® ?EE

		if ((pObj1 == NULL) || (pObj2 == NULL))
		{
			nDebugRegister = -10;	//¿ª½Ã³ª ¼ýÀÚ´Â ÀÇ¹Ì°¡ ¾ø´Ù..
			return false;
		}

		if ((pObj1->GetVisualMesh() == NULL) || (pObj2->GetVisualMesh() == NULL))
		{
			nDebugRegister = -10;
			return false;
		}

		// ¿¡´Ï¸ÞÀÌ¼Ç ¶§¹®¿¡ º®À» ¶Õ?Eµé¾ûÌ¡´Â °æ?E?ÀÖ¾ûØ­..
		rvector p1 = pObj1->GetPosition() + rvector(0.f, 0.f, 100.f);
		rvector p2 = pObj2->GetPosition() + rvector(0.f, 0.f, 100.f);

		if (bCoherentToPeer)
		{
			p1.x = short(p1.x);
			p1.y = short(p1.y);
			p1.z = short(p1.z);
			p2.x = short(p2.x);
			p2.y = short(p2.y);
			p2.z = short(p2.z);
			// ¿ÀÂ÷·Î ÀÎÇÑ ¹ö±× Àç?EÅ×½ºÆ®¸¦ ½±°Ô ÇÏ?EÀ§ÇØ 1ÀÇ ÀÚ¸®±û?EÀý»çÇÑ ¹ö?E
			/*p1.x = (short(p1.x * 0.1f)) * 10.f;
			p1.y = (short(p1.y * 0.1f)) * 10.f;
			p1.z = (short(p1.z * 0.1f)) * 10.f;
			p2.x = (short(p2.x * 0.1f)) * 10.f;
			p2.y = (short(p2.y * 0.1f)) * 10.f;
			p2.z = (short(p2.z * 0.1f)) * 10.f;*/
		}

		rvector dir = p2 - p1;

		Normalize(dir);

		ZPICKINFO pickinfo;

		if (Pick(pObj1, p1, dir, &pickinfo)) {//º®ÀÌ¶ó?E
			if (pickinfo.bBspPicked)//¸ÊÀÌ °É¸°°æ?E
			{
				nDebugRegister = FOR_DEBUG_REGISTER;
				return true;
			}
		}
		nDebugRegister = -10;
		return false;
	}

Open(ZGame.h) <br>
Find <br>

	int  SelectSlashEffectMotion(ZCharacter* pCharacter);
	//jintriple3 µð¹ö±× ·¹Áö½ºÅÍ ÇØÅ· ¹æÁö~!!!
	bool CheckWall(ZObject* pObj1,ZObject* pObj2, bool bCoherentToPeer=false);
	bool CheckWall(ZObject* pObj1,ZObject* pObj2, int & nDebugRegister/*´Ü¼ø ºñ±³¿ë*/, bool bCoherentToPeer=false);

	void InitRound();

Replace <br>

	int  SelectSlashEffectMotion(ZCharacter* pCharacter);
	//jintriple3 µð¹ö±× ·¹Áö½ºÅÍ ÇØÅ· ¹æÁö~!!!
	bool IsWallBlocked(ZObject* pObj1, ZObject* pObj2, bool bCoherentToPeer = false);
	bool IsWallBlocked(ZObject* pObj1, ZObject* pObj2, int& nDebugRegister/*´Ü¼ø ºñ±³¿ë*/, bool bCoherentToPeer = false);

	bool InRanged(ZObject* pAttacker, ZObject* pVictim);


	void InitRound();


Open(RMesh_Mtrl.cpp) <br>
Find <br>

	void RMesh::SetMtrlUvAni_ON()
	{
		if( m_pVisualMesh && m_pVisualMesh->m_bUVAni) { // on

			rmatrix mat;
			D3DXMatrixIdentity(&mat);

			float add_t = timeGetTime() / 1000.f;

			mat._31 = add_t * m_pVisualMesh->m_fUAniValue;
			mat._32 = add_t * m_pVisualMesh->m_fVAniValue;

			RGetDevice()->SetTransform( D3DTS_TEXTURE0, &mat);
			RGetDevice()->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2 ); 
			RGetDevice()->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, 0 );
		}
	}

	void RMesh::SetMtrlUvAni_OFF()
	{
		if( m_pVisualMesh && m_pVisualMesh->m_bUVAni) {//off

			RGetDevice()->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE );

		}
	}

Replace <br>

	void RMesh::SetMtrlUvAni_ON()
	{
		if( m_pVisualMesh && m_pVisualMesh->IsUVAni()) { // on

			rmatrix mat;
			D3DXMatrixIdentity(&mat);

			float add_t = timeGetTime() / 1000.f;

			mat._31 = add_t * m_pVisualMesh->GetUAniValue();
			mat._32 = add_t * m_pVisualMesh->GetVAniValue();

			RGetDevice()->SetTransform( D3DTS_TEXTURE0, &mat);
			RGetDevice()->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2 ); 
			RGetDevice()->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, 0 );
		}
	}

	void RMesh::SetMtrlUvAni_OFF()
	{
		if( m_pVisualMesh && m_pVisualMesh->IsUVAni()) {//off

			RGetDevice()->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE );

		}
	}

Find <br>

	if( m_pVisualMesh && !pMNode->m_bNpcWeaponMeshNode ) { 
		_color = m_pVisualMesh->m_NPCBlendColor; 
	}

Replace <br>

	if( m_pVisualMesh && !pMNode->m_bNpcWeaponMeshNode ) { 
		_color = m_pVisualMesh->GetNPCBlendColor(); 
	}


Open(RMesh_Render.cpp) <br>
Find <br>

	if(m_pVisualMesh && m_pVisualMesh->m_bIsCharacter)
		m_pVisualMesh->ClearPartInfo();

Replace <br>

	if(m_pVisualMesh && m_pVisualMesh->IsCharacter())
		m_pVisualMesh->ClearPartInfo();


Find <br>

		if(pPartsMeshNode->m_isDummyMesh)	{ //Bip,Bone,Dummy Skip

			if( m_pVisualMesh ) {
				if( m_pVisualMesh->m_pBipMatrix ) {
					if(pMeshNode->m_PartsPosInfoType!=eq_parts_pos_info_etc) { 
						m_pVisualMesh->m_pBipMatrix[pMeshNode->m_PartsPosInfoType] = pMeshNode->m_mat_result;
					}
				}
			}
			it_obj++;
			continue;
		}

Replace <br>

		if(pPartsMeshNode->m_isDummyMesh)	{ //Bip,Bone,Dummy Skip

			if( m_pVisualMesh ) {
				if( m_pVisualMesh->GetBipMatrixArray()) {
					if(pMeshNode->m_PartsPosInfoType!=eq_parts_pos_info_etc) { 
						m_pVisualMesh->GetBipMatrixArray()[pMeshNode->m_PartsPosInfoType] = pMeshNode->m_mat_result;
					}
				}
			}
			it_obj++;
			continue;
		}		

Find <br>

	if(m_pVisualMesh->m_pTOCCL)

Replace <br>

	if(m_pVisualMesh->GetTOCCL())

Find <br>

				if(m_pVisualMesh->m_bCheckViewFrustum) {//tool ÀÌ¶ó¸é false
					if(isInViewFrustumWithZ( &bb, RGetViewFrustum()) == false) {
						return false;
					}
				}

				return m_pVisualMesh->m_pTOCCL->IsVisible(bb);
			}

Replace <br>

				if(m_pVisualMesh->IsCheckViewFrustum()) {//tool ÀÌ¶ó¸é false
					if(isInViewFrustumWithZ( &bb, RGetViewFrustum()) == false) {
						return false;
					}
				}

				return m_pVisualMesh->GetTOCCL()->IsVisible(bb);
			}

Find <br>

	if(m_pVisualMesh)
		if(m_pVisualMesh->m_bRenderMatrix)//¸ÅÆ®¸¯½º °»½Å¸¸ ¿øÇÏ´Â °æ¿ì¶ó¸é....
			return;


Replace <br>

	if(m_pVisualMesh)
		if(m_pVisualMesh->IsRenderMatrix())//¸ÅÆ®¸¯½º °»½Å¸¸ ¿øÇÏ´Â °æ¿ì¶ó¸é....
			return;


Open(RVisualMesh.cpp) <br>
Find <br>

			pSInfo->SetName( m_pAniSet->GetSoundFileName() );
			pSInfo->SetRelatedToBsp( m_pAniSet->IsSoundRelatedToMap() );
			pSInfo->SetPos( pVMesh->m_WorldMat._41, pVMesh->m_WorldMat._42, pVMesh->m_WorldMat._43 );
		}
	}

Replace <br>

			pSInfo->SetName( m_pAniSet->GetSoundFileName() );
			pSInfo->SetRelatedToBsp( m_pAniSet->IsSoundRelatedToMap() );
			pSInfo->SetPos( pVMesh->GetWorldMat()._41, pVMesh->GetWorldMat()._42, pVMesh->GetWorldMat()._43 );
		}
	}

Find <br>

			if( m_pAniSet->IsHaveSoundFile()) {
				RAniSoundInfo* pSInfo = &m_SoundInfo;
				pSInfo->isPlay = true;
				pSInfo->SetName(m_pAniSet->GetSoundFileName());
				pSInfo->SetRelatedToBsp(m_pAniSet->IsSoundRelatedToMap());
				pSInfo->SetPos(pVMesh->m_WorldMat._41,pVMesh->m_WorldMat._42,pVMesh->m_WorldMat._43);
			}

Replace <br>

			if( m_pAniSet->IsHaveSoundFile()) {
				RAniSoundInfo* pSInfo = &m_SoundInfo;
				pSInfo->isPlay = true;
				pSInfo->SetName(m_pAniSet->GetSoundFileName());
				pSInfo->SetRelatedToBsp(m_pAniSet->IsSoundRelatedToMap());
				pSInfo->SetPos(pVMesh->GetWorldMat()._41,pVMesh->GetWorldMat()._42,pVMesh->GetWorldMat()._43);
			}

Find <br>

				if( (*(m_pAniNameEventSet->m_AniNameEventSetIter))->GetBeginFrame() <= m_nFrame )
				{
					(*(m_pAniNameEventSet->m_AniNameEventSetIter))->m_vPos.x = pVMesh->m_WorldMat._41;
					(*(m_pAniNameEventSet->m_AniNameEventSetIter))->m_vPos.y = pVMesh->m_WorldMat._42;
					(*(m_pAniNameEventSet->m_AniNameEventSetIter))->m_vPos.z = pVMesh->m_WorldMat._43;
					m_pEventFunc((*m_pAniNameEventSet->m_AniNameEventSetIter));		
					(*m_iterCheckAniEvent) = true;
				}

Replace <br>

				if( (*(m_pAniNameEventSet->m_AniNameEventSetIter))->GetBeginFrame() <= m_nFrame )
				{
					(*(m_pAniNameEventSet->m_AniNameEventSetIter))->m_vPos.x = pVMesh->GetWorldMat()._41;
					(*(m_pAniNameEventSet->m_AniNameEventSetIter))->m_vPos.y = pVMesh->GetWorldMat()._42;
					(*(m_pAniNameEventSet->m_AniNameEventSetIter))->m_vPos.z = pVMesh->GetWorldMat()._43;
					m_pEventFunc((*m_pAniNameEventSet->m_AniNameEventSetIter));		
					(*m_iterCheckAniEvent) = true;
				}

Find <br>

	void RVisualLightMgr::Clone(RVisualMesh* pVMesh)
	{
		if(!pVMesh) return;

		for(int i=0;i<VISUAL_LIGHT_MAX;i++) 
		{
			pVMesh->m_LightMgr.m_Light[i]		= m_Light[i];
			pVMesh->m_LightMgr.m_LightEnable[i] = m_LightEnable[i];
		}
	}

Replace <br>

	void RVisualLightMgr::Clone(RVisualMesh* pVMesh)
	{
		if(!pVMesh) return;

		for(int i=0;i<VISUAL_LIGHT_MAX;i++) 
		{
			pVMesh->GetLightMgr()->m_Light[i]		= m_Light[i];
			pVMesh->GetLightMgr()->m_LightEnable[i] = m_LightEnable[i];
		}
	}

Find <br>

	void RVisualMeshMgr::Render(int id) {

		if(m_list.empty()) return;

		r_vmesh_node node;
		for(node = m_list.begin(); node != m_list.end();) {
			if((*node)->m_id == id) {
				(*node)->Render();
				return;
			}
			else ++node;
		}
	}

Replace <br>

	void RVisualMeshMgr::Render(int id) {

		if(m_list.empty()) return;

		r_vmesh_node node;
		for(node = m_list.begin(); node != m_list.end();) {
			if((*node)->GetId() == id) {
				(*node)->Render();
				return;
			}
			else ++node;
		}
	}

Find <br>

	void RVisualMeshMgr::Del(int id) {

		if(m_list.empty()) return;

		r_vmesh_node node;

		for(node = m_list.begin(); node != m_list.end();) {
			if((*node)->m_id == id) {
				delete (*node);
				node = m_list.erase(node);
			}
			else ++node;
		}
	}

Replace <br>

	void RVisualMeshMgr::Del(int id) {

		if(m_list.empty()) return;

		r_vmesh_node node;

		for(node = m_list.begin(); node != m_list.end();) {
			if((*node)->GetId() == id) {
				delete (*node);
				node = m_list.erase(node);
			}
			else ++node;
		}
	}

Open(ZGame.h) <br>
Find <br>

		void OnPreDraw();
		bool OnRuleCommand(MCommand* pCommand);
		bool InRanged( ZObject* pAttacker, ZObject* pVictim);
		bool InRanged( ZObject* pAttacker, ZObject* pVictim, int &nDebugRegister/*µð¹ö±× ·¹Áö½ºÅÍ ÇØÅ· ¹æÁö¸¦ À§ÇÑ º¯¼ö*/);

	public:

Replace <br>

	void OnPreDraw();
	bool OnRuleCommand(MCommand* pCommand);
	bool InRanged(ZObject* pAttacker, ZObject* pVictim, int& nDebugRegister/*µð¹ö±× ·¹Áö½ºÅÍ ÇØÅ· ¹æÁö¸¦ À§ÇÑ º¯¼ö*/);

	public:

Open(ZGameAction.cpp) <br>
Find <br>

			bReturnValue = ZGetGame()->CheckWall( pOwnerCharacter, pTar) == true;
			if( ZGetGame()->CheckWall( pOwnerCharacter,pTar ) == true)
				PROTECT_DEBUG_REGISTER(bReturnValue)
					continue;

Replace <br>

			bReturnValue = ZGetGame()->IsWallBlocked( pOwnerCharacter, pTar) == true;
			if( ZGetGame()->IsWallBlocked( pOwnerCharacter,pTar ) == true)
				PROTECT_DEBUG_REGISTER(bReturnValue)
					continue;

Find <br>

				if(ZGetGame()->CheckWall(pOwnerCharacter,pTar)==true) //Áß°£¿¡ º®ÀÌ ¸·°í ÀÖ´Â°¡?
					bCheck = false;

Replace <br>

				if(ZGetGame()->IsWallBlocked(pOwnerCharacter,pTar)==true) //Áß°£¿¡ º®ÀÌ ¸·°í ÀÖ´Â°¡?
					bCheck = false;
Find <br>

				if(ZGetGame()->CheckWall(pOwnerCharacter,pTar)==true) //Áß°£¿¡ º®ÀÌ ¸·°í ÀÖ´Â°¡?
					bCheck = false;

Replace <br>

				if(ZGetGame()->IsWallBlocked(pOwnerCharacter,pTar)==true) //Áß°£¿¡ º®ÀÌ ¸·°í ÀÖ´Â°¡?
					bCheck = false;

Open(ZMyCharacter.cpp) <br>
Find <br>

					if(ZGetGame()->CheckWall(this,pTar)==true) //Áß°£¿¡ º®ÀÌ ¸·°í ÀÖ´Â°¡?
						bCheck = false;

Replace <br>

					if(ZGetGame()->IsWallBlocked(this,pTar)==true) //Áß°£¿¡ º®ÀÌ ¸·°í ÀÖ´Â°¡?
						bCheck = false;

Find <br>

				if (ZGetGame()->CheckWall(this, pTar) == true) //Áß°£¿¡ º®ÀÌ ¸·°í ÀÖ´Â°¡?
					bCheck = false;
					
Replace <br>

				if(ZGetGame()->IsWallBlocked(this,pTar)==true) //Áß°£¿¡ º®ÀÌ ¸·°í ÀÖ´Â°¡?
					bCheck = false;

Open(ZEffectAniMesh.cpp) <br>
Find <br>

	bool ZEffectAniMesh::Draw(unsigned long int nTime)
	{
		if(m_VMesh.m_pMesh==NULL)
			return false;

Replace <br>

	bool ZEffectAniMesh::Draw(unsigned long int nTime)
	{
		if(m_VMesh.GetMesh()==NULL)
			return false;

Find <br>

		if(m_nAutoAddEffect == ZEffectAutoAddType_Methor ) {

			pNode = m_VMesh.m_pMesh->GetMeshData("methor");

Replace <br>

		if(m_nAutoAddEffect == ZEffectAutoAddType_Methor ) {

			pNode = m_VMesh.GetMesh()->GetMeshData("methor");


Open(ZEffectManager.cpp) <br>
Find <br>

	void ZEffectManager::AddHasteBeginEffect(const rvector& Target, ZObject* pObj)
	{
		ZEffect* pNew = NULL;

		rvector pos = Target;
		rvector dir = -RealSpace2::RCameraDirection;
		dir.z = 0.f;

		pNew = new ZEffectDash(m_pHasteBeginEffect,pos,dir,pObj->GetUID());
		((ZEffectDash*)pNew)->SetScale(rvector(15,15,15));
		((ZEffectDash*)pNew)->SetAlignType(1);

		if (pObj->GetUID() == ZGetMyUID())
			((ZEffectDash*)pNew)->GetVMesh()->m_bCheckViewFrustum = false;

		Add(pNew);
	}

Replace <br>

	void ZEffectManager::AddHasteBeginEffect(const rvector& Target, ZObject* pObj)
	{
		ZEffect* pNew = NULL;

		rvector pos = Target;
		rvector dir = -RealSpace2::RCameraDirection;
		dir.z = 0.f;

		pNew = new ZEffectDash(m_pHasteBeginEffect,pos,dir,pObj->GetUID());
		((ZEffectDash*)pNew)->SetScale(rvector(15,15,15));
		((ZEffectDash*)pNew)->SetAlignType(1);

		if (pObj->GetUID() == ZGetMyUID())
			((ZEffectDash*)pNew)->GetVMesh()->SetCheckViewFrustum(false);

		Add(pNew);
	}

Open(ZEffectStaticMesh.cpp) <br>
Find <br>

	bool ZEffectStaticMesh::Draw(unsigned long int nTime)
	{
		if(m_VMesh.m_pMesh==NULL) 
			return false;

Replace <br>

	bool ZEffectStaticMesh::Draw(unsigned long int nTime)
	{
		if(m_VMesh.GetMesh()==NULL) 
			return false;

Open(ZObject.cpp) <br>
Find <br>

	void ZObject::SetVisualMesh(RVisualMesh* pVMesh)
	{ 
		m_pVMesh = pVMesh; 

		// ¾Ö´Ï¸ÞÀÌ¼Ç ÄÝ¹é µî·Ï
		for(int i=0;i<ani_mode_end;i++)
		{
			m_pVMesh->GetFrameInfo((RAniMode)i)->SetAnimEventHandler(ZAniEventHandler::ZAniEventHandlerCB);
		}
	}

Replace <br>

	void ZObject::SetVisualMesh(ZObjectVMesh* pVMesh)
	{ 
		m_pVMesh = pVMesh; 

		// ¾Ö´Ï¸ÞÀÌ¼Ç ÄÝ¹é µî·Ï
		for(int i=0;i<ani_mode_end;i++)
		{
			m_pVMesh->GetFrameInfo((RAniMode)i)->SetAnimEventHandler(ZAniEventHandler::ZAniEventHandlerCB);
		}
	}

Open(ZObject.h) <br>
Find <br>

	void SetVisualMesh(RVisualMesh* pVMesh);
	RVisualMesh* GetVisualMesh()					{ return m_pVMesh; }

Replace <br>


	void SetVisualMesh(ZObjectVMesh* pVMesh);
	ZObjectVMesh* GetVisualMesh()					{ return m_pVMesh; }


Find <br>

	#include "MMemoryProxy.h"

	#include <list>
	#include <string>


Replace <br>

	#include "ZObjectVMesh.h"

Open(ZObject.h) <br>
Find <br>

	RVisualMesh*			m_pVMesh;

Replace <br>

	ZObjectVMesh*			m_pVMesh;

Open(RVisualMesh.cpp) <br>
Find <br>

	void RVisualMesh::SetRotXYZ(rvector v) {
		m_vRotXYZ = v;
	}

Replace <br>

	//void RVisualMesh::SetRotXYZ(rvector v) {
	//	m_vRotXYZ = v;
	//}

Open(RVisualMesh.h) <br>
Find <br>

	void SetParts(RMeshPartsType parts,RMeshNode* pMN);
	void SetParts(RMeshPartsType parts,char* name);

Replace <br>

	void SetParts(RMeshPartsType parts,RMeshNode* pMN);
	void SetParts(RMeshPartsType parts,char* name, const char* eluName);

Find <br>

	bool SetAnimation(RAnimation* pAniSet,bool b=false);
	bool SetAnimation(char* ani_name,bool b=false);
	bool SetAnimation(RAniMode animode,RAnimation* pAniSet,bool b=false);
	bool SetAnimation(RAniMode animode,char* ani_name,bool b=false);

Replace <br>

	bool SetAnimation(RAnimation* pAniSet,bool b=false);
	bool SetAnimation(const char* ani_name,bool b=false);
	bool SetAnimation(RAniMode animode,RAnimation* pAniSet,bool b=false);
	bool SetAnimation(RAniMode animode,const char* ani_name,bool b=false);



Open(RVisualMesh.cpp) <br>
Find <br>

	bool RVisualMesh::SetAnimation(RAniMode animode,char* ani_name,bool b)
	{

Replace <br>

	bool RVisualMesh::SetAnimation(RAniMode animode,const char* ani_name,bool b)
	{

Find <br>

	bool RVisualMesh::SetAnimation(char* ani_name,bool b)
	{
		return SetAnimation(ani_mode_lower,ani_name,b);
	}

Replace <br>

	bool RVisualMesh::SetAnimation(const char* ani_name,bool b)
	{
		return SetAnimation(ani_mode_lower,ani_name,b);
	}

Open(ZCombatInterface.cpp) <br>
Find <br>

		pos = pObject->GetPosition();
		RVisualMesh* pVMesh = pObject->m_pVMesh;
		RealSpace2::rboundingbox box;

		if (pVMesh == NULL) continue;

Replace <br>

		pos = pObject->GetPosition();
		RealSpace2::rboundingbox box;

		if (pObject->m_pVMesh == NULL) continue;


Open(ZGame.cpp) <br>
Find <br>

		// °ø°ÝÀÚ¿Í Å¸°Ù »çÀÌ¿¡ º®ÀÌ ¸·°í ÀÖÀ¸¸é ´ÙÀ½ Å¸°ÙÀ¸·Î ³Ñ¾î°£´Ù.
		int nDebugRegister = 0;
		bRetVal = CheckWall( pAttacker, pVictim, nDebugRegister, true);
		//jintriple3 µð¹ö±× ·¹Áö½ºÅÍ ÇÙ ¹æÁö....
		if ( bRetVal)
			PROTECT_DEBUG_REGISTER(nDebugRegister == FOR_DEBUG_REGISTER)
				continue;

Replace <br>

		// °ø°ÝÀÚ¿Í Å¸°Ù »çÀÌ¿¡ º®ÀÌ ¸·°í ÀÖÀ¸¸é ´ÙÀ½ Å¸°ÙÀ¸·Î ³Ñ¾î°£´Ù.
		int nDebugRegister = 0;
		bRetVal = IsWallBlocked( pAttacker, pVictim, nDebugRegister, true);
		//jintriple3 µð¹ö±× ·¹Áö½ºÅÍ ÇÙ ¹æÁö....
		if ( bRetVal)
			PROTECT_DEBUG_REGISTER(nDebugRegister == FOR_DEBUG_REGISTER)
				continue;

Open(ZObjectManager.cpp) <br>
Find <br>

		RVisualMesh* pVMesh = pMyCharacter->GetVisualMesh();

Replace <br>

		ZObjectVMesh* pVMesh = pMyCharacter->GetVisualMesh();

Open(ZShadow.cpp) <br>
Find <br>

	bool ZShadow::setMatrix( RVisualMesh& vmesh, float size_ /* = 100.f  */, RBspObject* p_map /* = 0 */)
	{

Replace <br>

	bool ZShadow::setMatrix( ZObjectVMesh& vmesh, float size_ /* = 100.f  */, RBspObject* p_map /* = 0 */)
	{

Open(ZShadow.h) <br>
Find <br>

	bool setMatrix( ZCharacterObject& char_, float size_ = 100.0f );	// ¸Å ÇÁ·¹ÀÓ¸¶´Ù ºÒ·ÁÁ®¾ß ÇÔ
	bool setMatrix( RVisualMesh& vmesh, float size_ = 100.f, RBspObject* p_map  = 0 );
	void draw(bool bForced=false);

Replace <br>

	bool setMatrix( ZCharacterObject& char_, float size_ = 100.0f );	// ¸Å ÇÁ·¹ÀÓ¸¶´Ù ºÒ·ÁÁ®¾ß ÇÔ
	bool setMatrix( ZObjectVMesh& vmesh, float size_ = 100.f, RBspObject* p_map  = 0 );
	void draw(bool bForced=false);

Open(RAnimationMgr.h) <br>
Find <br>

	RAnimation* GetAnimation(char* name,int MotionTypeID=-1);
	RAnimation* GetAnimation(int sID,int MotionTypeID=-1);
	RAnimation* GetAnimationListMap(char* name,int wtype);

Replace <br>

	RAnimation* GetAnimation(const char* name,int MotionTypeID=-1);
	RAnimation* GetAnimation(int sID,int MotionTypeID=-1);
	RAnimation* GetAnimationListMap(const char* name,int wtype);

Open(RAnimationMgr.cpp) <br>
Find <br>

	RAnimation* RAnimationMgr::GetAnimationListMap(char* name,int wtype) {

		if(m_list_map_size==0) return NULL;

		if(m_list_map_size-1 < wtype) {
			return NULL;
		}

		RAnimation* pAni = m_list_map[wtype].Find(name);

		return pAni;
	}

	RAnimation* RAnimationMgr::GetAnimation(char* name,int wtype) 
	{
		if(!name) 
			return NULL;

		if(name[0]==0) 
			return NULL;

		if(m_list.empty())
			return NULL;

		RAnimation* pAni = NULL;

		if(wtype != -1)
			pAni = GetAnimationListMap(name,wtype);

		if(pAni) {
			return pAni;
		}

		pAni = m_list.Find(name);
		return pAni;
	}

Replace <br>

	RAnimation* RAnimationMgr::GetAnimationListMap(const char* name,int wtype) {

		if(m_list_map_size==0) return NULL;

		if(m_list_map_size-1 < wtype) {
			return NULL;
		}

		RAnimation* pAni = m_list_map[wtype].Find(name);

		return pAni;
	}

	RAnimation* RAnimationMgr::GetAnimation(const char* name,int wtype) 
	{
		if(!name) 
			return NULL;

		if(name[0]==0) 
			return NULL;

		if(m_list.empty())
			return NULL;

		RAnimation* pAni = NULL;

		if(wtype != -1)
			pAni = GetAnimationListMap(name,wtype);

		if(pAni) {
			return pAni;
		}

		pAni = m_list.Find(name);
		return pAni;
	}

Find <br>

	void RAnimationMgr::ReloadAll()
	{
		RAnimationHashList_Iter node;
		RAnimation* pANode = NULL;

		for(node = m_list.begin(); node != m_list.end(); ++node) {
			pANode = *node;
			if(pANode) {
				if(pANode->IsLoadDone()==false) {
					if (!pANode->LoadAni(pANode->m_filename)) {
						mlog("elu %s file loading failure !!!\n",pANode->m_filename);
					}
					pANode->SetLoadDone(true);
				}
			}
		}
	}

Replace <br>

	void RAnimationMgr::ReloadAll()
	{
		RAnimationHashList_Iter node;
		RAnimation* pANode = NULL;

		for(node = m_list.begin(); node != m_list.end(); ++node)
		{
			if (*node == nullptr)
			{
				mlog("Error, node is nullptr, skip\n");
				continue;
			}
			pANode = *node;
			if(pANode) {
				if(pANode->IsLoadDone()==false) {
					if (!pANode->LoadAni(pANode->m_filename)) {
						mlog("elu %s file loading failure !!!\n",pANode->m_filename);
					}
					pANode->SetLoadDone(true);
				}
			}
		}
	}

Open(ZBrain.cpp) <br>
Find <br>

	// Use default attack
	if ( bDefaultAttackEnabled && m_pBody->CanAttackMelee( GetTarget()) && !ZGetGame()->CheckWall(m_pBody, GetTarget(), true))
	{	// (½ÇÁ¦ ±ÙÁ¢Å¸°Ý ÆÇÁ¤ÇÒ¶§ º®Ã¼Å©ÇÏ´Â ÇÔ¼ö) CheckWall·Î Å¸°Ù°ú ³ª »çÀÌ¿¡ Àå¾Ö¹°ÀÌ ¾ø´ÂÁö È®ÀÎ- ¾È±×·¯¸é ±âµÕ µÚ¿¡¼­ °è¼Ó Çê¹æÄ£´Ù

		float fNextCoolTime = MakeDefaultAttackCoolTime();
		m_DefaultAttackTimer.Init( fNextCoolTime);

		ZTask* pNew = ZTaskManager::CreateAttackMelee( m_pBody);
		m_pBody->m_TaskManager.PushFront( pNew);

		return;
	}

Replace <br>

	// Use default attack
	if ( bDefaultAttackEnabled && m_pBody->CanAttackMelee( GetTarget()) && !ZGetGame()->IsWallBlocked(m_pBody, GetTarget(), true))
	{	// (½ÇÁ¦ ±ÙÁ¢Å¸°Ý ÆÇÁ¤ÇÒ¶§ º®Ã¼Å©ÇÏ´Â ÇÔ¼ö) CheckWall·Î Å¸°Ù°ú ³ª »çÀÌ¿¡ Àå¾Ö¹°ÀÌ ¾ø´ÂÁö È®ÀÎ- ¾È±×·¯¸é ±âµÕ µÚ¿¡¼­ °è¼Ó Çê¹æÄ£´Ù

		float fNextCoolTime = m_pBody->MakeDefaultAttackCoolTime();
		m_DefaultAttackTimer.Init( fNextCoolTime);

		ZTask* pNew = ZTaskManager::CreateAttackMelee( m_pBody);
		m_pBody->GetTaskManager()->PushFront( pNew);

		return;
	}


Open(ZActor.cpp) <br>
Find <br>

	void ZActor::OnNeglect( int nNum)
	{
		if ( nNum == 1)
			m_Animation.Input( ZA_EVENT_NEGLECT1);
		else if ( nNum == 2)
			m_Animation.Input( ZA_EVENT_NEGLECT2);
	}

Add <br>

	float ZActor::MakeSpeed( float fSpeed)
	{
		MQuestNPCGlobalAIValue* pGlobalAIValue = ZGetQuest()->GetNPCCatalogue()->GetGlobalAIValue();
		float fShakingRatio = pGlobalAIValue->m_fSpeed_ShakingRatio;
		float fExtraValue = fSpeed * fShakingRatio;
		float fMinSpeed = max( (fSpeed - fExtraValue), 0.0f);
		float fMaxSpeed = fSpeed + fExtraValue;

		return RandomNumber( fMinSpeed, fMaxSpeed);
	}


	float ZActor::MakePathFindingUpdateTime( char nIntelligence)
	{
		MQuestNPCGlobalAIValue* pGlobalAIValue = ZGetQuest()->GetNPCCatalogue()->GetGlobalAIValue();
		float fShakingRatio = pGlobalAIValue->m_fPathFinding_ShakingRatio;
		float fTime = pGlobalAIValue->m_fPathFindingUpdateTime[ nIntelligence - 1];
		float fExtraValue = fTime * fShakingRatio;
		float fMinTime = fTime - fExtraValue;
		if ( fMinTime < 0.0f)
			fMinTime = 0.0f;
		float fMaxTime = fTime + fExtraValue;

		return RandomNumber( fMinTime, fMaxTime);
	}

	float ZActor::MakeAttackUpdateTime( char nAgility)
	{
		MQuestNPCGlobalAIValue* pGlobalAIValue = ZGetQuest()->GetNPCCatalogue()->GetGlobalAIValue();
		float fShakingRatio = pGlobalAIValue->m_fAttack_ShakingRatio;
		float fTime = pGlobalAIValue->m_fAttackUpdateTime[ nAgility - 1];
		float fExtraValue = fTime * fShakingRatio;
		float fMinTime = fTime - fExtraValue;
		if ( fMinTime < 0.0f)
			fMinTime = 0.0f;
		float fMaxTime = fTime + fExtraValue;

		return RandomNumber( fMinTime, fMaxTime);
	}


	float ZActor::MakeDefaultAttackCoolTime()
	{
		if ( !m_pNPCInfo)
			return 0.0f;

		float fShakingRatio = 0.3f;
		float fCoolTime = m_pNPCInfo->fAttackCoolTime;
		float fExtraValue = fCoolTime * fShakingRatio;
		float fMinCoolTime = max( (fCoolTime - fExtraValue), 0.01f);
		float fMaxCoolTime = fCoolTime + fExtraValue;

		return RandomNumber( fMinCoolTime, fMaxCoolTime);
	}


	void ZActor::ShockBossGauge( float fDamage )
	{
		ZGetScreenEffectManager()->ShockBossGauge(fDamage);
	}

	void ZActor::LinkAniEventSet( MQUEST_NPC nNPCType )
	{
		//¾Ö´Ï¸ÞÀÌ¼Ç ÀÌº¥Æ® ¸Å´ÏÀú¿¡¼­ ÇØ´ç npc¿¡ ¸Â´Â ÀÌº¥Æ® ºÒ·¯¿À±â
		RAniIDEventSet* pAniIdEventSet = ZGetAniEventMgr()->GetAniIDEventSet((int)nNPCType);
		//ºñÁê¾ó ¸Þ½¬¿¡ ÇØ´ç ÀÌº¥Æ® ¼Â ¿¬°áÇÏ±â
		m_pVMesh->GetFrameInfo(RAniMode(0))->SetAniIdEventSet(pAniIdEventSet);
	}

	void ZActor::AddLandingEffect( rvector vPos, rvector vDir )
	{
		ZGetEffectManager()->AddLandingEffect(vPos,vDir);//³»ºÎ¿¡¼­ ¿É¼Ç¿¡ µû¶ó~
	}

	const MTD_NPCINFO* ZActor::GetMyActorServerNPCInfo( const MQUEST_NPC nNPCID )
	{
		if (!ZGetQuest()) return NULL;
		return ZGetQuest()->GetNPCInfoFromServerMgr().GetNPCInfo( nNPCID );
	}

	bool ZActor::GetQuestCheat( ZQuestCheetType cheat )
	{
	//#ifdef _DEBUG
	//	return (ZGetQuest()->GetCheet(cheat) == true);
	//#endif
		return false;
	}

	int ZActor::GetActualHP()
	{
		return (int)((float)m_pModule_HPAP->GetHP() * m_fTC);
	}

	int ZActor::GetActualAP()
	{
		return (int)((float)m_pModule_HPAP->GetAP() * m_fTC);
	}

	int ZActor::GetActualMaxHP()
	{
		const MTD_NPCINFO* pSvrQuestNPCInfo = GetMyActorServerNPCInfo( m_pNPCInfo->nID );
		if( NULL == pSvrQuestNPCInfo )
		{
			return 0;
		}

		//return (int)((float)pSvrQuestNPCInfo->m_nMaxHP * m_fTC); // ³­ÀÌµµ Á¶Àý °è¼ö(m_fTC)·Î ÀÎÇØ MaxHP°¡ º¯°æ ¾ÈµÈ »óÅÂ
		// ³­ÀÌµµ Á¶Àý °è¼ö(m_fTC)·Î ÀÎÇØ ÀÌ¹Ì MaxHP°¡ º¯°æµÈ »óÅÂ·Î Ã³¸®ÇØ¾ß °ÔÀÌÁö ¹Ù°¡ Á¦´ë·Î Ãâ·ÂµÈ´Ù.
		return (int)((float)m_pModule_HPAP->GetMaxHP() * m_fTC);
	}

	int ZActor::GetActualMaxAP()
	{
		const MTD_NPCINFO* pSvrQuestNPCInfo = GetMyActorServerNPCInfo( m_pNPCInfo->nID );
		if( NULL == pSvrQuestNPCInfo )
		{
			return 0;
		}

		//return (int)((float)pSvrQuestNPCInfo->m_nMaxAP * m_fTC); // ³­ÀÌµµ Á¶Àý °è¼ö(m_fTC)·Î ÀÎÇØ MaxAP°¡ º¯°æ ¾ÈµÈ »óÅÂ
		// ³­ÀÌµµ Á¶Àý °è¼ö(m_fTC)·Î ÀÎÇØ ÀÌ¹Ì MaxAP°¡ º¯°æµÈ »óÅÂ·Î Ã³¸®ÇØ¾ß °ÔÀÌÁö ¹Ù°¡ Á¦´ë·Î Ãâ·ÂµÈ´Ù.
		return (int)((float)m_pModule_HPAP->GetMaxAP() * m_fTC);
	}

	void ZActor::GetDebugInfoString(char* szBuf1, char* szBuf2, int index)
	{
	#ifndef _PUBLISH
		rvector pos = GetPosition();
		rvector dir = GetDirection();
		rvector vel = GetVelocity();

		MQuestNPCInfo* pNPCInfo = GetNPCInfo();
		int nTaskCount = GetTaskManager()->GetCount();
		ZTask* pCurrTask = GetTaskManager()->GetCurrTask();
		char szTaskName[256] = "None";
		if (pCurrTask)
		{
			strcpy(szTaskName, pCurrTask->GetTaskName());
		}

		sprintf(szBuf1, "[%02d], %s, HP(%02d)AP(%2d) pos(%.2f %.2f %.2f), dir(%.2f %.2f %.2f), vel(%.2f %.2f %.2f), Task: %d, CurrTask: %s",
			index, pNPCInfo->szName, 
			GetHP(), GetAP(),
			pos.x, pos.y, pos.z, dir.x, dir.y, dir.z, vel.x, vel.y, vel.z,
			nTaskCount, szTaskName);

		char szFlagLand[8] = "¡Û";
		char szFlagBlast[8] = "¡Û";
		char szFlagBlastDagger[8] = "¡Û";
		char szFlagMoving[8] = "¡Û";
		char szFlagDead[8] = "¡Û";
		char szFlagRequestedDead[8] = "¡Û";
		char szFlagMyControl[8] = "¡Û";

		if (CheckFlag(AF_LAND)) strcpy(szFlagLand, "¡Ü");
		if (CheckFlag(AF_BLAST)) strcpy(szFlagBlast, "¡Ü");
		if (CheckFlag(AF_BLAST_DAGGER)) strcpy(szFlagBlastDagger, "¡Ü");
		if (CheckFlag(AF_MOVING)) strcpy(szFlagMoving, "¡Ü");
		if (CheckFlag(AF_DEAD)) strcpy(szFlagDead, "¡Ü");
		if (CheckFlag(AF_REQUESTED_DEAD)) strcpy(szFlagRequestedDead, "¡Ü");
		if (CheckFlag(AF_MY_CONTROL)) strcpy(szFlagMyControl, "¡Ü");

		sprintf(szBuf2, "     LAND(%s), BLAST(%s), BLASTDAGGER(%s), MOVING(%s), DEAD(%s), REQUESTED_DEAD(%s), MY_CONTROL(%s), DistFloor(%.2f)",
			szFlagLand, szFlagBlast, szFlagBlastDagger ,szFlagMoving, szFlagDead, szFlagRequestedDead, szFlagMyControl, GetDistToFloor());
	#endif
	}

Open(ZActor.h) <br>
Find <br>




Add <br>

		// ¿ÜºÎ°´Ã¼¿¡ ÀÇÁ¸ÇÏ°í ÀÖ´Â ÄÚµå¸¦ °¡»óÇÔ¼ö·Î °¨½Î¼­ testableÇÏµµ·Ï ¸¸µë
	protected:
		virtual MQuestNPCInfo* GetQuestNPCInfo(MQUEST_NPC nNPCType) { return ZGetQuest()->GetNPCInfo(nNPCType); }
		virtual MUID GetQuestBossUid() { return ZGetQuest()->GetGameInfo()->GetBoss(); }
		virtual bool GetQuestCheat(ZQuestCheetType cheat);
		virtual const MTD_NPCINFO* GetMyActorServerNPCInfo( const MQUEST_NPC nNPCID );
		virtual void AddLandingEffect(rvector vPos, rvector vDir);
		virtual void ShockBossGauge(float fDamage);
		virtual void LinkAniEventSet(MQUEST_NPC nNPCType);
		virtual float MakeSpeed( float fSpeed);

	public:
		virtual float MakePathFindingUpdateTime( char nIntelligence);
		virtual float MakeAttackUpdateTime( char nAgility);
		virtual float MakeDefaultAttackCoolTime();

		virtual void GetDebugInfoString(char* szBuf1, char* szBuf2, int index);
	};

Find <br>

	public:
		ZActor();
		virtual ~ZActor();
		static ZActor* CreateActor(MQUEST_NPC nNPCType, float fTC, int nQL, bool bForceCollRadius35=false);
		void InputBasicInfo(ZBasicInfo* pni, BYTE anistate);
		void InputBossHpAp(float fHp, float fAp);
		void Input(AI_INPUT_SET nInput);
		void DebugTest();
		void SetMyControl(bool bMyControl);

		inline ZA_ANIM_STATE	GetCurrAni();
		inline void SetFlag(unsigned int nFlag, bool bValue);
		inline bool CheckFlag(unsigned int nFlag);
		inline void SetFlags(unsigned int nFlags);
		inline unsigned long GetFlags();
		inline bool IsMyControl();
		inline int GetHP();
		inline int GetAP();
		inline float GetTC();
		inline int GetQL();
		inline float GetHitRate();
		inline int GetActualHP();
		inline int GetActualAP();
		inline int GetActualMaxHP();
		inline int GetActualMaxAP();
	public:

Replace <br>

	public:
		ZActor();
		virtual ~ZActor();
		static ZActor* CreateActor(MQUEST_NPC nNPCType, float fTC, int nQL, bool bForceCollRadius35);
		virtual void InputBasicInfo(ZBasicInfo* pni, BYTE anistate);
		virtual void InputBossHpAp(float fHp, float fAp);
		void Input(AI_INPUT_SET nInput);
		void DebugTest();
		virtual void SetMyControl(bool bMyControl);

		inline ZA_ANIM_STATE	GetCurrAni();
		inline void SetFlag(unsigned int nFlag, bool bValue);
		inline bool CheckFlag(unsigned int nFlag);
		inline void SetFlags(unsigned int nFlags);
		inline unsigned long GetFlags();
		virtual bool IsMyControl() { return CheckFlag(AF_MY_CONTROL); }
		inline int GetHP();
		inline int GetAP();
		inline float GetTC();
		inline int GetQL();
		inline float GetHitRate();
		virtual int GetActualHP();
		virtual int GetActualAP();
		virtual int GetActualMaxHP();
		virtual int GetActualMaxAP();
		virtual bool IsNeverPushed() { if (m_pNPCInfo) return m_pNPCInfo->bNeverPushed; return false; }
		virtual float GetCollideRadius() { if (m_pNPCInfo) return m_pNPCInfo->fCollRadius; return 0;}
		virtual float ModifyAttackDamage(float fDamage)
		{
			return fDamage * (GetQL() * 0.2f + 1);
		}
	public:

Find <br>

	inline bool ZActor::IsMyControl()
	{
		return CheckFlag(AF_MY_CONTROL);
	}

	inline int ZActor::GetActualHP()
	{
		return (int)((float)m_pModule_HPAP->GetHP() * m_fTC);
	}

	inline int ZActor::GetActualAP()
	{
		return (int)((float)m_pModule_HPAP->GetAP() * m_fTC);
	}

	inline int ZActor::GetActualMaxHP()
	{
		const MTD_NPCINFO* pSvrQuestNPCInfo = GetMyActorServerNPCInfo( m_pNPCInfo->nID );
		if( NULL == pSvrQuestNPCInfo )
		{
			return 0;
		}

		//return (int)((float)pSvrQuestNPCInfo->m_nMaxHP * m_fTC); // ³­ÀÌµµ Á¶Àý °è¼ö(m_fTC)·Î ÀÎÇØ MaxHP°¡ º¯°æ ¾ÈµÈ »óÅÂ
		// ³­ÀÌµµ Á¶Àý °è¼ö(m_fTC)·Î ÀÎÇØ ÀÌ¹Ì MaxHP°¡ º¯°æµÈ »óÅÂ·Î Ã³¸®ÇØ¾ß °ÔÀÌÁö ¹Ù°¡ Á¦´ë·Î Ãâ·ÂµÈ´Ù.
		return (int)((float)m_pModule_HPAP->GetMaxHP() * m_fTC);
	}

	inline int ZActor::GetActualMaxAP()
	{
		const MTD_NPCINFO* pSvrQuestNPCInfo = GetMyActorServerNPCInfo( m_pNPCInfo->nID );
		if( NULL == pSvrQuestNPCInfo )
		{
			return 0;
		}

		//return (int)((float)pSvrQuestNPCInfo->m_nMaxAP * m_fTC); // ³­ÀÌµµ Á¶Àý °è¼ö(m_fTC)·Î ÀÎÇØ MaxAP°¡ º¯°æ ¾ÈµÈ »óÅÂ
		// ³­ÀÌµµ Á¶Àý °è¼ö(m_fTC)·Î ÀÎÇØ ÀÌ¹Ì MaxAP°¡ º¯°æµÈ »óÅÂ·Î Ã³¸®ÇØ¾ß °ÔÀÌÁö ¹Ù°¡ Á¦´ë·Î Ãâ·ÂµÈ´Ù.
		return (int)((float)m_pModule_HPAP->GetMaxAP() * m_fTC);
	}

Replace <br>

	/*
	inline bool ZActor::IsMyControl()
	{
		return CheckFlag(AF_MY_CONTROL);
	}

	inline int ZActor::GetActualHP()
	{
		return (int)((float)m_pModule_HPAP->GetHP() * m_fTC);
	}

	inline int ZActor::GetActualAP()
	{
		return (int)((float)m_pModule_HPAP->GetAP() * m_fTC);
	}

	inline int ZActor::GetActualMaxHP()
	{
		const MTD_NPCINFO* pSvrQuestNPCInfo = GetMyActorServerNPCInfo( m_pNPCInfo->nID );
		if( NULL == pSvrQuestNPCInfo )
		{
			return 0;
		}

		//return (int)((float)pSvrQuestNPCInfo->m_nMaxHP * m_fTC); // ³­ÀÌµµ Á¶Àý °è¼ö(m_fTC)·Î ÀÎÇØ MaxHP°¡ º¯°æ ¾ÈµÈ »óÅÂ
		// ³­ÀÌµµ Á¶Àý °è¼ö(m_fTC)·Î ÀÎÇØ ÀÌ¹Ì MaxHP°¡ º¯°æµÈ »óÅÂ·Î Ã³¸®ÇØ¾ß °ÔÀÌÁö ¹Ù°¡ Á¦´ë·Î Ãâ·ÂµÈ´Ù.
		return (int)((float)m_pModule_HPAP->GetMaxHP() * m_fTC);
	}

	inline int ZActor::GetActualMaxAP()
	{
		const MTD_NPCINFO* pSvrQuestNPCInfo = GetMyActorServerNPCInfo( m_pNPCInfo->nID );
		if( NULL == pSvrQuestNPCInfo )
		{
			return 0;
		}

		//return (int)((float)pSvrQuestNPCInfo->m_nMaxAP * m_fTC); // ³­ÀÌµµ Á¶Àý °è¼ö(m_fTC)·Î ÀÎÇØ MaxAP°¡ º¯°æ ¾ÈµÈ »óÅÂ
		// ³­ÀÌµµ Á¶Àý °è¼ö(m_fTC)·Î ÀÎÇØ ÀÌ¹Ì MaxAP°¡ º¯°æµÈ »óÅÂ·Î Ã³¸®ÇØ¾ß °ÔÀÌÁö ¹Ù°¡ Á¦´ë·Î Ãâ·ÂµÈ´Ù.
		return (int)((float)m_pModule_HPAP->GetMaxAP() * m_fTC);
	}*/


Open(ZCharacter.h) <br>
Find <br>

	void ZChangeCharParts(RVisualMesh* pVMesh, MMatchSex nSex, int nHair, int nFace, const unsigned long int* pItemID);
	void ZChangeCharWeaponMesh(RVisualMesh* pVMesh, unsigned long int nWeaponID);
	bool CheckTeenVersionMesh(RMesh** ppMesh);

Replace <br>

	void ZChangeCharParts(ZObjectVMesh* pVMesh, MMatchSex nSex, int nHair, int nFace, const unsigned long int* pItemID);
	void ZChangeCharWeaponMesh(ZObjectVMesh* pVMesh, unsigned long int nWeaponID);
	bool CheckTeenVersionMesh(RMesh** ppMesh);

Open(ZCharacter.cpp) <br>
Find <br>

	void ChangeCharHair(RVisualMesh* pVMesh, MMatchSex nSex, int nHairIndex)
	{

	void ChangeEquipAvatarParts(RVisualMesh* pVMesh, const unsigned long int* pItemID, MMatchSex nSex, int nHairIndex)
	{

	void ChangeEquipParts(RVisualMesh* pVMesh, const unsigned long int* pItemID)
	{


	void ChangeCharFace(ZObjectVMesh* pVMesh, MMatchSex nSex, int nFaceIndex)
	{


	void ZChangeCharParts(RVisualMesh* pVMesh, MMatchSex nSex, int nHair, int nFace, const unsigned long int* pItemID)
	{

	void ZChangeCharWeaponMesh(RVisualMesh* pVMesh, unsigned long int nWeaponID)
	{


Replace <br>

	void ChangeCharHair(ZObjectVMesh* pVMesh, MMatchSex nSex, int nHairIndex)
	{

	void ChangeEquipAvatarParts(ZObjectVMesh* pVMesh, const unsigned long int* pItemID, MMatchSex nSex, int nHairIndex)
	{

	void ChangeEquipParts(ZObjectVMesh* pVMesh, const unsigned long int* pItemID)
	{

	void ChangeCharFace(ZObjectVMesh* pVMesh, MMatchSex nSex, int nFaceIndex)
	{

	void ZChangeCharParts(ZObjectVMesh* pVMesh, MMatchSex nSex, int nHair, int nFace, const unsigned long int* pItemID)
	{

	void ZChangeCharWeaponMesh(ZObjectVMesh* pVMesh, unsigned long int nWeaponID)
	{


Open(ZActor.cpp) <br>
Find <br>

	void ZActor::InitMesh(char* szMeshName, MQUEST_NPC nNPCType)
	{
		// for test
		RMesh* pMesh;

		pMesh = ZGetNpcMeshMgr()->Get(szMeshName);//¿øÇÏ´Â ¸ðµ¨À» ºÙ¿©ÁÖ±â..
		if(!pMesh) 
		{
			_ASSERT(0);
			mlog("ZActor::InitMesh() -  ¿øÇÏ´Â ¸ðµ¨À» Ã£À»¼ö ¾øÀ½\n");
			return;
		}

		int nVMID = ZGetGame()->m_VisualMeshMgr.Add(pMesh);
		if(nVMID==-1) mlog("ZActor::InitMesh() - Ä³¸¯ÅÍ »ý¼º ½ÇÆÐ\n");

		RVisualMesh* pVMesh = ZGetGame()->m_VisualMeshMgr.GetFast(nVMID);

		SetVisualMesh(pVMesh);

		pVMesh->SetScale(rvector(15,15,15));

		m_Animation.Set(ZA_ANIM_RUN);

		//¾Ö´Ï¸ÞÀÌ¼Ç ÀÌº¥Æ® ¸Å´ÏÀú¿¡¼­ ÇØ´ç npc¿¡ ¸Â´Â ÀÌº¥Æ® ºÒ·¯¿À±â
		RAniIDEventSet* pAniIdEventSet = ZGetAniEventMgr()->GetAniIDEventSet((int)nNPCType);
		//ºñÁê¾ó ¸Þ½¬¿¡ ÇØ´ç ÀÌº¥Æ® ¼Â ¿¬°áÇÏ±â
		pVMesh->m_FrameInfo[0].SetAniIdEventSet(pAniIdEventSet);
	}

Replace <br>

	void ZActor::InitMesh(char* szMeshName, MQUEST_NPC nNPCType)
	{
		_ASSERT(m_pVMesh == NULL);
		AllocObjectVMesh();
		m_pVMesh->InitNpcMesh(this, szMeshName);

		m_pVMesh->SetScale(rvector(15,15,15));

		m_Animation.Set(ZA_ANIM_RUN);

		LinkAniEventSet(nNPCType);
	}

Open(ZActor.h) <br>
Find <br>

	#include "MMatchTransDataType.h"
	#include "ZNPCInfoFromServer.h"
	
Replace <br>

	#include "ZActorBase.h"

Find <br>

	class ZActor : public ZCharacterObject
	{


Replace <br>

	class ZActor : public ZActorBase
	{

Open(ZGameInterface.cpp) <br>
Find <br>

	void ZGameInterface::TestChangeWeapon(ZObjectVMesh* pVMesh)
	{

Replace <br>

	void ZGameInterface::TestChangeWeapon(RVisualMesh* pVMesh)
	{


Open(ZGameInterface.h) <br>
Find <br>

	void TestChangeWeapon(RVisualMesh* pVMesh = NULL);

Replace <br>

	void TestChangeWeapon(ZObjectVMesh* pVMesh = NULL);

Open(ZMeshView.h) <br>
Find <br>

	RTVisualMesh() {
		m_pVisualMesh = new RVisualMesh;
		bInit = false;
	}

Replace <br>

	RTVisualMesh() {
		m_pVisualMesh = new ZObjectVMesh;
		m_pVisualMesh->InitOwnVMesh();
		bInit = true;
	}

Find <br>

	bool bInit;
	RVisualMesh* GetVMesh(bool b=true);
	RVisualMesh* m_pVisualMesh;

Replace <br>

	bool bInit;
	ZObjectVMesh* GetVMesh(bool b=true);
	ZObjectVMesh* m_pVisualMesh;

Find <br>

	//	void SetMesh(RVisualMesh* pVisualMesh);
		void SetLight(rvector LPos);

	void SetEnableRotateZoom(bool bEnableRotate, bool bEnableZoom);

	RVisualMesh* GetVisualMesh() { 
		return m_pTVisualMesh.GetVMesh();

Replace <br>

	//	void SetMesh(ZObjectVMesh* pVisualMesh);
		void SetLight(rvector LPos);

		void SetEnableRotateZoom(bool bEnableRotate, bool bEnableZoom);

		ZObjectVMesh* GetVisualMesh() { 
			return m_pTVisualMesh.GetVMesh(); 


Open(ZCharacterSelectView.h) <br>
Find <br>

	RVisualMesh*			m_pVisualMesh;

Replace <br>

	ZObjectVMesh*			m_pVisualMesh;


Open(ZCharacterSelectView.cpp) <br>
Find <br>

	//m_pMesh = new RMesh;
	m_pVisualMesh = new RVisualMesh;

Replace <br>

	//m_pMesh = new RMesh;
	m_pVisualMesh = new ZObjectVMesh;

Open(RMeshUtil.h) <br>
Find <br>

	T Find(char *name) {

Replace <br>

	T Find(const char* name) {

Open(ZActor.cpp) <br>
Find <br>

	MImplementRTTI(ZActor, ZCharacterObject);

	///////////////////////////////////////////////////////////////////////
	ZActor::ZActor() : ZCharacterObject(), m_nFlags(0), m_nNPCType(NPC_GOBLIN_KING), m_pNPCInfo(NULL), m_pModule_Skills(NULL), m_fSpeed(0.0f), m_pBrain(NULL)
	{

Replace <br>

	MImplementRTTI(ZActor, ZActorBase);

	///////////////////////////////////////////////////////////////////////
	ZActor::ZActor() 
	: ZActorBase()
	, m_nFlags(0)
	, m_pNPCInfo(NULL)
	, m_pModule_Skills(NULL), m_fSpeed(0.0f), m_pBrain(NULL)
	{

Open(ZQuest.cpp) <br>
Find <br>

	float fTC = m_GameInfo.GetNPC_TC();
	ZActor* pNewActor = ZActor::CreateActor(NPCType, fTC, m_GameInfo.GetQuestLevel());
	if (pNewActor)

Replace <br>

	float fTC = m_GameInfo.GetNPC_TC();
	ZActorBase* pNewActor = ZActor::CreateActor(NPCType, fTC, m_GameInfo.GetQuestLevel(), false);
	if (pNewActor)

Open(ZGameInput_Debug.cpp) <br>
Find <br>

						if(ZGetQuest())
							pNPCInfo = 	ZGetQuest()->GetNPCInfo(MQUEST_NPC(nNPCType));

						ZActor* pNewActor = ZActor::CreateActor(MQUEST_NPC(nNPCType), 1.0f, 0);
						if (pNewActor)


Replace <br>

						if(ZGetQuest())
							pNPCInfo = 	ZGetQuest()->GetNPCInfo(MQUEST_NPC(nNPCType));

						ZActor* pNewActor = ZActor::CreateActor(MQUEST_NPC(nNPCType), 1.0f, 0, false);
						if (pNewActor)


Open(ZGame.cpp) <br>
Find <br>

	bool ZGame::CheckWall(ZObject* pObj1,ZObject* pObj2, bool bCoherentToPeer)
	{


Replace <br>

	/*
	bool ZGame::CheckWall(ZObject* pObj1,ZObject* pObj2, bool bCoherentToPeer)
	{	// ÇÇ¾î³¢¸® ÁÂÇ¥¸¦ º¸³¾¶§ ÇöÀç´Â float->short Ä³½ºÆÃÀÌ ÀÏ¾î³­´Ù (Áï ¼Ò¼öÁ¡ÀÌÇÏ ¹ö¸²)
		// µû¶ó¼­ Å¬¶óÀÌ¾ðÆ®µéÀÌ °¢ÀÚ ÆÇÁ¤ÇÑ °ªÀÌ ¹Ì¹¦ÇÏ°Ô ´Ù¸¦ ¼ö°¡ ÀÖ´Ù. ÀÌ°ÍÀÌ ±âÁ¸¿¡ ¹®Á¦¸¦ ÀÏÀ¸Å°Áø ¾Ê¾ÒÀ¸³ª
		// ¼­¹ÙÀÌ¹ú¿¡¼­ ³·Àº È®·ü·Î ¹®Á¦°¡ ¹ß»ý: npc°¡ ÇÃ·¹ÀÌ¾î¸¦ ±ÙÁ¢°ø°ÝÇÏ·Á°í ÇÒ¶§, npc ÄÁÆ®·Ñ·¯´Â °ø°Ý °¡´ÉÇÏ´Ù°í ÆÇÁ¤.
		// ÇÇ°Ý´çÇÏ´Â Å¬¶óÀÌ¾ðÆ®´Â °ø°Ý °¡´ÉÇÏÁö ¾Ê´Ù°í ÆÇÁ¤. ÀÌ·Î½á ÇÇ°ÝµÇ´Â À¯Àú°¡ À§Ä¡¸¦ ¹Ù²ÙÁö ¾Ê´ÂÇÑ ¸ó½ºÅÍ´Â Á¦ÀÚ¸®¿¡¼­ ¹«ÇÑ Çê¹æÀ» Ä¡°ÔµÊ (¼Ö±î¸» ¾Ç¿ë ºÒ°¡¶ó°í »ý°¢ÇÏÁö¸¸ ÆÛºí¸®¼ÅÀÇ ±Ù¼º¿¡ Á³À½)
		// bCoherentToPeer==true ÀÏ¶§ ÇÇ¾î¿¡°Ô º¸³½ °Í°ú °°Àº °ªÀ» »ç¿ëÇÔ..

		if( (pObj1==NULL) || (pObj2==NULL) )
			return false;

		if( (pObj1->GetVisualMesh()==NULL) || (pObj2->GetVisualMesh()==NULL) )
			return false;

		// ¿¡´Ï¸ÞÀÌ¼Ç ¶§¹®¿¡ º®À» ¶Õ°í µé¾î°¡´Â °æ¿ìµµ ÀÖ¾î¼­..
		rvector p1 = pObj1->GetPosition() + rvector(0.f,0.f,100.f);
		rvector p2 = pObj2->GetPosition() + rvector(0.f,0.f,100.f);

		if (bCoherentToPeer)
		{
			p1.x = short(p1.x);
			p1.y = short(p1.y);
			p1.z = short(p1.z);
			p2.x = short(p2.x);
			p2.y = short(p2.y);
			p2.z = short(p2.z);
			// ¿ÀÂ÷·Î ÀÎÇÑ ¹ö±× ÀçÇö Å×½ºÆ®¸¦ ½±°Ô ÇÏ±â À§ÇØ 1ÀÇ ÀÚ¸®±îÁö Àý»çÇÑ ¹öÀü
			/*p1.x = (short(p1.x * 0.1f)) * 10.f;
			p1.y = (short(p1.y * 0.1f)) * 10.f;
			p1.z = (short(p1.z * 0.1f)) * 10.f;
			p2.x = (short(p2.x * 0.1f)) * 10.f;
			p2.y = (short(p2.y * 0.1f)) * 10.f;
			p2.z = (short(p2.z * 0.1f)) * 10.f;
		}

		rvector dir = p2 - p1;

		Normalize(dir);

		ZPICKINFO pickinfo;

		if( Pick( pObj1 , p1 , dir, &pickinfo ) ) {//º®ÀÌ¶ó¸é
			if(pickinfo.bBspPicked)//¸ÊÀÌ °É¸°°æ¿ì
				return true;
		}

		return false;
	}
	//jintriple3 µð¹ö±× ·¹Áö½ºÅÍ ÇØÅ·.....ºñ±³¸¦ À§ÇØ¼­
	bool ZGame::CheckWall(ZObject* pObj1,ZObject* pObj2, int & nDebugRegister/*´Ü¼ø ºñ±³¿ë, bool bCoherentToPeer)
	{	//bCoherentToPeer¿¡ ´ëÇÑ°ÍÀº ¿øº» CheckWall ÁÖ¼® Âü°í

		if( (pObj1==NULL) || (pObj2==NULL) )
		{
			nDebugRegister = -10;	//¿ª½Ã³ª ¼ýÀÚ´Â ÀÇ¹Ì°¡ ¾ø´Ù..
			return false;
		}

		if( (pObj1->GetVisualMesh()==NULL) || (pObj2->GetVisualMesh()==NULL) )
		{
			nDebugRegister = -10;
			return false;
		}

		// ¿¡´Ï¸ÞÀÌ¼Ç ¶§¹®¿¡ º®À» ¶Õ°í µé¾î°¡´Â °æ¿ìµµ ÀÖ¾î¼­..
		rvector p1 = pObj1->GetPosition() + rvector(0.f,0.f,100.f);
		rvector p2 = pObj2->GetPosition() + rvector(0.f,0.f,100.f);

		if (bCoherentToPeer)
		{
			p1.x = short(p1.x);
			p1.y = short(p1.y);
			p1.z = short(p1.z);
			p2.x = short(p2.x);
			p2.y = short(p2.y);
			p2.z = short(p2.z);
			// ¿ÀÂ÷·Î ÀÎÇÑ ¹ö±× ÀçÇö Å×½ºÆ®¸¦ ½±°Ô ÇÏ±â À§ÇØ 1ÀÇ ÀÚ¸®±îÁö Àý»çÇÑ ¹öÀü
			/*p1.x = (short(p1.x * 0.1f)) * 10.f;
			p1.y = (short(p1.y * 0.1f)) * 10.f;
			p1.z = (short(p1.z * 0.1f)) * 10.f;
			p2.x = (short(p2.x * 0.1f)) * 10.f;
			p2.y = (short(p2.y * 0.1f)) * 10.f;
			p2.z = (short(p2.z * 0.1f)) * 10.f;
		}

		rvector dir = p2 - p1;

		Normalize(dir);

		ZPICKINFO pickinfo;

		if( Pick( pObj1 , p1 , dir, &pickinfo ) ) {//º®ÀÌ¶ó¸é
			if(pickinfo.bBspPicked)//¸ÊÀÌ °É¸°°æ¿ì
			{
				nDebugRegister = FOR_DEBUG_REGISTER;
				return true;
			}
		}
		nDebugRegister = -10;
		return false;
	}*/

Open(ZCharacter.cpp) <br>
Find <br>

	char* GetPartsNextName(RMeshPartsType ptype,RVisualMesh* pVMesh,bool bReverse)
	{

Replace <br>

	char* GetPartsNextName(RMeshPartsType ptype,ZObjectVMesh* pVMesh,bool bReverse)
	{

Find <br>

		pMesh = ZGetMeshMgr()->Get(szMeshName);//¿øÇÏ´Â ¸ðµ¨À» ºÙ¿©ÁÖ±â..

		if(!pMesh) {
			mlog("AddCharacter ¿øÇÏ´Â ¸ðµ¨À» Ã£À»¼ö ¾øÀ½\n");
		}

		int nVMID = ZGetGame()->m_VisualMeshMgr.Add(pMesh);

		if(nVMID==-1) {
			mlog("AddCharacter Ä³¸¯ÅÍ »ý¼º ½ÇÆÐ\n");
		}

		m_nVMID.Set_CheckCrc(nVMID);

		RVisualMesh* pVMesh = ZGetGame()->m_VisualMeshMgr.GetFast(nVMID);
		SetVisualMesh(pVMesh);

		// low polygon model ºÙ¿©ÁÖ±â..
		// ³²³à±¸ºÐ¾øÀÌ
	/*
		if (m_Property.nSex == MMS_MALE) {
			strcpy(szMeshName, "heroman_low1");
		}
		else {
			strcpy(szMeshName, "heroman_low2");
		}
	*/	
	}

Replace <br>


		_ASSERT(m_pVMesh==NULL);
		m_pVMesh = new ZObjectVMesh;
		int nVMID = m_pVMesh->InitCharacterMesh(this, szMeshName);

		m_nVMID.Set_CheckCrc(nVMID);
	}


Open(ZGameInterface.cpp) <br>
Find <br>

						if (ZGetCharacterViewList(GUNZ_LOBBY) != NULL)
						{
							RVisualMesh* pVMesh = 
								ZGetCharacterViewList(GUNZ_LOBBY)->Get(ZGetGameClient()->GetPlayerUID())->GetVisualMesh();

							TestChangeWeapon(pVMesh);
						}

Replace <br>

						if (ZGetCharacterViewList(GUNZ_LOBBY) != NULL)
						{
							ZObjectVMesh* pVMesh = 
								ZGetCharacterViewList(GUNZ_LOBBY)->Get(ZGetGameClient()->GetPlayerUID())->GetVisualMesh();

							TestChangeWeapon(pVMesh);
						}



Open(ZMeshView.cpp) <br>
Find <br>

	list<ZMeshView*> ZMeshView::msMeshViewList;

	RVisualMesh* RTVisualMesh::GetVMesh(bool b)
	{
		if(m_pVisualMesh->GetMesh()==NULL) {
			if( bInit == false ) {
				if(b) {
					mlog("RTVisualMesh::GetVMesh() ÃÊ±âÈ­ µÇÁö ¾ÊÀº »óÅÂ¿¡¼­ »ç¿ëÇÏ·Á ÇÑ´Ù.ÁÖÀÇ.\n");
				}
			}
		}
		return m_pVisualMesh;
	}

Replace <br>

	list<ZMeshView*> ZMeshView::msMeshViewList;

	ZObjectVMesh* RTVisualMesh::GetVMesh(bool b)
	{
		if(m_pVisualMesh->GetMesh()==NULL) {
			if( bInit == false ) {
				if(b) {
					mlog("RTVisualMesh::GetVMesh() ÃÊ±âÈ­ µÇÁö ¾ÊÀº »óÅÂ¿¡¼­ »ç¿ëÇÏ·Á ÇÑ´Ù.ÁÖÀÇ.\n");
				}
			}
		}
		return m_pVisualMesh;
	}

Open(ZCharacter.cpp) <br>
Find <br>

	pVMesh->SetParts(eq_parts_head, szMeshName);

Replace <br>

	pVMesh->SetParts(eq_parts_head, szMeshName,nullptr);

Find <br>

	void ChangeEquipAvatarParts(ZObjectVMesh* pVMesh, const unsigned long int* pItemID, MMatchSex nSex, int nHairIndex)
	{
		pVMesh->ClearParts();

		char* szMeshName;
		MMatchItemDesc* pDesc = MGetMatchItemDescMgr()->GetItemDesc(pItemID[MMCIP_AVATAR]);
		if( pDesc != NULL ) {
			szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szHeadMeshName;
			if( strlen(szMeshName) > 0 )	pVMesh->SetParts(eq_parts_head, szMeshName);
			else							ChangeCharHair(pVMesh, nSex, nHairIndex);

			szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szChestMeshName;
			if( strlen(szMeshName) > 0 )	pVMesh->SetParts(eq_parts_chest, szMeshName);
			else							pVMesh->SetBaseParts(eq_parts_chest);

			szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szHandMeshName;
			if( strlen(szMeshName) > 0 )	pVMesh->SetParts(eq_parts_hands, szMeshName);
			else							pVMesh->SetBaseParts(eq_parts_hands);

			szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szLegsMeshName;
			if( strlen(szMeshName) > 0 )	pVMesh->SetParts(eq_parts_legs, szMeshName);
			else							pVMesh->SetBaseParts(eq_parts_legs);

			szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szFeetMeshName;
			if( strlen(szMeshName) > 0 )	pVMesh->SetParts(eq_parts_feet, szMeshName);
			else							pVMesh->SetBaseParts(eq_parts_feet);
		}

		//pVMesh->SetBaseParts(eq_parts_face);
	}


Replace <br>

	void ChangeEquipAvatarParts(ZObjectVMesh* pVMesh, const unsigned long int* pItemID, MMatchSex nSex, int nHairIndex)
	{
		pVMesh->ClearParts();

		char* szMeshName;
		MMatchItemDesc* pDesc = MGetMatchItemDescMgr()->GetItemDesc(pItemID[MMCIP_AVATAR]);
		if( pDesc != NULL )
		{
			if (pDesc->GetEluName() != nullptr)
			{
				RMesh* playerMesh = nullptr;
				if (_stricmp(pVMesh->GetMesh()->GetName(), "heroman1") == 0)
				{
					playerMesh = ZGetMeshMgr()->Get("heroman1");
				}
				else
				{
					playerMesh = ZGetMeshMgr()->Get("herowoman1");
				}
				if (playerMesh->m_parts_mgr->Find(pDesc->m_szElu) == false)//Find(playerItem->m_szElu) == false)
				{
					string filePath = pDesc->m_szElu;
					if (filePath.find("woman") != std::string::npos)
					{
						filePath = string("model/woman/") + pDesc->m_szElu;
					}
					else
					{
						filePath = string("model/man/") + pDesc->m_szElu;
					}
					playerMesh->m_parts_mgr->Add((char*)filePath.c_str());// ("man")->AddNode(playerItem->m_szElu);//Add((char*)filePath.c_str());
				}
			}
			szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szHeadMeshName;
			if( strlen(szMeshName) > 0 )	pVMesh->SetParts(eq_parts_head, szMeshName,pDesc->GetEluName());
			else							ChangeCharHair(pVMesh, nSex, nHairIndex);

			szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szChestMeshName;
			if( strlen(szMeshName) > 0 )	pVMesh->SetParts(eq_parts_chest, szMeshName, pDesc->GetEluName());
			else							pVMesh->SetBaseParts(eq_parts_chest);

			szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szHandMeshName;
			if( strlen(szMeshName) > 0 )	pVMesh->SetParts(eq_parts_hands, szMeshName, pDesc->GetEluName());
			else							pVMesh->SetBaseParts(eq_parts_hands);

			szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szLegsMeshName;
			if( strlen(szMeshName) > 0 )	pVMesh->SetParts(eq_parts_legs, szMeshName, pDesc->GetEluName());
			else							pVMesh->SetBaseParts(eq_parts_legs);

			szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szFeetMeshName;
			if( strlen(szMeshName) > 0 )	pVMesh->SetParts(eq_parts_feet, szMeshName, pDesc->GetEluName());
			else							pVMesh->SetBaseParts(eq_parts_feet);
		}

		//pVMesh->SetBaseParts(eq_parts_face);
	}

Find <br>

	void ChangeEquipParts(ZObjectVMesh* pVMesh, const unsigned long int* pItemID)
	{
		pVMesh->ClearParts();

		struct _ZPARTSPAIR
		{
			_RMeshPartsType			meshparts;
			MMatchCharItemParts		itemparts;
		};

		static _ZPARTSPAIR PartsPair[] = 
		{
			{eq_parts_head,		MMCIP_HEAD},
			{eq_parts_chest,	MMCIP_CHEST},
			{eq_parts_hands,	MMCIP_HANDS},
			{eq_parts_legs,		MMCIP_LEGS},
			{eq_parts_feet,		MMCIP_FEET}
		};

		for (int i = 0; i < 5; i++) {
			if (pItemID[PartsPair[i].itemparts] != 0) {
				MMatchItemDesc* pDesc = MGetMatchItemDescMgr()->GetItemDesc(pItemID[PartsPair[i].itemparts]);
				if (pDesc != NULL) {
					pVMesh->SetParts(PartsPair[i].meshparts, pDesc->m_pMItemName->Ref().m_szMeshName);
				}
			}
			else {
				pVMesh->SetBaseParts( PartsPair[i].meshparts );
			}
		}

		pVMesh->SetBaseParts(eq_parts_face);
	}

Replace <br>

	void ChangeEquipParts(ZObjectVMesh* pVMesh, const unsigned long int* pItemID)
	{
		pVMesh->ClearParts();

		if (pVMesh->GetMesh() == nullptr)
			return;

		struct _ZPARTSPAIR
		{
			_RMeshPartsType			meshparts;
			MMatchCharItemParts		itemparts;
		};

		static _ZPARTSPAIR PartsPair[] = 
		{
			{eq_parts_head,		MMCIP_HEAD},
			{eq_parts_chest,	MMCIP_CHEST},
			{eq_parts_hands,	MMCIP_HANDS},
			{eq_parts_legs,		MMCIP_LEGS},
			{eq_parts_feet,		MMCIP_FEET}
		};

		//Dynamic resource loading
		for (int i = 0; i < 5; i++)
		{
			if (pItemID[PartsPair[i].itemparts] != 0)
			{
				MMatchItemDesc* pDesc = MGetMatchItemDescMgr()->GetItemDesc(pItemID[PartsPair[i].itemparts]);
				if (pDesc != NULL)
				{
					if (pDesc->GetEluName() != nullptr)
					{
						RMesh* playerMesh = nullptr;
						if (_stricmp(pVMesh->GetMesh()->GetName(),"heroman1")==0)
						{
							playerMesh = ZGetMeshMgr()->Get("heroman1");
						}
						else
						{
							playerMesh = ZGetMeshMgr()->Get("herowoman1");
						}
						if (playerMesh->m_parts_mgr->Find(pDesc->m_szElu) == false)//Find(playerItem->m_szElu) == false)
						{
							string filePath = pDesc->m_szElu;
							if (filePath.find("woman") != std::string::npos)
							{
								filePath = string("model/woman/") + pDesc->m_szElu;
							}
							else
							{
								filePath = string("model/man/") + pDesc->m_szElu;
							}
							playerMesh->m_parts_mgr->Add((char*)filePath.c_str());// ("man")->AddNode(playerItem->m_szElu);//Add((char*)filePath.c_str());
						}
						else
						{
							pVMesh->SetParts(PartsPair[i].meshparts, pDesc->m_pMItemName->Ref().m_szMeshName, pDesc->GetEluName());
						}
					}
				}
			}
			else {
				pVMesh->SetBaseParts( PartsPair[i].meshparts );
			}
		}

		pVMesh->SetBaseParts(eq_parts_face);
	}

Open(MMatchItem.cpp) <br>
Find <br>

	MUID MMatchItemMap::m_uidGenerate = MUID(0,0);
	MCriticalSection MMatchItemMap::m_csUIDGenerateLock;

Add <br>

	const char* MMatchItemDesc::GetEluName()
	{
		if (strlen(m_szElu) > 0)
			return m_szElu;

		return nullptr;
	}

Open(MMatchItem.h) <br>
Find <br>

	bool					m_bIsEnableMoveToAccountItem;

Replace <br>

	//Dynamic resource loading
	char					m_szElu[256];
	const char*				GetEluName();

Open(ZCharacter.cpp) <br>
Find <br>

		} else {
			char* szMeshName;
			MMatchItemDesc* pDesc = pAvatarItem->GetDesc();
			if( pDesc != NULL ) {
				m_pVMesh->ClearParts();

				szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szHeadMeshName;
				if( strlen(szMeshName) > 0 )	m_pVMesh->SetParts(eq_parts_head, szMeshName);
				else							ChangeCharHair(m_pVMesh, m_Property.nSex, m_Property.nHair);

				szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szChestMeshName;
				if( strlen(szMeshName) > 0 )	m_pVMesh->SetParts(eq_parts_chest, szMeshName);
				else							m_pVMesh->SetBaseParts(eq_parts_chest);

				szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szHandMeshName;
				if( strlen(szMeshName) > 0 )	m_pVMesh->SetParts(eq_parts_hands, szMeshName);
				else							m_pVMesh->SetBaseParts(eq_parts_hands);

				szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szLegsMeshName;
				if( strlen(szMeshName) > 0 )	m_pVMesh->SetParts(eq_parts_legs, szMeshName);
				else							m_pVMesh->SetBaseParts(eq_parts_legs);

				szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szFeetMeshName;
				if( strlen(szMeshName) > 0 )	m_pVMesh->SetParts(eq_parts_feet, szMeshName);
				else							m_pVMesh->SetBaseParts(eq_parts_feet);

				m_pVMesh->SetSkipRenderFaceParts(true);
			}
		}
	}

Replace <br>

			} else {
				char* szMeshName;
				MMatchItemDesc* pDesc = pAvatarItem->GetDesc();
				if( pDesc != NULL ) {
					m_pVMesh->ClearParts();

					szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szHeadMeshName;
					if( strlen(szMeshName) > 0 )	m_pVMesh->SetParts(eq_parts_head, szMeshName, pDesc->GetEluName());
					else							ChangeCharHair(m_pVMesh, m_Property.nSex, m_Property.nHair);

					szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szChestMeshName;
					if( strlen(szMeshName) > 0 )	m_pVMesh->SetParts(eq_parts_chest, szMeshName, pDesc->GetEluName());
					else							m_pVMesh->SetBaseParts(eq_parts_chest);

					szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szHandMeshName;
					if( strlen(szMeshName) > 0 )	m_pVMesh->SetParts(eq_parts_hands, szMeshName, pDesc->GetEluName());
					else							m_pVMesh->SetBaseParts(eq_parts_hands);

					szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szLegsMeshName;
					if( strlen(szMeshName) > 0 )	m_pVMesh->SetParts(eq_parts_legs, szMeshName, pDesc->GetEluName());
					else							m_pVMesh->SetBaseParts(eq_parts_legs);

					szMeshName = pDesc->m_pAvatarMeshName->Ref().m_szFeetMeshName;
					if( strlen(szMeshName) > 0 )	m_pVMesh->SetParts(eq_parts_feet, szMeshName, pDesc->GetEluName());
					else							m_pVMesh->SetBaseParts(eq_parts_feet);

					m_pVMesh->SetSkipRenderFaceParts(true);
				}
			}
		}

Find <br>

	pVMesh->SetParts(eq_parts_face, szMeshName);

Replace <br>

	pVMesh->SetParts(eq_parts_face, szMeshName,nullptr);

Find <br>

		if( pAvatarItem && pAvatarItem->IsEmpty() ) {
			for (int i = 0; i < MMCIP_END;i++) {
				switch (MMatchCharItemParts(i))
				{
				case MMCIP_HEAD:	mesh_parts_type = eq_parts_head;	break;
				case MMCIP_CHEST:	mesh_parts_type = eq_parts_chest;	break;
				case MMCIP_HANDS:	mesh_parts_type = eq_parts_hands;	break;
				case MMCIP_LEGS:	mesh_parts_type = eq_parts_legs;	break;
				case MMCIP_FEET:	mesh_parts_type = eq_parts_feet;	break;
				default: continue;
				}

				if (!GetItems()->GetItem(MMatchCharItemParts(i))->IsEmpty()) {
					m_pVMesh->SetParts(mesh_parts_type, GetItems()->GetItem(MMatchCharItemParts(i))->GetDesc()->m_pMItemName->Ref().m_szMeshName);
				}
				else {
					m_pVMesh->SetBaseParts(mesh_parts_type);
				}
			}	// for

Replace <br>

		if( pAvatarItem && pAvatarItem->IsEmpty() )
		{
			for (int i = 0; i < MMCIP_END;i++) {
				switch (MMatchCharItemParts(i))
				{
				case MMCIP_HEAD:	mesh_parts_type = eq_parts_head;	break;
				case MMCIP_CHEST:	mesh_parts_type = eq_parts_chest;	break;
				case MMCIP_HANDS:	mesh_parts_type = eq_parts_hands;	break;
				case MMCIP_LEGS:	mesh_parts_type = eq_parts_legs;	break;
				case MMCIP_FEET:	mesh_parts_type = eq_parts_feet;	break;
				default: continue;
				}

				if (!GetItems()->GetItem(MMatchCharItemParts(i))->IsEmpty())
				{
					MMatchItemDesc* itemDesc = GetItems()->GetItem(MMatchCharItemParts(i))->GetDesc();
					if (itemDesc->GetEluName() != nullptr)
					{
						RMesh* playerMesh = nullptr;
						if (_stricmp(m_pVMesh->GetMesh()->GetName(), "heroman1") == 0)
						{
							playerMesh = ZGetMeshMgr()->Get("heroman1");
						}
						else
						{
							playerMesh = ZGetMeshMgr()->Get("herowoman1");
						}
						if (playerMesh->m_parts_mgr->Find(itemDesc->m_szElu) == false)
						{
							string filePath = itemDesc->m_szElu;
							if (filePath.find("woman") != std::string::npos)
							{
								filePath = string("model/woman/") + itemDesc->m_szElu;
							}
							else
							{
								filePath = string("model/man/") + itemDesc->m_szElu;
							}
							playerMesh->m_parts_mgr->Add((char*)filePath.c_str());
							MeshesFinishedLoading = false;
							meshupdatetime = 0;
						}
						else
						{
							m_pVMesh->SetParts(mesh_parts_type, itemDesc->m_pMItemName->Ref().m_szMeshName, itemDesc->m_szElu);
						}
					}
					//m_pVMesh->SetParts(mesh_parts_type, itemDesc->m_pMItemName->Ref().m_szMeshName, itemDesc->m_szElu);
				}
				else {
					m_pVMesh->SetBaseParts(mesh_parts_type);
				}
			}	// for


Open(ZCharacter.h) <br>
Find <br>

	class ZCharacter : public ZCharacterObject
	{
		MDeclareRTTI;
		//friend class ZCharacterManager;
	private:

Add <br>

	bool MeshesFinishedLoading;

Open(ZCharacter.cpp) <br>
Find <br>

	void ZCharacter::OnUpdate(float fDelta)

Add Above <br>

	static DWORD meshupdatetime = 0;

Open(RMeshMgr.h) <br>
Find <br>

	vector<RMesh*> m_node_table;
	DWORD	m_cur;

Add <br>

	bool Find(const char* name);

Open(RMeshMgr.cpp) <br>
Find <br>

	RMeshNode* RMeshMgr::GetPartsNode(char* name)
	{
		r_mesh_node node;
		RMesh* pMesh = NULL;
		RMeshNode* pMeshNode = NULL;

		for(node = m_list.begin(); node != m_list.end(); ++node) {
			pMesh = (*node);
			pMeshNode = pMesh->GetMeshData(name);
			if(pMeshNode)
				return pMeshNode;
		}
		return NULL;
	}


Add <br>

	//Dynamic resource loading
	bool RMeshMgr::Find(const char* name)
	{
		r_mesh_node node;
		for (node = m_list.begin(); node != m_list.end(); ++node)
		{
			string modelName = (*node)->m_FileName.substr((*node)->m_FileName.find_last_of('/') + 1);
			if (modelName == name)
			{
				return true;
			}
		}
		return false;
	}

Open(ZGame.cpp) <br>
Find <br>

	void ZGame::OnExplosionDynamite(MUID uidOwner, rvector pos, float fDamage, float fRange, float fKnockBack, MMatchTeam nTeamID)
	{

Add <br>

	bool ZGame::PickWorld( const rvector &pos, const rvector &dir,RBSPPICKINFO *pOut,DWORD dwPassFlag)
	{
		RBspObject*  r_map = GetWorld()->GetBsp();
		return r_map->Pick(pos, dir, pOut, dwPassFlag);
	}

	bool ZGame::CheckWall(rvector &origin, rvector &targetpos, float fRadius, float fHeight, RCOLLISIONMETHOD method, int nDepth, rplane *pimpactplane)
	{
		return GetWorld()->GetBsp()->CheckWall(origin,targetpos,35,60,RCW_CYLINDER,0,pimpactplane);
	}














