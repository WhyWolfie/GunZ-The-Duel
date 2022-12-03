- masked level '--' instead of numbers.
- new colour system easier to manage.
- time in lobbychat/stagechat

htmlcolorcodes: [htmlcolorcodes](https://htmlcolorcodes.com/) <br>
copy hexcode and replace: 0xFF(stay like that) - FF8040 (your hex code) example: 0xFFFF8040

Almost completed

Open(ZCombatInterface.cpp) <br>
Find <br>

				// Player
				if ( pCharacter->GetUID() == pDuel->QInfo.m_uidChampion)
				{
					if ( ZGetMyUID() == pDuel->QInfo.m_uidChampion)
					{
						// Draw victory
						ZGetCombatInterface()->DrawVictory( pDC, 210, 86, pDuel->QInfo.m_nVictory);
					}
					else
					{
						sprintf( charName[ 0], "%s%d  %s", ZMsg( MSG_CHARINFO_LEVELMARKER), pCharacter->GetProperty()->nLevel, pCharacter->GetUserName());

						if ( (ZGetMyUID() == pDuel->QInfo.m_uidChampion) || (ZGetMyUID() == pDuel->QInfo.m_uidChallenger))
						{
							// Draw victory
							int nTextWidth = pFont->GetWidth( charName[ 0]);
							int nWidth = ZGetCombatInterface()->DrawVictory( pDC, 162, 300, pDuel->QInfo.m_nVictory, true);
							ZGetCombatInterface()->DrawVictory( pDC, 43+nTextWidth+nWidth, 157, pDuel->QInfo.m_nVictory);
						}
					}
				}
        
Replace <br>

				// Player
				if (pCharacter->GetUID() == pDuel->QInfo.m_uidChampion)
				{
					if (ZGetMyUID() == pDuel->QInfo.m_uidChampion)
					{
						// Draw victory
						ZGetCombatInterface()->DrawVictory(pDC, 210, 86, pDuel->QInfo.m_nVictory);
					}
					else
					{
						if (pCharacter->IsAdminName())
							sprintf(charName[0], "%s--  %s", ZMsg(MSG_CHARINFO_LEVELMARKER), pCharacter->GetUserName());
						else
							sprintf(charName[0], "%s%d  %s", ZMsg(MSG_CHARINFO_LEVELMARKER), pCharacter->GetProperty()->nLevel, pCharacter->GetUserName());
						ZGetGame()->GetUserGradeIDColor(pCharacter->GetUserGrade(), CharColour[0], "");
						if ((ZGetMyUID() == pDuel->QInfo.m_uidChampion) || (ZGetMyUID() == pDuel->QInfo.m_uidChallenger))
						{
							// Draw victory
							int nTextWidth = pFont->GetWidth(charName[0]);
							int nWidth = ZGetCombatInterface()->DrawVictory(pDC, 162, 300, pDuel->QInfo.m_nVictory, true);
							ZGetCombatInterface()->DrawVictory(pDC, 43 + nTextWidth + nWidth, 157, pDuel->QInfo.m_nVictory);
						}
					}
				}
        

Find

				else if ( pCharacter->GetUID() == pDuel->QInfo.m_uidChallenger)
				{
					if ( ZGetMyUID() != pDuel->QInfo.m_uidChallenger)
						sprintf( charName[ 0], "%s%d  %s", ZMsg( MSG_CHARINFO_LEVELMARKER), pCharacter->GetProperty()->nLevel, pCharacter->GetUserName());

					bIsChallengerDie = pCharacter->IsDie();
				}

				// Waiting 1
				else if (pCharacter->GetUID() == pDuel->QInfo.m_WaitQueue[0])
					sprintf( charName[ 1], "%s%d  %s", ZMsg( MSG_CHARINFO_LEVELMARKER), pCharacter->GetProperty()->nLevel, pCharacter->GetUserName());

				// Waiting 2
				else if (pCharacter->GetUID() == pDuel->QInfo.m_WaitQueue[1])
					sprintf( charName[ 2], "%s%d  %s", ZMsg( MSG_CHARINFO_LEVELMARKER), pCharacter->GetProperty()->nLevel, pCharacter->GetUserName());
			}
		}
        
        
