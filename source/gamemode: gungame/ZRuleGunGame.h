#pragma once
#include "ZRule.h"

class ZRuleGunGame : public ZRule
{
public:
	ZRuleGunGame(ZMatch* pMatch);
	virtual ~ZRuleGunGame();
	virtual bool OnCommand(MCommand* pCommand);


	int m_nSetID;
	void SetPlayerWeapons(MUID& uidPlayer, const int WeaponSetArray[], bool isSuicide);

	vector<GGWeaponSet> matchSet;
	vector<GGWeaponSet> GetMatchSet() { return matchSet; }
};