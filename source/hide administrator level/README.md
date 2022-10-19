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
        
        
        
        
        

