#include "stdafx.h"
#include "MMatchRuleSpy.h"
#include "MBlobArray.h"
#include "MMatchFormula.h"

MMatchRuleSpy::MMatchRuleSpy(MMatchStage* pStage) : MMatchRule(pStage)
{
	m_nStartPlayers = 0;
}

MMatchRuleSpy::~MMatchRuleSpy()
{
	m_vtSpy.clear();
	m_vtParticipant.clear();
}

void MMatchRuleSpy::OnBegin()
{
}

void MMatchRuleSpy::OnEnd()
{
}

bool MMatchRuleSpy::OnRun()
{
	bool ret = MMatchRule::OnRun();


	return ret;
}

void MMatchRuleSpy::OnRoundBegin()
{
	SendGameInfo();

	MMatchRule::OnRoundBegin();
}

void MMatchRuleSpy::OnRoundEnd()
{
	switch(m_nRoundArg)
	{
	case MMATCH_ROUNDRESULT_BLUE_ALL_OUT:
	case MMATCH_ROUNDRESULT_REDWON:
		DistributeTeamBonus(MMT_RED);
		break;

	case MMATCH_ROUNDRESULT_RED_ALL_OUT:
	case MMATCH_ROUNDRESULT_BLUEWON:
		DistributeTeamBonus(MMT_BLUE);
		break;

	case MMATCH_ROUNDRESULT_DRAW:
		break;
	}

	MMatchRule::OnRoundEnd();
}

bool MMatchRuleSpy::OnCheckEnableBattleCondition()
{
	// ｼｱｽﾂﾁｦﾀﾏ ｰ豼・ﾂ Freeｻﾂｰ｡ ｾﾈｵﾈｴﾙ.
	if (m_pStage->GetStageSetting()->IsTeamWinThePoint() == true)
	{
		return true;
	}

	int nPlayers = 0;
	int nStageObjects = 0;		// ｰﾔﾀﾓｾﾈｿ｡ ｾ・ｽｺﾅﾗﾀﾌﾁ｡ ﾀﾖｴﾂ ｻ邯・

	MMatchStage* pStage = GetStage();
	if (pStage == NULL) return false;

	for (MUIDRefCache::iterator i=pStage->GetObjBegin(); i!=pStage->GetObjEnd(); i++) 
	{
		MMatchObject* pObj = (MMatchObject*)(*i).second;
		if ((pObj->GetEnterBattle() == false) && (!pObj->IsLaunchedGame()))
		{
			nStageObjects++;
			continue;
		}

		nPlayers++;
	}

	if(nPlayers < MMatchSpyMode::GetMinPlayers())
	{
		return false;
	}

	return true;
}

// ｸｸｾ・ｷｹｵ衄ﾀﾀﾌｳｪ ｺ昞酥ﾀｿ｡ｼｭ ﾆﾀｿﾌ 0ｸ暲ﾏ ｰ豼・ﾂ false ｹﾝﾈｯ , true,false ｸﾎ AliveCount ｹﾝﾈｯ
bool MMatchRuleSpy::GetAliveCount(int* pRedAliveCount, int* pBlueAliveCount)
{
	int nRedCount = 0, nBlueCount = 0;
	int nRedAliveCount = 0, nBlueAliveCount = 0;
	(*pRedAliveCount) = 0;
	(*pBlueAliveCount) = 0;

	MMatchStage* pStage = GetStage();
	if (pStage == NULL) return false;

	for (MUIDRefCache::iterator i=pStage->GetObjBegin(); i!=pStage->GetObjEnd(); i++) 
	{
		MMatchObject* pObj = (MMatchObject*)(*i).second;
		if (pObj->GetEnterBattle() == false) continue;	// ｹ霹ｲﾂ・｡ﾇﾏｰ・ﾀﾖｴﾂ ﾇﾃｷｹﾀﾌｾ鋕ｸ ﾃｼﾅｩ

		if (pObj->GetTeam() == MMT_RED)
		{
			nRedCount++;
			if (pObj->CheckAlive()==true)
			{
				nRedAliveCount++;
			}
		}
		else if (pObj->GetTeam() == MMT_BLUE)
		{
			nBlueCount++;
			if (pObj->CheckAlive()==true)
			{
				nBlueAliveCount++;
			}
		}
	}

	(*pRedAliveCount) = nRedAliveCount;
	(*pBlueAliveCount) = nBlueAliveCount;

	if ((nRedAliveCount == 0) || (nBlueAliveCount == 0))
	{
		return false;
	}
	return true;
}

