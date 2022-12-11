Open(MBaseGameType.h) <br>
Find <br>

    enum MMATCH_GAMETYPE {

Add under <br>

	MMATCH_GAMETYPE_VAMPIRE				=15,


Open(MBaseGameType.cpp) <br>
Find <br>

    _InitGameType(MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR,  1.0f,			1.0f,					0.0f);

Add under <br>

    _InitGameType(MMATCH_GAMETYPE_VAMPIRE,			MMATCH_GAMETYPE_VAMPIRE,			MMATCH_GAMETYPE_VAMP_STR,			  1.0f,			1.0f,					0.0f);


Open(MMatchStage.cpp) <br>
Find <br>

	case MMATCH_GAMETYPE_QUEST:
		{
			return (new MMatchRuleQuest(this));
		}
		break;

Add under <br>

	case MMATCH_GAMETYPE_VAMPIRE:
		{
			return (new MMatchRuleVampire(this));
		}
		break;


Open(ZCharacter.cpp) <br>
Find <br>

	rvector dir = GetPosition() - srcPos;
	Normalize(dir);

Add under <br>

	if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_VAMPIRE)
	{
		if (pAttacker != NULL && pAttacker->GetUID() != ZGetMyUID() && this->GetUID() == ZGetMyUID())
			ZPostVampire(pAttacker->GetUID(), fDamage);
	}


Open(ZGame.cpp) <br>
Find <br>

    void ZGame::OnDamage(MUID& uid,MUID& tuid,int damage)

Add under <br>

    void ZGame::OnVampire(const MUID& uidVictim, const MUID& uidAttacker, float fDamage)
    {
      ZCharacter* pAttacker = (ZCharacter*)m_CharacterManager.Find(uidAttacker);
      ZCharacter* pVictim = (ZCharacter*)m_CharacterManager.Find(uidVictim);

      if (!pAttacker || !pVictim)
        return;

      if (!pAttacker->GetInitialized() || !pVictim->GetInitialized() || !pAttacker->IsVisible() || !pVictim->IsVisible())
        return;

      if (IsReplay())
      {
        int nAddHP = (int)(fDamage * 0.33f);
        int nCurrHP = pAttacker->GetHP();
        int nMaxHP = pAttacker->GetMaxHP();

        if (nCurrHP + nAddHP > nMaxHP)
        {
          pAttacker->SetHP(nMaxHP);

          int nAddAP = (nCurrHP + nAddHP) - nMaxHP;
          int nCurrAP = pAttacker->GetAP();
          int nMaxAP = pAttacker->GetMaxAP();

          if (nCurrAP + nAddAP > nMaxAP)
            pAttacker->SetAP(nMaxAP);
          else
            pAttacker->SetAP(nCurrAP + nAddAP);
        }
        else
          pAttacker->SetHP(nCurrHP + nAddHP);

        return;
      }

      if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_VAMPIRE)
      {
        if (uidAttacker == ZGetMyUID() && uidVictim != ZGetMyUID())
        {
          MMatchPeerInfo* pVictimPeer = ZGetGameClient()->FindPeer(uidVictim);

          if (!pVictimPeer)
            return;

          if (!pVictimPeer->IsOpened())
            return;

          int nAddHP = (int)(fDamage * 0.33f);
          int nCurrHP = m_pMyCharacter->GetHP();
          int nMaxHP = m_pMyCharacter->GetMaxHP();

          if (nCurrHP + nAddHP > nMaxHP)
          {
            m_pMyCharacter->SetHP(nMaxHP);

            int nAddAP = (nCurrHP + nAddHP) - nMaxHP;
            int nCurrAP = m_pMyCharacter->GetAP();
            int nMaxAP = m_pMyCharacter->GetMaxAP();

            if (nCurrAP + nAddAP > nMaxAP)
              m_pMyCharacter->SetAP(nMaxAP);
            else
              m_pMyCharacter->SetAP(nCurrAP + nAddAP);
          }
          else
            m_pMyCharacter->SetHP(nCurrHP + nAddHP);
        }
      }
    }

Open(ZGameInterface.cpp) <br>
Find <br>

    ZGetGameTypeManager()->SetGameTypeStr(MMATCH_GAMETYPE_QUEST, ZMsg(MSG_MT_QUEST));

