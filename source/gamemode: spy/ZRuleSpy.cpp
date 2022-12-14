#include "stdafx.h"
#include "ZRuleSpy.h"
#include "../SpyModeSystem/MMatchSpyMode.h"
#include "../SpyModeSystem/MMatchSpyMap.h"
#include "ZBmNumLabel.h"
#include "MBlobArray.h"
#include "ZScreenEffectManager.h"

ZRuleSpy::ZRuleSpy(ZMatch* pMatch) : ZRule(pMatch)
{

}

ZRuleSpy::~ZRuleSpy()
{
	m_vtLastSpyItem.clear();
	m_vtLastTrackerItem.clear();
}

bool ZRuleSpy::OnCommand(MCommand* pCommand)
{
	if(!ZApplication::GetGameInterface()->GetCombatInterface() || !ZGetGame()) 
	{
		_ASSERT(0);
		return false;
	}

	switch(pCommand->GetID())
	{
	case MC_SPY_GAME_INFO	:
		{
			if(ZGetGame()->GetMatch()->GetRoundState() == MMATCH_ROUNDSTATE_PLAY)
				if(!m_vtLastSpyItem.empty() || !m_vtLastTrackerItem.empty()) // assuming item empty = game info uninitialized. just accept this game info.
					break;

			unsigned int nSpyHPAP;

			pCommand->GetParameter(&nSpyHPAP, 2, MPT_UINT);

			MCommandParameter* pSpyParam = pCommand->GetParameter(0);
			MCommandParameter* pSpyItemParam = pCommand->GetParameter(1);
			MCommandParameter* pTrackerItemParam = pCommand->GetParameter(3);

			if(!pSpyParam || !pSpyItemParam || !pTrackerItemParam)
			{
				_ASSERT(0);
				break;
			}

			if(pSpyParam->GetType() != MPT_BLOB || pSpyItemParam->GetType() != MPT_BLOB || pTrackerItemParam->GetType() != MPT_BLOB)
			{
				_ASSERT(0);
				break;
			}

			void* pSpyBlob = pSpyParam->GetPointer();
			void* pSpyItemBlob = pSpyItemParam->GetPointer();
			void* pTrackerItemBlob = pTrackerItemParam->GetPointer();

			int nSpyCount = MGetBlobArrayCount(pSpyBlob);
			int nSpyItemCount = MGetBlobArrayCount(pSpyItemBlob);
			int nTrackerItemCount = MGetBlobArrayCount(pTrackerItemBlob);

			///// Set Spy /////
			// reset all players to MMT_BLUE (tracker).
			for(ZCharacterManager::iterator i = ZGetGame()->m_CharacterManager.begin(); i != ZGetGame()->m_CharacterManager.end(); i++)
			{
				ZCharacter* pCurrChar = (*i).second;

				pCurrChar->SpyHealthBonus(0);
				pCurrChar->SetTeamID(MMT_BLUE);
			}

			// and set selected spy as MMT_RED.
			for(int i = 0; i < nSpyCount; i++)
			{
				MUID* uid = (MUID*)MGetBlobArrayElement(pSpyBlob, i);

				ZCharacter* pCharacter = ZGetGame()->m_CharacterManager.Find(*uid);
				if(!pCharacter) continue;

				// pCharacter->SetMaxHP(pCharacter->GetMaxHP() + (float)nSpyHPAP);
				// pCharacter->SetMaxAP(pCharacter->GetMaxAP() + (float)nSpyHPAP);
				pCharacter->SpyHealthBonus((int)nSpyHPAP);

				pCharacter->SetTeamID(MMT_RED);
			}

			///// Save Spy Item /////
			m_vtLastSpyItem.clear();

			for(int i = 0; i < nSpyItemCount; i++)
			{
				MMatchSpyItem* pSpyItem = (MMatchSpyItem*)MGetBlobArrayElement(pSpyItemBlob, i);
				m_vtLastSpyItem.push_back(*pSpyItem);
			}

			///// Save Tracker Item /////
			m_vtLastTrackerItem.clear();

			for(int i = 0; i < nTrackerItemCount; i++)
			{
				MMatchSpyItem* pTrackerItem = (MMatchSpyItem*)MGetBlobArrayElement(pTrackerItemBlob, i);
				m_vtLastTrackerItem.push_back(*pTrackerItem);
			}
		}
		break;

	case MC_SPY_GAME_RESULT	:
		{
			MCommandParameter* pParam = pCommand->GetParameter(0);

			if(!pParam || pParam->GetType() != MPT_BLOB)
			{
				_ASSERT(0);
				break;
			}

			void* pBlob = pParam->GetPointer();

			for(int i = 0; i < MGetBlobArrayCount(pBlob); i++)
			{
				MTD_SpyRoundFinishInfo* info = (MTD_SpyRoundFinishInfo*)MGetBlobArrayElement(pBlob, i);

				ZCharacter* pCharacter = ZGetGame()->m_CharacterManager.Find(info->uidPlayer);
				if(!pCharacter) continue;

				pCharacter->GetStatus().CheckCrc();
				pCharacter->GetStatus().Ref().AddExp(info->nXP);
				pCharacter->GetStatus().MakeCrc();

				if(pCharacter == ZGetGame()->m_pMyCharacter)
				{
					ZGetScreenEffectManager()->AddExpEffect(info->nXP);

					ZGetMyInfo()->SetLevelPercent(info->nPercent);
					ZGetScreenEffectManager()->SetGaugeExpFromMyInfo();

					char szExp[64], szBounty[64];
					char szOutput[256];

					sprintf(szExp, "%d", info->nXP);
					sprintf(szBounty, "%d", info->nBP);

					if(ZTransMsg(szOutput, MSG_SPY_EXP_BONUS, 2, szExp, szBounty))
						ZChatOutput(szOutput, ZChat::CMT_SYSTEM, ZChat::CL_CURRENT);
				}
			}
		}
		break;
	}

	return false;
}

