Mark '//Rejoin' for now i will add that later in the future.

Open(MMatchChannel.h - MCHANNEL_TYPE)

	MCHANNEL_TYPE_PLAYERWARS = 6,
  
Open(MMatchDBMgr.h - GetLoginInfo_Netmarble)

	int IsPlayerWarsOpen();

Find(GetSurvivalModePrivateRanking - Add under)

	bool GetPlayerWarsCharInfo(DWORD dwCID, PlayerWarsCharInfo* pPWCharInfo);
	bool UpdatePlayerWarsCharInfo(DWORD dwCID, int Win, int Loss, int Draw, int Score, int Mode);
	bool GetPlayerWarsSideRankingInfo(DWORD dwCID, list<PWRankingInfo*>* pRankingList);

Find(RewardCharBattleTimeReward - Add under)

	bool UpdatePlayerWars();

Open(MMatchGlobal.h - g_nNeedLadderMemberCount[MLADDERTYPE_MAX])

    enum PlayerWars
    {
      MPLAYERWARSTYPE_NORMAL_1VS1 = 0,
      MPLAYERWARSTYPE_NORMAL_2VS2,
      MPLAYERWARSTYPE_NORMAL_3VS3,
      MPLAYERWARSTYPE_NORMAL_4VS4,
      MPLAYERWARSTYPE_NORMAL_5VS5,
      MPLAYERWARSTYPE_NORMAL_6VS6,
      MPLAYERWARSTYPE_NORMAL_7VS7,
      MPLAYERWARSTYPE_NORMAL_8VS8,
      MPLAYERWARSTYPE_MAX
    };

Find (typedef struct _MShortBuffInfo)

    struct PlayerWarsCharInfo
    {
      int Ranking;
      int Wins;
      int Losses;
      int Draws;
      int Score;
      void AddLoss() { Losses++; }
      void AddWin() { Wins++; }
      void AddDraw() { Draws++; }
      void AddScore(int score) { Score += score; }
      void MinusScore(int score) { Score -= score; if (Score <= -1) Score = 0; }
    };

Open(MMatchObject.h - m_IsRecvFirstGameguardResponse)

    public :
      unsigned long int PlayerWarsIdentifier;

Find (enum MMO_ACTION - Add under)

	enum PlayerWarsInviteState
	{
		Invited,
		Inviter,
		NotInvited
	};


Find (m_dwHShieldCheckCount - Add under)

	MUID PlayerWarsFriend;
	PlayerWarsInviteState PwState;

Find (chObjectDuelTournamentCharInfo* GetDuelTournamentCharInfo() - Add under)

	PlayerWarsCharInfo* m_pPlayerWarsCharInfo;
	PlayerWarsCharInfo* GetPlayerWarsInfo() { return m_pPlayerWarsCharInfo; }
	void SetPlayerWarsCharInfo(PlayerWarsCharInfo* info);
    void FreePlayerWarsInfo();


Open(MMatchServer.h)

    #include "MPlayerWarsMgr.h"

Find(class MMatchServer : public MServer - Add under)

	bool CanPlayerWars;

Find (MLadderMgr			m_LadderMgr - Add under)

	MPlayerWarsMgr		m_PlayerWarsMgr;

Find (void OnAsyncBuyQuestItem( MAsyncJob* pJobResult ); - Add under)

	void OnAsyncUpdatePlayerWars(MAsyncJob* pJobResult);
	void OnAsyncGetPlayerWarsCharInfo(MAsyncJob* pJobResult);

Find (MLadderMgr*	GetLadderMgr()				{ return &m_LadderMgr; } - Add under)

    MPlayerWarsMgr* GetPlayerWarsMgr()		{ return m_PlayerWarsMgr.GetInstance(); }

Find (void RouteCmdDuelTournamentMTDMatchResultInfo(const MUID& uidStage, MTD_DuelTournamentMatchResultInfo *MatchResultInfo); - Add under)

	void SendPlayerWarsCharInfoToPlayer(MUID uidPlayer);
	void SendPlayerWarsRewards(PlayerWarsListDef List, bool bIsDrawGame, MMatchTeam nWinnerTeam, int WinningScore, int LosingScore, int MapId);
	void LaunchPlayerWarsGame(PlayerJoiningDataStruct Data, PlayerWars Type, int nMapID);
	void UpdatePlayerWarsGame(MMatchStage* pStage, MMatchObject* pObj, MMatchTeam nTeam);
	void PostPlayerWarsCharInfo(MUID uidPlayer, PlayerWarsCharInfo *pPWCharInfo);
	void UpdatePlayerWarsQueueingCounts(MTD_PlayerWarsCounterInfo CounterInfo);
	void UpdatePlayerWarsCharInfo(int cid, int win, int loss, int draw, int score, int mode);
	void OnAsyncResponse_GetPlayerWarsSideRanking(MAsyncJob *pJobResult);
	void PostCmdPlayerWarsCharSideRankingInfo(MUID uidPlayer, list<PWRankingInfo*>* pSideRankingList);
	void SendPlayerWarsSideRankingToPlayer(MUID uidPlayer);

Open(MMatchStage.h - enum MMatchStageType - replace)

    enum MMatchStageType
    {
      MST_NORMAL = 0,
      MST_LADDER,
      MST_PLAYERWARS,

      MST_MAX
    };

Find (typedef map<MUID, MMATCH_RESOURCECHECKINFO>	ResourceCRC32CacheMap; - Add under)

    struct PlayerWarsInfos
    {
      MMatchTeam Team;
      MUID Player;
      PlayerWarsInfos(MMatchTeam t, MUID p)
      {
        Team = t;
        Player = p;
      }
    };

    typedef	map<int, PlayerWarsInfos*> PlayerWarsListDef;

Find(vector< MMatchStageSuicide > m_SuicideList; - Add under)

	PlayerWarsListDef PlayerWarsList;

Find(MMatchWorldItemManager	m_WorldItemManager; - Add above)

	void PlayerWarsAdd(int cid, MMatchTeam Team, MUID Player) { PlayerWarsList.insert(PlayerWarsListDef::value_type(cid, new PlayerWarsInfos(Team, Player))); }
	MMatchTeam PlayerWarsTeam(int cid) { PlayerWarsListDef::iterator i = PlayerWarsList.find(cid); if (i != PlayerWarsList.end()) return i->second->Team; return MMT_ALL; }

