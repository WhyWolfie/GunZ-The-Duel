Gamemode: Infected <br>

#define INFECTED_MIN_PLAYER_COUNT 4 (2) players <br>

Open(MBaseGameType.h) <br>
Find <br> 

    enum MMATCH_GAMETYPE {

Add <br>

    MMATCH_GAMETYPE_INFECTED			=19,

Find <br>

    inline bool MBaseGameTypeCatalogue::IsTeamGame(MMATCH_GAMETYPE nGameType)
    {

Add <br>

    (nGameType == MMATCH_GAMETYPE_INFECTED) ||

Find <br>

    inline bool MBaseGameTypeCatalogue::IsTeamLimitTime

Add <br>
  
    (nGameType == MMATCH_GAMETYPE_INFECTED) ||

Find <br>

    inline bool MBaseGameTypeCatalogue::IsWaitForRoundEnd

Add <br>

    (nGameType == MMATCH_GAMETYPE_INFECTED) ||


Open(MMatchRuleDeathMatch.h) <br>
Find <br>

    class MMatchRuleSoloDeath : public MMatchRule {

Add <br>

    class MMatchRuleTeamInfected : public MMatchRule
    {
    private:
      bool m_bInfectionStarted;
      const MUID ChooseInfected();
      MUID m_uidPatientZero;
      list<MUID> m_uidSurvivors;
      //list<int> m_PickHistory;

    protected:
      bool GetAliveCount(int* pRedAliveCount, int* pBlueAliveCount);
      virtual void OnBegin();
      virtual void OnEnd();
      virtual bool OnRun();
      void SetInfectedRoundState(MMATCH_ROUNDSTATE nState);
      //void OnPreCountDown();
      virtual void OnRoundBegin();
      virtual void OnRoundEnd();
      virtual void OnEnterBattle(MUID& uidChar);
      virtual void OnLeaveBattle(MUID& uidChar);
      virtual bool OnCheckRoundFinish();
      virtual void OnRoundTimeOut();
      virtual bool RoundCount();
      virtual bool OnCheckEnableBattleCondition();
      virtual void OnGameKill(const MUID& uidAttacker, const MUID& uidVictim);
      virtual void OnCommand(MCommand* pCommand);
      void OnInfectPlayer(const MUID& uidInfector, const MUID& uidVictim);

    public:
      MMatchRuleTeamInfected(MMatchStage* pStage);
      virtual ~MMatchRuleTeamInfected() {}
      virtual void CalcTeamBonus(MMatchObject* pAttacker, MMatchObject* pVictim,
        int nSrcExp, int* poutAttackerExp, int* poutTeamExp);
      virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_INFECTED; }
      virtual void* CreateRuleInfoBlob();
    };

Open(MBaseGameType.cpp) <br>
Find <br>

    #define MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR		"Death Match(Solo)"


Add <br>

    #define MMATCH_GAMETYPE_INFECTED_STR			"Infected"

Find <br>

    _InitGameType(MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR,  1.0f,			1.0f,					0.0f);

Add <br>

    _InitGameType(MMATCH_GAMETYPE_INFECTED, MMATCH_GAMETYPE_INFECTED, MMATCH_GAMETYPE_INFECTED_STR, 1.0f, 0.7f, 0.6f);

Open(MMatchRuleDeathMatch.cpp) <br>
Find <br>

    MMatchRuleTeamDeath::MMatchRuleTeamDeath(MMatchStage* pStage) : MMatchRule(pStage)
    {
    }

Add <br>

    // Infected Mode
    // red -> infected
    // blue -> survivors
    #define INFECTED_MIN_PLAYER_COUNT 4

    MMatchRuleTeamInfected::MMatchRuleTeamInfected(MMatchStage* pStage) : MMatchRule(pStage)
    {
      m_bInfectionStarted = false;
    }

    void MMatchRuleTeamInfected::OnBegin()
    {
    }

    void MMatchRuleTeamInfected::OnEnd()
    {
    }

    void MMatchRuleTeamInfected::SetInfectedRoundState(MMATCH_ROUNDSTATE nState)
    {
      if (m_nRoundState == nState) return;

      m_nRoundState = nState;
      SetRoundStateTimer(MMatchServer::GetInstance()->GetGlobalClockCount());

      if (nState == MMATCH_ROUNDSTATE_COUNTDOWN)
      {
        InitRound();
      }
      else if (nState == MMATCH_ROUNDSTATE_PRE_COUNTDOWN)
      {
        // don't know what to do with this now
        //OnPreCountDown();
      }
      else if (nState == MMATCH_ROUNDSTATE_PLAY)
      {
        OnRoundBegin();
      }
      else if (nState == MMATCH_ROUNDSTATE_FINISH)
      {
        OnRoundEnd();
      }
      else if (nState == MMATCH_ROUNDSTATE_FREE)
      {
        m_bInfectionStarted = false;
        m_uidSurvivors.clear();
        OnRoundEnd(); // force round end..
      }

      MMatchServer::GetInstance()->ResponseRoundState(GetStage()->GetUID());
    }

    bool MMatchRuleTeamInfected::OnRun()
    {
      DWORD nClock = MMatchServer::GetInstance()->GetGlobalClockCount();

      switch (GetRoundState())
      {
      case MMATCH_ROUNDSTATE_PREPARE:
      {
        if (GetStage()->CheckBattleEntry() == true)
        {
          if (OnCheckEnableBattleCondition())
          {
            if (!m_bInfectionStarted)	SetInfectedRoundState(MMATCH_ROUNDSTATE_PRE_COUNTDOWN);
            else								SetInfectedRoundState(MMATCH_ROUNDSTATE_COUNTDOWN);
          }
          else									SetInfectedRoundState(MMATCH_ROUNDSTATE_FREE);
        }
        return true;

      }

      case MMATCH_ROUNDSTATE_PRE_COUNTDOWN:
      {
        DWORD dwPeriod = 3000;

        if (nClock - GetRoundStateTimer() > dwPeriod) { SetInfectedRoundState(MMATCH_ROUNDSTATE_COUNTDOWN); }
        return true;
      }

      case MMATCH_ROUNDSTATE_COUNTDOWN: {
        if (nClock - GetRoundStateTimer() > 2 * 1000) { SetInfectedRoundState(MMATCH_ROUNDSTATE_PLAY); }
        return true;
      }

      case MMATCH_ROUNDSTATE_PLAY: {
        // °ÔÀÓÇÏÁö ¸øÇÒ »óÈ²ÀÌ¸é Free»óÅÂ·Î º¯È¯
        if (!OnCheckEnableBattleCondition()) { SetInfectedRoundState(MMATCH_ROUNDSTATE_FREE); }

        if (OnCheckRoundFinish())
        {
          SetInfectedRoundState(MMATCH_ROUNDSTATE_FINISH);
        }
        else if (OnCheckBattleTimeOut(nClock - GetRoundStateTimer()))
        {
          OnRoundTimeOut();
          SetInfectedRoundState(MMATCH_ROUNDSTATE_FINISH);
        }
        CheckOnGameEvent();
        return true;
      }

      case MMATCH_ROUNDSTATE_FINISH:
      {
        if (nClock - GetRoundStateTimer() > 3 * 1000) {
          if (RoundCount() == true)	{ SetInfectedRoundState(MMATCH_ROUNDSTATE_PREPARE); }
          else						{ SetInfectedRoundState(MMATCH_ROUNDSTATE_EXIT); }
        }
        return true;
      }

      case MMATCH_ROUNDSTATE_FREE: {
        if (OnCheckEnableBattleCondition()) { SetInfectedRoundState(MMATCH_ROUNDSTATE_PREPARE); }
        return true;
      }

      case MMATCH_ROUNDSTATE_EXIT: {
        return false;
      }

      default: {
        _ASSERT(0);
        return false;
      }
      }

      return false;
    }

    void MMatchRuleTeamInfected::OnRoundBegin()
    {
      // push commandId: MC_MATCH_SET_COMMANDER
      // swap all users to other team
      MMatchServer* pServer = MMatchServer::GetInstance();
      MMatchStage* pStage = GetStage();
      if (pServer == NULL || pStage == NULL) return;

      // force a damn shuffle
      //pStage->ShuffleTeamMembers();

      m_uidPatientZero = ChooseInfected();
      if (m_uidPatientZero == MUID(0, 0))
      {
        // aww ;-;
        mlog("<Infected> m_uidPatientZero could not be chosen.\n");
        SetRoundState(MMATCH_ROUNDSTATE_FREE);
        return;
      }
      MMatchObject* pObj = MMatchServer::GetInstance()->GetObject(m_uidPatientZero);

      if (!IsEnabledObject(pObj))
      {
        mlog("<Infected> m_uidPatientZero chosen but disconnected, object handle lost?\n");
        SetRoundState(MMATCH_ROUNDSTATE_FREE);
        return;
      }

      pStage->SwitchPlayerTeamForInfected(m_uidPatientZero);

      for (MUIDRefCache::iterator i = pStage->GetObjBegin(); i != pStage->GetObjEnd(); i++)
      {
        MMatchObject* pObj = (MMatchObject*)(*i).second;

        if ((pObj->GetEnterBattle() == true) && (pObj->GetGameInfo()->bJoinedGame == true) && !pObj->CheckPlayerFlags(MTD_PlayerFlags_AdminHide))
        {
          if (pObj->CheckAlive() && pObj->GetTeam() == MMT_BLUE)
          {
            m_uidSurvivors.push_back(pObj->GetUID());
          }
        }
      }

      // fuck logic
      //if (pObj->GetTeam() != MMT_RED)
      //	pStage->SwitchPlayerTeam(m_uidPatientZero, false);

      //pStage->SwitchPlayerTeam(m_uidPatientZero, true);

      m_bInfectionStarted = true;

      // notify the infection
      MCommand* pCmd = pServer->CreateCommand(MC_MATCH_ASSIGN_COMMANDER, MUID(0, 0));
      pCmd->AddParameter(new MCmdParamUID(m_uidPatientZero));
      pCmd->AddParameter(new MCmdParamUID(MUID(0, 0))); // unused
      pServer->RouteToStage(pStage->GetUID(), pCmd);
    }

    void MMatchRuleTeamInfected::OnRoundEnd()
    {
      if (m_pStage != NULL)
      {
        m_bInfectionStarted = false;
        m_pStage->SwitchPlayerTeamForInfected(m_uidPatientZero);

        switch (m_nRoundArg)
        {
        case MMATCH_ROUNDRESULT_BLUE_ALL_OUT: m_pStage->OnRoundEnd_FromTeamGame(MMT_RED); break;
        case MMATCH_ROUNDRESULT_RED_ALL_OUT: m_pStage->OnRoundEnd_FromTeamGame(MMT_BLUE); break;
        case MMATCH_ROUNDRESULT_REDWON: m_pStage->OnRoundEnd_FromTeamGame(MMT_RED); break;
        case MMATCH_ROUNDRESULT_BLUEWON: m_pStage->OnRoundEnd_FromTeamGame(MMT_BLUE); break;
        case MMATCH_ROUNDRESULT_DRAW: break;
        }

        m_uidSurvivors.clear();
        // do it!
        //m_pStage->ShuffleTeamMembers(); // shuffle next time
      }

      MMatchRule::OnRoundEnd();
    }

    const MUID MMatchRuleTeamInfected::ChooseInfected()
    {
      MMatchStage* pStage = GetStage();
      if (pStage == NULL) return MUID(0, 0);

      int nRedAliveCount, nBlueAliveCount, nChooseTeamCount;
      if (GetAliveCount(&nRedAliveCount, &nBlueAliveCount) == false)
        return MUID(0, 0);

      if ((nRedAliveCount + nBlueAliveCount) < INFECTED_MIN_PLAYER_COUNT)
        return MUID(0, 0);

      nChooseTeamCount = nRedAliveCount + nBlueAliveCount;

      MTime time;
      int nChoose = time.MakeNumber(1, nChooseTeamCount);

      //if (m_PickHistory.size() > 4)
      //	m_PickHistory.pop_front();

      //m_PickHistory.push_back(nChoose);

      //// avoid similar instances. infinite loop lol
      //while (true)
      //{
      //	if (std::find(m_PickHistory.begin(), m_PickHistory.end(), nChoose) != m_PickHistory.end())
      //	{
      //		// seek forward
      //		if (nChoose < nChooseTeamCount)
      //			++nChoose;
      //		else if (nChoose > 0)
      //			--nChoose;
      //	}
      //	else
      //		break;
      //}

      int nCount = 0;
      for (MUIDRefCache::iterator itor = pStage->GetObjBegin(); itor != pStage->GetObjEnd(); itor++)
      {
        MMatchObject* pObj = (MMatchObject*)(*itor).second;
        if (pObj->GetEnterBattle() == false || pObj->CheckPlayerFlags(MTD_PlayerFlags_AdminHide)) continue;

        nCount++;
        if (nCount == nChoose)
          return pObj->GetUID();
      }

      return MUID(0, 0);
    }

    bool MMatchRuleTeamInfected::GetAliveCount(int* pRedAliveCount, int* pBlueAliveCount)
    {
      int nRedCount = 0, nBlueCount = 0;
      int nRedAliveCount = 0, nBlueAliveCount = 0;
      (*pRedAliveCount) = 0;
      (*pBlueAliveCount) = 0;

      MMatchStage* pStage = GetStage();
      if (pStage == NULL) return false;

      for (MUIDRefCache::iterator i = pStage->GetObjBegin(); i != pStage->GetObjEnd(); i++)
      {
        MMatchObject* pObj = (MMatchObject*)(*i).second;
        if (pObj->GetEnterBattle() == false) continue;	// ¹èÆ²Âü°¡ÇÏ°í ÀÖ´Â ÇÃ·¹ÀÌ¾î¸¸ Ã¼Å©

        if (pObj->GetTeam() == MMT_RED)
        {
          nRedCount++;
          if (pObj->CheckAlive() == true)
          {
            nRedAliveCount++;
          }
        }
        else if (pObj->GetTeam() == MMT_BLUE)
        {
          nBlueCount++;
          if (pObj->CheckAlive() == true)
          {
            nBlueAliveCount++;
          }
        }
      }

      (*pRedAliveCount) = nRedAliveCount;
      (*pBlueAliveCount) = nBlueAliveCount;

      if (m_bInfectionStarted)
      {
        if (nRedAliveCount == 0 || nBlueAliveCount == 0)
          return false;

        //if (nRedAliveCount + nBlueAliveCount == 0)
        //	return false;
      }
      else
      {
        if (nRedAliveCount + nBlueAliveCount == 0 || (nRedAliveCount + nBlueAliveCount == 0 && m_uidPatientZero.IsValid()))
          return false;

      }

      //if (GetRoundState() != MMATCH_ROUNDSTATE_PLAY)
      //{
      //	if (nRedAliveCount + nBlueAliveCount == 0)
      //		return false;
      //}
      //else if ((nRedAliveCount == 0) || (nBlueAliveCount == 0))
      //{
      //	return false;
      //}
      return true;
    }

    bool MMatchRuleTeamInfected::OnCheckRoundFinish()
    {
      int nRedAliveCount = 0;
      int nBlueAliveCount = 0;

      MMatchStage* pStage = GetStage();
      if (pStage == NULL)
      {
        SetRoundArg(MMATCH_ROUNDRESULT_DRAW);
        return true;
      }

      if (m_bInfectionStarted && GetAliveCount(&nRedAliveCount, &nBlueAliveCount) == false)
      {
        int nRedTeam = 0, nBlueTeam = 0;
        int nStageObjects = 0;

        for (MUIDRefCache::iterator i = pStage->GetObjBegin(); i != pStage->GetObjEnd(); i++)
        {
          MMatchObject* pObj = (MMatchObject*)(*i).second;
          if ((pObj->GetEnterBattle() == false) && (!pObj->IsLaunchedGame()))
          {
            nStageObjects++;
            continue;
          }

          if (pObj->GetTeam() == MMT_RED)		nRedTeam++;
          else if (pObj->GetTeam() == MMT_BLUE)	nBlueTeam++;
        }

        MMatchObject* pInfectedObj = MMatchServer::GetInstance()->GetObject(m_uidPatientZero);
        if ((pInfectedObj == NULL) || (pInfectedObj->GetStageUID() != pStage->GetUID()))
        {
          SetRoundArg(MMATCH_ROUNDRESULT_BLUEWON);
          return true;
        }

        if (pInfectedObj->CheckAlive() == false)
        {
          SetRoundArg(MMATCH_ROUNDRESULT_BLUEWON);
          return true;
        }

        if (nRedAliveCount == 0)
        {
          SetRoundArg(MMATCH_ROUNDRESULT_BLUEWON);
          return true;
        }
        else if (nBlueAliveCount == 0 && m_uidSurvivors.size() > 0)
        {
          SetRoundArg(MMATCH_ROUNDRESULT_REDWON);
          return true;
        }
        else
        {
          SetRoundArg(MMATCH_ROUNDRESULT_DRAW);
          return true;
        }
        //if( nBlueTeam ==0 && (pStage->GetTeamScore(MMT_BLUE) > pStage->GetTeamScore(MMT_RED)) )
        //	SetRoundArg(MMATCH_ROUNDRESULT_BLUE_ALL_OUT);
        //else if( nRedTeam ==0 && (pStage->GetTeamScore(MMT_RED) > pStage->GetTeamScore(MMT_BLUE)) )
        //	SetRoundArg(MMATCH_ROUNDRESULT_RED_ALL_OUT);
        //else if ( (nRedAliveCount == 0) && (nBlueAliveCount == 0) )
        //	SetRoundArg(MMATCH_ROUNDRESULT_DRAW);
        //else if (nRedAliveCount == 0)
        //	SetRoundArg(MMATCH_ROUNDRESULT_BLUEWON);
        //else if (nBlueAliveCount == 0)
        //	SetRoundArg(MMATCH_ROUNDRESULT_REDWON);
      }

      if (nRedAliveCount == 0 || nBlueAliveCount == 0) return true;
      else return false;
    }

    bool MMatchRuleTeamInfected::RoundCount()
    {
      if (m_pStage == NULL) return false;

      int nTotalRound = m_pStage->GetStageSetting()->GetRoundMax();
      m_nRoundCount++;

      if (m_nRoundCount < nTotalRound) return true;

      return false;
    }

    void MMatchRuleTeamInfected::OnRoundTimeOut()
    {
      int nRedAliveCount = 0;
      int nBlueAliveCount = 0;
      GetAliveCount(&nRedAliveCount, &nBlueAliveCount);

      // red never wins unless they kill all :D
      if (nBlueAliveCount > 0)
        SetRoundArg(MMATCH_ROUNDRESULT_BLUEWON);
      else
        SetRoundArg(MMATCH_ROUNDRESULT_DRAW);

      //if (nRedAliveCount > nBlueAliveCount)
      //	SetRoundArg(MMATCH_ROUNDRESULT_REDWON);
      //else if (nBlueAliveCount > nRedAliveCount)
      //	SetRoundArg(MMATCH_ROUNDRESULT_BLUEWON);
      //else SetRoundArg(MMATCH_ROUNDRESULT_DRAW);
    }

    bool MMatchRuleTeamInfected::OnCheckEnableBattleCondition()
    {
      int nRedTeam = 0, nBlueTeam = 0;
      int nPreRedTeam = 0, nPreBlueTeam = 0;
      int nStageObjects = 0;

      MMatchStage* pStage = GetStage();
      if (pStage == NULL) return false;

      for (MUIDRefCache::iterator i = pStage->GetObjBegin(); i != pStage->GetObjEnd(); i++)
      {
        MMatchObject* pObj = (MMatchObject*)(*i).second;
        if ((pObj->GetEnterBattle() == false && !pObj->IsLaunchedGame()) || pObj->CheckPlayerFlags(MTD_PlayerFlags_AdminHide))
        {
          nStageObjects++;
          continue;
        }

        if (pObj->GetTeam() == MMT_RED)
        {
          nRedTeam++;
        }
        else if (pObj->GetTeam() == MMT_BLUE)
        {
          nBlueTeam++;
        }
      }

      if ((nRedTeam + nBlueTeam) < INFECTED_MIN_PLAYER_COUNT)
      {
        return false;
      }
      //if ( nRedTeam == 0 || nBlueTeam == 0)
      //{
      //	return false;
      //}

      return true;
    }

    void MMatchRuleTeamInfected::OnEnterBattle(MUID& uidChar)
    {
      MMatchObject* pChar = MMatchServer::GetInstance()->GetObject(uidChar);
      if (!pChar) return;
      if (!IsEnabledObject(pChar)) return;

      if (m_pStage != NULL)
      {
        if (GetRoundState() == MMATCH_ROUNDSTATE_PLAY)
        {
          // todo: create a state sync packet :: just sync for now
          list<MUID> listInfected;
          for (MUIDRefCache::iterator i = m_pStage->GetObjBegin(); i != m_pStage->GetObjEnd(); i++)
          {
            MMatchObject* pObj = (MMatchObject*)(*i).second;
            if ((pObj->GetEnterBattle() == false && !pObj->IsLaunchedGame()) || pObj->CheckPlayerFlags(MTD_PlayerFlags_AdminHide))
            {
              continue;
            }

            if (pObj->GetTeam() == MMT_RED && pObj->CheckAlive() && pObj->GetUID() != m_uidPatientZero)
            {
              listInfected.push_back(pObj->GetUID());
            }
          }

          for (list<MUID>::iterator it = listInfected.begin(); it != listInfected.end(); ++it)
          {
            // TODO: a state blob
            MCommand* pNew = MMatchServer::GetInstance()->CreateCommand(MC_MATCH_INFECT, MUID(0, 0));
            pNew->AddParameter(new MCmdParamUID((*it)));
            MMatchServer::GetInstance()->RouteToListener(pChar, pNew);
          }
        }
      }
    }

    void MMatchRuleTeamInfected::OnLeaveBattle(MUID& uidChar)
    {
      MMatchObject* pChar = MMatchServer::GetInstance()->GetObject(uidChar);

      if (m_pStage != NULL)
      {
        // remove player
        list<MUID>::iterator it = m_uidSurvivors.begin();

        while (it != m_uidSurvivors.end())
        {
          if ((*it) == uidChar)
          {
            it = m_uidSurvivors.erase(it);
            break;
          }
          else
            ++it;
        }
      }
    }

    void MMatchRuleTeamInfected::OnGameKill(const MUID& uidAttacker, const MUID& uidVictim)
    {
      MMatchObject* pAttacker = MMatchServer::GetInstance()->GetObject(uidAttacker);
      MMatchObject* pVictim = MMatchServer::GetInstance()->GetObject(uidVictim);

      if (m_pStage != NULL)
      {
        if (pAttacker != NULL && pVictim != NULL && pAttacker == pVictim)
        {
          return;
        }

        if (pVictim->GetTeam() != MMT_RED)
        {
          MUID uidAttacker = pAttacker ? pAttacker->GetUID() : MUID(0, 0);
          MUID uidVictim = pVictim ? pVictim->GetUID() : MUID(0, 0);
          OnInfectPlayer(uidAttacker, uidVictim);
        }
      }
    }

    void MMatchRuleTeamInfected::CalcTeamBonus(MMatchObject* pAttacker, MMatchObject* pVictim,
      int nSrcExp, int* poutAttackerExp, int* poutTeamExp)
    {
      if (m_pStage == NULL)
      {
        *poutAttackerExp = nSrcExp;
        *poutTeamExp = 0;
        return;
      }

      *poutTeamExp = (int)(nSrcExp * m_pStage->GetStageSetting()->GetCurrGameTypeInfo()->fTeamBonusExpRatio);
      *poutAttackerExp = (int)(nSrcExp * m_pStage->GetStageSetting()->GetCurrGameTypeInfo()->fTeamMyExpRatio);
    }

    void MMatchRuleTeamInfected::OnInfectPlayer(const MUID& uidInfector, const MUID& uidVictim)
    {
      MMatchObject* pInfector = MMatchServer::GetInstance()->GetObject(uidInfector);
      MMatchObject* pVictim = MMatchServer::GetInstance()->GetObject(uidVictim);

      if (!IsEnabledObject(pInfector) || !IsEnabledObject(pVictim))
        return;

      MCommand* pNew = MMatchServer::GetInstance()->CreateCommand(MC_MATCH_INFECT, MUID(0, 0));
      pNew->AddParameter(new MCmdParamUID(pVictim->GetUID()));
      MMatchServer::GetInstance()->RouteToBattle(m_pStage->GetUID(), pNew);

      m_pStage->SwitchPlayerTeam(uidVictim);
      pVictim->SetAlive(true);

      int nRedAliveCount = 0;
      int nBlueAliveCount = 0;

      if (GetAliveCount(&nRedAliveCount, &nBlueAliveCount) == false)
        return;

      if (nBlueAliveCount == 1)
      {
        MMatchStage* pStage = GetStage();

        if (!pStage)
          return;

        MUID uidLastSurvivor;
        for (MUIDRefCache::iterator i = pStage->GetObjBegin(); i != pStage->GetObjEnd(); i++)
        {
          MMatchObject* pObj = (MMatchObject*)(*i).second;
          if ((pObj->GetEnterBattle() == false && !pObj->IsLaunchedGame()) || pObj->CheckPlayerFlags(MTD_PlayerFlags_AdminHide))
            continue;

          if (pObj->GetTeam() == MMT_BLUE && pObj->CheckAlive())
          {
            uidLastSurvivor = pObj->GetUID();
            break;
          }
        }

        if (uidLastSurvivor.IsInvalid())
          return;

        pNew = MMatchServer::GetInstance()->CreateCommand(MC_MATCH_LASTSURVIVOR, MUID(0, 0));
        pNew->AddParameter(new MCmdParamUID(uidLastSurvivor));
        MMatchServer::GetInstance()->RouteToBattle(m_pStage->GetUID(), pNew);
      }
    }

    void MMatchRuleTeamInfected::OnCommand(MCommand* pCommand)
    {
      MMatchRule::OnCommand(pCommand);

      switch (pCommand->GetID())
      {
      case MC_MATCH_REQUEST_INFECT:
      {
        MUID uidInfector, uidVictim;

        pCommand->GetParameter(&uidInfector, 0, MPT_UID);
        uidVictim = pCommand->GetSenderUID();

        OnInfectPlayer(uidInfector, uidVictim);
      }
      break;
      }
    }


    void* MMatchRuleTeamInfected::CreateRuleInfoBlob()
    {
      void* pRuleInfoArray = MMakeBlobArray(sizeof(MTD_RuleInfo_Assassinate), 1);
      MTD_RuleInfo_Assassinate* pRuleItem = (MTD_RuleInfo_Assassinate*)MGetBlobArrayElement(pRuleInfoArray, 0);
      memset(pRuleItem, 0, sizeof(MTD_RuleInfo_Assassinate));

      pRuleItem->nRuleType = MMATCH_GAMETYPE_INFECTED;
      pRuleItem->uidRedCommander = m_uidPatientZero;
      pRuleItem->uidBlueCommander = MUID(0, 0);

      return pRuleInfoArray;
    }

Open(MMatchServer_Stage.cpp) <br>
Find <br>

	else if (nGameType == MMATCH_GAMETYPE_DUEL)
	{
		MMatchRuleDuel* pRuleDuel = (MMatchRuleDuel*)pStage->GetRule();
		if (pVictim->GetUID() == pRuleDuel->uidChallenger)
		{
			fGameExpRatio *= GetDuelVictoryMultiflier(pRuleDuel->GetVictory());
		}
		else
		{
			fGameExpRatio *= GetDuelVictoryMultiflier(pRuleDuel->GetVictory()) * GetDuelPlayersMultiflier(pStage->GetPlayers());

		}
		//		if (pRuleDuel->GetVictory() <= 1)
		//		{
		//			fGameExpRatio = fGameExpRatio * GetDuelPlayersMultiflier(pStage->GetPlayers()) * GetDuelVictoryMultiflier()
		//		}
	}


Add <br>

	else if (nGameType == MMATCH_GAMETYPE_INFECTED)
	{
		MMatchRuleTeamInfected* pRuleInfected = (MMatchRuleTeamInfected*)pStage->GetRule();
		if (pAttacker != pVictim)
		{
			if (pAttacker->GetTeam() != pVictim->GetTeam())
			{
				if (pVictim->GetTeam() == MMT_RED)
					fGameExpRatio *= 3;
				else if (pVictim->GetTeam() == MMT_BLUE)
					fGameExpRatio *= 1.5f;
			}
		}
		else
		{
			fGameExpRatio = 0.0f;
		}
	}

Open(MMatchStage.cpp) <br>
Find <br>

	case MMATCH_GAMETYPE_DUELTOURNAMENT:
		{
			return (new MMatchRuleDuelTournament(this));
		}
		break;

Add <br>

	case MMATCH_GAMETYPE_INFECTED:
	   {
		   return (new MMatchRuleTeamInfected(this));
	   }
	break;

Open(MMatchStage.cpp) <br>
Find <br>

	if (CheckAutoTeamBalancing())
	{
		ShuffleTeamMembers();
	}

Replace <br>

	if (GetStageSetting()->GetGameType() != MMATCH_GAMETYPE_INFECTED && CheckAutoTeamBalancing())
	{
		ShuffleTeamMembers();
	}

Open(ZCharacter.cpp - float ZCharacter::GetMoveSpeedRatio())
Find <br>

    float ZCharacter::GetMoveSpeedRatio()
    {
      float fRatio = 1.f;

      MMatchItemDesc* pMItemDesc = GetSelectItemDesc();

      if (pMItemDesc)
      {
        if (pMItemDesc->m_nLimitSpeed.Ref() <= 100)		//Á¤»ó À¯Àúµé..
          fRatio = pMItemDesc->m_nLimitSpeed.Ref() / 100.f;
        else					//ÇØÄ¿µé...Áë³» °³ ´À·ÁÁú²¬..¤»¤»¤»¤»
          fRatio = 0.1f;
      }

Add <br>

	if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_INFECTED)
	{
		if (m_bInfected)
			fRatio *= (120 / 100.0f);
	}


Find <br>

	if (uStatus.m_bDamaged && (!IsDie()) && (GetHP() < 30.f))

Add above <br>

	//Changed hurt sounds for infected game mode
	if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_INFECTED && uStatus.m_bDamaged && (!IsDie()) && m_bInfected)
	{
		DWORD currTime = timeGetTime();

		if ((m_damageInfo.Ref().m_dwLastDamagedTime + 5000) < currTime)
		{
			int nRandId = rand() % 6 + 1;

			char szSndName[128];
			memset(szSndName, 0, sizeof(szSndName));
			sprintf_s(szSndName, "zombie_pain%d", nRandId);

			ZGetSoundEngine()->PlaySound(szSndName, GetPosition(), IsObserverTarget());

			MEMBER_SET_CHECKCRC(m_damageInfo, m_dwLastDamagedTime, currTime);
		}

		uStatus.m_bDamaged = false;
		return;
	}

Find <br>

	void ZCharacter::InitRound()

Replace <br>

	void ZCharacter::InitRound()
	{
		// ¿Â°ÔÀÓ³ÝÀÇ ¿äÃ»À¸·Î Â¯ ¾ÆÀÌÄÜÀ» ´Þ¾ÆÁØ´Ù. initround½Ã¿¡, ³­ÀÔÇÒ¶§ ´Þ¾ÆÁØ´Ù
		if (GetUserGrade() == MMUG_STAR)
		{
			ZGetEffectManager()->AddStarEffect(this);
		}
		// Custom: Infected
		//if (m_pVMesh)
		//	m_pVMesh->ClearScale();

		m_bInfected = false;

		if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_INFECTED)
		{
			const MTD_CharInfo* pCharInfo = &m_MInitialInfo.Ref();

			for (int i = 0; i < MMCIP_END; i++) {	///< ¾ÆÀÌÅÛ ¼¼ÆÃ

				//m_Items.EquipItem(MMatchCharItemParts(i), pCharInfo->nEquipedItemDesc[i], pCharInfo->nEquipedItemCount[i], pCharInfo->nEquipedItemRarity[i], pCharInfo->nEquipedItemLevel[i]);
				m_Items.EquipItem(MMatchCharItemParts(i), pCharInfo->nEquipedItemDesc[i], pCharInfo->nEquipedItemCount[i]);
			}

			float fAddedAP = DEFAULT_CHAR_AP;			///< AP ÀçÁ¶Á¤
			for (int i = 0; i < MMCIP_END; i++) {
				if (!m_Items.GetItem(MMatchCharItemParts(i))->IsEmpty()) {
					//ÇÙ ¹æ¾î¿ë ÀÓ½ÃÄÚµå
					// Custom: Bypass AP limit of 40 (MAIET trap check)
					//if(m_Items.GetItem(MMatchCharItemParts(i))->GetDesc()->m_nAP.Ref() > 40) {
					//	m_Items.GetItem(MMatchCharItemParts(i))->GetDesc()->m_nAP.Ref() = 0; 
					//}
					fAddedAP += m_Items.GetItem(MMatchCharItemParts(i))->GetDesc()->m_nAP.Ref();
				}
			}

			float fAddedHP = DEFAULT_CHAR_HP;			///< HP ÀçÁ¶Á¤
			for (int i = 0; i < MMCIP_END; i++) {
				if (!m_Items.GetItem(MMatchCharItemParts(i))->IsEmpty()) {
					fAddedHP += m_Items.GetItem(MMatchCharItemParts(i))->GetDesc()->m_nHP.Ref();
				}
			}

			m_Property.fMaxAP.Set_CheckCrc(pCharInfo->nAP + fAddedAP);
			m_Property.fMaxHP.Set_CheckCrc(pCharInfo->nHP + fAddedHP);

			m_fPreMaxHP = pCharInfo->nHP + fAddedHP;
			m_fPreMaxAP = pCharInfo->nAP + fAddedAP;

			ZItem* pMeleeItem = m_Items.GetItem(MMCIP_MELEE);
			if (pMeleeItem != NULL && pMeleeItem->GetDesc() != NULL)
			{
				OnChangeWeapon(pMeleeItem->GetDesc()->m_pMItemName->Ref().m_szMeshName);
				ChangeWeapon(MMCIP_MELEE);
			}

			InitMeshParts();
		}
	}

