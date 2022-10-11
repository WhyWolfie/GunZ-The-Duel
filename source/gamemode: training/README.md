Team-Training & XMLs <br>
Open(MBaseGameType.h - enum MMATCH_GAMETYPE) <br>

	MMATCH_GAMETYPE_TEAM_TRAINING		=13,
  

Find(MBaseGameTypeCatalogue::IsTeamGame)

    (nGameType == MMATCH_GAMETYPE_TEAM_TRAINING) ||


Find(MBaseGameTypeCatalogue::IsTeamLimitTime)

    (nGameType == MMATCH_GAMETYPE_TEAM_TRAINING) ||

Find(MBaseGameTypeCatalogue::IsWaitForRoundEnd)

    (nGameType == MMATCH_GAMETYPE_TEAM_TRAINING) ||


Open(MMatchRule.h - IsGameRuleDeathMatch)

    (nGameType == MMATCH_GAMETYPE_TEAM_TRAINING) ||

Open(MMatchRuleTraining.h)

    class MMatchRuleTeamTraining : public MMatchRuleTeamDeath
    {
    public:
      MMatchRuleTeamTraining(MMatchStage* pStage);
      virtual ~MMatchRuleTeamTraining() { }
      virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_TEAM_TRAINING; }
    };
    
Open(MBaseGameType.cpp - MMATCH_GAMETYPE_DUELTOURNAMENT_STR)

    #define MMATCH_GAMETYPE_TEAM_TRAINING_STR		"Training(Team)"
    
    
Find(_InitGameType(MMATCH_GAMETYPE_DUELTOURNAMENT)

    _InitGameType(MMATCH_GAMETYPE_TEAM_TRAINING,	MMATCH_GAMETYPE_TEAM_TRAINING,		MMATCH_GAMETYPE_TEAM_TRAINING_STR,	  0.0f,			0.0f,					0.0f);


Open(MMatchServer_Stage.cpp)

	if (nGameType == MMATCH_GAMETYPE_TRAINING)
	{
		*poutAttackerExp = 0;
		*poutVictimExp = 0;
		return;
	}
  
Replace

	if (nGameType == MMATCH_GAMETYPE_TRAINING || nGameType == MMATCH_GAMETYPE_TEAM_TRAINING)
	{
		*poutAttackerExp = 0;
		*poutVictimExp = 0;
		return;
	}
  
Open(MMatchStage.cpp - MMatchStage::CreateRule(MMATCH_GAMETYPE nGameType))

	case MMATCH_GAMETYPE_TEAM_TRAINING:
		{
			return (new MMatchRuleTeamTraining(this));
		}
		break;
    
Open(ZGameInterface.cpp - ZGetGameTypeManager()->SetGameTypeStr( MMATCH_GAMETYPE_QUEST_CHALLENGE)

	ZGetGameTypeManager()->SetGameTypeStr( MMATCH_GAMETYPE_TEAM_TRAINING, "Team Training");

Open(ZRule.cpp - ZRule::CreateRule(ZMatch* pMatch, MMATCH_GAMETYPE nGameType))

	case MMATCH_GAMETYPE_TEAM_TRAINING:
		{
			return (new ZRuleTeamTraining(pMatch));
		}
		break;

Open(ZStageInterface.cpp - case MMATCH_GAMETYPE_TRAINING:)

    case MMATCH_GAMETYPE_TEAM_TRAINING:

Find

	else if ( (pSetting->nGameType == MMATCH_GAMETYPE_DEATHMATCH_TEAM) ||		// µ¥¾²¸ÅÄ¡ ÆÀÀüÀÌ°Å³ª...
		(pSetting->nGameType == MMATCH_GAMETYPE_DEATHMATCH_TEAM2) ||			// ¹«ÇÑµ¥½º¸ÅÄ¡ ÆÀÀüÀÌ°Å³ª...
		 (pSetting->nGameType == MMATCH_GAMETYPE_GLADIATOR_TEAM) ||				// Ä®Àü ÆÀÀüÀÌ°Å³ª...
		 (pSetting->nGameType == MMATCH_GAMETYPE_ASSASSINATE) ||
		 (pSetting->nGameType == MMATCH_GAMETYPE_CTF))					// ¾Ï»ìÀü ÀÌ¸é...
	{
		// ¸Ê ÀÌ¸§ ¹è°æ ÀÌ¹ÌÁö º¯È¯
		if ( pAniMapImg)
			pAniMapImg->SetCurrentFrame( 1);

		// Äù½ºÆ® UI °¨Ãã
		bQuestUI = false;
	}
     
Replace 

	else if ( (pSetting->nGameType == MMATCH_GAMETYPE_DEATHMATCH_TEAM) ||		// µ¥¾²¸ÅÄ¡ ÆÀÀüÀÌ°Å³ª...
		(pSetting->nGameType == MMATCH_GAMETYPE_DEATHMATCH_TEAM2) ||			// ¹«ÇÑµ¥½º¸ÅÄ¡ ÆÀÀüÀÌ°Å³ª...
		 (pSetting->nGameType == MMATCH_GAMETYPE_GLADIATOR_TEAM) ||				// Ä®Àü ÆÀÀüÀÌ°Å³ª...
		 (pSetting->nGameType == MMATCH_GAMETYPE_ASSASSINATE) ||				// ¾Ï»ìÀü ÀÌ¸é...
		 (pSetting->nGameType == MMATCH_GAMETYPE_TEAM_TRAINING) ||
		 (pSetting->nGameType == MMATCH_GAMETYPE_CTF))
	{
		// ¸Ê ÀÌ¸§ ¹è°æ ÀÌ¹ÌÁö º¯È¯
		if ( pAniMapImg)
			pAniMapImg->SetCurrentFrame( 1);

		// Äù½ºÆ® UI °¨Ãã
		bQuestUI = false;
	}


Open(ZRuleTraining.cpp) <br>

	ZRuleTeamTraining::ZRuleTeamTraining(ZMatch* pMatch) : ZRuleTeamDeathMatch(pMatch)
	{

	}

	ZRuleTeamTraining::~ZRuleTeamTraining()
	{

	}
	
Open(ZRuleTraining.h) <br>

	class ZRuleTeamTraining : public ZRuleTeamDeathMatch
	{
	public:
		ZRuleTeamTraining(ZMatch* pMatch);
		virtual ~ZRuleTeamTraining();
	};

Open(MMatchRuleTraining.cpp) <br>

	///////////////////////////////////////////////////////////////////////////////////////////////
	// MMatchRuleTeamTraining /////////////////////////////////////////////////////////////////////////
	MMatchRuleTeamTraining::MMatchRuleTeamTraining(MMatchStage* pStage) : MMatchRuleTeamDeath(pStage)
	{


	}

Open(System.mrs->ChannelRule.xml and Add)

	<GAMETYPE id="13" />

Open(System.mrs->Gametypecfg.xml and Add)

	<GAMETYPE id="13">	<!-- TEAM TRAINING -->
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
