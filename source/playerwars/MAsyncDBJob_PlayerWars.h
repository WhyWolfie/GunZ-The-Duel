#pragma once

#ifndef _MASYNCDBJOB_PLAYERWARS
#define _MASYNCDBJOB_PLAYERWARS

#include "MAsyncDBJob.h"

class MAsyncDBJob_GetPlayerWarsCharInfo : public MAsyncJob
{
protected:
	DWORD m_dwPlayerCID;

	MUID m_uidPlayer;
	PlayerWarsCharInfo m_pPWCharInfo;
public:
	MAsyncDBJob_GetPlayerWarsCharInfo(void) : MAsyncJob(MASYNCJOB_GET_PW_INFO, MUID(0, 0)) {
		m_dwPlayerCID = 0;
		m_uidPlayer = MUID(0, 0);
	}
	~MAsyncDBJob_GetPlayerWarsCharInfo(void){}

	void Input(MUID uidPlayer, DWORD dwPlayerCID) {
		m_uidPlayer = uidPlayer;
		m_dwPlayerCID = dwPlayerCID;		
	}

	virtual void Run(void* pContext);

	MUID GetPlayerUID()									{ return m_uidPlayer; }
	PlayerWarsCharInfo* GetPWCharInfo()	{ return &m_pPWCharInfo; }	
};

class MAsyncDBJob_UpdatePlayerWarsCharInfo : public MAsyncJob
{
protected:
	DWORD m_dwPlayerCID;
	int Win, Loss, Draw, Score, Mode;
public:
	MAsyncDBJob_UpdatePlayerWarsCharInfo(void) : MAsyncJob(MASYNCJOB_UPDATE_PW_INFO, MUID(0, 0)) {
		m_dwPlayerCID = 0;
	}
	~MAsyncDBJob_UpdatePlayerWarsCharInfo(void){}

	void Input(DWORD dwPlayerCID, int win, int loss, int draw, int score, int mode) {
		m_dwPlayerCID = dwPlayerCID;
		Win = win;
		Loss = loss;
		Draw = draw;
		Score = score;
		Mode = mode;
	}

	virtual void Run(void* pContext);
};

class MAsyncDBJob_GetPlayerWarsSideRankingInfo : public MAsyncJob
{
protected:
	DWORD m_dwPlayerCID;

	MUID m_uidPlayer;
	list<PWRankingInfo*> m_SideRankingList;
public:
	MAsyncDBJob_GetPlayerWarsSideRankingInfo(void) : MAsyncJob(MASYNCJOB_GET_PW_SIDE_RANKING, MUID(0, 0)) {
		m_dwPlayerCID = 0;
		m_uidPlayer = MUID(0, 0);
	}

	~MAsyncDBJob_GetPlayerWarsSideRankingInfo(void)
	{
		RemoveListAll();
	}


	void Input(MUID uidPlayer, DWORD dwPlayerCID) {
		m_uidPlayer = uidPlayer;
		m_dwPlayerCID = dwPlayerCID;		
	}

	virtual void Run(void* pContext);

	MUID GetPlayerUID()							{ return m_uidPlayer; }
	list<PWRankingInfo*>* GetSideRankingList()	{ return &m_SideRankingList; }	

	void RemoveListAll()
	{
		list<PWRankingInfo*>::iterator iter = m_SideRankingList.begin();
		for(; iter != m_SideRankingList.end(); ){
			PWRankingInfo *pInfo = (*iter);
			delete pInfo;

			iter = m_SideRankingList.erase(iter);			
		}
	}
};

#endif