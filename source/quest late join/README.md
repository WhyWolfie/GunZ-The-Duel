Not done yet. Still working on it. <br>

Open(MMatchRuleBaseQuest.cpp) <br>
Find <br>

    RouteGameInfo();

Replace <br>

    //RouteGameInfo();


Find <br>

    void MMatchRuleBaseQuest::OnEnterBattle(MUID& uidChar)
    {

    }

    void MMatchRuleBaseQuest::OnCommand(MCommand* pCommand)
    {



    }


Replace <br>

    void MMatchRuleBaseQuest::OnEnterBattle(MUID& uidChar)
    {
      MMatchObject* pObj = MMatchServer::GetInstance()->GetObject(uidChar);
      if (IsAdminGrade(pObj) && pObj->CheckPlayerFlags(MTD_PlayerFlags_AdminHide)) return;

      m_PlayerManager.AddPlayer(uidChar);
      m_NPCManager.OnAddPlayer(uidChar);

      if (GetRoundState() == MMATCH_ROUNDSTATE_PLAY)
      {
        m_NPCManager.RouteSpawnedToListener(uidChar);
      }
      pObj->SetAlive(false);

      MMatchServer::GetInstance()->OnQuestRequestDead(uidChar);
    }

    void MMatchRuleBaseQuest::OnQuestEnterBattle(MUID& uidChar)
    {
      RouteGameInfoToSingle(uidChar);
      PostNPCInfoForSingle(uidChar);
    }

    void MMatchRuleBaseQuest::OnQuestStageLaunch()
    {
      RouteGameInfo();
    }


    void MMatchRuleBaseQuest::OnCommand(MCommand* pCommand)
    {



    }


Open(MMatchNPCObject.cpp) <br>
Find <br>

    MMatchNPCObject::MMatchNPCObject(MUID& uid, MQUEST_NPC nType, unsigned long int nFlags)
              : m_UID(uid), m_nType(nType), m_uidController(MUID(0,0)), m_Pos(0.0f,0.0f,0.0f), m_nFlags(nFlags)
    {

    }

    void MMatchNPCObject::AssignControl(MUID& uidPlayer)
    {
      m_uidController = uidPlayer;
    }

Replace <br>

    MMatchNPCObject::MMatchNPCObject(MUID& uid, MQUEST_NPC nType, unsigned long int nFlags)
              : m_UID(uid), m_nType(nType), m_uidController(MUID(0,0)), m_Pos(0.0f,0.0f,0.0f), m_nFlags(nFlags)
    {
      m_nIndex = 0;
    }

    void MMatchNPCObject::AssignControl(MUID& uidPlayer, signed int nIndex)
    {
      m_uidController = uidPlayer;
      if(nIndex >= 0)
      m_nIndex = nIndex;
    }

Find <br>

    SetNPCObjectToControllerInfo(uidController, pNPCObject);

Replace <br>

			SetNPCObjectToControllerInfo(uidController, pNPCObject, nSpawnPositionIndex);

