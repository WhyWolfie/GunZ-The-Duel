Gamemode: Spymode <br>
CSCommon/Spymode files <br>

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



Open(ZGame.cpp) <br>
Find <br>

	void ZGame::OnChangeWeapon(MUID& uid, MMatchCharItemParts parts)
	{
		ZCharacter* pCharacter = m_CharacterManager.Find(uid);
	//	if (uid == ZGetGameClient()->GetUID()) pCharacter = m_pMyCharacter;
	//	_ASSERT(pCharacter != NULL);

		if (pCharacter && pCharacter!=m_pMyCharacter)		// ³» Ä³¸¯ÅÍ´Â ÀÌ¹Ì ¹Ù²å´Ù.
		{
			pCharacter->ChangeWeapon(parts);
		}
	}

Replace <br>

	void ZGame::OnChangeWeapon(MUID& uid, MMatchCharItemParts parts)
	{
		ZCharacter* pCharacter = m_CharacterManager.Find(uid);

		if (pCharacter && pCharacter != m_pMyCharacter)
		{
			pCharacter->ChangeWeapon(parts);
		}
		if (pCharacter)
		{
			if (pCharacter == m_pMyCharacter)
			{
				if (m_Match.GetMatchType() == MMATCH_GAMETYPE_SPY && m_Match.GetRoundState() == MMATCH_ROUNDSTATE_PLAY)
				{
					if (!ZApplication::GetGameInterface()->GetCombatInterface()) return;

					ZApplication::GetGameInterface()->GetCombatInterface()->SetDefaultSpyTip(m_pMyCharacter->GetTeamID());

					if (!ZApplication::GetGameInterface()->GetCombatInterface()->m_bSpyLocationOpened && !ZApplication::GetGameInterface()->GetCombatInterface()->GetObserverMode())
					{
						ZItem* pItem = m_pMyCharacter->GetItems()->GetItem(parts);
						if (!pItem) return;

						const char* pszSpyTip = ZApplication::GetGameInterface()->GetCombatInterface()->GetSuitableSpyItemTip((int)pItem->GetDescID());
						if (pszSpyTip)
							ZApplication::GetGameInterface()->GetCombatInterface()->SetSpyTip(pszSpyTip);
					}
				}
			}
			else
			{
				pCharacter->ChangeWeapon(parts);
			}
		}
	}

Find <br>

	case MMATCH_ROUNDSTATE_PLAY:
		{
			if (GetMatch()->GetMatchType() == MMATCH_GAMETYPE_CTF)
			{
			ZGetGameInterface()->PlayVoiceSound( VOICE_CTF, 1600);
			ZGetScreenEffectManager()->AddScreenEffect("ctf_splash");
			}
			else
			ZGetScreenEffectManager()->AddRock();
		}
		break;

Replace <br>

	case MMATCH_ROUNDSTATE_PLAY:
	{
		if (GetMatch()->GetMatchType() == MMATCH_GAMETYPE_CTF)
		{
			ZGetGameInterface()->PlayVoiceSound(VOICE_CTF, 1600);
			ZGetScreenEffectManager()->AddScreenEffect("ctf_splash");
		}
		MMATCH_GAMETYPE gameType = ZGetGameClient()->GetMatchStageSetting()->GetGameType();
		if (gameType == MMATCH_GAMETYPE_SPY)
		{
			ZGetScreenEffectManager()->AddScreenEffect("spy_selection");
			if (m_pMyCharacter->GetTeamID() == MMT_RED)
			{
				if (m_pMyCharacter->GetProperty()->nSex == MMS_MALE)
					ZGetGameInterface()->PlayVoiceSound("fx2/MAL01", 1500);
				else if (m_pMyCharacter->GetProperty()->nSex == MMS_FEMALE)
					ZGetGameInterface()->PlayVoiceSound("fx2/FEM01", 1500);
			}
			else
				ZGetGameInterface()->PlayVoiceSound(VOICE_LETS_ROCK, 1100);
		}
		ZGetScreenEffectManager()->AddRock();
	}
	break;;

Find <br>

					if((bAllKill) && (pAllKillPlayer))
					{
						MEMBER_SET_CHECKCRC(pAllKillPlayer->GetStatus(), nAllKill, pAllKillPlayer->GetStatus().Ref().nAllKill+1);
						pAllKillPlayer->AddIcon(ZCI_ALLKILL);
					}

Replace <br>

				if (GetMatch()->GetMatchType() == MMATCH_GAMETYPE_SPY)
					bAllKill = false;

				if ((bAllKill) && (pAllKillPlayer))
				{
					MEMBER_SET_CHECKCRC(pAllKillPlayer->GetStatus(), nAllKill, pAllKillPlayer->GetStatus().Ref().nAllKill + 1);
					pAllKillPlayer->AddIcon(ZCI_ALLKILL);
				}

Find <br>

	if(ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_DUEL)
	{
		ZRuleDuel* pDuel = (ZRuleDuel*)ZGetGameInterface()->GetGame()->GetMatch()->GetRule();
		nWritten = zfwrite(&pDuel->QInfo,sizeof(MTD_DuelQueueInfo),1,m_pReplayFile);
		if(nWritten==0) goto RECORDING_FAIL;
	}

Add under <br>

	else if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_SPY)
	{
		ZRuleSpy* pSpy = (ZRuleSpy*)m_Match.GetRule();

		int nSpyItemCount = (int)pSpy->m_vtLastSpyItem.size();
		nWritten = zfwrite(&nSpyItemCount, sizeof(int), 1, m_pReplayFile);
		if (nWritten == 0) goto RECORDING_FAIL;

		nWritten = zfwrite((void*)&pSpy->m_vtLastSpyItem[0], sizeof(MMatchSpyItem), nSpyItemCount, m_pReplayFile);
		if (nWritten == 0) goto RECORDING_FAIL;

		int nTrackerItemCount = (int)pSpy->m_vtLastTrackerItem.size();
		nWritten = zfwrite(&nTrackerItemCount, sizeof(int), 1, m_pReplayFile);
		if (nWritten == 0) goto RECORDING_FAIL;

		nWritten = zfwrite((void*)&pSpy->m_vtLastTrackerItem[0], sizeof(MMatchSpyItem), nTrackerItemCount, m_pReplayFile);
		if (nWritten == 0) goto RECORDING_FAIL;
	}

Open(ZGameClient.h) <br>
Find <br>

	bool IsDuelTournamentGame() { return m_MatchStageSetting.GetGameType() == MMATCH_GAMETYPE_DUELTOURNAMENT; }

Add under <br>

	bool IsSpyMode() { return m_MatchStageSetting.GetGameType() == MMATCH_GAMETYPE_SPY; }

Open(ZGameInterface.cpp) <br>
Find <br>

	ZGetGameTypeManager()->SetGameTypeStr(MMATCH_GAMETYPE_DEATHMATCH_SOLO, ZMsg(MSG_MT_DEATHMATCH_SOLO));

Add under <br>

	ZGetGameTypeManager()->SetGameTypeStr(MMATCH_GAMETYPE_SPY, "Spymode");

