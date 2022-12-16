#include "stdafx.h"
#include "ZRuleReverseBerserker.h"


#define BERSERKER_UPDATE_HEALTH_TIME		5.0f		// 버서커는 5초마다 피가 10씩 준다.
#define BERSERKER_UPDATE_HEALTH				10
#define BERSERKER_BONUS_HEALTH				50			// 버서커는 적을 죽이면 50의 피가 찬다.

ZRuleReverseBerserker::ZRuleReverseBerserker(ZMatch* pMatch) : ZRule(pMatch), m_uidBerserker(0,0)
{

}

ZRuleReverseBerserker::~ZRuleReverseBerserker()
{


}

bool ZRuleReverseBerserker::OnCommand(MCommand* pCommand)
{
	if (!ZGetGame()) return false;

	switch (pCommand->GetID())
	{
	case MC_MATCH_ASSIGN_REVERSE_BERSERKER:
		{
			MUID uidBerserker;
			pCommand->GetParameter(&uidBerserker,		0, MPT_UID);

			AssignBerserker(uidBerserker);
		}
		break;
	case MC_MATCH_GAME_DEAD:
		{
			MUID uidAttacker, uidVictim;
			unsigned long int nAttackerArg, nVictimArg;

			pCommand->GetParameter(&uidAttacker, 0, MPT_UID);
			pCommand->GetParameter(&nAttackerArg, 1, MPT_UINT);
			pCommand->GetParameter(&uidVictim, 2, MPT_UID);
			pCommand->GetParameter(&nVictimArg, 3, MPT_UINT);


			bool bSuicide = false;
			if (uidAttacker == uidVictim) bSuicide = true;

			if ((uidAttacker != MUID(0,0)) && (uidAttacker == m_uidBerserker))
			{
				if (!bSuicide)
				{
					ZCharacter* pAttacker = ZGetGame()->m_CharacterManager.Find(uidAttacker);
					BonusHealth(pAttacker);
				}
			}
		}
		break;
	}

	return false;
}

void ZRuleReverseBerserker::OnResponseRuleInfo(MTD_RuleInfo* pInfo)
{
	MTD_RuleInfo_Berserker* pBerserkerRule = (MTD_RuleInfo_Berserker*)pInfo;
	AssignBerserker(pBerserkerRule->uidBerserker);
}


void ZRuleReverseBerserker::AssignBerserker(MUID& uidBerserker)
{
	if (!ZGetGame()) return;

	for (ZCharacterManager::iterator itor = ZGetGame()->m_CharacterManager.begin();
		itor != ZGetGame()->m_CharacterManager.end(); ++itor)
	{
		ZCharacter* pCharacter = (*itor).second;
		pCharacter->SetTagger(false);
	}

	ZCharacter* pBerserkerChar = ZGetGame()->m_CharacterManager.Find(uidBerserker);
	if (pBerserkerChar)
	{
		ZGetEffectManager()->AddBerserkerIcon(pBerserkerChar);
		pBerserkerChar->SetTagger(true);
		
		// 버서커가 되면 피가 꽉 찬다.
		if (!pBerserkerChar->IsDie())
		{
			float fMaxHP = pBerserkerChar->GetProperty()->fMaxHP.Ref();
			float fMaxAP = pBerserkerChar->GetProperty()->fMaxAP.Ref();
			pBerserkerChar->SetHP(fMaxHP);
			pBerserkerChar->SetAP(fMaxAP);


			if ( uidBerserker == ZGetMyUID())
				ZGetGameInterface()->PlayVoiceSound( VOICE_GOT_BERSERKER, 1600);
			else
				ZGetGameInterface()->PlayVoiceSound( VOICE_BERSERKER_DOWN, 1200);
		}

	}

	m_uidBerserker = uidBerserker;
	m_fElapsedHealthUpdateTime = 0.0f;
}

void ZRuleReverseBerserker::OnUpdate(float fDelta)
{
	m_fElapsedHealthUpdateTime += fDelta;

	if (BERSERKER_UPDATE_HEALTH_TIME < m_fElapsedHealthUpdateTime)
	{
		m_fElapsedHealthUpdateTime = 0.0f;
		for (ZCharacterManager::iterator itor = ZGetGame()->m_CharacterManager.begin();	itor != ZGetGame()->m_CharacterManager.end(); ++itor)
		{
			ZCharacter* pCharacter = (*itor).second;
			if(pCharacter->GetUID() != GetBerserkerUID() && !pCharacter->IsDie())
			AddHealth(pCharacter);
		}
	}
}

void ZRuleReverseBerserker::BonusHealth(ZCharacter* pBerserker)
{
	if (pBerserker)
	{
		if (pBerserker->IsDie()) 
		{
			CHECK_RETURN_CALLSTACK(BonusHealth);
			return;
		}

		float fBonusAP = 0.0f;
		float fBonusHP = BERSERKER_BONUS_HEALTH;

		float fMaxHP = pBerserker->GetProperty()->fMaxHP.Ref();

		if ((fMaxHP - pBerserker->GetHP()) < BERSERKER_BONUS_HEALTH)
		{
			fBonusHP = fMaxHP - pBerserker->GetHP();
			fBonusAP = BERSERKER_BONUS_HEALTH - fBonusHP;
		}

		pBerserker->SetHP(pBerserker->GetHP() + fBonusHP);
		pBerserker->SetAP(pBerserker->GetAP() + fBonusAP);
	}
	CHECK_RETURN_CALLSTACK(BonusHealth);
}

void ZRuleReverseBerserker::AddHealth(ZCharacter* Uid)
{
	float fAP = max(0.0f, Uid->GetAP() + BERSERKER_UPDATE_HEALTH);
	Uid->SetAP(fAP);

	float fHP = max(1.0f, Uid->GetHP() + BERSERKER_UPDATE_HEALTH);
    Uid->SetHP(fHP);

}