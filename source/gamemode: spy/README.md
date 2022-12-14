Gamemode: Spymode <br>
CSCommon/Spymode files <br>
- MMatchRuleSpy.cpp
- MMatchRuleSpy.h
- MMatchServer_Spy.cpp
- MMatchSpyMap.cpp
- MMatchSpyMap.h
- MMatchSpyMode.cpp
- MMatchSpyMode.h

Gunz/Spymode files <br>
- ZRuleSpy.cpp
- ZRuleSpy.h

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

          if (m_StageSetting.GetGameType() == MMATCH_GAMETYPE_SPY)
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

Find <br>

	if (m_bTeamPlay && !bInfectedMode)
	{
	
Replace <br>

	if (m_bTeamPlay && !bSpyMode && !bInfectedMode)
	{

Find <br>

	if( pSItem->m_nTeam == 0)

Replace <br>

	if (pSItem->m_nTeam == 0 || bSpyMode)

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

				if(!ZApplication::GetStageInterface()->GetIsRelayMapRegisterComplete())
				{
					ZGetGameInterface()->ShowMessage(MSG_GAME_RELAYMAP_CONFIRM_BUTTON_PUSH);
					return true;
				}
			
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

		MFont* pFont = MFontManager::Get("FONTb11b");
		if (pFont == NULL)
			//_ASSERT(0);
		pDC->SetFont(pFont);

Replace <br>

		MFont* pFont = MFontManager::Get("FONTb11b");
		if (pFont == NULL)
			//_ASSERT(0);
			pDC->SetFont(pFont);
		if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_SPY)
			TextRelative(pDC, 0.5f, 763.0f / 800.0f, szName, true);


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

Open(MMatchStageSetting.cpp) <br>
Find <br>

	#include "stdafx.h"
	#include "MMatchStageSetting.h"
	#include "MMatchServer.h"
	#include "MMatchObject.h"

Add <br>

	#include "MMatchSpyMap.h"

Add ZRuleSpy.cpp & ZRuleSpy.h in Gunz Project<br>

Open(ZReplay.cpp) <br>
Find <br>

	#include "ZRuleDuel.h"
	#include "ZRuleDuelTournament.h"
	#include "ZRuleDeathMatch.h"
	#include "ZWorldItem.h"

Add <br>

	#include "ZRuleSpy.h"

Open(ZInterfaceListener.cpp) <br>
Find <br>

	#include "ZShopEquipInterface.h"
	#include "ZShopEquipListbox.h"

	#ifdef LOCALE_NHNUSA
	#include "ZNHN_USA_Report.h"
	#endif

Add <br>

	#include "../CSCommon/MMatchSpyMode.h"
	#include "../CSCommon/MMatchSpyMap.h"

Open(ZRule.cpp) <br>
Find <br>

	#include "ZRuleBerserker.h"
	#include "ZRuleDuel.h"
	#include "ZRuleDuelTournament.h"

Add <br>

	#include "ZRuleSpy.h"

Open(ZStageInterface.cpp) <br>
Find <br>

	#include "ZItemSlotView.h"
	#include "ZMessages.h"
	#include "ZLanguageConf.h"

Add <br>

	#include "../CSCommon/MMatchSpyMap.h"

Find <br>

	MAnimation* pAniMapImg = (MAnimation*)pResource->FindWidget( "Stage_MapNameBG");
	bool bQuestUI = false;

Replace <br>

	MAnimation* pAniMapImg = (MAnimation*)pResource->FindWidget( "Stage_MapNameBG");
	bool bQuestUI = false, bSpyUI = false;

Find <br>

	pPicture = (MPicture*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "Stage_RelayMapListBG");
	if ( pPicture)
		pPicture->SetBitmap( NULL);

Add under <br>

	pPicture = (MPicture*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Stage_SpyBanMapListBG");
	if (pPicture)
		pPicture->SetBitmap(NULL);

Find <br>

	if (m_pRelayMapListFrameImg != NULL)
	{
		delete m_pRelayMapListFrameImg;
		m_pRelayMapListFrameImg = NULL;
	}

Add Under <br>

	if (m_pSpyBanMapListFrameImg != NULL)
	{
		delete m_pSpyBanMapListFrameImg;
		m_pSpyBanMapListFrameImg = NULL;
	}

Find <br>

	m_bRelayMapRegisterComplete = true;
	m_bEnableWidgetByRelayMap = true;

Add under <br>

	m_pSpyBanMapListFrameImg = NULL;
	m_nSpyBanMapListFramePos = 0;

Open(ZMessages.h) <br>
Find <br>

	#define MSG_BONUS_REWARD_GET						2060	///< [xxxÀÌº¥Æ®] ¤·¤·¤·´ÔÀÌ ¤·¤·¤·¸¦ ¹ÞÀ¸¼Ì½À´Ï´Ù.
	#define MSG_BONUS_REWARD_REMAIN						2061	///< ³²Àº º¸³Ê½º ±âÈ¸ : 00È¸
	#define MSG_BONUS_REWARD_NOCHANCE					2062	///< [xxxÀÌº¥Æ®] ³²Àº º¸³Ê½º ±âÈ¸°¡ ¾ø¾î º¸³Ê½º¸¦ ¹ÞÁö ¸øÇß½À´Ï´Ù.
	#define MSG_BONUS_REWARD_RESET						2063	///< ¤·¤·¿¡ º¸³Ê½º ±âÈ¸°¡ ÃæÀüµË´Ï´Ù.

Add under <br>

	#define MSG_SPY_WAITING_FOR_PLAYERS					2200
	#define MSG_SPY_SPYSIDE_SPY_LOCATION_OPEN			2201
	#define MSG_SPY_TRACKERSIDE_SPY_LOCATION_OPEN		2202
	#define MSG_SPY_TIP_FROZEN_TRAP						2203
	#define MSG_SPY_TIP_FLASH_BANG						2204
	#define MSG_SPY_TIP_SMOKE							2205
	#define MSG_SPY_TIP_STUN_GRENADE					2206
	#define MSG_SPY_TIP_LANDMINE						2207
	#define MSG_SPY_TIP_SPYSIDE							2208
	#define MSG_SPY_TIP_TRACKERSIDE						2209
	#define MSG_SPY_BAN_MAPLIST_UPDATE					2210
	#define MSG_SPY_AUTO_UNBAN_MAP						2211
	#define MSG_SPY_WON_POINT							2212
	#define MSG_SPY_WORD_PLAYERS						2213
	#define MSG_SPY_PARTICIPATION_GUIDANCE				2214
	#define MSG_SPY_EXP_BONUS							2215
	#define MSG_SPY_IDENTITY							2216
	#define MSG_SPY_NO_SUITABLE_MAP						2217

Open(ZGameClient.cpp) <br>
Find <br>

		} else if (nType == MATCHCACHEMODE_REMOVE) {
			for(int i=0; i<nCount; i++){
				MMatchObjCache* pCache = (MMatchObjCache*)MGetBlobArrayElement(pBlob, i);
				pList->DelPlayer(pCache->GetUID());

				ZGetPlayerManager()->RemovePlayer( pCache->GetUID());
			}

			// Ãß¹æ ÈÄ¿¡ Ã»/È«ÆÀÀÇ »ç¶÷ ¼ö¸¦ ´Ù½Ã ±¸ÇÑ´Ù.(µ¿È­´Ï°¡ Ãß°¡)
			ZApplication::GetGameInterface()->UpdateBlueRedTeam();
		}

Replace <br>

		} else if (nType == MATCHCACHEMODE_REMOVE) {
			for(int i=0; i<nCount; i++){
				MMatchObjCache* pCache = (MMatchObjCache*)MGetBlobArrayElement(pBlob, i);
				pList->DelPlayer(pCache->GetUID());
				ZGetPlayerManager()->RemovePlayer( pCache->GetUID());
			}
			ZApplication::GetGameInterface()->UpdateBlueRedTeam();
			ZApplication::GetStageInterface()->CreateSpyBanMapList();
		}

Find <br>

	bool bEndRelayMap = !bIsRelayMapUnFinish;
	ZApplication::GetStageInterface()->SetEnableWidgetByRelayMap(bEndRelayMap);

	ZPostRequestStageSetting(ZGetGameClient()->GetStageUID());	
	}

Replace <br>

	bool bEndRelayMap = !bIsRelayMapUnFinish;
	ZApplication::GetStageInterface()->SetEnableWidgetByRelayMap(bEndRelayMap);

	ZPostRequestStageSetting(ZGetGameClient()->GetStageUID());	
	ZPostRequestSpyBanMapList();
	}

Open(ZGameInterface.cpp) <br>
Find <br>

	SetListenerWidget("Stage_RelayMap_OK_Button", ZGetRelayMapOKButtonListener());
	SetListenerWidget("Stage_RelayMapBoxOpen", ZStageRelayMapBoxOpen());
	SetListenerWidget("Stage_RelayMapBoxClose", ZStageRelayMapBoxClose());

Add under <br>

	SetListenerWidget("Stage_SpyBanMapList", ZGetSpyBanMapListListener());
	SetListenerWidget("Stage_SpyBanMapBoxOpen", ZStageSpyBanMapBoxOpen());
	SetListenerWidget("Stage_SpyBanMapBoxClose", ZStageSpyBanMapBoxClose());

