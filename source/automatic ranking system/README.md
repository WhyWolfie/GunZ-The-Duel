Open(MMatchDBMgr.cpp) <br>
Find <br>

    bool MMatchDBMgr::RewardCharBattleTimeReward

Add Under <br>


    TCHAR spUpdatePlayerWars[] = _T("{CALL spPWRegularUpdateRanking}");
    TCHAR spUpdateClanRanking[] = _T("{CALL spRegularUpdateClanRanking}");
    TCHAR spUpdateSurvivalRanking[] = _T("{CALL spFetchSurvivalRanking}");
    TCHAR spUpdateGunzSystem[] = _T("{CALL spUpdateGunzSystem}");

    bool MMatchDBMgr::UpdatePlayerWars()
    {
      _STATUS_DB_START;
      if (!CheckOpen()) return false;

      CString strSQL;
      try
      {
        strSQL.Format(spUpdatePlayerWars);
        m_DB.ExecuteSQL(strSQL);
      }
      catch (CDBException* e)
      {
        ExceptionHandler(strSQL, e);
        return false;
      }

      _STATUS_DB_END(36);
      return true;
    }
    bool MMatchDBMgr::UpdateClanRanking()
    {
      _STATUS_DB_START;
      if (!CheckOpen()) return false;

      CString strSQL;
      try
      {
        strSQL.Format(spUpdateClanRanking);
        m_DB.ExecuteSQL(strSQL);
      }
      catch (CDBException* e)
      {
        ExceptionHandler(strSQL, e);
        return false;
      }

      _STATUS_DB_END(36);
      return true;
    }
    bool MMatchDBMgr::UpdateSurvivalRanking()
    {
      _STATUS_DB_START;
      if (!CheckOpen()) return false;

      CString strSQL;
      try
      {
        strSQL.Format(spUpdateSurvivalRanking);
        m_DB.ExecuteSQL(strSQL);
      }
      catch (CDBException* e)
      {
        ExceptionHandler(strSQL, e);
        return false;
      }

      _STATUS_DB_END(36);
      return true;
    }

    bool MMatchDBMgr::UpdateGunzSystem()
    {
      _STATUS_DB_START;
      if (!CheckOpen()) return false;

      CString strSQL;
      try
      {
        strSQL.Format(spUpdateGunzSystem);
        m_DB.ExecuteSQL(strSQL);
      }
      catch (CDBException* e)
      {
        ExceptionHandler(strSQL, e);
        return false;
      }

      _STATUS_DB_END(36);
      return true;
    }

Open(MMatchDBMgr.h) <br>
Find <br>

    bool RewardCharBattleTimeReward(int nCID, int nBRID, int nBRTID, int nBattleTime, int nKillCount, int nItemID, int nItemCnt, int nRentHourPeriod, bool bIsSpendable, int* noutCIID);

Add under <br>

	bool UpdatePlayerWars();
	bool UpdateClanRanking();
	bool UpdateSurvivalRanking();
	bool UpdateGunzSystem();

Open(MMatchServer.cpp) <br>
Find <br>

    MGetServerStatusSingleton()->SetRunStatus(106);

Add under <br>

	static unsigned int SystemUpdate = nGlobalClock;
	if (nGlobalClock - SystemUpdate > _SYSTEMUPDATETIME)
	{
		GetDBMgr()->UpdatePlayerWars();
		GetDBMgr()->UpdateClanRanking();
		GetDBMgr()->UpdateGunzSystem();
	}























    
