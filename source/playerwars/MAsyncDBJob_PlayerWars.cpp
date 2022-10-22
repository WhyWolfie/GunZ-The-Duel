#include "stdafx.h"
#include "MAsyncDBJob_PlayerWars.h"

void MAsyncDBJob_GetPlayerWarsCharInfo::Run(void* pContext)
{
	MMatchDBMgr* pDBMgr = (MMatchDBMgr*)pContext;
	if (!pDBMgr->GetPlayerWarsCharInfo(m_dwPlayerCID, &m_pPWCharInfo) ) {
			SetResult(MASYNC_RESULT_FAILED);
			return;
		}
	SetResult(MASYNC_RESULT_SUCCEED);
}

void MAsyncDBJob_UpdatePlayerWarsCharInfo::Run(void* pContext)
{
	MMatchDBMgr* pDBMgr = (MMatchDBMgr*)pContext;
	if (!pDBMgr->UpdatePlayerWarsCharInfo(m_dwPlayerCID, Win, Loss, Draw, Score, Mode) ) {
			SetResult(MASYNC_RESULT_FAILED);
			return;
		}
	SetResult(MASYNC_RESULT_SUCCEED);
}

void MAsyncDBJob_GetPlayerWarsSideRankingInfo::Run(void* pContext)
{
	MMatchDBMgr* pDBMgr = (MMatchDBMgr*)pContext;
	if (!pDBMgr->GetPlayerWarsSideRankingInfo(m_dwPlayerCID, &m_SideRankingList) ) {
			SetResult(MASYNC_RESULT_FAILED);
			return;
		}
	SetResult(MASYNC_RESULT_SUCCEED);
}