Replace

				else if (pCharacter->GetUID() == pDuel->QInfo.m_uidChallenger)
				{
					if (ZGetMyUID() != pDuel->QInfo.m_uidChallenger)
					{
						if (pCharacter->IsAdminName())
							sprintf(charName[0], "%s--  %s", ZMsg(MSG_CHARINFO_LEVELMARKER), pCharacter->GetUserName());
						else
							sprintf(charName[0], "%s%d  %s", ZMsg(MSG_CHARINFO_LEVELMARKER), pCharacter->GetProperty()->nLevel, pCharacter->GetUserName());
						ZGetGame()->GetUserGradeIDColor(pCharacter->GetUserGrade(), CharColour[0], "");
					}

					bIsChallengerDie = pCharacter->IsDie();
				}

				// Waiting 1
				else if (pCharacter->GetUID() == pDuel->QInfo.m_WaitQueue[0])
				{
					if (pCharacter->IsAdminName())
						sprintf(charName[1], "%s--  %s", ZMsg(MSG_CHARINFO_LEVELMARKER), pCharacter->GetUserName());
					else
						sprintf(charName[1], "%s%d  %s", ZMsg(MSG_CHARINFO_LEVELMARKER), pCharacter->GetProperty()->nLevel, pCharacter->GetUserName());
					ZGetGame()->GetUserGradeIDColor(pCharacter->GetUserGrade(), CharColour[1], "");
				}
				// Waiting 2
				else if (pCharacter->GetUID() == pDuel->QInfo.m_WaitQueue[1])
				{
					if (pCharacter->IsAdminName())
						sprintf(charName[2], "%s--  %s", ZMsg(MSG_CHARINFO_LEVELMARKER), pCharacter->GetUserName());
					else
						sprintf(charName[2], "%s%d  %s", ZMsg(MSG_CHARINFO_LEVELMARKER), pCharacter->GetProperty()->nLevel, pCharacter->GetUserName());
					ZGetGame()->GetUserGradeIDColor(pCharacter->GetUserGrade(), CharColour[2], "");
				}
			}
		}

Find

		if(pCharacter->IsAdminName()) {
			sprintf(pItem->szLevel,"%d%s",pCharacter->GetProperty()->nLevel, ZMsg(MSG_CHARINFO_LEVELMARKER));
			pItem->SetColor(ZCOLOR_ADMIN_NAME);
		}

Replace

		if(pCharacter->IsAdminName()) {
			sprintf(pItem->szLevel,"--%s", ZMsg(MSG_CHARINFO_LEVELMARKER));
			pItem->SetColor(ZCOLOR_ADMIN_NAME);
		}

Find

		if(pCharacter->IsAdminHide()) continue;

		
		sprintf(pItem->szName,"%d%s %s",pCharacter->GetProperty()->nLevel, ZMsg(MSG_CHARINFO_LEVELMARKER), pCharacter->GetUserName());


Replace

		if(pCharacter->IsAdminHide()) continue;

		if(pCharacter->IsAdminName())
		sprintf(pItem->szName,"--%s %s", ZMsg(MSG_CHARINFO_LEVELMARKER), pCharacter->GetUserName());
		else
		sprintf(pItem->szName,"%d%s %s",pCharacter->GetProperty()->nLevel, ZMsg(MSG_CHARINFO_LEVELMARKER), pCharacter->GetUserName());


Open(ZGameInterface.cpp) <br>
Find <br>

		// LV
		pLabel = (MLabel*)pRes->FindWidget("Lobby_PlayerSpecLevel");
		sprintf( buf, "%s : %d %s", ZMsg( MSG_CHARINFO_LEVEL), ZGetMyInfo()->GetLevel(), ZMsg(MSG_CHARINFO_LEVELMARKER));
		if (pLabel) pLabel->SetText(buf);

Replace <br>

		// LV
		pLabel = (MLabel*)pRes->FindWidget("Lobby_PlayerSpecLevel");
		if (ZGetMyInfo()->IsAdminGrade())
			sprintf(buf, "%s : --", ZMsg(MSG_CHARINFO_LEVEL));
		else
			sprintf(buf, "%s : %d (%d%%)", ZMsg(MSG_CHARINFO_LEVEL), ZGetMyInfo()->GetLevel(), ZGetMyInfo()->GetLevelPercent());
		if (pLabel) pLabel->SetText(buf);
		
		// XP
		//pLabel = (MLabel*)pRes->FindWidget("Lobby_PlayerSpecXP");
		//sprintf( buf, "%s : %d%%", ZMsg( MSG_CHARINFO_XP), ZGetMyInfo()->GetLevelPercent());
		//if (pLabel) pLabel->SetText(buf);

