Open(MBaseGameType.h) <br>
Find <br>

    enum MMATCH_GAMETYPE {

Add <br>

    MMATCH_GAMETYPE_REVERSE_BERSERKER	=22,

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

    class MMatchRuleReverseBerserker : public MMatchRuleSoloDeath {
    protected:
      // ¸â¹öº¯¼ö ---------------------
      MUID		m_uidBerserker;				// ÇöÀç ¹ö¼­Ä¿ÀÎ ÇÃ·¹ÀÌ¾î

      // ÇÔ¼ö -------------------------
      bool CheckKillCount(MMatchObject* pOutObject);
      virtual void OnRoundBegin();
      virtual bool OnCheckRoundFinish();
      void RouteAssignBerserker();
      MUID RecommendReverseBerserker();
    public:
      MMatchRuleReverseBerserker(MMatchStage* pStage);
      virtual ~MMatchRuleReverseBerserker() { }
      virtual void* CreateRuleInfoBlob();
      virtual void OnEnterBattle(MUID& uidChar);			///< °ÔÀÓÁß ³­ÀÔÇÒ¶§ È£ÃâµÈ´Ù.
      virtual void OnLeaveBattle(MUID& uidChar);			///< °ÔÀÓÁß ³ª°¬À»¶§ È£ÃâµÈ´Ù.
      virtual void OnGameKill(const MUID& uidAttacker, const MUID& uidVictim);
      virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_REVERSE_BERSERKER; }
      MUID& GetBerserker() { return m_uidBerserker; }
    };

Open(MBaseGameType.cpp) <br>
Find <br>

    #define MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR		"Death Match(Solo)"

Add <br>

    #define MMATCH_GAMETYPE_REVERSE_BERSERKER_STR	"Reverse Berserker"

Find <br>

    const char* MMatchGameTypeAcronym[MMATCH_GAMETYPE_MAX] = {
      "DM",		// DEATHMATCH_SOLO


Add <br>

	"DMRB",		// MMATCH_GAMETYPE_REVERSE_BERSERKER

Find <br>

    _InitGameType(MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR,  1.0f,			1.0f,					0.0f);

Add <br>

    _InitGameType(MMATCH_GAMETYPE_REVERSE_BERSERKER, MMATCH_GAMETYPE_REVERSE_BERSERKER, MMATCH_GAMETYPE_REVERSE_BERSERKER_STR, 1.5f, 0.0f, 0.0f);

Open(MMatchStage.cpp) <br>
Find <br>

	case MMATCH_GAMETYPE_DUEL:
		{
			return (new MMatchRuleDuel(this));
		}
		break;


Add <br>

	case MMATCH_GAMETYPE_REVERSE_BERSERKER:
		{
			return (new MMatchRuleReverseBerserker(this));
		}
		break;

Open(ZGame.cpp) <br>
Find <br>


    float CalcActualDamage(ZObject* pAttacker, ZObject* pVictim, float fDamage)
    {
      if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_BERSERKER)
      {
        ZRuleBerserker* pRule = (ZRuleBerserker*)ZGetGame()->GetMatch()->GetRule();
        if ((pAttacker) && (pAttacker != pVictim) && (pAttacker->GetUID() == pRule->GetBerserkerUID()))
        {
          return fDamage * BERSERKER_DAMAGE_RATIO;			
        }
      }

      else if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_REVERSE_BERSERKER)
      {
        ZRuleReverseBerserker* pRule = (ZRuleReverseBerserker*)ZGetGame()->GetMatch()->GetRule();
        if ((pAttacker) && (pAttacker != pVictim) && (pAttacker->GetUID() == pRule->GetBerserkerUID()))
        {
          return fDamage * BERSERKER_DAMAGE_RATIO;
        }
      }

      return fDamage;
    }

Open(ZGameInterface.cpp) <br>
Find <br>

	ZGetGameTypeManager()->SetGameTypeStr( MMATCH_GAMETYPE_DEATHMATCH_SOLO, ZMsg( MSG_MT_DEATHMATCH_SOLO));

Add <br>

	ZGetGameTypeManager()->SetGameTypeStr( MMATCH_GAMETYPE_REVERSE_BERSERKER, "Reverse Berserker");


Open(ZRule.cpp) <br>
Find <br>

	case MMATCH_GAMETYPE_DUEL:
		{
			return (new ZRuleDuel(pMatch));
		}
		break;

Add <br>

	case MMATCH_GAMETYPE_REVERSE_BERSERKER:
	{
		return (new ZRuleReverseBerserker(pMatch));
	}
	break;

