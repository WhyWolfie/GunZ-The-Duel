<b>Snowtown Particle System</b><br>
MMFeatureDefine.h

    #define _XMASJORK2 1
    
    
in ZCharacter.cpp line "void ZCharacter::InitProperties()" add


        #ifdef _XMASJORK2
          if ((ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_DEATHMATCH_SOLO) ||
            (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_QUEST ||
            ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_TRAINING ||
            ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_GLADIATOR_SOLO ||
            ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_SURVIVAL ||
            ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_BERSERKER ||
            ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_PAINTBALL_SOLO ||
            ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_CLASSIC_SOLO ||
            ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_MODE_STAFF))//Xmas
          {

            if (GetProperty()->nSex == MMS_FEMALE){
              m_Items.EquipItem(MMCIP_HEAD, 520513);
            }
            else{
              m_Items.EquipItem(MMCIP_HEAD, 520013);
            }
            m_Items.EquipItem(MMCIP_FINGERL, 525005);
          }
        #endif


in ZGame.cpp line "class ZSnowTownParticleSystem" remplace for these:

    class ZSnowTownParticleSystem
    {
    private:
      RParticles*		m_pParticles[5];
      bool IsSnowTownMap()
      {
    #ifdef _XMASJORK2
        if ((ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_MAX, 4)) return true;//Xmas
    #else
        if (!strnicmp(ZGetGameClient()->GetMatchStageSetting()->GetMapName(), "snow", 4)) return true;
    #endif
        return false;
      }
    public:
      void Update(float fDeltaTime)
      {
        if (!IsSnowTownMap()) return;

    #define SNOW_PARTICLE_COUNT_PER_SECOND		600		// ´ë·« ÃÊ´ç 300°³Âë ¿ø·¡ ÇÁ·¹ÀÓ´ç 14°³¿´À½.

        int nSnowParticleCountPerSec = SNOW_PARTICLE_COUNT_PER_SECOND;
        switch (ZGetConfiguration()->GetVideo()->nEffectLevel)
        {
        case Z_VIDEO_EFFECT_HIGH:	break;
        case Z_VIDEO_EFFECT_NORMAL:	nSnowParticleCountPerSec = nSnowParticleCountPerSec / 8; break;
        case Z_VIDEO_EFFECT_LOW:	nSnowParticleCountPerSec = nSnowParticleCountPerSec / 12; break;
        default: nSnowParticleCountPerSec = 0; break;
        }

        int nCount = min(nSnowParticleCountPerSec * fDeltaTime,20);	// ÇÑ¹ø¿¡ 20°³ ÀÌ»óÀº ¾È³ª¿Àµµ·ÏÇÑ´Ù
        for(int i=0;i<nCount;i++)
        {
          RParticle *pp=new RSnowParticle();
          pp->ftime=0;
          pp->position = rvector(RandomNumber(-8000.0f, 8000.0f), RandomNumber(-8000.0f, 8000.0f), 1500.0f);
          pp->velocity = rvector(RandomNumber(-40.0f, 40.0f), RandomNumber(-40.0f, 40.0f), RandomNumber(-150.0f, -250.0f));
          pp->accel=rvector(0,0,-5.f);

          int particle_index = RandomNumber(0, 2);
          if (m_pParticles[particle_index]) m_pParticles[particle_index]->push_back(pp);
        }
      }
      void Create()
      {
        if (!IsSnowTownMap()) return;

        for (int i = 0; i < 3; i++)
        {
          m_pParticles[i] = NULL;
        }

        // ÆÄÆ¼Å¬ »ý¼º
        m_pParticles[0] = RGetParticleSystem()->AddParticles("sfx/water_now.bmp", 25.0f);
        m_pParticles[1] = RGetParticleSystem()->AddParticles("sfx/water_splash.bmp", 20.0f);
        m_pParticles[2] = RGetParticleSystem()->AddParticles("sfx/water_now.bmp", 15.0f);
        m_pParticles[3] = RGetParticleSystem()->AddParticles("sfx/water_splash.bmp", 5.0f);
        m_pParticles[4] = RGetParticleSystem()->AddParticles("sfx/water_now.bmp", 5.0f);
      }
      void Destroy()
      {
        if (!IsSnowTownMap()) return;

        m_pParticles[0]->Clear();
        m_pParticles[1]->Clear();
        m_pParticles[2]->Clear();
      }
    };



in ZWorld.cpp in line "bool ZWorld::Create(ZLoadingProgress *pLoading )" add these

    #ifdef _XMASJORK2
      if ((ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_DEATHMATCH_SOLO) || 
        (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_QUEST || 
        ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_TRAINING || 
        ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_GLADIATOR_SOLO || 
        ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_SURVIVAL || 
        ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_BERSERKER || 
        ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_PAINTBALL_SOLO ||
        ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_VAMPIRE ||
        ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_CLASSIC_SOLO ||
        ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_MODE_STAFF))//Xmas
    #else
      if ((ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_VAMPIRE))
    #endif
      {
        m_bFog = true;
        m_fFogNear = 0.0f;
        m_fFogFar = 6000.0f;
    #ifdef _XMASJORK2
        m_dwFogColor = 0xCCF1FF;
    #else
        m_dwFogColor = 0xC30404;
    #endif
      }
      else
      {
        FogInfo finfo = GetBsp()->GetFogInfo();
        m_bFog = finfo.bFogEnable;
        m_fFogNear = finfo.fNear;
        m_fFogFar = finfo.fFar;
        m_dwFogColor = finfo.dwFogColor;
      }

      m_bCreated = true;




















    