bool MMatchRuleSpy::OnCheckRoundFinish()
{
	int nRedAliveCount = 0;
	int nBlueAliveCount = 0;

	// ﾆﾀｿﾌ 0ｸ暲ﾎ ﾆﾀﾀﾌ ﾀﾖﾀｸｸ・falseｹﾝﾈｯ
	if (GetAliveCount(&nRedAliveCount, &nBlueAliveCount) == false)
	{
		int nRedTeam = 0, nBlueTeam = 0;
		int nStageObjects = 0;		// ｰﾔﾀﾓｾﾈｿ｡ ｾ・ｽｺﾅﾗﾀﾌﾁ｡ ﾀﾖｴﾂ ｻ邯・

		MMatchStage* pStage = GetStage();

		for (MUIDRefCache::iterator i=pStage->GetObjBegin(); i!=pStage->GetObjEnd(); i++) 
		{
			MMatchObject* pObj = (MMatchObject*)(*i).second;
			if ((pObj->GetEnterBattle() == false) && (!pObj->IsLaunchedGame()))
			{
				nStageObjects++;
				continue;
			}

			if (pObj->GetTeam() == MMT_RED)		nRedTeam++;
			else if (pObj->GetTeam() == MMT_BLUE)	nBlueTeam++;
		}

		if( nBlueTeam ==0 && (pStage->GetTeamScore(MMT_BLUE) > pStage->GetTeamScore(MMT_RED)) )
			SetRoundArg(MMATCH_ROUNDRESULT_BLUE_ALL_OUT);
		else if( nRedTeam ==0 && (pStage->GetTeamScore(MMT_RED) > pStage->GetTeamScore(MMT_BLUE)) )
			SetRoundArg(MMATCH_ROUNDRESULT_RED_ALL_OUT);
		else if ( (nRedAliveCount == 0) && (nBlueAliveCount == 0) )
			SetRoundArg(MMATCH_ROUNDRESULT_DRAW);
		else if (nRedAliveCount == 0)
			SetRoundArg(MMATCH_ROUNDRESULT_BLUEWON);
		else if (nBlueAliveCount == 0)
			SetRoundArg(MMATCH_ROUNDRESULT_REDWON);
	}

	if (nRedAliveCount==0 || nBlueAliveCount==0) return true;
	else return false;
}

void MMatchRuleSpy::OnRoundTimeOut()
{
	SetRoundArg(MMATCH_ROUNDRESULT_REDWON);
}

void MMatchRuleSpy::OnRoundCountdown()
{
	if(!m_pStage) return;

	m_vtParticipant.clear();

	for(MUIDRefCache::iterator i = m_pStage->GetObjBegin(); i != m_pStage->GetObjEnd(); i++)
	{
		MMatchObject* pObj = (MMatchObject*)(*i).second;
		if(pObj->GetEnterBattle()) m_vtParticipant.push_back(pObj->GetUID());
	}

	m_nStartPlayers = (int)m_vtParticipant.size();

	SelectRandomSpy();
}

// ｹﾝﾈｯｰｪﾀﾌ falseﾀﾌｸ・ｰﾔﾀﾓﾀﾌ ｳ｡ｳｭｴﾙ.
bool MMatchRuleSpy::RoundCount() 
{
	if (m_pStage == NULL) return false;

	int nTotalRound = m_pStage->GetStageSetting()->GetRoundMax();
	m_nRoundCount++;

	if (m_pStage->GetStageSetting()->IsTeamWinThePoint() == false)
	{
		// ｼｱｽﾂﾁｦｰ｡ ｾﾆｴﾒ ｰ豼・
		if (m_nRoundCount < nTotalRound) return true;

	}
	else
	{
		// ｼｱｽﾂﾁｦﾀﾏ ｰ豼・

		// ﾆﾀｿﾌ 0ｸ暲ﾎ ﾆﾀﾀﾌ ﾀﾖｾ鋙ｵ ｰﾔﾀﾓﾀﾌ ｳ｡ｳｭｴﾙ.
		int nRedTeamCount=0, nBlueTeamCount=0;
		m_pStage->GetTeamMemberCount(&nRedTeamCount, &nBlueTeamCount, NULL, true);

		if ((nRedTeamCount == 0) || (nBlueTeamCount == 0))
		{
			return false;
		}

		int nRedScore = m_pStage->GetTeamScore(MMT_RED);
		int nBlueScore = m_pStage->GetTeamScore(MMT_BLUE);
		
		// ｷ｡ｴﾔﾀﾓｿ｡ｼｭ ｸﾕﾀ・4ｽﾂﾀﾎ ﾆﾀﾀﾌ ｽﾂｸｮ
		const int LADDER_WINNING_ROUNT_COUNT = 4;


		// ｵﾎﾆﾀﾀﾌ ｸﾎ 4ｽﾂﾀﾌ ｾﾆｴﾏｸ・trueｹﾝﾈｯ
		if ((nRedScore < LADDER_WINNING_ROUNT_COUNT) && (nBlueScore < LADDER_WINNING_ROUNT_COUNT))
		{
			return true;
		}
	}

	return false;
}

