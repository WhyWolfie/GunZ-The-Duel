#include "stdafx.h"
#include "MMatchRuleGunGame.h"
#include "MBlobArray.h"
#include <algorithm>
#include <random>

MMatchRuleGunGame::MMatchRuleGunGame(MMatchStage* pStage) : MMatchRule(pStage)
{
}

MMatchRuleGunGame::~MMatchRuleGunGame()
{
}

void MMatchRuleGunGame::OnBegin()
{
	if (m_MatchSet.size() > 0)
		m_MatchSet.clear();

	m_MatchSet = MGetGunGame()->GetGGSet(rand() % MGetGunGame()->GetSetCount());
	//To shuffle or not to shuffle? that is the question.
	std::random_shuffle(m_MatchSet.begin(), m_MatchSet.end());
}

void MMatchRuleGunGame::OnRoundBegin()
{

}

void MMatchRuleGunGame::OnEnd()
{
	m_MatchSet.clear();
}

void MMatchRuleGunGame::OnRoundEnd()
{
}

bool MMatchRuleGunGame::RoundCount()
{
	if (++m_nRoundCount < 1) return true;
	return false;
}


void MMatchRuleGunGame::OnRoundTimeOut()
{
	SetRoundArg(MMATCH_ROUNDRESULT_DRAW);
}

void MMatchRuleGunGame::OnGameKill(const MUID& uidAttacker, const MUID& uidVictim)
{
	MMatchObject* pAttacker = MGetMatchServer()->GetObject(uidAttacker);
	MMatchObject* pVictim = MGetMatchServer()->GetObject(uidVictim);
	if (!GetStage())
		return;
	if (!pAttacker || !pVictim)
		return;

	//OnKilling yourself, you go back a level
	if (pAttacker == pVictim)
	{
		pAttacker->SetKillCount(pAttacker->GetKillCount() - 1);
	}

	SendNewSet(pAttacker->GetUID(), pAttacker->GetKillCount(), pAttacker == pVictim);
}

bool MMatchRuleGunGame::CheckKillCount(MMatchObject* pOutObj)
{
	MMatchStage* pStage = GetStage();
	for (MUIDRefCache::iterator i = pStage->GetObjBegin(); i != pStage->GetObjEnd(); i++)
	{
		MMatchObject* pObj = (MMatchObject*)(*i).second;
		if (pObj->GetEnterBattle() == false) continue;

		//We want the player to be able to hit the last gungame level
		if (pObj->GetKillCount() > (unsigned int)pStage->GetStageSetting()->GetRoundMax())
		{
			pOutObj = pObj;
			return true;
		}
	}
	return false;
}

bool MMatchRuleGunGame::OnCheckRoundFinish()
{
	MMatchObject* pObj = nullptr;

	if (CheckKillCount(pObj))
	{
		return true;
	}
	return false;
}

void MMatchRuleGunGame::SendNewSet(const MUID& uidPlayer,int KillCount, bool isSuicide)
{
	if (KillCount > static_cast<int>(m_MatchSet.size()))
		return;
	GGSet pSet = m_MatchSet.at(KillCount);
	MCommand* pCommand = MGetMatchServer()->CreateCommand(MC_MATCH_GUNGAME_SEND_NEW_WEAPON, MUID(0, 0));
	pCommand->AddParameter(new MCmdParamUID(uidPlayer));
	pCommand->AddParameter(new MCmdParamUInt(pSet.WeaponSet[0]));
	pCommand->AddParameter(new MCmdParamUInt(pSet.WeaponSet[1]));
	pCommand->AddParameter(new MCmdParamUInt(pSet.WeaponSet[2]));
	pCommand->AddParameter(new MCmdParamBool(isSuicide));

	MGetMatchServer()->RouteToBattle(GetStage()->GetUID(), pCommand);
}

bool MMatchRuleGunGame::OnRun()
{
	return MMatchRule::OnRun();
}

void MMatchRuleGunGame::OnEnterBattle(MUID& uidPlayer)
{
	MMatchObject* pJoiner = MGetMatchServer()->GetObject(uidPlayer);
	SendNewSet(pJoiner->GetUID(), 0,false);
	for (auto itor = GetStage()->GetObjBegin(); itor != GetStage()->GetObjEnd(); ++itor)
	{
		MMatchObject* pObj = (MMatchObject*)(*itor).second;
		if (pObj->GetUID() == uidPlayer)
			continue;
		if (!pObj->GetEnterBattle())
			continue;
		//TODO: make a separate function to send all players weapon info?
		SendNewSet(pObj->GetUID(), pObj->GetKillCount(),false);
	}

	MCommand* pCmd = MGetMatchServer()->CreateCommand(MC_MATCH_GUNGAME_SET, MUID(0, 0));
	void* weaponSet = MMakeBlobArray(sizeof(GGWeaponSet), (int)m_MatchSet.size());
	vector<GGSet> items;
	for (int i = 0; i < MGetBlobArrayCount(weaponSet); ++i)
	{
		GGWeaponSet itemSet = {};
		memcpy(itemSet.WeaponSet, m_MatchSet[i].WeaponSet,12);
		*(GGWeaponSet*)MGetBlobArrayElement(weaponSet, i) = itemSet;
	}
	pCmd->AddParameter(new MCmdParamBlob(weaponSet, MGetBlobArraySize(weaponSet)));

	MGetMatchServer()->RouteToListener(pJoiner, pCmd);
}