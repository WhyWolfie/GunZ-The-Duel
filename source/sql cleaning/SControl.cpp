#include "StdAfx.h"
#include "SControl.h"
#include <iostream>
#include <fstream>
using namespace std;

#include <stdio.h>

#define OTL_ODBC_MSSQL_2005
#define OTL_ENABLE_MSSQL_MARS
#define OTL_DEFAULT_NUMERIC_NULL_TO_VAL	0
#include "otlv4.h"

#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#define DUELTOURNAMENT_RANKING_WEEKLY_UPDATE	// Remove this definition if you want to do daily update.

#define MILLISECOND_SECOND	(1000)						// 1 sec.
#define MILLISECOND_MINUTE	(MILLISECOND_SECOND * 60)	// 1 min.
#define MILLISECOND_HOUR	(MILLISECOND_MINUTE * 60)	// 1 hour.
#define MILLISECOND_DAY		(MILLISECOND_HOUR * 24)		// 1 day.
#define MILLISECOND_WEEK	(MILLISECOND_DAY * 7)		// 1 week.
#define TIME_COLOR	RGB(128, 128, 128)

char m_szDB_DNS[64];					///< DB DNS
char m_szDB_UserName[64];				///< DB Username
char m_szDB_Password[64];				///< DB Password

otl_connect db;


void SQLErr(otl_exception *e)	{
	cout << e->msg << '\n' << e->stm_text << '\n' << e->var_info << '\n';
	cout << "An error occurred while processing SQL.\n";

	ofstream ErrLog("SQL Error.txt", ios::out | ios::app);
	ErrLog << e->msg << '\n' << e->stm_text << '\n' << e->var_info << '\n';
	ErrLog << "----------------------------------------------------------------------\n";
	ErrLog.close();
}