void MMatchRuleSpy::DistributeTeamBonus(MMatchTeam nTeam)
{
	if(!m_pStage) return;

	const unsigned long int nCurrTime = MMatchServer::GetInstance()->GetGlobalClockCount();
	const unsigned long int nElapsedTime = nCurrTime - m_tmRoundStateTimer;

	const int nBonusXP = (int)(nElapsedTime / 3);
	const int nBonusBP = (int)(nElapsedTime / 25);

	if(nBonusXP <= 0 && nBonusBP <= 0) return;

	vector<MTD_SpyRoundFinishInfo> vtBlobInfo;

	for(MUIDRefCache::iterator i = m_pStage->GetObjBegin(); i != m_pStage->GetObjEnd(); i++)
	{
		MMatchObject* pObj = (MMatchObject*)(*i).second;
		if(!IsEnabledObject(pObj)) continue;

		if(!IsParticipant(pObj->GetUID())) continue;
		if(pObj->GetTeam() != nTeam) continue;

		MMatchServer::GetInstance()->ProcessPlayerXPBP(m_pStage, pObj, nBonusXP, nBonusBP);


		MTD_SpyRoundFinishInfo info;

		info.uidPlayer = pObj->GetUID();
		info.nXP = nBonusXP;
		info.nPercent = MMatchFormula::GetLevelPercent(pObj->GetCharInfo()->m_nXP, pObj->GetCharInfo()->m_nLevel);
		info.nBP = nBonusBP;
		info.nPoint = 0;

		vtBlobInfo.push_back(info);
	}

	void* pTeamBonusBlob = MMakeBlobArray(sizeof(MTD_SpyRoundFinishInfo), (int)vtBlobInfo.size());

	for(int i = 0; i < (int)vtBlobInfo.size(); i++)
		*(MTD_SpyRoundFinishInfo*)MGetBlobArrayElement(pTeamBonusBlob, i) = vtBlobInfo[i];

	MCommand* pCmd = MMatchServer::GetInstance()->CreateCommand(MC_SPY_GAME_RESULT, MUID(0,0));
	pCmd->AddParameter(new MCmdParamBlob(pTeamBonusBlob, MGetBlobArraySize(pTeamBonusBlob)));
	MMatchServer::GetInstance()->RouteToBattle(m_pStage->GetUID(), pCmd);

	MEraseBlobArray(pTeamBonusBlob);
}

void MMatchRuleSpy::OnEnterBattle(MUID& uidChar)
{
	// SendGameInfo();
}

void MMatchRuleSpy::OnLeaveBattle(MUID& uidChar)
{
	vector<MUID>::iterator itSpyBegin, itSpyEnd, itSpyFound, itParticipantBegin, itParticipantEnd, itParticipantFound;

	itSpyBegin	= m_vtSpy.begin();
	itSpyEnd	= m_vtSpy.end();
	itSpyFound	= std::find(itSpyBegin, itSpyEnd, uidChar);

	if(itSpyFound != itSpyEnd)
		m_vtSpy.erase(itSpyFound);

	itParticipantBegin	= m_vtParticipant.begin();
	itParticipantEnd	= m_vtParticipant.end();
	itParticipantFound	= std::find(itParticipantBegin, itParticipantEnd, uidChar);

	if(itParticipantFound != itParticipantEnd)
		m_vtParticipant.erase(itParticipantFound);
}

bool MMatchRuleSpy::IsSpy(const MUID& uidPlayer)
{
	return std::find(m_vtSpy.begin(), m_vtSpy.end(), uidPlayer) != m_vtSpy.end();
}

bool MMatchRuleSpy::IsParticipant(const MUID& uidPlayer)
{
	return std::find(m_vtParticipant.begin(), m_vtParticipant.end(), uidPlayer) != m_vtParticipant.end();
}

