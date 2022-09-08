Open(ZGameInput.cpp) - Gets 1+hp every second<br>
Find <br>

    ZGameInput* ZGameInput::m_pInstance = NULL;
    
Add all the way at the top

    #include "ZModule_HealOverTime.h"
    
Find <br>

    ZMyCharacter* pMyCharacter = ZGetGameInterface()->GetGame()->m_pMyCharacter;

Place under <br>

  	ZModule_HealOverTime *pModule = (ZModule_HealOverTime*)ZGetGame()->m_pMyCharacter->GetModule(ZMID_HEALOVERTIME);
	  pModule->BeginHeal(MMDT_HEAL, 1 ,1000,MMIEI_NONE,30001);









