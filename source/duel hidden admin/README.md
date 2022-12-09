Open(MMatchRuleDuel.cpp) <br>
Find <br>

    void MMatchRuleDuel::OnBegin()

Replace <br>

    void MMatchRuleDuel::OnBegin()
    {
      uidChampion = MUID(0, 0);
      uidChallenger = MUID(0, 0);

      MMatchStage* pStage = GetStage();

      WaitQueue.clear();	// ´ë±â Å¥¸¦ ºñ¿ì°í

      if (pStage != NULL)
      {
        for(MUIDRefCache::iterator itor=pStage->GetObjBegin(); itor!=pStage->GetObjEnd(); itor++) 
        {
          MMatchObject* pItorObj = (MMatchObject*)(*itor).second;

          //Hide GM from Duel Queue
          if( pItorObj && IsAdminGrade( pItorObj ) && pItorObj->CheckPlayerFlags( MTD_PlayerFlags_AdminHide ) )
            continue;

          WaitQueue.push_back((*itor).first);			// ÇÃ·¹ÀÌ¾îµé ±×³É ¸ù¶¥ ´ë±â Å¥¿¡ ³Ö´Â´Ù.
        }

    //		SpawnPlayers();
      }

      nVictory = 0;

      return;
    }

Find <br>

    void MMatchRuleDuel::OnRoundBegin()

Replace <br>

    void MMatchRuleDuel::OnRoundBegin()
    {
      isRoundEnd = false;
      isTimeover = true;

      SpawnPlayers();
      SendQueueInfo(true);
      // ¿Ö±×·±Áö ¸ô¶óµµ ¿ÉÀú¹ö ÇØ¾ß ÇÒ ³ðÀÌ ½ºÆùµÈ°É ºÁ¼­ -_- Á×¿©¹ö¸°´Ù. ¼­¹ö¿¡¼± ½ºÆù¾ÈµÆÀ¸´Ï ´õÀÌ»óÀÇ Ã³¸®´Â ÇÊ¿ä¾øÀ»µí.
      // ÀÌ°Å ÇÑ ÈÄ¿¡ ½ºÆùµÇ´Â°Å¸é ³¶ÆÒµ¥;
      for (list<MUID>::iterator i = WaitQueue.begin(); i!=WaitQueue.end();  ++i)
        MMatchServer::GetInstance()->OnDuelSetObserver(*i);							

      //Set observer for hidden GMs
      for (MUIDRefCache::iterator i=m_pStage->GetObjBegin(); i!=m_pStage->GetObjEnd(); i++) 
      {
        MMatchObject* pObj = (MMatchObject*)(*i).second;
        if (pObj->GetEnterBattle() == false) continue;

        if( IsAdminGrade( pObj ) && pObj->CheckPlayerFlags( MTD_PlayerFlags_AdminHide ) )
        {
          MUID uid = (*i).first;
          MMatchServer::GetInstance()->OnDuelSetObserver( uid );
        }
      }
    }

Find <br>

    void MMatchRuleDuel::OnEnterBattle(MUID& uidChar)


Replace <br>

    void MMatchRuleDuel::OnEnterBattle(MUID& uidChar)
    {
      MMatchObject* pJoiner = m_pStage->GetObj( uidChar );

      //Don't add hidden GM to duel queue.
      if( pJoiner && IsAdminGrade(pJoiner) && pJoiner->CheckPlayerFlags( MTD_PlayerFlags_AdminHide ) )
      {
        SendQueueInfo();
        LogInfo();
        return;
      }

      if ((uidChar != uidChampion) && (uidChar != uidChallenger) && (find(WaitQueue.begin(), WaitQueue.end(), uidChar) == WaitQueue.end()))
      {
        WaitQueue.push_back(uidChar);
        SpawnPlayers();
      }
      SendQueueInfo();
      LogInfo();
    }

















