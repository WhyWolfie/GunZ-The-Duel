Roomtag: [PAINT] <br>
Gamemode: Paintball <br>
Decompile SFX.mrs - unzip the sfx.zip (SFX/paintball01.tga)<br>

Open(MBaseGameType.h) <br>
Find <br>

    MMATCH_GAMETYPE_TRAINING			=5,

Add <br>


	MMATCH_GAMETYPE_PAINTBALL_SOLO     = 16,
	MMATCH_GAMETYPE_PAINTBALL_TEAM     = 17,

Find <br>

	inline bool MBaseGameTypeCatalogue::IsTeamGame(MMATCH_GAMETYPE nGameType)

Add under <br>

	(nGameType == MMATCH_GAMETYPE_PAINTBALL_TEAM) ||

Find <br>

	inline bool MBaseGameTypeCatalogue::IsTeamLimitTime(MMATCH_GAMETYPE nGameType)

Add under <br>
	
	(nGameType == MMATCH_GAMETYPE_PAINTBALL_TEAM) ||

Find <br>

	inline bool MBaseGameTypeCatalogue::IsWaitForRoundEnd(MMATCH_GAMETYPE nGameType)

Add under <br>

	(nGameType == MMATCH_GAMETYPE_PAINTBALL_TEAM) ||

Open(MBaseGameType.cpp) <br>
Find <br>

    #define MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR		"Death Match(Solo)"
    #define MMATCH_GAMETYPE_DEATHMATCH_TEAM_STR		"Death Match(Team)"

Add <br>

    #define MMATCH_GAMETYPE_PAINTBALL_SOLO_STR      "Paintball"
    #define MMATCH_GAMETYPE_PAINTBALL_TEAM_STR      "Team Paintball"

Find <br>

    _InitGameType(MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR,  1.0f,			1.0f,					0.0f);

Add <br>

    _InitGameType(MMATCH_GAMETYPE_PAINTBALL_SOLO, MMATCH_GAMETYPE_PAINTBALL_SOLO, MMATCH_GAMETYPE_PAINTBALL_SOLO_STR, 1.0f, 1.0f, 0.0f);
    _InitGameType(MMATCH_GAMETYPE_PAINTBALL_TEAM, MMATCH_GAMETYPE_PAINTBALL_TEAM, MMATCH_GAMETYPE_PAINTBALL_TEAM_STR, 1.0f, 0.8f, 0.3f);

Open(MMatchStage.cpp) <br>
Find <br>

	case MMATCH_GAMETYPE_DUEL:
		{
			return (new MMatchRuleDuel(this));
		}
		break;

Add <br>

	case MMATCH_GAMETYPE_PAINTBALL_SOLO:
		{
			return (new MMatchRuleSoloPaintball(this));
		}
		break;
		case MMATCH_GAMETYPE_PAINTBALL_TEAM:
		{
			return (new MMatchRuleTeamPaintball(this));
		}
		break;

Open(ZEffectBulletMarkList.cpp) <br>
Find <br>

    void ZEffectBulletMarkList::Update(float fElapsed)

Replace <br>

    void ZEffectBulletMarkList::Update(float fElapsed) {
      if (!strstr(strlwr((char*)ZGetGameClient()->GetStageName()), "[PAINT]")) {
        if ((ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_PAINTBALL_SOLO) != 0) {
          if ((ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_PAINTBALL_TEAM) != 0) {
            for (iterator i = begin(); i != end();) {
              ZEFFECTBULLETMARKITEM *p = (ZEFFECTBULLETMARKITEM*)*i;
              p->fElapsedTime += fElapsed;
              if (p->fElapsedTime > m_fLifeTime)
              {
                delete p;
                i = erase(i);
                continue;
              }
              float fVanish = min(1, max(0, (m_fLifeTime - p->fElapsedTime) / m_fVanishTime));
              DWORD color = ((DWORD)(fVanish * 255)) << 24 | 0xffffff;
              p->v[0].color = color;
              p->v[1].color = color;
              p->v[2].color = color;
              p->v[3].color = color;
              i++;
            }
          }
        }
      }
    }

Open(ZEffectManager.cpp) <br>
Find <br>

    m_BulletMarkList.Create("SFX/gz_sfx_shotgun_bulletmark01.tga");

Add under <br>

	//Paintball texture setup
	m_PaintballMarkList.Create("SFX/paintball01.tga");
	m_Paintball2MarkList.Create("SFX/paintball02.tga");
	m_Paintball3MarkList.Create("SFX/paintball03.tga");
	m_Paintball4MarkList.Create("SFX/paintball04.tga");
	m_Paintball5MarkList.Create("SFX/paintball05.tga");
	m_Paintball6MarkList.Create("SFX/paintball06.tga");
	m_Paintball7MarkList.Create("SFX/paintball07.tga");

Find <br>

    m_BulletMarkList.Clear();

