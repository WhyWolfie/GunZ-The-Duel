Open(ZMatch.cpp) <br>
Find <br>

    void ZMatch::InitRound()
    {
        // ½?°£?» 0?¸·?
        ZGetGame()->InitRound();

        InitCharactersPosition();
        InitCharactersProperties();

        // ¿?µ?¾????? ??±??­
        ZGetWorldItemManager()->Reset();

        // ¸? ?³?½ °???½? ½÷??½??²´?.
        rvector pos = ZGetGame()->m_pMyCharacter->GetPosition();
        rvector dir = ZGetGame()->m_pMyCharacter->m_DirectionLower;

        m_nRoundKills = 0;

        bool isObserver = false;

    if (ZApplication::GetInstance()->GetLaunchMode() == ZApplication::ZLAUNCH_MODE_DEBUG) {
    #ifdef _DEBUG
    ZPostSpawn(pos, dir);
    #endif
    } else {
            if (ZGetGame()->GetSpawnRequested() == false) {
                if (GetMatchType() == MMATCH_GAMETYPE_DUEL)
                {
    //                ZRuleDuel* pDuel = (ZRuleDuel*)GetRule();
    //                if (pDuel->GetQueueIdx(ZGetMyUID()) <= 1){
    //                    ZPostRequestSpawn(ZGetMyUID(), pos, dir);
    //                    g_pGame->SetSpawnRequested(true);
    //                } else isObserver = true;
                    for (ZCharacterManager::iterator itor = ZGetGame()->m_CharacterManager.begin();
                        itor != ZGetGame()->m_CharacterManager.end(); ++itor)
                    {
                        ZCharacter* pCharacter = (*itor).second;
                        pCharacter->ForceDie();
                        pCharacter->SetVisible(false);
                    }
                }
                else if(GetMatchType() == MMATCH_GAMETYPE_DUELTOURNAMENT){
                    for (ZCharacterManager::iterator itor = ZGetGame()->m_CharacterManager.begin();
                        itor != ZGetGame()->m_CharacterManager.end(); ++itor)
                    {
                        ZCharacter* pCharacter = (*itor).second;
                        pCharacter->ForceDie();
                        pCharacter->SetVisible(false);
                    }
                }
                else
                {
                    ZPostRequestSpawn(ZGetMyUID(), pos, dir);
                    ZGetGame()->SetSpawnRequested(true);
                }
            }
        }

    //    m_nRoundKills = 0;

        // AdminHide ?³¸®
        MMatchObjCache* pObjCache = ZGetGameClient()->FindObjCache(ZGetMyUID());
        if (pObjCache && pObjCache->CheckFlag(MTD_PlayerFlags_AdminHide)) {
            ZGetGameInterface()->GetCombatInterface()->SetObserverMode(true);
        } else {
            // ¿??®¹? ¸?µ?¿´?¸¸? ???¦.
            if (!isObserver)
                ZGetGame()->ReleaseObserver();
            else
            {
                ZGetGameInterface()->GetCombatInterface()->SetObserverMode(true);
                ZGetGame()->ReserveObserver();
                ZGetGame()->m_pMyCharacter->ForceDie();

            }
        }
        memset(m_nTeamKillCount, 0, sizeof(m_nTeamKillCount));
    }
    
Replace <br>

    void ZMatch::InitRound()
    {
      // ½Ã°£À» 0À¸·Î
      ZGetGame()->InitRound();

      InitCharactersPosition();
      InitCharactersProperties();

      // ¿ùµå¾ÆÀÌÅÛ ÃÊ±âÈ­
      ZGetWorldItemManager()->Reset();

      // ¸Ç Ã³À½ °ÔÀÓ½Ã ½ºÆù½ÃÅ²´Ù.
      rvector pos = ZGetGame()->m_pMyCharacter->GetPosition();
      rvector dir = ZGetGame()->m_pMyCharacter->m_DirectionLower;

      m_nRoundKills = 0;

      bool isObserver = false;

      if (ZGetGame()->GetSpawnRequested() == false) {
        if (GetMatchType() == MMATCH_GAMETYPE_DUEL)
        {
          isObserver = true;
          for (ZCharacterManager::iterator itor = ZGetGame()->m_CharacterManager.begin();
            itor != ZGetGame()->m_CharacterManager.end(); ++itor)
          {
            isObserver = false;
            ZCharacter* pCharacter = (*itor).second;
            pCharacter->ForceDie();
            pCharacter->SetVisible(false);
          }
      }
        else if (GetMatchType() == MMATCH_GAMETYPE_DUELTOURNAMENT){
          isObserver = true;
          for (ZCharacterManager::iterator itor = ZGetGame()->m_CharacterManager.begin();
            itor != ZGetGame()->m_CharacterManager.end(); ++itor)
          {
            isObserver = false;
            ZCharacter* pCharacter = (*itor).second;
            pCharacter->ForceDie();
            pCharacter->SetVisible(false);
          }
        }
        else
        {
          isObserver = false;
          ZPostRequestSpawn(ZGetMyUID(), pos, dir);
          ZGetGame()->SetSpawnRequested(true);
        }
    }

      //	m_nRoundKills = 0;

      // AdminHide Ã³¸®
      MMatchObjCache* pObjCache = ZGetGameClient()->FindObjCache(ZGetMyUID());
      if (pObjCache && pObjCache->CheckFlag(MTD_PlayerFlags_AdminHide)) {
        ZGetGameInterface()->GetCombatInterface()->SetObserverMode(true);
      }
      else {
        // ¿ÉÁ®¹ö ¸ðµå¿´À¸¸é ÇØÁ¦.
        if (!isObserver)
          ZGetGame()->ReleaseObserver();
        else
        {
          ZGetGameInterface()->GetCombatInterface()->SetObserverMode(true);
          ZGetGame()->ReserveObserver();
          ZGetGame()->m_pMyCharacter->ForceDie();

        }
      }
      memset(m_nTeamKillCount, 0, sizeof(m_nTeamKillCount));
    }
