#pragma once
#include "MMatchRule.h"
#include "GunGame.h"

class MMatchRuleGunGame : public MMatchRule {
protected:
	int			   m_nSet;
	vector<GGSet>  m_MatchSet;
			void SendNewSet(const MUID& uidPlayer, int KillCount,bool isSuicide);
	virtual void OnBegin();
	virtual void OnEnd();
	virtual void OnRoundTimeOut();
	virtual void OnGameKill(const MUID& uidAttacker, const MUID& uidVictim);
	virtual void OnEnterBattle(MUID& uidPlayer);
	virtual bool CheckKillCount(MMatchObject* pOutObj);
	virtual bool OnRun();
	virtual bool OnCheckRoundFinish();
	virtual bool RoundCount();
	virtual void OnRoundBegin();
	virtual void OnRoundEnd();

public:
	MMatchRuleGunGame(MMatchStage* pStage);
	virtual ~MMatchRuleGunGame();
	virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_GUNGAME; }
};