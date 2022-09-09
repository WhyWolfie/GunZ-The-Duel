Open (MFeatureDefine.h) <br>
Add this

    #define _LADDERGAME
    
Open (MMatchDBMgr.cpp)
Find

    MMatchDBMgr::GetLadderTeamID

Replace


    bool MMatchDBMgr::GetLadderTeamID(const int nTeamTableIndex, const int* pnMemberCIDArray, const int nMemberCount, int* pnoutTID)
    {
      _STATUS_DB_START;

      if (!CheckOpen()) return false;


      CString strSQL;

      // ÇöÀç´Â 4¸í ÆÀ¹Û¿¡ Áö¿øÇÏÁö ¾Ê´Â´Ù.
      if ((nTeamTableIndex == 4) && (nMemberCount == 4))
      {
        strSQL.Format(g_szDB_GET_LADDER_TEAM4_ID, pnMemberCIDArray[0], pnMemberCIDArray[1], pnMemberCIDArray[2], pnMemberCIDArray[3]);
      }

    #ifdef _LADDERGAME
      else if ((nTeamTableIndex == 1) && (nMemberCount == 1))
      {
        // for test
        strSQL.Format(g_szDB_GET_LADDER_TEAM4_ID, pnMemberCIDArray[0], 1, 1, 1);
      }
      else if ((nTeamTableIndex == 2) && (nMemberCount == 2))
      {
        // for test
        strSQL.Format(g_szDB_GET_LADDER_TEAM4_ID, pnMemberCIDArray[0], pnMemberCIDArray[1], 1, 1);
      }
    #endif
      else
      {
        return false;
      }

      CODBCRecordset rs(&m_DB);


      try 
      {
        rs.Open(strSQL, CRecordset::forwardOnly, CRecordset::readOnly);
      } 
      catch(CDBException* e)
      {

        ExceptionHandler(strSQL, e);
        *pnoutTID = 0;
        return false;
      }

      if ((rs.IsOpen() == FALSE) || (rs.GetRecordCount() <= 0) || (rs.IsBOF()==TRUE)) 
      {
        *pnoutTID = 0;
        return false;
      }

      char szFieldName[64] = "";

      //#ifdef _DEBUG
      strcpy(szFieldName, "TID4");	// Áö±ÝÀº ¸ðµÎ´Ù TID4·Î ÅëÀÏÁß
      //#else
      //	sprintf(szFieldName, "TID%d", nTeamTableIndex);
      //#endif

      *pnoutTID = rs.Field(szFieldName).AsInt();


      _STATUS_DB_END(42);
      return true;


    }
    
Open (MTeamGameStrategy.cpp) <br>
Find <br>

    MClanGameStrategy::MClanGameStrategy

Replace

    MClanGameStrategy::MClanGameStrategy()
    {
    #ifdef _LADDERGAME
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
    #endif // _LADDERGAME

      for (int i = MLADDERTYPE_NORMAL_2VS2; i <= MLADDERTYPE_NORMAL_3VS3; i++) //CLANWAR MAPS22
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

      for (int i = MLADDERTYPE_NORMAL_4VS4; i < MLADDERTYPE_MAX; i++)
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

Find

    MClanGameStrategy::GetRandomMap(int nTeamMember)

Replace

    int MClanGameStrategy::GetRandomMap(int nTeamMember)
    {
      int nVecIndex = 0;
      int nMaxSize = 0;
      switch (nTeamMember)
      {
    #ifdef _LADDERGAME
      case 1:
        nVecIndex = MLADDERTYPE_NORMAL_1VS1;
        break;
    #endif // _LADDERGAME
      case 2:
        nVecIndex = MLADDERTYPE_NORMAL_2VS2;
        break;
      case 3:
        nVecIndex = MLADDERTYPE_NORMAL_3VS3;
        break;
      case 4:
        nVecIndex = MLADDERTYPE_NORMAL_4VS4;
        break;
      };

      nMaxSize = (int)m_RandomMapVec[nVecIndex].size();

      int nRandomMapIndex = 0;
      int nRandomMap = 0;

      if (nMaxSize != 0) {
        nRandomMapIndex = rand() % nMaxSize;
        nRandomMap = m_RandomMapVec[nVecIndex][nRandomMapIndex];
      }

      return nRandomMap;
    }

Open (ZInterfaceListener.cpp)
Find

    case MSM_CLAN:

Replace

        case MSM_CLAN:
          {
            bool bRightMember = false;
            for (int i = 0; i < MLADDERTYPE_MAX; i++)
            {
              if ((g_nNeedLadderMemberCount[i]-1) == nCount)
              {
                bRightMember = true;
                break;
              }
            }

            // ÀûÀýÇÑ ¼öÀÇ ÆÀÀÌ¸é

            if((0<nCount) && (bRightMember))
            {
              ZGetGameClient()->RequestProposal(MPROPOSAL_CLAN_INVITE, ppNames, nCount);
            } 
    #ifdef _LADDERGAME
            // if this MChannel - This Name (##############) execute this
            else if (nCount == 0)
            {
              // ÀÚ±â ÀÚ½Å¸¸ÀÏ¶§
              char szMember[1][MATCHOBJECT_NAME_LENGTH];
              char* ppMember[1];

              ppMember[0] = szMember[0];
              strcpy(szMember[0], ZGetMyInfo()->GetCharName());

              // Balance ¿É¼Ç
              int nBalancedMatching = 0;
              ZIDLResource* pResource = ZGetGameInterface()->GetIDLResource();
              MButton* pButton = (MButton*)pResource->FindWidget("BalancedMatchingCheckBox");
              if ((pButton) && (pButton->GetCheck()))
              {
                nBalancedMatching = 1;
              }
              int nAntiLead = 0;
              MButton* pButton2 = (MButton*)pResource->FindWidget("AntiLeadCheckBox");
              if ((pButton2) && (pButton2->GetCheck()))
              {
                nAntiLead = 1;
              }
              ZPostLadderRequestChallenge(ppMember, 1, nBalancedMatching, nAntiLead);
            }
    #else
            else if (nCount == 0)
            {
              // ÀÚ±â ÀÚ½Å¸¸ÀÏ¶§
              char szMember[1][MATCHOBJECT_NAME_LENGTH];
              char* ppMember[1];

              ppMember[0] = szMember[0];
              strcpy(szMember[0], ZGetMyInfo()->GetCharName());

              // Balance ¿É¼Ç
              int nBalancedMatching = 0;
              ZIDLResource* pResource = ZGetGameInterface()->GetIDLResource();
              MButton* pButton = (MButton*)pResource->FindWidget("BalancedMatchingCheckBox");
              if ((pButton) && (pButton->GetCheck()))
              {
                nBalancedMatching = 1;
              }
              int nAntiLead = 0;
              MButton* pButton2 = (MButton*)pResource->FindWidget("AntiLeadCheckBox");
              if ((pButton2) && (pButton2->GetCheck()))
              {
                nAntiLead = 1;
              }
              ZPostLadderRequestChallenge(ppMember, 1, nBalancedMatching, nAntiLead);
            }
    #endif
            // else normal proposal
            else
            {
              ZChatOutput(MCOLOR(ZCOLOR_CHAT_SYSTEM), 
                ZMsg(MSG_LADDER_INVALID_COUNT) );
            }
          }
          break;
        }
      }
    END_IMPLEMENT_LISTENER();


![img](https://i.imgur.com/4lBnP9z.png)
