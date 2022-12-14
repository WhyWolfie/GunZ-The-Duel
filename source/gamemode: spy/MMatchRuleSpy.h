#pragma once

#include "MMatchRule.h"
#include "MMatchSpyMode.h"
#include "MMatchSpyMap.h"

class MMatchRuleSpy : public MMatchRule
{
protected:
	bool GetAliveCount(int* pRedAliveCount, int* pBlueAliveCount);
	virtual void OnBegin();
	virtual void OnEnd();
	virtual bool OnRun();
	virtual void OnRoundBegin();
	virtual void OnRoundEnd();
	virtual bool OnCheckRoundFinish();
	virtual void OnRoundTimeOut();
	virtual void OnRoundCountdown();
	virtual bool RoundCount();
	virtual bool OnCheckEnableBattleCondition();
public:
	MMatchRuleSpy(MMatchStage* pStage);
	virtual ~MMatchRuleSpy();
	virtual void DistributeTeamBonus(MMatchTeam nTeam);
	virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_SPY; }
	virtual void OnEnterBattle(MUID& uidChar);
	virtual void OnLeaveBattle(MUID& uidChar);

public:
	bool IsSpy(const MUID& uidPlayer);
	bool IsParticipant(const MUID& uidPlayer);
	bool SelectRandomSpy();
	void RefreshTeamIDs();
	void SendGameInfo();
protected:
	vector<MUID> m_vtSpy, m_vtParticipant;
	int m_nStartPlayers;
};