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







































































Credits To FreeStyleGunz
