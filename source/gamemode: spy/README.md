Open(MBaseGameType.h) <br>
Find <br>

    enum MMATCH_GAMETYPE {

Add <br>

	MMATCH_GAMETYPE_SPY					=21,

Find <br>

    inline bool MBaseGameTypeCatalogue::IsTeamGame(MMATCH_GAMETYPE nGameType)
    {


Add <br>

    (nGameType == MMATCH_GAMETYPE_SPY) ||

Find <br>

    inline bool MBaseGameTypeCatalogue::IsTeamLimitTime(MMATCH_GAMETYPE nGameType)
    {

Add <br>

    (nGameType == MMATCH_GAMETYPE_SPY) ||

Find <br>

    inline bool MBaseGameTypeCatalogue::IsWaitForRoundEnd(MMATCH_GAMETYPE nGameType)
    {

Add <br>

    (nGameType == MMATCH_GAMETYPE_SPY) ||

Open(MBaseGameType.cpp) <br>
Find <br>

    #define MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR		"Death Match(Solo)"

Add <br>

    #define MMATCH_GAMETYPE_SPY_STR					"Spy Mode"

Find <br>

    _InitGameType(MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR,  1.0f,			1.0f,					0.0f);

Add <br>

    _InitGameType(MMATCH_GAMETYPE_SPY, MMATCH_GAMETYPE_SPY, MMATCH_GAMETYPE_SPY_STR, 1.0f, 0.8f, 0.3f);

Open(MMatchRule.cpp) <br>
Find <br>

    case MMATCH_ROUNDSTATE_COUNTDOWN:

Replace <br>

	case MMATCH_ROUNDSTATE_COUNTDOWN:
	{
		unsigned long int nCountdownTime = 1000 * 2;	// Default : countdown for 2 sec.

		if (GetGameType() == MMATCH_GAMETYPE_SPY)
			nCountdownTime = MSPYMODE_ROUNDSTATE_COUNTDOWN_TIME;	// Spy : for 10 sec.

		// if (nClock - GetRoundStateTimer() > 2*1000) {
		if (nClock - GetRoundStateTimer() > nCountdownTime) {
			SetRoundState(MMATCH_ROUNDSTATE_PLAY);
			return true;
		}
		else {
			// Countdown proceeding now, Do Nothing..
			return true;
		}

	}
	break;

Open(MMatchServer_Item.cpp) <br>
Find <br>

    void MMatchServer::OnRequestUseSpendableNormalItem(const MUID& uidPlayer, const MUID& uidItem)
    {

Replace <br>

    void MMatchServer::OnRequestUseSpendableNormalItem(const MUID& uidPlayer, const MUID& uidItem)
    {
      MMatchObject* pObj = GetObject(uidPlayer);
      if (pObj == NULL) return;

      MMatchStage* pStage = FindStage(pObj->GetStageUID());
      if (pStage != NULL)
      {
        if (pStage->GetStageSetting()->GetGameType() == MMATCH_GAMETYPE_SPY)
          return;
      }

      MMatchCharInfo* pCharInfo = pObj->GetCharInfo();
      if (pCharInfo == NULL) return;

      MMatchItem *pItem = pCharInfo->m_ItemList.GetItem(uidItem);	///< UID·Î ¾ÆÀÌÅÛ Ã£±â
      if( pItem == NULL ) {
        mlog("Use Spendable Item Failed[CID : %d, MUID(%d%d)]\n", pCharInfo->m_nCID, uidItem.High, uidItem.Low);
        return;
      }

      if( pItem->GetDesc()->IsSpendableItem() ) 
      { 
        UseSpendableItem(uidPlayer, uidItem);	
      }	
    }

Open(MMatchServer_Stage.cpp) <br>
Find <br>

    bool MMatchServer::StageEnterBattle(const MUID& uidPlayer, const MUID& uidStage)
    {

Replace <br>

    bool MMatchServer::StageEnterBattle(const MUID& uidPlayer, const MUID& uidStage)
    {
      MMatchObject* pObj = GetObject(uidPlayer);
      if (!IsEnabledObject(pObj)) return false;

      if (pObj->GetStageUID() != uidStage)
        mlog(" stage enter battle hack %s (%d, %d) ignore\n", pObj->GetName(), uidPlayer.High, uidPlayer.Low);

      MMatchStage* pStage = FindStage(pObj->GetStageUID());
      if (pStage == NULL) return false;

      pObj->SetPlace(MMP_BATTLE);

      for (MUIDRefCache::iterator itor = pStage->GetObjBegin(); itor != pStage->GetObjEnd(); itor++)
      {
        MMatchObject *pPeer = reinterpret_cast<MMatchObject *>(itor->second);

        MCommand *pNew = CreateCommand(MC_MATCH_STAGE_ENTERBATTLE, MUID(0, 0));

        unsigned char nParam = MCEP_NORMAL;
        if (pObj->IsForcedEntried()) nParam = MCEP_FORCED;
        pNew->AddParameter(new MCommandParameterUChar(nParam));

        void *pPeerArray = MMakeBlobArray(sizeof(MTD_PeerListNode), 1);
        MTD_PeerListNode *pNode = (MTD_PeerListNode*)MGetBlobArrayElement(pPeerArray, 0);
        memset(pNode, 0, sizeof(MTD_PeerListNode));

        pNode->uidChar = pObj->GetUID();
        pNode->dwIP = pObj->GetIP();
        pNode->nPort = pObj->GetPort();

        CopyCharInfoForTrans(&pNode->CharInfo, pObj->GetCharInfo(), pObj);
        pNode->ExtendInfo.nPlayerFlags = pObj->GetPlayerFlags();

        if (pStage->GetStageSetting()->GetGameType() == MMATCH_GAMETYPE_SPY)
        {
          pStage->PlayerTeam(uidPlayer, MMT_BLUE);
          pNode->ExtendInfo.nTeam = (char)MMT_BLUE;
        }
        else if (pStage->GetStageSetting()->IsTeamPlay())
        {
          pNode->ExtendInfo.nTeam = (char)pObj->GetTeam();
        }
        else
        {
          pNode->ExtendInfo.nTeam = 0;
        }

        pNew->AddParameter(new MCommandParameterBlob(pPeerArray, MGetBlobArraySize(pPeerArray)));
        MEraseBlobArray(pPeerArray);

        RouteToListener(pPeer, pNew);
      }

      pObj->GetCharInfo()->m_nBattleStartTime = MMatchServer::GetInstance()->GetGlobalClockCount();
      pObj->GetCharInfo()->m_nBattleStartXP = pObj->GetCharInfo()->m_nXP;

      return ExceptionTraceStageEnterBattle(pObj, pStage);
    }

Find <br>

    void MMatchServer::OnRequestSpawn(const MUID& uidChar, const MVector& pos, const MVector& dir)
    {
  
  
Replace <br>

    void MMatchServer::OnRequestSpawn(const MUID& uidChar, const MVector& pos, const MVector& dir)
    {
      MMatchObject* pObj = GetObject(uidChar);
      if (pObj == NULL) return;

      // Do Not Spawn when AdminHiding
      if (IsAdminGrade(pObj) && pObj->CheckPlayerFlags(MTD_PlayerFlags_AdminHide)) return;


      // ¸¶Áö¸· Á×¾ú´ø ½Ã°£°ú »õ·Î ¸®½ºÆùÀ» ¿äÃ»ÇÑ ½Ã°£ »çÀÌ¿¡ 2ÃÊ ÀÌ»óÀÇ ½Ã°£ÀÌ ÀÖ¾ú´ÂÁö °Ë»çÇÑ´Ù.
      DWORD dwTime = timeGetTime() - pObj->GetLastSpawnTime();	
      if ( dwTime < RESPAWN_DELAYTIME_AFTER_DYING_MIN) return;
      pObj->SetLastSpawnTime(timeGetTime());

      MMatchStage* pStage = FindStage(pObj->GetStageUID());
      if (pStage == NULL) return;
      if ( (pStage->GetRule()->GetRoundState() != MMATCH_ROUNDSTATE_PREPARE) && (!pObj->IsEnabledRespawnDeathTime(GetTickTime())) )
         return;

      MMatchRule* pRule = pStage->GetRule();					// ÀÌ·± ½ÄÀÇ ÄÚµå´Â ¸¶À½¿¡ ¾ÈµéÁö¸¸ -_-; °ÔÀÓÅ¸ÀÔ º¸°í ¿¹¿ÜÃ³¸®.
      MMATCH_GAMETYPE gameType = pRule->GetGameType();		// ´Ù¸¥ ¹æ¹ý ÀÖ³ª¿ä.
      if (gameType == MMATCH_GAMETYPE_DUEL)
      {
        MMatchRuleDuel* pDuel = (MMatchRuleDuel*)pRule;		// RTTI ¾È½á¼­ dynamic cast´Â ÆÐ½º.. ¿¹¿ÜÃ³¸®µµ Â¥Áõ³ª°í -,.-
        if (uidChar != pDuel->uidChampion && uidChar != pDuel->uidChallenger)
        {
          OnDuelSetObserver(uidChar);
          return;
        }
      }

      else if (gameType == MMATCH_GAMETYPE_SPY)
      {
        MMatchRuleSpy* pSpy = (MMatchRuleSpy*)pRule;
        if (!pSpy->IsParticipant(uidChar))
        {
          OnDuelSetObserver(uidChar);
          return;
        }
      }

      pObj->ResetCustomItemUseCount();
      pObj->SetAlive(true);

      MCommand* pCmd = CreateCommand(MC_MATCH_GAME_RESPONSE_SPAWN, MUID(0,0));
      pCmd->AddParameter(new MCmdParamUID(uidChar));
      pCmd->AddParameter(new MCmdParamShortVector(pos.x, pos.y, pos.z));
      pCmd->AddParameter(new MCmdParamShortVector(DirElementToShort(dir.x), DirElementToShort(dir.y), DirElementToShort(dir.z)));
      RouteToBattle(pObj->GetStageUID(), pCmd);
    }

Find <br>

    void MMatchServer::OnRequestSpawnWorldItem(const MUID& uidPlayer, const int nItemID, const float x, const float y, const float z, float fDropDelayTime)
    {

Replace <br>

    void MMatchServer::OnRequestSpawnWorldItem(const MUID& uidPlayer, const int nItemID, const float x, const float y, const float z, float fDropDelayTime)
    {
      MMatchObject* pObj = GetObject(uidPlayer);
      if (pObj == NULL) return;
      MMatchStage* pStage = FindStage(pObj->GetStageUID());
      if (pStage == NULL) return;

      if (pStage->GetStageSetting()->GetGameType() == MMATCH_GAMETYPE_SPY && nItemID == MSPYMODE_WORLDITEM_LANDMINE_ID)
      {
        pStage->RequestSpawnWorldItem(pObj, nItemID, x, y, z, fDropDelayTime);
        return;
      }

      if( !pObj->IsHaveCustomItem() )
        return;

      if( pObj->IncreaseCustomItemUseCount() )
      {
        pStage->RequestSpawnWorldItem(pObj, nItemID, x, y, z, fDropDelayTime);
      }
    }

Open(MMatchStage.cpp) <br>
Find <br>

    void MMatchStage::EnterBattle(MMatchObject* pObj)
    {

Add <br>

    void MMatchStage::EnterBattle(MMatchObject* pObj)
    {
      pObj->OnEnterBattle();

      if (GetState() == STAGE_STATE_RUN)
      {
        if (pObj->IsForcedEntried())
        {
          if (m_StageSetting.IsWaitforRoundEnd())
          {
            pObj->SetAlive(false);
          }

          // ¿ùµå¾ÆÀÌÅÛ Á¤º¸¸¦ º¸³»ÁØ´Ù
          m_WorldItemManager.RouteAllItems(pObj);
          m_ActiveTrapManager.RouteAllTraps(pObj);

          if (m_StageSetting.GetGameType() == MMATCH_GAMETYPE_SPY && m_StageSetting.GetGameType() == MMATCH_GAMETYPE_DROPMAGIC)
          {
            if (m_pRule)
              ((MMatchRuleSpy*)m_pRule)->SendGameInfo();
          }

          // ³­ÀÔÀÚ¿¡°Ô ¹æ»óÅÂ¸¦ Àü¼ÛÇÑ´Ù.
          MMatchServer::GetInstance()->ResponseRoundState(pObj, GetUID());
        }

        if (m_pRule)
        {
          MUID uidChar = pObj->GetUID();
          m_pRule->OnEnterBattle(uidChar);
        }
      }

      // ¹æ¿¡ µé¾î°¬À¸¸é ³­ÀÔÇß´ÂÁö ¿©ºÎ´Â ´Ù½Ã false·Î ÃÊ±âÈ­
      pObj->SetForcedEntry(false);
      pObj->ResetCustomItemUseCount();

      RequestResourceCRC32Cache( pObj->GetUID() );
    }

Find <br>

	case MMATCH_GAMETYPE_DEATHMATCH_SOLO:
		{
			return (new MMatchRuleSoloDeath(this));
		}
		break;

Add <br>

	case MMATCH_GAMETYPE_SPY:
	{
		return (new MMatchRuleSpy(this));
	}
	break;

Open(ZCharacter.cpp) <br>
Find <br>

    #define EXCELLENT_TIME	3.0f
      ZCharacter *pLastAttacker = ZGetCharacterManager()->Find(GetLastAttacker());
      if (pLastAttacker && pLastAttacker != this)
      {
        if (ZGetGame()->GetTime() - pLastAttacker->m_killInfo.Ref().m_fLastKillTime < EXCELLENT_TIME
          && ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_DUEL

Replace <br>

    #define EXCELLENT_TIME	3.0f
      ZCharacter *pLastAttacker = ZGetCharacterManager()->Find(GetLastAttacker());
      if (pLastAttacker && pLastAttacker != this)
      {
        if (ZGetGame()->GetTime() - pLastAttacker->m_killInfo.Ref().m_fLastKillTime < EXCELLENT_TIME
          && ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_DUEL
          && ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_DUELTOURNAMENT
          && ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_SPY)
        {
          MEMBER_SET_CHECKCRC(pLastAttacker->GetStatus(), nExcellent, pLastAttacker->GetStatus().Ref().nExcellent + 1)
            pLastAttacker->AddIcon(ZCI_EXCELLENT);
        }

Find <br>

		MEMBER_SET_CHECKCRC(pLastAttacker->m_killInfo, m_fLastKillTime, ZGetGame()->GetTime());

		// fantastic ÆÇÁ¤
		if(!uStatus.m_bLand && GetDistToFloor()>200.f && ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_DUEL
			&& ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_DUELTOURNAMENT)
		{
			MEMBER_SET_CHECKCRC(pLastAttacker->GetStatus(), nFantastic, pLastAttacker->GetStatus().Ref().nFantastic+1)
			pLastAttacker->AddIcon(ZCI_FANTASTIC);
		}


Replace <br>

		MEMBER_SET_CHECKCRC(pLastAttacker->m_killInfo, m_fLastKillTime, ZGetGame()->GetTime());

		if (!uStatus.m_bLand && GetDistToFloor() > 200.f && ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_DUEL
			&& ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_DUELTOURNAMENT
			&& ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_SPY)
		{
			MEMBER_SET_CHECKCRC(pLastAttacker->GetStatus(), nFantastic, pLastAttacker->GetStatus().Ref().nFantastic + 1)
				pLastAttacker->AddIcon(ZCI_FANTASTIC);
		}

Find <br>

		// unbelievable ÆÇÁ¤
		if(pLastAttacker && ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_DUEL
			&& ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_DUELTOURNAMENT)
		{
			m_killInfo.CheckCrc();
			ZCharacter::KillInfo& lastAttackerKillInfo = m_killInfo.Ref();
			lastAttackerKillInfo.m_nKillsThisRound++;
			if(lastAttackerKillInfo.m_nKillsThisRound==3)
				MEMBER_SET_CHECKCRC(pLastAttacker->GetStatus(), nUnbelievable, pLastAttacker->GetStatus().Ref().nUnbelievable+1);
			if(lastAttackerKillInfo.m_nKillsThisRound>=3)
			{
				pLastAttacker->AddIcon(ZCI_UNBELIEVABLE);
			}
			m_killInfo.MakeCrc();
		}

Replace <br>

		if (pLastAttacker && ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_DUEL
			&& ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_DUELTOURNAMENT
			&& ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_SPY)
		{
			m_killInfo.CheckCrc();
			ZCharacter::KillInfo& lastAttackerKillInfo = m_killInfo.Ref();
			lastAttackerKillInfo.m_nKillsThisRound++;
			if (lastAttackerKillInfo.m_nKillsThisRound == 3)
				MEMBER_SET_CHECKCRC(pLastAttacker->GetStatus(), nUnbelievable, pLastAttacker->GetStatus().Ref().nUnbelievable + 1);
			if (lastAttackerKillInfo.m_nKillsThisRound >= 3)
			{
				pLastAttacker->AddIcon(ZCI_UNBELIEVABLE);
			}
			m_killInfo.MakeCrc();
		}


Open(ZCombatInterface.cpp) <br>
Find <br>

	// °ÔÀÓ ³ª°¡±â ¹öÆ°ÀÇ È®ÀÎ ¸Þ½ÃÁö¸¦ °ÔÀÓ·ê¿¡ µû¶ó º¯°æÇÑ´Ù
	MButton* pExitConfirmButton = (MButton*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("StageExit");
	if (pExitConfirmButton) {
		char szConfirmMsg[256];
		if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_DUELTOURNAMENT)
		{
			ZTransMsg(szConfirmMsg, MSG_GAME_DUELTOURNAMENT_MATCH_EXITSTAGE_CONFIRM);
			pExitConfirmButton->SetAlterableConfirmMessage(szConfirmMsg);
		}
		else
		{
			pExitConfirmButton->RestoreIDLConfirmMessage();
		}
	}

Add under <br>

	if (ZGetGame())
	{
		if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_SPY)
		{
			m_pSpyIcon = new MBitmapR2;
			m_pSpyIcon->Create("icon_spy.tga", RGetDevice(), "interface/default/icon_spy.tga");

			OnSpyCreate();
		}
	}

Find <br>

	if (ZGetCamera()->GetLookMode() == ZCAMERA_FREELOOK || bDrawAllPlayerName)
		DrawAllPlayerName(pDC);
	else
	{
		if(!ZGetGameInterface()->IsMiniMapEnable()) 
		{
			DrawFriendName(pDC);
			DrawEnemyName(pDC);
		}
	}


Replace <br>

	if (ZGetCamera()->GetLookMode() == ZCAMERA_FREELOOK || bDrawAllPlayerName)
		DrawAllPlayerName(pDC);
	else
	{
		if (!ZGetGameInterface()->IsMiniMapEnable())
		{
			if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_SPY)
				DrawSpyName(pDC);
			else
				DrawFriendName(pDC);

			DrawEnemyName(pDC);
		}
	}

Find <br>

	// µ¿¿µ»ó Ä¸ÃÄ...2008.10.20
	if (ZGetGameInterface()->GetBandiCapturer() != NULL)
		ZGetGameInterface()->GetBandiCapturer()->DrawCapture(pDC);
	
Add under <br>

		if (ZGetGame() && ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_SPY)
			OnSpyDraw(pDC);

Find <br>

	if ((pCharacter->GetItems()->GetSelectedWeaponParts() == MMCIP_MELEE) || (pSItem->GetDesc()->m_nWeaponType.Ref() == MWT_SNIFER) && (m_bSniferMode == false)) {
		ShowCrossHair(false);
	}
	else {
		ShowCrossHair(true);
	}

	GameCheckPickCharacter();

Add under <br>

	if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_SPY)
		OnSpyUpdate(fElapsed);

Find <br>

				pDC->SetFont(pFont);

				int x = Cp.x - pDC->GetFont()->GetWidth(pPickedCharacter->GetUserName()) / 2;
				pDC->Text(x, Cp.y - pDC->GetFont()->GetHeight()-10, pPickedCharacter->GetUserName());

Replace <br>

					if (pFont == NULL) _ASSERT(0);
					pDC->SetFont(pFont);
					if (pPickedCharacter->IsAdminName())
						pDC->SetColor(CharNameColor);
					int x = Cp.x - pDC->GetFont()->GetWidth(pPickedCharacter->GetUserName()) / 2;
					pDC->Text(x, Cp.y - pDC->GetFont()->GetHeight() - 10, pPickedCharacter->GetUserName());

					if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_SPY &&
						ZGetGame()->GetMatch()->GetRoundState() == MMATCH_ROUNDSTATE_PLAY &&
						pPickedCharacter->GetTeamID() == MMT_RED &&
						!m_bSpyLocationOpened)
					{
						const int nIconWidth = 48, nIconHeight = 48;
						rvector screen_pos = RGetTransformCoord(pPickedCharacter->GetVisualMesh()->GetHeadPosition() + rvector(0, 0, 30.f));

						pDC->SetBitmap((MBitmap*)m_pSpyIcon);
						pDC->Draw(screen_pos.x - nIconWidth / 2, screen_pos.y - nIconHeight / 2 - 34, nIconWidth, nIconHeight);
					}

Find <br>

    ZSCOREBOARDITEMLIST items;

Add under <br>

	bool bSpyOpenCountDown = (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_SPY &&
		(ZGetGame()->GetMatch()->GetRoundState() == MMATCH_ROUNDSTATE_COUNTDOWN || ZGetGame()->GetMatch()->GetRoundState() == MMATCH_ROUNDSTATE_FREE));


Find <br>

	for(i=items.begin();i!=items.end();i++)
	{
		ZScoreBoardItem *pItem=*i;

		if(nCurrentTeamIndex!=pItem->nTeam)	// ÆÀÀÌ ¹Ù²î¸é
		{
			nCurrentTeamIndex=pItem->nTeam;
			nCount = max(nCount,min(8,nMaxLineCount - ((int)items.size()-nCount)));
		}

Replace <br>

	for (i = items.begin(); i != items.end(); i++)
	{
		ZScoreBoardItem *pItem = *i;

		if (nCurrentTeamIndex != pItem->nTeam)
		{
			int nLineSeparate = nMaxLineCount / 2;

			if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_SPY)
				nLineSeparate = 4;

			nCurrentTeamIndex = pItem->nTeam;
			nCount = max(nCount, min(nLineSeparate, nMaxLineCount - ((int)items.size() - nCount)));
		}

Find <br>

		else if ( ZGetGameInterface()->m_bTeamPlay)		// ÆÀÀüÀÌ¸é...
		{

Replace <br>

		else if (ZGetGameInterface()->m_bTeamPlay && ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_SPY)
		{

Find <br>

	if(ZGetGame()->GetMatch()->IsTeamPlay() && !ZGetGameClient()->IsLadderGame())
	{

Replace <br>

	if (ZGetGame()->GetMatch()->IsTeamPlay() && !ZGetGameClient()->IsLadderGame() && ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_SPY)
	{

Find <br>

		strcpy(pItem->szClan,pCharacter->GetProperty()->GetClanName());
		pItem->nClanID = pCharacter->GetClanID();
		pItem->nTeam = ZGetGame()->GetMatch()->IsTeamPlay() ? pCharacter->GetTeamID() : MMT_END;
		pItem->nScore = pCharacter->GetStatus().Ref().nExp;
		pItem->nKills = pCharacter->GetStatus().Ref().nKills;
		pItem->nDeaths = pCharacter->GetStatus().Ref().nDeaths;


Replace <br>

		strcpy(pItem->szClan, pCharacter->GetProperty()->GetClanName());
		pItem->nClanID = pCharacter->GetClanID();
		pItem->nTeam = ZGetGame()->GetMatch()->IsTeamPlay() && ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_SPY ? pCharacter->GetTeamID() : MMT_END;
		pItem->nScore = pCharacter->GetStatus().Ref().nExp;
		pItem->nKills = pCharacter->GetStatus().Ref().nKills;
		pItem->nDeaths = pCharacter->GetStatus().Ref().nDeaths;






















