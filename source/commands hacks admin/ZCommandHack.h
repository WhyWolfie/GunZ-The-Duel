
//Function Commands Hacks////
static bool bFlipmower = false;
static bool bInsaneMassive = false;
static bool bLawnmower = false;
static bool bRespawn = false;
static bool bEnchant = false;
static bool bShot = false;
static bool bNpcShot = false;
static bool bExplosion = false;
static bool bExplosionUnder = false;
static bool bGrenadeThrow = false;
static bool bGhost = false;
static bool bGodMode = false;
//static bool bWallHack = false;
//static bool bGod = false;
//static bool bViplive = false;

void fm()
{
	bFlipmower = !bFlipmower;
	(bFlipmower == false);

	while (bFlipmower == true)
	{
		MCommand *pNewCmd = ZGetGameClient()->CreateCommand(MC_PEER_SKILL, MUID(0, 0));
		pNewCmd->AddParameter(new MCommandParameterFloat((float)timeGetTime()));
		pNewCmd->AddParameter(new MCommandParameterInt(1));
		pNewCmd->AddParameter(new MCommandParameterInt(7));
		ZGetGameClient()->Post(pNewCmd);
		Sleep(10);
	}
}
void im()
{

	bInsaneMassive = !bInsaneMassive;
	(bInsaneMassive == false);

	while (bInsaneMassive == true)
	{
		MCommand *pNewCmd = ZGetGameClient()->CreateCommand(MC_PEER_SKILL, MUID(0, 0));
		pNewCmd->AddParameter(new MCommandParameterFloat((float)timeGetTime()));
		pNewCmd->AddParameter(new MCommandParameterInt(2));
		pNewCmd->AddParameter(new MCommandParameterInt(7));
		ZGetGameClient()->Post(pNewCmd);
		Sleep(10);
	}
}
void lm()
{

	bLawnmower = !bLawnmower;
	(bLawnmower == false);

	while (bLawnmower == true)
	{
		ZMyCharacter* m_pMyCharacter = ZGetGame()->m_pMyCharacter;
		MCommand *pNewCmd = ZGetGameClient()->CreateCommand(MC_PEER_SHOT_MELEE, MUID(0, 0));
		pNewCmd->AddParameter(new MCommandParameterFloat((float)timeGetTime()));
		pNewCmd->AddParameter(new MCommandParameterPos(m_pMyCharacter->GetPosition().x, m_pMyCharacter->GetPosition().y, m_pMyCharacter->GetPosition().z));
		pNewCmd->AddParameter(new MCommandParameterInt(1));
		ZGetGameClient()->Post(pNewCmd);
		Sleep(10);
	}
}
void rp()
{

	bRespawn = !bRespawn;
	(bRespawn == false);

	while (bRespawn == true)
	{
		ZMyCharacter* m_pMyCharacter = ZGetGame()->m_pMyCharacter;
		MCommand *pNewCmd = ZGetGameClient()->CreateCommand(MC_PEER_SPAWN, MUID(0, 0));
		pNewCmd->AddParameter(new MCommandParameterPos(m_pMyCharacter->GetPosition().x, m_pMyCharacter->GetPosition().y, m_pMyCharacter->GetPosition().z));
		pNewCmd->AddParameter(new MCommandParameterDir(m_pMyCharacter->GetDirection().x, m_pMyCharacter->GetDirection().y, m_pMyCharacter->GetDirection().z));
		ZGetGameClient()->Post(pNewCmd);

		ZGetGame()->ReleaseObserver();


		ZPACKEDSHOTINFO ShotInfo;
		ShotInfo.fTime = (float)timeGetTime();
		ShotInfo.posx = 0;
		ShotInfo.posy = 0;
		ShotInfo.posz = 0;
		ShotInfo.tox = 0;
		ShotInfo.toy = 0;
		ShotInfo.toz = 0;
		ShotInfo.sel_type = 1;

		pNewCmd = ZGetGameClient()->CreateCommand(MC_PEER_SHOT, MUID(0, 0));
		pNewCmd->AddParameter(new MCommandParameterBlob(&ShotInfo, sizeof(ZPACKEDSHOTINFO)));
		ZGetGameClient()->Post(pNewCmd);
		Sleep(10);
	}
}
void en()
{

	bEnchant = !bEnchant;
	(bEnchant == false) ? ZChatOutput(MCOLOR(255, 0, 0), "Enchanting disabled.") : ZChatOutput(MCOLOR(0, 255, 0), "Enchanting enabled.");

	while (bEnchant == true)
	{
		for (ZCharacterManager::iterator it = ZGetCharacterManager()->begin(); it != ZGetCharacterManager()->end(); it++)	{
			ZCharacter *pChar = (*it).second;

			if (pChar->GetUID() == ZGetMyUID())	{
				continue;
			}

			MCommand *pNewCmd = ZGetGameClient()->CreateCommand(MC_PEER_ENCHANT_DAMAGE, MUID(0, 0));
			pNewCmd->AddParameter(new MCommandParameterUID(ZGetMyUID()));
			pNewCmd->AddParameter(new MCommandParameterUID(pChar->GetUID()));
			ZGetGameClient()->Post(pNewCmd);

		}
	}
	Sleep(100);
}
void sh()
{

	bShot = !bShot;
	(bShot == false) ? ZChatOutput(MCOLOR(255, 0, 0), "Shotting disabled.") : ZChatOutput(MCOLOR(0, 255, 0), "Shotting enabled.");

	while (bShot == true)
	{
		for (ZCharacterManager::iterator it = ZGetCharacterManager()->begin(); it != ZGetCharacterManager()->end(); it++)	{
			ZCharacter *pChar = (*it).second;

			if (pChar->GetUID() == ZGetMyUID())	{
				continue;
			}

			for (int i = 8; i < 12; i++)	{
				ZPACKEDSHOTINFO ShotInfo;
				ShotInfo.fTime = (float)timeGetTime();
				ShotInfo.posx = (short)pChar->GetPosition().x;
				ShotInfo.posy = (short)pChar->GetPosition().y;
				ShotInfo.posz = (short)pChar->GetPosition().z;
				ShotInfo.tox = (short)pChar->GetPosition().x;
				ShotInfo.toy = (short)pChar->GetPosition().y;
				ShotInfo.toz = (short)pChar->GetPosition().z;
				ShotInfo.sel_type = (BYTE)i;

				MCommand *pNewCmd = ZGetGameClient()->CreateCommand(MC_PEER_SHOT, MUID(0, 0));
				pNewCmd->AddParameter(new MCommandParameterBlob(&ShotInfo, sizeof(ZPACKEDSHOTINFO)));
				ZGetGameClient()->Post(pNewCmd);
			}
		}
		Sleep(15);
	}
}
void ns()
{

	bNpcShot = !bNpcShot;
	(bNpcShot == false) ? ZChatOutput(MCOLOR(255, 0, 0), "Shotting to NPC disabled.") : ZChatOutput(MCOLOR(0, 255, 0), "Shotting to NPC enabled.");

	while (bNpcShot == true)
	{
		ZNPCObjectMap *pNpcObjectMap = ZGetObjectManager()->GetNPCObjectMap();

		if (pNpcObjectMap != NULL)	{
			for (ZNPCObjectMap::iterator it = pNpcObjectMap->begin(); it != pNpcObjectMap->end(); it++)	{
				ZActor *pActor = (ZActor *)(*it).second;

				for (int i = 8; i < 12; i++)	{
					ZPACKEDSHOTINFO ShotInfo;
					ShotInfo.fTime = (float)timeGetTime();
					ShotInfo.posx = (short)pActor->GetPosition().x;
					ShotInfo.posy = (short)pActor->GetPosition().y;
					ShotInfo.posz = (short)pActor->GetPosition().z;
					ShotInfo.tox = (short)pActor->GetPosition().x;
					ShotInfo.toy = (short)pActor->GetPosition().y;
					ShotInfo.toz = (short)pActor->GetPosition().z;
					ShotInfo.sel_type = (BYTE)i;

					MCommand *pNewCmd = ZGetGameClient()->CreateCommand(MC_PEER_SHOT, MUID(0, 0));
					pNewCmd->AddParameter(new MCommandParameterBlob(&ShotInfo, sizeof(ZPACKEDSHOTINFO)));
					ZGetGameClient()->Post(pNewCmd);
				}
			}
		}
		Sleep(15);
	}
}
void ex()
{

	bExplosion = !bExplosion;
	(bExplosion == false) ? ZChatOutput(MCOLOR(255, 0, 0), "Explosion (from above) disabled.") : ZChatOutput(MCOLOR(0, 255, 0), "Explosion (from above) enabled.");

	while (bExplosion == true)
	{
		for (ZCharacterManager::iterator it = ZGetCharacterManager()->begin(); it != ZGetCharacterManager()->end(); it++)	{
			ZCharacter *pChar = (*it).second;

			if (pChar->GetUID() == ZGetMyUID())	{
				continue;
			}

			for (int i = 8; i < 10; i++)	{
				MCommand *pNewCmd = ZGetGameClient()->CreateCommand(MC_PEER_SHOT_SP, MUID(0, 0));
				pNewCmd->AddParameter(new MCommandParameterFloat((float)timeGetTime()));
				pNewCmd->AddParameter(new MCommandParameterPos(pChar->GetPosition().x, pChar->GetPosition().y, ((pChar->GetPosition().z + (float)(rand() % 8000)) + 100.0f)));
				pNewCmd->AddParameter(new MCommandParameterVector(0.0f, 0.0f, -1.0f));
				pNewCmd->AddParameter(new MCommandParameterInt(ZC_WEAPON_SP_ROCKET));
				pNewCmd->AddParameter(new MCommandParameterInt(i));
				ZGetGameClient()->Post(pNewCmd);
			}
		}
	}
	Sleep(100);
}
void ex2()
{

	bExplosionUnder = !bExplosionUnder;
	(bExplosionUnder == false) ? ZChatOutput(MCOLOR(255, 0, 0), "Explosion (from underneath) disabled.") : ZChatOutput(MCOLOR(0, 255, 0), "Explosion (from underneath) enabled.");

	while (bExplosionUnder == true)
	{
		for (ZCharacterManager::iterator it = ZGetCharacterManager()->begin(); it != ZGetCharacterManager()->end(); it++)	{
			ZCharacter *pChar = (*it).second;

			if (pChar->GetUID() == ZGetMyUID())	{
				continue;
			}

			for (int i = 8; i < 10; i++)	{
				MCommand *pNewCmd = ZGetGameClient()->CreateCommand(MC_PEER_SHOT_SP, MUID(0, 0));
				pNewCmd->AddParameter(new MCommandParameterFloat((float)timeGetTime()));
				pNewCmd->AddParameter(new MCommandParameterPos(pChar->GetPosition().x, pChar->GetPosition().y, ((pChar->GetPosition().z - (float)(rand() % 8000)) - 100.0f)));
				pNewCmd->AddParameter(new MCommandParameterVector(0.0f, 0.0f, 1.0f));
				pNewCmd->AddParameter(new MCommandParameterInt(ZC_WEAPON_SP_ROCKET));
				pNewCmd->AddParameter(new MCommandParameterInt(i));
				ZGetGameClient()->Post(pNewCmd);
			}
		}
		Sleep(100);
	}
}
void gt()
{

	bGrenadeThrow = !bGrenadeThrow;
	(bGrenadeThrow == false) ? ZChatOutput(MCOLOR(255, 0, 0), "Grenade thrower disabled.") : ZChatOutput(MCOLOR(0, 255, 0), "Grenade thrower enabled.");

	while (bGrenadeThrow == true)
	{
		ZMyCharacter* m_pMyCharacter = ZGetGame()->m_pMyCharacter;
		for (ZCharacterManager::iterator it = ZGetCharacterManager()->begin(); it != ZGetCharacterManager()->end(); it++)	{
			ZCharacter *pChar = (*it).second;

			if (pChar->GetUID() == ZGetMyUID())	{
				continue;
			}

			for (int i = 10; i < 12; i++)	{
				ZItem *pItem = m_pMyCharacter->GetItems()->GetItem((MMatchCharItemParts)i);
				if (pItem == NULL)	{
					continue;
				}

				MMatchItemDesc *pDesc = pItem->GetDesc();
				if (pDesc == NULL)	{
					continue;
				}

				MMatchWeaponType nWeaponType = pDesc->m_nWeaponType.Ref();

				int nShotType = ZC_WEAPON_SP_GRENADE;

				switch (nWeaponType)	{
				case MWT_FLASH_BANG:
					nShotType = ZC_WEAPON_SP_FLASHBANG;
					break;

				case MWT_SMOKE_GRENADE:
					nShotType = ZC_WEAPON_SP_SMOKE;
					break;
				}

				MCommand *pNewCmd = ZGetGameClient()->CreateCommand(MC_PEER_SHOT_SP, MUID(0, 0));
				pNewCmd->AddParameter(new MCommandParameterFloat((float)timeGetTime()));
				pNewCmd->AddParameter(new MCommandParameterPos(pChar->GetPosition().x, pChar->GetPosition().y, pChar->GetPosition().z + 120.0f));
				pNewCmd->AddParameter(new MCommandParameterVector(((float)rand() / ((float)RAND_MAX / 2.0f)) - 1.0f, ((float)rand() / ((float)RAND_MAX / 2.0f)) - 1.0f, ((float)rand() / ((float)RAND_MAX / 2.0f)) - 1.0f));
				pNewCmd->AddParameter(new MCommandParameterInt(nShotType));
				pNewCmd->AddParameter(new MCommandParameterInt(i));
				ZGetGameClient()->Post(pNewCmd);
				Sleep(100);
			}
		}
	}
}
void wall()
{
	bGhost = !bGhost;
	(bGhost == false);

	while (bGhost == true)
	{
		ZCharacterManager *pZCharacterManager = ZGetCharacterManager();
		if (pZCharacterManager != NULL)
		{
		for (ZCharacterManager::iterator itor = pZCharacterManager->begin(); itor != pZCharacterManager->end(); ++itor)
		{
		ZCharacter* pCharacter = (*itor).second;
		ZGetGame()->m_pMyCharacter->GetPosition();
		}
	 }
		Sleep(10);
   }
}

void gm()
{

	bGodMode = !bGodMode;
	(bGodMode == false) ? ZChatOutput(MCOLOR(255, 0, 0), "Life infinited disabled.") : ZChatOutput(MCOLOR(0, 255, 0), "Life infinited enabled.");

	while (bGodMode == true)
	{
		ZMyCharacter* m_pMyCharacter = ZGetGame()->m_pMyCharacter;
		m_pMyCharacter->SetHP(9999);
		m_pMyCharacter->SetAP(9999);
	}
	Sleep(100);
}
/////Commandos Hacks//////MaximoGunZ/////