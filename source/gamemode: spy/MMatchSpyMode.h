#pragma once

////////// HARD-CODED //////////
#define MSPYMODE_ROUNDSTATE_COUNTDOWN_TIME	(1000 * 10)

enum MMATCH_SPYTABLE
{
	MMATCH_SPYTABLE_2P		= 0, 
	MMATCH_SPYTABLE_4P,
	MMATCH_SPYTABLE_5P, 
	MMATCH_SPYTABLE_6P, 
	MMATCH_SPYTABLE_7P, 
	MMATCH_SPYTABLE_8P, 
	MMATCH_SPYTABLE_9P, 
	MMATCH_SPYTABLE_10P, 
	MMATCH_SPYTABLE_11P, 
	MMATCH_SPYTABLE_12P, 

	MMATCH_SPYTABLE_MAX
};

#define MSPYMODE_WORLDITEM_LANDMINE_ID		200

struct MMatchSpyItem
{
	unsigned long	nItemID;
	unsigned int	nItemCount;
};

struct MMatchSpyTableData
{
	int nSpyCount;
	int nHPAP;

	enum ITEM
	{
		BAG		= 0,
		LIGHT,	
		ICE,		
		SMOKE,	
		MAX		
	};
	MMatchSpyItem SpyItem[ITEM::MAX];
};

static const MMatchSpyTableData g_SpyTableData[MMATCH_SPYTABLE_MAX] = 
{
	{	// 2P
		1,
		50,
		{ { 601006, 1 },{ 601001, 2 },{ 601003, 4 },{ 601002, 8 } }
	},
	{	// 4P
		1, 
		50, 
		{{601006, 1}, {601001, 2}, {601003, 4}, {601002, 8}}
	},
	{	// 5P
		1, 
		100, 
		{{601006, 1}, {601001, 3}, {601003, 5}, {601002, 10}}
	},
	{	// 6P
		1, 
		150, 
		{{601006, 1}, {601001, 4}, {601003, 6}, {601002, 12}}
	},
	{	// 7P
		2, 
		50, 
		{{601006, 1}, {601001, 2}, {601003, 4}, {601002, 5}}
	},
	{	// 8P
		2, 
		80, 
		{{601006, 1}, {601001, 3}, {601003, 5}, {601002, 6}}
	},
	{	// 9P
		2, 
		110, 
		{{601006, 1}, {601001, 4}, {601003, 6}, {601002, 7}}
	},
	{	// 10P
		3, 
		50, 
		{{601006, 1}, {601001, 2}, {601003, 3}, {601002, 4}}
	},
	{	// 11P
		3, 
		70, 
		{{601006, 1}, {601001, 3}, {601003, 4}, {601002, 5}}
	},
	{	// 12P
		3, 
		90, 
		{{601006, 1}, {601001, 4}, {601003, 5}, {601002, 6}}
	}
};

struct MMatchSpyTrackerTableData
{
	enum ITEM
	{
		STUN	= 0, 
		MINE, 
		MAX
	};
	MMatchSpyItem TrackerItem[ITEM::MAX];
};

static MMatchSpyTrackerTableData g_SpyTrackerTableData = 
{
	{{601004, 2}, {601005, 10}}
};


namespace MMatchSpyMode
{
	const int GetMinPlayers();

	const MMatchSpyTableData* GetSpyTable(int nPlayers);
	const MMatchSpyTrackerTableData* GetTrackerTable();

	const bool IsSpyItem(int nItemID);
};
