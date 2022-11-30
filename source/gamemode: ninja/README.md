Open(MBaseGameType.h) <br>
Find <br>

    enum MMATCH_GAMETYPE

Add <br>

    MMATCH_GAMETYPE_NINJA				=14,


Open(MMatchRule.h) <br>
Find <br>

    inline bool IsGameRuleDeathMatch(MMATCH_GAMETYPE nGameType)

Add <br>

    (nGameType == MMATCH_GAMETYPE_NINJA) ||


Open(MBaseGameType.cpp) <br>
Find <br>

    #define MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR

Add <br>

    #define MMATCH_GAMETYPE_NINJA_STR			    "Ninja"


Find <br>

    _InitGameType(MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR,  1.0f,			1.0f,					0.0f);

Add <br>

    _InitGameType(MMATCH_GAMETYPE_NINJA, MMATCH_GAMETYPE_NINJA, MMATCH_GAMETYPE_NINJA_STR, 1.0f, 1.0f, 0.0f);

Open(MMatchStage.cpp) <br>

Find <br>

	case MMATCH_GAMETYPE_DUEL:
		{
			return (new MMatchRuleDuel(this));
		}
		break;


Add <br>

	case MMATCH_GAMETYPE_NINJA:
	{
		return (new MMatchRuleNinja(this));
	}
	break;


Open(ZGame.cpp) <br>
Find <br>

			ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_GLADIATOR_SOLO ||


Add <br>

			ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_NINJA ||


Open(ZGameInterface.cpp) <br>
Find <br>

	ZGetGameTypeManager()->SetGameTypeStr( MMATCH_GAMETYPE_DEATHMATCH_SOLO, ZMsg( MSG_MT_DEATHMATCH_SOLO));

Add <br>

	ZGetGameTypeManager()->SetGameTypeStr(MMATCH_GAMETYPE_NINJA, ZMsg(MSG_MT_NINJA));


Open(ZMyCharacter.cpp) <br>
Find <br>

			bool bJump2=(ZGetGame()->GetTime()-m_pModule_Movable->GetAdjustedTime()<0.2f 
				&& Magnitude(pickorigin-bpi.PickPos)<100.f
				&& DotProduct(rvector(0,0,-1),PickedNormal)<0.1f
				&& (fDotJump2>.8f || fDotJump2<-.8f || fDotJump2right>.8f || fDotJump2right<-.8f)
				&& ZGetGame()->GetTime()-m_timeInfo.Ref().m_fJump2Time>.5f)
				&& fProjSpeed < -100.f
				&& GetDistToFloor() > 30.f
				&& !uStatus.m_bWallJump && !bWallJump && !uStatus.m_bLand && !zStatus.m_bGuard;


Add <br> 

			if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_NINJA)
				bJump2 = true;

Open(ZRule.cpp) <br>
Find <br>

	case MMATCH_GAMETYPE_DUEL:
		{
			return (new ZRuleDuel(pMatch));
		}
		break;


Add <br>

	case MMATCH_GAMETYPE_NINJA:
		{
			return (new ZRuleNinja(pMatch));
		}
		break;

Open(ZStageInterface.cpp) <br>
Find <br>

		case MMATCH_GAMETYPE_DEATHMATCH_SOLO:
			color = SDM_COLOR;
			break;
      
Replace <br>

		case MMATCH_GAMETYPE_DEATHMATCH_SOLO:
		case MMATCH_GAMETYPE_NINJA:
			color = SDM_COLOR;
			break;


Find <br>

    MAnimation* pAniMapImg = (MAnimation*)pResource->FindWidget( "Stage_MapNameBG");


Add <br>

    (pSetting->nGameType == MMATCH_GAMETYPE_NINJA) ||


Find <br>

    MWidget* pWidget = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "StageRoundCountLabel");

Add <br>

    (pSetting->nGameType == MMATCH_GAMETYPE_NINJA) ||


Open(ZRuleDeathMatch.cpp) <br>
Find <br>

    ZRuleSoloDeathMatch::ZRuleSoloDeathMatch(ZMatch* pMatch) : ZRule(pMatch)
    {

    }

    ZRuleSoloDeathMatch::~ZRuleSoloDeathMatch()
    {

    }


Add <br>


    ZRuleNinja::ZRuleNinja(ZMatch* pMatch) : ZRuleSoloDeathMatch(pMatch)
    {

    }

    ZRuleNinja::~ZRuleNinja()
    {

    }


Open(ZRuleDeathMatch.h) <br>
Find <br>

    class ZRuleTeamDeathMatch : public ZRule
    {
    public:
      ZRuleTeamDeathMatch(ZMatch* pMatch);
      virtual ~ZRuleTeamDeathMatch();
    };


Add <br>

    class ZRuleNinja : public ZRuleSoloDeathMatch
    {
    public:
      ZRuleNinja(ZMatch* pMatch);
      virtual ~ZRuleNinja();
    };


Open(MMatchRuleDeathMatch.h)
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


Add <br>

    ///////////////////////////////////////////////////////////////////////////////////////////////
    class MMatchRuleNinja : public MMatchRuleSoloDeath {
    public:
      MMatchRuleNinja(MMatchStage* pStage);
      virtual ~MMatchRuleNinja() { }
      virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_NINJA; }
    };


Open(MMatchRuleDeathMatch.cpp)
Find <br>

    MMatchRuleTeamDeath2::MMatchRuleTeamDeath2(MMatchStage* pStage) : MMatchRule(pStage)
    {
    }

Add Above <br>

    MMatchRuleNinja::MMatchRuleNinja(MMatchStage* pStage) : MMatchRuleSoloDeath(pStage)
    {
    }


System/MatchServer <br>
Open(ChannelRule.xml) <br>

    <GAMETYPE id="14" />


Open(Gametypecfg.xml) <br>

	<GAMETYPE id="14">
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








