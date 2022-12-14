#include "stdafx.h"
#include "MMatchSpyMode.h"

const int MMatchSpyMode::GetMinPlayers()
{
#ifdef _DEBUG
	return 2;
#else
	return 4;
#endif
}

const MMatchSpyTableData* MMatchSpyMode::GetSpyTable(int nPlayers)
{
	switch(nPlayers)
	{
	    case 2:  return &g_SpyTableData[MMATCH_SPYTABLE_2P];
		case 4:  return &g_SpyTableData[MMATCH_SPYTABLE_4P];
		case 5:  return &g_SpyTableData[MMATCH_SPYTABLE_5P];
		case 6:  return &g_SpyTableData[MMATCH_SPYTABLE_6P];
		case 7:  return &g_SpyTableData[MMATCH_SPYTABLE_7P];
		case 8:  return &g_SpyTableData[MMATCH_SPYTABLE_8P];
		case 9:  return &g_SpyTableData[MMATCH_SPYTABLE_9P];
		case 10: return &g_SpyTableData[MMATCH_SPYTABLE_10P];
		case 11: return &g_SpyTableData[MMATCH_SPYTABLE_11P];
		case 12: return &g_SpyTableData[MMATCH_SPYTABLE_12P];
	}

	return &g_SpyTableData[MMATCH_SPYTABLE_4P];
}

const MMatchSpyTrackerTableData* MMatchSpyMode::GetTrackerTable()
{
	return &g_SpyTrackerTableData;
}

const bool MMatchSpyMode::IsSpyItem(int nItemID)
{
	if(nItemID >= 601001 && nItemID <= 601006)
		return true;
	return false;
}