Add under <br>

	m_PaintballMarkList.Clear();
	m_Paintball2MarkList.Clear();
	m_Paintball3MarkList.Clear();
	m_Paintball4MarkList.Clear();
	m_Paintball5MarkList.Clear();
	m_Paintball6MarkList.Clear();
	m_Paintball7MarkList.Clear();


Find <br>

    m_BulletMarkList.Draw();

Add under <br>

		//Paintball drawing
		m_PaintballMarkList.Draw();
		m_Paintball2MarkList.Draw();
		m_Paintball3MarkList.Draw();
		m_Paintball4MarkList.Draw();
		m_Paintball5MarkList.Draw();
		m_Paintball6MarkList.Draw();
		m_Paintball7MarkList.Draw();

Find <br>

    m_BulletMarkList.Draw();

Add under <br>

	//Paintball drawing
	m_PaintballMarkList.Draw();
	m_Paintball2MarkList.Draw();
	m_Paintball3MarkList.Draw();
	m_Paintball4MarkList.Draw();
	m_Paintball5MarkList.Draw();
	m_Paintball6MarkList.Draw();
	m_Paintball7MarkList.Draw();

Find <br>

    void ZEffectManager::Update(float fElapsed)

Replace <br>

    void ZEffectManager::Update(float fElapsed)
    {
      m_LightFragments.Update(fElapsed);
      for(int i=0;i<BILLBOARDLISTS_COUNT;i++)
        m_BillboardLists[i].Update(fElapsed);
      //Paintball update
      m_PaintballMarkList.Update(fElapsed);
      m_Paintball2MarkList.Update(fElapsed);
      m_Paintball3MarkList.Update(fElapsed);
      m_Paintball4MarkList.Update(fElapsed);
      m_Paintball5MarkList.Update(fElapsed);
      m_Paintball6MarkList.Update(fElapsed);
      m_Paintball7MarkList.Update(fElapsed);

      m_BulletMarkList.Update(fElapsed);

      for(int i=0;i<BILLBOARDTEXANILIST_COUNT;i++)
        m_BillBoardTexAniList[i].Update(fElapsed);

      m_ShadowList.Update(fElapsed);
    }

Find <br>

    void ZEffectManager::AddBulletMark(rvector& Target, rvector& TargetNormal)

Replace <br>

    void ZEffectManager::AddBulletMark(rvector& Target, rvector& TargetNormal)
    {
      if(g_nEffectLevel > Z_VIDEO_EFFECT_NORMAL) return; // ÇÏ±ÞÀº »ý·«~

      //Check for paintball mode
      if ((ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_PAINTBALL_SOLO) ||
        (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_PAINTBALL_TEAM)) {

        switch (rand() % 7 + 1) { //edit 7 to increase paintball count
        case 1:
        {
              m_PaintballMarkList.Add(Target + TargetNormal, TargetNormal);
              int nBulletCount = 0;
        }
          break;
        case 2:
        {
              m_Paintball2MarkList.Add(Target + TargetNormal, TargetNormal);
              int nBulletCount = 0;
        }
          break;
        case 3:
        {
              m_Paintball3MarkList.Add(Target + TargetNormal, TargetNormal);
              int nBulletCount = 0;
        }
        case 4:
        {
              m_Paintball4MarkList.Add(Target + TargetNormal, TargetNormal);
              int nBulletCount = 0;
        }
          break;
        case 5:
        {
              m_Paintball5MarkList.Add(Target + TargetNormal, TargetNormal);
              int nBulletCount = 0;
        }
          break;
        case 6:
        {
              m_Paintball6MarkList.Add(Target + TargetNormal, TargetNormal);
              int nBulletCount = 0;
        }
          break;
        case 7:
        {
              m_Paintball7MarkList.Add(Target + TargetNormal, TargetNormal);
              int nBulletCount = 0;
        }
          break;
        }
        if (rand() % 1)
          m_BulletMarkList.Add(Target + TargetNormal, TargetNormal);
      }
      else {
        m_BulletMarkList.Add(Target + TargetNormal, TargetNormal);
      }

      ZEffect* pNew = NULL;
      pNew = new ZEffectSlash(m_pBulletOnWallEffect[rand()%BULLETONWALL_COUNT],Target,TargetNormal);
      ((ZEffectSlash*)pNew)->SetAlignType(1);
      Add(pNew);
    }

Open(ZGameInterface.cpp) <br>
Find <br>

	ZGetGameTypeManager()->SetGameTypeStr( MMATCH_GAMETYPE_DEATHMATCH_SOLO, ZMsg( MSG_MT_DEATHMATCH_SOLO));

Add under <br>

	ZGetGameTypeManager()->SetGameTypeStr( MMATCH_GAMETYPE_PAINTBALL_SOLO, "Paintball Solo");
	ZGetGameTypeManager()->SetGameTypeStr( MMATCH_GAMETYPE_PAINTBALL_TEAM, "Paintball Team");

Open(ZRule.cpp) <br>
Find <br>

	case MMATCH_GAMETYPE_DUEL:
		{
			return (new ZRuleDuel(pMatch));
		}
		break;