void ZRuleSpy::AfterCommandProcessed(MCommand* pCommand)
{
	if(!ZGetGame()) 
	{
		_ASSERT(0);
		return;
	}

	switch(pCommand->GetID())
	{
	case MC_MATCH_GAME_DEAD	:
		{
			if(!ZGetScreenEffectManager())
			{
				_ASSERT(0);
				break;
			}

			MUID uidVictim;
			pCommand->GetParameter(&uidVictim, 2, MPT_UID);

			ZCharacter* pCharacter = ZGetGame()->m_CharacterManager.Find(uidVictim);
			if(!pCharacter) break;

			if(pCharacter->GetTeamID() == MMT_RED)
			{
				int nRedCount = 0;

				for(ZCharacterManager::iterator i = ZGetGame()->m_CharacterManager.begin(); i != ZGetGame()->m_CharacterManager.end(); i++)
				{
					ZCharacter* pCurrCharacter = (*i).second;

					if(!pCurrCharacter->GetInitialized()) continue;
					if(pCurrCharacter->IsDie()) continue;

					if(pCurrCharacter->GetTeamID() == MMT_RED)
					{
						nRedCount++;
					}
				}

				if(nRedCount == 0)
					ZGetScreenEffectManager()->AddScreenEffect("spy_eliminationAllKill");
				else if(nRedCount == 1)
					ZGetScreenEffectManager()->AddScreenEffect("spy_elimination1Remain");
				else if(nRedCount == 2)
					ZGetScreenEffectManager()->AddScreenEffect("spy_elimination2Remain");
			}
		}
		break;
	}
}