Find <br>

	MButton* pBlueTeamBtn  = (MButton*)m_IDLResource.FindWidget("StageTeamBlue");
	MButton* pBlueTeamBtn2 = (MButton*)m_IDLResource.FindWidget("StageTeamBlue2");
	MButton* pRedTeamBtn  = (MButton*)m_IDLResource.FindWidget("StageTeamRed");
	MButton* pRedTeamBtn2 = (MButton*)m_IDLResource.FindWidget("StageTeamRed2");
	if ((pRedTeamBtn == NULL) || (pBlueTeamBtn == NULL) || (pRedTeamBtn2 == NULL) || (pBlueTeamBtn2 == NULL))
		return;

Add under <br>

	bool bSpyMode = ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_SPY;


Open(ZInterfaceListener.cpp) <br>
Find <br>

				// ¸Ê µî·ÏÀÌ ¾ÈµÇ¾î ÀÖÀ¸¸é °ÔÀÓ ½ÃÀÛÀº ÇØÁÖÁö ¾Ê´Â´Ù.
				if(!ZApplication::GetStageInterface()->GetIsRelayMapRegisterComplete())
				{
					ZGetGameInterface()->ShowMessage(MSG_GAME_RELAYMAP_CONFIRM_BUTTON_PUSH);
					return true;
				}

				// ¸ÊÀÌ °ñ¶óÁ³À»¶§ ½ÃÀÛ °¡´É.
				if(ZGetGameClient()->GetMatchStageSetting()->GetMapName()[0]!=0)
				{
					ZApplication::GetStageInterface()->ChangeStageEnableReady( true);

					ZPostStageStart(ZGetGameClient()->GetPlayerUID(), ZGetGameClient()->GetStageUID());
				}
				else
				{
					ZGetGameInterface()->ShowMessage("¼±ÅÃÇÏ½Å ¸ÊÀÌ ¾ø½À´Ï´Ù. ¸ÊÀ» ¼±ÅÃÇØ ÁÖ¼¼¿ä.");
				}

				return true;
			}
			return false;
		}
	};
	MGameStartListener	g_GameStartListener;

Replace <br>

				if (pStageSetting->nGameType == MMATCH_GAMETYPE_SPY)
				{
					if (nPlayerCnt >= MMatchSpyMode::GetMinPlayers())
					{
						vector<int> vecMapIDs;

						if (ZApplication::GetStageInterface()->GetPlayableSpyMapList(nPlayerCnt, vecMapIDs))
						{
							ZApplication::GetStageInterface()->ChangeStageEnableReady(true);

							void* pMapListBlob = MMakeBlobArray(sizeof(int), (int)vecMapIDs.size());

							for (int i = 0; i < (int)vecMapIDs.size(); i++)
								*(int*)MGetBlobArrayElement(pMapListBlob, i) = vecMapIDs[i];

							ZPostSpyStageStart(pMapListBlob);

							MEraseBlobArray(pMapListBlob);
						}
						else
						{
							ZGetGameInterface()->ShowMessage(MSG_SPY_NO_SUITABLE_MAP);
						}
					}
					else
					{
						ZGetGameInterface()->ShowErrorMessage(MERR_SPY_LACKING_PLAYERS);
					}
				}
				else
				{
					if (ZGetGameClient()->GetMatchStageSetting()->GetMapName()[0] != 0)
					{
						ZApplication::GetStageInterface()->ChangeStageEnableReady(true);

						ZPostStageStart(ZGetGameClient()->GetPlayerUID(), ZGetGameClient()->GetStageUID());
					}
					else
					{
						ZGetGameInterface()->ShowMessage("¼±ÅÃÇÏ½Å ¸ÊÀÌ ¾ø½À´Ï´Ù. ¸ÊÀ» ¼±ÅÃÇØ ÁÖ¼¼¿ä.");
					}
				}
				return true;
			}
			return false;
		}
	};
	MGameStartListener	g_GameStartListener;

Open(ZMatch.cpp) <br>
Find <br>

        if (IsTeamPlay())
        {
            int nSpawnIndex[2] = { 0, 0 };
            for (int i = 0; i < 2; i++)
                if (ZGetGame()->m_pMyCharacter->GetTeamID() == MMT_RED + i)
                    pSpawnData = ZGetGame()->GetMapDesc()->GetSpawnManager()->GetTeamData(i, nSpawnIndex[i]);
        }
        else
            pSpawnData = ZGetGame()->GetMapDesc()->GetSpawnManager()->GetSoloRandomData();
        

Replace <br>

		if (IsTeamPlay() && GetMatchType() != MMATCH_GAMETYPE_SPY)
		{
			int nSpawnIndex[2] = { 0, 0 };
			for (int i = 0; i < 2; i++)
				if (ZGetGame()->m_pMyCharacter->GetTeamID() == MMT_RED + i)
					pSpawnData = ZGetGame()->GetMapDesc()->GetSpawnManager()->GetTeamData(i, nSpawnIndex[i]);
		}
		else
			pSpawnData = ZGetGame()->GetMapDesc()->GetSpawnManager()->GetSoloRandomData();


Find <br>

	void ZMatch::InitCharactersPosition()
	{
	    // ÆÀÀüÀÏ °æ¿ì
	    if (IsTeamPlay() && GetMatchType() != MMATCH_GAMETYPE_INFECTED)
		{
		    int nSpawnIndex[2] = { 0, 0 };


Replace <br>

	void ZMatch::InitCharactersPosition()
	{
		// ÆÀÀüÀÏ °æ¿ì
		if (IsTeamPlay() && GetMatchType() != MMATCH_GAMETYPE_INFECTED)
			if (IsTeamPlay() && GetMatchType() != MMATCH_GAMETYPE_SPY)
		{
			int nSpawnIndex[2] = { 0, 0 };

Find <br>

                else if (nArg == MMATCH_ROUNDRESULT_DRAW)
                {
                    // Do nothing...
                } 
                else {
                    MMatchTeam nTeamWon = (nArg == MMATCH_ROUNDRESULT_REDWON ? MMT_RED : MMT_BLUE);
                    if (nTeamWon == MMT_RED)
                        m_nTeamScore[MMT_RED]++;
                    else if (nTeamWon == MMT_BLUE)
                        m_nTeamScore[MMT_BLUE]++;
                }
            }
        }
        break;

Replace <br>

			else if (nArg == MMATCH_ROUNDRESULT_DRAW)
			{
				// Do nothing...
			}
			else {
				MMatchTeam nTeamWon = (nArg == MMATCH_ROUNDRESULT_REDWON ? MMT_RED : MMT_BLUE);
				if (nTeamWon == MMT_RED)
					m_nTeamScore[MMT_RED]++;
				else if (nTeamWon == MMT_BLUE)
					m_nTeamScore[MMT_BLUE]++;
			}
		}

		if (GetMatchType() == MMATCH_GAMETYPE_SPY)
		{
			MMatchTeam nWinnerTeam = (nArg == MMATCH_ROUNDRESULT_REDWON || nArg == MMATCH_ROUNDRESULT_BLUE_ALL_OUT ? MMT_RED : MMT_BLUE);

			for (ZCharacterManager::iterator i = ZGetGame()->m_CharacterManager.begin(); i != ZGetGame()->m_CharacterManager.end(); i++)
			{
				ZCharacter* pCharacter = (*i).second;

				if (pCharacter->GetTeamID() != nWinnerTeam)
				{
					pCharacter->ActDead();
					pCharacter->Die();
				}
			}
		}
	}
	break;

