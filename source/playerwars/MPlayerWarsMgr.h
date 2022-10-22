#pragma once
#include <map>
using namespace std;
#include "MMatchGlobal.h"
#include "MUID.h"
typedef map<MUID, MUID> PlayerJoiningDataStruct;

struct MapSelectionStruct
{
	PlayerJoiningDataStruct Players;
	PlayerWars Type;
	int Maps[3];
	int Votes[3];
	int SelectedMap;
	unsigned long int RegisterTime;
};

class PlayerWarsData
{
private:
	vector<MUID> AntiLead; 
	PlayerWarsData* m_pInstance;
public:
	PlayerWarsData()
	{
		_ASSERT(m_pInstance==NULL);
		m_pInstance = this;
	}
	PlayerWarsData* GetInstance() { return m_pInstance; }

	bool IsPlayerAlreadyQueued(MUID ID)
	{
		vector<MUID>::iterator i;
		i = find(AntiLead.begin(), AntiLead.end(), ID);
		if(i != AntiLead.end()) return true;
		return false;
	}

	void AddPlayer(MUID ID)
	{  
			AntiLead.push_back(ID); 
	}

	bool RemovePlayer(MUID ID) 
	{ 
		vector<MUID>::iterator i = find(AntiLead.begin(), AntiLead.end(), ID);
		if(i != AntiLead.end()) 
		{
			AntiLead.erase(i);
			return true;
		}
		return false;
	}
	MUID GetFirst() { return (MUID)(*AntiLead.begin()); }
	int GetCount() { return AntiLead.size(); }
};

class MPlayerWarsMgr
{
private:
	unsigned long int nLastTime, nLastTime1;
	PlayerWarsData WatingGames[MPLAYERWARSTYPE_MAX];
	MPlayerWarsMgr* m_pInstance;
	map<unsigned long int, MapSelectionStruct*> WaitingMapSelectionGames;
	unsigned long int counter;
public: 
	void Tick();
	PlayerWarsData* GetWaitingGames(PlayerWars Type) { return WatingGames[(int)Type].GetInstance(); }
	void MapSelection(PlayerJoiningDataStruct ReadyGame, PlayerWars Type, unsigned long int NowTime);
	void MatchMaking(unsigned long int NowTime);
	void UpdateQueueingCounters(unsigned long int NowTime);
	void UpdateMapCountDown(unsigned long int NowTime);
	void RemovePlayer(MUID PlayerID);
	bool IsWaitingGame(MUID PlayerID)
	{
		for(map<unsigned long int, MapSelectionStruct*>::iterator i = WaitingMapSelectionGames.begin(); i != WaitingMapSelectionGames.end();)
		{
			MapSelectionStruct* m = i->second;
			if(m)
			for (PlayerJoiningDataStruct::iterator i=m->Players.begin(); i!=m->Players.end(); i++) 
				if(PlayerID == i->first) return true;
		}
		return false;
	}

	void UpdatePlayerVote(int VoteID, MMatchObject* pObj)
	{
		if(pObj->PlayerWarsIdentifier != -1)
		{
			map<unsigned long int, MapSelectionStruct*>::iterator i = WaitingMapSelectionGames.find(pObj->PlayerWarsIdentifier);
			if(i!=WaitingMapSelectionGames.end())
			{
				MapSelectionStruct*  m = i->second;
				if(m)
				{
					if(pObj->LastVoteID != -1)
						m->Votes[pObj->LastVoteID]--;
					m->Votes[VoteID]++;
					pObj->LastVoteID = VoteID;
				}
			}
		}
	}
	MPlayerWarsMgr()
	{
		_ASSERT(m_pInstance==NULL);
		m_pInstance = this;
		counter = 0;
	}
	MPlayerWarsMgr* GetInstance() { return m_pInstance; }
};