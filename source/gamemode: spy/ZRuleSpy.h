#pragma once

#include "ZRule.h"
#include "../SpyModeSystem/MMatchSpyMode.h"

class ZRuleSpy : public ZRule
{
public:
	ZRuleSpy(ZMatch* pMatch);
	virtual ~ZRuleSpy();

	virtual bool OnCommand(MCommand* pCommand);
	virtual void AfterCommandProcessed(MCommand* pCommand);
	virtual void OnSetRoundState(MMATCH_ROUNDSTATE roundState);



	vector<MMatchSpyItem> m_vtLastSpyItem, m_vtLastTrackerItem;
};