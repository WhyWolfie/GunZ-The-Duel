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


#define _ODBC_DATABASE_USERNAME	"sa"		// database username.
#define _ODBC_DATABASE_PASSWORD	"12345"	// database password.
#define _ODBC_DATABASE_NAME		"gunzdb"	// database name.

otl_connect db;


bool IsExit = false;

BOOL WINAPI HandlerRoutine(DWORD dwCtrlType)	{
	if(dwCtrlType == CTRL_C_EVENT || 
		dwCtrlType == CTRL_BREAK_EVENT || 
		dwCtrlType == CTRL_CLOSE_EVENT || 
		dwCtrlType == CTRL_LOGOFF_EVENT || 
		dwCtrlType == CTRL_SHUTDOWN_EVENT)	{

			IsExit = true;
			return TRUE;
	}

	return FALSE;
}

void SQLErr(otl_exception *e)	{
	cout << e->msg << '\n' << e->stm_text << '\n' << e->var_info << '\n';
	cout << "An error occurred while processing SQL.\n";

	ofstream ErrLog("SQL Error.txt", ios::out | ios::app);
	ErrLog << e->msg << '\n' << e->stm_text << '\n' << e->var_info << '\n';
	ErrLog << "----------------------------------------------------------------------\n";
	ErrLog.close();
}

int main()	{
	cout << "Release Date : " << __DATE__ << ' ' << __TIME__ << ".\n";

	// Handler register start.
	if(SetConsoleCtrlHandler(&HandlerRoutine, TRUE) == 0)	{
		cout << "Failed to add the handler.\n";
		return -1;
	}
	// Handler register end.

	// OTL init start.
	otl_connect::otl_initialize();

	char strConnectToDB[256];
	sprintf_s(strConnectToDB, "%s/%s@%s", _ODBC_DATABASE_USERNAME, _ODBC_DATABASE_PASSWORD, _ODBC_DATABASE_NAME);

	try	{	// try to connect to the db via ODBC.
		db.rlogon(strConnectToDB);
		db.auto_commit_on();
	}
	catch(otl_exception &e)	{	// OTL init failed.
		SQLErr(&e);
		cout << "Failed to connect to the database.\n";
		return -1;
	}
	// OTL init end.

	cout << "Ranking updater start.\n";


	DWORD dwClanDelTime = timeGetTime();	// clan removed at 3 hours interval.

	DWORD dwCharacterTime = timeGetTime();	// character ranking updated at 1 day interval.
	DWORD dwClanTime = timeGetTime();	// clan ranking updated at 1 day interval.
	DWORD dwSurvivalTime = timeGetTime();	// survival ranking updated at 1 day interval.
	DWORD dwDuelTournamentTime = timeGetTime();	// duel tournament ranking updated at 1 day interval.

	while(IsExit == false)	{	// exit signal.
		// Delete clan start.
		if(dwClanDelTime <= timeGetTime())	{
			dwClanDelTime = timeGetTime() + (MILLISECOND_HOUR * 3);	// + 3 hours.

			long nResult1 = 0, nResult2 = 0;	// 1 = deleted member count, 2 = deleted clan count.
			try	{
				nResult1 = db.direct_exec("DELETE FROM ClanMember WHERE CLID=(SELECT CLID FROM Clan WHERE DeleteFlag=2);", otl_exception::enabled);	// clean clan member.
				nResult2 = db.direct_exec("UPDATE Clan SET Name=NULL, DeleteFlag=1, DeleteName=Name WHERE DeleteFlag=2;", otl_exception::enabled);	// clean clan.
			}
			catch(otl_exception &e)	{	// fail.
				SQLErr(&e);
				cout << "Clan cleaning failed.\n";
				continue;
			}

			// success.
			cout << "Clan is successfully cleaned. (Removed members :" << nResult1 << " - clans :" << nResult2 << ".)\n";
		}
		// Delete clan end.


		// Character ranking start.
		if(dwCharacterTime <= timeGetTime())	{
			dwCharacterTime = timeGetTime() + MILLISECOND_DAY;	// + 1 day.

			try	{
				db.direct_exec("EXECUTE spFetchTotalRanking;", otl_exception::enabled);	// call character ranking update stored function.
			}
			catch(otl_exception &e)	{	// fail.
				SQLErr(&e);
				cout << "Error at updating character ranking.\n";
				continue;
			}

			// success.
			cout << "Character ranking updated.\n";
		}
		// Character ranking end.


		// Clan ranking start.
		if(dwClanTime <= timeGetTime())	{
			dwClanTime = dwClanTime + MILLISECOND_DAY;	// + 1 day.

			try	{
				db.direct_exec("EXECUTE spRegularUpdateClanRanking;", otl_exception::enabled);	// call clan ranking update stored function.
			}
			catch(otl_exception &e)	{	// fail.
				SQLErr(&e);
				cout << "Error clan ranking update.\n";
				continue;
			}

			// success.
			cout << "Clan ranking update done.\n";
		}
		// Clan ranking end.


		// Survival ranking start.
		if(dwSurvivalTime <= timeGetTime())	{
			dwSurvivalTime = timeGetTime() + MILLISECOND_DAY;	// + 1 day.

			try	{
				db.direct_exec("EXECUTE spFetchSurvivalRanking;", otl_exception::enabled);	// call survival ranking update stored function.
			}
			catch(otl_exception &e)	{	// fail.
				SQLErr(&e);
				cout << "Error at survival ranking update.\n";
				continue;
			}

			// success.
			cout << "Survival ranking updated.\n";
		}
		// Survival ranking end.


		// Duel tournament ranking start.
		if(dwDuelTournamentTime <= timeGetTime())	{
			dwDuelTournamentTime = timeGetTime() + MILLISECOND_DAY;	// + 1 day.

			try	{
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
			catch(otl_exception &e)	{	// fail.
				SQLErr(&e);
				cout << "Process duel tournament ranking fail.\n";
				continue;
			}

			// success.
			cout << "Updated duel tournament ranking and timestamp.\n";
		}
		// Duel tournament ranking end.


		Sleep(MILLISECOND_SECOND);	// 1 sec Sleep.
	}

	db.logoff();

	return 0;
}