Add under <br>

	ZGetGameTypeManager()->SetGameTypeStr(MMATCH_GAMETYPE_VAMPIRE, "Vampire");

Open(ZMatch.cpp) <br>
Find <br>

    void ZMatch::Update(float fDelta)

Replace <br>

    float fElapsedVampire = 0.0f;
    void ZMatch::Update(float fDelta)

Find <br>

    case MMATCH_ROUNDSTATE_PLAY:
        {
            ProcessRespawn();
        }
        break;
    }


Replace <br>

        case MMATCH_ROUNDSTATE_PLAY:
            {
                ProcessRespawn();
            }
            break;
        }

      if (m_pRule)
      {
        m_pRule->Update(fDelta);

        if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_VAMPIRE)
        {
          if (!ZGetGameInterface()->GetCombatInterface()->GetObserverMode() && !ZGetGame()->IsReplay())
          {
            fElapsedVampire += fDelta;

            if (1.0f < fElapsedVampire)
            {
              fElapsedVampire = 0.0f;

              ZCharacter* pMyChar = ZGetGame()->m_pMyCharacter;

              if (!pMyChar->IsVisible() || pMyChar->IsDie())
                return;

              if (pMyChar->GetAP() > 0)
              {
                float fAP = max(0.0f, pMyChar->GetAP() - 3);
                pMyChar->SetAP(fAP);
              }
              else
              {
                float fHP = max(1.0f, pMyChar->GetHP() - 3);
                pMyChar->SetHP(fHP);
              }
            }
          }
        }
      }
    }

Open(ZRule.cpp)
Find <br>


	case MMATCH_GAMETYPE_DUEL:
		{
			return (new ZRuleDuel(pMatch));
		}
		break;



Add under <br>


	case MMATCH_GAMETYPE_VAMPIRE:
	{
		return (new ZRuleVampire(pMatch));
	}
	break;

Open(ZStageInterface.cpp) <br>
Find <br>

    MAnimation* pAniMapImg = (MAnimation*)pResource->FindWidget( "Stage_MapNameBG");

Add under <br>

    (pSetting->nGameType == MMATCH_GAMETYPE_VAMPIRE) ||

Open(ZPost.h) <br>
Find <br>

    inline void ZPostRequestUseSpendableBuffItem(const MUID& uid)
    {
      ZPOSTCMD1(MC_MATCH_REQUEST_USE_SPENDABLE_BUFF_ITEM, MCmdParamUID(uid));
    }

Add under <br>

    inline void ZPostVampire(const MUID& uidAttacker, float fDamage)
    {
      ZPOSTCMD2(MC_PEER_VAMPIRE, MCommandParameterUID(uidAttacker), MCommandParameterFloat(fDamage));
    }


Open(ZGame.h) <br>
Find <br>

    void OnDamage(MUID& uid,MUID& tuid,int damage);

Add under <br>

	void OnVampire(const MUID& uidVictim, const MUID& uidAttacker, float fDamage);

Open(MBaseGameType.cpp) <br>
Find <br>

    #define MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR		"Death Match(Solo)"

Add under <br>

    #define MMATCH_GAMETYPE_VAMP_STR				"Vampire"


Open(MMatchRuleDeathMatch.h) <br>
Find <br>

    class MMatchRuleSoloDeath : public MMatchRule {
    protected:
      bool CheckKillCount(MMatchObject* pOutObject);
      virtual void OnBegin();
      virtual void OnEnd();
      virtual void OnRoundTimeOut();
      virtual bool OnCheckRoundFinish();
      virtual bool RoundCount();
    public:
      MMatchRuleSoloDeath(MMatchStage* pStage);
      virtual ~MMatchRuleSoloDeath() { }
      virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_DEATHMATCH_SOLO; }
    };

Add under <br>

    ///////////////////////////////////////////////////////////////////////////////////////////////
    class MMatchRuleVampire : public MMatchRuleSoloDeath {
    public:
      MMatchRuleVampire(MMatchStage* pStage);
      virtual ~MMatchRuleVampire() { }
      virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_VAMPIRE; }
    };

Open(MSharedCommandTable.h) <br>
Find <br>

    #define MC_LOCAL_UPDATE_ACCEPT_INVALID_IP

Add under <br>

    #define MC_PEER_VAMPIRE							50073

Open(MSharedCommandTable.cpp) <br>
Find <br>

		C(MC_PEER_RELOAD, "Peer.Reload", "Reload", MCDT_PEER2PEER);