Open(ZObserver.cpp) <br>
Find <br>

		if(SetFirstTarget())
		{
			m_fDelay=ZOBSERVER_DEFAULT_DELAY_TIME;
			ShowInfo(true);
			m_bVisible = true;
			//ZApplication::GetGameInterface()->SetCursorEnable(true);

			return;
		}
	}

Replace <br>

		if(SetFirstTarget())
		{
			m_fDelay=ZOBSERVER_DEFAULT_DELAY_TIME;
			ShowInfo(true);
			m_bVisible = true;
			//			ZApplication::GetGameInterface()->SetCursorEnable(true);

			if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_SPY)
				ZApplication::GetGameInterface()->GetCombatInterface()->SetDefaultSpyTip(ZGetGame()->m_pMyCharacter->GetTeamID());

			return;
		}
	}

Find <br>

	else if (ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_DUEL)
	{
		char szName[128];
		sprintf(szName, "%s (HP:%d, AP:%d)", m_pTargetCharacter->GetUserName(), (int)m_pTargetCharacter->GetHP(), (int)m_pTargetCharacter->GetAP());
		MCOLOR CharNameColor;
		ZGetGame()->GetUserGradeIDColor(m_pTargetCharacter->GetUserGrade(), CharNameColor, "");
		if (m_pTargetCharacter->IsAdminName())
			pDC->SetColor(CharNameColor);
		else
			pDC->SetColor(CharNameColor);

		MFont* pFont = MFontManager::Get("FONTb11b");
		if (pFont == NULL)
			_ASSERT(0);
		pDC->SetFont(pFont);

		if (ZGetGameTypeManager()->IsTeamExtremeGame(ZGetGame()->GetMatch()->GetMatchType()))
			TextRelative(pDC, 0.5f, 75.0f / 800.0f, szName, true);
		else
			TextRelative(pDC, 0.5f, 50.0f / 800.0f, szName, true);
	}

Replace <br>

	else if ( ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_DUEL)
	{
		char szName[128];
		sprintf(szName, "%s (HP:%d, AP:%d)", m_pTargetCharacter->GetUserName(), (int)m_pTargetCharacter->GetHP(), (int)m_pTargetCharacter->GetAP());
		int nRed = m_pTargetCharacter->GetCharInfo()->nRedColor, nGreen = m_pTargetCharacter->GetCharInfo()->nGreenColor, nBlue = m_pTargetCharacter->GetCharInfo()->nBlueColor;
		pDC->SetColor(MCOLOR(nRed, nGreen, nBlue));

		MFont *pFont = MFontManager::Get( "FONTb11b");
		if ( pFont == NULL)
			//_ASSERT(0);
				pDC->SetFont( pFont);
		if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_SPY)
			TextRelative(pDC, 0.5f, 763.0f / 800.0f, szName, true);

		if(ZGetGameTypeManager()->IsTeamExtremeGame(ZGetGame()->GetMatch()->GetMatchType()))
			TextRelative( pDC, 0.5f, 75.0f/800.0f, szName, true);
		else
			TextRelative( pDC, 0.5f, 50.0f/800.0f, szName, true);
	}


Open(ZPlayerListBox.cpp) <br>
Find <br>

	void ZPlayerListBox::AddPlayer(MUID& puid, MMatchObjectStageState state, int nLevel, char* szName, char* szClanName, unsigned int nClanID, bool isMaster, MMatchTeam nTeam, int duelTournamentGrade
		, int nR, int nG, int nB)
	{
		if ((int)strlen(szName) == 0)
			return;


		char szFileName[64] = "";
		char szFileNameState[64] = "";
		char szLevel[64] = "";

		char* szRefName = NULL;

		MCOLOR _color = MCOLOR(nR, nG, nB);
		char sp_name[256];
		bool bSpUser = false;

		MMatchUserGradeID gid = MMUG_FREE;

		if (GetUserInfoUID(puid, _color, sp_name, gid)) {
			sprintf(szLevel, "--");
			szRefName = szName;
			bSpUser = true;
		}
		else {
			sprintf(szLevel, "%2d", nLevel);
			szRefName = szName;
		}

Add under <br>

	if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_SPY)
		nTeam = MMT_ALL;