Find <br>

    bool MMatchNPCManager::Spawn(MUID& uidNPC, MUID& uidController, unsigned char nSpawnPositionIndex)
    {

Add under <br>

    bool MMatchNPCManager::RouteSpawnedToListener(MUID& uidListener)
    {
      MMatchObject* pListener = MMatchServer::GetInstance()->GetObject(uidListener);
      if (IsEnabledObject(pListener) && (m_pStage))
      {
        for (MMatchNPCObjectMap::iterator itorNPC = this->m_NPCObjectMap.begin(); itorNPC != this->m_NPCObjectMap.end(); ++itorNPC)
        {
          if (m_pStage)
          {
            MMatchNPCObject* pNPCObject = (*itorNPC).second;
            if (pNPCObject && pNPCObject->GetIndex() >= 0)
            {
              // route cmd
              MCommand* pCmd = MMatchServer::GetInstance()->CreateCommand(MC_QUEST_NPC_SPAWN, pNPCObject->GetController());
              pCmd->AddParameter(new MCmdParamUID(pNPCObject->GetController()));
              pCmd->AddParameter(new MCmdParamUID(pNPCObject->GetUID()));
              pCmd->AddParameter(new MCmdParamUChar((unsigned char)pNPCObject->GetType()));
              pCmd->AddParameter(new MCmdParamUChar((unsigned char)pNPCObject->GetIndex()));
              MMatchServer::GetInstance()->RouteToListener(pListener, pCmd);
            }
          }
        }
      }
      return true;
    }

Find <br>

    void MMatchNPCManager::ClearNPC()

Add above <br>

    void MMatchNPCManager::OnAddPlayer(const MUID& uidPlayer)
    {
      // Create È£Ãâ Àü¿¡.. ½ÇÇàµÉ ¼öµµ ÀÖ´Ù. - By È«±âÁÖ 2009.08.17
      if( m_pPlayerManager == NULL ) return;
    }

Find <br>

    void MMatchNPCManager::SetNPCObjectToControllerInfo(MUID& uidChar, MMatchNPCObject* pNPCObject)
    {
      MUID uidLaster = pNPCObject->GetController();
      if (uidLaster != MUID(0,0))
      {
        DelNPCObjectToControllerInfo(uidLaster, pNPCObject);
      }

      // Create È£Ãâ Àü¿¡.. ½ÇÇàµÉ ¼öµµ ÀÖ´Ù. - By È«±âÁÖ 2009.08.17
      // ´õ ±ò²ûÇÑ ¹æ¹ýÀ» °­±¸ÇØº¸ÀÚ! - ÀÏ´ÜÀº ÀÌ·¸°Ô Á¶Ä¡ÇÔ
      if( m_pPlayerManager == NULL ) return;

      MQuestPlayerInfo* pControllerInfo = m_pPlayerManager->GetPlayerInfo(uidChar);
      if (pControllerInfo)
      {
        pNPCObject->AssignControl(uidChar);
        pControllerInfo->NPCObjects.insert(MMatchNPCObjectMap::value_type(pNPCObject->GetUID(), pNPCObject));
      }
    }

Replace <br>

    void MMatchNPCManager::SetNPCObjectToControllerInfo(MUID& uidChar, MMatchNPCObject* pNPCObject, signed int nIndex)
    {
      MUID uidLaster = pNPCObject->GetController();
      if (uidLaster != MUID(0,0))
      {
        DelNPCObjectToControllerInfo(uidLaster, pNPCObject);
      }

      // Create È£Ãâ Àü¿¡.. ½ÇÇàµÉ ¼öµµ ÀÖ´Ù. - By È«±âÁÖ 2009.08.17
      // ´õ ±ò²ûÇÑ ¹æ¹ýÀ» °­±¸ÇØº¸ÀÚ! - ÀÏ´ÜÀº ÀÌ·¸°Ô Á¶Ä¡ÇÔ
      if( m_pPlayerManager == NULL ) return;

      MQuestPlayerInfo* pControllerInfo = m_pPlayerManager->GetPlayerInfo(uidChar);
      if (pControllerInfo)
      {
        pNPCObject->AssignControl(uidChar, nIndex);
        pControllerInfo->NPCObjects.insert(MMatchNPCObjectMap::value_type(pNPCObject->GetUID(), pNPCObject));
      }
    }

Open(MMatchNPCObject.h) <br>
Find <br>

	MUID				m_UID;						///< ID
	MQUEST_NPC			m_nType;					///< NPCÅ¸ÀÔ
	MUID				m_uidController;

Add under <br>

	signed int			m_nIndex;

Find <br>

    void AssignControl(MUID& uidPlayer);

Replace <br>

	void AssignControl(MUID& uidPlayer, signed int nIndex = -1);

Find <br>

    MQUEST_NPC	GetType()			{ return m_nType; }

Add under <br>

    signed int	GetIndex()			{ return m_nIndex; }

Find <br>

    void SetNPCObjectToControllerInfo(MUID& uidChar, MMatchNPCObject* pNPCObject);

Replace <br>

	void SetNPCObjectToControllerInfo(MUID& uidChar, MMatchNPCObject* pNPCObject, signed int nIndex = -1);

Find <br>

    void OnDelPlayer(const MUID& uidPlayer);

Add under <br>

	//Add Player (intrude)
	void OnAddPlayer(const MUID& uidPlayer);

Find <br>

    void RemovePlayerControl(const MUID& uidPlayer);

Add under <br>

    bool RouteSpawnedToListener(MUID& uidListener);

Open(MMatchNPCObject.cpp) <br>
Add <br>

    #include "MMatchNPCObject.h"


Open(MMatchNPCObject.h) <br>
Find <br>

    void AssignControl(MUID& uidPlayer);

Replace <br>

	void AssignControl(MUID& uidPlayer, signed int nIndex = -1);

Find <br>

    void SetNPCObjectToControllerInfo(MUID& uidChar, MMatchNPCObject* pNPCObject);

Replace <br>

	void SetNPCObjectToControllerInfo(MUID& uidChar, MMatchNPCObject* pNPCObject, signed int nIndex = -1);

Open(MMatchServer_Stage.cpp) <br>
Find <br>

    void MMatchServer::StageLaunch(const MUID& uidStage)
    {
      MMatchStage* pStage = FindStage(uidStage);
      if (pStage == NULL) return;

      ReserveAgent(pStage);

      MCommand* pCmd = CreateCommand(MC_MATCH_STAGE_LAUNCH, MUID(0,0));
      pCmd->AddParameter(new MCmdParamUID(uidStage));
      pCmd->AddParameter(new MCmdParamStr( const_cast<char*>(pStage->GetMapName()) ));
      RouteToStage(uidStage, pCmd);
    }

Replace <br>

    void MMatchServer::StageLaunch(const MUID& uidStage)
    {
      MMatchStage* pStage = FindStage(uidStage);
      if (pStage == NULL) return;

      //ReserveAgent(pStage);

      if (MGetGameTypeMgr()->IsQuestDerived(pStage->GetStageSetting()->GetGameType()))
      {
        if (pStage->m_pRule)
        {
          pStage->m_pRule->OnQuestStageLaunch();
        }
      }

      MCommand* pCmd = CreateCommand(MC_MATCH_STAGE_LAUNCH, MUID(0, 0));
      pCmd->AddParameter(new MCmdParamUID(uidStage));
      pCmd->AddParameter(new MCmdParamStr(const_cast<char*>(pStage->GetMapName())));
      RouteToStage(uidStage, pCmd);
    }


Open(MMatchRuleBaseQuest.h) <br>
Find <br>

	class MMatchQuestGameLogInfoManager;

Replace <br>

	//class MMatchQuestGameLogInfoManager;

Find <br>

	virtual void RouteGameInfo() = 0;

Add under <br>

	virtual void RouteGameInfoToSingle(MUID& uidPlayer) = 0;

Find <br>

	public:
		MMatchRuleBaseQuest(MMatchStage* pStage);			///< »ý¼ºÀÚ
		virtual ~MMatchRuleBaseQuest();						///< ¼Ò¸êÀÚ
		virtual void OnEnterBattle(MUID& uidChar);			///< °ÔÀÓÁß ³­ÀÔÇÒ¶§ È£ÃâµÈ´Ù.
		virtual void OnLeaveBattle(MUID& uidChar);			///< °ÔÀÓÁß ³ª°¬À»¶§ È£ÃâµÈ´Ù.

		virtual void RefreshStageGameInfo() = 0;
	};