Find <br>

			pLabel = (MLabel*)pRes->FindWidget("Stage_PlayerSpecLevel");
			if ( pLabel)
			{
				if ( bShowMe)
					sprintf( buf, "%s : %d %s", ZMsg( MSG_CHARINFO_LEVEL), ZGetMyInfo()->GetLevel(), ZMsg(MSG_CHARINFO_LEVELMARKER));
				else
					sprintf( buf, "%s : %s %s", ZMsg( MSG_CHARINFO_LEVEL), pItem->GetString( 1), ZMsg(MSG_CHARINFO_LEVELMARKER));
				pLabel->SetText(buf);
			}


Replace <br>

			pLabel = (MLabel*)pRes->FindWidget("Stage_PlayerSpecLevel");
			if (pLabel)
			{
				if (bShowMe)
					if (ZGetMyInfo()->IsAdminGrade())
						sprintf(buf, "%s : --", ZMsg(MSG_CHARINFO_LEVEL));
					else
						sprintf(buf, "%s : %d", ZMsg(MSG_CHARINFO_LEVEL), ZGetMyInfo()->GetLevel());
				else
					sprintf(buf, "%s : %s", ZMsg(MSG_CHARINFO_LEVEL), pItem->GetString(1));
				pLabel->SetText(buf);
			}



Open(ZPlayerListBox.cpp) <br>
Find <br>

		if(GetUserGradeIDColor(nGrade,_color,sp_name)) {
	sprintf(szLevel,"%2d",nLevel);
	szRefName = szName;
	bSpUser = true;
	}
	else {
	sprintf(szLevel,"%2d",nLevel);
	szRefName = szName;
	}

Replace <br>

	if (IsAdminGrade(nGrade))
		sprintf(szLevel, "--");
	else
		sprintf(szLevel, "%2d", nLevel);
	szRefName = szName;

Find <br>

		if(GetUserInfoUID(puid,_color,sp_name,gid)){
	sprintf(szLevel,"%2d",nLevel);
	szRefName = szName;
	bSpUser = true;
	}
	else {
	sprintf(szLevel,"%2d",nLevel);
	szRefName = szName;
	}

Replace <br>

	if (GetUserInfoUID(puid, _color, sp_name, gid))
	{
		bSpUser = true;
	}
	MMatchObjCache* pObjCache = ZGetGameClient()->FindObjCache(puid);
	if (IsAdminGrade(pObjCache->GetUGrade()))
		sprintf(szLevel, "--");
	else
		sprintf(szLevel, "%2d", nLevel);
	szRefName = szName;

Open(ZShopEquipInterface.cpp) <br>
Find <br>

	szColor = szGray;
	if (nReqLevel > ZGetMyInfo()->GetLevel())
		szColor = szRed;
	sprintf(sz1, "^9%s : %s%d ^9%s", ZMsg(MSG_CHARINFO_LEVEL), szColor, ZGetMyInfo()->GetLevel(), ZMsg(MSG_CHARINFO_LEVELMARKER));
	pTextArea[0]->AddText(sz1);

Replace <br>

	szColor = szGray;
	if (nReqLevel > ZGetMyInfo()->GetLevel())
		szColor = szRed;

	if (ZGetMyInfo()->IsAdminGrade())
		sprintf(sz1, "^9%s : --", ZMsg(MSG_CHARINFO_LEVEL), szColor, ZGetMyInfo()->GetLevel()/*, ZMsg(MSG_CHARINFO_LEVELMARKER)*/);
	else
		sprintf(sz1, "^9%s : %s%d", ZMsg(MSG_CHARINFO_LEVEL), szColor, ZGetMyInfo()->GetLevel()/*, ZMsg(MSG_CHARINFO_LEVELMARKER)*/);
	pTextArea[0]->AddText(sz1);




Matching colours
Open(ZGame.cpp) <br>
Find <br>

	bool ZGame::GetUserGradeIDColor

Replace <br>

	bool ZGame::GetUserGradeIDColor(MMatchUserGradeID UGradeID, MCOLOR& CharNameColor, char* sp_name)
	{
		switch (UGradeID)
		{
		case MMUG_DEVELOPER:
			CharNameColor = MCOLOR(0xFFFF4500);
			break;
		case MMUG_ADMIN:
			CharNameColor = MCOLOR(0xFFFF8040);
			break;
		case MMUG_CHAT_LIMITED:
			CharNameColor = MCOLOR(0xFFFF0000);
			break;
		case MMUG_EVENTMASTER:
			CharNameColor = MCOLOR(0xFFFF8040);
			break;
		case MMUG_VIP:
			CharNameColor = MCOLOR(0xFF228B22);
			break;
		default:
			CharNameColor = MCOLOR(0xFFFFFFFF);
			break;
		}
		return true;
	}