Open(MMatchTransDataType.h - #pragma pack(1) - Add under)

    struct MTD_PlayerWarsCounterInfo
    {
      int Count[MPLAYERWARSTYPE_MAX];
    };

Open(MSharedCommandTable.h)

    #define MC_MATCH_PLAYERWARS_RANDOM_MAPS			50044
    #define MC_MATCH_PLAYERWARS_VOTE				    50045
    #define MC_MATCH_PLAYERWARS_VOTE_UPDATE			50046
    #define MC_MATCH_PLAYERWARS_FRIENDINVITE		50047
    #define MC_MATCH_PLAYERWARS_FRIENDACCEPT		50048
    #define MC_MATCH_PLAYERWARS_FRIENDLEAVE			50049
    #define MC_MATCH_PLAYERWARS_CHARINFO			  50050
    #define MC_MATCH_JOIN_PLAYERWARS				    50051
    #define MC_MATCH_PLAYERWARS_COUNTER				  50052
    #define MC_MATCH_PLAYERWARS_SIDERANK			  50053
    #define MC_MATCH_PLAYERWARS_INVITED         50054

Open(MTeamGameStrategy.h - virtual void SavePointOnFinishGame)

	virtual int GetPlayerWarsRandomMap(int nTeamMember) = 0;

Find (virtual void SavePointOnFinishGame - Add under)

	virtual int GetPlayerWarsRandomMap(int nTeamMember);

Find (virtual void SavePointOnFinishGame - Add under)

	virtual int GetPlayerWarsRandomMap(int nTeamMember);

Add (CSCommon\MMatchServer_PlayerWars.cpp) <br>
Add (CSCommon\MAsyncDBJob_PlayerWars.h) <br>
Add (CSCommon\MAsyncDBJob_PlayerWars.cpp) <br>
Add (CSCommon\MPlayerWarsMgr.cpp) <br>
Add (CSCommon\MPlayerWarsMgr.h) <br>

Open(MBaseGameType.cpp)

    #define MMATCH_GAMETYPE_PLAYERWARS_STR			"Player Wars"

Open(MLadderMgr.cpp - MLadderMgr::MakeMatch - Replace)

    int MLadderMgr::MakeMatch(MLADDERTYPE nLadderType)
    {
      MLadderGroupMap* pWaitGroupMap = GetWaitGroupContainer(nLadderType);
      if (pWaitGroupMap == NULL) return 0;

      MTime time;
      MLadderPicker	ladderPicker;

      for (MLadderGroupMap::iterator i = pWaitGroupMap->begin();
        i != pWaitGroupMap->end(); i++)
      {
        MLadderGroup* pGroup = (*i).second;
        pGroup->UpdateTick();

        int nClanPoint = DEFAULT_CLAN_POINT;
        MMatchClan* pClan = MMatchServer::GetInstance()->GetClanMap()->GetClan(pGroup->GetCLID());
        if (pClan)
        {
          nClanPoint = pClan->GetClanInfoEx()->nPoint;
        }

        const int MAX_RANDOM_ARG = 100;

        ladderPicker.AddTicket(pGroup, nClanPoint, pGroup->GetTickCount(), time.MakeNumber(0, MAX_RANDOM_ARG));
      }

      ladderPicker.Shuffle();

      int nLaunchCount = 0;
      while (true) {
        int nGroupA = 0;
        int nGroupB = 0;
        if (ladderPicker.PickMatch(&nGroupA, &nGroupB) == false)
          break;
        MLadderGroupMap* pGroupMap = GetWaitGroupContainer(nLadderType);
        MLadderGroup* pGroupA = pGroupMap->Find(nGroupA);
        MLadderGroup* pGroupB = pGroupMap->Find(nGroupB);
        MMatchServer* pServer = MMatchServer::GetInstance();
        LaunchLadder(nLadderType, nGroupA, nGroupB);
        nLaunchCount++;
      }
      return nLaunchCount;
    }


Find (MLadderMgr::CancelChallenge - Replace)

    void MLadderMgr::CancelChallenge(int nGroupID, const char* pszCancelName)
    {
      MLadderGroup* pGroup = FindLadderGroup(nGroupID);
      if (pGroup == NULL) return;
      MLadderGroupMap* pGroupMap = GetWaitGroupContainer((MLADDERTYPE)pGroup->GetLadderType());
      if (pGroupMap == NULL) return;

      for (list<MUID>::iterator i = pGroup->GetPlayerListBegin(); i != pGroup->GetPlayerListEnd(); i++)
      {
        MUID uidMember = (*i);

        MMatchObject* pMemberObject = MMatchServer::GetInstance()->GetObject(uidMember);
        if (!IsEnabledObject(pMemberObject)) continue;
        pMemberObject->SetLadderChallenging(false);
        pMemberObject->SetLadderGroupID(0);

        MCommand* pCmd = MMatchServer::GetInstance()->CreateCommand(MC_MATCH_LADDER_CANCEL_CHALLENGE, uidMember);
        pCmd->AddParameter(new MCmdParamStr(pszCancelName));
        pCmd->AddParameter(new MCmdParamBool(false));
        MMatchObject* pObj = MMatchServer::GetInstance()->GetObject(uidMember);
        if (!IsEnabledObject(pObj))
        {
          delete pCmd;
          continue;
        }

        MMatchServer::GetInstance()->RouteToListener(pObj, pCmd);
      }
      pGroupMap->Remove(pGroup->GetID());
      RemoveFromGroupList(pGroup);
      delete pGroup;
    }

Open(MLadderMgr::LaunchLadder - Replace)

    void MLadderMgr::LaunchLadder(MLADDERTYPE nLadderType, int nGroupA, int nGroupB)
    {

      MLadderGroupMap* pGroupMap = GetWaitGroupContainer(nLadderType);
      if (pGroupMap == NULL) return;

      MLadderGroup* pGroupA = pGroupMap->Find(nGroupA);
      MLadderGroup* pGroupB = pGroupMap->Find(nGroupB);

      if ((pGroupA != NULL) && (pGroupB != NULL) && (pGroupA->IsSameGroup(pGroupB))) return;

      pGroupMap->Remove(nGroupA);
      pGroupMap->Remove(nGroupB);

      RemoveFromGroupList(pGroupA);
      RemoveFromGroupList(pGroupB);

      if ((pGroupA == NULL) || (pGroupB == NULL)) {
        return;
      }

      LadderGameMapVoteInfo* m = new LadderGameMapVoteInfo();
      for (int i = 0; i < 3; i++)
      {
        m->Votes[i] = 0;
        m->Maps[i] = -1;
      }
      MBaseTeamGameStrategy* pTeamGameStrategy = MBaseTeamGameStrategy::GetInstance(MGetServerConfig()->GetServerMode());
      if (pTeamGameStrategy)
      {
        for (int i = 0; i < 3; i++)
        {
          int index = pTeamGameStrategy->GetPlayerWarsRandomMap((int)pGroupA->GetPlayerCount());
          while (index == m->Maps[0] || index == m->Maps[1] || index == m->Maps[2])
            index = pTeamGameStrategy->GetPlayerWarsRandomMap((int)pGroupA->GetPlayerCount());
          m->Maps[i] = index;
        }
      };
      int ID = counter++;
      m->RegisterTime = timeGetTime();
      MMatchServer* pServer = MMatchServer::GetInstance();
      pServer = MMatchServer::GetInstance();
      MCommand* pCommand = pServer->CreateCommand(MC_MATCH_PLAYERWARS_RANDOM_MAPS, MUID(0, 0));
      pCommand->AddParameter(new MCmdParamInt(m->Maps[0]));
      pCommand->AddParameter(new MCmdParamInt(m->Maps[1]));
      pCommand->AddParameter(new MCmdParamInt(m->Maps[2]));
      for (list<MUID>::iterator i = pGroupA->GetPlayerListBegin(); i != pGroupA->GetPlayerListEnd(); i++)
      {
        MUID uidPlayer = (*i);
        MMatchObject* pObj = (MMatchObject*)pServer->GetObject(uidPlayer);
        if (pObj)
        {
          pObj->PlayerWarsIdentifier = ID;
          MCommand* pSendCmd = pCommand->Clone();
          pServer->RouteToListener(pObj, pSendCmd);
        }
      }
      for (list<MUID>::iterator i = pGroupB->GetPlayerListBegin(); i != pGroupB->GetPlayerListEnd(); i++)
      {
        MUID uidPlayer = (*i);
        MMatchObject* pObj = (MMatchObject*)pServer->GetObject(uidPlayer);
        if (pObj)
        {
          pObj->PlayerWarsIdentifier = ID;
          MCommand* pSendCmd = pCommand->Clone();
          pServer->RouteToListener(pObj, pSendCmd);
        }
      }
      delete pCommand;
      m->pGroupA = pGroupA;
      m->pGroupB = pGroupB;
      WaitingMapSelectionGames.insert(map<unsigned long int, LadderGameMapVoteInfo*>::value_type(ID, m));
    }

Find (LaunchLadder - Add under)

    void MLadderMgr::UpdatePlayerVote(int VoteID, MMatchObject* pObj)
    {
      if (pObj->PlayerWarsIdentifier != -1)
      {
        map<unsigned long int, LadderGameMapVoteInfo*>::iterator i = WaitingMapSelectionGames.find(pObj->PlayerWarsIdentifier);
        if (i != WaitingMapSelectionGames.end())
        {
          LadderGameMapVoteInfo*  m = i->second;
          if (m)
          {
            if (pObj->LastVoteID != -1)
              m->Votes[pObj->LastVoteID]--;
            m->Votes[VoteID]++;
            pObj->LastVoteID = VoteID;
            pObj->bMatching = true;
          }
        }
      }
    }

    void MLadderMgr::UpdateMapCountDown(unsigned long int NowTime)
    {
      MMatchServer* pServer = MMatchServer::GetInstance();
      for (map<unsigned long int, LadderGameMapVoteInfo*>::iterator i = WaitingMapSelectionGames.begin(); i != WaitingMapSelectionGames.end();)
      {
        LadderGameMapVoteInfo* m = i->second;
        if (!m)
        {
          i = WaitingMapSelectionGames.erase(i);
          continue;
        }
        if ((NowTime - m->RegisterTime) >= 15000)
        {
          int winningmapindex = -1, winningindex = -1, votecount = 0;
          for (int a = 0; a < 3; a++)
          {
            if (m->Votes[a] == votecount)
            {
              votecount = m->Votes[a];
              winningmapindex = m->Maps[a];
              winningindex = a;
            }
            else if (m->Votes[a] >= votecount)
            {
              votecount = m->Votes[a];
              winningmapindex = m->Maps[a];
              winningindex = a;
            }
          }
          if (winningmapindex == -1)
            winningmapindex = m->Maps[RandomNumber(0, 2)];
          else
          {
            switch (winningindex)
            {
            case 0:
              if (m->Votes[winningindex] == m->Votes[1])
                winningmapindex = m->Maps[RandomNumber(0, 1)];
              else if (m->Votes[winningindex] == m->Votes[2])
                if (RandomNumber(0, 1) == 0)
                  winningmapindex = m->Maps[winningindex];
                else
                  winningmapindex = m->Maps[2];
              break;
            case 1:
              if (m->Votes[winningindex] == m->Votes[0])
                winningmapindex = m->Maps[RandomNumber(0, 1)];
              else if (m->Votes[winningindex] == m->Votes[2])
                if (RandomNumber(0, 1) == 0)
                  winningmapindex = m->Maps[winningindex];
                else
                  winningmapindex = m->Maps[2];
              break;
            case 2:
              if (m->Votes[winningindex] == m->Votes[1])
                winningmapindex = m->Maps[RandomNumber(1, 2)];
              else if (m->Votes[winningindex] == m->Votes[0])
                if (RandomNumber(0, 1) == 1)
                  winningmapindex = m->Maps[winningindex];
                else
                  winningmapindex = m->Maps[0];
              break;
            }
          }
          i = WaitingMapSelectionGames.erase(i);
          pServer->LadderGameLaunch(m->pGroupA, m->pGroupB, winningmapindex);
          continue;
        }
        else
        {
          MCommand* pCommand = pServer->CreateCommand(MC_MATCH_PLAYERWARS_VOTE_UPDATE, MUID(0, 0));
          pCommand->AddParameter(new MCmdParamInt(m->Votes[0]));
          pCommand->AddParameter(new MCmdParamInt(m->Votes[1]));
          pCommand->AddParameter(new MCmdParamInt(m->Votes[2]));
          for (list<MUID>::iterator i = m->pGroupA->GetPlayerListBegin(); i != m->pGroupA->GetPlayerListEnd(); i++)
          {
            MUID uidPlayer = (*i);
            MMatchObject* pObj = (MMatchObject*)pServer->GetObject(uidPlayer);
            if (pObj)
            {
              MCommand* pSendCmd = pCommand->Clone();
              pServer->RouteToListener(pObj, pSendCmd);
            }
          }
          for (list<MUID>::iterator i = m->pGroupB->GetPlayerListBegin(); i != m->pGroupB->GetPlayerListEnd(); i++)
          {
            MUID uidPlayer = (*i);
            MMatchObject* pObj = (MMatchObject*)pServer->GetObject(uidPlayer);
            if (pObj)
            {
              MCommand* pSendCmd = pCommand->Clone();
              pServer->RouteToListener(pObj, pSendCmd);
            }
          }
          delete pCommand;
        }
        i++;
      }
    }


Find(MLadderMgr::Tick - Replace)

    void MLadderMgr::Tick(unsigned long nTick)
    {
      if (nTick - GetLastTick() < GetTickInterval())
        return;
      else
        SetLastTick(nTick);

      CleaningGarbages();

      for (int i = 0; i < MLADDERTYPE_MAX; i++)
      {
        MakeMatch(MLADDERTYPE(i));
      }
      UpdateMapCountDown(timeGetTime());
      m_Stat.Tick(nTick);
    }

Find (unsigned long MLadderMgr::GetChecksum - Replace)

    unsigned long MLadderMgr::GetChecksum(int nFirstIndex, int nGroupCount)
    {
      unsigned long int nGroupListChecksum = 0;

      auto itorGroup = m_GroupList.begin();
      for (int i = 0; i < nFirstIndex; i++, itorGroup++)
      {
        if (itorGroup == m_GroupList.end()) return 0;
      }

      for (int i = 0; i < nGroupCount; i++)
      {
        if (itorGroup == m_GroupList.end()) return nGroupListChecksum;

        MLadderGroup* pGroup = (*itorGroup);
        nGroupListChecksum += pGroup->GetChecksum();
        itorGroup++;
      }

      return nGroupListChecksum;

    }


Find (#define MTIME_LADDER_DEFAULT_TICKINTERVAL - Replace)

    constexpr auto MTIME_LADDER_DEFAULT_TICKINTERVAL = 10000;

Open(MMatchChannel.cpp - nType == MCHANNEL_TYPE_PRESET || nType == MCHANNEL_TYPE_DUELTOURNAMENT - Replace)

	if (nType == MCHANNEL_TYPE_PRESET || nType == MCHANNEL_TYPE_DUELTOURNAMENT || nType == MCHANNEL_TYPE_PLAYERWARS)
	{
		if (!stricmp(m_szRuleName, MCHANNEL_RULE_NOVICE_STR))				m_nRuleType = MCHANNEL_RULE_NOVICE;
		else if (!stricmp(m_szRuleName, MCHANNEL_RULE_NEWBIE_STR))			m_nRuleType = MCHANNEL_RULE_NEWBIE;
		else if (!stricmp(m_szRuleName, MCHANNEL_RULE_ROOKIE_STR))			m_nRuleType = MCHANNEL_RULE_ROOKIE;
		else if (!stricmp(m_szRuleName, MCHANNEL_RULE_MASTERY_STR))			m_nRuleType = MCHANNEL_RULE_MASTERY;
		else if (!stricmp(m_szRuleName, MCHANNEL_RULE_ELITE_STR))			m_nRuleType = MCHANNEL_RULE_ELITE;
		else if (!stricmp(m_szRuleName, MCHANNEL_RULE_CHAMPION_STR))		m_nRuleType = MCHANNEL_RULE_CHAMPION;
		else if (!stricmp(m_szRuleName, MCHANNEL_RULE_QUEST_STR))			m_nRuleType = MCHANNEL_RULE_QUEST;
		else if (!stricmp(m_szRuleName, MCHANNEL_RULE_DUELTOURNAMENT_STR))	m_nRuleType = MCHANNEL_RULE_DUELTOURNAMENT;
		else if (!stricmp(m_szRuleName, MCHANNEL_RULE_SET1_STR))			m_nRuleType = MCHANNEL_RULE_SET1;
		else if (!stricmp(m_szRuleName, MCHANNEL_RULE_SET2_STR))			m_nRuleType = MCHANNEL_RULE_SET2;
		else if (!stricmp(m_szRuleName, MCHANNEL_RULE_SET3_STR))			m_nRuleType = MCHANNEL_RULE_SET3;
	}


Find(MMatchChannel::CheckLifePeriod() - Replace)

    bool MMatchChannel::CheckLifePeriod()
    {
      MCHANNEL_TYPE nType = GetChannelType();
      if (nType == MCHANNEL_TYPE_PRESET || nType == MCHANNEL_TYPE_DUELTOURNAMENT || nType == MCHANNEL_TYPE_PLAYERWARS) return true;

      if (GetObjCount() > 0) return true;
      if (GetEmptyPeriod() < MTICK_CHANNEL_EMPTY_PERIOD_LIMIT) return true;

      return false;
    }

Open(MMatchDBMgr.cpp - MatchDBMgr::MMatchDBMg - Place Above)

	TCHAR g_spInsertPWGameLog[] = _T("{CALL PWInsertGameLog('%s', '%s', %d, %d, %d)}");
	TCHAR g_spPlayerWarsOpen[] = _T("{CALL spPWOpen()}");

Find(MMatchDBMgr::LogCallback - Add under)

	bool MMatchDBMgr::InsertPWGameLog(TCHAR* Winners, TCHAR* Losers, int WinningScore, int LosingScore, int MapID){
		_STATUS_DB_START;
		if (!CheckOpen()) return false;
		CString strSQL;
		try {
			strSQL.Format(g_spInsertPWGameLog, m_DBFilter.Filtering(Winners).c_str(), m_DBFilter.Filtering(Losers).c_str(), WinningScore, LosingScore, MapID);
			m_DB.ExecuteSQL(strSQL);
		}
		catch (CDBException* e) {
			ExceptionHandler(strSQL, e);
			return false;
		}
		_STATUS_DB_END(1);
		return true;
	}
	int MMatchDBMgr::IsPlayerWarsOpen()
	{
		_STATUS_DB_START;
		if (!CheckOpen()) return -1;
		CString strSQL;
		strSQL.Format(g_spPlayerWarsOpen);
		CODBCRecordset rs(&m_DB);
		try {
			rs.Open(strSQL, CRecordset::forwardOnly, CRecordset::readOnly);
		}
		catch (CDBException* e) {
			ExceptionHandler(strSQL, e);
			return -1;
		}
		if ((rs.IsOpen() == FALSE) || (rs.GetRecordCount() <= 0) || (rs.IsBOF() == TRUE)) {
			return -1;
		}
		return rs.Field("Opened").AsInt();
		_STATUS_DB_END(0);

	}

Find (MMatchDBMgr::GetDuelTournamentSideRankingInfo - Add under)

	bool MMatchDBMgr::UpdatePlayerWarsCharInfo(DWORD dwCID, int Win, int Loss, int Draw, int Score, int mode)
	{
		_STATUS_DB_START;
		if (!CheckOpen())
			return false;

		CString strSQL;

		try
		{
			strSQL.Format(g_spUpdatePWCharacterInfo, dwCID, Win, Loss, Draw, Score, mode);

			m_DB.ExecuteSQL(strSQL);
		}
		catch (CDBException* e)
		{

			ExceptionHandler(strSQL, e);
			return false;
		}

		_STATUS_DB_END(51);

		return true;
	}

	bool MMatchDBMgr::GetPlayerWarsCharInfo(DWORD dwCID, PlayerWarsCharInfo *pPWCharInfo)
	{
		_STATUS_DB_START;
		if (!CheckOpen()) return false;

		CString strSQL;
		strSQL.Format(g_spGetPWCharacterInfo, dwCID);
		CODBCRecordset rs(&m_DB);

		try {
			rs.Open(strSQL, CRecordset::forwardOnly, CRecordset::readOnly);
		}
		catch (CDBException* e) {

			ExceptionHandler(strSQL, e);
			return false;
		}

		if ((rs.IsOpen() == FALSE) || (rs.GetRecordCount() <= 0) || (rs.IsBOF() == TRUE)) {
			return false;
		}
		pPWCharInfo->Ranking = rs.Field("Ranking").AsInt();
		pPWCharInfo->Wins = rs.Field("Wins").AsInt();
		pPWCharInfo->Losses = rs.Field("Losses").AsInt();
		pPWCharInfo->Draws = rs.Field("Draws").AsInt();
		pPWCharInfo->Score = rs.Field("Score").AsInt();
		_STATUS_DB_END(51);

		return true;
	}

	bool MMatchDBMgr::GetPlayerWarsSideRankingInfo(DWORD dwCID, list<PWRankingInfo*> *pRankingList)
	{
		_STATUS_DB_START;
		CString strSQL;
		strSQL.Format(g_PWGetSideRanking, dwCID);
		CODBCRecordset rs(&m_DB);

		try {
			rs.Open(strSQL, CRecordset::forwardOnly, CRecordset::readOnly);
		}
		catch (CDBException* e) {

			ExceptionHandler(strSQL, e);
			return false;
		}

		if ((rs.IsOpen() == FALSE)) {
			return false;
		}

		for (int nIndex = 0; !rs.IsEOF(); rs.MoveNext())
		{
			PWRankingInfo *pInfo = new PWRankingInfo;

			strcpy(pInfo->m_szCharName, rs.Field("Name").AsString());
			pInfo->m_nWins = rs.Field("Wins").AsInt();
			pInfo->m_nLoses = rs.Field("Losses").AsInt();
			pInfo->m_nRanking = rs.Field("Ranking").AsInt();
			pRankingList->push_back(pInfo);
		}

		_STATUS_DB_END(51);
		return true;
	}


Find (MMatchDBMgr::RewardCharBattleTimeReward - Add under)

	TCHAR spUpdatePlayerWars[] = _T("{CALL spPWRegularUpdateRanking}");

	bool MMatchDBMgr::UpdatePlayerWars()
	{
		_STATUS_DB_START;
		if (!CheckOpen()) return false;

		CString strSQL;
		try
		{
			strSQL.Format(spUpdatePlayerWars);
			m_DB.ExecuteSQL(strSQL);
		}
		catch (CDBException* e)
		{
			ExceptionHandler(strSQL, e);
			return false;
		}

		_STATUS_DB_END(36);
		return true;
	}

Open(MMatchObject.cpp - m_pDuelTournamentCharInfo = NULL; - Add under)

	m_nLastCheckBattleTimeReward = 0;
	PlayerWarsFriend = MUID(0, 0);
	PwState = NotInvited;
	PlayerWarsIdentifier = -1;
	LastVoteID = -1;
	bMatching = false;

Find (MMatchObject::~MMatchObject() - Replace)

	MMatchObject::~MMatchObject()
	{
		FreeCharInfo();
		FreeFriendInfo();
		FreeDuelTournamentInfo();
		FreePlayerWarsInfo();

		LoginNotCompleted();
	}

Find (MMatchObject::FreeFriendInfo() - Add under)

	void MMatchObject::FreePlayerWarsInfo()
	{
		if (m_pPlayerWarsCharInfo)
		{
			m_pPlayerWarsCharInfo = NULL;
		}
	}

Find (MMatchObject::OnEnterBattle() - Replace)

	void MMatchObject::OnEnterBattle()
	{	
		SetAlive(false);
		SetKillCount(0);
		SetDeathCount(0);
		SetAllRoundDeathCount(0);	
		SetAllRoundKillCount(0);
		SetEnterBattle(true);
		SetBattleTimeReward(true);
		MMatchChannel* pChannel = MGetMatchServer()->FindChannel(GetChannelUID());
		if (pChannel && pChannel->GetChannelType() != MCHANNEL_TYPE_PLAYERWARS && pChannel && pChannel->GetChannelType() != MCHANNEL_TYPE_CLAN)
		ResetGamePlayInfo();
	}

Find (MMatchObject::OnLeaveBattle() - Replace)

	void MMatchObject::OnLeaveBattle()
	{	
		SetKillCount(0);
		SetDeathCount(0);
		SetAlive(false);
		SetStageState(MOSS_NONREADY);
		SetLaunchedGame(false);
		MMatchChannel* pChannel = MGetMatchServer()->FindChannel(GetChannelUID());
		if (pChannel && pChannel->GetChannelType() != MCHANNEL_TYPE_PLAYERWARS && pChannel && pChannel->GetChannelType() != MCHANNEL_TYPE_CLAN)
		SetEnterBattle(false);
		SetBattleTimeReward(false);
	}

Find (MMatchObject::SetCharInfo - Add under)

	void MMatchObject::SetPlayerWarsCharInfo(PlayerWarsCharInfo *pPWCharInfo)
	{
		// ÀÌ¹Ì ÀÖ´Â Á¤º¸¸é ¾îÂ¼ÁÒ? -.,-;
		// ±×·² ÀÏÀº ¾ø°ÚÁö¸¸.. Áö¿ì°í ´Ù½Ã ÇÒ´çÇÏÀÚ!
		if (m_pPlayerWarsCharInfo) {
			delete m_pPlayerWarsCharInfo;
			m_pPlayerWarsCharInfo = NULL;
		}

		m_pPlayerWarsCharInfo = new PlayerWarsCharInfo();
		memcpy(m_pPlayerWarsCharInfo, pPWCharInfo, sizeof(PlayerWarsCharInfo));;
	}

Open(MMatchRule.cpp - OnCheckBattleTimeOut - Add under)

	int nGameType = GetStage()->GetStageType();
	int nLimitTime = 0; // just 4 declare?

	switch (nGameType)
	{
	case MST_LADDER:
	case MST_PLAYERWARS:
		nLimitTime = GetStage()->GetStageSetting()->GetLimitTime() * 60 * 1000;
		//MMatchServer::GetInstance()->LOG(MMatchServer::LOG_PROG,("ITS PASSING BY LADDER OR CW EVENT\n"));
		break;
	default:
		nLimitTime = GetStage()->GetStageSetting()->GetLimitTime() * 60 * 1000;
		//MMatchServer::GetInstance()->LOG(MMatchServer::LOG_PROG,("NORMAL MATCH \n"));
		break;
	}

Open(MMatchServer.cpp - m_dwNonBlockCount = 0; - Add under)

	CanPlayerWars = true;
	IsRunningCheck = false;

Find (bool bIsDuelTournament = false; - Add under)

	bool	bIsPlayerWars = false;

Find (childElement.GetAttribute(&bIsDuelTournament, "IsDuelTournament"); - Add under)

	childElement.GetAttribute(&bIsPlayerWars, "IsPlayerWars");

Find (nChannelType = MCHANNEL_TYPE_DUELTOURNAMENT; - Add under)


	else if (bIsPlayerWars)
		nChannelType = MCHANNEL_TYPE_PLAYERWARS;

Find ((MGetServerConfig()->GetServerMode() == MSM_CLAN) - Replace)

	if (MGetServerConfig()->GetServerMode() == MSM_CLAN)
	{
		GetLadderMgr()->Tick(nGlobalClock);
		GetPlayerWarsMgr()->Tick();
	}

Find ((NULL != pObj->GetCharInfo()) - Replace)

	if (NULL != pObj->GetCharInfo())
	{
		pObj->FreeCharInfo();
		pObj->FreeDuelTournamentInfo();
		pObj->FreeFriendInfo();
		pObj->FreePlayerWarsInfo();
	}

Open(MMatchServer_Async.cpp - Add)

	#include "MAsyncDBJob_PlayerWars.h"

Find (switch (pJob->GetJobID()) - Add under)

		case MASYNCJOB_UPDATE_PW_INFO:
		{
			OnAsyncUpdatePlayerWars(pJob);
		}
		break;
		case MASYNCJOB_GET_PW_INFO:
		{
			OnAsyncGetPlayerWarsCharInfo(pJob);
		}
		break;
		case MASYNCJOB_GET_PW_SIDE_RANKING:
		{
			OnAsyncResponse_GetPlayerWarsSideRanking(pJob);
		}
		break;

Find (MMatchServer::OnAsyncGetAccountCharList - Add above)

	void MMatchServer::OnAsyncUpdatePlayerWars(MAsyncJob* pJobResult)
	{
		MAsyncDBJob_UpdatePlayerWarsCharInfo* pJob = (MAsyncDBJob_UpdatePlayerWarsCharInfo*)pJobResult;

		if (pJob->GetResult() != MASYNC_RESULT_SUCCEED) {
			char szTime[128] = "";
			_strtime(szTime);

			mlog("[%s] Async DB Query(UpdatePlayerWars) Failed\n", szTime);
			return;
		}
	}


Open(MMatchServer_Channel.cpp - Replace)

		if (nChannelType == MCHANNEL_TYPE_DUELTOURNAMENT)
			return false;
		if (nChannelType == MCHANNEL_TYPE_PLAYERWARS)
			return false;

Open(MMatchServer_Char.cpp - Add)

	#include "MAsyncDBJob_PlayerWars.h"

Open(MMatchServer_Ladder.cpp - Replace)
  
	  void MMatchServer::LadderGameLaunch(MLadderGroup* pGroupA, MLadderGroup* pGroupB, int nMapID)
	{
		MUID uidStage = MUID(0, 0);
		if (StageAdd(NULL, "LADDER_GAME", true, "", &uidStage) == false) {
			GetLadderMgr()->CancelChallenge(pGroupA->GetID(), "");
			GetLadderMgr()->CancelChallenge(pGroupB->GetID(), "");
			return;
		}
		MMatchStage* pStage = FindStage(uidStage);
		if (pStage == NULL) {
			GetLadderMgr()->CancelChallenge(pGroupA->GetID(), "");
			GetLadderMgr()->CancelChallenge(pGroupB->GetID(), "");
			return;
		}

		for (list<MUID>::iterator i = pGroupA->GetPlayerListBegin(); i != pGroupA->GetPlayerListEnd(); i++)
		{
			MUID uidPlayer = (*i);
			MMatchObject* pObj = (MMatchObject*)GetObject(uidPlayer);
			if (pObj)
			{
				pObj->PlayerWarsIdentifier = -1;
				pObj->LastVoteID = -1;
				LadderJoin(uidPlayer, uidStage, MMT_RED);
			}
		}
		for (list<MUID>::iterator i = pGroupB->GetPlayerListBegin(); i != pGroupB->GetPlayerListEnd(); i++)
		{
			MUID uidPlayer = (*i);
			MMatchObject* pObj = (MMatchObject*)GetObject(uidPlayer);
			if (pObj)
			{
				pObj->PlayerWarsIdentifier = -1;
				pObj->LastVoteID = -1;
				LadderJoin(uidPlayer, uidStage, MMT_BLUE);
			}
		}
		//////////////////////////////////////////////////////////////////////////////
		int nRandomMap = 0;
		MBaseTeamGameStrategy* pTeamGameStrategy = MBaseTeamGameStrategy::GetInstance(MGetServerConfig()->GetServerMode());

		if (pTeamGameStrategy)
		{
			nRandomMap = pTeamGameStrategy->GetRandomMap((int)pGroupA->GetPlayerCount());
		};

		MMATCH_GAMETYPE nGameType = MMATCH_GAMETYPE_DEATHMATCH_TEAM;

		pStage->SetStageType(MST_LADDER);
		pStage->ChangeRule(nGameType);

		if (pTeamGameStrategy)
		{
			MMatchLadderTeamInfo a_RedLadderTeamInfo, a_BlueLadderTeamInfo;
			pTeamGameStrategy->SetStageLadderInfo(&a_RedLadderTeamInfo, &a_BlueLadderTeamInfo, pGroupA, pGroupB);

			pStage->SetLadderTeam(&a_RedLadderTeamInfo, &a_BlueLadderTeamInfo);
		};
		MMatchStageSetting* pSetting = pStage->GetStageSetting();
		pSetting->SetMasterUID(MUID(0, 0));

		pSetting->SetMapIndex(nMapID);

		pSetting->SetMapIndex(nRandomMap);

		pSetting->SetGameType(nGameType);
		pSetting->SetLimitTime(3 * 60 * 1000);
		pSetting->SetRoundMax(99);
		pSetting->SetAntiLead(pGroupA->GetAntiLeadMatching());
		MCommand* pCmd = CreateCmdResponseStageSetting(uidStage);
		RouteToStage(uidStage, pCmd);

		if ((MGetMapDescMgr()->MIsCorrectMap(nMapID)) && (MGetGameTypeMgr()->IsCorrectGameType(nGameType)))
		{
			if (pStage->StartGame(MGetServerConfig()->IsUseResourceCRC32CacheCheck()) == true) {
				ReserveAgent(pStage);

				MMatchObjectCacheBuilder CacheBuilder;
				CacheBuilder.Reset();
				for (MUIDRefCache::iterator i = pStage->GetObjBegin(); i != pStage->GetObjEnd(); i++) {
					MUID uidObj = (MUID)(*i).first;
					MMatchObject* pScanObj = (MMatchObject*)GetObject(uidObj);
					if (pScanObj) {
						CacheBuilder.AddObject(pScanObj);
					}
				}
				MCommand* pCmdCacheAdd = CacheBuilder.GetResultCmd(MATCHCACHEMODE_UPDATE, this);
				RouteToStage(pStage->GetUID(), pCmdCacheAdd);
				/////////////////////////////////////////////////////////////////////////////////////////////
				MCommand* pCmd = CreateCommand(MC_MATCH_LADDER_LAUNCH, MUID(0, 0));
				pCmd->AddParameter(new MCmdParamUID(uidStage));
				pCmd->AddParameter(new MCmdParamStr(const_cast<char*>(pStage->GetMapName())));
				pCmd->AddParameter(new MCmdParamBool(false));
				RouteToStage(uidStage, pCmd);
			}
			else {
				GetLadderMgr()->CancelChallenge(pGroupA->GetID(), "");
				GetLadderMgr()->CancelChallenge(pGroupB->GetID(), "");
			}
		}
	}


Open(MMatchServer_OnCommand.cpp - MC_MATCH_LADDER_REQUEST_CANCEL_CHALLENGE - Replace)

	case MC_MATCH_LADDER_REQUEST_CANCEL_CHALLENGE:
	{
		bool PlayerWars;
		pCommand->GetParameter(&PlayerWars, 0, MPT_BOOL);
		if (PlayerWars)
		{
			GetPlayerWarsMgr()->RemovePlayer(pCommand->GetSenderUID());
		}
		else
			OnLadderRequestCancelChallenge(pCommand->GetSenderUID());
	}
	break;

Add those under

	case MC_MATCH_PLAYERWARS_VOTE:
	{
		MMatchObject* pObj = (MMatchObject*)GetObject(pCommand->GetSenderUID());
		if (pObj)
		{
			int Map;
			if (pCommand->GetParameter(&Map, 0, MPT_INT) == false) break;
			if (Map < 0 || Map > 2) return true;
			MMatchChannel* chan = MGetMatchServer()->FindChannel(pObj->GetChannelUID());
			if (chan && chan->GetChannelType() == MCHANNEL_TYPE_PLAYERWARS || chan && chan->GetChannelType() == MCHANNEL_TYPE_PLAYERWARS)
				GetPlayerWarsMgr()->UpdatePlayerVote(Map, pObj);
			else
				GetLadderMgr()->UpdatePlayerVote(Map, pObj);
		}
	}
	break;

		case MC_MATCH_JOIN_PLAYERWARS:
		{
			MMatchObject* pObj = (MMatchObject*)GetObject(pCommand->GetSenderUID());
			if (pObj)
			{

				int Lead, GameType;
				if (pCommand->GetParameter(&Lead, 0, MPT_INT) == false) break;
				if (pCommand->GetParameter(&GameType, 1, MPT_INT) == false) break;
				if (GameType <= -1 || GameType >= MPLAYERWARSTYPE_MAX) break;
				bool Leada = false;
				if (Lead == 1) Leada = true;
				if (CanPlayerWars == false)
					Announce(pObj, "Player Wars Scores Are Resetting...");
				else
				{
					bool DoesExist = false;
					for (int i = 0; i < MPLAYERWARSTYPE_MAX; i++)
						if (GetPlayerWarsMgr()->GetWaitingGames((PlayerWars)i)->IsPlayerAlreadyQueued(pObj->GetUID()) == true)
							DoesExist = true;
					if (DoesExist == true)
						return true;
					else
					{
						GetPlayerWarsMgr()->GetWaitingGames((PlayerWars)GameType)->AddPlayer(pObj->GetUID());
						if (pObj->PwState == MMatchObject::Inviter)
						{
							MMatchObject* pFObj = (MMatchObject*)GetObject(pObj->PlayerWarsFriend);
							if (!pFObj)
							{
								pObj->PwState = MMatchObject::NotInvited;
								pObj->PlayerWarsFriend = MUID(0, 0);
								return true;
							}
							MMatchChannel* chan = FindChannel(pFObj->GetChannelUID());
							if (chan && chan->GetChannelType() == MCHANNEL_TYPE_PLAYERWARS)
							{
								bool DoesExist = false;
								for (int i = 0; i < MPLAYERWARSTYPE_MAX; i++)
									if (GetPlayerWarsMgr()->GetWaitingGames((PlayerWars)i)->IsPlayerAlreadyQueued(pFObj->GetUID()) == true)
										DoesExist = true;
								if (DoesExist == false)
								{
									MCommand* pCommand = MMatchServer::GetInstance()->CreateCommand(MC_MATCH_PLAYERWARS_INVITED, MUID(0, 0));
									MMatchServer::GetInstance()->RouteToListener(pFObj, pCommand);
									char buf[256];
									sprintf(buf, "%s Has invited you.", pObj->GetCharInfo()->m_szName);
									Announce(pFObj, buf);
									GetPlayerWarsMgr()->GetWaitingGames((PlayerWars)GameType)->AddPlayer(pFObj->GetUID());
								}
							}
						}
					}
				}
			}
		}
		break;


Open(MMatchServer_Stage.cpp - MMatchServer::OnStageTeam - Replace)


	void MMatchServer::OnStageTeam(const MUID& uidPlayer, const MUID& uidStage, MMatchTeam nTeam)
	{
		MMatchStage* pStage = FindStage(uidStage);
		if (pStage == NULL) return;

		MMatchObject* pChar = GetObject(uidPlayer);
		if (pChar == NULL) return;
		if (pStage->GetStageType() == MST_LADDER && !IsAdminGrade(pChar) && !pChar->GetAccountInfo()->m_nUGrade == MMUG_DEVELOPER && !pChar->GetAccountInfo()->m_nUGrade == MMUG_DEVELOPER || pStage->GetStageType() == MST_PLAYERWARS && !IsAdminGrade(pChar) && !pChar->GetAccountInfo()->m_nUGrade == MMUG_DEVELOPER) return;
		if (pStage->GetStageSetting()->GetGameType() == MMATCH_GAMETYPE_DEATHMATCH_TEAM &&
			pChar->GetTeam() == nTeam) {
			nTeam = MMT_RED;
		}
		StageTeam(uidPlayer, uidStage, nTeam);
	}

Find(pStage->GetStageType() == MST_LADDER - Replace)


	if (pStage->GetStageType() == MST_LADDER || pStage->GetStageType() == MST_PLAYERWARS)
	{
		sprintf(szMsg, "%s%d", MTOK_ANNOUNCE_PARAMSTR, MERR_CANNOT_VOTE_LADERGAME);
		Announce(uidPlayer, szMsg);

		return;
	}

Find (MGetMapDescMgr()->MIsCorrectMap(nMapID)) && (MGetGameTypeMgr()->IsCorrectGameType(nGameType) - Replace)

	if ((MGetMapDescMgr()->MIsCorrectMap(nMapID)) && (MGetGameTypeMgr()->IsCorrectGameType(nGameType)))
	{
		if (pStage->GetStageType() != MST_LADDER && pStage->GetStageType() != MST_PLAYERWARS)
		{
			MMatchObject* pMaster = GetObject(pStage->GetMasterUID());

			MAsyncDBJob_InsertGameLog* pJob = new MAsyncDBJob_InsertGameLog(uidStage);
			pJob->Input(pMaster == NULL ? 0 : pMaster->GetCharInfo()->m_nCID,
				MGetMapDescMgr()->GetMapName(nMapID),
				MGetGameTypeMgr()->GetInfo(MMATCH_GAMETYPE(nGameType))->szGameTypeStr);
			PostAsyncJob(pJob);
		}
	}

Open(MMatchStage.cpp - case MST_LADDER: - Add under)

	case MST_PLAYERWARS:
		{
			m_StageSetting.SetTeamWinThePoint(true);
		}
		break;

Find(m_nStageType == MST_LADDER) && - Replace)

		if ((m_nStageType == MST_LADDER) && (GetStageSetting()->IsTeamPlay()) || m_nStageType == MST_PLAYERWARS && (GetStageSetting()->IsTeamPlay()))
		{

Find (MBaseTeamGameStrategy* pTeamGameStrategy = MBaseTeamGameStrategy::GetInstance(MGetServerConfig()->GetServerMode()); - Replace)

			if (m_nStageType == MST_PLAYERWARS)
			{
				MMatchTeam LosingTeam = nWinnerTeam == MMT_RED ? MMT_BLUE : MMT_RED;
				MMatchServer::GetInstance()->SendPlayerWarsRewards(PlayerWarsList, bIsDrawGame, nWinnerTeam, GetTeamScore(nWinnerTeam), GetTeamScore(LosingTeam), GetStageSetting()->GetMapIndex());
			}
			else
			{
				MBaseTeamGameStrategy* pTeamGameStrategy = MBaseTeamGameStrategy::GetInstance(MGetServerConfig()->GetServerMode());
				if (pTeamGameStrategy)
				{
					/*pTeamGameStrategy->SavePointOnFinishGame(this, nWinnerTeam, bIsDrawGame, &m_Teams[MMT_RED].LadderInfo,
						&m_Teams[MMT_BLUE].LadderInfo, GetStageSetting()->GetGameType());*/

					pTeamGameStrategy->SavePointOnFinishGame(this, nWinnerTeam, bIsDrawGame, &m_Teams[MMT_RED].LadderInfo,
						&m_Teams[MMT_BLUE].LadderInfo), GetStageSetting()->GetGameType();
				};
			}
		}
	}