Find <br>

	MPicture* pPicture = (MPicture*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Stage_StripBottom");
	if (pPicture != NULL)	pPicture->SetBitmapColor(0xFFFFFFFF);
	pPicture = (MPicture*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Stage_StripTop");
	if (pPicture != NULL)	pPicture->SetBitmapColor(0xFFFFFFFF);

	ZPostRequestStageSetting(ZGetGameClient()->GetStageUID());
	SerializeStageInterface();

Add under <br>

	ZPostRequestSpyBanMapList();

Find <br>

		MListBox* pRelayMapListBox = (MListBox*)m_IDLResource.FindWidget("Stage_RelayMapListbox");
		if (pRelayMapListBox)
		{
			pRelayMapListBox->m_FontAlign = MAM_LEFT;
			pRelayMapListBox->AddField("ICON", 23);
			pRelayMapListBox->AddField("NAME", 170);
			pRelayMapListBox->SetItemHeight(23);
			pRelayMapListBox->SetVisibleHeader(false);
			pRelayMapListBox->m_bNullFrame = true;
		}
	}
	
Add under <br>

	MListBox* pSpyBanMapListBox = (MListBox*)m_IDLResource.FindWidget("Stage_SpyBanMapList");
	if (pSpyBanMapListBox)
	{
		pSpyBanMapListBox->m_FontAlign = MAM_LEFT;
		pSpyBanMapListBox->AddField("ICON", 23);
		pSpyBanMapListBox->AddField("NAME", 170);
		pSpyBanMapListBox->SetItemHeight(23);
		pSpyBanMapListBox->SetVisibleHeader(false);
		pSpyBanMapListBox->m_bNullFrame = true;
	}

Find <br>

			if ( rect.x != nEndPos)
			{
				int nNewPos = rect.x + ( nEndPos - rect.x) * 0.25;
				if ( nNewPos == rect.x)		// not changed
					rect.x = nEndPos;
				else						// changed
					rect.x = nNewPos;

				pWidget->SetBounds( rect);

				if ( rect.x == 0)
				{
					pWidget = pRes->FindWidget( "Stage_CharacterInfo");
					if ( pWidget)
						pWidget->Enable( false);
				}
			}
		}
	}

Replace <br>

			if (rect.x != nEndPos)
			{
				int nNewPos = rect.x + (nEndPos - rect.x) * 0.25;
				if (nNewPos == rect.x)		// not changed
					rect.x = nEndPos;
				else						// changed
					rect.x = nNewPos;

				pWidget->SetBounds(rect);

				if (rect.x == 0)
				{
					pWidget = pRes->FindWidget("Stage_CharacterInfo");
					if (pWidget)
						pWidget->Enable(false);
				}
			}
			pWidget = pRes->FindWidget("Stage_SpyBanMapListView");
			if (!pWidget)
				return;

			nEndPos = ZApplication::GetStageInterface()->m_nSpyBanMapListFramePos;
			rect = pWidget->GetRect();
			if (rect.x != nEndPos)
			{
				int nNewPos = rect.x + (nEndPos - rect.x) * 0.25;
				if (nNewPos == rect.x)
					rect.x = nEndPos;
				else
					rect.x = nNewPos;

				pWidget->SetBounds(rect);

				if (rect.x == 0)
				{
					pWidget = pRes->FindWidget("Stage_CharacterInfo");
					if (pWidget)
						pWidget->Enable(false);
				}
			}
		}
	}

Open(ZPost.h) <br>
Find <br>

	inline void ZPostRequestUseSpendableBuffItem( const MUID& uid )
	{
		ZPOSTCMD1( MC_MATCH_REQUEST_USE_SPENDABLE_BUFF_ITEM, MCmdParamUID(uid) );
	}

Add <br>

	inline void ZPostRequestSpyBanMapList()
	{
		ZPOSTCMD0(MC_SPY_STAGE_REQUEST_BAN_MAP_LIST);
	}

Open(ZStageInterface.h) <br>
Find <br>

	// ¸±·¹ÀÌ¸Ê ÀÏ½Ã ¸Ê ¸®½ºÆ®
	class RelayMapList : public MListItem
	{
	protected:
		char				m_szName[ 128];
		MBitmap*			m_pBitmap;

	public:
		RelayMapList();
		RelayMapList( const char* szName, MBitmap* pBitmap)
		{
			strcpy( m_szName, szName);
			m_pBitmap = pBitmap;
		}

		virtual void SetString(const char *szText)
		{
			strcpy(m_szName, szText);
		}
		virtual const char* GetString( void)
		{
			return m_szName;
		}
		virtual const char* GetString( int i)
		{
			if ( i == 1)
				return m_szName;

			return NULL;
		}
		virtual MBitmap* GetBitmap( int i)
		{
			if ( i == 0)
				return m_pBitmap;

			return NULL;
		}

		const char* GetItemName( void)		{ return m_szName; }
	};

Add under <br>

	class SpyBanMapList : public RelayMapList
	{
	protected:
		int					m_nMapID;
		MCOLOR				m_Color;

	public:
		SpyBanMapList(const char* szName, MBitmap* pBitmap, int nMapID) : RelayMapList(szName, pBitmap)
		{
			m_nMapID = nMapID;
			m_Color = MCOLOR(DEFCOLOR_MLIST_TEXT);
		}

		virtual int GetMapID()
		{
			return m_nMapID;
		}

		virtual const MCOLOR GetColor(void) { return GetColor(0); }
		virtual const MCOLOR GetColor(int i) {
			return m_Color;
		}

		virtual void SetColor(const MCOLOR& color)	{
			m_Color = color;
		}
	};

Find <br>

	// Listner
	MListener* ZGetSacrificeItemListBoxListener( void);
	MListener* ZGetRelayMapListBoxListener( void);
	MListener* ZGetMapListBoxListener( void);

Add under <br>

	MListener* ZGetSpyBanMapListListener(void);

Open(ZGame.cpp) <br>
Find <br>

	#include "ZRuleDuel.h"
	#include "ZRuleDeathMatch.h"
	#include "ZMyCharacter.h"
	#include "MMatchCRC32XORCache.h"
	#include "MMatchObjCache.h"

	#include "ZModule_HealOverTime.h"

Add under <br>

	#include "ZRuleSpy.h"

Open(MMatchStage.cpp) <br>
Find <br>

	#include "MMatchRuleBerserker.h"
	#include "MMatchRuleDuel.h"
	#include "MMatchRuleDuelTournament.h"
	#include "MMatchCRC32XORCache.h"

Add <br>

	#include "../CSCommon/MMatchRuleSpy.h"

Open(MMatchRule.cpp) <br>
Find <br>

	#include "MBlobArray.h"
	#include "MMatchConfig.h"
	#include "MMatchEventFactory.h"

Add under <br>

	#include "MMatchSpyMode.h"