Find <br>

	void ZPlayerListBox::UpdatePlayer(MUID& puid,MMatchObjectStageState state, bool isMaster,MMatchTeam nTeam)
	{
		ZStagePlayerListItem* pItem = (ZStagePlayerListItem*)GetUID(puid);

		if(pItem) {

			char szFileName[64] = "";
			char szFileNameState[64] = "";

			MBitmap* pBitmap = NULL;
			MBitmap* pBitmapState = NULL;

			const MSTAGE_SETTING_NODE* pStageSetting = ZGetGameClient()->GetMatchStageSetting()->GetStageSetting();


Add under <br>

		//Infected game mode room list
		if ((nTeam != MMT_SPECTATOR) && (ZGetGameTypeManager()->IsTeamGame(pStageSetting->nGameType) == false) ||
			pStageSetting->nGameType == MMATCH_GAMETYPE_INFECTED || pStageSetting->nGameType == MMATCH_GAMETYPE_SPY)
		{
			nTeam = MMT_ALL;
		}


Find <br>

	void ZPlayerListBox::UpdatePlayer(MUID& puid,MMatchObjectStageState state, char* szName, int  nLevel ,bool isMaster,MMatchTeam nTeam)
	{
		return;

		ZStagePlayerListItem* pItem = (ZStagePlayerListItem*)GetUID(puid);
		if(pItem) {

			char szFileName[64] = "";
			char szFileNameState[64] = "";
			char szLevel[64];

			MBitmap* pBitmap = NULL;
			MBitmap* pBitmapState = NULL;

Add under <br>

		if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_SPY)
			nTeam = MMT_ALL;


Open(ZReplay.cpp) <br>
Find <br>

	if(m_StageSetting.nGameType==MMATCH_GAMETYPE_DUEL)
	{
		ZRuleDuel* pDuel = (ZRuleDuel*)ZGetGameInterface()->GetGame()->GetMatch()->GetRule();
		int nRead = zfread(&pDuel->QInfo,sizeof(MTD_DuelQueueInfo),1,file);
		if(nRead==0) return false;
	}

Add under <br>

	else if (m_StageSetting.nGameType == MMATCH_GAMETYPE_SPY)
	{
		ZRuleSpy* pSpy = (ZRuleSpy*)ZGetGame()->GetMatch()->GetRule();

		int nSpyItemCount;
		int nRead = zfread(&nSpyItemCount, sizeof(int), 1, file);
		if (nRead == 0) return false;

		vector<MMatchSpyItem> vecSpyItem;
		for (int i = 0; i < nSpyItemCount; i++)
		{
			MMatchSpyItem item;
			nRead = zfread(&item, sizeof(MMatchSpyItem), 1, file);
			if (nRead == 0) return false;

			vecSpyItem.push_back(item);
		}

		pSpy->m_vtLastSpyItem = vecSpyItem;

		int nTrackerItemCount;
		nRead = zfread(&nTrackerItemCount, sizeof(int), 1, file);
		if (nRead == 0) return false;

		vector<MMatchSpyItem> vecTrackerItem;
		for (int i = 0; i < nTrackerItemCount; i++)
		{
			MMatchSpyItem item;
			nRead = zfread(&item, sizeof(MMatchSpyItem), 1, file);
			if (nRead == 0) return false;

			vecTrackerItem.push_back(item);
		}

		pSpy->m_vtLastTrackerItem = vecTrackerItem;
	}


Open(ZRule.cpp) <br>
Find <br>

	case MMATCH_GAMETYPE_DEATHMATCH_SOLO:
		{
			return (new ZRuleSoloDeathMatch(pMatch));
		}
		break;

Add under <br>

	case MMATCH_GAMETYPE_SPY:
	{
		return (new ZRuleSpy(pMatch));
	}
	break;

Open(ZStageInterface.cpp) <br>
Find <br>

		MComboBox* pCombo = (MComboBox*)pResource->FindWidget("Stage_RelayMapType");			
		if ( pCombo)
			pCombo->CloseComboBoxList();
		pCombo = (MComboBox*)pResource->FindWidget("Stage_RelayMapRepeatCount");					
		if ( pCombo)
			pCombo->CloseComboBoxList();

		MListBox* pListBox = (MListBox*)pResource->FindWidget( "Stage_RelayMapListbox");
		if ( pListBox)
			pListBox->RemoveAll();
		pListBox = (MListBox*)pResource->FindWidget( "Stage_MapListbox");
		if ( pListBox)
			pListBox->RemoveAll();
	}

Add under <br>

	{ // SPY mode : ban map list.
		pPicture = (MPicture*)pResource->FindWidget("Stage_SpyBanMapListBG");
		if (pPicture)
		{ // f¸±·¹ÀÌ¸Ê ¸®½ºÆ® ¹è°EÀÌ¹ÌÁE
			m_pSpyBanMapListFrameImg = new MBitmapR2;
			((MBitmapR2*)m_pSpyBanMapListFrameImg)->Create("spybanmaplistframe.tga", RGetDevice(), "interface/loadable/spybanmaplistframe.tga");

			if (m_pSpyBanMapListFrameImg != NULL)
				pPicture->SetBitmap(m_pSpyBanMapListFrameImg->GetSourceBitmap());
		}
		MWidget* pWidget = (MWidget*)pResource->FindWidget("Stage_SpyBanMapListView");
		if (pWidget)
		{
			MRECT rect;
			rect = pWidget->GetRect();
			rect.x = -rect.w;
			m_nSpyBanMapListFramePos = rect.x;
			pWidget->SetBounds(rect);
		}

		MListBox* pListBox = (MListBox*)pResource->FindWidget("Stage_SpyBanMapList");
		if (pListBox)
			pListBox->RemoveAll();

		pLabel = (MLabel*)pResource->FindWidget("Stage_SpyRandomMapLabel");
		if (pLabel)
			pLabel->Show(false);

		MComboBox* pComboBox = (MComboBox*)pResource->FindWidget("MapSelection");
		if (pComboBox)
			pComboBox->Show(true);
	}

Find <br>

		if ( ZGetGameClient()->GetMatchStageSetting()->GetStageState() == STAGE_STATE_STANDBY)
		{
			ZGetGameClient()->ReleaseForcedEntry();

			// ÀÎÅÍÆäÀÌ½º°ü·Ã
			ZApplication::GetGameInterface()->EnableWidget( "StageSettingCaller", true);	// ¹æ¼³Á¤ ¹öÆ°
			ZApplication::GetGameInterface()->EnableWidget( "MapSelection", true);			// ¸Ê¼±ÅÃ ÄÞº¸¹Ú½º
			ZApplication::GetGameInterface()->EnableWidget( "StageType", true);				// °ÔÀÓ¹æ½Ä ÄÞº¸¹Ú½º
			ZApplication::GetGameInterface()->EnableWidget( "StageMaxPlayer", true);		// ÃÖ´ëÀÎ¿ø ÄÞº¸¹Ú½º
			ZApplication::GetGameInterface()->EnableWidget( "StageRoundCount", true);		// °æ±âÈ½¼ö ÄÞº¸¹Ú½º
		}
		
Replace <br>

		if ( ZGetGameClient()->GetMatchStageSetting()->GetStageState() == STAGE_STATE_STANDBY)
		{
			ZGetGameClient()->ReleaseForcedEntry();

			// ÀÎÅÍÆäÀÌ½º°ü·Ã
			ZApplication::GetGameInterface()->EnableWidget("StageSettingCaller", ZGetGameClient()->GetMatchStageSetting()->GetGameType() != MMATCH_GAMETYPE_SPY);	// ¹æ¼³Á¤ ¹öÆ°
			ZApplication::GetGameInterface()->EnableWidget("MapSelection", true);			// ¸Ê¼±ÅÃ ÄÞº¸¹Ú½º
		}


Find <br>

		case MMATCH_GAMETYPE_DUELTOURNAMENT:
			color = SDM_COLOR;
			break;
			
Add under <br>

		case MMATCH_GAMETYPE_SPY:
			color = TDM_COLOR;
			break;


Find <br>

	else if ( pSetting->nGameType == MMATCH_GAMETYPE_QUEST)						// Äù½ºÆ® ¸ðµåÀÌ¸é...
	{
		// ¸Ê ÀÌ¸§ ¹è°æ ÀÌ¹ÌÁö º¯È¯
		if ( pAniMapImg)
			pAniMapImg->SetCurrentFrame( 2);

		// Äù½ºÆ® UI º¸ÀÓ
		bQuestUI = true;
	}
	
Add under <br>

	else if (pSetting->nGameType == MMATCH_GAMETYPE_SPY)
	{
		if (pAniMapImg)
			pAniMapImg->SetCurrentFrame(4);
		bQuestUI = false;
		bSpyUI = true;
	}

Find <br>

	if (pSetting->bIsRelayMap)
		OpenRelayMapBox();
	else
		HideRelayMapBox();
		
Add under <br>

	///// SPY MODE /////
	if (bSpyUI)
		OpenSpyBanMapBox();
	else
		HideSpyBanMapBox();

	MLabel* pSpyRandomMapLabel = (MLabel*)pResource->FindWidget("Stage_SpyRandomMapLabel");
	if (pSpyRandomMapLabel)
		pSpyRandomMapLabel->Show(bSpyUI);

	pCombo = (MComboBox*)pResource->FindWidget("MapSelection");
	if (pCombo)
		pCombo->Show(!bSpyUI);
	////////////////////

Find <br>

	if ( (pSetting->nGameType == MMATCH_GAMETYPE_SURVIVAL) || (pSetting->nGameType == MMATCH_GAMETYPE_QUEST))
		ZApplication::GetGameInterface()->EnableWidget( "StageSettingCaller", false);

Replace <br>

	if ((pSetting->nGameType == MMATCH_GAMETYPE_SURVIVAL) || (pSetting->nGameType == MMATCH_GAMETYPE_QUEST) || (pSetting->nGameType == MMATCH_GAMETYPE_SPY))
		ZApplication::GetGameInterface()->EnableWidget("StageSettingCaller", false);

Find <br>

		if ( ZGetGameClient()->AmIStageMaster())
		{
			ZApplication::GetGameInterface()->EnableWidget( "MapSelection", !bReady);
			ZApplication::GetGameInterface()->EnableWidget( "StageType", !bReady);
			ZApplication::GetGameInterface()->EnableWidget( "StageMaxPlayer", !bReady);
			ZApplication::GetGameInterface()->EnableWidget( "StageRoundCount", !bReady);
			ZApplication::GetGameInterface()->EnableWidget( "StageSettingCaller", !bReady);
			ZApplication::GetGameInterface()->EnableWidget( "Stage_RelayMap_OK_Button", !bReady);
			ZApplication::GetGameInterface()->EnableWidget( "Stage_RelayMapType", !bReady);
			ZApplication::GetGameInterface()->EnableWidget( "Stage_RelayMapRepeatCount", !bReady);
		}

Replace <br>

		if ( ZGetGameClient()->AmIStageMaster())
		{
			ZApplication::GetGameInterface()->EnableWidget( "MapSelection", !bReady);
			ZApplication::GetGameInterface()->EnableWidget( "StageType", !bReady);
			ZApplication::GetGameInterface()->EnableWidget( "StageMaxPlayer", !bReady);
			ZApplication::GetGameInterface()->EnableWidget( "StageRoundCount", !bReady);
			ZApplication::GetGameInterface()->EnableWidget("StageSettingCaller", !bReady && m_nGameType != MMATCH_GAMETYPE_SPY);
			ZApplication::GetGameInterface()->EnableWidget( "Stage_RelayMap_OK_Button", !bReady);
			ZApplication::GetGameInterface()->EnableWidget( "Stage_RelayMapType", !bReady);
			ZApplication::GetGameInterface()->EnableWidget( "Stage_RelayMapRepeatCount", !bReady);
		}

Find <br>

		else if( INVALID_MAP == nType )
		{
			char szMsg[ 128 ];

				sprintf( szMsg, "INVALID MAP!" );
					//MGetStringResManager()->GetErrorStr(MERR_CANNOT_START_NEED_TICKET), 
					//ZApplication::GetInstance()->GetGameClient()->GetObjName(uidParam).c_str() );

				ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
				ZChatOutput(szMsg, ZChat::CMT_BROADCAST);
		}

		// Stage UI Enable
		ChangeStageEnableReady( false);
	}

Add under <br>

	////////////////////////////////// Spy Mode. //////////////////////////////////
	class MSpyBanMapListListener : public MListener
	{
	public:
		virtual bool OnCommand(MWidget* pWidget, const char* szMessage)
		{
			// ½ºÅ×ÀÌÁE¸¶½ºÅÍ°¡ ¾Æ´Ï¸E¸Ê ¸®½ºÆ®¸¦ ÄÁÆ®·Ñ ÇÒ¼ö¾ø´Ù.
			if (!ZGetGameClient()->AmIStageMaster())
				return false;
			// On select
			if (MWidget::IsMsg(szMessage, MLB_ITEM_SEL) == true)
			{
				MListBox* pListBox = (MListBox*)ZGetGameInterface()->GetIDLResource()->FindWidget("Stage_SpyBanMapList");
				if (!pListBox) return false;

				SpyBanMapList* pSpyBanMapList = (SpyBanMapList*)pListBox->GetSelItem();
				if (!MMatchSpyMap::IsExistingMap(pSpyBanMapList->GetMapID())) return false;

				ZPostActivateSpyMap(pSpyBanMapList->GetMapID(), ZGetGameClient()->GetMatchStageSetting()->IsIncludedSpyMap(pSpyBanMapList->GetMapID()));
				return true;
			}

			return false;
		}
	};
	MSpyBanMapListListener g_SpyBanMapListListener;
	MListener* ZGetSpyBanMapListListener(void)
	{
		return &g_SpyBanMapListListener;
	}

	///////////////////////////////////////////////////////

	void ZStageInterface::OpenSpyBanMapBox()
	{
		ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();

		MButton* pButton = (MButton*)pResource->FindWidget("Stage_SpyBanMapBoxOpen");
		if (pButton)
			pButton->Show(false);
		pButton = (MButton*)pResource->FindWidget("Stage_SpyBanMapBoxClose");
		if (pButton)
			pButton->Show(true);

		SetSpyBanMapBoxPos(2);

		CreateSpyBanMapList();
	}

	void ZStageInterface::CloseSpyBanMapBox()
	{
		ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();

		MButton* pButton = (MButton*)pResource->FindWidget("Stage_SpyBanMapBoxClose");
		if (pButton)
			pButton->Show(false);
		pButton = (MButton*)pResource->FindWidget("Stage_SpyBanMapBoxOpen");
		if (pButton)
			pButton->Show(true);

		MWidget* pWidget = pResource->FindWidget("Stage_CharacterInfo");
		if (pWidget)
			pWidget->Enable(true);

		SetSpyBanMapBoxPos(1);
	}

	void ZStageInterface::HideSpyBanMapBox()
	{
		ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();

		MButton* pButton = (MButton*)pResource->FindWidget("Stage_SpyBanMapBoxClose");
		if (pButton)
			pButton->Show(false);
		pButton = (MButton*)pResource->FindWidget("Stage_SpyBanMapBoxOpen");
		if (pButton)
			pButton->Show(true);

		MWidget* pWidget = pResource->FindWidget("Stage_CharacterInfo");
		if (pWidget)
			pWidget->Enable(true);

		SetSpyBanMapBoxPos(0);
	}

	void ZStageInterface::SetSpyBanMapBoxPos(int nBoxPos)
	{
		MWidget* pWidget = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Stage_SpyBanMapListView");
		if (pWidget)
		{
			MRECT rect;

			switch (nBoxPos)
			{
			case 0:		// Hide
				rect = pWidget->GetRect();
				m_nSpyBanMapListFramePos = -rect.w;
				break;

			case 1:		// Close
				rect = pWidget->GetRect();
				m_nSpyBanMapListFramePos = -rect.w + (rect.w * 0.14);
				break;

			case 2:		// Open
				m_nSpyBanMapListFramePos = 0;
				break;
			}
		}
	}

	void ZStageInterface::CreateSpyBanMapList()
	{
		// ¸Ê ¸®½ºÆ® ¸¸µé¾EÁÖ±E
		MListBox* pMapListBox = (MListBox*)ZGetGameInterface()->GetIDLResource()->FindWidget("Stage_SpyBanMapList");
		if (pMapListBox == NULL) return;

		pMapListBox->RemoveAll();	// ±âÁ¸ ¸±·¹ÀÌ¸Ê ¸®½ºÆ®¸¦ ¸ðµÎ Áö¿öÁØ´Ù.
		int nCurrPlayers = (int)ZGetGameClient()->GetMatchStageSetting()->m_CharSettingList.size();

		for (int i = MMATCH_SPY_MAP_MANSION; i < MMATCH_SPY_MAP_MAX; i++)
		{
			char szListName[256];
			sprintf(szListName, "(%d~%d%s) %s", g_SpyMapNode[i].nMinPlayers, g_SpyMapNode[i].nMaxPlayers, ZMsg(MSG_SPY_WORD_PLAYERS), g_SpyMapNode[i].szName);

			SpyBanMapList* pSpyBanMapList = new SpyBanMapList(szListName,
				MBitmapManager::Get(
				ZGetGameClient()->GetMatchStageSetting()->IsIncludedSpyMap(g_SpyMapNode[i].nID) ?
				"Mark_Arrow.bmp" : "Mark_X.bmp"),
				g_SpyMapNode[i].nID);

			if (nCurrPlayers < g_SpyMapNode[i].nMinPlayers || nCurrPlayers > g_SpyMapNode[i].nMaxPlayers)
			{
				pSpyBanMapList->SetColor(MCOLOR(0xFFFF0000));	// RED color.
			}

			pMapListBox->Add(pSpyBanMapList);
		}
	}

	bool ZStageInterface::GetPlayableSpyMapList(int players, vector<int>& out)
	{
		int nCurrPlayers = (int)ZGetGameClient()->GetMatchStageSetting()->m_CharSettingList.size();

		for (int i = MMATCH_SPY_MAP_MANSION; i < MMATCH_SPY_MAP_MAX; i++)
		{
			if (ZGetGameClient()->GetMatchStageSetting()->IsIncludedSpyMap(g_SpyMapNode[i].nID))
			{
	#if !defined(_ARTIC_DEBUG)
				if (nCurrPlayers >= g_SpyMapNode[i].nMinPlayers && nCurrPlayers <= g_SpyMapNode[i].nMaxPlayers)
	#endif
				{
					out.push_back(g_SpyMapNode[i].nID);
				}
			}
		}

		return !out.empty();
	}

	void ZStageInterface::OnSpyStageActivateMap(int nMapID, bool bExclude)
	{
		MMatchStageSetting* pSetting = ZGetGameClient()->GetMatchStageSetting();

		if (bExclude)
			pSetting->ExcludeSpyMap(nMapID);
		else
			pSetting->IncludeSpyMap(nMapID);

		CreateSpyBanMapList();	// Refresh.
	}

	void ZStageInterface::OnSpyStageBanMapList(void* pMapListBlob)
	{
		MMatchStageSetting* pSetting = ZGetGameClient()->GetMatchStageSetting();
		pSetting->UnbanAllSpyMap();

		int nCount = MGetBlobArrayCount(pMapListBlob);

		for (int i = 0; i < nCount; i++)
			pSetting->ExcludeSpyMap(*(int*)MGetBlobArrayElement(pMapListBlob, i));

		CreateSpyBanMapList();
	}
	///////////////////////////////////////////////////////////////////////////////

Open(ZStageSetting.cpp) <br>
Find <br>

	ZGameTypeConfig* pGameTypeCfg = ZGetConfiguration()->GetGameTypeList()->GetGameTypeCfg(pOutNode->nGameType);
	if (pGameTypeCfg)
	{
		// ÃÖ´ë ÀÎ¿ø
		if (!BUILD_STAGESETTING_LISTITEM(pResource, "StageMaxPlayer", pOutNode->nMaxPlayers, pGameTypeCfg->m_MaxPlayers))
			return false;

		// ¶ó¿îµå
		if (!BUILD_STAGESETTING_LISTITEM(pResource, "StageRoundCount", pOutNode->nRoundMax, pGameTypeCfg->m_Round))
			return false;

		// Á¦ÇÑ½Ã°£
		if (!BUILD_STAGESETTING_LISTITEM(pResource, "StageLimitTime", pOutNode->nLimitTime, pGameTypeCfg->m_LimitTime))
			return false;
	}

Replace <br>

	ZGameTypeConfig* pGameTypeCfg = ZGetConfiguration()->GetGameTypeList()->GetGameTypeCfg(pOutNode->nGameType);
	if (pGameTypeCfg)
	{
		// ÃÖ´ë ÀÎ¿ø
		BUILD_STAGESETTING_LISTITEM("StageMaxPlayer", pOutNode->nMaxPlayers, pGameTypeCfg->m_MaxPlayers);

		// ¶ó¿îµå
		BUILD_STAGESETTING_LISTITEM("StageRoundCount", pOutNode->nRoundMax, pGameTypeCfg->m_Round);

		if (pOutNode->nGameType == MMATCH_GAMETYPE_SPY)
		{
			pOutNode->nLimitTime = -1;//99999;
		}
		else
		{
			// Á¦ÇÑ½Ã°£
			BUILD_STAGESETTING_LISTITEM("StageLimitTime", pOutNode->nLimitTime, pGameTypeCfg->m_LimitTime);
		}
	}

Open(MMatchServer.h) <br>
Find <br>

		void OnAsyncRequest_RewardCharBP(const MUID& uidPlayer, int nBRID, int nBRTID, int nRewardCount, int nBattleTime, int nKillCount, int nItemID, int nItemCnt, int nRentHourPeriod);
		void OnAsyncRequest_UpdateCharBRInfo(const MUID& uidPlayer, int nBRID, int nBRTID, int nRewardCount, int nBattleTime, int nKillCount);

Add under <br>

	MCommand* BuildSpyBanMapListCommand(MMatchStageSetting* pSetting);

	void OnSpyStageRequestBanMapList(const MUID& uidPlayer);
	void OnSpyStageActivateMap(const MUID& uidPlayer, int nMapID, bool bExclude);
	void OnSpyStageStart(const MUID& uidPlayer, void* pMapListBlob);

Open(MMatchServer_OnCommand.cpp) <br>
Find <br>

		case MC_MATCH_DUELTOURNAMENT_REQUEST_SIDERANKING_INFO :
			{
				MUID uidPlayer;

				pCommand->GetParameter(&uidPlayer, 0, MPT_UID);

				if( MGetServerConfig()->IsEnabledDuelTournament() ){
					ResponseDuelTournamentCharSideRanking(uidPlayer);
				}
			}
			break;

Add <br>

	case MC_SPY_STAGE_REQUEST_BAN_MAP_LIST:
	{
		OnSpyStageRequestBanMapList(pCommand->GetSenderUID());
	}
	break;

	case MC_SPY_STAGE_ACTIVATE_MAP:
	{
		int nMapID;
		bool bExclude;

		pCommand->GetParameter(&nMapID, 0, MPT_INT);
		pCommand->GetParameter(&bExclude, 1, MPT_BOOL);

		OnSpyStageActivateMap(pCommand->GetSenderUID(), nMapID, bExclude);
	}
	break;

	case MC_SPY_STAGE_REQUEST_START:
	{
		MCommandParameter* pParam = pCommand->GetParameter(0);
		if ((!pParam) || (pParam->GetType() != MPT_BLOB) || (pParam->GetSize() < (sizeof(int) * 2)))
		{
			_ASSERT(0);
			break;
		}

		void* pBlob = pParam->GetPointer();
		if (MGetBlobArraySize(pBlob) != (pParam->GetSize() - sizeof(int)))
		{
			_ASSERT(0);
			break;
		}

		OnSpyStageStart(pCommand->GetSenderUID(), pBlob);
	}
	break;

Open(ZGameInterface_OnCommand.cpp) <br>
Find <br>

	case MC_MATCH_CLAN_ACCOUNCE_DELETE :
		{
			char szDeleteDate[ 128 ] = {0,};
			pCommand->GetParameter( szDeleteDate, 0, MPT_STR, 128 );

			ZApplication::GetGameInterface()->OnAnnounceDeleteClan( szDeleteDate );
		}
		break;

Add under <br>

	case MC_SPY_STAGE_BAN_MAP_LIST:
	{
		MCommandParameter* pParam = pCommand->GetParameter(0);
		if(pParam->GetType() != MPT_BLOB) 
		{
			_ASSERT(0);
			break;
	}

		void* pMapListBlob = pParam->GetPointer();
		if (!pMapListBlob)
		{
			_ASSERT(0);
			break;
		}

		ZApplication::GetStageInterface()->OnSpyStageBanMapList(pMapListBlob);
		}
	break;

	case MC_SPY_STAGE_ACTIVATE_MAP:
	{
		int nMapID;
		bool bExclude;

		pCommand->GetParameter(&nMapID, 0, MPT_INT);
		pCommand->GetParameter(&bExclude, 1, MPT_BOOL);

		ZApplication::GetStageInterface()->OnSpyStageActivateMap(nMapID, bExclude);
	}
	break;

Open(ZStageInterface.h) <br>
Find <br>

	#ifdef _QUEST_ITEM
		bool OnResponseDropSacrificeItemOnSlot( const int nResult, const MUID& uidRequester, const int nSlotIndex, const int nItemID );
		bool OnResponseCallbackSacrificeItem( const int nResult, const MUID& uidRequester, const int nSlotIndex, const int nItemID );
		bool OnResponseQL( const int nQL );
		bool OnResponseSacrificeSlotInfo( const MUID& uidOwner1, const unsigned long int nItemID1, 
										  const MUID& uidOwner2, const unsigned long int nItemID2 );
		bool OnNotAllReady();
		bool OnQuestStartFailed( const int nState );
		bool OnStageGameInfo( const int nQL, const int nMapsetID, const unsigned int nScenarioID );
	#endif

		bool OnStopVote();
	};