Open(ZStageInterface.cpp) <br>
Find <br>

    MAnimation* pAniMapImg = (MAnimation*)pResource->FindWidget( "Stage_MapNameBG");
    bool bQuestUI = false, bSpyUI = false;

Add <br>

    (pSetting->nGameType == MMATCH_GAMETYPE_REVERSE_BERSERKER ) ||


Open(ZRuleDeathMatch.cpp) <br>
Find <br>

    ZRuleSoloDeathMatch::ZRuleSoloDeathMatch(ZMatch* pMatch) : ZRule(pMatch)
    {

    }

    ZRuleSoloDeathMatch::~ZRuleSoloDeathMatch()
    {





    }

Add <br>

    #define BERSERKER_UPDATE_HEALTH_TIME		5.0f		// ¹ö¼­Ä¿´Â 5ÃÊ¸¶´Ù ÇÇ°¡ 10¾¿ ÁØ´Ù.
    #define BERSERKER_UPDATE_HEALTH				10
    #define BERSERKER_BONUS_HEALTH				50			// ¹ö¼­Ä¿´Â ÀûÀ» Á×ÀÌ¸é 50ÀÇ ÇÇ°¡ Âù´Ù.

    ZRuleReverseBerserker::ZRuleReverseBerserker(ZMatch* pMatch) : ZRule(pMatch), m_uidBerserker(0,0)
    {

    }

    ZRuleReverseBerserker::~ZRuleReverseBerserker()
    {


    }

    bool ZRuleReverseBerserker::OnCommand(MCommand* pCommand)
    {
      if (!ZGetGame()) return false;

      switch (pCommand->GetID())
      {
      case MC_MATCH_ASSIGN_REVERSE_BERSERKER:
        {
          MUID uidBerserker;
          pCommand->GetParameter(&uidBerserker,		0, MPT_UID);

          AssignBerserker(uidBerserker);
        }
        break;
      case MC_MATCH_GAME_DEAD:
        {
          MUID uidAttacker, uidVictim;
          unsigned long int nAttackerArg, nVictimArg;

          pCommand->GetParameter(&uidAttacker, 0, MPT_UID);
          pCommand->GetParameter(&nAttackerArg, 1, MPT_UINT);
          pCommand->GetParameter(&uidVictim, 2, MPT_UID);
          pCommand->GetParameter(&nVictimArg, 3, MPT_UINT);


          bool bSuicide = false;
          if (uidAttacker == uidVictim) bSuicide = true;

          if ((uidAttacker != MUID(0,0)) && (uidAttacker == m_uidBerserker))
          {
            if (!bSuicide)
            {
              ZCharacter* pAttacker = ZGetGame()->m_CharacterManager.Find(uidAttacker);
              BonusHealth(pAttacker);
            }
          }
        }
        break;
      }

      return false;
    }

    void ZRuleReverseBerserker::OnResponseRuleInfo(MTD_RuleInfo* pInfo)
    {
      MTD_RuleInfo_Berserker* pBerserkerRule = (MTD_RuleInfo_Berserker*)pInfo;
      AssignBerserker(pBerserkerRule->uidBerserker);
    }


    void ZRuleReverseBerserker::AssignBerserker(MUID& uidBerserker)
    {
      if (!ZGetGame()) return;

      for (ZCharacterManager::iterator itor = ZGetGame()->m_CharacterManager.begin();
        itor != ZGetGame()->m_CharacterManager.end(); ++itor)
      {
        ZCharacter* pCharacter = (*itor).second;
        pCharacter->SetTagger(false);
      }

      ZCharacter* pBerserkerChar = ZGetGame()->m_CharacterManager.Find(uidBerserker);
      if (pBerserkerChar)
      {
        ZGetEffectManager()->AddBerserkerIcon(pBerserkerChar);
        pBerserkerChar->SetTagger(true);

        // ¹ö¼­Ä¿°¡ µÇ¸é ÇÇ°¡ ²Ë Âù´Ù.
        if (!pBerserkerChar->IsDie())
        {
          float fMaxHP = pBerserkerChar->GetProperty()->fMaxHP.Ref();
          float fMaxAP = pBerserkerChar->GetProperty()->fMaxAP.Ref();
          pBerserkerChar->SetHP(fMaxHP);
          pBerserkerChar->SetAP(fMaxAP);


          if ( uidBerserker == ZGetMyUID())
            ZGetGameInterface()->PlayVoiceSound( VOICE_GOT_BERSERKER, 1600);
          else
            ZGetGameInterface()->PlayVoiceSound( VOICE_BERSERKER_DOWN, 1200);
        }

      }

      m_uidBerserker = uidBerserker;
      m_fElapsedHealthUpdateTime = 0.0f;
    }

    void ZRuleReverseBerserker::OnUpdate(float fDelta)
    {
      m_fElapsedHealthUpdateTime += fDelta;

      if (BERSERKER_UPDATE_HEALTH_TIME < m_fElapsedHealthUpdateTime)
      {
        m_fElapsedHealthUpdateTime = 0.0f;
        for (ZCharacterManager::iterator itor = ZGetGame()->m_CharacterManager.begin();	itor != ZGetGame()->m_CharacterManager.end(); ++itor)
        {
          ZCharacter* pCharacter = (*itor).second;
          if(pCharacter->GetUID() != GetBerserkerUID() && !pCharacter->IsDie())
          AddHealth(pCharacter);
        }
      }
    }

    void ZRuleReverseBerserker::BonusHealth(ZCharacter* pBerserker)
    {
      if (pBerserker)
      {
        if (pBerserker->IsDie()) 
        {
          CHECK_RETURN_CALLSTACK(BonusHealth);
          return;
        }

        float fBonusAP = 0.0f;
        float fBonusHP = BERSERKER_BONUS_HEALTH;

        float fMaxHP = pBerserker->GetProperty()->fMaxHP.Ref();

        if ((fMaxHP - pBerserker->GetHP()) < BERSERKER_BONUS_HEALTH)
        {
          fBonusHP = fMaxHP - pBerserker->GetHP();
          fBonusAP = BERSERKER_BONUS_HEALTH - fBonusHP;
        }

        pBerserker->SetHP(pBerserker->GetHP() + fBonusHP);
        pBerserker->SetAP(pBerserker->GetAP() + fBonusAP);
      }
      CHECK_RETURN_CALLSTACK(BonusHealth);
    }

    void ZRuleReverseBerserker::AddHealth(ZCharacter* Uid)
    {
      float fAP = max(0.0f, Uid->GetAP() + BERSERKER_UPDATE_HEALTH);
      Uid->SetAP(fAP);

      float fHP = max(1.0f, Uid->GetHP() + BERSERKER_UPDATE_HEALTH);
        Uid->SetHP(fHP);

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

    class ZRuleReverseBerserker : public ZRule
    {
    private:
      MUID	m_uidBerserker;
      float	m_fElapsedHealthUpdateTime;
      void AssignBerserker(MUID& uidBerserker);
      virtual void OnUpdate(float fDelta);
      void BonusHealth(ZCharacter* pBerserker);
      void AddHealth(ZCharacter* Uid);
    public:
      ZRuleReverseBerserker(ZMatch* pMatch);
      virtual ~ZRuleReverseBerserker();
      virtual bool OnCommand(MCommand* pCommand);
      virtual void OnResponseRuleInfo(MTD_RuleInfo* pInfo);
      MUID GetBerserkerUID() const { return m_uidBerserker; }
    };


Open(MSharedCommandTable.h) <br>
Find <br>

    #define MC_MATCH_FLAG_STATE	50022

Add <br>

    #define MC_MATCH_ASSIGN_REVERSE_BERSERKER		50077

Open(MSharedCommandTable.cpp) <br>
Find <br>

	C(MC_MATCH_DUELTOURNAMENT_GAME_MATCH_RESULT_INFO, "Match.DuelTournament.Game Match Result Info", "Duel Tournament Game Match-Result Info", MCDT_MACHINE2MACHINE)
		P(MPT_BLOB, "GameMatchResultInfo");

Add <br>
  
	C(MC_MATCH_ASSIGN_REVERSE_BERSERKER, "Match.Assign.Reverse.Berserker", "Assign Reverse Berserker", MCDT_MACHINE2MACHINE)
		P(MPT_UID, "uidPlayer");

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

	case MC_MATCH_ASSIGN_REVERSE_BERSERKER:

Open(MMatchRuleDeathMatch.cpp) <br>
Find <br>

    // TEAM DEATH RULE ///////////////////////////////////////////////////////////////
    MMatchRuleTeamDeath::MMatchRuleTeamDeath(MMatchStage* pStage) : MMatchRule(pStage)
    {
    }

Add <br>


    //////////////////////////////////////////////////////////////////////////////////
    // MMatchRuleReverseBerserker ///////////////////////////////////////////////////////////
    MMatchRuleReverseBerserker::MMatchRuleReverseBerserker(MMatchStage* pStage) : MMatchRuleSoloDeath(pStage), m_uidBerserker(0,0)
    {

    }

    bool MMatchRuleReverseBerserker::OnCheckRoundFinish()
    {
      return MMatchRuleSoloDeath::OnCheckRoundFinish();
    }

    void MMatchRuleReverseBerserker::OnRoundBegin()
    {
      m_uidBerserker = MUID(0,0);
    }

    void* MMatchRuleReverseBerserker::CreateRuleInfoBlob()
    {
      void* pRuleInfoArray = MMakeBlobArray(sizeof(MTD_RuleInfo_Berserker), 1);
      MTD_RuleInfo_Berserker* pRuleItem = (MTD_RuleInfo_Berserker*)MGetBlobArrayElement(pRuleInfoArray, 0);
      memset(pRuleItem, 0, sizeof(MTD_RuleInfo_Berserker));

      pRuleItem->nRuleType = MMATCH_GAMETYPE_BERSERKER;
      pRuleItem->uidBerserker = m_uidBerserker;

      return pRuleInfoArray;
    }

    void MMatchRuleReverseBerserker::RouteAssignBerserker()
    {	MCommand* pNew = MMatchServer::GetInstance()->CreateCommand(MC_MATCH_ASSIGN_REVERSE_BERSERKER, MUID(0, 0));
      pNew->AddParameter(new MCmdParamUID(m_uidBerserker));
      MMatchServer::GetInstance()->RouteToBattle(m_pStage->GetUID(), pNew);
    }


    MUID MMatchRuleReverseBerserker::RecommendReverseBerserker()
    {
      MMatchStage* pStage = GetStage();
      if (pStage == NULL) return MUID(0,0);

      int nCount = 0;
      for(MUIDRefCache::iterator itor=pStage->GetObjBegin(); itor!=pStage->GetObjEnd(); itor++) {
        MMatchObject* pObj = (MMatchObject*)(*itor).second;
        if (pObj->GetEnterBattle() == false) continue;	// ¹èÆ²Âü°¡ÇÏ°í ÀÖ´Â ÇÃ·¹ÀÌ¾î¸¸ Ã¼Å©
        if (pObj->CheckAlive())
        {
          return pObj->GetUID();
        }
      }
      return MUID(0,0);

    }


    void MMatchRuleReverseBerserker::OnEnterBattle(MUID& uidChar)
    {
    }

    void MMatchRuleReverseBerserker::OnLeaveBattle(MUID& uidChar)
    {
      if (uidChar == m_uidBerserker)
      {
        m_uidBerserker = MUID(0,0);
        RouteAssignBerserker();
      }
    }

    void MMatchRuleReverseBerserker::OnGameKill(const MUID& uidAttacker, const MUID& uidVictim)
    {
      // Èñ»ýÀÚ°¡ ¹ö¼­Ä¿ÀÌ°Å³ª ÇöÀç ¹ö¼­Ä¿°¡ ÇÑ¸íµµ ¾øÀ»¶§
      if ((m_uidBerserker == uidVictim) || (m_uidBerserker == MUID(0,0)))
      {
        bool bAttackerCanBeBerserker = false;

         // °ø°ÝÀÚ°¡ ÀÚ½ÅÀÌ ¾Æ´Ò °æ¿ì
        if (uidAttacker != uidVictim)
        {
          MMatchObject* pAttacker = MMatchServer::GetInstance()->GetObject(uidAttacker);

          // °ø°ÝÀÚ°¡ Á×¾îÀÖÀ¸¸é ¹ö¼­Ä¿°¡ µÉ ¼ö ¾ø´Ù(·¯ºê¼¦)
          if ((pAttacker) && (pAttacker->CheckAlive()))
          {
            bAttackerCanBeBerserker = true;
          }
        }
        // °ø°ÝÀÚ°¡ ÀÚ½ÅÀÏ °æ¿ì ¹ö¼­Ä¿´Â ¾Æ¹«µµ µÇÁö ¾Ê´Â´Ù.
        else if ((uidAttacker == MUID(0,0)) || (uidAttacker == uidVictim))
        {
          bAttackerCanBeBerserker = false;
        }

        if (bAttackerCanBeBerserker) m_uidBerserker = uidAttacker;
        else m_uidBerserker = MUID(0,0);

        RouteAssignBerserker();
      }
    }

