Open(ZCombatInterface.cpp) <br>
Find <br>

	m_bNetworkAlive = true;		// ÀÎÅÍ³Ý ¿¬°áµÇ¾îÀÖÀ½
	m_dLastTimeTick = 0;
	m_dAbuseHandicapTick = 0;

	m_bSkipUIDrawByRule = false;

Add <br>

	m_pInfectedOverlay = NULL;
	m_pInfectedWidescreenOverlay = NULL;


Find <br>

		else
		{
			pWidget->Show( false);

			MWidget *pPicture = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "TDM_RedWin");
			if ( pPicture)
				pPicture->Show( false);
			pPicture = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "TDM_BlueWin");
			if ( pPicture)
				pPicture->Show( false);
		}

Add <br>

	// Infected
	if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_INFECTED)
	{
		SAFE_DELETE(m_pInfectedOverlay);
		SAFE_DELETE(m_pInfectedWidescreenOverlay);
		m_pInfectedOverlay = new MBitmapR2;
		m_pInfectedWidescreenOverlay = new MBitmapR2;
		m_pInfectedOverlay->Create("zombie_overlay.dds", RGetDevice(), "interface/Default/Combat/zombie_overlay.dds");
		m_pInfectedWidescreenOverlay->Create("zombie_overlay_ws.dds", RGetDevice(), "interface/Default/Combat/zombie_overlay_ws.dds");
	}