Replace <br>

	public:
		MMatchRuleBaseQuest(MMatchStage* pStage);			///< »ý¼ºÀÚ
		virtual ~MMatchRuleBaseQuest();						///< ¼Ò¸êÀÚ
		virtual void OnEnterBattle(MUID& uidChar);			///< °ÔÀÓÁß ³­ÀÔÇÒ¶§ È£ÃâµÈ´Ù.
		virtual void OnQuestEnterBattle(MUID& uidChar);			///< °ÔÀÓÁß ³­ÀÔÇÒ¶§ È£ÃâµÈ´Ù.
		virtual void PostNPCInfoForSingle(MUID& uidPlayer) {}
		virtual void OnQuestStageLaunch();			///< °ÔÀÓÁß ³­ÀÔÇÒ¶§ È£ÃâµÈ´Ù.
		virtual void OnLeaveBattle(MUID& uidChar);			///< °ÔÀÓÁß ³ª°¬À»¶§ È£ÃâµÈ´Ù.
		MQuestPlayerManager* GetPlayerManager() { return &m_PlayerManager; }

		virtual void RefreshStageGameInfo() = 0;
	};

Open(MMatchRuleQuest.cpp) <br>
Find <br>

	void MMatchRuleQuest::RouteGameInfo()

Add under <br>

	void MMatchRuleQuest::RouteGameInfoToSingle(MUID& uidPlayer)
	{
		MCommand* pCmd = MMatchServer::GetInstance()->CreateCommand(MC_QUEST_GAME_INFO, MUID(0,0));

		void* pBlobGameInfoArray = MMakeBlobArray(sizeof(MTD_QuestGameInfo), 1);
		MTD_QuestGameInfo* pGameInfoNode = (MTD_QuestGameInfo*)MGetBlobArrayElement(pBlobGameInfoArray, 0);

		if (m_pQuestLevel)
		{
			m_pQuestLevel->Make_MTDQuestGameInfo(pGameInfoNode, MMATCH_GAMETYPE_QUEST);
		}

		pCmd->AddParameter(new MCommandParameterBlob(pBlobGameInfoArray, MGetBlobArraySize(pBlobGameInfoArray)));
		MEraseBlobArray(pBlobGameInfoArray);

		MMatchObject* pObj = MMatchServer::GetInstance()->GetObject(uidPlayer);
		if(!IsEnabledObject(pObj)) return;

		MMatchServer::GetInstance()->RouteToListener(pObj, pCmd);
	}