bool MMatchRuleSpy::SelectRandomSpy()
{
	// clear old.
	m_vtSpy.clear();

	if(!m_pStage) return false;

	const MMatchSpyTableData* pSpyTable = MMatchSpyMode::GetSpyTable(m_nStartPlayers);
	_ASSERT(pSpyTable != NULL);

	deque<MUID> vtCandUIDs;

	// get.
	/*
	for(MUIDRefCache::iterator it = m_pStage->GetObjBegin(); it != m_pStage->GetObjEnd(); i++)
	{
		MMatchObject* pObj = (MMatchObject*)(*it).second;
		if(pObj->GetEnterBattle()) vtCandUIDs.push_back(pObj->GetUID());
	}
	*/
	for(vector<MUID>::iterator it = m_vtParticipant.begin(); it != m_vtParticipant.end(); it++)
		vtCandUIDs.push_back(*it);

	if(vtCandUIDs.size() == 0)
	{
		_ASSERT(0);
		return false;
	}

	// shuffle.
	for(int i = 0; i < (int)vtCandUIDs.size(); i++)
	{
		int nRand = ((int)rand() % (int)vtCandUIDs.size());

		MUID tmp = vtCandUIDs[nRand];
		vtCandUIDs[nRand] = vtCandUIDs[i];
		vtCandUIDs[i] = tmp;
	}

	// make.
	int nInsert = pSpyTable->nSpyCount;

	while(nInsert > 0 && !vtCandUIDs.empty())
	{
		m_vtSpy.push_back(vtCandUIDs.front());
		vtCandUIDs.pop_front();

		nInsert--;
	}

	RefreshTeamIDs();

	SendGameInfo();

	return true;
}

void MMatchRuleSpy::RefreshTeamIDs()
{
	if(!m_pStage) return;

	for(MUIDRefCache::iterator it = m_pStage->GetObjBegin(); it != m_pStage->GetObjEnd(); it++)
	{
		MMatchObject* pObj = (MMatchObject*)(*it).second;

		if(pObj->GetEnterBattle())
		{
			MMatchTeam nTeam = IsSpy(pObj->GetUID()) ? MMT_RED : MMT_BLUE;
			m_pStage->PlayerTeam(pObj->GetUID(), nTeam);
		}
	}
}

void MMatchRuleSpy::SendGameInfo()
{
	if(!m_pStage) return;

	// Spy.
	void* pSpyBlob = MMakeBlobArray(sizeof(MUID), (int)m_vtSpy.size());

	for(int i = 0; i < (int)m_vtSpy.size(); i++)
		*(MUID*)MGetBlobArrayElement(pSpyBlob, (int)i) = m_vtSpy[i];

	// Spy Item.
	const MMatchSpyTableData* pSpyTable = MMatchSpyMode::GetSpyTable(m_nStartPlayers);
	_ASSERT(pSpyTable != NULL);

	void* pSpyItemBlob = MMakeBlobArray(sizeof(MMatchSpyItem), MMatchSpyTableData::ITEM::MAX);

	for(int i = 0; i < MMatchSpyTableData::MAX; i++)
		*(MMatchSpyItem*)MGetBlobArrayElement(pSpyItemBlob, i) = pSpyTable->SpyItem[i];

	// Tracker Item.
	const MMatchSpyTrackerTableData* pTrackerTable = MMatchSpyMode::GetTrackerTable();
	_ASSERT(pTrackerTable != NULL);

	void* pTrackerItemBlob = MMakeBlobArray(sizeof(MMatchSpyItem), MMatchSpyTrackerTableData::ITEM::MAX);

	for(int i = 0; i < MMatchSpyTrackerTableData::ITEM::MAX; i++)
		*(MMatchSpyItem*)MGetBlobArrayElement(pTrackerItemBlob, i) = pTrackerTable->TrackerItem[i];

	// Send Command.
	MCommand* pCmd = MMatchServer::GetInstance()->CreateCommand(MC_SPY_GAME_INFO, MUID(0,0));
	pCmd->AddParameter(new MCmdParamBlob(pSpyBlob, MGetBlobArraySize(pSpyBlob)));
	pCmd->AddParameter(new MCmdParamBlob(pSpyItemBlob, MGetBlobArraySize(pSpyItemBlob)));
	pCmd->AddParameter(new MCmdParamUInt(pSpyTable->nHPAP));
	pCmd->AddParameter(new MCmdParamBlob(pTrackerItemBlob, MGetBlobArraySize(pTrackerItemBlob)));
	MMatchServer::GetInstance()->RouteToBattle(m_pStage->GetUID(), pCmd);

	MEraseBlobArray(pTrackerItemBlob);
	MEraseBlobArray(pSpyItemBlob);
	MEraseBlobArray(pSpyBlob);
}

