Open(MBaseGameType.h) <br>
Find <br>

    MMATCH_GAMETYPE_DEATHMATCH_SOLO		=0,

Add under <br>

	MMATCH_GAMETYPE_GUNMODE				=18,

Find <br>

    inline bool IsGameRuleDeathMatch(MMATCH_GAMETYPE nGameType)

Add under <br>

    (nGameType == MMATCH_GAMETYPE_GUNMODE) ||

Open(MMatchRuleDeathMatch.cpp) <br>
Find <br>

    class MMatchRuleTeamCTF : public MMatchRule {

Add under <br>

    class MMatchRuleGunMode : public MMatchRule {
    protected:
      bool CheckKillCount(MMatchObject* pOutObject);
      virtual void OnBegin();
      virtual void OnEnd();
      virtual void OnRoundTimeOut();
      virtual bool OnCheckRoundFinish();
      virtual bool RoundCount();
    public:
      MMatchRuleGunMode(MMatchStage* pStage);
      virtual ~MMatchRuleGunMode() { }
      virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_GUNMODE; }
    };

Open(MBaseGameType.cpp) <br>
Find <br>

    #define MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR		"Death Match(Solo)"

Add under <br>

    #define MMATCH_GAMETYPE_GUNMODE_STR			    "GunGame"


Find <br>

    _InitGameType(MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR,  1.0f,			1.0f,					0.0f);

Add under <br>

    _InitGameType(MMATCH_GAMETYPE_GUNMODE, MMATCH_GAMETYPE_GUNMODE, MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR, 1.0f, 1.0f, 0.0f);

Open(MMatchStage.cpp) <br>
Find <br>

	case MMATCH_GAMETYPE_CTF:
		{
			return (new MMatchRuleTeamCTF(this));
		}
		break;

Add under <br>

	case MMATCH_GAMETYPE_GUNMODE:
	{
		return (new MMatchRuleGunMode(this));
	}
	break;

Open(ZCombatInterface.cpp) <br>
Find <br>

    DrawMyWeaponPont(pDC);

Add under <br>

				if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_GUNMODE)
				{
					char buffer[256];
					sprintf(buffer, "[Level %d / %d ]", m_nGunLevel, ZGetGame()->GetMatch()->GetRoundCount());
					TextRelative(pDC, 660.f / 800.f, 480.f / 600.f, buffer);
				}

Open(ZGame.cpp) <br>
Find <br>

		pAttacker->GetStatus().Ref().AddExp(nAttackerExp);
		if (!bSuicide) 
			pAttacker->GetStatus().Ref().AddKills();

Add under <br>

		if (GetMatch()->GetMatchType() == MMATCH_GAMETYPE_GUNMODE && pVictim != m_pMyCharacter)
		{

			ZGetCombatInterface()->GunMode(pAttacker, pAttacker->GetKils());
			ZGetCombatInterface()->AddGunLevel();
		}

Open(ZGameInterface.cpp) <br>
Find <br>

	ZGetGameTypeManager()->SetGameTypeStr( MMATCH_GAMETYPE_DEATHMATCH_SOLO, ZMsg( MSG_MT_DEATHMATCH_SOLO));

Add under <br>

	ZGetGameTypeManager()->SetGameTypeStr( MMATCH_GAMETYPE_GUNMODE, "GunGame");

Open(ZRule.cpp) <br>
Find <br>

	case MMATCH_GAMETYPE_DUEL:
		{
			return (new ZRuleDuel(pMatch));
		}
		break;

Add under <br>

	case MMATCH_GAMETYPE_GUNMODE:
	{
		return (new ZRuleGunMode(pMatch));
	}
	break;

Open(ZStageInterface.cpp) <br>
Find <br>

    case MMATCH_GAMETYPE_DEATHMATCH_SOLO:

Add under <br>

    case MMATCH_GAMETYPE_GUNMODE:


Find <br>

    MAnimation* pAniMapImg = (MAnimation*)pResource->FindWidget( "Stage_MapNameBG");

Add under <br>

    (pSetting->nGameType == MMATCH_GAMETYPE_GUNMODE) ||


Find <br>

    MWidget* pWidget = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "StageRoundCountLabel");

Add under <br>

    (pSetting->nGameType == MMATCH_GAMETYPE_GUNMODE) ||



