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














































































  
  
  
  
  
  
  