Replace <br>

	#ifdef _QUEST_ITEM
		bool OnResponseDropSacrificeItemOnSlot( const int nResult, const MUID& uidRequester, const int nSlotIndex, const int nItemID );
		bool OnResponseCallbackSacrificeItem( const int nResult, const MUID& uidRequester, const int nSlotIndex, const int nItemID );
		bool OnResponseQL( const int nQL );
		bool OnResponseSacrificeSlotInfo( const MUID& uidOwner1, const unsigned long int nItemID1, 
										  const MUID& uidOwner2, const unsigned long int nItemID2 );
		bool OnNotAllReady();
		bool OnQuestStartFailed( const int nState );
		bool OnStageGameInfo( const int nQL, const int nMapsetID, const unsigned int nScenarioID );
	#endif

		bool OnStopVote();

		// Spy Mode.
	protected:
		MBitmapR2*		m_pSpyBanMapListFrameImg;
	public:
		void OpenSpyBanMapBox();
		void CloseSpyBanMapBox();
		void HideSpyBanMapBox();
		void SetSpyBanMapBoxPos(int nBoxPos);

		void CreateSpyBanMapList();
		bool GetPlayableSpyMapList(int players, vector<int>& out);

		void OnSpyStageActivateMap(int nMapID, bool bExclude);
		void OnSpyStageBanMapList(void* pMapListBlob);

		int m_nSpyBanMapListFramePos;
	};

