Open(MBaseGameType.h) <br>
Find <br>

    enum MMATCH_GAMETYPE {

Add 

    MMATCH_GAMETYPE_NOKSTYLE			=20,

Open(MMatchRule.h) <br>
Find <br>

    inline bool IsGameRuleDeathMatch(MMATCH_GAMETYPE nGameType)

Add 

    (nGameType == MMATCH_GAMETYPE_NOKSTYLE) ||

Open(MBaseGameType.cpp) <br>
Find <br>

    #define MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR		"Death Match(Solo)"

Add <br>

    #define MMATCH_GAMETYPE_NOKSTYLE_STR			"No K-Style"


Find <br>

    _InitGameType(MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR,  1.0f,			1.0f,					0.0f);

Add <br>

    _InitGameType(MMATCH_GAMETYPE_NOKSTYLE, MMATCH_GAMETYPE_NOKSTYLE, MMATCH_GAMETYPE_NOKSTYLE_STR, 1.0f, 1.0f, 0.0f);


Open(MMatchStage.cpp) <br>
Find <br>

	case MMATCH_GAMETYPE_DEATHMATCH_SOLO:
		{
			return (new MMatchRuleSoloDeath(this));
		}
		break;

Add <br>

	case MMATCH_GAMETYPE_NOKSTYLE:
	{
		return (new MMatchRuleNKS(this));
	}
	break;

Open(ZGameInterface.cpp) <br>
Find <br>

	ZGetGameTypeManager()->SetGameTypeStr( MMATCH_GAMETYPE_DEATHMATCH_SOLO, ZMsg( MSG_MT_DEATHMATCH_SOLO));


Add <br>

	ZGetGameTypeManager()->SetGameTypeStr(MMATCH_GAMETYPE_NOKSTYLE, "No K-Style");

Open(ZMyCharacter.cpp) <br>
Find <br>

	if (bBothPressed)
	{
		if (!zStatus.m_bGuard && bGuardTime)
		{

Add under <br>

			if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_NOKSTYLE || (strstr(ZGetGameClient()->GetChannelName(), "Classic")))
			{
				if (zStatus.m_bShot || zStatus.m_bJumpShot || zStatus.m_bSkill)
					return;
			}

Open(ZRule.cpp) <br>
Find <br>

	case MMATCH_GAMETYPE_GLADIATOR_TEAM:
		{
			return (new ZRuleTeamGladiator(pMatch));
		}
		break;

Add <br>

	case MMATCH_GAMETYPE_NOKSTYLE:
	{
		return (new ZRuleNKS(pMatch));
	}
	break;

Open(ZStageInterface.cpp) <br>
Find <br>

		case MMATCH_GAMETYPE_DEATHMATCH_SOLO:
			color = SDM_COLOR;
			break;
      
Add <br>

		case MMATCH_GAMETYPE_NOKSTYLE:

Find <br>

	MAnimation* pAniMapImg = (MAnimation*)pResource->FindWidget( "Stage_MapNameBG");
	bool bQuestUI = false;

Add <br>

    (pSetting->nGameType == MMATCH_GAMETYPE_NOKSTYLE) ||

Find <br>

	MWidget* pWidget = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "StageRoundCountLabel");
	if ( pWidget)

Add <br>

    (pSetting->nGameType == MMATCH_GAMETYPE_NOKSTYLE) ||

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


Add <br>

    class MMatchRuleNKS : public MMatchRuleSoloDeath  {
    public:
      MMatchRuleNKS(MMatchStage* pStage);
      virtual ~MMatchRuleNKS() { }
      virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_NOKSTYLE; }
    };


Open(MMatchRuleDeathMatch.cpp) <br>
Find <br>

    // TEAM DEATH RULE ///////////////////////////////////////////////////////////////
    MMatchRuleTeamDeath::MMatchRuleTeamDeath(MMatchStage* pStage) : MMatchRule(pStage)
    {
    }

Add <br>

    MMatchRuleNKS::MMatchRuleNKS(MMatchStage* pStage) : MMatchRuleSoloDeath(pStage)
    {
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

    class ZRuleNKS : public ZRuleSoloDeathMatch
    {
    public:
      ZRuleNKS(ZMatch* pMatch);
      virtual ~ZRuleNKS();
    };


Open(ZRuleDeathMatch.cpp) <br>
Find <br>

    ZRuleSoloDeathMatch::ZRuleSoloDeathMatch(ZMatch* pMatch) : ZRule(pMatch)
    {

    }

Add <br>

    ZRuleNKS::ZRuleNKS(ZMatch* pMatch) : ZRuleSoloDeathMatch(pMatch)
    {

    }

    ZRuleNKS::~ZRuleNKS()
    {

    }


System/ChannelRule.xml <br>

		<GAMETYPE id="20" />

System/Gametypecfg.xml <br>

	<GAMETYPE id="20">	<!-- k-style -->
		<ROUNDS    round="10"	str="10" />
		<ROUNDS    round="20"	str="20" />
		<ROUNDS    round="30"	str="30" default="true" />
		<ROUNDS    round="50"	str="50" />
		<ROUNDS    round="70"	str="70" />
		<ROUNDS    round="100"	str="100" />
		<LIMITTIME sec="99999"	str="STR:GAMETYPECFG_LIMITTIME_INFINITE" />
		<LIMITTIME sec="5"	str="STR:GAMETYPECFG_LIMITTIME_5MIN" />
		<LIMITTIME sec="10"	str="STR:GAMETYPECFG_LIMITTIME_10MIN" default="true" />
		<LIMITTIME sec="15"	str="STR:GAMETYPECFG_LIMITTIME_15MIN" />
		<LIMITTIME sec="20"	str="STR:GAMETYPECFG_LIMITTIME_20MIN" />
		<LIMITTIME sec="25"	str="STR:GAMETYPECFG_LIMITTIME_25MIN" />
		<LIMITTIME sec="30"	str="STR:GAMETYPECFG_LIMITTIME_30MIN" />
		<MAXPLAYERS player="4"  str="4" />
		<MAXPLAYERS player="8"  str="8" default="true" />
		<MAXPLAYERS player="12" str="12" />
		<MAXPLAYERS player="16" str="16" />
	</GAMETYPE>

Replace MatchServer / System.mrs <br>

Rebuild Gunz & MatchServer <br>


















































































































































