Find <br>

	void ZCombatInterface::OnDestroy()
	{
		if(m_nClanIDBlue) {
			ZGetEmblemInterface()->DeleteClanInfo(m_nClanIDBlue);
			m_nClanIDBlue = 0;
		}
		if(m_nClanIDRed) {
			ZGetEmblemInterface()->DeleteClanInfo(m_nClanIDRed);
			m_nClanIDRed = 0;
		}

Add <br>

	// Infected Mode
	if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_INFECTED)
	{
		SAFE_DELETE(m_pInfectedOverlay);
		SAFE_DELETE(m_pInfectedWidescreenOverlay);
	}

Find <br>

	bool bDrawAllPlayerName = false;

Add <br>

	if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_INFECTED &&
		ZGetGame()->m_pMyCharacter->GetTeamID() == MMT_RED)


Find <br>

		if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_BERSERKER)
		{
			if (pCharacter->IsTagger()) pItem->bCommander = true;
		}

Add <br>

		if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_INFECTED && pCharacter->m_dwStatusBitPackingValue.Ref().m_bCommander)
			pItem->bCommander = true;

Find <br>

			if(ZGetGameInterface()->GetCamera()->GetLookMode()==ZCAMERA_DEFAULT)
				m_CrossHair.Draw(pDC);
		}