Open(MMatchStageSetting.h) <br>
Find <br>

		// ÇÙ¹æ¾î¿ë Å¬¶ó¿¡¼­¸¸ È£Ãâ
		void AntiHack_ShiftHeapPos()	{ m_StageSetting.ShiftHeapPos(); }
		void AntiHack_CheckCrc()		{ m_StageSetting.CheckCrc(); }
	};

Replace <br>

	// ÇÙ¹æ¾î¿ë Å¬¶ó¿¡¼­¸¸ È£Ãâ
	void AntiHack_ShiftHeapPos()	{ m_StageSetting.ShiftHeapPos(); }
	void AntiHack_CheckCrc()		{ m_StageSetting.CheckCrc(); }

	// Spy Mode...
	public:
		vector<int>		m_vecSpyBanMapList;

		void ExcludeSpyMap(int nMapID);
		void IncludeSpyMap(int nMapID);

		bool IsExcludedSpyMap(int nMapID);
		bool IsIncludedSpyMap(int nMapID);

		void UnbanAllSpyMap();
	};

Open(MMatchStageSetting.cpp) <br>
Find <br>

	void MMatchStageSetting::Clear()
	{
		SetDefault();
		m_CharSettingList.DeleteAll();
		m_uidMaster = MUID(0,0);
		m_nStageState = STAGE_STATE_STANDBY;
		m_bIsCheckTicket = false;

	}

