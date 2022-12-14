#pragma once

////////// HARD-CODED //////////
struct MMatchSpyMapNode
{
	int nID;
	char szName[MAPNAME_LENGTH];
	int nMinPlayers;
	int nMaxPlayers;
	int nLimitTime;
	int nSpyOpenTime;
};

enum MMATCH_SPY_MAP
{
	MMATCH_SPY_MAP_MANSION			= 0, 
	MMATCH_SPY_MAP_PRISON, 
	MMATCH_SPY_MAP_STATION, 
	MMATCH_SPY_MAP_BATTLE_ARENA, 
	MMATCH_SPY_MAP_TOWN, 
	MMATCH_SPY_MAP_DUNGEON, 
	MMATCH_SPY_MAP_RUIN, 
	MMATCH_SPY_MAP_ISLAND, 
	MMATCH_SPY_MAP_GARDEN, 
	MMATCH_SPY_MAP_CASTLE, 
	MMATCH_SPY_MAP_FACTORY, 
	MMATCH_SPY_MAP_PORT, 
	MMATCH_SPY_MAP_LOST_SHRINE, 
	MMATCH_SPY_MAP_STAIRWAY, 
	MMATCH_SPY_MAP_HIGH_HAVEN, 
	MMATCH_SPY_MAP_CITADEL, 
	MMATCH_SPY_MAP_WEAPONSHOP, 
	MMATCH_SPY_MAP_PAVILION,

	MMATCH_SPY_MAP_MAX
};

static const MMatchSpyMapNode g_SpyMapNode[MMATCH_SPY_MAP_MAX] = 
{
	{0,		"Mansion",			8,		9,		135,		27},
	{1,		"Prison",			10,		11,		135,		27},
	{2,		"Station",			6,		7,		105,		21},
	{4,		"Battle Arena",		11,		12,		135,		27},
	{5,		"Town",				7,		8,		120,		24},
	{6,		"Dungeon",			9,		10,		135,		27},
	{7,		"Ruin",				11,		12,		150,		30},
	{8,		"Island",			6,		7,		120,		24},
	{9,		"Garden",			8,		9,		105,		21},
	{10,	"Castle",			10,		11,		135,		27},
	{11,	"Factory",			4,		5,		50,			10},
	{12,	"Port",				8,		9,		135,		27},
	{13,	"Lost Shrine",		5,		6,		75,			15},
	{14,	"Stairway",			11,		12,		135,		27},
	{20,	"High_Heaven",		5,		6,		90,			18},
	{21,	"Citadel",			7,		8,		120,		24},
	{24,	"Weaponshop",		4,		5,		50,			10},
    {25,	"Pavilion",		    4,		5,		50,			24}
};


namespace MMatchSpyMap
{
	const MMatchSpyMapNode* GetMap(int nMapID);
	const MMatchSpyMapNode* GetMap(const char* pszMapName);

	bool IsExistingMap(int nMapID);
};