Add <br>

		if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_INFECTED)
		{
			ZBmNumLabel* pBmNumLabel = NULL;
			MPOINT point;

			pBmNumLabel = (ZBmNumLabel*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("TDM_Score_Max");
			if (pBmNumLabel)
			{
				point = pBmNumLabel->GetPosition();

				if (RGetIsWidthScreen() || RGetIsLongScreen())
				{
					point.x += 28;
					point.y += 50;
				}
				else
				{
					point.x += 14;
					point.y += 50;
				}

				if (g_bShowCTFMsg && GetTickCount() - g_dwCTFMsgShowTime < 5000)
				{
					point = pBmNumLabel->GetPosition();

					if (RGetIsWidthScreen() || RGetIsLongScreen())
					{
						point.x -= 90;
						point.y += 145;
					}
					else
					{
						point.x -= 100;
						point.y += 145;
					}

					pDC->SetFont(MFontManager::Get("FONTa10_O2Wht"));
					pDC->SetColor(MCOLOR(0xFF00FFDC));
					pDC->Text(point, g_szCTFMsg);
				}
			}
		}

Open(ZGame.cpp) <br>
Find <br>


	char szVictim[256];
	strcpy(szVictim, pVictim ? pVictim->GetUserAndClanName() : szAnonymous);

	char szAttacker[256];
	strcpy(szAttacker, pAttacker ? pAttacker->GetUserAndClanName() : szAnonymous);

Add <br>

	if (GetMatch()->GetMatchType() == MMATCH_GAMETYPE_INFECTED)
	{
		char szInfectedMsg[128];
		memset(szInfectedMsg, 0, sizeof(szInfectedMsg));

		if (pVictim == pAttacker && pVictim->GetTeamID() == MMT_BLUE)
			sprintf_s(szInfectedMsg, "Human '%s' has died!", pVictim ? pVictim->GetUserName() : "Unknown");
		else if (pVictim->GetTeamID() == MMT_RED)
		{
			sprintf_s(szInfectedMsg, "Zombie '%s' has been slain!", pVictim ? pVictim->GetUserName() : "Unknown");
			ZGetSoundEngine()->PlaySound("zombie_die");
		}
		else if (pVictim->GetTeamID() == MMT_BLUE)
			sprintf_s(szInfectedMsg, "Human '%s' has been infected!", pVictim ? pVictim->GetUserName() : "Unknown");
		ZGetGameInterface()->GetCombatInterface()->UpdateCTFMsg(szInfectedMsg);
	}


Find <br>

						if (GetMatch()->GetMatchType() == MMATCH_GAMETYPE_ASSASSINATE)
						{
							if ( nTeamWon == MMT_RED)
								ZGetGameInterface()->PlayVoiceSound( VOICE_BLUETEAM_BOSS_DOWN, 2100);
							else
								ZGetGameInterface()->PlayVoiceSound( VOICE_REDTEAM_BOSS_DOWN, 2000);
						}

Replace  <br>

						if (GetMatch()->GetMatchType() == MMATCH_GAMETYPE_ASSASSINATE || GetMatch()->GetMatchType() == MMATCH_GAMETYPE_INFECTED)
						{
							if (nTeamWon == MMT_RED)
								ZGetGameInterface()->PlayVoiceSound(VOICE_BLUETEAM_BOSS_DOWN, 2100);
							else
								ZGetGameInterface()->PlayVoiceSound(VOICE_REDTEAM_BOSS_DOWN, 2000);
						}


Find <br>

	if(ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_DUEL)
	{
		ZRuleDuel* pDuel = (ZRuleDuel*)ZGetGameInterface()->GetGame()->GetMatch()->GetRule();
		nWritten = zfwrite(&pDuel->QInfo,sizeof(MTD_DuelQueueInfo),1,m_pReplayFile);
		if(nWritten==0) goto RECORDING_FAIL;
	}

Add <br>

	else if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_INFECTED)
	{
		ZRuleTeamInfected* pTeamInfected = (ZRuleTeamInfected*)ZGetGameInterface()->GetGame()->GetMatch()->GetRule();
		nWritten = zfwrite(&pTeamInfected->m_uidPatientZero, sizeof(MUID), 1, m_pReplayFile);
		if (nWritten == 0) goto RECORDING_FAIL;
	}