Add under <br>

		//Packets (p2p)
		C(MC_PEER_VAMPIRE, "Peer.Vampire", "Vampire", MCDT_PEER2PEER)
		P(MPT_UID, "AttackerUID")
		P(MPT_FLOAT, "damage")

Open(ZGameClient.cpp) <br>
Find <br>

    cmdId == MC_PEER_SHOT ||

Add under <br>

    cmdId == MC_PEER_VAMPIRE ||

Open(ZRuleDeathMatch.h) <br>
Find <br>

    class ZRuleTeamDeathMatch : public ZRule
    {
    public:
      ZRuleTeamDeathMatch(ZMatch* pMatch);
      virtual ~ZRuleTeamDeathMatch();
    };

Add under <br>

    class ZRuleVampire : public ZRuleSoloDeathMatch
    {
    public:
      ZRuleVampire(ZMatch* pMatch);
      virtual ~ZRuleVampire();
    };

Open(ZRuleDeathMatch.cpp) <br>
Find <br>

	ZRuleSoloDeathMatch::ZRuleSoloDeathMatch(ZMatch* pMatch) : ZRule(pMatch)
	{
	}

	ZRuleSoloDeathMatch::~ZRuleSoloDeathMatch()
	{
	}

Add under <br>

	/////////////////////////////////////////////////////////////////////////////////////////
	ZRuleVampire::ZRuleVampire(ZMatch* pMatch) : ZRuleSoloDeathMatch(pMatch)
	{
	}

	ZRuleVampire::~ZRuleVampire()
	{
	}

Open(MMatchRuleDeathMatch.cpp) <br>
Find <br>

	void MMatchRuleSoloDeath::OnRoundTimeOut()
	{
		SetRoundArg(MMATCH_ROUNDRESULT_DRAW);
	}

Add under <br>

	MMatchRuleVampire::MMatchRuleVampire(MMatchStage* pStage) : MMatchRuleSoloDeath(pStage)
	{
	}


System/ChannelRule.xml <br>
FInd <br>

	<CHANNELRULE id="0" name="novice">

Add <br>

	<GAMETYPE id="15" />

System/Gametypecfg.xml <br>
Find <br>

	<!-- GAMETYPE_DEATHMATCH_SOLO -->

Add <br>

	<GAMETYPE id="15">	<!-- GAMETYPE_VAMPIRE -->
		<ROUNDS    round="10"	str="10" />
		<ROUNDS    round="20"	str="20" />
		<ROUNDS    round="30"	str="30" />
		<ROUNDS    round="50"	str="50" default="true" />
		<ROUNDS    round="70"	str="70" />
		<ROUNDS    round="100"	str="100" />
		<LIMITTIME sec="99999"	str="STR:GAMETYPECFG_LIMITTIME_INFINITE" />
		<LIMITTIME sec="10"	str="STR:GAMETYPECFG_LIMITTIME_10MIN" />
		<LIMITTIME sec="20"	str="STR:GAMETYPECFG_LIMITTIME_20MIN" />
		<LIMITTIME sec="30"	str="STR:GAMETYPECFG_LIMITTIME_30MIN" default="true" />
		<LIMITTIME sec="40"	str="STR:GAMETYPECFG_LIMITTIME_40MIN" />
		<LIMITTIME sec="50"	str="STR:GAMETYPECFG_LIMITTIME_50MIN" />
		<LIMITTIME sec="60"	str="STR:GAMETYPECFG_LIMITTIME_60MIN" />
		<MAXPLAYERS player="4"  str="4" />
		<MAXPLAYERS player="8"  str="8" default="true" />
		<MAXPLAYERS player="12" str="12" />
		<MAXPLAYERS player="16" str="16" />
	</GAMETYPE>


[Extras] <br>
Open(ZWorld.cpp) <br>
Find <br>

	sprintf(szBuf, "%s%s/smoke.xml", szMapPath, ZGetGameClient()->GetMatchStageSetting()->GetMapName());
	m_pMapDesc->LoadSmokeDesc(szBuf);

Add under <br>

	if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_VAMPIRE)
	{
		m_bFog = true;
		m_fFogNear = 0.0f;
		m_fFogFar = 6000.0f;
		m_dwFogColor = 0xC30404;
	}




































