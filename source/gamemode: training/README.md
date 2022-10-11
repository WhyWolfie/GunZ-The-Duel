Unfinished <br>
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

	ZGetGameTypeManager()->SetGameTypeStr( MMATCH_GAMETYPE_TEAM_TRAINING, ZMsg( MSG_MT_TEAM_TRAINING));

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