Find <br>

	void ZGame::OnResetTeamMembers(MCommand* pCommand)
	{
		if (!m_Match.IsTeamPlay()) return;

		ZChatOutput( MCOLOR(ZCOLOR_GAME_INFO), ZMsg(MSG_GAME_MAKE_AUTO_BALANCED_TEAM) );


Replace <br>

	void ZGame::OnResetTeamMembers(MCommand* pCommand)
	{
		if (!m_Match.IsTeamPlay()) return;

		if (m_Match.GetMatchType() != MMATCH_GAMETYPE_INFECTED)
			ZChatOutput(MCOLOR(ZCOLOR_GAME_INFO), ZMsg(MSG_GAME_MAKE_AUTO_BALANCED_TEAM));

Open(ZGameClient.cpp) <br>
Find <br>

			sprintf(szTranslated, szErrStr, szArg);
			ZChatOutput(szTranslated, ZChat::CMT_SYSTEM);


Add <br>

			if (ZGetGame() && ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_INFECTED)
			{
				if (idErrMsg == MERR_TIME_10REMAINING || idErrMsg == MERR_TIME_30REMAINING || idErrMsg == MERR_TIME_60REMAINING)
				{
					ZGetSoundEngine()->PlaySound("time_tick_alert");
				}
			}


Find <br>

		ZTransMsg(szText, MSG_JOINED_STAGE, 1, szTmp);
		ZChatOutput(szText, ZChat::CMT_SYSTEM, ZChat::CL_STAGE);


Add <br>

		if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_INFECTED)
		{
			ZPostRequestTakeoffItem(ZGetGameClient()->GetPlayerUID(), MMCIP_AVATAR);
		}


Find <br>

	string name = GetObjName(uidChar);
	char szText[256];
	if (uidChar == GetPlayerUID())
	{
		ZGetGameInterface()->GetChat()->Clear(ZChat::CL_STAGE);

		char szTmp[ 256];
		sprintf(szTmp, "(%03d)%s", nRoomNo, szStageName);

		ZTransMsg( szText, MSG_JOINED_STAGE, 1, szTmp);
		ZChatOutput(szText, ZChat::CMT_SYSTEM, ZChat::CL_STAGE);
	}

Replace <br>

	string name = GetObjName(uidChar);
	char szText[256];
	if (uidChar == GetPlayerUID())
	{
		ZGetGameInterface()->GetChat()->Clear(ZChat::CL_STAGE);

		char szTmp[ 256];
		sprintf(szTmp, "(%03d)%s", nRoomNo, szStageName);

		//Infected game mode avatar check
		if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_INFECTED)
		{
			ZPostRequestTakeoffItem(ZGetGameClient()->GetPlayerUID(), MMCIP_AVATAR);
		}

		ZTransMsg( szText, MSG_JOINED_STAGE, 1, szTmp);
		ZChatOutput(szText, ZChat::CMT_SYSTEM, ZChat::CL_STAGE);
	}


Find <br>

	void ZGameClient::UpdateStageSetting(MSTAGE_SETTING_NODE* pSetting, STAGE_STATE nStageState, const MUID& uidMaster)
	{
		//m_MatchStageSetting.ShiftHeapPos();
		m_MatchStageSetting.UpdateStageSetting(pSetting);
		m_MatchStageSetting.SetMasterUID(uidMaster);
		m_MatchStageSetting.SetStageState(nStageState);

		bool bForceEntry = false;
		if (nStageState != STAGE_STATE_STANDBY)
		{
			bForceEntry = true;
		}
		m_bForcedEntry = bForceEntry;

		ZApplication::GetGameInterface()->SerializeStageInterface();
	}

Replace <br>


	void ZGameClient::UpdateStageSetting(MSTAGE_SETTING_NODE* pSetting, STAGE_STATE nStageState, const MUID& uidMaster)
	{
		//m_MatchStageSetting.ShiftHeapPos();
		m_MatchStageSetting.UpdateStageSetting(pSetting);
		m_MatchStageSetting.SetMasterUID(uidMaster);
		m_MatchStageSetting.SetStageState(nStageState);

		//Infected game mode avatar check
		if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_INFECTED)
		{
			ZPostRequestTakeoffItem(ZGetGameClient()->GetPlayerUID(), MMCIP_AVATAR);
		}

		bool bForceEntry = false;
		if (nStageState != STAGE_STATE_STANDBY)
		{
			bForceEntry = true;
		}
		m_bForcedEntry = bForceEntry;

		ZApplication::GetGameInterface()->SerializeStageInterface();
	}

Open(ZGameInterface.cpp) <br>
Find <br>

	ZGetGameTypeManager()->SetGameTypeStr(MMATCH_GAMETYPE_DUELTOURNAMENT, ZMsg(MSG_MT_DUELTOURNAMENT));

Add <br>

	ZGetGameTypeManager()->SetGameTypeStr( MMATCH_GAMETYPE_INFECTED, "Infected");