Find (void MMatchStage::ShuffleTeamMembers() - Replace)

	void MMatchStage::ShuffleTeamMembers()
	{
		// ·¡´õ°ÔÀÓÀÌ³ª ÆÀ°ÔÀÓÀÌ ¾Æ´Ï¸é ÇÏÁö ¾Ê´Â´Ù.
		if ((m_nStageType == MST_LADDER) || (m_nStageType == MST_PLAYERWARS) || (m_StageSetting.IsTeamPlay() == false)) return;
		if (m_ObjUIDCaches.empty()) return;

		int nTeamMemberCount[MMT_END] = {0, };
		MMatchTeam nWinnerTeam;

		GetTeamMemberCount(&nTeamMemberCount[MMT_RED], &nTeamMemberCount[MMT_BLUE], NULL, true);
		if (nTeamMemberCount[MMT_RED] >= nTeamMemberCount[MMT_BLUE]) nWinnerTeam = MMT_RED; 
		else nWinnerTeam = MMT_BLUE;

		int nShuffledMemberCount = abs(nTeamMemberCount[MMT_RED] - nTeamMemberCount[MMT_BLUE]) / 2;
		if (nShuffledMemberCount <= 0) return;

		vector<MMatchObject*> sortedObjectList;

		for (MUIDRefCache::iterator i=m_ObjUIDCaches.begin(); i!=m_ObjUIDCaches.end(); i++) 
		{
			MMatchObject* pObj = (MMatchObject*)(*i).second;

			if ((pObj->GetEnterBattle() == true) && (pObj->GetGameInfo()->bJoinedGame == true))
			{
				if ((pObj->GetTeam() == nWinnerTeam) && (!IsAdminGrade(pObj)))
				{
					sortedObjectList.push_back(pObj);
				}
			}
		}

		std::sort(sortedObjectList.begin(), sortedObjectList.end(), moreTeamMemberKills);

		int nCounter = 0;
		for (vector<MMatchObject*>::iterator itor = sortedObjectList.begin(); itor != sortedObjectList.end(); ++itor)
		{
			MMatchObject* pObj = (*itor);
			PlayerTeam(pObj->GetUID(), NegativeTeam(MMatchTeam(pObj->GetTeam())));
			nCounter++;

			if (nCounter >= nShuffledMemberCount) break;
		}

		// ¸Þ¼¼Áö Àü¼Û
		MCommand* pCmd = MMatchServer::GetInstance()->CreateCommand(MC_MATCH_RESET_TEAM_MEMBERS, MUID(0,0));
		int nMemberCount = (int)m_ObjUIDCaches.size();
		void* pTeamMemberDataArray = MMakeBlobArray(sizeof(MTD_ResetTeamMembersData), nMemberCount);

		nCounter = 0;
		for (MUIDRefCache::iterator i=m_ObjUIDCaches.begin(); i!=m_ObjUIDCaches.end(); i++) 
		{
			MMatchObject* pObj = (MMatchObject*)(*i).second;
			MTD_ResetTeamMembersData* pNode = (MTD_ResetTeamMembersData*)MGetBlobArrayElement(pTeamMemberDataArray, nCounter);
			pNode->m_uidPlayer = pObj->GetUID();
			pNode->nTeam = (char)pObj->GetTeam();

			nCounter++;
		}

		pCmd->AddParameter(new MCommandParameterBlob(pTeamMemberDataArray, MGetBlobArraySize(pTeamMemberDataArray)));
		MEraseBlobArray(pTeamMemberDataArray);
		MMatchServer::GetInstance()->RouteToBattle(GetUID(), pCmd);
	}

Find (MMatchStage::CheckAutoTeamBalancing() - Replace)

	bool MMatchStage::CheckAutoTeamBalancing()
	{
		if ((m_nStageType == MST_LADDER) || (m_nStageType == MST_PLAYERWARS) || (m_StageSetting.IsTeamPlay() == false)) return false;
		if (m_StageSetting.GetAutoTeamBalancing() == false) return false;

		int nMemberCount[MMT_END] = {0, };
		GetTeamMemberCount(&nMemberCount[MMT_RED], &nMemberCount[MMT_BLUE], NULL, true);

		// 2¸í ÀÌ»ó ÀÎ¿ø¼ö°¡ Â÷ÀÌ³ª°í ÀÎ¿ø¼ö ¸¹Àº ÆÀÀÌ 3¿¬½ÂÀÌ»ó °è¼ÓµÉ °æ¿ì ÆÀÀ» ¼¯´Â´Ù.
		const int MEMBER_COUNT = 2;
		const int SERIES_OF_VICTORIES = 3;

		//	const int MEMBER_COUNT = 1;
		//	const int SERIES_OF_VICTORIES = 2;

		if ( ((nMemberCount[MMT_RED] - nMemberCount[MMT_BLUE]) >= MEMBER_COUNT) && 
			(m_Teams[MMT_RED].nSeriesOfVictories >= SERIES_OF_VICTORIES) )
		{
			return true;
		}
		else if ( ((nMemberCount[MMT_BLUE] - nMemberCount[MMT_RED]) >= MEMBER_COUNT) && 
			(m_Teams[MMT_BLUE].nSeriesOfVictories >= SERIES_OF_VICTORIES) )
		{
			return true;
		}

		return false;
	}