Open(ZGame.h) <br>
Find <br>

	void ShowReplayInfo( bool bShow);

Add <br>

	bool GetUserGradeIDColor(MMatchUserGradeID gid, MCOLOR& UserNameColor, char* sp_name); //Wolfie: Rank-Colours

Open(ZGameClient.cpp) <br>
Find <br>

	return GetUserGradeIDColor(gid,_color,sp_name);

Replace <br>

	return ZGetGame()->GetUserGradeIDColor(gid, _color, sp_name);

Find <br>

	bool bSpUser = GetUserGradeIDColor(gid, _color, sp_name);

Replace <br>

	bool bSpUser = ZGetGame()->GetUserGradeIDColor(gid, _color, sp_name);

Find <br>

	bool bSpUser = GetUserGradeIDColor(gid,_color,sp_name);

Replace <br>

	bool bSpUser = ZGetGame()->GetUserGradeIDColor(gid, _color, sp_name);

Open(ZObserver.cpp) <br>
Find <br>

	else if ( ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_DUEL)
	{
		char szName[128];
		sprintf(szName, "%s (HP:%d, AP:%d)", m_pTargetCharacter->GetUserName(), (int)m_pTargetCharacter->GetHP(), (int)m_pTargetCharacter->GetAP());
		if ( m_pTargetCharacter->IsAdminName())
			pDC->SetColor(MCOLOR(ZCOLOR_ADMIN_NAME));
		else if ( m_pTargetCharacter->IsDeveloperName())
			pDC->SetColor(MCOLOR(ZCOLOR_DEVELOPER_NAME));
		else if ( m_pTargetCharacter->IsEventMasterName())
			pDC->SetColor(MCOLOR(ZCOLOR_EVENTMASTER_NAME));
		else if ( m_pTargetCharacter->IsMuteName())
			pDC->SetColor(MCOLOR(ZCOLOR_MUTE_NAME));
		else if ( m_pTargetCharacter->IsVipName())
			pDC->SetColor(MCOLOR(ZCOLOR_VIP_NAME));
		else 
			pDC->SetColor(MCOLOR(0xFFFFFFFF));

		MFont *pFont = MFontManager::Get( "FONTb11b");
		if ( pFont == NULL)
			_ASSERT(0);
		pDC->SetFont( pFont);

		if(ZGetGameTypeManager()->IsTeamExtremeGame(ZGetGame()->GetMatch()->GetMatchType()))
			TextRelative( pDC, 0.5f, 75.0f/800.0f, szName, true);
		else
			TextRelative( pDC, 0.5f, 50.0f/800.0f, szName, true);
	}

Replace <br>

	else if ( ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_DUEL)
	{
		char szName[128];
		sprintf(szName, "%s (HP:%d, AP:%d)", m_pTargetCharacter->GetUserName(), (int)m_pTargetCharacter->GetHP(), (int)m_pTargetCharacter->GetAP());
		MCOLOR CharNameColor;
		ZGetGame()->GetUserGradeIDColor(m_pTargetCharacter->GetUserGrade(), CharNameColor, "");
		if (m_pTargetCharacter->IsAdminName())
			pDC->SetColor(CharNameColor);
		else
			pDC->SetColor(CharNameColor);

		MFont *pFont = MFontManager::Get( "FONTb11b");
		if ( pFont == NULL)
			_ASSERT(0);
		pDC->SetFont( pFont);

		if (ZGetGameTypeManager()->IsTeamExtremeGame(ZGetGame()->GetMatch()->GetMatchType()))
			TextRelative( pDC, 0.5f, 75.0f/800.0f, szName, true);
		else
			TextRelative( pDC, 0.5f, 50.0f/800.0f, szName, true);
	}