Find <br> 

	const bool MMatchRuleQuest::PostNPCInfo()

Add under <br>

	void MMatchRuleQuest::PostNPCInfoForSingle(MUID& uidPlayer)
	{
		MMatchQuest*		pQuest			= MMatchServer::GetInstance()->GetQuest();
		MQuestScenarioInfo* pScenarioInfo	= pQuest->GetScenarioInfo( m_StageGameInfo.nScenarioID );
		if( NULL == pScenarioInfo )
		{
			return;
		}

		vector< MQUEST_NPC > NPCList;

		for( size_t i = 0; i < SCENARIO_STANDARD_DICE_SIDES; ++i )
		{
			MakeJacoNPCList( NPCList, pScenarioInfo->Maps[i] );
			MakeNomalNPCList( NPCList, pScenarioInfo->Maps[i], pQuest );
		}

		void* pBlobNPC = MMakeBlobArray(sizeof(MTD_NPCINFO), int(NPCList.size()) );
		if( NULL == pBlobNPC )
		{
			return;
		}

		vector< MQUEST_NPC >::iterator	itNL;
		vector< MQUEST_NPC >::iterator	endNL;
		MQuestNPCInfo*					pQuestNPCInfo		= NULL;
		int								nNPCIndex			= 0;
		MTD_NPCINFO*					pMTD_QuestNPCInfo	= NULL;

		endNL = NPCList.end();
		for( itNL = NPCList.begin(); endNL != itNL; ++ itNL )
		{
			pQuestNPCInfo = pQuest->GetNPCInfo( (*itNL) );	
			if( NULL == pQuestNPCInfo )
			{
				MEraseBlobArray( pBlobNPC );
				return;
			}

			pMTD_QuestNPCInfo = reinterpret_cast< MTD_NPCINFO* >( MGetBlobArrayElement(pBlobNPC, nNPCIndex++) );
			if( NULL == pMTD_QuestNPCInfo )
			{
				//_ASSERT( 0 );
				MEraseBlobArray( pBlobNPC );
				return;
			}

			CopyMTD_NPCINFO( pMTD_QuestNPCInfo, pQuestNPCInfo );
		}

		MCommand* pCmdNPCList = MGetMatchServer()->CreateCommand( MC_QUEST_NPCLIST, MUID(0, 0) );
		if( NULL == pCmdNPCList )
		{
			MEraseBlobArray( pBlobNPC );
			return;
		}

		pCmdNPCList->AddParameter( new MCommandParameterBlob(pBlobNPC, MGetBlobArraySize(pBlobNPC)) );
		pCmdNPCList->AddParameter( new MCommandParameterInt(GetGameType()) );

		MMatchObject* pObj = MMatchServer::GetInstance()->GetObject(uidPlayer);

		if(!IsEnabledObject(pObj)) return;

		MGetMatchServer()->RouteToListener(pObj, pCmdNPCList );

		MEraseBlobArray( pBlobNPC );

		return;
	}