Replace <br>

	void MMatchStageSetting::Clear()
	{
		SetDefault();
		m_CharSettingList.DeleteAll();
		m_uidMaster = MUID(0,0);
		m_nStageState = STAGE_STATE_STANDBY;
		m_bIsCheckTicket = false;
		m_vecSpyBanMapList.reserve(MMATCH_SPY_MAP_MAX - 1);

	}

Find <br>

	void MMatchStageSetting::SetRelayMapList(RelayMap* pValue)
	{ 
		m_StageSetting.CheckCrc();
		memcpy(m_StageSetting.Ref().MapList, pValue, sizeof(m_StageSetting.Ref().MapList));
		m_StageSetting.MakeCrc();
	}

Add under <br>

	void MMatchStageSetting::ExcludeSpyMap(int nMapID)
	{
		vector<int>::iterator itBegin = m_vecSpyBanMapList.begin(), itEnd = m_vecSpyBanMapList.end();
		vector<int>::iterator itFound = std::find(itBegin, itEnd, nMapID);

		if (itFound != itEnd) return;
		m_vecSpyBanMapList.push_back(nMapID);
	}

	void MMatchStageSetting::IncludeSpyMap(int nMapID)
	{
		vector<int>::iterator itBegin = m_vecSpyBanMapList.begin(), itEnd = m_vecSpyBanMapList.end();
		vector<int>::iterator itFound = std::find(itBegin, itEnd, nMapID);

		if (itFound == itEnd) return;
		m_vecSpyBanMapList.erase(itFound);
	}

	bool MMatchStageSetting::IsExcludedSpyMap(int nMapID)
	{
		vector<int>::iterator itBegin = m_vecSpyBanMapList.begin(), itEnd = m_vecSpyBanMapList.end();
		vector<int>::iterator itFound = std::find(itBegin, itEnd, nMapID);

		return itFound != itEnd;
	}

	bool MMatchStageSetting::IsIncludedSpyMap(int nMapID)
	{
		return !IsExcludedSpyMap(nMapID);
	}

	void MMatchStageSetting::UnbanAllSpyMap()
	{
		m_vecSpyBanMapList.clear();

	}

