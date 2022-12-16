Gamemode: Challenge Quest <br>

Not Finished! <br>
CSCommon <br>
- MMatchRuleQuestChallenge.h <br>
- IMatchRuleNewQuest.h <br>
- MNewQuestScenario.h <br>
- MActorDef.h <br>

Gunz <br>
- ZActorWithFSM.h
- ZActorBase.h
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









    