Open(MSharedCommandTable.cpp - Add)

	C(MC_MATCH_JOIN_PLAYERWARS, "knaw65goag", "jnaaw", MCDT_MACHINE2MACHINE);//Playerwars.join
		P(MPT_INT, "Lead")
		P(MPT_INT, "GameType")

Find (MC_MATCH_LADDER_LAUNCH - Replace)

		C(MC_MATCH_LADDER_LAUNCH, "Ladder.Launch", "Launch Ladder Game", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage")
			P(MPT_STR, "MapName")
			P(MPT_BOOL, "PlayerWars")

Find( MC_MATCH_REPORT - Add under)

			C(MC_MATCH_PLAYERWARS_RANDOM_MAPS, "Maps", "Maps", MCDT_MACHINE2MACHINE)
				P(MPT_INT, "1");
				P(MPT_INT, "2");
				P(MPT_INT, "3");
			C(MC_MATCH_PLAYERWARS_VOTE, "Maps", "Maps", MCDT_MACHINE2MACHINE)
				P(MPT_INT, "Map");
			C(MC_MATCH_PLAYERWARS_VOTE_UPDATE, "Maps", "Maps", MCDT_MACHINE2MACHINE)
				P(MPT_INT, "1");
				P(MPT_INT, "2");
				P(MPT_INT, "3");
				C(MC_MATCH_PLAYERWARS_FRIENDINVITE, "InviteFriend", "InviteFriend", MCDT_MACHINE2MACHINE)
					P(MPT_STR, "name");
				C(MC_MATCH_PLAYERWARS_FRIENDACCEPT, "AcceptFriend", "AcceptFriend", MCDT_MACHINE2MACHINE)
					C(MC_MATCH_PLAYERWARS_FRIENDLEAVE, "LeaveFriend", "LeaveFriend", MCDT_MACHINE2MACHINE)
					C(MC_MATCH_PLAYERWARS_INVITED, "InvitedPlayer", "InvitedPlayer", MCDT_MACHINE2MACHINE)
					C(MC_ADMIN_RESPONSE_KICK_PLAYER, "Admin.ResponseKickPlayer", "Response Kick Player", MCDT_MACHINE2MACHINE)
					P(MPT_INT, "Result");

Open(MTeamGameStrategy.cpp - GetRandomMap - Add under)

	int MLadderGameStrategy::GetPlayerWarsRandomMap(int nTeamMember)
	{
		int nVecIndex = 0;
		int nMaxSize = 0;
		switch (nTeamMember)
		{
		case 2:
			nVecIndex = MLADDERTYPE_NORMAL_2VS2;
			break;
		case 3:
			nVecIndex = MLADDERTYPE_NORMAL_3VS3;
			break;
		case 4:
			nVecIndex = MLADDERTYPE_NORMAL_4VS4;
			break;
		};

		nMaxSize = (int)m_RandomMapVec[nVecIndex].size();

		int nRandomMapIndex = 0;
		int nRandomMap = 0;

		if (nMaxSize != 0) {
			nRandomMapIndex = rand() % nMaxSize;
			nRandomMap = m_RandomMapVec[nVecIndex][nRandomMapIndex];
		}

		return nRandomMap;
	}

	int MClanGameStrategy::GetPlayerWarsRandomMap(int nTeamMember)
	{
		int nVecIndex = 0;
		int nMaxSize = 0;
		switch (nTeamMember)
		{
		case 1:
			nVecIndex = MLADDERTYPE_NORMAL_1VS1;
			break;
		case 2:
			nVecIndex = MLADDERTYPE_NORMAL_2VS2;
			break;
		case 3:
			nVecIndex = MLADDERTYPE_NORMAL_3VS3;
			break;
		case 4:
			nVecIndex = MLADDERTYPE_NORMAL_4VS4;
			break;
		};

		nMaxSize = (int)m_RandomMapVec[nVecIndex].size();

		int nRandomMapIndex = 0;
		int nRandomMap = 0;

		if (nMaxSize != 0) {
			nRandomMapIndex = rand() % nMaxSize;
			nRandomMap = m_RandomMapVec[nVecIndex][nRandomMapIndex];
		}

		return nRandomMap;
	}

Open(ZChat_Cmds.cpp)

	void ChatCmd_PlayerWarsInvite(const char* line, const int argc, char **const argv);
	void ChatCmd_PlayerWarsAccept(const char* line, const int argc, char **const argv);
	void ChatCmd_PlayerWarsLeave(const char* line, const int argc, char **const argv);
	void ChatCmd_PlayerWarsHelp(const char* line, const int argc, char **const argv);

Part 2

	void ChatCmd_PlayerWarsAccept(const char* line, const int argc, char **const argv)
	{
		ZPostPlayerWarsAccept();
	}

	void ChatCmd_PlayerWarsLeave(const char* line, const int argc, char **const argv)
	{
		ZPostPlayerWarsLeave();
	}

	void ChatCmd_PlayerWarsHelp(const char* line, const int argc, char **const argv)
	{
		char szBuf[1024] = "";
		sprintf(szBuf, "Commands: /pwaccept, /pwleave, /pwinvite <charname>");
		ZChatOutput(szBuf, ZChat::CMT_SYSTEM);
	}

Open(ZCombatInterface.cpp - ZCombatInterface::Update - Replace)

	if (m_bShowResult)
	{
		if (timeGetTime() > m_nReservedOutTime)
		{
			if (ZGetGameClient()->IsLadderGame()|| 
				ZGetGameClient()->IsDuelTournamentGame() || 
				ZGetGameClient()->IsPlayerWars())
				ZChangeGameState(GUNZ_LOBBY);
			else
				ZChangeGameState(GUNZ_STAGE);
		}
	}

Find(bClanGame = ZGetGameClient()->IsLadderGame(); - Replace)

	bool bClanGame = ZGetGameClient()->IsLadderGame();
	bool IsTeamPlay = ZGetGame()->GetMatch()->IsTeamPlay();
	bool bPlayerWars = ZGetGameClient()->IsPlayerWars();

Find(bClanGame - Replace)

	char szText[256];
	int nRed = 0, nBlue = 0;
	if (bClanGame || bPlayerWars)
	{
		for (ZCharacterManager::iterator itor = ZGetCharacterManager()->begin();
			itor != ZGetCharacterManager()->end(); ++itor)
		{
			ZCharacter* pCharacter = (*itor).second;

			if (pCharacter->GetTeamID() == MMT_BLUE) nBlue++;
			if (pCharacter->GetTeamID() == MMT_RED) nRed++;
		}
		if (bPlayerWars)
			sprintf(szText, "Ladder (%d) : (%d)", nRed, nBlue);
		else
		{
			switch (ZGetGame()->GetMatch()->GetMatchType())
			{
			case MMATCH_GAMETYPE_ASSASSINATE:
				sprintf(szText, "Clan War Assassinate %d:%d (%s vs %s)", nRed, nBlue, m_szRedClanName, m_szBlueClanName);
				break;
			case MMATCH_GAMETYPE_GLADIATOR_TEAM:
				sprintf(szText, "Clan War Gladiator %d:%d (%s vs %s)", nRed, nBlue, m_szRedClanName, m_szBlueClanName);
				break;
			default:
				sprintf(szText, "Clan War %d:%d (%s vs %s)", nRed, nBlue, m_szRedClanName, m_szBlueClanName);
				break;
			}
		}
		//char nvsn[32];
		//sprintf(nvsn,"%d:%d",nRed,nBlue);
		//ZTransMsg( szText, MSG_GAME_SCORESCREEN_STAGENAME, 3, nvsn, m_szRedClanName, m_szBlueClanName );

	}
	else
	{
		// Å¬·£ÀüÀÌ ¾Æ´Ï¸é ¹æÁ¦¸¦ Ç¥½ÃÇÑ´Ù
		sprintf(szText, "(%03d) %s", ZGetGameClient()->GetStageNumber(), ZGetGameClient()->GetStageName());
	}
	TextRelative(pDC, 0.26f, 0.22f, szText);

Find (if (ZGetGame()->GetMatch()->IsTeamPlay()) - Replace)

	if (ZGetGame()->GetMatch()->IsTeamPlay())
	{
		if (bPlayerWars)
			sprintf(szText, "%d (Ladder Red)  VS  %d (Ladder Blue)", ZGetGame()->GetMatch()->GetTeamScore(MMT_RED), ZGetGame()->GetMatch()->GetTeamScore(MMT_BLUE));
		else if (bClanGame)
		{

			{

				sprintf(szText, "%d (%s)  VS  %d (%s)",
					ZGetGame()->GetMatch()->GetTeamScore(MMT_RED), m_szRedClanName,
					ZGetGame()->GetMatch()->GetTeamScore(MMT_BLUE), m_szBlueClanName);
			}
		}
		else
		{
			if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_DEATHMATCH_TEAM2) // ÆÀÀEÏ¶§ ¹«ÇÑµ¥½º¸ÅÄ¡¸¸ ¿¹¿Ü°¡ ¸¹ÀÌ ¹ß»ýÇÕ´Ï´Ù =_=;
				sprintf(szText, "%s : %d(Red) vs %d(Blue)", ZGetGameTypeManager()->GetGameTypeStr(ZGetGame()->GetMatch()->GetMatchType()),
				ZGetGame()->GetMatch()->GetTeamKills(MMT_RED),
				ZGetGame()->GetMatch()->GetTeamKills(MMT_BLUE));
		}
	}
	else

