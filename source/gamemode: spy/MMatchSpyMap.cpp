#include "stdafx.h"
#include "MMatchSpyMap.h"
#include "MMatchMap.h"

const MMatchSpyMapNode* MMatchSpyMap::GetMap(int nMapID)
{
	for(int i = MMATCH_SPY_MAP_MANSION; i < MMATCH_SPY_MAP_MAX; i++)
		if(g_SpyMapNode[i].nID == nMapID) return &g_SpyMapNode[i];

	return &g_SpyMapNode[MMATCH_SPY_MAP_MANSION];
}

const MMatchSpyMapNode* MMatchSpyMap::GetMap(const char* pszMapName)
{
	int nMapID = MMATCH_MAP_MANSION;

	for(int i = MMATCH_MAP_MANSION; i < MMATCH_MAP_MAX; i++)
	{
		if(MGetMapDescMgr()->MIsCorrectMap(i))
		{
			if(!stricmp(MGetMapDescMgr()->GetMapName(i), pszMapName))
			{
				nMapID = i;
				break;
			}
		}
	}

	return GetMap(nMapID);
}

bool MMatchSpyMap::IsExistingMap(int nMapID)
{
	for(int i = MMATCH_SPY_MAP_MANSION; i < MMATCH_SPY_MAP_MAX; i++)
		if(g_SpyMapNode[i].nID == nMapID) return true;

	return false;
}