Not completed

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
				if ( pCharacter->GetUID() == pDuel->QInfo.m_uidChampion)
				{
					if ( ZGetMyUID() == pDuel->QInfo.m_uidChampion)
					{
						// Draw victory
						ZGetCombatInterface()->DrawVictory( pDC, 210, 86, pDuel->QInfo.m_nVictory);
					}
					else
					{
						if(pCharacter->IsAdminName())
						sprintf( charName[ 0], "%s--  %s", ZMsg( MSG_CHARINFO_LEVELMARKER), pCharacter->GetUserName());
						else
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

				else if ( pCharacter->GetUID() == pDuel->QInfo.m_uidChallenger)
				{
					if (ZGetMyUID() != pDuel->QInfo.m_uidChallenger) {
						if (pCharacter->IsAdminName())
							sprintf(charName[0], "%s--  %s", ZMsg(MSG_CHARINFO_LEVELMARKER), pCharacter->GetUserName());
						else
							sprintf(charName[0], "%s%d  %s", ZMsg(MSG_CHARINFO_LEVELMARKER), pCharacter->GetProperty()->nLevel, pCharacter->GetUserName());
					}
					bIsChallengerDie = pCharacter->IsDie();
				}

				// Waiting 1
				else if (pCharacter->GetUID() == pDuel->QInfo.m_WaitQueue[0]) {
					if(pCharacter->IsAdminName())
						sprintf( charName[ 1], "%s--  %s", ZMsg( MSG_CHARINFO_LEVELMARKER), pCharacter->GetUserName());
						else
						sprintf( charName[ 1], "%s%d  %s", ZMsg( MSG_CHARINFO_LEVELMARKER), pCharacter->GetProperty()->nLevel, pCharacter->GetUserName());
				}
				// Waiting 2
				else if (pCharacter->GetUID() == pDuel->QInfo.m_WaitQueue[1]) {
					if(pCharacter->IsAdminName())
						sprintf( charName[ 2], "%s--  %s", ZMsg( MSG_CHARINFO_LEVELMARKER), pCharacter->GetUserName());
						else
						sprintf( charName[ 2], "%s%d  %s", ZMsg( MSG_CHARINFO_LEVELMARKER), pCharacter->GetProperty()->nLevel, pCharacter->GetUserName());
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

