Add under <br>

	case MMATCH_GAMETYPE_PAINTBALL_SOLO:
	{
		return (new ZRuleSoloPaintball(pMatch));
	}
	break;
	case MMATCH_GAMETYPE_PAINTBALL_TEAM:
	{
		return (new ZRuleTeamPaintball(pMatch));
	}
	break;

Open(ZStageInterface.cpp) <br>
Find <br>

    case MMATCH_GAMETYPE_DEATHMATCH_SOLO:

Add under <br>

		case MMATCH_GAMETYPE_PAINTBALL_SOLO:

Find <br>

    case MMATCH_GAMETYPE_DEATHMATCH_TEAM:

Add under <br>

    case MMATCH_GAMETYPE_PAINTBALL_TEAM:

Find <br>

    MAnimation* pAniMapImg = (MAnimation*)pResource->FindWidget( "Stage_MapNameBG");

Add under <br>

    (pSetting->nGameType == MMATCH_GAMETYPE_PAINTBALL_SOLO) ||

Find <br>

    else if ((pSetting->nGameType == MMATCH_GAMETYPE_DEATHMATCH_TEAM) ||

Add under <br>

    (pSetting->nGameType == MMATCH_GAMETYPE_PAINTBALL_TEAM) ||

Open(MMatchRuleDeathMatch.h)  <br>
Find <br>

    class MMatchRuleTeamDeath2 : public MMatchRule {

Add under <br>

    class MMatchRuleSoloPaintball : public MMatchRuleSoloDeath {
    public:
      MMatchRuleSoloPaintball(MMatchStage* pStage);
      virtual ~MMatchRuleSoloPaintball() { }
      virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_PAINTBALL_SOLO; }
    };

    class MMatchRuleTeamPaintball : public MMatchRuleTeamDeath {
    public:
      MMatchRuleTeamPaintball(MMatchStage* pStage);
      virtual ~MMatchRuleTeamPaintball() {}
      virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_PAINTBALL_TEAM; }
    };

Open(MMatchRuleDeathMatch.cpp) <br>
Find <br>

    void MMatchRuleTeamDeath2::OnGameKill(const MUID& uidAttacker, const MUID& uidVictim)

Add under <br>

    MMatchRuleSoloPaintball::MMatchRuleSoloPaintball(MMatchStage* pStage) : MMatchRuleSoloDeath(pStage)
    {
    }

    MMatchRuleTeamPaintball::MMatchRuleTeamPaintball(MMatchStage* pStage) : MMatchRuleTeamDeath(pStage)
    {
    }

Open(ZEffectManager.h) <br>
Find <br>

	RMeshMgr* m_pEffectMeshMgr;

Add under <br>

	//Paintball declaration
	ZEffectBulletMarkList        m_PaintballMarkList;
	ZEffectBulletMarkList        m_Paintball2MarkList;
	ZEffectBulletMarkList        m_Paintball3MarkList;
	ZEffectBulletMarkList        m_Paintball4MarkList;
	ZEffectBulletMarkList        m_Paintball5MarkList;
	ZEffectBulletMarkList        m_Paintball6MarkList;
	ZEffectBulletMarkList        m_Paintball7MarkList;

Open(MBaseGameType.h) <br>
Find <br>

	inline bool MBaseGameTypeCatalogue::IsTeamExtremeGame(MMATCH_GAMETYPE nGameType)

Add under <br>

	inline bool IsGameRulePaintballTeam(MMATCH_GAMETYPE nGameType)
	{
		return (nGameType == MMATCH_GAMETYPE_PAINTBALL_TEAM);
	}

	inline bool IsGameRulePaintballSolo(MMATCH_GAMETYPE nGameType)
	{
		return (nGameType == MMATCH_GAMETYPE_PAINTBALL_SOLO);
	}

Open(ZRuleDeathMatch.cpp) <br>
Find <br>

	ZRuleTeamDeathMatch::ZRuleTeamDeathMatch(ZMatch* pMatch) : ZRule(pMatch)

Add under <br>

	ZRuleSoloPaintball::ZRuleSoloPaintball(ZMatch* pMatch) : ZRuleSoloDeathMatch(pMatch)
	{
	}

	ZRuleSoloPaintball::~ZRuleSoloPaintball()
	{
	}
	ZRuleTeamPaintball::ZRuleTeamPaintball(ZMatch* pMatch) : ZRuleTeamDeathMatch(pMatch)
	{
	}

	ZRuleTeamPaintball::~ZRuleTeamPaintball()
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

Add under <br>


	class ZRuleSoloPaintball : public ZRuleSoloDeathMatch
	{
	public:
		ZRuleSoloPaintball(ZMatch* pMatch);
		virtual ~ZRuleSoloPaintball();
	};


	class ZRuleTeamPaintball : public ZRuleTeamDeathMatch
	{
	public:
		ZRuleTeamPaintball(ZMatch* pMatch);
		virtual ~ZRuleTeamPaintball();
	};
