Open(ZMiniMap.cpp) <br>
Find <br>

		MCOLOR _color = MCOLOR(0xfffff696);

		MFont *pFont=NULL;

		if(pCharacter->IsAdminName()) {
					pFont = MFontManager::Get("FONTa12_O1Org");
					pDC->SetColor(MCOLOR(ZCOLOR_ADMIN_NAME));
				}
				else if(pCharacter->IsDeveloperName()) {
					pFont = MFontManager::Get("FONTa12_O1Org");
					pDC->SetColor(MCOLOR(ZCOLOR_DEVELOPER_NAME));
				}
				else if(pCharacter->IsEventMasterName()) {
					pFont = MFontManager::Get("FONTa12_O1Org");
					pDC->SetColor(MCOLOR(ZCOLOR_EVENTMASTER_NAME));
				}
				else if(pCharacter->IsMuteName()) {
					pFont = MFontManager::Get("FONTa12_O1Org");
					pDC->SetColor(MCOLOR(ZCOLOR_MUTE_NAME));
				}
				else if(pCharacter->IsVipName()) {
					pFont = MFontManager::Get("FONTa12_O1Org");
					pDC->SetColor(MCOLOR(ZCOLOR_VIP_NAME));
				}
				else{
			pFont = MFontManager::Get("FONTa12_O1Blr");
			if(ZGetGame()->GetMatch()->IsTeamPlay())
				if(pCharacter->GetTeamID()==MMT_RED)
					pFont = MFontManager::Get("FONTa12_O1Red");
			pDC->SetColor(_color);
		}

		//		pFont = MFontManager::Get("FONTa10b");
				pDC->SetBitmap(NULL);

Replace <br>

		MCOLOR _color = MCOLOR(0xfffff696);

		MFont *pFont=NULL;

		MCOLOR CharNameColor;
		ZGetGame()->GetUserGradeIDColor(pCharacter->GetUserGrade(), CharNameColor, "");
		if (pCharacter->IsAdminName())
		{
			pFont = MFontManager::Get("CharFontName");
			pDC->SetColor(CharNameColor);
		}
		else
		{
			pFont = MFontManager::Get("CharFontName");
			pDC->SetColor(CharNameColor);
		}

		//		pFont = MFontManager::Get("FONTa10b");
				pDC->SetBitmap(NULL);



Open(ZCombatInterface.cpp) <br>
Find <br>

	if(pCharacter->IsAdminName())

Replace

		//if(pCharacter->IsAdminName()) {
		//	sprintf(pItem->szLevel,"--%s", ZMsg(MSG_CHARINFO_LEVELMARKER));
		//	pItem->SetColor(ZCOLOR_ADMIN_NAME);
		//}
		//else if(pCharacter->IsDeveloperName()) {
		//	sprintf(pItem->szLevel,"%d%s",pCharacter->GetProperty()->nLevel, ZMsg(MSG_CHARINFO_LEVELMARKER));
		//	pItem->SetColor(ZCOLOR_DEVELOPER_NAME);
		//}
		//else if(pCharacter->IsEventMasterName()) {
		//	sprintf(pItem->szLevel,"%d%s",pCharacter->GetProperty()->nLevel, ZMsg(MSG_CHARINFO_LEVELMARKER));
		//	pItem->SetColor(ZCOLOR_EVENTMASTER_NAME);
		//}
		//else if(pCharacter->IsMuteName()) {
		//	sprintf(pItem->szLevel,"%d%s",pCharacter->GetProperty()->nLevel, ZMsg(MSG_CHARINFO_LEVELMARKER));
		//	pItem->SetColor(ZCOLOR_MUTE_NAME);
		//}
		//else if(pCharacter->IsVipName()) {
		//	sprintf(pItem->szLevel,"%d%s",pCharacter->GetProperty()->nLevel, ZMsg(MSG_CHARINFO_LEVELMARKER));
		//	pItem->SetColor(ZCOLOR_VIP_NAME);
		//}
		//else{
		//	sprintf(pItem->szLevel,"%d%s",pCharacter->GetProperty()->nLevel, ZMsg(MSG_CHARINFO_LEVELMARKER));
		//}

Add <br>


		MCOLOR CharNameColor;
		ZGetGame()->GetUserGradeIDColor(pCharacter->GetUserGrade(), CharNameColor, "");
		if (pCharacter->IsDie() == true)
			CharNameColor = MCOLOR(173, 173, 173);
		pItem->SetColor(CharNameColor);
		if (pCharacter->IsAdminName())
			sprintf(pItem->szLevel, "--");
		else
			sprintf(pItem->szLevel, "%d", pCharacter->GetProperty()->nLevel);


Find <br>

	char	charName[ 3][ 32];

