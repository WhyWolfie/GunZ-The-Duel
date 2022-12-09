Open(MTeamGameStrategy.cpp) <br>
Find <br>

	case 1:
		nVecIndex = MLADDERTYPE_NORMAL_1VS1;
		break;
    
Replace <br>

      int nVecIndex = 0;
      int nMaxSize = 0;
      switch (nTeamMember)
      {
      case 1:
        nVecIndex = MLADDERTYPE_NORMAL_1VS1;
        break;
      case 2:
        nVecIndex = MLADDERTYPE_NORMAL_2VS2;
        break;
      case 3:
        nVecIndex = MLADDERTYPE_NORMAL_3VS3;
        break;
      case 4:
        nVecIndex = MLADDERTYPE_NORMAL_4VS4;
        break;
      case 5:
        nVecIndex = MLADDERTYPE_NORMAL_5VS5;
        break;
      case 6:
        nVecIndex = MLADDERTYPE_NORMAL_6VS6;
        break;
      case 7:
        nVecIndex = MLADDERTYPE_NORMAL_7VS7;
        break;
      case 8:
        nVecIndex = MLADDERTYPE_NORMAL_8VS8;
        break;
      };

      nMaxSize = (int)m_RandomMapVec[nVecIndex].size();

      int nRandomMapIndex = 0;
      int nRandomMap = 0;

      if (nMaxSize != 0) 
      {
        nRandomMapIndex = rand() % nMaxSize;
        nRandomMap = m_RandomMapVec[nVecIndex][nRandomMapIndex];
      }

      return nRandomMap;
    }


Find <br>

	for (MUIDRefCache::iterator itor=pStage->GetObjBegin(); itor!=pStage->GetObjEnd(); itor++) 
	{
    
Replace <br>

	for (MUIDRefCache::iterator itor=pStage->GetObjBegin(); itor!=pStage->GetObjEnd(); itor++) 
	{
		MMatchObject* pObj = (MMatchObject*)(*itor).second;
		if (IsEnabledObject(pObj))
		{
			if (pObj->GetTeam() == nWinnerTeam)
			{
				if (pObj->GetCharInfo()->m_ClanInfo.GetClanID() != pWinnerClan->GetCLID())
					continue;

				WinnerObjUIDs.push_back(pObj->GetUID());
				strcat(szWinnerMembers, pObj->GetCharInfo()->m_szName);
				strcat(szWinnerMembers, " ");
			}
			else
			{
				if (pObj->GetCharInfo()->m_ClanInfo.GetClanID() != pLoserClan->GetCLID())
					continue;

				strcat(szLoserMembers, pObj->GetCharInfo()->m_szName);
				strcat(szLoserMembers, " ");
			}
		}
	}


Find: <br>

    for (int i = MLADDERTYPE_NORMAL_1VS1; i <= MLADDERTYPE_NORMAL_2VS2; i++)

Replace <br>

      for (int i = MLADDERTYPE_NORMAL_1VS1; i <= MLADDERTYPE_NORMAL_2VS2; i++)
      {
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_MANSION, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_PRISON_II, 5);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_BATTLE_ARENA, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_TOWN, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_DUNGEON, 2);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_PORT, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_CASTLE, 5);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_ISLAND, 5);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_GARDEN, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_FACTORY, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_HIGH_HAVEN, 10);
      }
      for (int i = MLADDERTYPE_NORMAL_2VS2; i <= MLADDERTYPE_NORMAL_3VS3; i++)
      {
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_MANSION, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_PRISON_II, 5);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_BATTLE_ARENA, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_TOWN, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_DUNGEON, 2);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_PORT, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_CASTLE, 5);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_ISLAND, 5);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_GARDEN, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_FACTORY, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_HIGH_HAVEN, 10);
      }
      for (int i = MLADDERTYPE_NORMAL_3VS3; i <= MLADDERTYPE_NORMAL_4VS4; i++)
      {
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_MANSION, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_PRISON_II, 5);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_BATTLE_ARENA, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_TOWN, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_DUNGEON, 2);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_PORT, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_CASTLE, 5);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_ISLAND, 5);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_GARDEN, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_FACTORY, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_HIGH_HAVEN, 10);
      }

      for (int i = MLADDERTYPE_NORMAL_5VS5; i < MLADDERTYPE_MAX; i++)
      {
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_MANSION, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_PRISON_II, 5);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_BATTLE_ARENA, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_TOWN, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_DUNGEON, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_PORT, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_ISLAND, 5);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_GARDEN, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_CASTLE, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_FACTORY, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_HIGH_HAVEN, 10);
      }
      for (int i = MLADDERTYPE_NORMAL_6VS6; i < MLADDERTYPE_MAX; i++)
      {
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_MANSION, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_PRISON_II, 5);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_BATTLE_ARENA, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_TOWN, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_DUNGEON, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_PORT, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_ISLAND, 5);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_GARDEN, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_CASTLE, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_FACTORY, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_HIGH_HAVEN, 10);
      }
      for (int i = MLADDERTYPE_NORMAL_7VS7; i < MLADDERTYPE_MAX; i++)
      {
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_MANSION, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_PRISON_II, 5);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_BATTLE_ARENA, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_TOWN, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_DUNGEON, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_PORT, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_ISLAND, 5);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_GARDEN, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_CASTLE, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_FACTORY, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_HIGH_HAVEN, 10);
      }
      for (int i = MLADDERTYPE_NORMAL_8VS8; i < MLADDERTYPE_MAX; i++)
      {
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_MANSION, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_PRISON_II, 5);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_BATTLE_ARENA, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_TOWN, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_DUNGEON, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_PORT, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_ISLAND, 5);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_GARDEN, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_CASTLE, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_FACTORY, 10);
        InsertLadderRandomMap(m_RandomMapVec[i], MMATCH_MAP_HIGH_HAVEN, 10);
      }
    }