Open(MMatchTransDataType.h) <br>
Find <br>

	struct MTD_ShopItemInfo
	{
		unsigned int	nItemID;
		int				nItemCount;
	};

Add under <br>

	struct MTD_SpyRoundFinishInfo
	{
		MUID uidPlayer;
		int nXP;
		int nPercent;
		int nBP;
		int nPoint;
	};

	struct MTD_SpyPlayerScoreInfo
	{
		MUID uidPlayer;
		int nWin;
		int nLose;
		int nPoint;
	};

Open(MMatchServer_Stage.cpp) <br>
Find <br>

	#include "MMatchRuleDuel.h"
	#include "MCrashDump.h"

Add <br>

	#include "MMatchRuleSpy.h"

Open(ZCombatInterface.h) <br>
Find <br>

		const char* GetRedClanName() const { return m_szRedClanName; }
		const char* GetBlueClanName() const { return m_szBlueClanName; }
	};

Replace <br>

		const char* GetRedClanName() const { return m_szRedClanName; }
		const char* GetBlueClanName() const { return m_szBlueClanName; }
		ZWeaponScreenEffect* GetWeaponScreenEffect() { return m_pWeaponScreenEffect; }
	public:
		void OnSpyCreate();
		void OnSpyDestroy();

		void CreateSpyGameInterface();
		void CreateSpyWaitInterface();

		void OnSpyUpdate(float fElapsed);
		void OnSpyDraw(MDrawContext* pDC);

		void SetSpyTip(const char* msg);
		void SetSpyEventMsg(const char* imgName);
		void SetSpyNotice(const char* imgName);

		void SetDefaultSpyTip(MMatchTeam team);
		const char* GetSuitableSpyItemTip(int itemid);

		bool m_bSpyLocationOpened;

	protected:
		MBitmapR2* m_pSpyIcon;

	protected:
		void SetSpyTimeLimitValue(int m, int s, int ms);
		void SetSpyTimeLimitValue(DWORD dwTime);

	public:
		void SetSpyTimer(DWORD dwTimeLimit);
	protected:
		DWORD m_dwSpyTimer;

	public:
		void PlaySpyNotice(const char* imgName);
	protected:
		bool m_bSpyNoticePlaying;
		DWORD m_dwSpyNoticePlayStartedTime;
	};

Open(MSharedCommandTable.h) <br>
Find <br>

	#define MC_LOCAL_UPDATE_CUSTOM_IP				50008
	#define MC_LOCAL_UPDATE_ACCEPT_INVALID_IP		50009

Add under <br>

	//SpyMode
	#define MC_SPY_STAGE_REQUEST_BAN_MAP_LIST			            60040
	#define MC_SPY_STAGE_BAN_MAP_LIST					            60041
	#define MC_SPY_STAGE_ACTIVATE_MAP					            60042
	#define MC_SPY_STAGE_REQUEST_START					            60043
	#define MC_SPY_GAME_INFO							            60044
	#define MC_SPY_GAME_RESULT							            60045
	#define MC_SPY_GAME_SCORE							            60046

Open(MSharedCommandTable.cpp) <br>
Find <br>

	END_CMD_DESC();
	
Add Above <br>


	////////// Spy Mode //////////
	C(MC_SPY_STAGE_ACTIVATE_MAP, "Ban/UnBan Spy Map", "Mark Spy Mode map as (de)activated.", MCDT_MACHINE2MACHINE)
		P(MPT_INT, "Map ID")
		P(MPT_BOOL, "Exclude")

	C(MC_SPY_STAGE_REQUEST_BAN_MAP_LIST, "Request Spy Map List", "Keep client's spy ban map list correct.", MCDT_MACHINE2MACHINE)

	C(MC_SPY_STAGE_BAN_MAP_LIST, "Spy Map List", "Sync map list info of Spy Mode between Client and Server.", MCDT_MACHINE2MACHINE)
		P(MPT_BLOB, "Map IDs")

	C(MC_SPY_STAGE_REQUEST_START, "Start Spy Mode stage", "Start Spy Mode game.", MCDT_MACHINE2MACHINE)
		P(MPT_BLOB, "Map IDs")

	C(MC_SPY_GAME_INFO, "Spy Mode game info", "Refresh Spy Mode status of client.", MCDT_MACHINE2MACHINE)
		P(MPT_BLOB, "Spy UIDs")
		P(MPT_BLOB, "Spy-side Items")
		P(MPT_UINT, "Spy bonus HP/AP")
		P(MPT_BLOB, "Tracker-side Items")

	C(MC_SPY_GAME_RESULT, "Spy Mode game result", "Spy Mode round finish info to client.", MCDT_MACHINE2MACHINE)
		P(MPT_BLOB, "EXP Bonus Info")

	C(MC_SPY_GAME_SCORE, "Spy Mode game score", "Client/Server Sync Spy Mode character score info.", MCDT_MACHINE2MACHINE)
		P(MPT_BLOB, "Char Score Info")

Open(ZCommandUDPHackShield.cpp) <br>
Find <br>

	AddDeniedCommand(MC_MATCH_RESPONSE_MONSTER_BIBLE_INFO);
	AddDeniedCommand(MC_MATCH_FLAG_EFFECT);
	AddDeniedCommand(MC_MATCH_FLAG_CAP);
	AddDeniedCommand(MC_MATCH_FLAG_STATE);

Add under <br>

	AddDeniedCommand(MC_SPY_STAGE_ACTIVATE_MAP);
	AddDeniedCommand(MC_SPY_STAGE_REQUEST_BAN_MAP_LIST);
	AddDeniedCommand(MC_SPY_STAGE_BAN_MAP_LIST);
	AddDeniedCommand(MC_SPY_STAGE_REQUEST_START);
	AddDeniedCommand(MC_SPY_GAME_INFO);
	AddDeniedCommand(MC_SPY_GAME_RESULT);
	AddDeniedCommand(MC_SPY_GAME_SCORE);


























