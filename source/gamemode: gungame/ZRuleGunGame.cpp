#include "stdafx.h"
#include "ZRuleGunGame.h"

ZRuleGunGame::ZRuleGunGame(ZMatch* pMatch) : ZRule(pMatch)
{
	m_nSetID = 0;
	matchSet.clear();
}

ZRuleGunGame::~ZRuleGunGame()
{
	matchSet.clear();
}

bool ZRuleGunGame::OnCommand(MCommand* pCommand)
{
	if (!ZGetGame())
		return false;

	switch (pCommand->GetID())
	{
		case MC_MATCH_GUNGAME_SET:
		{
			MCommandParameter*  pParam = pCommand->GetParameter(0);
			if (pParam->GetType() != MPT_BLOB)
				break;

			void* weaponSet = pParam->GetPointer();
			int Count = MGetBlobArrayCount(weaponSet);
			for (int i = 0; i < Count; ++i)
			{
				GGWeaponSet itemSet = *(GGWeaponSet*)MGetBlobArrayElement(weaponSet, i);
				matchSet.push_back(itemSet);
			}
			return true;
		}
		break;
		case MC_MATCH_GUNGAME_SEND_NEW_WEAPON:
		{
			int WeaponSet[3];
			MUID uidPlayer;
			bool isSuicide;
			pCommand->GetParameter(&uidPlayer,0,MPT_UID);
			pCommand->GetParameter(&WeaponSet[0], 1,MPT_UINT);
			pCommand->GetParameter(&WeaponSet[1], 2, MPT_UINT);
			pCommand->GetParameter(&WeaponSet[2], 3, MPT_UINT);
			pCommand->GetParameter(&isSuicide, 4, MPT_BOOL);

			SetPlayerWeapons(uidPlayer, WeaponSet,isSuicide);

			return true;
		}
		break;
		//TODO: go back a set if you die?
		/*
		case MC_MATCH_GUNGAME_DIE:
		{
			int WeaponSet[3];
			MUID uidPlayer;
			pCommand->GetParameter(&uidPlayer,0,MPT_UID);
			pCommand->GetParameter(&WeaponSet[0],1,MPT_UINT);
			pCommand->GetParameter(&WeaponSet[1],2,MPT_UINT);
			pCommand->GetParameter(&WeaponSet[2],3,MPT_UINT);

			SetPlayerWeapons(uidPlayer,WeaponSet);
			return true;
		}break;
		*/
		default:
			break;
	}
	return false;
}

bool ItemsAlreadyEquipped(ZCharacter* player,const int WeaponSetArray[])
{

	if (player->m_Items.GetItem(MMCIP_MELEE)->GetDescID() == WeaponSetArray[0]
		&& player->m_Items.GetItem(MMCIP_PRIMARY)->GetDescID() == WeaponSetArray[1]
		&& player->m_Items.GetItem(MMCIP_SECONDARY)->GetDescID() == WeaponSetArray[2])
		return true;

	return false;
}

void ZRuleGunGame::SetPlayerWeapons(MUID& uidPlayer, const int WeaponSetArray[], bool isSuicide)
{
	ZCharacter* pChar = (ZCharacter*)ZGetCharacterManager()->Find(uidPlayer);
	if (pChar == nullptr)
	{
		mlog("Error, char is nullptr?\n");
		return;
	}

	if (isSuicide)
	{
		string message = pChar->GetCharName();
		message.append("has killed themselves and went back a level!");

		ZChatOutput(message.c_str());
	}

	//ugly logic yes, but it saves having to use another packet
	if (ItemsAlreadyEquipped(pChar, WeaponSetArray))
	{
		unsigned long nItemID[MMCIP_END];
		for (int i = 0; i < MMCIP_END; ++i)
		{
			nItemID[i] = pChar->m_Items.GetItem((MMatchCharItemParts)i)->GetDescID();
		}
		ZChangeCharParts(pChar->m_pVMesh, pChar->GetProperty()->nSex, pChar->GetProperty()->nHair, pChar->GetProperty()->nFace,
			nItemID);
		return;
	}

	pChar->m_Items.EquipItem(MMCIP_MELEE, WeaponSetArray[0]);
	pChar->m_Items.EquipItem(MMCIP_PRIMARY, WeaponSetArray[1]);
	pChar->m_Items.EquipItem(MMCIP_SECONDARY, WeaponSetArray[2]);
	
	pChar->m_Items.EquipItem(MMCIP_CUSTOM1, 0);
	pChar->m_Items.EquipItem(MMCIP_CUSTOM2, 0);

	//if (pChar->m_Items.GetItem(MMCIP_CUSTOM3) != nullptr)
	//{
	//	//TODO: report hacker
	//}

	MMatchItemDesc* pPrimary = MGetMatchItemDescMgr()->GetItemDesc(WeaponSetArray[1]);
	MMatchItemDesc* pSecondary = MGetMatchItemDescMgr()->GetItemDesc(WeaponSetArray[2]);

	if (pChar == ZGetGame()->m_pMyCharacter)
	{
		pChar->ChangeWeapon(pChar->GetItems()->GetSelectedWeaponParts() == MMCIP_MELEE ? MMCIP_PRIMARY : MMCIP_MELEE);
		pChar->m_Items.GetItem(MMCIP_PRIMARY)->SetBulletCurrMagazine(pPrimary->m_nMagazine.Ref());
		pChar->m_Items.GetItem(MMCIP_PRIMARY)->SetBulletSpare(pPrimary->m_nMaxBullet.Ref());
		pChar->m_Items.GetItem(MMCIP_SECONDARY)->SetBulletCurrMagazine(pSecondary->m_nMagazine.Ref());
		pChar->m_Items.GetItem(MMCIP_SECONDARY)->SetBulletSpare(pSecondary->m_nMaxBullet.Ref());

	}
	unsigned long nItemID[MMCIP_END];
	for (int i = 0; i < MMCIP_END; ++i)
	{
		nItemID[i] = pChar->m_Items.GetItem((MMatchCharItemParts)i)->GetDescID();
	}

	ZChangeCharParts(pChar->m_pVMesh,pChar->GetProperty()->nSex,pChar->GetProperty()->nHair,pChar->GetProperty()->nFace,
		nItemID);


	if (pChar->GetKils() == ZGetGame()->GetMatch()->GetRoundCount())
	{
		char buffer[64];
		sprintf_s(buffer, 64, "%s is on the last gun Level!", pChar->GetCharName());
		ZChatOutput(MCOLOR(ZCOLOR_CHAT_SYSTEM),buffer);
	}
}