void SControl::Main()
{
	mlog("================================== Server Clean info ======================================\n");
	mlog("CLEAN : Release Date : %s %s\n",__DATE__,__TIME__ );
	mlog("CLEAN : Credits : DelPa, SeaTroll\n");

	#define SERVER_CONFIG_FILENAME			"./server.ini"
	GetPrivateProfileString("DB", "DNS", "dns", m_szDB_DNS, 64, SERVER_CONFIG_FILENAME);
	GetPrivateProfileString("DB", "USERNAME", "username", m_szDB_UserName, 64, SERVER_CONFIG_FILENAME);
	GetPrivateProfileString("DB", "PASSWORD", "password", m_szDB_Password, 64, SERVER_CONFIG_FILENAME);

	// lOGIN DATABASE
	char strConnectToDB[256];
	sprintf(strConnectToDB, "%s/%s@%s", m_szDB_UserName, m_szDB_Password, m_szDB_DNS);
	try	
	{	
		// try to connect to the db via ODBC.
		db.rlogon(strConnectToDB);
		db.auto_commit_on();
	}
	catch(otl_exception &e)	
	{	
		// OTL init failed.
		SQLErr(&e);
		mlog("CLEAN : Failed to connect to the database.\n");
	}
	// LOGIN DATABASE END

	// TIME SAVE DWORD
	DWORD dwCleanSystemTime= timeGetTime();	
	DWORD dwClanDelTime = timeGetTime();		
	DWORD dwCharacterTime = timeGetTime();		
	DWORD dwClanTime = timeGetTime();			
	DWORD dwSurvivalTime = timeGetTime();		
	DWORD dwDuelTournamentTime = timeGetTime();	

	// Delete clan start.
	if(dwCleanSystemTime <= timeGetTime())
	{
		dwCleanSystemTime = timeGetTime() + (MILLISECOND_HOUR * 1);

		if(dwClanDelTime <= timeGetTime())	
		{
			dwClanDelTime = timeGetTime() + (MILLISECOND_HOUR * 1);
			try	
			{
				db.direct_exec("DELETE FROM ClanMember WHERE CLID=(SELECT CLID FROM Clan WHERE DeleteFlag=2);", otl_exception::enabled);	// clean clan member.
				db.direct_exec("UPDATE Clan SET Name=NULL, DeleteFlag=1, DeleteName=Name WHERE DeleteFlag=2;", otl_exception::enabled);	// clean clan.
			}
			catch(otl_exception &e)	
			{	
				// fail.
				SQLErr(&e);
				mlog("CLEAN : Clan cleaning - FAILED.\n");
			}
			// success.
			mlog("CLEAN : Clan cleaning - SUCCESS.\n");
		}
		// Delete clan end.

		// Character ranking start.
		if(dwCharacterTime <= timeGetTime())	
		{
			dwCharacterTime = timeGetTime() + (MILLISECOND_HOUR * 1);
			try	
			{
				db.direct_exec("EXECUTE spFetchTotalRanking;", otl_exception::enabled);	// call character ranking update stored function.
			}
			catch(otl_exception &e)	
			{	
				// fail.
				mlog("CLEAN : Character ranking updated - FAILED.\n");
			}
			// success.
			mlog("CLEAN : Character ranking updated - SUCCESS.\n");
		}
		// Character ranking end.

		// Clan ranking start.
		if(dwClanTime <= timeGetTime())	
		{
			dwClanTime = dwClanTime + (MILLISECOND_HOUR * 1);
			try	
			{
				db.direct_exec("EXECUTE spRegularUpdateClanRanking;", otl_exception::enabled);	// call clan ranking update stored function.
			}
			catch(otl_exception &e)	
			{	
				// fail.
				SQLErr(&e);
				mlog("CLEAN : Clan ranking updated - FAILED.\n");
			}
			// success.
			mlog("CLEAN : Clan ranking updated - SUCCESS.\n");
		}
		// Clan ranking end.

		// Survival ranking start.
		if(dwSurvivalTime <= timeGetTime())	
		{
			dwSurvivalTime = timeGetTime() + (MILLISECOND_HOUR * 1);
			try	
			{
				db.direct_exec("EXECUTE spFetchSurvivalRanking;", otl_exception::enabled);	// call survival ranking update stored function.
			}
			catch(otl_exception &e)	
			{	
				// fail.
				SQLErr(&e);
				mlog("CLEAN : Survival ranking updated - FAILED.\n");
			}
			// success.
			mlog("CLEAN : Survival ranking updated - SUCCESS.\n");
		}
		// Survival ranking end.


		// Duel tournament ranking start.
		if(dwDuelTournamentTime <= timeGetTime())	
		{
			dwDuelTournamentTime = timeGetTime() + (MILLISECOND_HOUR * 1);
				try	
				{
				#ifdef DUELTOURNAMENT_RANKING_WEEKLY_UPDATE
				// weekly update.
				db.direct_exec(
					"IF NOT EXISTS(SELECT * FROM DTTimeStamp WHERE TimeStamp=(CONVERT( CHAR(8), DATEADD(dd, DATEPART(WEEKDAY, CONVERT(DATETIME, GETDATE()))*(-1)+2, CONVERT(DATETIME, GETDATE())), 112))) BEGIN\n"
					"    EXECUTE spDTInsertDTTimeStamp 1;\n"
					"END\n"
					"EXECUTE spDTFetchDTRanking;", 
					otl_exception::enabled);
				#else
				// daily update.
				db.direct_exec(
					"IF NOT EXISTS(SELECT * FROM DTTimeStamp WHERE TimeStamp=(CONVERT( CHAR(8), GETDATE(), 112))) BEGIN\n"
					"    EXECUTE spDTInsertDTTimeStamp 0;\n"
					"END\n"
					"EXECUTE spDTFetchDTRanking;", 
					otl_exception::enabled);
			#endif
			}
			catch(otl_exception &e)	
			{	
				// fail.
				SQLErr(&e);
				mlog("CLEAN : Process duel tournament ranking - FAILED.\n");
			}
			// success.
			mlog("CLEAN : Updated duel tournament ranking and timestamp - SUCCESS.\n");
		}
		// Duel tournament ranking end.

		db.logoff();
		mlog("\n===========================================================================================\n");
	}
}
