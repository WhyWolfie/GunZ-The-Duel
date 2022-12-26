ZGame.cpp <br>
for case MMATCH_ROUNDSTATE_FINISH: and add these <br>

			char szRotationMsg[50];
			sprintf(szRotationMsg, "The base rotation has started!");
			ZGetGameInterface()->GetCombatInterface()->m_Chat.OutputChatMsg(szRotationMsg);

ZMatch.cpp
for void ZMatch::InitCharactersPosition() and add these, compare the code that is already written there, which is similar to what you are going to put, here it is not copy and paste, be careful. <br>

	if (IsTeamPlay())
	{
		int nSpawnIndex[2] = { 0, 0 };
		auto nSpawn = 0;

		for (ZCharacterManager::iterator itor = ZGetGame()->m_CharacterManager.begin();
			itor != ZGetGame()->m_CharacterManager.end(); ++itor)
		{
			ZCharacter* pCharacter = (ZCharacter*)(*itor).second;
			for (int i = 0; i < 2; i++)
			{
				if (pCharacter->GetTeamID() == MMT_RED + i)
				{
					if ((IsTeamPlay) && GetCurrRound() > 0 && GetCurrRound() % 2)
					{
						if (i == 0)
							nSpawn = 1;
						else
							nSpawn = 0;
					}
					else
						nSpawn = i;

					ZMapSpawnData* pSpawnData = ZGetGame()->GetMapDesc()->GetSpawnManager()->GetTeamData(nSpawn, nSpawnIndex[nSpawn]);

					if (pSpawnData != NULL)
					{
						pCharacter->SetPosition(pSpawnData->m_Pos);
						pCharacter->SetDirection(pSpawnData->m_Dir);

						nSpawnIndex[nSpawn]++;
					}
				}
			}
		}
		return;
	}