void ZRuleSpy::OnSetRoundState(MMATCH_ROUNDSTATE roundState)
{
	switch(roundState)
	{
	case MMATCH_ROUNDSTATE_PREPARE:
		{
			if(ZApplication::GetGameInterface()->GetCombatInterface())
			{
				ZIDLResource* pIDLResource = ZApplication::GetGameInterface()->GetIDLResource();

				MFrame* pFrame = (MFrame*)pIDLResource->FindWidget("CombatSpyInfo");
				if(pFrame)
					pFrame->Show(false);

				ZBmNumLabel* pNumLabel = (ZBmNumLabel*)pIDLResource->FindWidget("Spy_CountDownTime");
				if(pNumLabel)
					pNumLabel->Show(false);

				pNumLabel = (ZBmNumLabel*)pIDLResource->FindWidget("Spy_CountDownTime_Red");
				if(pNumLabel)
					pNumLabel->Show(false);

				ZApplication::GetGameInterface()->GetCombatInterface()->SetSpyEventMsg(NULL);
				ZApplication::GetGameInterface()->GetCombatInterface()->SetSpyTip(NULL);
				ZApplication::GetGameInterface()->GetCombatInterface()->SetSpyNotice(NULL);
				ZApplication::GetGameInterface()->GetCombatInterface()->m_bSpyLocationOpened = false;
			}
		}
		break;

	case MMATCH_ROUNDSTATE_COUNTDOWN:
		{
			if(ZApplication::GetGameInterface()->GetCombatInterface())
			{
				ZApplication::GetGameInterface()->GetCombatInterface()->CreateSpyGameInterface();
				ZApplication::GetGameInterface()->GetCombatInterface()->SetSpyTimer(MSPYMODE_ROUNDSTATE_COUNTDOWN_TIME);
				ZApplication::GetGameInterface()->GetCombatInterface()->SetSpyEventMsg("Spy_EventMsg_ComingSoonOpenSpy.png");

				if(ZGetGame() && ZGetGame()->m_pMyCharacter)
				{
					if(ZGetGame()->m_pMyCharacter->GetTeamID() == MMT_RED)
						ZApplication::GetGameInterface()->GetCombatInterface()->PlaySpyNotice("Spy_Notice_Spy.png");
					else
						ZApplication::GetGameInterface()->GetCombatInterface()->PlaySpyNotice("Spy_Notice_Tracer.png");
				}
			}
		}
		break;

	case MMATCH_ROUNDSTATE_PLAY:
		{
			if(ZApplication::GetGameInterface()->GetCombatInterface())
			{
				ZApplication::GetGameInterface()->GetCombatInterface()->CreateSpyGameInterface();
				ZApplication::GetGameInterface()->GetCombatInterface()->SetSpyTimer(ZGetGameClient()->GetMatchStageSetting()->GetLimitTime());

				if(ZGetGame())
				{
					if(ZGetGame()->m_pMyCharacter)
					{
						ZApplication::GetGameInterface()->GetCombatInterface()->SetDefaultSpyTip(ZGetGame()->m_pMyCharacter->GetTeamID());
						if(ZGetGame()->m_pMyCharacter->GetTeamID() == MMT_RED)
							ZApplication::GetGameInterface()->GetCombatInterface()->SetSpyEventMsg("Spy_EventMsg_Survive.png");
						else
							ZApplication::GetGameInterface()->GetCombatInterface()->SetSpyEventMsg("Spy_EventMsg_EliminateSpy.png");
					}

					for(ZCharacterManager::iterator i = ZGetGame()->m_CharacterManager.begin(); i != ZGetGame()->m_CharacterManager.end(); i++)
					{
						ZCharacter* pCharacter = (*i).second;

						if(pCharacter->GetTeamID() == MMT_RED)
						{
							pCharacter->DistributeSpyItem(m_vtLastSpyItem);
						}
						else
						{
							pCharacter->DistributeSpyItem(m_vtLastTrackerItem);
						}
					}

					_ASSERT(!m_vtLastSpyItem.empty() || !m_vtLastTrackerItem.empty());
				}
			}
		}
		break;

	case MMATCH_ROUNDSTATE_FINISH:
		{
			ZBmNumLabel* pNumLabel = (ZBmNumLabel*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Spy_CountDownTime");
			if(pNumLabel)
				pNumLabel->Show(false);

			pNumLabel = (ZBmNumLabel*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Spy_CountDownTime_Red");
			if(pNumLabel)
				pNumLabel->Show(false);

			if(ZGetGame())
			{
				for(ZCharacterManager::iterator i = ZGetGame()->m_CharacterManager.begin(); i != ZGetGame()->m_CharacterManager.end(); i++)
				{
					ZCharacter* pCharacter = (*i).second;
					pCharacter->TakeoutSpyItem();
				}
			}
		}
		break;

	case MMATCH_ROUNDSTATE_FREE:
		{
			if(ZApplication::GetGameInterface()->GetCombatInterface())
			{
				ZApplication::GetGameInterface()->GetCombatInterface()->CreateSpyWaitInterface();
			}
		}
		break;
	}
}