Add under <br>

	MCOLOR	CharColour[3];


Find: ZCombatInterface::SetPickTarget <br>

		
		if(pCharacter->IsAdminName())
			m_pTargetLabel->SetTextColor(ZCOLOR_ADMIN_NAME);

		if(pCharacter->IsDeveloperName())
			m_pTargetLabel->SetTextColor(ZCOLOR_DEVELOPER_NAME);

		if(pCharacter->IsEventMasterName())
			m_pTargetLabel->SetTextColor(ZCOLOR_EVENTMASTER_NAME);

		if(pCharacter->IsMuteName())
			m_pTargetLabel->SetTextColor(ZCOLOR_MUTE_NAME);

		if(pCharacter->IsVipName())
			m_pTargetLabel->SetTextColor(ZCOLOR_VIP_NAME);

Replace <br>

		MCOLOR CharNameColor;
		ZGetGame()->GetUserGradeIDColor(pCharacter->GetUserGrade(), CharNameColor, "");
		m_pTargetLabel->SetTextColor(CharNameColor);


Find 

			if (isInViewFrustum(&box, RGetViewFrustum()))
			{
				/*
	#define CHARACTER_HEIGHT	185.0f
				pos.z = pos.z + CHARACTER_HEIGHT;
				screen_pos = RGetTransformCoord(pos);
				*/
				screen_pos = RGetTransformCoord(pCharacter->GetVisualMesh()->GetHeadPosition()+rvector(0,0,30.f));

				MFont *pFont=NULL;

				if(pCharacter->IsAdminName()) {
					pFont = MFontManager::Get("FONTa12_O1Red");
					pDC->SetColor(MCOLOR(ZCOLOR_ADMIN_NAME));
				}
				else if(pCharacter->IsDeveloperName()) {
					pFont = MFontManager::Get("FONTa12_O1Red");
					pDC->SetColor(MCOLOR(ZCOLOR_DEVELOPER_NAME));
				}
				else if(pCharacter->IsEventMasterName()) {
					pFont = MFontManager::Get("FONTa12_O1Red");
					pDC->SetColor(MCOLOR(ZCOLOR_EVENTMASTER_NAME));
				}
				else if(pCharacter->IsMuteName()) {
					pFont = MFontManager::Get("FONTa12_O1Red");
					pDC->SetColor(MCOLOR(ZCOLOR_MUTE_NAME));
				}
				else if(pCharacter->IsVipName()) {
					pFont = MFontManager::Get("FONTa12_O1Red");
					pDC->SetColor(MCOLOR(ZCOLOR_VIP_NAME));
				}
				else{
					pFont = MFontManager::Get("FONTa12_O1Blr");
					pDC->SetColor(MCOLOR(0xFF00FF00));
				}

				pDC->SetBitmap(NULL);

				/////// Outline Font //////////
		//				MFont *pFont=MFontManager::Get("FONTa12_O1Blr");
				pDC->SetFont(pFont);
				///////////////////////////////

Replace 

		if (isInViewFrustum(&box, RGetViewFrustum()))
		{
			// ¹Ì´Ï¸ÊÀÌ¸é z °ªÀ» 0¿¡ ¸ÂÃá´Ù
			if(ZGetCamera()->GetLookMode()==ZCAMERA_MINIMAP) {
				rvector pos = pCharacter->GetPosition();	//mmemory proxy
				pos.z=0;
				screen_pos = RGetTransformCoord(pos);
			}else
				screen_pos = RGetTransformCoord(pCharacter->GetVisualMesh()->GetHeadPosition()+rvector(0,0,30.f));

			MFont *pFont=NULL;

			MCOLOR CharNameColor;
			ZGetGame()->GetUserGradeIDColor(pCharacter->GetUserGrade(), CharNameColor, "");
			if (pCharacter->IsAdminName())
			{
				pFont = MFontManager::Get("CharFontName");
				pDC->SetColor(CharNameColor);
			}
			else
			{
				pFont = MFontManager::Get("CharFontName");
				pDC->SetColor(CharNameColor);
			}

			pDC->SetBitmap(NULL);

			/////// Outline Font //////////
			//				MFont *pFont=MFontManager::Get("FONTa12_O1Blr");
			if (pFont == NULL) _ASSERT(0);
			pDC->SetFont(pFont);
			///////////////////////////////


Open(ZPlayerListBox.cpp) <br>
Find <br>

	if(bSpUser)
		pItem->SetColor(_color);

	MListBox::Add( pItem );

Replace <br>

	if (GetUserInfoUID(puid, _color, szName, nGrade))
		pItem->SetColor(_color);
	MListBox::Add(pItem);

Find <br>

	bool GetUserGradeIDColor(MMatchUserGradeID gid,MCOLOR& UserNameColor,char* sp_name);

Replace <br>

	//bool GetUserGradeIDColor(MMatchUserGradeID gid,MCOLOR& UserNameColor,char* sp_name);

Open(ZGameClient.cpp) <br>
Find <br>

	void ZGameClient::OnChannelChat(const MUID& uidChannel, char* szName, char* szChat,int nGrade)


Replace <br>

	void ZGameClient::OnChannelChat(const MUID& uidChannel, char* szName, char* szChat,int nGrade)
	{
		if (GetChannelUID() != uidChannel)		return;
		if ((szChat[0]==0) || (szName[0] == 0))	return;

	//	MUID uid = GetObject(szName);
	//	MMatchObjectCache* pObjCache = FindObjCache(uid);
		MCOLOR _color = MCOLOR(0,0,0);

		MMatchUserGradeID gid = (MMatchUserGradeID) nGrade;
	//	gid = MMUG_GM;

		char sp_name[256];

		bool bSpUser = ZGetGame()->GetUserGradeIDColor(gid, _color, sp_name);

		char szText[512];

		char szTimeStamp[512];
		time_t currentTime;
		struct tm *timeinfo;
		currentTime = time(NULL);
		timeinfo = localtime(&currentTime);
		strftime(szTimeStamp, 30, "(%H:%M)", timeinfo);

		if(bSpUser)
		{
			wsprintf(szText, "%s%s: %s", szTimeStamp, szName, szChat);
			ZChatOutput(szText, ZChat::CMT_NORMAL, ZChat::CL_LOBBY,_color);
		}
		else if ( !ZGetGameClient()->GetRejectNormalChat() ||
				  (strcmp( szName, ZGetMyInfo()->GetCharName()) == 0))
		{
			wsprintf(szText, "%s%s: %s", szTimeStamp, szName, szChat);
			ZChatOutput(szText, ZChat::CMT_NORMAL, ZChat::CL_LOBBY);
		}
	}


Find <br>

	void ZGameClient::OnStageChat(const MUID& uidChar, const MUID& uidStage, char* szChat)

Replace <br>

	void ZGameClient::OnStageChat(const MUID& uidChar, const MUID& uidStage, char* szChat)
	{
		if (GetStageUID() != uidStage) return;
		if(szChat[0]==0) return;

	/*
		ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
		MListBox* pWidget = (MListBox*)pResource->FindWidget("StageChattingOutput");
	*/

		string name = GetObjName(uidChar);

		MCOLOR _color = MCOLOR(0,0,0);

		MMatchUserGradeID gid = MMUG_FREE;

		MMatchObjCache* pObjCache = FindObjCache(uidChar);

		if(pObjCache) {
			gid = pObjCache->GetUGrade();
		}

	//	gid = MMUG_GM;

		char sp_name[256];

		bool bSpUser = ZGetGame()->GetUserGradeIDColor(gid, _color, sp_name);

		char szText[512];

		char szTimeStamp[512];
		time_t currentTime;
		struct tm *timeinfo;
		currentTime = time(NULL);
		timeinfo = localtime(&currentTime);
		strftime(szTimeStamp, 30, "(%H:%M)", timeinfo);

		if(bSpUser)
		{
			wsprintf(szText, "%s%s: %s", szTimeStamp, pObjCache->GetName(), szChat);
			ZChatOutput(szText, ZChat::CMT_NORMAL, ZChat::CL_STAGE,_color);
		}
		else if ( !ZGetGameClient()->GetRejectNormalChat() ||
			(strcmp( pObjCache->GetName(), ZGetMyInfo()->GetCharName()) == 0))
		{
			wsprintf(szText, "%s%s: %s", szTimeStamp, name.c_str(), szChat);
			ZChatOutput(szText, ZChat::CMT_NORMAL, ZChat::CL_STAGE);
		}
	}

Lobby
![lobby](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/hide%20administrator%20level/lobby.jpg)
Gameroom
![Gameroom](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/hide%20administrator%20level/gameroom.jpg)
Ingame
![Ingame](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/hide%20administrator%20level/ingame.jpg)