Find(GetGame()->GetMatch()->IsWaitForRoundEnd() - Replace)

	else if (ZGetGame()->GetMatch()->IsWaitForRoundEnd() && !bClanGame && !bPlayerWars)
	{


Find (ZGetGame()->GetMatch()->GetRoundState() == MMATCH_ROUNDSTATE_PLAY - Replace)

	else if (!bClanGame && !bPlayerWars)
	{

Find (const float normalXPOS[]  - Add under)

	bool clanpos = false;
	if (bPlayerWars || bClanGame) clanpos = true;

Find (GetGameTypeManager()->IsQuestDerived( ZGetGame()->GetMatch()->GetMatchType() - Add under)

	else if (bClanGame || bPlayerWars)
	{
		x = ITEM_XPOS[2];	// HP/AP
		sprintf(szBuff, "%s/%s", ZMsg(MSG_CHARINFO_HP), ZMsg(MSG_CHARINFO_AP));
		TextRelative(pDC, x, y, szBuff);
	}


Find (ZGetGameTypeManager()->IsQuestDerived(ZGetGame()->GetMatch()->GetMatchType() - Replace)

	if (ZGetGameTypeManager()->IsQuestDerived(ZGetGame()->GetMatch()->GetMatchType()))
			pItem->nExp = pCharacter->GetStatus().Ref().nKills * 100;
		else
			pItem->nExp = pCharacter->GetStatus().Ref().nExp;

		if (bClanGame || bPlayerWars)
		{
			if (ZGetGame()->m_pMyCharacter->IsTeam(pCharacter))
			{
				pItem->HP = pCharacter->GetHP();
				pItem->AP = pCharacter->GetAP();
				pItem->MaxHP = pCharacter->GetMaxHP();
				pItem->MaxAP = pCharacter->GetMaxAP();
			}
			else
			{
				pItem->HP = 0;
				pItem->AP = 0;
			}
		}
		pItem->nKills = pCharacter->GetStatus().Ref().nKills;
		pItem->nDeaths = pCharacter->GetStatus().Ref().nDeaths;
		pItem->uidUID = pCharacter->GetUID();


Find (backgroundcolor = BACKGROUND_COLOR_MYCHAR_DEATH_MATCH; - Replace)

		MCOLOR backgroundcolor;
		if (pItem->bMyChar) {
			backgroundcolor = BACKGROUND_COLOR_MYCHAR_DEATH_MATCH;
			if (!bClanGame && !bPlayerWars) {
				backgroundcolor =
					(pItem->nTeam == MMT_RED) ? BACKGROUND_COLOR_MYCHAR_RED_TEAM :
					(pItem->nTeam == MMT_BLUE) ? BACKGROUND_COLOR_MYCHAR_BLUE_TEAM :
					BACKGROUND_COLOR_MYCHAR_DEATH_MATCH;
			}
		}


Find (pItem->bMyChar || pItem->bCommander - Replace)

		if (pItem->bMyChar || pItem->bCommander)
		{
			int y1 = itemy * MGetWorkspaceHeight();
			int y2 = (y + linespace * nCount) * MGetWorkspaceHeight();
			bool clangame = false;
			if (bPlayerWars || bClanGame) clangame = true;
			int x1 = clangame ? 0.43 * MGetWorkspaceWidth() : 0.255 * MGetWorkspaceWidth();
			int x2 = (0.715 + 0.26) * MGetWorkspaceWidth();

			pDC->SetColor(backgroundcolor);
			pDC->FillRectangleW(x1, y1, x2 - x1, y2 - y1);
		}

Find(!bClanGame - Replace)

		if (!bClanGame && !bPlayerWars)
		{
			if (pItem->nTeam == MMT_RED)		// red
				textcolor = pItem->bDeath ? TEXT_COLOR_RED_TEAM_DEAD : TEXT_COLOR_RED_TEAM;
			else
				if (pItem->nTeam == MMT_BLUE)		// blue
					textcolor = pItem->bDeath ? TEXT_COLOR_BLUE_TEAM_DEAD : TEXT_COLOR_BLUE_TEAM;
				else
					if (pItem->nTeam == MMT_SPECTATOR)
						textcolor = TEXT_COLOR_SPECTATOR;

		}


Find(!bClanGame - Replace)

		if (!bClanGame && !bPlayerWars)
		{
			x = ITEM_XPOS[1];
			//x = 0.399f;
			int nIconSize = .8f * linespace * (float)MGetWorkspaceHeight();
			float icony = itemy + (linespace - (float)nIconSize / (float)MGetWorkspaceHeight())*.5f;

			if (pItem->szClan[0]) {
				MBitmap *pbmp = ZGetEmblemInterface()->GetClanEmblem(pItem->nClanID);
				if (pbmp) {
					pDC->SetBitmap(pbmp);
					int screenx = x*MGetWorkspaceWidth();
					int screeny = icony*MGetWorkspaceHeight();

					pDC->Draw(screenx, screeny, nIconSize, nIconSize);

				}
			}
			x += (float)nIconSize / (float)MGetWorkspaceWidth() + 0.005f;
			TextRelative(pDC, x, texty, pItem->szClan);
		}

Find((ZGetGameTypeManager()->IsQuestDerived(ZGetGame()->GetMatch()->GetMatchType())) - Replace)


		if (ZGetGameTypeManager()->IsQuestDerived(ZGetGame()->GetMatch()->GetMatchType()))
		{
			bool bDraw = m_Observer.IsVisible();

			ZCharacterManager::iterator itor = ZGetGame()->m_CharacterManager.find(pItem->uidUID);
			if (itor != ZGetGame()->m_CharacterManager.end())
			{
				ZCharacter* pQuestPlayerInfo = (*itor).second;

				MCOLOR tmpColor = pDC->GetColor();

				x = ITEM_XPOS[2];

				pDC->SetColor(MCOLOR(0x30000000));
				pDC->FillRectangleW((x*MGetWorkspaceWidth()), texty*MGetWorkspaceHeight() + 1, 0.08*MGetWorkspaceWidth(), 7);
				float nValue = (0.08 * (pQuestPlayerInfo->GetHP() / pQuestPlayerInfo->GetMaxHP()));
				pDC->SetColor(MCOLOR(0xFFFF0000));
				pDC->FillRectangleW((x*MGetWorkspaceWidth()), texty*MGetWorkspaceHeight() + 1, nValue*MGetWorkspaceWidth(), 7);

				pDC->SetColor(MCOLOR(0x30000000));
				pDC->FillRectangleW((x*MGetWorkspaceWidth()), texty*MGetWorkspaceHeight() + 9, 0.08*MGetWorkspaceWidth(), 3);
				float nValuee = (0.08 * (pQuestPlayerInfo->GetAP() / pQuestPlayerInfo->GetMaxAP()));
				pDC->SetColor(MCOLOR(0xFF00FF00));
				pDC->FillRectangleW((x*MGetWorkspaceWidth()), texty*MGetWorkspaceHeight() + 9, nValuee*MGetWorkspaceWidth(), 3);

				pDC->SetColor(tmpColor);

				x = ITEM_XPOS[3];
				int nKills = 0;
				ZModule_QuestStatus* pMod = (ZModule_QuestStatus*)pQuestPlayerInfo->GetModule(ZMID_QUESTSTATUS);
				if (pMod)
					nKills = pMod->GetKills();
				sprintf(szText, "%d", nKills);
				TextRelative(pDC, x, texty, szText, true);
			}
		}
		else
		{
			if (bClanGame || bPlayerWars)
			{
				x = ITEM_XPOS[2] - 0.02f;
				sprintf(szText, "%d", pItem->nExp);
				if (!pItem->bDeath && ZGetGame()->m_pMyCharacter->GetTeamID() == pItem->nTeam)
				{
					x = ITEM_XPOS[2] + 0.04f;
					pDC->SetColor(MCOLOR(0x30000000));
					pDC->FillRectangleW((x*MGetWorkspaceWidth()), texty*MGetWorkspaceHeight() + 1, 0.04*MGetWorkspaceWidth(), 7);
					float nValue = (0.04 * (pItem->HP / pItem->MaxHP));
					pDC->SetColor(MCOLOR(0xFFFF0000));
					pDC->FillRectangleW((x*MGetWorkspaceWidth()), texty*MGetWorkspaceHeight() + 1, nValue*MGetWorkspaceWidth(), 7);

					pDC->SetColor(MCOLOR(0x30000000));
					pDC->FillRectangleW((x*MGetWorkspaceWidth()), texty*MGetWorkspaceHeight() + 9, 0.04*MGetWorkspaceWidth(), 3);
					float nValuee = (0.04 * (pItem->AP / pItem->MaxAP));
					pDC->SetColor(MCOLOR(0xFF00FF00));
					pDC->FillRectangleW((x*MGetWorkspaceWidth()), texty*MGetWorkspaceHeight() + 9, nValuee*MGetWorkspaceWidth(), 3);
				}
			}
		    else
			{
				x = ITEM_XPOS[2];
				sprintf(szText, "%d", pItem->nExp);
				TextRelative(pDC, x, texty, szText, true);
			}	

Open(ZCommandUDPHackShield.cpp - Add)

	AddDeniedCommand(MC_MATCH_JOIN_PLAYERWARS);
	AddDeniedCommand(MC_MATCH_PLAYERWARS_SIDERANK);

Open(ZGame.cpp - else if (nTeam == nMyTeam) - Replace)

				else if (nTeam == nMyTeam)
				{
					if ((!ZGetGameClient()->IsLadderGame() && !ZGetGameClient()->IsPlayerWars() && !ZGetGameClient()->GetRejectTeamChat()) ||
						((ZGetGameClient()->IsLadderGame() || ZGetGameClient()->IsPlayerWars()) && !ZGetGameClient()->GetRejectClanChat()) ||
						(strcmp(pChar->GetUserName(), ZGetMyInfo()->GetCharName()) == 0))
					{
						ZGetSoundEngine()->PlaySound("if_error");
						char szTemp[256];

						sprintf(szTemp, "%s(Team)%s : %s", ((pChar->IsDie()) ? "[DEAD] " : ""), pChar->GetProperty()->GetName(),szMsg);
						ZChatOutput(TeamChatColor, szTemp);
					}
				}


Find (GetGame()->m_pMyCharacter->IsAdminHide() && nTeam != MMT_ALL && nTeam != MMT_SPECTATOR - Replace)

				if (ZGetGame()->m_pMyCharacter->IsAdminHide() && nTeam != MMT_ALL && nTeam != MMT_SPECTATOR)
				{
					if ( (!ZGetGameClient()->IsLadderGame() && !ZGetGameClient()->IsPlayerWars()&& !ZGetGameClient()->GetRejectTeamChat()) ||
						 (( ZGetGameClient()->IsLadderGame() || ZGetGameClient()->IsPlayerWars()) && !ZGetGameClient()->GetRejectClanChat()) ||
						 ( strcmp( pChar->GetUserName(), ZGetMyInfo()->GetCharName()) == 0))
					{
						ZGetSoundEngine()->PlaySound("if_error");
						char szTemp[256];

						if( !pChar->IsVisible() || pChar->IsDie() )
							sprintf(szTemp, "(%s)(%s Team)%s : %s", ZStr(std::string("UI_GAMESTATE_01")), nTeam == MMT_RED ? "Red" : "Blue", pChar->GetProperty()->GetName(),szMsg);
						else
							sprintf(szTemp, "(%s Team)%s : %s", nTeam == MMT_RED ? "Red" : "Blue", pChar->GetProperty()->GetName(),szMsg);

						ZChatOutput(TeamChatColor, szTemp);
					}
				}
			}
		}
		break;

Open(ZGameClient.cpp - MC_ADMIN_ANNOUNCE - Add under)

			cmdId == MC_MATCH_PLAYERWARS_FRIENDINVITE ||
			cmdId == MC_MATCH_PLAYERWARS_FRIENDACCEPT ||
			cmdId == MC_MATCH_PLAYERWARS_FRIENDLEAVE ||

Find (m_bLadderGame = false; - Add under)

	m_bPlayerWars = false;


Find(ZGameClient::OnStageLaunch - Replace)

	void ZGameClient::OnStageLaunch(const MUID& uidStage, const char* pszMapName)
	{
		m_bLadderGame = false;
		m_bPlayerWars = false;
		SetAllowTunneling(false);

		m_MatchStageSetting.SetMapName(const_cast<char*>(pszMapName));

		if (ZApplication::GetGameInterface()->GetState() != GUNZ_GAME) {
			ZChangeGameState(GUNZ_GAME);		// thread safely
		}
	}

Find (ZGameClient::OnForcedEntryToGame - Replace)

	void ZGameClient::OnForcedEntryToGame()
	{
		m_bLadderGame = false;
		m_bForcedEntry = true;
		m_bPlayerWars = false;
		SetAllowTunneling(false);
		ZChangeGameState(GUNZ_GAME);
	}

Open(ZGameClient.h - class ZGameClient : public MMatchClient - m_bLadderGame; - Add under)

	bool				m_bPlayerWars;


Find (int tournamentPoint, wins, losses, ranking, winners, lastWeekGrade; - Replace)

	struct DTCHARINFO {
		int tournamentPoint, wins, losses, ranking, winners, lastWeekGrade;
	};
	struct PWCHARINFO
	{
		int Ranking, Wins, Losses, Draws, Score;
	};
	const PWCHARINFO* GetMyPlayerWarsCharInfo() { return &m_PWCharInfo; };
	const DTCHARINFO* GetMyDuelTournamentCharInfo()		{ return &m_dtCharInfo; }
	const DTCHARINFO* GetMyDuelTournamentCharInfoPrev() { return &m_dtCharInfoPrev; }

Find(OnLadderLaunch - Replace)

	void OnLadderLaunch(const MUID& uidStage, const char* pszMapName, bool PlayerWars);
	
Find (bool IsLadderGame() { return m_bLadderGame; } - Add under)

	bool IsPlayerWars() { return m_bPlayerWars; }

Open(ZGameClient_Ladder.cpp - OnLadderLaunch - Replace)

	void ZGameClient::OnLadderLaunch(const MUID& uidStage, const char* pszMapName, bool PlayerWars)
	{
		ZGetGameInterface()->OnArrangedTeamGameUI(false);
		if (PlayerWars)
			m_bPlayerWars = true;
		else
			m_bLadderGame = true;

		m_uidStage = uidStage;
		strcpy(m_szStageName, "UnNamedStage");

		SetAllowTunneling(false);

		m_MatchStageSetting.SetMapName(const_cast<char*>(pszMapName));


		unsigned int nStageNameChecksum = m_szStageName[0] + m_szStageName[1] + m_szStageName[2] + m_szStageName[3];
		InitPeerCrypt(uidStage, nStageNameChecksum);

		if (ZApplication::GetGameInterface()->GetState() != GUNZ_GAME)
		{
			ZChangeGameState(GUNZ_GAME);
		}
	}

Open(ZGameClient_OnCommand.cpp - ZGameClient::OnCommand)

	case MC_MATCH_PLAYERWARS_RANDOM_MAPS:
	{
		int nRandomIndex[3];
		pCommand->GetParameter(&nRandomIndex[0], 0, MPT_INT);
		pCommand->GetParameter(&nRandomIndex[1], 1, MPT_INT);
		pCommand->GetParameter(&nRandomIndex[2], 2, MPT_INT);
		ZIDLResource* pResource = ZGetGameInterface()->GetIDLResource();



		char Name[100];

		for (int i = 0; i < 3; i++)
		{
			sprintf(Name, "PlayerWarsMap%d", i);
			MLabel* pLabel = (MLabel*)pResource->FindWidget(Name);
			if (pLabel)
				pLabel->SetText(MGetMapDescMgr()->GetMapName(nRandomIndex[i]));
		}
		ZGetGameInterface()->OnArrangedTeamGameUI(true, true);
		ZGetGameClient()->bMatching = true; //quejeso
	}
	break;
	case MC_MATCH_PLAYERWARS_INVITED:
	{
		ZIDLResource* pResource = ZGetGameInterface()->GetIDLResource();
		ZGetGameClient()->LastVoteID = -1;
		MWidget* pWidget = pResource->FindWidget("PlayerWarsGameDialog");
		if (pWidget != NULL)
			pWidget->Show(false);
		ZGetGameInterface()->OnArrangedTeamGameUI(true);
	};
	case MC_MATCH_PLAYERWARS_VOTE_UPDATE:
	{

		int nRandomIndex[3];
		pCommand->GetParameter(&nRandomIndex[0], 0, MPT_INT);
		pCommand->GetParameter(&nRandomIndex[1], 1, MPT_INT);
		pCommand->GetParameter(&nRandomIndex[2], 2, MPT_INT);
		ZIDLResource* pResource = ZGetGameInterface()->GetIDLResource();
		char Name[100], Text[40];
		for (int i = 0; i < 3; i++)
		{
			sprintf(Name, "PlayerWarsVote%d", i);
			if(nRandomIndex[i] < 0)
				sprintf(Text, "0");
			else
				sprintf(Text, "%d", nRandomIndex[i]);

			MLabel* pLabel = (MLabel*)pResource->FindWidget(Name);
			if (pLabel)
				pLabel->SetText(Text);
		}
	}
	break;

Find (MC_MATCH_LADDER_CANCEL_CHALLENGE - Replace)

		case MC_MATCH_LADDER_CANCEL_CHALLENGE:
		{
			bool PlayerWars;
			pCommand->GetParameter(&PlayerWars, 1, MPT_BOOL);
			ZGetGameInterface()->OnArrangedTeamGameUI(false);
			if (PlayerWars == false)
			{

				char szCharName[MATCHOBJECT_NAME_LENGTH];
				pCommand->GetParameter(szCharName, 0, MPT_STR, sizeof(szCharName));

				if (szCharName[0] != 0) {
					char szOutput[256];
					ZTransMsg(szOutput, MSG_LADDER_CANCEL, 1, szCharName);
					ZChatOutput(MCOLOR(ZCOLOR_CHAT_SYSTEM), szOutput);

				}
				else	 // ÀÌ¸§ÀÌ ¾øÀ¸¸é ½ÇÆÐÇÑ°æ¿ì´Ù.
				{
					ZChatOutput(MCOLOR(ZCOLOR_CHAT_SYSTEM),
						ZMsg(MSG_LADDER_FAILED));
				}
			}
		}break;

Find (MC_MATCH_LADDER_PREPARE - Add under)

		case MC_MATCH_PLAYERWARS_COUNTER:
		{
			if (ZGetGameInterface()->GetState() == GUNZ_LOBBY)
			{
				MCommandParameter* pParam = pCommand->GetParameter(0);
				if (pParam->GetType() != MPT_BLOB) return false;
				void* pBlob = pParam->GetPointer();
				MTD_PlayerWarsCounterInfo* Info = (MTD_PlayerWarsCounterInfo*)MGetBlobArrayElement(pBlob, 0);
				ZIDLResource* pRes = ZApplication::GetGameInterface()->GetIDLResource();
				if (!pRes) return false;
				char szOutput[256];
				char szWigetName[100];
				for (int i = 0; i <= 7; i++)
				{
					sprintf(szWigetName, "Lobby_PlayerWarsCount%d", i);
					sprintf(szOutput, "%d Players Waiting", Info->Count[i]);
					MLabel* pLabel = (MLabel*)pRes->FindWidget(szWigetName);
					if (pLabel)
						pLabel->SetText(szOutput);
				}
			}
		}
		break;

Find (MC_MATCH_LADDER_LAUNCH - Replace)

		case MC_MATCH_LADDER_LAUNCH:
		{
			MUID uidStage;
			pCommand->GetParameter(&uidStage, 0, MPT_UID);
			char szMapName[128];
			pCommand->GetParameter(szMapName, 1, MPT_STR, sizeof(szMapName));
			bool PlayerWars;
			pCommand->GetParameter(&PlayerWars, 2, MPT_BOOL);
			OnLadderLaunch(uidStage, szMapName, PlayerWars);
		}break;


Find (MC_MATCH_DUELTOURNAMENT_CHAR_INFO - Add under)

		case MC_MATCH_PLAYERWARS_CHARINFO:
		{
			pCommand->GetParameter(&m_PWCharInfo.Ranking, 0, MPT_INT);
			pCommand->GetParameter(&m_PWCharInfo.Wins, 1, MPT_INT);
			pCommand->GetParameter(&m_PWCharInfo.Losses, 2, MPT_INT);
			pCommand->GetParameter(&m_PWCharInfo.Draws, 3, MPT_INT);
			pCommand->GetParameter(&m_PWCharInfo.Score, 4, MPT_INT);
			ZGetGameInterface()->UpdatePlayerWarsMyCharInfo();
		}
		break;


Open(ZGameInput.cpp - (ZGetCombatInterface()->IsShowResult()) - Replace)

		if (ZGetCombatInterface()->IsShowResult())
		{
			if (((ZGetCombatInterface()->m_nReservedOutTime - timeGetTime()) / 1000) < 13)
			{
				if (ZGetGameClient()->IsPlayerWars() || ZGetGameClient()->IsLadderGame() || ZGetGameClient()->IsDuelTournamentGame())
					ZChangeGameState(GUNZ_LOBBY);
				else
					ZChangeGameState(GUNZ_STAGE);

				return true;
			}
		}

Open(ZGameInterface.cpp - Add)

	#include "ZPlayerWarsRankingListBox.h"

Find (SetListenerWidget("LobbyChannelPlayerListNext", ZGetPlayerListNextListener()); Add under)

	SetListenerWidget("ArrangedPlayerWars", ZGetArrangedPlayerWarsListener());
	SetListenerWidget("PlayerWarsDialogOk", ZGetPlayerWarsDialogOkListener());
	SetListenerWidget("PlayerWarsVoteButton0", ZGetPlayerWarsVote0());
	SetListenerWidget("PlayerWarsVoteButton1", ZGetPlayerWarsVote1());
	SetListenerWidget("PlayerWarsVoteButton2", ZGetPlayerWarsVote2());
	SetListenerWidget("PlayerWarsDialogClose", ZGetPlayerWarsDialogCloseListener());
	SetListenerWidget("ChannelList_PlayerWars", ZGetChannelList());


Find (	if ((ZApplication::GetInstance()->GetLaunchMode() == ZApplication::ZLAUNCH_MODE_STANDALONE_REPLAY) - Replace)

	if ((ZApplication::GetInstance()->GetLaunchMode() == ZApplication::ZLAUNCH_MODE_STANDALONE_REPLAY) ||
		(ZGetGameClient()->IsLadderGame()) ||
		ZGetGameTypeManager()->IsQuestDerived(ZGetGameClient()->GetMatchStageSetting()->GetGameType()) ||
		ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_DUELTOURNAMENT)
	{
		m_CombatMenu.EnableItem(ZCombatMenu::ZCMI_BATTLE_EXIT, false);
		m_CombatMenu.EnableItem(ZCombatMenu::ZCMI_STAGE_EXIT, true);
	}
	else if ((ZGetGameClient()->IsPlayerWars()))
	{
		m_CombatMenu.EnableItem(ZCombatMenu::ZCMI_BATTLE_EXIT, false);
		m_CombatMenu.EnableItem(ZCombatMenu::ZCMI_STAGE_EXIT, false);
	}
	else
	{
		m_CombatMenu.EnableItem(ZCombatMenu::ZCMI_BATTLE_EXIT, true);
		m_CombatMenu.EnableItem(ZCombatMenu::ZCMI_STAGE_EXIT, true);
	}


Find(OnGameOnLoginDestroy - Add under)

	void ZGameInterface::SelectBackground(int i)
	{
		MWidget* pWidget;
		switch (i)
		{
		case 0:
			pWidget = m_IDLResource.FindWidget("Lobby_MainNormalBG");
			if (pWidget) pWidget->Show(true);
			pWidget = m_IDLResource.FindWidget("Lobby_MainDuelBG");
			if (pWidget) pWidget->Show(false);
			pWidget = m_IDLResource.FindWidget("Lobby_MainPlayerWarsBG");
			if (pWidget) pWidget->Show(false);
			pWidget = m_IDLResource.FindWidget("Lobby_MainClanBG");
			if (pWidget) pWidget->Show(false);
			break;
		case 1:
			pWidget = m_IDLResource.FindWidget("Lobby_MainNormalBG");
			if (pWidget) pWidget->Show(false);
			pWidget = m_IDLResource.FindWidget("Lobby_MainDuelBG");
			if (pWidget) pWidget->Show(false);
			pWidget = m_IDLResource.FindWidget("Lobby_MainPlayerWarsBG");
			if (pWidget) pWidget->Show(false);
			pWidget = m_IDLResource.FindWidget("Lobby_MainClanBG");
			if (pWidget) pWidget->Show(true);
			break;
		case 2:
			pWidget = m_IDLResource.FindWidget("Lobby_MainNormalBG");
			if (pWidget) pWidget->Show(false);
			pWidget = m_IDLResource.FindWidget("Lobby_MainClanBG");
			if (pWidget) pWidget->Show(false);
			pWidget = m_IDLResource.FindWidget("Lobby_MainPlayerWarsBG");
			if (pWidget) pWidget->Show(false);
			pWidget = m_IDLResource.FindWidget("Lobby_MainDuelBG");
			if (pWidget) pWidget->Show(true);
			break;
		case 3:
			pWidget = m_IDLResource.FindWidget("Lobby_MainNormalBG");
			if (pWidget) pWidget->Show(false);
			pWidget = m_IDLResource.FindWidget("Lobby_MainClanBG");
			if (pWidget) pWidget->Show(false);
			pWidget = m_IDLResource.FindWidget("Lobby_MainDuelBG");
			if (pWidget) pWidget->Show(false);
			pWidget = m_IDLResource.FindWidget("Lobby_MainPlayerWarsBG");
			if (pWidget) pWidget->Show(true);
			break;
		case 4:
			pWidget = m_IDLResource.FindWidget("Lobby_MainNormalBG");
			if (pWidget) pWidget->Show(false);
			pWidget = m_IDLResource.FindWidget("Lobby_MainClanBG");
			if (pWidget) pWidget->Show(false);
			pWidget = m_IDLResource.FindWidget("Lobby_MainDuelBG");
			if (pWidget) pWidget->Show(false);
			pWidget = m_IDLResource.FindWidget("Lobby_MainPlayerWarsBG");
			if (pWidget) pWidget->Show(false);
			break;
		}

	}

Find (ZDuelTournamentRankingListBox* pDTRankingListBox - Add under)

	ZPlayerWarsRankingListBox* pPWRankingListBox = (ZPlayerWarsRankingListBox*)m_IDLResource.FindWidget("Lobby_PlayerWarsRankingList");
	if (pPWRankingListBox) pPWRankingListBox->LoadInterfaceImgs();


Find(InitLobbyUIByChannelType() - Replace)

	void ZGameInterface::InitLobbyUIByChannelType()
	{
		bool bClanBattleUI =  ((ZGetGameClient()->GetServerMode() == MSM_CLAN) && (ZGetGameClient()->GetChannelType()==MCHANNEL_TYPE_CLAN));
		bool bDuelTournamentUI = (ZGetGameClient()->GetChannelType() == MCHANNEL_TYPE_DUELTOURNAMENT);
		bool bPlayerWarsUI = (((ZGetGameClient()->GetServerMode() == MSM_CLAN)) && (ZGetGameClient()->GetChannelType() == MCHANNEL_TYPE_PLAYERWARS));
		if (bClanBattleUI == true)
			SelectBackground(1);
		else if (bDuelTournamentUI == true)
			SelectBackground(2);
		else if (bPlayerWarsUI == true)
			SelectBackground(3);
		else
			SelectBackground(0);
		if (bClanBattleUI)
		{
			ZGetGameInterface()->InitDuelTournamentLobbyUI(false);
			//	ZGetGameInterface()->InitBattleLobbyUI(false);
			ZGetGameInterface()->InitPlayerWarsUI(false);
			ZGetGameInterface()->InitClanLobbyUI(true);
		}
		else if (bDuelTournamentUI)
		{
			ZGetGameInterface()->InitClanLobbyUI(false);
			ZGetGameInterface()->InitPlayerWarsUI(false);
			ZGetGameInterface()->InitDuelTournamentLobbyUI(true);
			//	ZGetGameInterface()->InitBattleLobbyUI(false);

			ZPostDuelTournamentRequestSideRankingInfo(ZGetMyUID());
		}
		else if (bPlayerWarsUI)
		{
			ZGetGameInterface()->InitDuelTournamentLobbyUI(false);
			ZGetGameInterface()->InitClanLobbyUI(false);
			ZGetGameInterface()->InitPlayerWarsUI(true);
			//	ZGetGameInterface()->InitBattleLobbyUI(false);
		}
		else
		{
			ZGetGameInterface()->InitClanLobbyUI(false);
			ZGetGameInterface()->InitDuelTournamentLobbyUI(false);
			ZGetGameInterface()->InitPlayerWarsUI(false);
			//	ZGetGameInterface()->InitBattleLobbyUI(false);
		}
	}

Find(ZDuelTournamentRankingListBox* pDTRankingListBox - Add under)

	ZPlayerWarsRankingListBox* pPWRankingListBox = (ZPlayerWarsRankingListBox*)m_IDLResource.FindWidget("Lobby_DuelTournamentRankingList");
	if (pPWRankingListBox) {
		pPWRankingListBox->UnloadInterfaceImgs();
		pPWRankingListBox->SetVisible(false);
	}


Find (InitClanLobbyUI - Add above)

	void ZGameInterface::InitPlayerWarsUI(bool bPlayerWarsEnable)
	{
		MWidget* pWidget;

		pWidget = m_IDLResource.FindWidget("StageBeforeBtn");
		if (pWidget) pWidget->Show(!bPlayerWarsEnable);
		pWidget = m_IDLResource.FindWidget("StageAfterBtn");
		if (pWidget) pWidget->Show(!bPlayerWarsEnable);
		bool bCheck = !bPlayerWarsEnable;
		for (int i = 1; i <= 6; i++)
		{
			char szBuffer[64];
			sprintf(szBuffer, "Lobby_RoomNo%d", i);
			pWidget = (MButton*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget(szBuffer);
			if (pWidget)
			{
				pWidget->Show(bCheck);
			}
		}
		pWidget = m_IDLResource.FindWidget("StageJoin");
		if (pWidget) pWidget->Show(!bPlayerWarsEnable);
		pWidget = m_IDLResource.FindWidget("StageCreateFrameCaller");
		if (pWidget) pWidget->Show(!bPlayerWarsEnable);
		pWidget = m_IDLResource.FindWidget("QuickJoin");
		if (pWidget) pWidget->Show(!bPlayerWarsEnable);

		m_CombatMenu.EnableItem(ZCombatMenu::ZCMI_BATTLE_EXIT, !bPlayerWarsEnable);

		pWidget = m_IDLResource.FindWidget("QuickJoin");
		if (pWidget) pWidget->Show(!bPlayerWarsEnable);

		pWidget = m_IDLResource.FindWidget("QuickJoin2");
		if (pWidget) pWidget->Show(!bPlayerWarsEnable);

		pWidget = m_IDLResource.FindWidget("RequestLadderRejoin");
		if (pWidget) pWidget->Show(bPlayerWarsEnable);

		pWidget = m_IDLResource.FindWidget("ArrangedPlayerWars");
		if (pWidget) pWidget->Show(bPlayerWarsEnable);
		pWidget = m_IDLResource.FindWidget("Lobby_PlayerWarsRankingList");
		if (pWidget)
		{
			pWidget->Show(bPlayerWarsEnable);
		}
	}

Find (ZGameInterface::OnArrangedTeamGameUI - Replace)

	void ZGameInterface::OnArrangedTeamGameUI(bool bFinding, bool isvote)
	{
		MWidget* pWidget;
		if (isvote == true)
		{
			pWidget = m_IDLResource.FindWidget("ArrangedTeamGame");
			if (pWidget) pWidget->Show(false);

			pWidget = m_IDLResource.FindWidget("LobbyFindClanTeam");
			if (pWidget != NULL) pWidget->Show(false);

			pWidget = m_IDLResource.FindWidget("PlayerWarsMapVote");
			if (pWidget)
			{
				pWidget->Show(bFinding);
				pWidget->SetText("Clan War Map Voter");
			}
		}
		else
		{
			pWidget = m_IDLResource.FindWidget("PlayerWarsMapVote");
			if (pWidget) pWidget->Show(false);

			pWidget = m_IDLResource.FindWidget("ArrangedTeamGame");
			if (pWidget) pWidget->Show(!bFinding);

			pWidget = m_IDLResource.FindWidget("LobbyFindClanTeam");
			if (pWidget != NULL) pWidget->Show(bFinding);
		}

Find (SAFE_ENABLE("DuelTournamentGame_4Test", bWaiting); - Add under)

	SAFE_ENABLE("ArrangedPlayerWars", bWaiting);

Find (SetDuelTournamentCharacterList - Add under)

	void ZGameInterface::UpdatePlayerWarsMyCharInfo()
	{
		ZIDLResource* pRes = ZApplication::GetGameInterface()->GetIDLResource();
		if (!pRes) return;

		const ZGameClient::PWCHARINFO* pCharInfo = GetGameClient()->GetMyPlayerWarsCharInfo();
		if (!pCharInfo) return;

		char szOutput[256];
		sprintf(szOutput, "%d", pCharInfo->Ranking);
		MLabel* pLabel = (MLabel*)pRes->FindWidget("Lobby_PlayerWarsRanking");
		pLabel->SetText(szOutput);
		sprintf(szOutput, "%d", pCharInfo->Wins);
		pLabel = (MLabel*)pRes->FindWidget("Lobby_PlayerWarsWins");
		pLabel->SetText(szOutput);
		sprintf(szOutput, "%d", pCharInfo->Losses);
		pLabel = (MLabel*)pRes->FindWidget("Lobby_PlayerWarsLosses");
		pLabel->SetText(szOutput);
		sprintf(szOutput, "%d", pCharInfo->Draws);
		pLabel = (MLabel*)pRes->FindWidget("Lobby_PlayerWarsDraws");
		pLabel->SetText(szOutput);
		sprintf(szOutput, "%d", pCharInfo->Score);
		pLabel = (MLabel*)pRes->FindWidget("Lobby_PlayerWarsScore");
		pLabel->SetText(szOutput);
		sprintf(szOutput, "%s", ZGetMyInfo()->GetCharName());
		pLabel = (MLabel*)pRes->FindWidget("Lobby_PlayerWarsName");
		pLabel->SetText(szOutput);
	}

Open(ZGameInterface.h - void InitClanLobbyUI(bool bClanBattleEnable); - Add under)

	void InitPlayerWarsUI(bool bPlayerWarsEnable);

Find (void UpdateDuelTournamantMyCharInfoPreviousUI(); - Add under)

	void UpdatePlayerWarsMyCharInfo();

Open(ZGameInterface_OnCommand.cpp - Add)

	#include "ZPlayerWarsRankingListBox.h"

Find (MC_MATCH_STAGE_RESPONSE_QUICKJOIN - Add under)

	case MC_MATCH_PLAYERWARS_SIDERANK:
	{
		MCommandParameter* pParam = pCommand->GetParameter(0);
		if (!pParam) { _ASSERT(0); break; }
		void* pBlob = pParam->GetPointer();
		int nCount = MGetBlobArrayCount(pBlob);

		_ASSERT(nCount <= NUM_DISPLAY_DUELTOURNAMENT_RANKING);

		ZIDLResource* pRes = ZApplication::GetGameInterface()->GetIDLResource();
		MWidget* pWidget = pRes->FindWidget("Lobby_PlayerWarsRankingList");
		if (!pWidget) { _ASSERT(0); break; }

		ZPlayerWarsRankingListBox* pRankingList = (ZPlayerWarsRankingListBox*)pWidget;
		pRankingList->ClearAll();

		for (int i = 0; i<nCount; ++i)
		{
			PWRankingInfo *pRankInfo = reinterpret_cast<PWRankingInfo*>(MGetBlobArrayElement(pBlob, i));
			if (!pRankInfo) { _ASSERT(0); break; }
			ZPLAYERRANKINGITEM tempItem;
			tempItem.nLosses = pRankInfo->m_nLoses;
			tempItem.nWins = pRankInfo->m_nWins;
			tempItem.nRank = pRankInfo->m_nRanking;
			strcpy(tempItem.szCharName, pRankInfo->m_szCharName);
			pRankingList->SetRankInfo(i, tempItem);
		}

		// ´ÙÀ½ ¼øÀ§±îÁö ³²Àº Æ÷ÀÎÆ® Ãâ·Â
		int myRankIndex = -1;
		for (int i = 0; i<nCount; ++i)
		{
			DTRankingInfo *pRankInfo = reinterpret_cast<DTRankingInfo*>(MGetBlobArrayElement(pBlob, i));
			if (!pRankInfo) { _ASSERT(0); break; }

			if (0 == strcmp(pRankInfo->m_szCharName, ZGetMyInfo()->GetCharName())) {
				myRankIndex = i;
				break;
			}
		}
		pRankingList->SetMyRankIndex(myRankIndex);
	}
	break;

Open(ZIDLResource.cpp - Add)

	#include "ZPlayerWarsRankingListBox.h"

Find(ZDuelTournamentRankingListBox* ZIDLResource::GetDuelTournamentRankingListBox - Add under)

	ZPlayerWarsRankingListBox* ZIDLResource::GetPlayerWarsRankingListBox(MXmlElement& element)
	{
		MXmlElement childElement;
		char szBuf[4096];
		//	char szAttr[4096];

		MWidget* pParentWidget = GetParentWidget(element);
		ZPlayerWarsRankingListBox* pWidget = new ZPlayerWarsRankingListBox("", pParentWidget, pParentWidget);
		InsertWidget(element, pWidget);

		int iCount = element.GetChildNodeCount();

		for (int i = 0; i < iCount; i++)
		{
			memset(szBuf, 0, sizeof(szBuf));
			childElement = element.GetChildNode(i);
			childElement.GetTagName(szBuf);

			if (GetCommonWidgetProperty(pWidget, childElement, szBuf)) continue;
		}
		return pWidget;
	}

Find(if (!strcmp(szTagName, "DUELTOURNAMENTRANKINGLIST")) - Add under)

	else if (!strcmp(szTagName, "PLAYERWARSRANKINGLIST"))
	{
		GetPlayerWarsRankingListBox(element);
	}

Open(ZIDLResource.h - class ZDuelTournamentRankingListBox; - Add under)

	class ZPlayerWarsRankingListBox;

Find (ZDuelTournamentRankingListBox* GetDuelTournamentRankingListBox( MXmlElement& element ); - Add under)

	ZPlayerWarsRankingListBox* GetPlayerWarsRankingListBox(MXmlElement& element);

Open(ZInterfaceListener.cpp - BEGIN_IMPLEMENT_LISTENER(ZGetBattleExitButtonListener, MBTN_CLK_MSG) - Replace )

	BEGIN_IMPLEMENT_LISTENER(ZGetBattleExitButtonListener, MBTN_CLK_MSG)
	if (!ZGetGameClient()->IsLadderGame() && !ZGetGameClient()->IsPlayerWars())
	{
		if (pWidget->GetParent() != NULL) pWidget->GetParent()->Show(false);
		ZGetGameInterface()->ReserveLeaveBattle();
	}
	END_IMPLEMENT_LISTENER()

Find (BEGIN_IMPLEMENT_LISTENER( ZGetRegisterListener, MBTN_CLK_MSG) - Add under)

	BEGIN_IMPLEMENT_LISTENER(ZGetArrangedPlayerWarsListener, MBTN_CLK_MSG)
	ZIDLResource* pResource = ZGetGameInterface()->GetIDLResource();
	MWidget* pWidget = pResource->FindWidget("PlayerWarsMapVote");
	if (pWidget != NULL && pWidget->IsVisible()) return true;
	pWidget = pResource->FindWidget("PlayerWarsGameDialog");
	if (pWidget != NULL && pWidget->IsVisible()) return true;
	pWidget = pResource->FindWidget("LobbyFindClanTeam");
	if (pWidget != NULL && pWidget->IsVisible()) return true;

	pWidget = pResource->FindWidget("PlayerWarsGameDialog");
	if (pWidget != NULL)
	{
		pWidget->Show(true, true);
		unsigned long int nPlaceFilter = 0;
		SetBitSet(nPlaceFilter, MMP_LOBBY);
		char Name[100];
		for (int i = 0; i < 3; i++)
		{
			sprintf(Name, "PlayerWarsVote%d", i);
			MLabel* pLabel = (MLabel*)pResource->FindWidget(Name);
			if (pLabel)
				pLabel->SetTextColor(MCOLOR(255, 255, 15));
		}
	}
	END_IMPLEMENT_LISTENER();

	BEGIN_IMPLEMENT_LISTENER(ZGetPlayerWarsVote0, MBTN_CLK_MSG)
	ZIDLResource* pResource = ZGetGameInterface()->GetIDLResource();
	char Name[100];
	for (int i = 0; i < 3; i++)
	{
		sprintf(Name, "PlayerWarsVote%d", i);
		MLabel* pLabel = (MLabel*)pResource->FindWidget(Name);
		if (pLabel)
			pLabel->SetTextColor(MCOLOR(255, 255, 15));
	}
	ZGetGameClient()->LastVoteID = 0;
	MLabel* pLabel = (MLabel*)pResource->FindWidget("PlayerWarsVote0");
	if (pLabel)
	pLabel->SetTextColor(MCOLOR(102, 205, 0));
	ZPostPlayerWarsVote(0);
	END_IMPLEMENT_LISTENER();

	BEGIN_IMPLEMENT_LISTENER(ZGetPlayerWarsVote1, MBTN_CLK_MSG)
	ZIDLResource* pResource = ZGetGameInterface()->GetIDLResource();
	char Name[100];
	for (int i = 0; i < 3; i++)
	{
		sprintf(Name, "PlayerWarsVote%d", i);
		MLabel* pLabel = (MLabel*)pResource->FindWidget(Name);
		if (pLabel)
			pLabel->SetTextColor(MCOLOR(255, 255, 15));
	}
	ZGetGameClient()->LastVoteID = 1;
	MLabel* pLabel = (MLabel*)pResource->FindWidget("PlayerWarsVote1");
	if (pLabel)
	pLabel->SetTextColor(MCOLOR(102, 205, 0));
	ZPostPlayerWarsVote(1);
	END_IMPLEMENT_LISTENER();

	BEGIN_IMPLEMENT_LISTENER(ZGetPlayerWarsVote2, MBTN_CLK_MSG)
	ZIDLResource* pResource = ZGetGameInterface()->GetIDLResource();
	char Name[100];
	for (int i = 0; i < 3; i++)
	{
		sprintf(Name, "PlayerWarsVote%d", i);
		MLabel* pLabel = (MLabel*)pResource->FindWidget(Name);
		if (pLabel)
			pLabel->SetTextColor(MCOLOR(255, 255, 15));
	}
	ZGetGameClient()->LastVoteID = 2;
	MLabel* pLabel = (MLabel*)pResource->FindWidget("PlayerWarsVote2");
	if (pLabel)
	pLabel->SetTextColor(MCOLOR(102, 205, 0));
	ZPostPlayerWarsVote(2);
	END_IMPLEMENT_LISTENER();

	BEGIN_IMPLEMENT_LISTENER(ZGetPlayerWarsDialogOkListener, MBTN_CLK_MSG)
		ZIDLResource* pResource = ZGetGameInterface()->GetIDLResource();
		ZGetGameClient()->LastVoteID = -1;
		MWidget* pWidget = pResource->FindWidget("PlayerWarsGameDialog");
		if(pWidget!=NULL)
			pWidget->Show(false);
		int Lead, GameType;
		MButton* pButton = (MButton*)pResource->FindWidget("PlayerWarsLead");
		if ((pButton) && (pButton->GetCheck()))
		{
			Lead = 1;
		}		
		MComboBox* pCWidget = (MComboBox*)pResource->FindWidget("PlayerWarsGameType");
		if(pCWidget)	
		{
			GameType = pCWidget->GetSelIndex();
		}
		ZPostJoinPlayerWars(Lead, GameType);
		ZGetGameInterface()->OnArrangedTeamGameUI(true);
	END_IMPLEMENT_LISTENER();

	BEGIN_IMPLEMENT_LISTENER(ZGetPlayerWarsDialogCloseListener, MBTN_CLK_MSG)
		ZIDLResource* pResource = ZGetGameInterface()->GetIDLResource();
		MWidget* pWidget = pResource->FindWidget("PlayerWarsGameDialog");
		if(pWidget!=NULL)
			pWidget->Show(false);

		pWidget = pResource->FindWidget("LobbyFindClanTeam");
		if(pWidget!=NULL)
			pWidget->Show(false);
	END_IMPLEMENT_LISTENER();


Find (ZGetArrangedTeamGame_CancelListener - Replace)

	BEGIN_IMPLEMENT_LISTENER(ZGetArrangedTeamGame_CancelListener, MBTN_CLK_MSG)
		ZIDLResource* pResource = ZGetGameInterface()->GetIDLResource();
		MWidget* pWidget = pResource->FindWidget("LobbyFindClanTeam");
		if(pWidget!=NULL)
			pWidget->Show(false);
		bool bPlayerWarsUI = (ZGetGameClient()->GetChannelType() == MCHANNEL_TYPE_PLAYERWARS);
		ZPostLadderCancel(bPlayerWarsUI);
	END_IMPLEMENT_LISTENER();

Find (nChannelType = MCHANNEL_TYPE_DUELTOURNAMENT - Add under)

	case 4 : nChannelType = MCHANNEL_TYPE_PLAYERWARS; break;

Find (ZGetGameResultQuit - Replace)

	BEGIN_IMPLEMENT_LISTENER(ZGetGameResultQuit, MBTN_CLK_MSG)
	if (!ZGetGameClient()->IsPlayerWars())
	{
		if (ZGetGameClient()->IsLadderGame() || 
			ZGetGameClient()->IsDuelTournamentGame())
			PostMessage(g_hWnd, WM_CHANGE_GAMESTATE, GUNZ_LOBBY, 0);
		else
			PostMessage(g_hWnd, WM_CHANGE_GAMESTATE, GUNZ_STAGE, 0);
	}
	END_IMPLEMENT_LISTENER();

Open(ZInterfaceListener.h - ZGetLanguageChangeConfirmListenter - Under)

	DECLARE_LISTENER(ZGetPlayerWarsVote0);
	DECLARE_LISTENER(ZGetPlayerWarsVote1);
	DECLARE_LISTENER(ZGetPlayerWarsVote2);
	DECLARE_LISTENER(ZGetArrangedPlayerWarsListener)
	DECLARE_LISTENER(ZGetPlayerWarsDialogOkListener);
	DECLARE_LISTENER(ZGetPlayerWarsDialogCloseListener);

Add(Gunz\ZPlayerWarsRankingListBox.cpp) <br>
Add(Gunz\ZPlayerWarsRankingListBox.h) <br>

Open(ZPost.h - ZPostRequestUseSpendableBuffItem - Add under) <br>

	inline void ZPostPlayerWarsVote(int Map)
	{
		ZPOSTCMD1(MC_MATCH_PLAYERWARS_VOTE, MCmdParamInt(Map));
	}
	inline void ZPostJoinPlayerWars(int Lead, int GameType)
	{
		ZPOSTCMD2(MC_MATCH_JOIN_PLAYERWARS, MCmdParamInt(Lead), MCmdParamInt(GameType));
	}
	inline void ZPostPlayerWarsAccept()
	{
	}
	inline void ZPostPlayerWarsLeave()
	{
	}

Find(void ZPostLadderCancel - Replace)

	inline void ZPostLadderCancel(bool PlayerWars)
	{
		ZPOSTCMD1(MC_MATCH_LADDER_REQUEST_CANCEL_CHALLENGE, MCmdParamBool(PlayerWars));
	}

Open(ZStageInterface.cpp - ZGetGameTypeManager()->IsQuestDerived(pSetting->nGameType) - Replace)

	#ifdef _QUEST
		if (ZGetGameTypeManager()->IsQuestDerived(pSetting->nGameType) || ZGetGameClient()->IsLadderGame() || pSetting->nGameType == MMATCH_GAMETYPE_DUELTOURNAMENT)
		{
			ZApplication::GetGameInterface()->GetCombatMenu()->EnableItem(ZCombatMenu::ZCMI_BATTLE_EXIT, false);
		}
		else if (ZGetGameClient()->IsPlayerWars())
		{
			ZApplication::GetGameInterface()->GetCombatMenu()->EnableItem(ZCombatMenu::ZCMI_BATTLE_EXIT, false);
			ZApplication::GetGameInterface()->GetCombatMenu()->EnableItem(ZCombatMenu::ZCMI_STAGE_EXIT, false);
			//ZApplication::GetGameInterface()->GetCombatMenu()->EnableItem(ZCombatMenu::ZCMI_PROG_EXIT, false);
			//ZApplication::GetGameInterface()->GetCombatMenu()->EnableItem(ZCombatMenu::ZCMI_CLOSE, false);
		}
		else
		{
			ZApplication::GetGameInterface()->GetCombatMenu()->EnableItem(ZCombatMenu::ZCMI_BATTLE_EXIT, true);
			ZApplication::GetGameInterface()->GetCombatMenu()->EnableItem(ZCombatMenu::ZCMI_STAGE_EXIT, true);
			//ZApplication::GetGameInterface()->GetCombatMenu()->EnableItem(ZCombatMenu::ZCMI_PROG_EXIT, true);
		}

	#endif
	}

Open(MBMatchServer_Stage.cpp - ValidateStageJoin - Replace)

	int MBMatchServer::ValidateStageJoin(const MUID& uidPlayer, const MUID& uidStage)
	{
		MMatchObject* pObj = GetObject(uidPlayer);
		if (!IsEnabledObject(pObj)) return MERR_CANNOT_JOIN_STAGE;

		MMatchStage* pStage = FindStage(uidStage);
		if (pStage == NULL) return MERR_CANNOT_JOIN_STAGE;

		if (pStage->GetState() == STAGE_STATE_CLOSE) return MERR_CANNOT_JOIN_STAGE;

		if (!IsAdminGrade(pObj))
		{
			if (pStage->GetStageType() == MST_PLAYERWARS && pStage->PlayerWarsTeam(pObj->GetCharInfo()->m_nCID) == MMT_ALL)
			{
				return MERR_CANNOT_JOIN_STAGE;
			}
			if (pStage->GetStageType() == MST_LADDER && pObj->GetCharInfo()->m_ClanInfo.m_nClanID != pStage->GetRedCLID() && pObj->GetCharInfo()->m_ClanInfo.m_nClanID != pStage->GetBlueCLID() && pObj->GetCharInfo())
			{
				return MERR_CANNOT_JOIN_STAGE;
			}
			if (pStage->GetStageSetting()->GetMaxPlayers() <= pStage->GetCountableObjCount())
			{
				return MERR_CANNOT_JOIN_STAGE_BY_MAXPLAYERS;
			}

			if (pStage->GetStageSetting()->GetLimitLevel() != 0)
			{
				int nMasterLevel, nLimitLevel;
				MMatchObject* pMaster = GetObject(pStage->GetMasterUID());

				if (IsEnabledObject(pMaster))
				{
					nMasterLevel = pMaster->GetCharInfo()->m_nLevel;
					nLimitLevel = pStage->GetStageSetting()->GetLimitLevel();
					if (abs(pObj->GetCharInfo()->m_nLevel - nMasterLevel) > nLimitLevel)
					{
						return MERR_CANNOT_JOIN_STAGE_BY_LEVEL;
					}
				}
			}

			if ((pStage->GetStageSetting()->GetForcedEntry() == false) &&
				(pStage->GetState() != STAGE_STATE_STANDBY))
			{
				return MERR_CANNOT_JOIN_STAGE_BY_FORCEDENTRY;
			}

			if (pStage->CheckBanList(pObj->GetCharInfo()->m_nCID))
				return MERR_CANNOT_JOIN_STAGE_BY_BAN;

		}

		return MOK;
	}

Open(OnProcessAsyncJob.cpp - pObj->FreeFriendInfo(); - Add under)

		pObj->FreePlayerWarsInfo();

Find(SendDuelTournamentCharInfoToPlayer(pJob->GetUID()); - Add under)

	SendPlayerWarsCharInfoToPlayer(pJob->GetUID());
	SendPlayerWarsSideRankingToPlayer(pJob->GetUID());


Some missing parts... <br>

Open(ZGameClient.h - DTCHARINFO				m_dtCharInfo, m_dtCharInfoPrev; - Add under)

	PWCHARINFO m_PWCharInfo;

Open(MMatchGlobal.h - typedef struct _MShortBuffInfo - Add under)

	typedef struct _PWRankingInfo
	{
		char m_szCharName[MATCHOBJECT_NAME_LENGTH];
		int m_nWins;
		int m_nLoses;
		int m_nRanking;
	} PWRankingInfo;

Open(MAsyncDBJob.h - MASYNCJOB_REWARD_CHAR_BR - Add under)

	MASYNCJOB_GET_PW_INFO,
	MASYNCJOB_UPDATE_PW_INFO,
	MASYNCJOB_GET_PW_SIDE_RANKING,


Open(MMatchDBMgr.h - GetLoginInfo - Add above)

	bool InsertPWGameLog(TCHAR* Winners, TCHAR* Losers, int WinningScore, int LosingScore, int MapID);

Open(ZGameInterface.h - OnGreeterDestroy(void); - Add under)

	void SelectBackground(int i);


Open(MMatchDBMgr.cpp - TCHAR g_spGetSurvivalPrivateRanking[] - Add under)

	TCHAR g_spGetPWCharacterInfo[] = _T("{CALL spPWGetCharacterInfo(%u)}");
	TCHAR g_spUpdatePWCharacterInfo[] = _T("{CALL spPWUpdateCharacterInfo(%u, %d, %d, %d, %d, %d)}");
	TCHAR g_PWGetSideRanking[] = _T("{CALL PWGetSideRanking(%u)}");

Open(ZCombatInterface.cpp - struct ZScoreBoardItem - Add under)

	float HP, AP, MaxHP, MaxAP;
	
Find (ZScoreBoardItem - Replace)

	ZScoreBoardItem( const MUID& _uidUID, char* _szLevel, char *_szName,char *_szClan,int _nTeam,bool _bDeath,int _nExp,int _nKills,int _nDeaths,int _nPing,int _nDTLastWeekGrade, bool _bMyChar,bool _bGameRoomUser, float hp, float ap, float maxhp, float maxap, bool _bCommander = false)
	{
		uidUID=_uidUID;
		strcpy(szLevel,_szLevel);
		strcpy(szName,_szName);
		strcpy(szClan,_szClan);
		nTeam=_nTeam;
		bDeath=_bDeath;
		nExp=_nExp;
		nKills=_nKills;
		nDeaths=_nDeaths;
		nPing=_nPing;
		bMyChar = _bMyChar;
		bCommander = _bCommander;
		bSpColor = false;
		SpColor = MCOLOR(0,0,0);
		bGameRoomUser = _bGameRoomUser;
		nDTLastWeekGrade = _nDTLastWeekGrade;
		HP = hp;
		AP = ap;
		MaxHP = maxhp;
		MaxAP = maxap;
	}
	
Find (ZScoreBoardItem() - Replace)


	ZScoreBoardItem() {
		bSpColor = false;
		SpColor = MCOLOR(0,0,0);
		HP = 0;
		AP = 0;
		MaxHP = 0;
		MaxAP = 0;
	}


Open(ZGameInterface.h - InitLadderUI(bool bLadderEnable); - Add under)

	void InitPlayerWarsUI(bool bPlayerWarsEnable);

Open(MMatchStage.h - unsigned long GetStartTime() - Add under)

	int GetRedCLID() { return m_nRedCLID; }
	int GetBlueCLID() { return m_nBlueCLID; }
	void SetCLID(int nCLID, MMatchTeam t) { switch (t) { case MMT_RED: m_nRedCLID = nCLID; break; case MMT_BLUE: m_nBlueCLID = nCLID; break; } }

Find (m_vecRelayMapsRemained - Add under)

	int						m_nRedCLID;
	int						m_nBlueCLID;


Open(MMatchServer.h - bool CanPlayerWars; - Add under)

	bool IsRunningCheck;

Find(const DWORD GetBuffCRC32Cache( const int nBuffID ); - Add under)

	unsigned long int CustomEventTimers[5];

Open(MMatchServer.cpp - CanPlayerWars = true; - Add under)

	IsRunningCheck = false;

Find (#define MINTERVAL_GARBAGE_SESSION_PING - Replace)

	#define MINTERVAL_GARBAGE_SESSION_PING	(7 * 60 * 1000)	// 7 min
		static unsigned long tmLastGarbageSessionCleaning = nGlobalClock;
		if (nGlobalClock - tmLastGarbageSessionCleaning > MINTERVAL_GARBAGE_SESSION_PING)
		{
			tmLastGarbageSessionCleaning = nGlobalClock;
			LOG(LOG_PROG, "GARBAGE SESSION CLEANING : m_This(%d%d), ClientCount=%d, SessionCount=%d, AgentCount=%d, CommandPool=%d, objHistoryCount=%d\n",
				m_This.High, m_This.Low, GetClientCount(), GetCommObjCount(), GetAgentCount(),
				CMemPool<MCommand>::GetCapacity(),
				m_objectCommandHistory.GetObjectCount());
			MCommand* pNew = CreateCommand(MC_NET_PING, MUID(0, 0));
			pNew->AddParameter(new MCmdParamUInt(nGlobalClock));
			RouteToAllConnection(pNew);
		}
		if (nGlobalClock - CustomEventTimers[5] >= 1200000)
		{
			tm* ptm = MMatchGetLocalTime();
			if (ptm->tm_wday == 1)
			{
				if (IsRunningCheck == false && ptm->tm_hour == 9 && ptm->tm_min >= 30)
				{
					IsRunningCheck = true;
					CanPlayerWars = false;
				}
				else if (CanPlayerWars == false && m_MatchDBMgr.IsPlayerWarsOpen() == 1)
				{
					CanPlayerWars = true;
				}
			}
			else if (ptm->tm_wday == 2 && CanPlayerWars == true)
			{
				IsRunningCheck = false;
			}
			CustomEventTimers[5] = nGlobalClock;
		}
		MGetCheckLoopTimeInstance()->SetLadderTick();
	#ifndef _QUESTCLAN
		if (MGetServerConfig()->GetServerMode() == MSM_CLAN)
	#endif
		{
			GetLadderMgr()->Tick(nGlobalClock);
			GetPlayerWarsMgr()->Tick();
		}
		if (MGetServerConfig()->IsEnabledDuelTournament() == true) {
			GetDTMgr()->Tick(nGlobalClock);
		}

		if (GetDTMgr()->GetTimeStampChanged() && MGetServerConfig()->IsEnabledDuelTournament()) {
			static DWORD dwLastRequestGetDTCharacterInfo = nGlobalClock;

			// ¸ðµç ÄÉ¸¯ÅÍ Á¤º¸¸¦ ¿äÃ»ÇÏ´Ùº¸¸é ºÎÇÏ°¡ °É¸± ¼ö ÀÖÀ¸¹Ç·Î, 1.5ÃÊ´ç 50°³¾¿ ¿äÃ»!
			// ¸ñÇ¥´Â 2ºÐ ¾È¿¡ ¸ðµÎ ½ÇÇà!
			if (nGlobalClock - dwLastRequestGetDTCharacterInfo > 1500) {
				dwLastRequestGetDTCharacterInfo = nGlobalClock;

				bool bAllSameTimeStamp = true;

				int nCount = 0;
				for (MMatchObjectList::iterator i = m_Objects.begin(); i != m_Objects.end(); i++) {
					MMatchObject *pObj = (MMatchObject*)((*i).second);
					MMatchObjectDuelTournamentCharInfo* pInfo = pObj->GetDuelTournamentCharInfo();
					if (!pObj || !pObj->GetCharInfo()) continue;
					if (nCount == 50) break;
					if (pInfo != NULL)
					{
						// Å¸ÀÓ ½ºÅÆÇÁ°¡ °°Àº ÄÉ¸¯ÅÍ°¡ ÀÖÀ» ¼öµµ ÀÖ´Ù. ´Ù¸¥ ÄÉ¸¯ÅÍ¸¸ ¿äÃ»!
						if (GetDTMgr()->IsSameTimeStamp(pInfo->GetTimeStamp()) == false) {
							bAllSameTimeStamp = false;

							// ÇöÀç °ÔÀÓ µà¾óÅä³Ê¸ÕÆ® °ÔÀÓ¿¡ Âü¿©ÇÏ°í ÀÖÁö ¾ÊÀº ÄÉ¸¯ÅÍ¸¸ Á¤º¸ ¿äÃ»!
							if (pObj->GetDuelTournamentCharInfo()->IsJoinDuelTournament() == false) {
								LOG(LOG_PROG, "Request Character Info, Character Previous Info(%d%d)", pObj->GetUID().High, pObj->GetUID().Low);

								OnAsyncRequest_GetDuelTournamentCharacterInfo(pObj->GetUID(), pObj->GetCharInfo()->m_nCID);
								OnAsyncRequest_GetDuelTournamentPreviousCharacterInfo(pObj->GetUID(), pObj->GetCharInfo()->m_nCID);

								nCount++;
							}
						}
					}
				}

				if (bAllSameTimeStamp) { GetDTMgr()->SetTimeStampChanged(false); }
			}
		}

		if (nGlobalClock - GetBattleTimeRewardMachine().GetLastUpdateTime() > MGetServerConfig()->GetBRDescriptionRefreshInterval())
		{
			GetBattleTimeRewardMachine().SetLastUpdateTime(nGlobalClock);

			MAsyncDBJob_GetBattleTimeRewardDescription *pJob = new MAsyncDBJob_GetBattleTimeRewardDescription;
			MMatchServer::GetInstance()->PostAsyncJob(pJob);
		}
		/* end of  shit */
		MGetServerStatusSingleton()->SetRunStatus(108);




XML (Default/Lobby.xml)


	<LABEL item="Lobby_PlayerWarsCount0" parent="Lobby_MainPlayerWarsBG">
		<FONT>FONTa9</FONT>
		<TEXTCOLOR>
			<R>173</R>
			<G>173</G>
			<B>173</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>100</X>
			<Y>164</Y> <!-- +14 -->
			<W>140</W>
			<H>20</H>
		</BOUNDS>
		<TEXT>0 Players Queuing</TEXT>
	</LABEL>
	<LABEL item="Lobby_PlayerWarsCount1" parent="Lobby_MainPlayerWarsBG">
		<FONT>FONTa9</FONT>
		<TEXTCOLOR>
			<R>173</R>
			<G>173</G>
			<B>173</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>100</X>
			<Y>178</Y> <!-- +14 -->
			<W>140</W>
			<H>20</H>
		</BOUNDS>
		<TEXT>0 Players Queuing</TEXT>
	</LABEL>
	<LABEL item="Lobby_PlayerWarsCount2" parent="Lobby_MainPlayerWarsBG">
		<FONT>FONTa9</FONT>
		<TEXTCOLOR>
			<R>173</R>
			<G>173</G>
			<B>173</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>100</X>
			<Y>192</Y> <!-- +14 -->
			<W>140</W>
			<H>20</H>
		</BOUNDS>
		<TEXT>0 Players Queuing</TEXT>
	</LABEL>
	<LABEL item="Lobby_PlayerWarsCount3" parent="Lobby_MainPlayerWarsBG">
		<FONT>FONTa9</FONT>
		<TEXTCOLOR>
			<R>173</R>
			<G>173</G>
			<B>173</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>100</X>
			<Y>206</Y> <!-- +14 -->
			<W>140</W>
			<H>20</H>
		</BOUNDS>
		<TEXT>0 Players Queuing</TEXT>
	</LABEL>
	<LABEL item="Lobby_PlayerWarsCount4" parent="Lobby_MainPlayerWarsBG">
		<FONT>FONTa9</FONT>
		<TEXTCOLOR>
			<R>173</R>
			<G>173</G>
			<B>173</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>100</X>
			<Y>220</Y> <!-- +14 -->
			<W>140</W>
			<H>20</H>
		</BOUNDS>
		<TEXT>0 Players Queuing</TEXT>
	</LABEL>
	<LABEL item="Lobby_PlayerWarsCount5" parent="Lobby_MainPlayerWarsBG">
		<FONT>FONTa9</FONT>
		<TEXTCOLOR>
			<R>173</R>
			<G>173</G>
			<B>173</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>100</X>
			<Y>234</Y> <!-- +14 -->
			<W>140</W>
			<H>20</H>
		</BOUNDS>
		<TEXT>0 Players Queuing</TEXT>
	</LABEL>
	<LABEL item="Lobby_PlayerWarsCount6" parent="Lobby_MainPlayerWarsBG">
		<FONT>FONTa9</FONT>
		<TEXTCOLOR>
			<R>173</R>
			<G>173</G>
			<B>173</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>100</X>
			<Y>248</Y> <!-- +14 -->
			<W>140</W>
			<H>20</H>
		</BOUNDS>
		<TEXT>0 Players Queuing</TEXT>
	</LABEL>
	<LABEL item="Lobby_PlayerWarsCount7" parent="Lobby_MainPlayerWarsBG">
		<FONT>FONTa9</FONT>
		<TEXTCOLOR>
			<R>173</R>
			<G>173</G>
			<B>173</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>100</X>
			<Y>262</Y> <!-- +14 -->
			<W>140</W>
			<H>20</H>
		</BOUNDS>
		<TEXT>0 Players Queuing</TEXT>
	</LABEL>
<PLAYERWARSRANKINGLIST item="Lobby_PlayerWarsRankingList" parent="Lobby_MainPlayerWarsBG">
		<BOUNDS>
			<X>530</X>
			<Y>140</Y>
			<W>250</W>
			<H>170</H>
		</BOUNDS>
	</PLAYERWARSRANKINGLIST>
	
	<LABEL item="Lobby_PlayerWarsName" parent="Lobby_MainPlayerWarsBG">
		<FONT>FONTa9</FONT>
		<TEXTCOLOR>
			<R>173</R>
			<G>173</G>
			<B>173</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>365</X>
			<Y>154</Y> <!-- -10 -->
			<W>140</W>
			<H>20</H>
		</BOUNDS>
		<TEXT></TEXT>
	</LABEL>
	
	<LABEL item="Lobby_PlayerWarsRanking" parent="Lobby_MainPlayerWarsBG">
		<FONT>FONTa9</FONT>
		<TEXTCOLOR>
			<R>173</R>
			<G>173</G>
			<B>173</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>365</X>
			<Y>180</Y>
			<W>40</W>
			<H>20</H>
		</BOUNDS>
		<TEXT></TEXT>
	</LABEL>
	<LABEL item="Lobby_PlayerWarsWins" parent="Lobby_MainPlayerWarsBG">
		<FONT>FONTa9</FONT>
		<TEXTCOLOR>
			<R>173</R>
			<G>173</G>
			<B>173</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>365</X>
			<Y>204</Y>
			<W>60</W>
			<H>20</H>
		</BOUNDS>
		<TEXT></TEXT>
	</LABEL>
	<LABEL item="Lobby_PlayerWarsLosses" parent="Lobby_MainPlayerWarsBG">
		<FONT>FONTa9</FONT>
		<TEXTCOLOR>
			<R>173</R>
			<G>173</G>
			<B>173</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>365</X>
			<Y>228</Y>
			<W>60</W>
			<H>20</H>
		</BOUNDS>
		<TEXT></TEXT>
	</LABEL>
	<LABEL item="Lobby_PlayerWarsDraws" parent="Lobby_MainPlayerWarsBG">
		<FONT>FONTa9</FONT>
		<TEXTCOLOR>
			<R>173</R>
			<G>173</G>
			<B>173</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>365</X>
			<Y>252</Y>
			<W>60</W>
			<H>20</H>
		</BOUNDS>
		<TEXT></TEXT>
	</LABEL>
	<LABEL item="Lobby_PlayerWarsScore" parent="Lobby_MainPlayerWarsBG">
		<FONT>FONTa9</FONT>
		<TEXTCOLOR>
			<R>173</R>
			<G>173</G>
			<B>173</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>365</X>
			<Y>276</Y>
			<W>60</W>
			<H>20</H>
		</BOUNDS>
		<TEXT></TEXT>
	</LABEL>
	<FRAME item="PlayerWarsMapVote" >
		<BOUNDS>
			<X>150</X>
			<Y>110</Y>
			<W>280</W>
			<H>100</H>
		</BOUNDS>
		<ALIGN>
			<HALIGN>center</HALIGN>
			<VALIGN>center</VALIGN>
		</ALIGN>
		<VISIBLE>false</VISIBLE>
		<MOVABLE>false</MOVABLE>
		<RESIZABLE>false</RESIZABLE>
		<FRAMELOOK>DefaultFrameLook</FRAMELOOK>
		<TEXT>Player Wars Map Vote</TEXT> <!-- 팀 게임 -->
	</FRAME>
	<LABEL item="PlayerWarsMap0" parent="PlayerWarsMapVote">
		<TEXTCOLOR>
			<R>200</R>
			<G>200</G>
			<B>200</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>12</X>
			<Y>20</Y>
			<W>110</W>
			<H>28</H>
		</BOUNDS>
		<TEXT></TEXT> <!-- 최대 인원 -->
		<SELECTED>true</SELECTED>
	</LABEL>
	<LABEL item="PlayerWarsMap1" parent="PlayerWarsMapVote">
		<TEXTCOLOR>
			<R>200</R>
			<G>200</G>
			<B>200</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>112</X>
			<Y>20</Y>
			<W>110</W>
			<H>28</H>
		</BOUNDS>
		<TEXT></TEXT> <!-- 최대 인원 -->
		<SELECTED>true</SELECTED>
	</LABEL>
	<LABEL item="PlayerWarsMap2" parent="PlayerWarsMapVote">
		<TEXTCOLOR>
			<R>200</R>
			<G>200</G>
			<B>200</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>217</X>
			<Y>20</Y>
			<W>110</W>
			<H>28</H>
		</BOUNDS>
		<TEXT></TEXT> <!-- 최대 인원 -->
		<SELECTED>true</SELECTED>
	</LABEL>
	
	<LABEL item="PlayerWarsVote0" parent="PlayerWarsMapVote">
		<TEXTCOLOR>
			<R>200</R>
			<G>200</G>
			<B>200</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>12</X>
			<Y>40</Y>
			<W>110</W>
			<H>28</H>
		</BOUNDS>
		<TEXT>Votes: 0</TEXT> <!-- 최대 인원 -->
		<SELECTED>true</SELECTED>
	</LABEL>
	
	<BUTTON item="PlayerWarsVoteButton0" parent="PlayerWarsMapVote">
		<BUTTONLOOK>DefaultButtonLook</BUTTONLOOK>
		<ANCHORS>
			<LEFT>false</LEFT>
			<TOP>false</TOP>
			<RIGHT>true</RIGHT>
			<BOTTOM>true</BOTTOM>
		</ANCHORS>
		<BOUNDS>
			<X>5</X>
			<Y>60</Y>
			<W>60</W>
			<H>32</H>
		</BOUNDS>
		<TEXT>Vote</TEXT> <!-- 확인(&amp;O) -->
	</BUTTON>
	<LABEL item="PlayerWarsVote1" parent="PlayerWarsMapVote">
		<TEXTCOLOR>
			<R>200</R>
			<G>200</G>
			<B>200</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>112</X>
			<Y>40</Y>
			<W>110</W>
			<H>28</H>
		</BOUNDS>
		<TEXT>Votes: 0</TEXT>
		<SELECTED>true</SELECTED>
	</LABEL>
	<BUTTON item="PlayerWarsVoteButton1" parent="PlayerWarsMapVote">
		<BUTTONLOOK>DefaultButtonLook</BUTTONLOOK>
		<ANCHORS>
			<LEFT>false</LEFT>
			<TOP>false</TOP>
			<RIGHT>true</RIGHT>
			<BOTTOM>true</BOTTOM>
		</ANCHORS>
		<BOUNDS>
			<X>105</X>
			<Y>60</Y>
			<W>60</W>
			<H>32</H>
		</BOUNDS>
		<TEXT>Vote</TEXT> <!-- 확인(&amp;O) -->
	</BUTTON>
	<LABEL item="PlayerWarsVote2" parent="PlayerWarsMapVote">
		<TEXTCOLOR>
			<R>200</R>
			<G>200</G>
			<B>200</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>212</X>
			<Y>40</Y>
			<W>110</W>
			<H>28</H>
		</BOUNDS>
		<TEXT>Votes: 0</TEXT>
		<SELECTED>true</SELECTED>
	</LABEL>
	<BUTTON item="PlayerWarsVoteButton2" parent="PlayerWarsMapVote">
		<BUTTONLOOK>DefaultButtonLook</BUTTONLOOK>
		<ANCHORS>
			<LEFT>false</LEFT>
			<TOP>false</TOP>
			<RIGHT>true</RIGHT>
			<BOTTOM>true</BOTTOM>
		</ANCHORS>
		<BOUNDS>
			<X>205</X>
			<Y>60</Y>
			<W>60</W>
			<H>32</H>
		</BOUNDS>
		<TEXT>Vote</TEXT> <!-- 확인(&amp;O) -->
	</BUTTON>
	<FRAME item="PlayerWarsGameDialog" >
		<BOUNDS>
			<X>240</X>
			<Y>110</Y>
			<W>280</W>
			<H>120</H>
		</BOUNDS>
		<ALIGN>
			<HALIGN>center</HALIGN>
			<VALIGN>center</VALIGN>
		</ALIGN>
		<VISIBLE>false</VISIBLE>
		<MOVABLE>false</MOVABLE>
		<RESIZABLE>false</RESIZABLE>
		<FRAMELOOK>DefaultFrameLook</FRAMELOOK>
		<TEXT>Player Wars Options</TEXT> <!-- 팀 게임 -->
	</FRAME>
	<LABEL item="GameTypeLabel" parent="PlayerWarsGameDialog">
		<TEXTCOLOR>
			<R>200</R>
			<G>200</G>
			<B>200</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>63</X>
			<Y>35</Y>
			<W>110</W>
			<H>28</H>
		</BOUNDS>
		<TEXT>GameType:</TEXT> <!-- 최대 인원 -->
		<CHECKED>true</CHECKED>
		<SELECTED>true</SELECTED>
	</LABEL>
	
	<COMBOBOX item="PlayerWarsGameType" parent="PlayerWarsGameDialog">
		<LISTBOXLOOK>CustomListBoxLook</LISTBOXLOOK>
		<BUTTONLOOK>ListBoxButtonLook</BUTTONLOOK>
		<FONT>FONTa9</FONT>
		<TEXTCOLOR>
			<R>205</R>
			<G>205</G>
			<B>205</B>
		</TEXTCOLOR>
		<TEXTALIGN>
			<VALIGN>center</VALIGN>
			<HALIGN>center</HALIGN>
		</TEXTALIGN>
		<BOUNDS>
			<X>140</X>
			<Y>40</Y>
			<W>110</W>
			<H>18</H>
		</BOUNDS>
		<LISTITEM selected="true">1 vs 1</LISTITEM>
		<LISTITEM>2 vs 2</LISTITEM>
		<LISTITEM>3 vs 3</LISTITEM>
		<LISTITEM>4 vs 4</LISTITEM>
		<LISTITEM>5 vs 5</LISTITEM>
		<LISTITEM>6 vs 6</LISTITEM>
		<LISTITEM>7 vs 7</LISTITEM>
		<LISTITEM>8 vs 8</LISTITEM>
		<DROPSIZE>140</DROPSIZE>
		<COMBOTYPE>1</COMBOTYPE>
	</COMBOBOX>
	<BUTTON item="PlayerWarsDialogClose" parent="PlayerWarsGameDialog">
		<BUTTONLOOK>DefaultButtonLook</BUTTONLOOK>
		<ANCHORS>
			<LEFT>false</LEFT>
			<TOP>false</TOP>
			<RIGHT>true</RIGHT>
			<BOTTOM>true</BOTTOM>
		</ANCHORS>
		<BOUNDS>
			<X>60</X>
			<Y>65</Y>
			<W>90</W>
			<H>32</H>
		</BOUNDS>
		<DEFAULTKEY>ESC</DEFAULTKEY>
		<TEXT>STR:UI_LOBBY_18</TEXT> <!-- 취소(&amp;C) -->
	</BUTTON>
	<BUTTON item="PlayerWarsDialogOk" parent="PlayerWarsGameDialog">
		<BUTTONLOOK>DefaultButtonLook</BUTTONLOOK>
		<ANCHORS>
			<LEFT>false</LEFT>
			<TOP>false</TOP>
			<RIGHT>true</RIGHT>
			<BOTTOM>true</BOTTOM>
		</ANCHORS>
		<BOUNDS>
			<X>160</X>
			<Y>65</Y>
			<W>90</W>
			<H>32</H>
		</BOUNDS>
		<TEXT>STR:UI_LOBBY_17</TEXT> <!-- 확인(&amp;O) -->
	</BUTTON>

XML(Default/ChannelListFrame.xml)

	<BUTTON item="ChannelList_PlayerWars" parent="ChannelListFrame">	
		<BUTTONLOOK>DefaultButtonLook</BUTTONLOOK>
		<ANCHORS>
			<LEFT>true</LEFT>
			<TOP>true</TOP>
			<RIGHT>true</RIGHT>
			<BOTTOM>true</BOTTOM>
		</ANCHORS>
		<BOUNDS>
			<X>15</X>
			<Y>219</Y>
			<W>110</W>
			<H>32</H>
		</BOUNDS>
		<TEXT>Player Wars</TEXT> <!-- 듀얼토너먼트 -->
		<GROUP>ChannelList</GROUP>
	</BUTTON>

XML(Default/Lobby.xml)

	<!-- Button : 클랜전 결성 버튼 -->
	<BMBUTTON item ="ArrangedPlayerWars" parent="Lobby">
		<BOUNDS>
			<X>320</X>
			<Y>313</Y>
			<W>203</W>
			<H>42</H>
		</BOUNDS>
		<STRETCH/>
		<VISIBLE>false</VISIBLE>
		<BITMAP type="up">playerwars_off_kr.tga</BITMAP>
		<BITMAP type="over">playerwars_on_kr.tga</BITMAP>
		<BITMAP type="down">playerwars_on_kr.tga</BITMAP>
	</BMBUTTON>

Forgot this part too

Open(MSharedCommandTable.cpp - Scroll all the way down and add this code...)

	C(MC_MATCH_PLAYERWARS_CHARINFO, "ga15g5awfwa", "hssgseo", MCDT_MACHINE2MACHINE)//MC_MATCH_PLAYERWARS_CHARINFO
		P(MPT_INT, "Ranking")
		P(MPT_INT, "Wins")
		P(MPT_INT, "Loses")
		P(MPT_INT, "Draws")
		P(MPT_INT, "Score")
	C(MC_MATCH_PLAYERWARS_COUNTER, "MC_MATCH_PLAYERWARS_COUNTER", "Player Wars Counter Info", MCDT_MACHINE2MACHINE)
		P(MPT_BLOB, "Data")
	C(MC_MATCH_PLAYERWARS_SIDERANK, "MC_MATCH_PLAYERWARS_SIDERANK", "Player Wars Side Rank Info", MCDT_MACHINE2MACHINE)
		P(MPT_BLOB, "Data")


