Open(ZCombatInterface.cpp) <br>
Find <br>

	void ZCombatInterface::DrawAllPlayerName(MDrawContext* pDC)
	{

Add under <br>

	void ZCombatInterface::DrawSpyName(MDrawContext* pDC)
	{
		ZCharacter* pTargetCharacter = GetTargetCharacter();
		if (!pTargetCharacter) return;

		bool bCountDown = ZGetGame()->GetMatch()->GetRoundState() == MMATCH_ROUNDSTATE_COUNTDOWN;
		bool bOpen = ZGetGame()->GetMatch()->GetRoundState() == MMATCH_ROUNDSTATE_PLAY && m_bSpyLocationOpened;

		for (ZCharacterManager::iterator itor = ZGetGame()->m_CharacterManager.begin();
			itor != ZGetGame()->m_CharacterManager.end(); ++itor)
		{
			rvector pos, screen_pos;
			ZCharacter* pCharacter = (*itor).second;
			if (!pCharacter->IsVisible()) continue;
			if (pCharacter->IsDie()) continue;
			if (pCharacter == pTargetCharacter) continue;

			if ((!bCountDown) && (!bOpen || pTargetCharacter->GetTeamID() == MMT_RED))
				if (pCharacter->GetTeamID() != pTargetCharacter->GetTeamID())
					continue;

			pos = pCharacter->GetPosition();
			RVisualMesh* pVMesh = pCharacter->m_pVMesh;
			RealSpace2::rboundingbox box;

			if (pVMesh == NULL) continue;

			box.vmax = pos + rvector(50.f, 50.f, 190.f);
			box.vmin = pos + rvector(-50.f, -50.f, 0.f);

			if (isInViewFrustum(&box, RGetViewFrustum()))
			{
				if (ZGetCamera()->GetLookMode() == ZCAMERA_MINIMAP) {
					rvector pos = pCharacter->GetPosition();
					pos.z = 0;
					screen_pos = RGetTransformCoord(pos);
				}
				else
					screen_pos = RGetTransformCoord(pCharacter->GetVisualMesh()->GetHeadPosition() + rvector(0, 0, 30.f));

				MFont *pFont = NULL;

				if (pCharacter->IsAdminName()) {
					pFont = MFontManager::Get("FONTa12_O1Org");
					pDC->SetColor(MCOLOR(ZCOLOR_ADMIN_NAME));
				}
				else {
					if (bCountDown)
						pFont = MFontManager::Get("FONTa12_O1Blr");
					else if (pTargetCharacter->GetTeamID() != pCharacter->GetTeamID())
						pFont = MFontManager::Get("FONTa12_O1Red");
					else
						pFont = MFontManager::Get("FONTa12_O1Blr");

					pDC->SetColor(MCOLOR(0xFF2669B2));
				}

				pDC->SetBitmap(NULL);

				if (pFont == NULL) _ASSERT(0);
				pDC->SetFont(pFont);
				int x = screen_pos.x - pDC->GetFont()->GetWidth(pCharacter->GetUserName()) / 2;

				pDC->Text(x, screen_pos.y - 12, pCharacter->GetUserName());

				if (bOpen && pTargetCharacter->GetTeamID() == MMT_BLUE && pCharacter->GetTeamID() == MMT_RED)
				{
					const int nIconWidth = 48, nIconHeight = 48;

					pDC->SetBitmap((MBitmap*)m_pSpyIcon);
					pDC->Draw(screen_pos.x - nIconWidth / 2, screen_pos.y - nIconHeight / 2 - 34, nIconWidth, nIconHeight);
				}
			}
		}
	}

Open(ZCombatInterface.h) <br>
Find <br>

	void DrawFriendName(MDrawContext* pDC);			// °°ÀºÆí ÀÌ¸§
	void DrawEnemyName(MDrawContext* pDC);			// Àû ÀÌ¸§
	void DrawAllPlayerName(MDrawContext* pDC);

Add under <br>

	void DrawSpyName(MDrawContext* pDC);


Open(ZInterfaceListener.cpp) <br>
Find <br>

	BEGIN_IMPLEMENT_LISTENER( ZGetRelayMapOKButtonListener, MBTN_CLK_MSG)
		ZApplication::GetStageInterface()->PostRelayMapInfoUpdate();
	END_IMPLEMENT_LISTENER();

Add under <br>

	BEGIN_IMPLEMENT_LISTENER(ZStageSpyBanMapBoxOpen, MBTN_CLK_MSG)
	ZApplication::GetStageInterface()->OpenSpyBanMapBox();
	END_IMPLEMENT_LISTENER()

Open(ZInterfaceListener.h) <br>
Find <br>

	DECLARE_LISTENER(ZStageRelayMapBoxClose)
	DECLARE_LISTENER(ZGetRelayMapOKButtonListener)

Add under <br>

	DECLARE_LISTENER(ZStageSpyBanMapBoxOpen)
	DECLARE_LISTENER(ZStageSpyBanMapBoxClose)

Open(ZPost.h) <br>
Find <br>

	inline void ZPostRequestGamble( const MUID& uid)
	{
		ZPOSTCMD1( MC_MATCH_REQUEST_GAMBLE, MCmdParamUID(uid) );
	}

Add under <br>

	inline void ZPostSpyStageStart(void* pMapListBlob)
	{
		ZPOSTCMD1(MC_SPY_STAGE_REQUEST_START, MCmdParamBlob(pMapListBlob, MGetBlobArraySize(pMapListBlob)));
	}

Open(ZCharacter.cpp) <br>
Find <br>

	void ZCharacter::ApplyBuffEffect()
	{

	}

Add under <br>

	void ZCharacter::SpyHealthBonus(int nHPAP)
	{
		const MTD_CharInfo* pCharInfo = &m_MInitialInfo.Ref();

		float fAddedAP = DEFAULT_CHAR_AP;
		for (int i = 0; i < MMCIP_END; i++) {
			if (!m_Items.GetItem(MMatchCharItemParts(i))->IsEmpty()) {
				if (m_Items.GetItem(MMatchCharItemParts(i))->GetDesc()->m_nAP.Ref() > 40) {
					m_Items.GetItem(MMatchCharItemParts(i))->GetDesc()->m_nAP.Ref() = 0;
				}
				fAddedAP += m_Items.GetItem(MMatchCharItemParts(i))->GetDesc()->m_nAP.Ref();
			}
		}

		float fAddedHP = DEFAULT_CHAR_HP;
		for (int i = 0; i < MMCIP_END; i++) {
			if (!m_Items.GetItem(MMatchCharItemParts(i))->IsEmpty()) {
				fAddedHP += m_Items.GetItem(MMatchCharItemParts(i))->GetDesc()->m_nHP.Ref();
			}
		}

		m_Property.fMaxAP.Set_CheckCrc(pCharInfo->nAP + fAddedAP + (float)nHPAP);
		m_Property.fMaxHP.Set_CheckCrc(pCharInfo->nHP + fAddedHP + (float)nHPAP);


		m_fPreMaxHP = pCharInfo->nHP + fAddedHP;
		m_fPreMaxAP = pCharInfo->nAP + fAddedAP;


		InitHPAP();
	}

	void ZCharacter::InitSpyWeaponBullet()
	{
		for (int i = MMCIP_MELEE; i <= MMCIP_CUSTOM2; i++)
		{
			ZItem* pItem = m_Items.GetItem((MMatchCharItemParts)i);
			if (pItem->IsEmpty()) continue;

			if (MMatchSpyMode::IsSpyItem((int)pItem->GetDescID()))
			{
				pItem->SetBulletCurrMagazine(pItem->GetItemCount());
				pItem->SetBulletSpare(pItem->GetBulletCurrMagazine());
			}
		}
	}

	void ZCharacter::DistributeSpyItem(vector<MMatchSpyItem> &vt)
	{
		if (GetTeamID() == MMT_RED)
		{
			m_Items.EquipItem(MMCIP_MELEE, 0, 0);
			m_Items.EquipItem(MMCIP_PRIMARY, 0, 0);
			m_Items.EquipItem(MMCIP_SECONDARY, 0, 0);
			m_Items.EquipItem(MMCIP_CUSTOM1, 0, 0);
			m_Items.EquipItem(MMCIP_CUSTOM2, 0, 0);
		}
		else
		{
			m_Items.EquipItem(MMCIP_CUSTOM1, 0, 0);
			m_Items.EquipItem(MMCIP_CUSTOM2, 0, 0);
		}

		for (vector<MMatchSpyItem>::iterator i = vt.begin(); i != vt.end(); i++)
		{
			MMatchSpyItem* pItem = &(*i);

			MMatchCharItemParts nParts = MMCIP_END;
			switch (pItem->nItemID)
			{
			case 601001:
				nParts = MMCIP_SECONDARY;	break;
			case 601002:
				nParts = MMCIP_CUSTOM2;		break;
			case 601003:
				nParts = MMCIP_CUSTOM1;		break;
			case 601004:
				nParts = MMCIP_CUSTOM1;		break;
			case 601005:
				nParts = MMCIP_CUSTOM2;		break;
			case 601006:
				nParts = MMCIP_MELEE;		break;
			default:
				_ASSERT(0);					break;
			}

			m_Items.EquipItem(nParts, pItem->nItemID, pItem->nItemCount, false);
		}

		InitSpyWeaponBullet();

		ChangeWeapon(MMCIP_MELEE, true);
	}

	void ZCharacter::TakeoutSpyItem()
	{
		const MTD_CharInfo* pCharInfo = &m_MInitialInfo.Ref();

		for (int i = 0; i < MMCIP_END; i++)
		{
			m_Items.EquipItem(MMatchCharItemParts(i), pCharInfo->nEquipedItemDesc[i], pCharInfo->nEquipedItemCount[i]);
		}

		InitItemBullet();

		ChangeWeapon(MMCIP_MELEE, true);
	}

Find <br>

	void ZCharacter::ChangeWeapon(MMatchCharItemParts nParts, bool bReSelect)
	{

Replace <br>

	void ZCharacter::ChangeWeapon(MMatchCharItemParts nParts, bool bReSelect)
	{
		if(!bReSelect){
			if(m_Items.GetSelectedWeaponParts()==nParts) 
				return;
		}

		if( nParts < 0 || nParts > MMCIP_END )
			return;

		if (m_Items.GetItem(nParts) == NULL) 
			return;

		if (m_Items.GetItem(nParts)->GetDesc() == NULL)
			return;

		if (ZGetGame()->GetMatch()->IsRuleGladiator()){
			if ((nParts == MMCIP_PRIMARY) || (nParts == MMCIP_SECONDARY))
				return;
		}

		MMatchCharItemParts BackupParts = m_Items.GetSelectedWeaponParts();
		m_Items.SelectWeapon(nParts);

		if(m_Items.GetSelectedWeapon()==NULL) 
			return;

		MMatchItemDesc* pSelectedItemDesc = m_Items.GetSelectedWeapon()->GetDesc();
		if (pSelectedItemDesc==NULL) {
			m_Items.SelectWeapon(BackupParts);
		//	mlog("¼±ÅÃµÈ ¹«±âÀÇ µ¥ÀÌÅÍ°¡ ¾ø´Ù.\n");
		//	mlog("ZCharacter ¹«±â»óÅÂ¿Í RVisualMesh ÀÇ ¹«±â»óÅÂ°¡ Æ²·ÁÁ³´Ù\n");
			return;
		}

		OnChangeWeapon(pSelectedItemDesc->m_pMItemName->Ref().m_szMeshName);

		if(nParts!=MMCIP_MELEE)
		{
			m_bCharged->Set_CheckCrc(false);
		}
	}


Open(ZCharacter.h) <br>
Find <br>

	const MTD_CharInfo* GetCharInfo() const { return &m_MInitialInfo.Ref(); }

Add under <br>

	public:
		ZSkill m_Skill;
		void SpyHealthBonus(int nHPAP);

		void InitSpyWeaponBullet();

		virtual void DistributeSpyItem(vector<MMatchSpyItem> &vt);
		void TakeoutSpyItem();

Find <br>

	#include "MMatchObject.h"
	#include "RCharCloth.h"
	#include "ZFile.h"
	#include "Mempool.h"

	#include "ZModule_HPAP.h"

	#include <list>
	#include <string>

Add under <br>

	#include "../CSCommon/MMatchSpyMode.h"

Find <br>

	enum ZC_SHOT_SP_TYPE {
		ZC_WEAPON_SP_NONE = 0,

		// grenade type
		ZC_WEAPON_SP_GRENADE,
		ZC_WEAPON_SP_ROCKET,
		ZC_WEAPON_SP_FLASHBANG,
		ZC_WEAPON_SP_SMOKE,
		ZC_WEAPON_SP_TEAR_GAS,

Add under <br>

	ZC_WEAPON_SP_FLASHBANG_SPY,
	ZC_WEAPON_SP_SMOKE_SPY,
	ZC_WEAPON_SP_TRAP_SPY,
	ZC_WEAPON_SP_STUN_SPY,

Find <br>

	void ChangeWeapon(MMatchCharItemParts nParts);

Replace <br>

	void ChangeWeapon(MMatchCharItemParts nParts, bool bReSelect = false);


Open(ZCharacterItem.h) <br>
Find <br>
	
	bool EquipItem(MMatchCharItemParts parts, int nItemDescID, int nItemCount = 1);


Replace <br>

	bool EquipItem(MMatchCharItemParts parts, int nItemDescID, int nItemCount = 1, bool bValidationCheck = true);

Open(ZCharacterItem.cpp) <br>
Find <br>

	bool ZCharacterItem::EquipItem(MMatchCharItemParts parts, int nItemDescID, int nItemCount, bool bValidationCheck)
	{


Replace <br>

	bool ZCharacterItem::EquipItem(MMatchCharItemParts parts, int nItemDescID, int nItemCount, bool bValidationCheck)
	{
		if (nItemDescID == 0) {
			m_Items[parts].Create(MUID(0,0), NULL, 0);
			return true;
		}

		MMatchItemDesc* pDesc = MGetMatchItemDescMgr()->GetItemDesc(nItemDescID);

		if (pDesc == NULL) { return false; }
		if (!Confirm(parts, pDesc)) {
			return false;
		}

		m_Items[parts].Create(MUID(0,0), pDesc, 1, nItemCount);
		return true;
	}

Open(MErrorTable.h) <br>
Find <br>

	#define MERR_HE_IS_NOT_READY								200008 //  '%s'´ÔÀº ÁØºñ°¡ ¾ÈµÇ¾ú½À´Ï´Ù.

Add <br>

	#define MERR_SPY_LACKING_PLAYERS							200009 /// <SpyMode>

Open(ZPost.h)
Find <br>

	inline void ZPostSpyStageStart(void* pMapListBlob)
	{
		ZPOSTCMD1(MC_SPY_STAGE_REQUEST_START, MCmdParamBlob(pMapListBlob, MGetBlobArraySize(pMapListBlob)));
	}

Add <br>

	inline void ZPostActivateSpyMap(int nMapID, bool bExclude)
	{
		ZPOSTCMD2(MC_SPY_STAGE_ACTIVATE_MAP, MCmdParamInt(nMapID), MCmdParamBool(bExclude));
	}

Open(ZCombatInterface.cpp) <br>
Find <br>

	void ZCombatInterface::OnRestore()
	{
		ZCharacterView* pCharView = GetWidgetCharViewLeft();
		if (pCharView)
			pCharView->OnRestore();
		pCharView = GetWidgetCharViewRight();
		if (pCharView)
			pCharView->OnRestore();
		pCharView = GetWidgetCharViewResult();
		if (pCharView)
			pCharView->OnRestore();
	}

Add under <br>


	////////// Spy mode ////////// 
	void ZCombatInterface::OnSpyCreate()
	{
		CreateSpyWaitInterface();
	}

	void ZCombatInterface::OnSpyDestroy()
	{
		ZIDLResource* pIDLResource = ZApplication::GetGameInterface()->GetIDLResource();

		MFrame* pFrame = (MFrame*)pIDLResource->FindWidget("CombatSpyInfo");
		if (pFrame)
			pFrame->Show(false);

		ZBmNumLabel* pNumLabel = (ZBmNumLabel*)pIDLResource->FindWidget("Spy_CountDownTime");
		if (pNumLabel)
			pNumLabel->Show(false);

		pNumLabel = (ZBmNumLabel*)pIDLResource->FindWidget("Spy_CountDownTime_Red");
		if (pNumLabel)
			pNumLabel->Show(false);

		SetSpyEventMsg(NULL);
		SetSpyTip(NULL);
		SetSpyNotice(NULL);
	}

	void ZCombatInterface::CreateSpyGameInterface()
	{
		ZIDLResource* pIDLResource = ZApplication::GetGameInterface()->GetIDLResource();

		MFrame* pFrame = (MFrame*)pIDLResource->FindWidget("CombatSpyInfo");
		if (pFrame)
			pFrame->Show(true);

		ZBmNumLabel* pNumLabel = (ZBmNumLabel*)pIDLResource->FindWidget("Spy_CountDownTime");
		if (pNumLabel)
			pNumLabel->Show(true);

		pNumLabel = (ZBmNumLabel*)pIDLResource->FindWidget("Spy_CountDownTime_Red");
		if (pNumLabel)
			pNumLabel->Show(false);

		SetSpyEventMsg(NULL);
		SetSpyTip(NULL);
		SetSpyNotice(NULL);

		m_bSpyLocationOpened = false;
	}

	void ZCombatInterface::CreateSpyWaitInterface()
	{
		ZIDLResource* pIDLResource = ZApplication::GetGameInterface()->GetIDLResource();

		MFrame* pFrame = (MFrame*)pIDLResource->FindWidget("CombatSpyInfo");
		if (pFrame)
			pFrame->Show(true);

		ZBmNumLabel* pNumLabel = (ZBmNumLabel*)pIDLResource->FindWidget("Spy_CountDownTime");
		if (pNumLabel)
			pNumLabel->Show(false);

		pNumLabel = (ZBmNumLabel*)pIDLResource->FindWidget("Spy_CountDownTime_Red");
		if (pNumLabel)
			pNumLabel->Show(false);

		SetSpyEventMsg(NULL);

		char minPlayers[32];
		sprintf(minPlayers, "%d", MMatchSpyMode::GetMinPlayers());

		char tip[256];
		ZTransMsg(tip, MSG_SPY_WAITING_FOR_PLAYERS, 4, minPlayers);

		SetSpyTip(tip);

		SetSpyNotice("Spy_Notice_Wait_OtherPlayer.png");

		m_bSpyLocationOpened = false;
	}

	void ZCombatInterface::OnSpyUpdate(float fElapsed)
	{
		DWORD dwNowTime = timeGetTime();

		int nRemainedTime = (int)(m_dwSpyTimer - dwNowTime);
		SetSpyTimeLimitValue((DWORD)((nRemainedTime < 0) ? (0) : (nRemainedTime)));

		if (ZGetGame())
		{
			if (ZGetGame()->GetMatch()->GetRoundState() == MMATCH_ROUNDSTATE_PLAY)
			{
				const MMatchSpyMapNode* pSpyMap = MMatchSpyMap::GetMap(ZGetGame()->GetMatch()->GetMapName());
				_ASSERT(pSpyMap != NULL);

				if (((nRemainedTime / 1000) <= pSpyMap->nSpyOpenTime))
				{
	#define SPYTIME_FLASHING_INTERVAL	300

					bool bRedTime = ((nRemainedTime % (SPYTIME_FLASHING_INTERVAL * 2)) < SPYTIME_FLASHING_INTERVAL);

					ZBmNumLabel* pNumLabel = (ZBmNumLabel*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Spy_CountDownTime");
					if (pNumLabel)
						pNumLabel->Show(!bRedTime);

					pNumLabel = (ZBmNumLabel*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Spy_CountDownTime_Red");
					if (pNumLabel)
						pNumLabel->Show(bRedTime);

					if (!m_bSpyLocationOpened)
					{
						if (ZGetScreenEffectManager())
							ZGetScreenEffectManager()->AddScreenEffect("spy_location");

						m_bSpyLocationOpened = true;

						SetDefaultSpyTip(ZGetGame()->m_pMyCharacter->GetTeamID());
					}
				}
			}
		}

		if (m_bSpyNoticePlaying)
		{
			MPicture* pPicture = (MPicture*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Spy_Notice");
			if (pPicture)
			{
	#define SPYNOTICE_PLAYER_WAITTIME	1000
	#define SPYNOTICE_PLAYER_FADETIME	300
	#define SPYNOTICE_PLAYER_SHOWTIME	3000

				/*
				DWORD dwPlayTime = dwNowTime - m_dwSpyNoticePlayStartedTime;

				if(dwPlayTime < SPYNOTICE_PLAYER_WAITTIME)
				{
				pPicture->SetOpacity(0);
				}
				else if(dwPlayTime < (SPYNOTICE_PLAYER_WAITTIME + SPYNOTICE_PLAYER_FADETIME))
				{
				float fOpacity = ((float)dwPlayTime / ((float)255 / (float)SPYNOTICE_PLAYER_FADETIME));
				if(fOpacity < 0.f) fOpacity = 0.f;

				pPicture->SetOpacity((unsigned char)fOpacity);
				}
				else if(dwPlayTime < (SPYNOTICE_PLAYER_WAITTIME + SPYNOTICE_PLAYER_FADETIME + SPYNOTICE_PLAYER_SHOWTIME))
				{
				pPicture->SetOpacity(255);
				}
				else if(dwPlayTime < (SPYNOTICE_PLAYER_WAITTIME + SPYNOTICE_PLAYER_FADETIME + SPYNOTICE_PLAYER_SHOWTIME + SPYNOTICE_PLAYER_FADETIME))
				{
				int fOpacity = (((float)SPYNOTICE_PLAYER_FADETIME - (float)dwPlayTime) / ((float)SPYNOTICE_PLAYER_FADETIME / (float)255));
				if(fOpacity > 255.f) fOpacity = 255.f;

				pPicture->SetOpacity((unsigned char)fOpacity);
				}
				else
				{
				pPicture->Show(false);
				pPicture->SetBitmap(NULL);
				}
				*/

				DWORD dwPlayTime = dwNowTime - m_dwSpyNoticePlayStartedTime;

				if (dwPlayTime >= (SPYNOTICE_PLAYER_WAITTIME + SPYNOTICE_PLAYER_FADETIME + SPYNOTICE_PLAYER_SHOWTIME + SPYNOTICE_PLAYER_FADETIME))
				{
					pPicture->Show(false);
					pPicture->SetBitmap(NULL);
				}
				else if (dwPlayTime >= (SPYNOTICE_PLAYER_WAITTIME + SPYNOTICE_PLAYER_FADETIME + SPYNOTICE_PLAYER_SHOWTIME))
				{
					pPicture->SetOpacity(0);
				}
				else if (dwPlayTime >= (SPYNOTICE_PLAYER_WAITTIME + SPYNOTICE_PLAYER_FADETIME))
				{
					pPicture->SetOpacity(255);
				}
			}
		}
	}

	void ZCombatInterface::OnSpyDraw(MDrawContext* pDC)
	{
		if (!ZGetGame())
		{
			_ASSERT(0);
			return;
		}

		if (ZGetGame()->GetMatch()->GetRoundState() == MMATCH_ROUNDSTATE_PLAY)
		{
			int nElapsedTime = (int)ZGetGame()->GetMatch()->GetRemaindTime();

			if (nElapsedTime >= 2500 && nElapsedTime < 7500)
			{
				if (!m_Observer.IsVisible())
				{
					MFont* pFont = MFontManager::Get("FONTa12_O2Wht");
					_ASSERT(pFont != NULL);

					pDC->SetFont(pFont);
					pDC->Text(MRECT(MGetWorkspaceWidth() / 2, MGetWorkspaceHeight() / 2, 0, 0), ZMsg(MSG_SPY_IDENTITY), MAM_HCENTER | MAM_VCENTER);

					int nFontHeight = pFont->GetHeight();

					pFont = MFontManager::Get("FONTa12_O1Red");
					_ASSERT(pFont != NULL);

					char szSpyName[256] = "";

					for (ZCharacterManager::iterator it = ZGetGame()->m_CharacterManager.begin(); it != ZGetGame()->m_CharacterManager.end(); it++)
					{
						ZCharacter* pCharacter = (*it).second;

						if (pCharacter->GetTeamID() == MMT_RED)
						{
							strcat(szSpyName, pCharacter->GetUserName());
							strcat(szSpyName, " ");
						}
					}

					int nTextLen = (int)strlen(szSpyName);

					if (szSpyName[nTextLen] == ' ')
						szSpyName[nTextLen] = '\0';

					pDC->SetFont(pFont);
					pDC->Text(MRECT(MGetWorkspaceWidth() / 2, MGetWorkspaceHeight() / 2 + nFontHeight, 0, 0), szSpyName, MAM_HCENTER | MAM_VCENTER);
				}
			}
		}
	}

	void ZCombatInterface::SetSpyTip(const char* msg)
	{
		MLabel* pLabel = (MLabel*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Spy_Tip");
		if (pLabel)
		{
			if (pLabel->GetFont())
			{
				pLabel->SetSize(pLabel->GetFont()->GetWidth(msg), 20.f / 600.f * MGetWorkspaceHeight());
				pLabel->SetPosition(MGetWorkspaceWidth() / 2 - pLabel->GetRect().w / 2, 540.f / 600.f * MGetWorkspaceHeight());
			}

			if (msg)
			{
				pLabel->SetText(msg);
				pLabel->Show(true);
			}
			else
			{
				pLabel->SetText("");
				pLabel->Show(false);
			}
		}

		MPicture* pPicture = (MPicture*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Spy_TipBG");
		if (pPicture)
		{
			if (pLabel && pLabel->GetFont())
			{
				pPicture->SetSize(pLabel->GetFont()->GetWidth(msg) * 1.04f, 20.f / 600.f * MGetWorkspaceWidth());
				pPicture->SetPosition(MGetWorkspaceWidth() / 2 - pPicture->GetRect().w / 2, 540.f / 600.f * MGetWorkspaceHeight());
			}

			if (msg)
			{
				pPicture->SetOpacity(100);
				pPicture->Show(true);
			}
			else
			{
				pPicture->SetOpacity(255);
				pPicture->Show(false);
			}
		}
	}

	void ZCombatInterface::SetSpyEventMsg(const char* imgName)
	{
		/*
		Spy_EventMsg_ComingSoonOpenSpy.png  :   for when Counting down.
		Spy_EventMsg_Survive.png            :   for Spy side.
		Spy_EventMsg_EliminateSpy.png       :   for Tracker side.
		*/

		MPicture* pPicture = (MPicture*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Spy_EventMsg");
		if (pPicture)
		{
			if (imgName)
			{
				MBitmap* pBitmap = (MBitmap*)MBitmapManager::Get(imgName);
				if (pBitmap)
				{
					pPicture->SetBitmap(pBitmap);
					pPicture->Show(true);
				}
				else _ASSERT(0);
			}
			else
			{
				pPicture->Show(false);
				pPicture->SetBitmap(NULL);
			}
		}
	}

	void ZCombatInterface::SetSpyNotice(const char* imgName)
	{
		/*
		Spy_Notice_Wait_OtherPlayer.png    :   Waiting for other players.
		Spy_Notice_Tracer.png              :   You are selected as tracker.
		Spy_Notice_Spy.png                 :   You are selected as spy.
		*/

		m_bSpyNoticePlaying = false;

		MPicture* pPicture = (MPicture*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Spy_Notice");
		if (pPicture)
		{
			if (imgName)
			{
				MBitmap* pBitmap = (MBitmap*)MBitmapManager::Get(imgName);
				if (pBitmap)
				{
					pPicture->SetBitmap(pBitmap);
					pPicture->SetOpacity(255);
					pPicture->Show(true);
				}
				else _ASSERT(0);
			}
			else
			{
				pPicture->Show(false);
				pPicture->SetBitmap(NULL);
			}
		}
	}

	void ZCombatInterface::SetDefaultSpyTip(MMatchTeam team)
	{
		if (m_Observer.IsVisible())
		{
			SetSpyTip(ZMsg(MSG_SPY_PARTICIPATION_GUIDANCE));
		}
		else
		{
			if (team == MMT_RED)
			{
				if (m_bSpyLocationOpened)
					SetSpyTip(ZMsg(MSG_SPY_SPYSIDE_SPY_LOCATION_OPEN));
				else
					SetSpyTip(ZMsg(MSG_SPY_TIP_SPYSIDE));
			}
			else
			{
				if (m_bSpyLocationOpened)
					SetSpyTip(ZMsg(MSG_SPY_TRACKERSIDE_SPY_LOCATION_OPEN));
				else
					SetSpyTip(ZMsg(MSG_SPY_TIP_TRACKERSIDE));
			}
		}
	}

	const char* ZCombatInterface::GetSuitableSpyItemTip(int itemid)
	{
		switch (itemid)
		{
		case 601001:	// flashbang.
			return ZMsg(MSG_SPY_TIP_FLASH_BANG);
		case 601002:	// smoke.
			return ZMsg(MSG_SPY_TIP_SMOKE);
		case 601003:	// frozen trap.
			return ZMsg(MSG_SPY_TIP_FROZEN_TRAP);
		case 601004:	// stun grenade.
			return ZMsg(MSG_SPY_TIP_STUN_GRENADE);
		case 601005:	// landmine.
			return ZMsg(MSG_SPY_TIP_LANDMINE);
		}

		return NULL;	// nothing found.
	}

	void ZCombatInterface::SetSpyTimeLimitValue(int m, int s, int ms)
	{
		char szText[256];
		sprintf(szText, "%d:%02d:%02d", m, s, ms);

		ZBmNumLabel* pNumLabel = (ZBmNumLabel*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Spy_CountDownTime");
		if (pNumLabel)
			pNumLabel->SetText(szText);

		pNumLabel = (ZBmNumLabel*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Spy_CountDownTime_Red");
		if (pNumLabel)
			pNumLabel->SetText(szText);
	}

	void ZCombatInterface::SetSpyTimeLimitValue(DWORD dwTime)
	{
		int m = (int)(dwTime / 1000 / 60);
		int s = (int)(dwTime / 1000 % 60);
		int ms = (int)(dwTime % 1000 / 10);

		SetSpyTimeLimitValue(m, s, ms);
	}

	void ZCombatInterface::SetSpyTimer(DWORD dwTimeLimit)
	{
		DWORD dwNowTime = timeGetTime();
		DWORD dwEndTime = dwNowTime + dwTimeLimit;

		SetSpyTimeLimitValue(dwTimeLimit);

		m_dwSpyTimer = dwEndTime;
	}

	void ZCombatInterface::PlaySpyNotice(const char* imgName)
	{
		if (!imgName)
		{
			_ASSERT(0);
			return;
		}

		MPicture* pPicture = (MPicture*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Spy_Notice");
		if (pPicture)
		{
			MBitmap* pBitmap = (MBitmap*)MBitmapManager::Get(imgName);
			if (pBitmap)
			{
				pPicture->SetBitmap(pBitmap);
				pPicture->SetOpacity(0);
				pPicture->Show(true);
			}
			else _ASSERT(0);
		}

		m_dwSpyNoticePlayStartedTime = timeGetTime();
		m_bSpyNoticePlaying = true;
	}


Find <br>

	#include "ZModule_QuestStatus.h"
	#include "ZLocale.h"

	#include "ZRuleDuel.h"
	#include "ZRuleDuelTournament.h"
	#include "ZInput.h"

	#include "ZNHN_USA_Report.h"

Add under <br>

	#include "../CSCommon/MMatchSpyMap.h"

Open(ZInterfaceListener.cpp) <br>
Find <br>

	BEGIN_IMPLEMENT_LISTENER(ZStageSpyBanMapBoxOpen, MBTN_CLK_MSG)
		ZApplication::GetStageInterface()->OpenSpyBanMapBox();
	END_IMPLEMENT_LISTENER()

Add under <br>

	BEGIN_IMPLEMENT_LISTENER(ZStageSpyBanMapBoxClose, MBTN_CLK_MSG)
		ZApplication::GetStageInterface()->CloseSpyBanMapBox();
	END_IMPLEMENT_LISTENER()

System/Gametypecfg.xml <br>

	<GAMETYPE id="21">	<!-- GAMETYPE_SPY -->
		<ROUNDS    round="3"	str="3" default="true"/>
		<ROUNDS    round="4"	str="4" />
		<ROUNDS    round="5"	str="5" />
		<MAXPLAYERS player="4"  str="4" />
		<MAXPLAYERS player="5"  str="5" />
		<MAXPLAYERS player="6"  str="6" />
		<MAXPLAYERS player="7"  str="7" />
		<MAXPLAYERS player="8"  str="8" default="true" />
		<MAXPLAYERS player="9"  str="9" />
		<MAXPLAYERS player="10"  str="10" />
		<MAXPLAYERS player="11"  str="11" />
		<MAXPLAYERS player="12"  str="12" />
		<LIMITTIME sec="-1"	str="STR:GAMETYPECFG_LIMITTIME_INFINITE" />
	</GAMETYPE>	

System/ChannelRule.xml <br>

	<GAMETYPE id="21" />


System/Messages.xml <br>
Find <br>

	<!-- 플레이 보너스 보상 -->
	<MSG id="2060">[$1] $2 received $3!</MSG>
	<MSG id="2061">Remaining bonus chance : $1</MSG>
	<MSG id="2062">[$1] There are no bonus chances remaining.</MSG>
	<MSG id="2063">Bonus chance has been recharged : $1</MSG>

Add under <br>

	<!-- Spymode -->
	<MSG id="2200">Board games are waiting for more people. (You need at least $1)</MSG>
	<MSG id="2201">A crawler has been launched to the location. It must survive!</MSG>
	<MSG id="2202">The location of Spy has been revealed. We have to hurry!</MSG>
	<MSG id="2203">Tip: Freeze spy photo is activated immediately, the effect will be much better.</MSG>
	<MSG id="2204">Tip: Spy flares explode immediately, and almost do not affect the spy.</MSG>
	<MSG id="2205">Tip: Spy Smoke spreads immediately, and the range is wide.</MSG>
	<MSG id="2206">Tip: Use the stun grenade, while below it is characteristic of a spy.</MSG>
	<MSG id="2207">Tip: You can also see the installed spyware mines.</MSG>
	<MSG id="2208">Tip: You can create spy weapons, but only from ice shots / Flares / smoke bombs to receive payment.</MSG>
	<MSG id="2209">Tip: Using the spy tracker is useful for grenades and mines, you must acquire it in order to use it.</MSG>
	<MSG id="2210">The list of maps has been updated.</MSG>
	<MSG id="2211">People are not suitable for current maps, except the selected one.</MSG>
	<MSG id="2212">He has scored points !!!</MSG>
	<MSG id="2213">Quote</MSG>
	<MSG id="2214">You can participate in the game from the next round</MSG>
	<MSG id="2215">Win a round the Coins $1 y $2 obtained from experience.</MSG>
	<MSG id="2216">Static public spy! :</MSG>
	<MSG id="2217">All of maps that can be started have been excluded from the list.</MSG>

System/Strings.xml <br>
Find <br>

	<STR id="ZITEM_NAME_600306">Giston's Eye</STR>
	<STR id="ZITEM_DESC_600306">[Enchant Lv.0] Enchanted on this tiny jewel is the power of Giston. Melee weapon fires up when charged. Any opponent hit by enchant attack will get damaged at every second for a certain amount of time.</STR>

Add under <br>

	<STR id="ZITEM_NAME_601001">Flare SPY Flare</STR>
	<STR id="ZITEM_DESC_601001">Spy flares explode immediately, and almost no spy is affected.</STR>

	<STR id="ZITEM_NAME_601002">SPY Smoke</STR>
	<STR id="ZITEM_DESC_601002">Spy smoke smoke immediately unfolded, and the range is too wide.</STR>

	<STR id="ZITEM_NAME_601003">SPY Photos Freeze</STR>
	<STR id="ZITEM_DESC_601003">freezing and activated immediately, the effect is much better.</STR>

	<STR id="ZITEM_NAME_601004">Stun Grenades</STR>
	<STR id="ZITEM_DESC_601004">Spy according to stun grenades stunned for a moment falls into the state.</STR>

	<STR id="ZITEM_NAME_601005">Explosive Mines</STR>
	<STR id="ZITEM_DESC_601005">To quote an invisible spy from Minas, and it will last a minute.</STR>

	<STR id="ZITEM_NAME_601006">Confidential Briefcase</STR>
	<STR id="ZITEM_DESC_601006">This is the briefcase where the spy has the papers and ammunition forbidden under the astra world.</STR>

System/Zitem.xml <br>

	<!-- Mode SPY Items -->
	  <ITEM id="601001" name="STR:ZITEM_NAME_601001" mesh_name="flashbang01" totalpoint="0" type="custom" res_sex="a" res_level="0" slot="custom" weapon="flashbang_spy" weight="0" bt_price="0" delay="1500" damage="0" ctrl_ability="20" magazine="4" maxbullet="4" reloadtime="10" slug_output="false" gadget_id="0" hp="0" ap="0" maxwt="0" sf="0" fr="0" cr="0" pr="0" lr="0" color="#FFFFFFFF" image_id="3" bullet_image_id="0" magazine_image_id="0" snd_fire="we_grenade_fire" desc="STR:ZITEM_DESC_601001" iscashitem="true"/>
	  <ITEM id="601002" name="STR:ZITEM_NAME_601002" mesh_name="smoke01" totalpoint="0" type="custom" res_sex="a" res_level="0" slot="custom" weapon="smoke_spy" weight="0" bt_price="0" delay="1500" damage="0" ctrl_ability="20" magazine="10" maxbullet="10" reloadtime="10" slug_output="false" gadget_id="0" hp="0" ap="0" maxwt="0" sf="0" fr="0" cr="0" pr="0" lr="0" color="#FFFFFFFF" image_id="3" bullet_image_id="0" magazine_image_id="0" snd_fire="we_grenade_fire" desc="STR:ZITEM_DESC_601001" iscashitem="true"/>
	  <ITEM id="601003" name="STR:ZITEM_NAME_601003" mesh_name="trap_frozenfield" type="custom" slot="custom" weapon="trap_spy" spendable="true" spendtype="normal" itempower="20" damagetime="3000" damagetype="cold" magazine="5" maxbullet="5" lifetime="6000" weight="0" delay="1000" totalpoint="0" res_sex="a" res_level="0" bt_price="500000" color="#FFFFFFFF" snd_fire="we_grenade_fire" desc="STR:ZITEM_DESC_601001" iscashitem="true"/>
	  <ITEM id="601004" name="STR:ZITEM_NAME_601004" mesh_name="spy_stungrenade" type="custom" slot="custom" weapon="stungrenade_spy" spendable="true" spendtype="normal" damage="20" magazine="1" maxbullet="1" weight="0" delay="1500" totalpoint="0" res_sex="a" res_level="0" bt_price="500000" color="#FFFFFFFF" snd_fire="we_grenade_fire" bullet_image_id="0" magazine_image_id="0" desc="STR:ZITEM_DESC_601004" iscashitem="true"/>
	  <ITEM id="601005" name="STR:ZITEM_NAME_601005" mesh_name="spy_landmine" totalpoint="0" type="custom" res_sex="a" res_level="0" slot="custom" weapon="landmine_spy" weight="0" bt_price="400" delay="400" damage="0" ctrl_ability="0" magazine="3" maxbullet="3" reloadtime="10" slug_output="false" gadget_id="0" hp="0" ap="0" maxwt="0" sf="0" fr="0" cr="0" pr="0" lr="0" color="#FFFFFFFF" image_id="3" bullet_image_id="0" magazine_image_id="0" snd_fire="we_grenade_fire" desc="STR:ZITEM_DESC_601005" iscashitem="true"/>
	  <ITEM id="601006" name="STR:ZITEM_NAME_601006" mesh_name="katana_spycase" totalpoint="0" type="melee" res_sex="a" res_level="0" slot="melee" weapon="spy_case" weight="0" bt_price="500000" delay="329" damage="0" range="200" ctrl_ability="0" magazine="0" reloadtime="0" slug_output="false" gadget_id="0" hp="0" ap="0" maxwt="0" sf="0" fr="0" cr="0" pr="0" lr="0" color="#FFFFFFFF" image_id="0" bullet_image_id="0" magazine_image_id="0" snd_weapon_fiber="rubber" desc="STR:ZITEM_DESC_601006" iscashitem="true"/>

Default/Lobby.xml <br>
Find <br>

	BITMAP type="icon" mode="12">ChallengeQuest_Guerilla-mode.tga</BITMAP>

Add under <br>

	<BITMAP type="icon" mode="21">Spy_mode.tga</BITMAP>

Default/Templates.xml <br>
Find <br>

	<ANIMATIONTEMPLATE item="MapAnimation">
		<BITMAP>gametype_solo.tga</BITMAP>
		<BITMAP>gametype_team.tga</BITMAP>

Add under <br>

	<BITMAP>gametype_spy.tga</BITMAP>

Default/Stage.xml <br>
Find <br>
	
	<!-- BMBUTTON : 릴레이맵 리스트 닫기 버튼 -->
	<BMBUTTON item="Stage_RelayMapBoxClose" parent="Stage_RelayMapListView">
		<BOUNDS>
			<X>195</X>
			<Y>162</Y>
			<W>21</W>
			<H>100</H>
		</BOUNDS>
		<STRETCH/>
		<BITMAP type="up">listframeclosebtn_off.tga</BITMAP>
		<BITMAP type="over">listframeclosebtn_on.tga</BITMAP>
		<BITMAP type="down">listframeclosebtn_on.tga</BITMAP>
	</BMBUTTON>

Add <br>

	<!-- FRAME : 스파이모드 밴맵 리스트 뷰어 -->
	<FRAME item="Stage_SpyBanMapListView" parent="Stage">
		<FRAMELOOK>NullFrameLook</FRAMELOOK>
		<BOUNDS>
			<X>0</X>
			<Y>117</Y>
			<W>226</W>
			<H>425</H>
		</BOUNDS>
		<TITLEBAR>false</TITLEBAR>
		<RESIZABLE>false</RESIZABLE>
		<FOCUSABLE>false</FOCUSABLE>
		<VISIBLE>true</VISIBLE>
	</FRAME>
	
	<!-- Picture : 스파이모드 밴맵 리스트 배경 이미지 출력 -->
	<PICTURE item ="Stage_SpyBanMapListBG" parent="Stage_SpyBanMapListView">
		<BOUNDS>
			<X>0</X>
			<Y>0</Y>
			<W>226</W>
			<H>425</H>
		</BOUNDS>
		<STRETCH/>
		<BITMAP></BITMAP>
	</PICTURE>
	
	<!-- BMBUTTON : 스파이모드 밴맵 리스트 열기 버튼 -->
	<BMBUTTON item="Stage_SpyBanMapBoxOpen" parent="Stage_SpyBanMapListView">
		<BOUNDS>
			<X>195</X>
			<Y>162</Y>
			<W>21</W>
			<H>100</H>
		</BOUNDS>
		<STRETCH/>
		<BITMAP type="up">listframeopenbtn_off.tga</BITMAP>
		<BITMAP type="over">listframeopenbtn_on.tga</BITMAP>
		<BITMAP type="down">listframeopenbtn_on.tga</BITMAP>
	</BMBUTTON>
	
	<!-- BMBUTTON : 스파이모드 밴맵 리스트 닫기 버튼 -->
	<BMBUTTON item="Stage_SpyBanMapBoxClose" parent="Stage_SpyBanMapListView">
		<BOUNDS>
			<X>195</X>
			<Y>162</Y>
			<W>21</W>
			<H>100</H>
		</BOUNDS>
		<STRETCH/>
		<BITMAP type="up">listframeclosebtn_off.tga</BITMAP>
		<BITMAP type="over">listframeclosebtn_on.tga</BITMAP>
		<BITMAP type="down">listframeclosebtn_on.tga</BITMAP>
	</BMBUTTON>
	
	<!-- LABEL : 스파이모드 '맵을 클릭해 제외할 수 있습니다.' -->
	<LABEL item="Stage_SpyBanMapLabel" parent="Stage_SpyBanMapListView">
		<FONT>FONTa12</FONT>
		<TEXTCOLOR>
			<R>255</R>
			<G>255</G>
			<B>255</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>7</X>
			<Y>7</Y>
			<W>185</W>
			<H>25</H>
		</BOUNDS>
		<TEXT>STR:UI_STAGE_502</TEXT>
	</LABEL>
	
	<!-- LISTBOX : 스파이모드 밴맵 리스트 -->
	<LISTBOX item="Stage_SpyBanMapList" parent="Stage_SpyBanMapListView">
		<LISTBOXLOOK>NullListBoxLook</LISTBOXLOOK>
		<BOUNDS>
			<X>7</X>
			<Y>32</Y>
			<W>185</W>
			<H>393</H>
		</BOUNDS>
		<STRETCH/>
	</LISTBOX>
	
	<!-- LABEL : 스파이모드 맵 선택에 랜덤 맵이라고 표시 -->
	<LABEL item="Stage_SpyRandomMapLabel" parent="StageGameInfo">
		<FONT>FONTa12</FONT>
		<TEXTCOLOR>
			<R>255</R>
			<G>255</G>
			<B>255</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>336</X>
			<Y>40</Y>
			<W>218</W>
			<H>24</H>
		</BOUNDS>
		<TEXTALIGN>
			<HALIGN>center</HALIGN>
			<VALIGN>center</VALIGN>
		</TEXTALIGN>
		<TEXT>STR:UI_STAGE_501</TEXT>
	</LABEL>

Default/GameResult.xml <br>
Find <br>

	<!-- Label : 보상아이템 이름 표시 -->
	<LABEL item="CQ_Result_RewardText" parent="ChallengeQuestResult">
		<FONT>FONTa6b</FONT>
		<TEXTCOLOR>
			<R>210</R>
			<G>80</G>
			<B>80</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>568</X>
			<Y>521</Y>
			<W>140</W>
			<H>12</H>
		</BOUNDS>
	</LABEL>

Add under <br>

	<!-- FRAME : Combat Result 화면 구성 -->
	<FRAME item="SpyResult" parent="GameResult">
		<FRAMELOOK>NullFrameLook</FRAMELOOK>
		<BOUNDS>
			<X>0</X>
			<Y>20</Y>
			<W>800</W>
			<H>600</H>
		</BOUNDS>
		<TITLEBAR>false</TITLEBAR>
		<RESIZABLE>false</RESIZABLE>
		<FOCUSABLE>false</FOCUSABLE>
		<VISIBLE>false</VISIBLE>
	</FRAME>
	
	<!-- Picture : Finish -->
	<PICTURE item="SpyResult_Finish" parent="SpyResult">
		<BOUNDS>
			<X>135</X>
			<Y>34</Y>
			<W>310</W>
			<H>77</H>
		</BOUNDS>
		<STRETCH/>
		<BITMAP>result_finish.tga</BITMAP>
	</PICTURE>
	
	<!-- Picture : Header -->
	<PICTURE item="SpyResult_Header" parent="SpyResult">
		<BOUNDS>
			<X>57</X>
			<Y>139</Y>
			<W>453</W>
			<H>21</H>
		</BOUNDS>
		<STRETCH/>
		<BITMAP>blacknullframe.tga</BITMAP>
	</PICTURE>
	
	<!-- Label : 플레이어 이름 리스트 레이블 -->
	<LABEL item="SpyResult_PlayerNameListLabel" parent="SpyResult">
		<FONT>FONTa10b</FONT>
		<TEXTCOLOR>
			<R>210</R>
			<G>210</G>
			<B>210</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>60</X>
			<Y>140</Y>
			<W>300</W>
			<H>20</H>
		</BOUNDS>
		<TEXT>STR:UI_ETC_01</TEXT>
	</LABEL>

	<!-- TEXTAREA : 플레이어 이름 리스트 -->
	<TEXTAREA item = "SpyResult_PlayerNameList" parent = "SpyResult">
		<FONT>FONTa10b</FONT>
		<TEXTCOLOR>
			<R>205</R>
			<G>205</G>
			<B>205</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>60</X>
			<Y>165</Y>
			<W>260</W>
			<H>400</H>
		</BOUNDS>
		<MOVABLE>false</MOVABLE>
		<EDITABLE>false</EDITABLE>
	</TEXTAREA>

	<!-- Label : 플레이어 점수 리스트 레이블 -->
	<LABEL item="SpyResult_PlayerScoreListLabel" parent="SpyResult">
		<FONT>FONTa10b</FONT>
		<TEXTCOLOR>
			<R>210</R>
			<G>210</G>
			<B>210</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>335</X>
			<Y>140</Y>
			<W>65</W>
			<H>20</H>
		</BOUNDS>
		<TEXT>STR:UI_ETC_06</TEXT>
	</LABEL>
	
	<!-- TEXTAREA : 플레이어 점수 리스트 -->
	<TEXTAREA item = "SpyResult_PlayerScoreList" parent = "SpyResult">
		<FONT>FONTa10b</FONT>
		<TEXTCOLOR>
			<R>205</R>
			<G>205</G>
			<B>205</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>345</X>
			<Y>165</Y>
			<W>55</W>
			<H>400</H>
		</BOUNDS>
		<MOVABLE>false</MOVABLE>
		<EDITABLE>false</EDITABLE>
	</TEXTAREA>
	
	<!-- Label : 플레이어 승 리스트 레이블 -->
	<LABEL item="SpyResult_PlayerWinListLabel" parent="SpyResult">
		<FONT>FONTa10b</FONT>
		<TEXTCOLOR>
			<R>210</R>
			<G>210</G>
			<B>210</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>400</X>
			<Y>140</Y>
			<W>50</W>
			<H>20</H>
		</BOUNDS>
		<TEXT>STR:UI_ETC_07</TEXT>
	</LABEL>
	
	<!-- TEXTAREA : 플레이어 승 리스트 -->
	<TEXTAREA item = "SpyResult_PlayerWinList" parent = "SpyResult">
		<FONT>FONTa10b</FONT>
		<TEXTCOLOR>
			<R>205</R>
			<G>205</G>
			<B>205</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>410</X>
			<Y>165</Y>
			<W>40</W>
			<H>400</H>
		</BOUNDS>
		<MOVABLE>false</MOVABLE>
		<EDITABLE>false</EDITABLE>
	</TEXTAREA>

	<!-- Label : 플레이어 패 리스트 레이블 -->
	<LABEL item="SpyResult_PlayerLoseListLabel" parent="SpyResult">
		<FONT>FONTa10b</FONT>
		<TEXTCOLOR>
			<R>210</R>
			<G>210</G>
			<B>210</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>450</X>
			<Y>140</Y>
			<W>50</W>
			<H>20</H>
		</BOUNDS>
		<TEXT>STR:UI_ETC_08</TEXT>
	</LABEL>
	
	<!-- TEXTAREA : 플레이어 패 리스트 -->
	<TEXTAREA item = "SpyResult_PlayerLoseList" parent = "SpyResult">
		<FONT>FONTa10b</FONT>
		<TEXTCOLOR>
			<R>205</R>
			<G>205</G>
			<B>205</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>460</X>
			<Y>165</Y>
			<W>40</W>
			<H>400</H>
		</BOUNDS>
		<MOVABLE>false</MOVABLE>
		<EDITABLE>false</EDITABLE>
	</TEXTAREA>

Copy from Github(Default/CombatInterface_Spy.xml) <br>

Default/CombatInterface.xml <br>
Find <br>

	<INCLUDE>CombatInterface_DuelTournament.xml</INCLUDE>

Add under <br>

	<INCLUDE>CombatInterface_Spy.xml</INCLUDE>

Default/Screeneffect.xml <br>
Find <br>

	<AddEffectElu name="duel9">
		<AddBaseModel name="duel9" filename="ef_duel_num_9.elu" />
		<AddAnimation name="play" filename="ef_duel_num_9.elu.ani" motion_type="0" motion_loop_type="lastframe" />
	</AddEffectElu>

Add under <br>

	<!--SPYMODE-->	
		<AddEffectElu name="spy_selection">
			<AddBaseModel name="spy_selection" filename="ef_spy_selection.elu" />
			<AddAnimation name="play" filename="ef_spy_selection.elu.ani" motion_type="0" motion_loop_type="lastframe" />
		</AddEffectElu>
	
	<AddEffectElu name="spy_eliminationAllKill">
		<AddBaseModel name="spy_eliminationAllKill" filename="ef_spy_eliminationAllKill.elu" />
		<AddAnimation name="play" filename="ef_spy_eliminationAllKill.elu.ani" motion_type="0" motion_loop_type="lastframe" />
	</AddEffectElu>
	
	<AddEffectElu name="spy_elimination1Remain">
		<AddBaseModel name="spy_elimination1Remain" filename="ef_spy_elimination1Remain.elu" />
		<AddAnimation name="play" filename="ef_spy_elimination1Remain.elu.ani" motion_type="0" motion_loop_type="lastframe" />
	</AddEffectElu>
	
		<AddEffectElu name="spy_elimination2Remain">
		<AddBaseModel name="spy_elimination2Remain" filename="ef_spy_elimination2Remain.elu" />
		<AddAnimation name="play" filename="ef_spy_elimination2Remain.elu.ani" motion_type="0" motion_loop_type="lastframe" />
	</AddEffectElu>
	
	<AddEffectElu name="spy_location">
		<AddBaseModel name="spy_location" filename="ef_spy_location.elu" />
		<AddAnimation name="play" filename="ef_spy_location.elu.ani" motion_type="0" motion_loop_type="lastframe" />
	</AddEffectElu>

	<AddEffectElu name="ef_in_icon_spy_landmine.elu">
		<AddBaseModel name="ef_in_icon_spy_landmine.elu" filename="ef_in_icon_spy_landmine.elu" />
	</AddEffectElu>
	<AddEffectElu name="ef_in_icon_spy_stungrenade.elu">
		<AddBaseModel name="ef_in_icon_spy_stungrenade.elu" filename="ef_in_icon_spy_stungrenade.elu" />
	</AddEffectElu>
	<AddEffectElu name="ef_in_icon_spy_spycase.elu">
		<AddBaseModel name="ef_in_icon_spy_spycase.elu" filename="ef_in_icon_spy_spycase.elu" />
	</AddEffectElu>	

Default/BitmapAlias.xml <br>
Find <br>

	  <BITMAPALIAS name="dt_grade2.png">
		<SOURCE>interface.tga</SOURCE>
		<BOUNDS>
			<X>96</X>
			<Y>198</Y>
			<W>32</W>
			<H>32</H>
		</BOUNDS>
	  </BITMAPALIAS>
	  <BITMAPALIAS name="dt_grade1.png">
		<SOURCE>interface.tga</SOURCE>
		<BOUNDS>
			<X>128</X>
			<Y>198</Y>
			<W>32</W>
			<H>32</H>
		</BOUNDS>
	  </BITMAPALIAS>

Add under <br>

	  <!-- 스파이모드 이벤트 메시지 -->
	  <BITMAPALIAS name="Spy_EventMsg_ComingSoonOpenSpy.png">
	    <SOURCE>Spy_EventMsg.png</SOURCE>
	    <BOUNDS> <X>0</X> <Y>0</Y> <W>1024</W> <H>72</H> </BOUNDS>
	  </BITMAPALIAS>
	  <BITMAPALIAS name="Spy_EventMsg_Survive.png">
	    <SOURCE>Spy_EventMsg.png</SOURCE>
	    <BOUNDS> <X>0</X> <Y>72</Y> <W>1024</W> <H>72</H> </BOUNDS>
	  </BITMAPALIAS>
	  <BITMAPALIAS name="Spy_EventMsg_EliminateSpy.png">
	    <SOURCE>Spy_EventMsg.png</SOURCE>
	    <BOUNDS> <X>0</X> <Y>144</Y> <W>1024</W> <H>72</H> </BOUNDS>
	  </BITMAPALIAS>

	  <BITMAPALIAS name="Spy_Notice_Wait_OtherPlayer.png">
	    <SOURCE>Spy_EventMsg.png</SOURCE>
	    <BOUNDS> <X>0</X> <Y>753</Y> <W>675</W> <H>109</H> </BOUNDS>
	  </BITMAPALIAS>
	  <BITMAPALIAS name="Spy_Notice_Tracer.png">
	    <SOURCE>Spy_EventMsg.png</SOURCE>
	    <BOUNDS> <X>0</X> <Y>862</Y> <W>390</W> <H>80</H> </BOUNDS>
	  </BITMAPALIAS>
	  <BITMAPALIAS name="Spy_Notice_Spy.png">
	    <SOURCE>Spy_EventMsg.png</SOURCE>
	    <BOUNDS> <X>0</X> <Y>943</Y> <W>390</W> <H>80</H> </BOUNDS>
	  </BITMAPALIAS>
	  </XML> 

Open(ZGameInterface.cpp) <br>
Find <br>

	pBmNumLabel = (ZBmNumLabel*)m_IDLResource.FindWidget("SurvivalResult_GetBounty");
	if (pBmNumLabel)
	{
		pBmNumLabel->SetCharMargin(nMargin);
		pBmNumLabel->SetIndexOffset(16);
	}

Add under <br>

	int nSpyMargin[BMNUM_NUMOFCHARSET] = { 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 20, 20, 20 };

	pBmNumLabel = (ZBmNumLabel*)m_IDLResource.FindWidget("Spy_CountDownTime");
	if (pBmNumLabel)
	{
		pBmNumLabel->SetAlignmentMode(MAM_HCENTER);
		pBmNumLabel->SetNumber(0);
		pBmNumLabel->SetHeightRatio(64);
		pBmNumLabel->SetCharMargin(nSpyMargin);
	}
	pBmNumLabel = (ZBmNumLabel*)m_IDLResource.FindWidget("Spy_CountDownTime_Red");
	if (pBmNumLabel)
	{
		pBmNumLabel->SetAlignmentMode(MAM_HCENTER);
		pBmNumLabel->SetNumber(0);
		pBmNumLabel->SetHeightRatio(64);
		pBmNumLabel->SetCharMargin(nSpyMargin);
	}


Open(ZBmNumLabel.h) <br>
Find <br>

	class ZBmNumLabel : public MWidget{
	protected:
		MBitmap*		m_pLabelBitmap;
		MSIZE			m_CharSize;
		MAlignmentMode	m_AlignmentMode;
		int				m_nIndexOffset;
		int				m_nCharMargin[ BMNUM_NUMOFCHARSET];

Add under <br>

	int				m_nHeightRatio;

Find <br>
	
	void SetIndexOffset(int nOffset) { m_nIndexOffset = nOffset; }
	void SetCharMargin( int* nMargin);
	void SetAlignmentMode( MAlignmentMode am)			{ m_AlignmentMode = am; }

Add under <br>

	void SetHeightRatio(int n)	{ m_nHeightRatio = n; }

Open(ZCombatInterface.cpp) <br>
Find <br>

	m_bNetworkAlive = true;		// ÀÎÅÍ³Ý ¿¬°áµÇ¾îÀÖÀ½
	m_dLastTimeTick = 0;
	m_dAbuseHandicapTick = 0;

	m_bSkipUIDrawByRule = false;

Add under <br>

	m_bSpyLocationOpened = false;
	m_pSpyIcon = NULL;

	m_dwSpyTimer = 0;

	m_bSpyNoticePlaying = false;
	m_dwSpyNoticePlayStartedTime = 0;

Find <br>

	if (m_pTargetLabel)
	{
		delete m_pTargetLabel;
		m_pTargetLabel = NULL;
	}
	ShowInfo(false);

Replace <br>

	if (m_pTargetLabel)
	{
		delete m_pTargetLabel;
		m_pTargetLabel = NULL;
	}
	ShowInfo(false);
	if (m_pSpyIcon)
	{
		delete m_pSpyIcon;
		m_pSpyIcon = NULL;
	}

	OnSpyDestroy();







Replace (Matchserver & System.mrs) <br>
Rebuild (Matchserver & Gunz project) <br>

































