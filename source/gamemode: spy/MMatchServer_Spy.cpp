#include "stdafx.h"
#include "MMatchServer.h"
#include "MBlobArray.h"
#include "MMatchStage.h"
#include "MMatchSpyMap.h"

MCommand* MMatchServer::BuildSpyBanMapListCommand(MMatchStageSetting* pSetting)
{
	// Sync Spy Mode ban map list.

	// Find for ban map list and store it to std::vector once.
	vector<int> vecMapIDs;	// Ban Map ID List.

	for(int i = MMATCH_SPY_MAP_MANSION; i < MMATCH_SPY_MAP_MAX; i++)
		if(pSetting->IsExcludedSpyMap(g_SpyMapNode[i].nID))
			vecMapIDs.push_back(g_SpyMapNode[i].nID);

	// Make Blob command.
	void* pMapListBlob = MMakeBlobArray(sizeof(int), (int)vecMapIDs.size());

	for(int i = 0; i < (int)vecMapIDs.size(); i++)
	{
		int* id = (int*)MGetBlobArrayElement(pMapListBlob, i);
		(*id) = vecMapIDs[i];
	}

	// Make Command.
	MCommand* pCmd = CreateCommand(MC_SPY_STAGE_BAN_MAP_LIST, MUID(0,0));
	pCmd->AddParameter(new MCmdParamBlob(pMapListBlob, MGetBlobArraySize(pMapListBlob)));

	// post-process.
	MEraseBlobArray(pMapListBlob);

	return pCmd;
}

void MMatchServer::OnSpyStageRequestBanMapList(const MUID& uidPlayer)
{
	MMatchObject* pObj = GetObject(uidPlayer);
	if(!IsEnabledObject(pObj)) return;

	MMatchStage* pStage = FindStage(pObj->GetStageUID());
	if(!pStage) return;

	MMatchStageSetting* pSetting = pStage->GetStageSetting();

	MCommand* pCmd = BuildSpyBanMapListCommand(pSetting);
	RouteToStage(pStage->GetUID(), pCmd);
}

void MMatchServer::OnSpyStageActivateMap(const MUID& uidPlayer, int nMapID, bool bExclude)
{
	MMatchObject* pObj = GetObject(uidPlayer);
	if(!IsEnabledObject(pObj)) return;

	MMatchStage* pStage = FindStage(pObj->GetStageUID());
	if(!pStage) return;
	if(pStage->GetState() != STAGE_STATE_STANDBY) return;

	if(pStage->GetMasterUID() != uidPlayer) return;

	MMatchStageSetting* pSetting = pStage->GetStageSetting();
	if (pSetting->GetGameType() != MMATCH_GAMETYPE_SPY) return;

	if(bExclude)	
		pSetting->ExcludeSpyMap(nMapID);
	else			
		pSetting->IncludeSpyMap(nMapID);

	MCommand* pCmd = CreateCommand(MC_SPY_STAGE_ACTIVATE_MAP, MUID(0,0));
	pCmd->AddParameter(new MCmdParamInt(nMapID));
	pCmd->AddParameter(new MCmdParamBool(bExclude));
	RouteToStage(pStage->GetUID(), pCmd);
}

void MMatchServer::OnSpyStageStart(const MUID& uidPlayer, void* pMapListBlob)
{
	MMatchObject* pObj = GetObject(uidPlayer);
	if(!IsEnabledObject(pObj)) return;

	MMatchStage* pStage = FindStage(pObj->GetStageUID());
	if(!pStage) return;
	if(pStage->GetState() != STAGE_STATE_STANDBY) return;

	if(pStage->GetMasterUID() != uidPlayer) return;

	MMatchStageSetting* pSetting = pStage->GetStageSetting();
	if (pSetting->GetGameType() != MMATCH_GAMETYPE_SPY) return;

	int nMapCount = MGetBlobArrayCount(pMapListBlob);
	if(nMapCount <= 0 || nMapCount > 20) return;	// Limited max map count to 20.

	int nRand = rand() % nMapCount;
	int nMapID = *(int*)MGetBlobArrayElement(pMapListBlob, nRand);

	if(!MMatchSpyMap::IsExistingMap(nMapID)) return;

	const MMatchSpyMapNode* pSpyMap = MMatchSpyMap::GetMap(nMapID);
	_ASSERT(pSpyMap != NULL);

	pSetting->SetMapIndex(nMapID);
	pSetting->SetLimitTime(pSpyMap->nLimitTime * 1000); //Update Time

	MCommand* pCmd = CreateCmdResponseStageSetting(pStage->GetUID());
	RouteToStage(pStage->GetUID(), pCmd);

	OnStageStart(uidPlayer, pStage->GetUID(), 3);
}