Find <br>

	void ZGameInterface::UpdateBlueRedTeam( void)
	{
		MButton* pBlueTeamBtn  = (MButton*)m_IDLResource.FindWidget("StageTeamBlue");
		MButton* pBlueTeamBtn2 = (MButton*)m_IDLResource.FindWidget("StageTeamBlue2");
		MButton* pRedTeamBtn  = (MButton*)m_IDLResource.FindWidget("StageTeamRed");
		MButton* pRedTeamBtn2 = (MButton*)m_IDLResource.FindWidget("StageTeamRed2");
		if ((pRedTeamBtn == NULL) || (pBlueTeamBtn == NULL) || (pRedTeamBtn2 == NULL) || (pBlueTeamBtn2 == NULL))
			return;

Add <br>

	bool bInfectedMode = ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_INFECTED;


Open(ZMatch.cpp) <br>
Find <br>

	void ZMatch::InitCharactersPosition()
	{
	    // ?????? °?¿?
	    if (IsTeamPlay())
	    {
		int nSpawnIndex[ 2] = { 0, 0 };


Replace <br>

	void ZMatch::InitCharactersPosition()
	{
		// ÆÀÀüÀÏ °æ¿ì
	    if (IsTeamPlay() && GetMatchType() != MMATCH_GAMETYPE_INFECTED)
		{
			int nSpawnIndex[2] = { 0, 0 };

Find <br>

	  switch(m_nRoundState) 
	    {

    case MMATCH_ROUNDSTATE_PREPARE: 
        {

        }
        break;
    case MMATCH_ROUNDSTATE_PRE_COUNTDOWN:
        {
        }
        break;
    case MMATCH_ROUNDSTATE_COUNTDOWN : 
        {
            OutputDebugString("MMATCH_ROUNDSTATE_COUNTDOWN>> InitRound BEGIN \n");
            InitRound();
            OutputDebugString("MMATCH_ROUNDSTATE_COUNTDOWN>> InitRound END \n");
        }
        break;
    case MMATCH_ROUNDSTATE_PLAY:
        {
            if (!IsTeamPlay())
            {

            }
        }
        break;

Replace <br>

    switch(m_nRoundState) 
    {

    case MMATCH_ROUNDSTATE_PREPARE: 
        {

        }
        break;
	case MMATCH_ROUNDSTATE_PRE_COUNTDOWN:
	{
		if (GetMatchType() == MMATCH_GAMETYPE_INFECTED)
			InitRound();
	}
	break;
	case MMATCH_ROUNDSTATE_COUNTDOWN:
	{
		OutputDebugString("MMATCH_ROUNDSTATE_COUNTDOWN>> InitRound BEGIN \n");
		if (GetMatchType() != MMATCH_GAMETYPE_INFECTED)
			InitRound();
		OutputDebugString("MMATCH_ROUNDSTATE_COUNTDOWN>> InitRound END \n");
	}
	break;
    case MMATCH_ROUNDSTATE_PLAY:
        {
            if (!IsTeamPlay())
            {

            }
        }
        break;


Open(ZPlayerListBox.cpp) <br>
Find <br>

		const MSTAGE_SETTING_NODE* pStageSetting = ZGetGameClient()->GetMatchStageSetting()->GetStageSetting();

		if ( (nTeam != MMT_SPECTATOR) && (ZGetGameTypeManager()->IsTeamGame(pStageSetting->nGameType) == false))
		{
			nTeam = MMT_ALL;
		}


Replace <br>

		const MSTAGE_SETTING_NODE* pStageSetting = ZGetGameClient()->GetMatchStageSetting()->GetStageSetting();

		//Infected game mode room list
		if ((nTeam != MMT_SPECTATOR) && (ZGetGameTypeManager()->IsTeamGame(pStageSetting->nGameType) == false) ||
			pStageSetting->nGameType == MMATCH_GAMETYPE_INFECTED)
		{
			nTeam = MMT_ALL;
		}

Open(ZReplay.cpp) <br>
Find <br>

	bool ZReplayLoader::LoadStageSettingEtc(ZFile* file)
	{
		// °ÔÀÓ·ê º° Ãß°¡ ¼¼ÆÃ°ª ·Îµå
		if(m_StageSetting.nGameType==MMATCH_GAMETYPE_DUEL)
		{
			ZRuleDuel* pDuel = (ZRuleDuel*)ZGetGameInterface()->GetGame()->GetMatch()->GetRule();
			int nRead = zfread(&pDuel->QInfo,sizeof(MTD_DuelQueueInfo),1,file);
			if(nRead==0) return false;
		}
Add <br>

	if (m_StageSetting.nGameType == MMATCH_GAMETYPE_INFECTED)
	{
		ZRuleTeamInfected* pTeamInfected = (ZRuleTeamInfected*)ZGetGameInterface()->GetGame()->GetMatch()->GetRule();

		MUID uidPatientZero;
		int nRead = zfread(&uidPatientZero, sizeof(MUID), 1, file);
		if (nRead == 0) return false;

		pTeamInfected->m_uidPatientZero = uidPatientZero;
	}

Find <br>

			pChar->SetVisible(true);
	#ifdef _REPLAY_TEST_LOG
			mlog("[Add Character %s(%d)]\n", pChar->GetUserName());
	#endif

		}

Add under <br>

	// lazy way of "fixing"
	if (m_StageSetting.nGameType == MMATCH_GAMETYPE_INFECTED)
	{
		if (ZGetGame()->GetMatch()->GetRoundState() == MMATCH_ROUNDSTATE_PLAY)
		{
			for (ZCharacterManager::iterator itor = ZGetGame()->m_CharacterManager.begin(); itor != ZGetGame()->m_CharacterManager.end(); ++itor)
			{
				ZCharacter* pCharacter = (ZCharacter*)(*itor).second;
				if (pCharacter)
				{
					if (pCharacter->GetInitialized() && !pCharacter->IsAdminHide() && pCharacter->GetTeamID() == MMT_RED && !pCharacter->IsDie())
						pCharacter->InfectCharacter(false);
				}
			}
		}
	}

Open(ZRule.cpp) <br>
Find <br>

	case MMATCH_GAMETYPE_DUELTOURNAMENT:
		{
			return (new ZRuleDuelTournament(pMatch));
		}
		break;

Add <br>

	case MMATCH_GAMETYPE_INFECTED:
	{
		return (new ZRuleTeamInfected(pMatch));
	}
	break;

Open(ZShopEquipInterface.cpp) <br>
Find <br>

	bool ZShopEquipInterface::Equip(MMatchCharItemParts parts, MUID& uidItem)
	{

Replace <br>

	bool ZShopEquipInterface::Equip(MMatchCharItemParts parts, MUID& uidItem)
	{
		ZPostRequestEquipItem(ZGetGameClient()->GetPlayerUID(), uidItem, parts);
		return true;

		//Infected game mode avatar check
		if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_INFECTED)
		{
			if (parts == MMCIP_AVATAR)
				return false;
		}
	}


Find <br>

	case MMATCH_GAMETYPE_DEATHMATCH_SOLO:

Add <br>

	case MMATCH_GAMETYPE_INFECTED:

Find <br>

	else if ( pSetting->nGameType == MMATCH_GAMETYPE_QUEST)						// Äù½ºÆ® ¸ðµåÀÌ¸é...
	{
		// ¸Ê ÀÌ¸§ ¹è°æ ÀÌ¹ÌÁö º¯È¯
		if ( pAniMapImg)
			pAniMapImg->SetCurrentFrame( 2);

		// Äù½ºÆ® UI º¸ÀÓ
		bQuestUI = true;
	}

Add <br>

	else if (pSetting->nGameType == MMATCH_GAMETYPE_INFECTED)					// Infected Mode
	{
		if (pAniMapImg)
			pAniMapImg->SetCurrentFrame(3);

		bQuestUI = false;
	}


Open(ZWorld.cpp) <br>
Find <br>

		FogInfo finfo = GetBsp()->GetFogInfo();
		m_bFog = finfo.bFogEnable;
		m_fFogNear = finfo.fNear;
		m_fFogFar = finfo.fFar;
		m_dwFogColor = finfo.dwFogColor;

Replace <br>

	if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_INFECTED)
	{
		m_bFog = true;
		m_fFogNear = 0;
		m_fFogFar = 5000;
		m_dwFogColor = 0xffff0000;
	}
	else
	{
		FogInfo finfo = GetBsp()->GetFogInfo();
		m_bFog = finfo.bFogEnable;
		m_fFogNear = finfo.fNear;
		m_fFogFar = finfo.fFar;
		m_dwFogColor = finfo.dwFogColor;
	}


Open(MMatchStage.h) <br>
Find <br>

	void OnGameKill(const MUID& uidAttacker, const MUID& uidVictim);
	bool CheckAutoTeamBalancing();	// trueÀÌ¸é ÆÀ¿øÀ» ¼¯¾î¾ß ÇÑ´Ù.
	void ShuffleTeamMembers();

Add <br>

	void SwitchPlayerTeamForInfected(const MUID& uidPlayer);
	void SwitchPlayerTeam(const MUID& uidPlayer);


Open(MMatchStage.cpp) <br>
Find <br>

	void MMatchStage::SetRelayMapList(RelayMap* pRelayMapList)
	{


Add <br>

	void MMatchStage::SwitchPlayerTeam(const MUID& uidPlayer)
	{
		if (m_StageSetting.IsTeamPlay() == false) return;
		if (m_ObjUIDCaches.empty()) return;

		MMatchObject* pPlayer = MMatchServer::GetInstance()->GetObject(uidPlayer);
		if (!IsEnabledObject(pPlayer))
			return;

		vector<MMatchObject*> sortedObjectList;

		for (MUIDRefCache::iterator i = m_ObjUIDCaches.begin(); i != m_ObjUIDCaches.end(); i++)
		{
			MMatchObject* pObj = (MMatchObject*)(*i).second;

			if ((pObj->GetEnterBattle() == true) && (pObj->GetGameInfo()->bJoinedGame == true) && !pObj->CheckPlayerFlags(MTD_PlayerFlags_AdminHide))
			{
				if (pObj->GetUID() == uidPlayer)
					sortedObjectList.push_back(pObj);
			}
		}

		int nCounter = 0;
		for (vector<MMatchObject*>::iterator itor = sortedObjectList.begin(); itor != sortedObjectList.end(); ++itor)
		{
			MMatchObject* pObj = (*itor);
			PlayerTeam(pObj->GetUID(), NegativeTeam(MMatchTeam(pObj->GetTeam())));
			nCounter++;
		}

		if (nCounter <= 0)
			return;

		nCounter = 0;

		MCommand* pCmd = MMatchServer::GetInstance()->CreateCommand(MC_MATCH_RESET_TEAM_MEMBERS, MUID(0, 0));
		int nMemberCount = (int)sortedObjectList.size(); //(int)m_ObjUIDCaches.size();
		void* pTeamMemberDataArray = MMakeBlobArray(sizeof(MTD_ResetTeamMembersData), nMemberCount);

		for (vector<MMatchObject*>::iterator itor = sortedObjectList.begin(); itor != sortedObjectList.end(); ++itor)
		{
			MMatchObject* pObj = (*itor);
			MTD_ResetTeamMembersData* pNode = (MTD_ResetTeamMembersData*)MGetBlobArrayElement(pTeamMemberDataArray, nCounter++);
			pNode->m_uidPlayer = pObj->GetUID();
			pNode->nTeam = (char)pObj->GetTeam();
		}

		pCmd->AddParameter(new MCommandParameterBlob(pTeamMemberDataArray, MGetBlobArraySize(pTeamMemberDataArray)));
		MEraseBlobArray(pTeamMemberDataArray);
		MMatchServer::GetInstance()->RouteToBattle(GetUID(), pCmd);
	}


	void MMatchStage::SwitchPlayerTeamForInfected(const MUID& uidPlayer)
	{
		if (m_StageSetting.IsTeamPlay() == false) return;
		if (m_ObjUIDCaches.empty()) return;

		MMatchObject* pPlayer = MMatchServer::GetInstance()->GetObject(uidPlayer);
		if (!IsEnabledObject(pPlayer))
			return;

		if (pPlayer->GetEnterBattle() == false || pPlayer->GetGameInfo()->bJoinedGame == false || pPlayer->CheckPlayerFlags(MTD_PlayerFlags_AdminHide))
			return;

		vector<MMatchObject*> sortedObjectList;

		for (MUIDRefCache::iterator i = m_ObjUIDCaches.begin(); i != m_ObjUIDCaches.end(); i++)
		{
			MMatchObject* pObj = (MMatchObject*)(*i).second;

			if ((pObj->GetEnterBattle() == true) && (pObj->GetGameInfo()->bJoinedGame == true) && !pObj->CheckPlayerFlags(MTD_PlayerFlags_AdminHide))
			{
				//if (pObj->GetUID() == uidPlayer || (pObj->GetUID() != pPlayer->GetUID() && pObj->GetTeam() == pPlayer->GetTeam()))
				if ((pObj->GetTeam() == MMT_RED && pObj->GetUID() != pPlayer->GetUID()) || pObj->GetUID() == uidPlayer)
					sortedObjectList.push_back(pObj);
			}
		}

		int nCounter = 0;
		for (vector<MMatchObject*>::iterator itor = sortedObjectList.begin(); itor != sortedObjectList.end(); ++itor)
		{
			MMatchObject* pObj = (*itor);

			if (pObj->GetUID() == pPlayer->GetUID())
				PlayerTeam(pObj->GetUID(), MMT_RED);
			else
				PlayerTeam(pObj->GetUID(), MMT_BLUE);

			nCounter++;
		}

		if (nCounter <= 0)
			return;

		nCounter = 0;

		MCommand* pCmd = MMatchServer::GetInstance()->CreateCommand(MC_MATCH_RESET_TEAM_MEMBERS, MUID(0, 0));
		int nMemberCount = (int)sortedObjectList.size();
		void* pTeamMemberDataArray = MMakeBlobArray(sizeof(MTD_ResetTeamMembersData), nMemberCount);

		for (vector<MMatchObject*>::iterator itor = sortedObjectList.begin(); itor != sortedObjectList.end(); ++itor)
		{
			MMatchObject* pObj = (*itor);
			MTD_ResetTeamMembersData* pNode = (MTD_ResetTeamMembersData*)MGetBlobArrayElement(pTeamMemberDataArray, nCounter++);
			pNode->m_uidPlayer = pObj->GetUID();
			pNode->nTeam = (char)pObj->GetTeam();
		}

		pCmd->AddParameter(new MCommandParameterBlob(pTeamMemberDataArray, MGetBlobArraySize(pTeamMemberDataArray)));
		MEraseBlobArray(pTeamMemberDataArray);
		MMatchServer::GetInstance()->RouteToBattle(GetUID(), pCmd);
	}

Open(MSharedCommandTable.h) <br>
Find <br>

	#define MC_MATCH_FLAG_EFFECT					50010


Add <br>

	//Infected Mode
	#define MC_MATCH_REQUEST_INFECT		60032
	#define MC_MATCH_INFECT			60033
	#define MC_MATCH_LASTSURVIVOR		60034

Open(MSharedCommandTable.cpp) <br>
Find <br>

	C(MC_MATCH_DUELTOURNAMENT_GAME_NEXT_MATCH_PLYAERINFO, "Match.DuelTournament.Game Next Match Player Info", "Duel Tournament Game Next Match Player Info", MCDT_MACHINE2MACHINE)
		P(MPT_BLOB, "NextMatchPlayerInfo");

Add <br>

        	//Infected Mode
		C(MC_MATCH_REQUEST_INFECT, "Match.Infected.RequestInfect", "Request Infected", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidInfector")

		C(MC_MATCH_INFECT, "Match.Infected.Infect", "Infect", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")

		C(MC_MATCH_LASTSURVIVOR, "Match.Infected.LastSurvivor", "Last Survivor Notify", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")


Open(ZCommandUDPHackShield.cpp) <br>
Find <br>

	AddDeniedCommand(MC_MATCH_FLAG_EFFECT);
	AddDeniedCommand(MC_MATCH_FLAG_CAP);
	AddDeniedCommand(MC_MATCH_FLAG_STATE);

Add <br>

	//Infected
	AddDeniedCommand(MC_MATCH_REQUEST_INFECT);
	AddDeniedCommand(MC_MATCH_INFECT);
	AddDeniedCommand(MC_MATCH_LASTSURVIVOR);

Open(ZGame.cpp) <br>
Find <br>

	bool ZGame::OnRuleCommand(MCommand* pCommand)
	{
	#ifdef _QUEST
		if (ZGetQuest()->OnGameCommand(pCommand)) return true;
	#endif

		switch (pCommand->GetID())
		{

Add <br>

	case MC_MATCH_INFECT:
	case MC_MATCH_LASTSURVIVOR:



Open(ZCharacter.h) <br>
Find <br>

	float	m_fGlobalHP;			// ´Ù¸¥»ç¶÷µéÀÌ º¼¶§ ÀÌÄ³¸¯ÅÍÀÇ HPÀÇ Æò±Õ.. ÅõÇ¥¸¦ À§ÇÔ.
	int		m_nReceiveHPCount;		// Æò±Õ³»±âÀ§ÇÑ...

Add under <br>

	//Infected
	bool	m_bInfected;


Open(ZCharacter.cpp) <br>
Find <br>

	ZCharaterStatusBitPacking uState;
	uState.dwFlagsPublic = 1;

Add <br>

	m_bInfected = false;


Find <br>

	void ZCharacter::OnKnockback(rvector& dir, float fForce)
	{
		// ³²ÀÇ Ä³¸¯ÅÍ´Â ³Ë¹éÀ» ¾ø¾Ø´Ù
		if(IsHero())
			ZCharacterObject::OnKnockback(dir,fForce);
	}

Replace <br>

	void ZCharacter::OnKnockback(rvector& dir, float fForce)
	{
		// ³²ÀÇ Ä³¸¯ÅÍ´Â ³Ë¹éÀ» ¾ø¾Ø´Ù
		if (IsHero())
		{
			// Custom: Infected game mode
			float fForceMod = fForce;

			if (m_bInfected)
				fForceMod *= 15.f;

			ZCharacterObject::OnKnockback(dir, fForceMod);
		}
	}

Find <br>

	void ZCharacter::TestToggleCharacter()

Add <br>


	//Infected Mode
	void ZCharacter::InfectCharacter(bool bFirst)
	{
	#define ZOMBIE_MELEE_ITEMID			6000000
	#define ZOMBIE_AVATAR_M_ITEMID		6000001
	#define ZOMBIE_AVATAR_F_ITEMID		6000002
	#define ZOMBIE_HP					500.f
	#define ZOMBIE_MINOR_HP				250.f
	#define ZOMBIE_AP					0.f

		if (m_bInfected)
			return;

		/*if (!m_pVMesh->GetMesh())
		return;*/
		if (!m_pVMesh->m_pMesh)
			return;

		m_bInfected = true;

		// lol scales dont work
		//m_pVMesh->SetScale(D3DXVECTOR3(m_pVMesh->GetScale().x*1.5f, m_pVMesh->GetScale().y*1.5f, m_pVMesh->GetScale().z*1.5f));

		unsigned long nEquipedItemDesc[MMCIP_END], nEquipedItemCount[MMCIP_END];
		memset(nEquipedItemDesc, 0, sizeof(nEquipedItemDesc));
		memset(nEquipedItemCount, 0, sizeof(nEquipedItemCount));

		nEquipedItemDesc[MMCIP_AVATAR] = (m_Property.nSex == MMS_MALE) ? ZOMBIE_AVATAR_M_ITEMID : ZOMBIE_AVATAR_F_ITEMID;
		nEquipedItemDesc[MMCIP_MELEE] = ZOMBIE_MELEE_ITEMID;

		nEquipedItemCount[MMCIP_AVATAR] = 1;
		nEquipedItemCount[MMCIP_MELEE] = 1;

		ZChangeCharParts(m_pVMesh, m_Property.nSex, m_Property.nHair, m_Property.nFace, nEquipedItemDesc);

		for (int i = 0; i < MMCIP_END; i++)
		{
			m_Items.EquipItem(MMatchCharItemParts(i), nEquipedItemDesc[i], nEquipedItemCount[i]);
		}

		// change the weapon
		ChangeWeapon(MMCIP_MELEE);

		MMatchItemDesc* pSelectedItemDesc = m_Items.GetSelectedWeapon()->GetDesc();

		if (pSelectedItemDesc == NULL)
		{
			m_Items.SelectWeapon(MMCIP_MELEE);
		}
		else
			OnChangeWeapon(pSelectedItemDesc->m_pMItemName->Ref().m_szMeshName);

		SetMaxHP(bFirst ? ZOMBIE_HP : ZOMBIE_MINOR_HP);
		SetHP(bFirst ? ZOMBIE_HP : ZOMBIE_MINOR_HP);
		m_Property.fMaxHP.Set(bFirst ? ZOMBIE_HP : ZOMBIE_MINOR_HP);
		m_Property.fMaxHP.MakeCrc();
		SetMaxAP(ZOMBIE_AP);
		SetAP(ZOMBIE_AP);
		m_Property.fMaxAP.Set(ZOMBIE_AP);
		m_Property.fMaxAP.MakeCrc();
	}

Open(ZCharacter.cpp) <br>
Find <br>

	void TestChangePartsAll();
	void TestToggleCharacter();

Add <br>

	void InfectCharacter(bool bFirst);

Open(ZRuleDeathMatch.cpp) <br>
Find <br>

	ZRuleSoloDeathMatch::ZRuleSoloDeathMatch(ZMatch* pMatch) : ZRule(pMatch)
	{

	}

Add <br>

	//Infected Mode
	ZRuleTeamInfected::ZRuleTeamInfected(ZMatch* pMatch) : ZRule(pMatch)
	{
		m_bLastFive = false;
	}

	ZRuleTeamInfected::~ZRuleTeamInfected()
	{

	}

	bool ZRuleTeamInfected::OnCommand(MCommand* pCommand)
	{
		if (!ZGetGame()) return false;

		switch (pCommand->GetID())
		{
		case MC_MATCH_ASSIGN_COMMANDER:
		{
			MUID uidPlayer;

			pCommand->GetParameter(&uidPlayer, 0, MPT_UID);
			//pCommand->GetParameter(&uidBlueCommander,	1, MPT_UID);

			OnInfected(uidPlayer, true);
		}
		break;

		case MC_MATCH_INFECT:
		{
			MUID uidPlayer;

			pCommand->GetParameter(&uidPlayer, 0, MPT_UID);

			OnInfected(uidPlayer, false);
		}
		break;

		case MC_MATCH_LASTSURVIVOR:
		{
			MUID uidPlayer;
			pCommand->GetParameter(&uidPlayer, 0, MPT_UID);

			if (uidPlayer.IsInvalid())
				break;

			ZCharacter* pChar = (ZCharacter*)ZGetGame()->m_CharacterManager.Find(uidPlayer);
			if (pChar)
			{
				char szInfectedMsg[128];
				memset(szInfectedMsg, 0, sizeof(szInfectedMsg));

				if (pChar == ZGetGame()->m_pMyCharacter && !ZGetGameInterface()->GetCombatInterface()->GetObserverMode())
				{
					sprintf_s(szInfectedMsg, "You are the last survivor.");
					ZGetGameInterface()->GetCombatInterface()->UpdateCTFMsg(szInfectedMsg);
				}
				else
				{
					sprintf_s(szInfectedMsg, "'%s' is the last survivor.", pChar->GetUserName());
					ZGetGameInterface()->GetCombatInterface()->UpdateCTFMsg(szInfectedMsg);
				}
			}

			ZGetSoundEngine()->PlaySound("last_survivor");
		}
		break;
		}

		return false;
	}

	void ZRuleTeamInfected::OnInfected(const MUID& uidPlayer, bool bFirst)
	{
		if (!ZGetGame()) return;

		if (uidPlayer.IsInvalid()) return;

		char szTest[128];
		memset(szTest, 0, sizeof(szTest));

		//sprintf_s (szTest, "player [%u-%u] - infect call start", uidPlayer.High, uidPlayer.Low);
		//ZChatOutput(szTest, ZChat::CMT_SYSTEM);

		if (bFirst)
		{
			for (ZCharacterManager::iterator itor = ZGetGame()->m_CharacterManager.begin(); itor != ZGetGame()->m_CharacterManager.end(); ++itor)
			{
				ZGetEffectManager()->Clear();
				ZCharacter* pCharacter = (ZCharacter*)(*itor).second;
				pCharacter->m_dwStatusBitPackingValue.Ref().m_bCommander = false;
			}
		}

		ZCharacter* pChar = (ZCharacter*)ZGetGame()->m_CharacterManager.Find(uidPlayer);

		if (pChar)
		{
			if (pChar->m_bInfected)
			{
				//sprintf_s (szTest, "player [%u-%u] - infect FAIL (done)", uidPlayer.High, uidPlayer.Low);
				//ZChatOutput(szTest, ZChat::CMT_SYSTEM);
				return;
			}

			if (!pChar->GetInitialized() || pChar->IsAdminHide())
				return;

			//sprintf_s (szTest, "player [%u-%u] - infect OK", uidPlayer.High, uidPlayer.Low);
			//ZChatOutput(szTest, ZChat::CMT_SYSTEM);

			pChar->SetVisible(true);
			pChar->Revival();
			pChar->InfectCharacter(bFirst);
			pChar->OnScream();

			// because revival() resets the commander flag
			if (bFirst)
			{
				ZGetEffectManager()->AddCommanderIcon(pChar, 0);
				pChar->m_dwStatusBitPackingValue.Ref().m_bCommander = true;
				m_uidPatientZero = pChar->GetUID();
			}
			else
			{
				ZGetSoundEngine()->PlaySound("scored");
				ZCharacter* pMaster = (ZCharacter*)ZGetGame()->m_CharacterManager.Find(m_uidPatientZero);

				if (pMaster && pMaster == ZGetGame()->m_pMyCharacter)
				{
					pMaster->SetHP(500.f); // ZOMBIE_HP
				}
			}

			int nRandId = rand() % 14 + 1;

			char szSndName[128];
			memset(szSndName, 0, sizeof(szSndName));
			sprintf_s(szSndName, "zombie_voice_idle%d", nRandId);

			ZGetSoundEngine()->PlaySound(szSndName/*, pChar->GetPosition(), pChar->IsObserverTarget()*/);

			if ((!ZGetGameInterface()->GetCombatInterface()->GetObserverMode() && pChar == ZGetGame()->m_pMyCharacter) || (ZGetGameInterface()->GetCombatInterface()->GetObserverMode() && pChar == ZGetGameInterface()->GetCombatInterface()->GetObserver()->GetTargetCharacter()))
			{
				// don't release
				if (pChar == ZGetGame()->m_pMyCharacter)
					ZGetGame()->ReleaseObserver();

				ZGetCamera()->Shock(2000.0f, .7f, rvector(0.0f, 0.0f, -1.0f)); // Vibrate camera

				char szInfectedMsg[128];
				memset(szInfectedMsg, 0, sizeof(szInfectedMsg));

				sprintf_s(szInfectedMsg, "YOU are Infected. KILL THEM ALL!");

				ZGetGameInterface()->GetCombatInterface()->UpdateCTFMsg(szInfectedMsg);
				ZGetSoundEngine()->PlaySound("you_infected");
			}
		}
	}

	void ZRuleTeamInfected::OnSetRoundState(MMATCH_ROUNDSTATE roundState)
	{
		switch (roundState)
		{
		case MMATCH_ROUNDSTATE_PRE_COUNTDOWN:
		{
			ZGetGameInterface()->GetCombatInterface()->UpdateCTFMsg("Zombies will spawn soon. HIDE!");
			m_bLastFive = false;
			m_uidPatientZero = MUID(0, 0);
			//ZChatOutput("HIDE NOW", ZChat::CMT_SYSTEM);
			ZGetSoundEngine()->PlaySound("wait_zombie_player");
		}
		break;
		case MMATCH_ROUNDSTATE_COUNTDOWN:
		{
			//ZChatOutput("", ZChat::CMT_SYSTEM);
		}
		break;
		case MMATCH_ROUNDSTATE_PLAY:
		{
			if (ZGetGame()->IsReplay() && m_uidPatientZero.IsValid() && ZGetGame()->m_pMyCharacter->GetUID() == m_uidPatientZero && !ZGetGame()->m_pMyCharacter->m_bInfected)
				ZGetGame()->m_pMyCharacter->InfectCharacter(true);

			if (ZGetGame()->IsReplay() && m_uidPatientZero.IsValid() && ZGetGame()->m_pMyCharacter->GetTeamID() == MMT_RED && !ZGetGame()->m_pMyCharacter->m_bInfected)
				ZGetGame()->m_pMyCharacter->InfectCharacter(false);

			ZGetGameInterface()->GetCombatInterface()->UpdateCTFMsg("RUN!");
			ZChatOutput("RUN! The zombies come for you, remember to work as a team.", ZChat::CMT_SYSTEM);
			ZGetSoundEngine()->PlaySound("run_for_you_life");
		}
		break;

		case MMATCH_ROUNDSTATE_FREE:
		{
			ZGetGameInterface()->GetCombatInterface()->UpdateCTFMsg("4 or more players are required to start the game.");
			m_bLastFive = false;
			m_uidPatientZero = MUID(0, 0);
			//ZChatOutput("RS -> (Free)", ZChat::CMT_SYSTEM);
			ZGetSoundEngine()->PlaySound("player_4");
		}
		break;
		}
	}

	void ZRuleTeamInfected::OnResponseRuleInfo(MTD_RuleInfo* pInfo)
	{
		MTD_RuleInfo_Assassinate* pAssassinateRule = (MTD_RuleInfo_Assassinate*)pInfo;
		OnInfected(pAssassinateRule->uidRedCommander, true);
	}

	void ZRuleTeamInfected::OnUpdate(float fDelta)
	{
		if (ZGetGame()->GetMatch()->GetRoundState() == MMATCH_ROUNDSTATE_PLAY)
		{
			DWORD dwTime = ZGetGame()->GetMatch()->GetRemaindTime();
			DWORD dwLimitTime = ZGetGameClient()->GetMatchStageSetting()->GetStageSetting()->nLimitTime;
			if (dwLimitTime != 99999)
			{
				dwLimitTime *= 60000;
				if (dwTime <= dwLimitTime)
				{
					dwTime = (dwLimitTime - dwTime) / 1000;

					if ((dwTime / 60) == 0 && (dwTime % 60) == 5 && !m_bLastFive)
					{
						m_bLastFive = true;
						ZGetSoundEngine()->PlaySound("time_tick_last5");
					}
				}
			}
		}
	   }

Open(ZRuleDeathMatch.h) <br>
Find <br>

	class ZRuleSoloDeathMatch : public ZRule
	{
	public:
		ZRuleSoloDeathMatch(ZMatch* pMatch);
		virtual ~ZRuleSoloDeathMatch();
	};

Add <br>

	class ZRuleTeamInfected : public ZRule
	{
	public:
		ZRuleTeamInfected(ZMatch* pMatch);
		virtual ~ZRuleTeamInfected();

		virtual bool OnCommand(MCommand* pCommand);
		virtual void OnSetRoundState(MMATCH_ROUNDSTATE roundState);
		virtual void OnResponseRuleInfo(MTD_RuleInfo* pInfo);

		MUID m_uidPatientZero;

	private:
		virtual void OnUpdate(float fDelta);
		void OnInfected(const MUID& uidPlayer, bool bFirst);
		bool m_bLastFive;
	};


Open(ZCombatInterface.cpp) <br>
Find <br>

	void ZCombatInterface::DrawAfterWidgets(MDrawContext* pDC)
	{
		// µà¾óÅä³Ê¸ÕÆ® °á°úÃ¢¿ë ´ëÁøÇ¥¸¦ ±×¸°´Ù.
		if (m_bShowResult)
			if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_DUELTOURNAMENT)
				((ZRuleDuelTournament*)ZGetGame()->GetMatch()->GetRule())->ShowMatchOrder(pDC, true, m_fElapsed);
	}

add <br>

	void ZCombatInterface::UpdateCTFMsg(const char* szMsg)
	{
		g_bShowCTFMsg = true;
		g_dwCTFMsgShowTime = GetTickCount();
		strcpy_s(g_szCTFMsg, szMsg);
	}

Open(ZCombatInterface.h) <br>
Find <br>

	void OnAddCharacter(ZCharacter *pChar);

Add <br>

	void UpdateCTFMsg(const char* szMsg);


Open(ZCombatInterface.cpp) <br>
Find <br>

	#define TEXT_COLOR_TITLE			0xFFAAAAAA
	#define TEXT_COLOR_DEATH_MATCH		0xfffff696
	#define TEXT_COLOR_DEATH_MATCH_DEAD	0xff807b4b
	#define TEXT_COLOR_BLUE_TEAM		0xff8080ff
	#define TEXT_COLOR_BLUE_TEAM_DEAD	0xff606080
	#define TEXT_COLOR_RED_TEAM			0xffff8080
	#define TEXT_COLOR_RED_TEAM_DEAD	0xff806060
	#define TEXT_COLOR_SPECTATOR		0xff808080
	#define TEXT_COLOR_CLAN_NAME		0xffffffff

Add <br>

	// Custom: CTF
	bool g_bShowCTFMsg = false;
	DWORD g_dwCTFMsgShowTime = 0;
	static char g_szCTFMsg[128] = { 0, };



![1](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/gamemode%3A%20infected/1.jpg)
![2](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/gamemode%3A%20infected/2.jpg)


Credits To FreeStyleGunz
