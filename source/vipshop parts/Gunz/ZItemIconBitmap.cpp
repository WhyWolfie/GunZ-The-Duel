#include "stdafx.h"
#include "ZItemIconBitmap.h"
#include "MBitmap.h"
#include "MMatchItem.h"


// 파일 이름은 그냥 하드코딩..-_-;
MBitmap* GetItemIconBitmap(MMatchItemDesc* pItemDesc)
{
	if (pItemDesc == NULL) return false;

	// 아이템 썸네일 파일을 먼저 찾아봅니다. 만약 없으면 기존대로 종류별 아이콘을 로딩합니다.
	MBitmap* pBitmapThumbnail = GetItemThumbnailBitmap(pItemDesc);
	if (pBitmapThumbnail)
		return pBitmapThumbnail;

	char szFileName[64] = "";

	switch (pItemDesc->m_nSlot)
	{
	case MMIST_NONE:
		// 입장권
		if ( pItemDesc->m_nType.Ref() == MMIT_TICKET)
			strcpy(szFileName, "slot_icon_ticket");
		break;

	case MMIST_CUSTOM:
		{
			MMatchWeaponType nWeaponType = pItemDesc->m_nWeaponType.Ref();

			switch (nWeaponType)
			{
			case MWT_FRAGMENTATION:		strcpy(szFileName, "slot_icon_grenade");		break;
			case MWT_FLASH_BANG:
			case MWT_SMOKE_GRENADE:		strcpy(szFileName, "slot_icon_flashbang");		break;
			case MWT_MED_KIT:			strcpy(szFileName, "slot_icon_medikit");		break;				
			case MWT_FOOD:				strcpy(szFileName, "slot_icon_food");			break;
			case MWT_REPAIR_KIT:		strcpy(szFileName, "slot_icon_repairkit");		break;
			case MWT_BULLET_KIT:		strcpy(szFileName, "slot_icon_magazine");		break;
			case MWT_ENCHANT_FIRE:		strcpy(szFileName, "slot_icon_en_fire");		break;
			case MWT_ENCHANT_COLD:		strcpy(szFileName, "slot_icon_en_cold");		break;
			case MWT_ENCHANT_LIGHTNING:	strcpy(szFileName, "slot_icon_en_lightning");	break;
			case MWT_ENCHANT_POISON:	strcpy(szFileName, "slot_icon_en_poison");		break;
			case MWT_POTION:			strcpy(szFileName, GetItemIconBitmap_Potion(pItemDesc));	break;
			case MWT_TRAP:				strcpy(szFileName, GetItemIconBitmap_Trap(pItemDesc));		break;
			case MWT_DYNAMITYE:			strcpy(szFileName, "slot_icon_exgrenade");		break;

			default:
				_ASSERT(0);
				break;
			}
		}
		break;

	case MMIST_HEAD:	strcpy(szFileName, "slot_icon_head");	break;
	case MMIST_CHEST:	strcpy(szFileName, "slot_icon_chest");	break;
	case MMIST_HANDS:	strcpy(szFileName, "slot_icon_hands");	break;
	case MMIST_LEGS:	strcpy(szFileName, "slot_icon_legs");	break;
	case MMIST_FEET:	strcpy(szFileName, "slot_icon_feet");	break;
	case MMIST_FINGER:
		{
			if (pItemDesc->IsCashItem()) {
				strcpy(szFileName, "slot_icon_ringG");	break;
			} else {
				strcpy(szFileName, "slot_icon_ringS");	break;
			}
		}
	case MMIST_MELEE:
	case MMIST_RANGE:
		{
			MMatchWeaponType type = pItemDesc->m_nWeaponType.Ref();
			{
				switch (type) {

				case MWT_DAGGER:		strcpy(szFileName, "slot_icon_dagger"); break;
				case MWT_DUAL_DAGGER:	strcpy(szFileName, "slot_icon_D_dagger"); break;
				case MWT_KATANA:		strcpy(szFileName, "slot_icon_katana"); break;
				case MWT_GREAT_SWORD:	strcpy(szFileName, "slot_icon_sword"); break;
				case MWT_DOUBLE_KATANA:	strcpy(szFileName, "slot_icon_blade"); break;

				case MWT_PISTOL:		strcpy(szFileName, "slot_icon_pistol"); break;
				case MWT_PISTOLx2:		strcpy(szFileName, "slot_icon_D_pistol"); break;
				case MWT_REVOLVER:		strcpy(szFileName, "slot_icon_pistol"); break;
				case MWT_REVOLVERx2:	strcpy(szFileName, "slot_icon_D_pistol"); break;
				case MWT_SMG:			strcpy(szFileName, "slot_icon_smg"); break;
				case MWT_SMGx2:			strcpy(szFileName, "slot_icon_D_smg"); break;
				case MWT_SHOTGUN:		strcpy(szFileName, "slot_icon_shotgun"); break;
				case MWT_SAWED_SHOTGUN:	strcpy(szFileName, "slot_icon_shotgun"); break;
				case MWT_RIFLE:			strcpy(szFileName, "slot_icon_rifle"); break;
				case MWT_SNIFER:		strcpy(szFileName, "slot_icon_rifle"); break;
				case MWT_MACHINEGUN:	strcpy(szFileName, "slot_icon_machinegun"); break;
				case MWT_ROCKET:		strcpy(szFileName, "slot_icon_rocket"); break;
				}
			}
		}
		break;

		// TodoH(상) - 아바타 아이템의 슬롯 리소스가 필요
	case MMIST_AVATAR:	strcpy(szFileName, "slot_icon_ringS");	break;

		// TodoH(상) - 커뮤니티, 롱버프 아이템의 슬롯 리소스가 필요
	case MMIST_COMMUNITY:
	case MMIST_LONGBUFF:
		strcpy(szFileName, "slot_icon_ticket");
		break;

	default:
		break;
	}

	strcat(szFileName, ".tga");	

	MBitmap *pBitmap = MBitmapManager::Get(szFileName);
	_ASSERT(pBitmap!=NULL);
	return pBitmap;
}

const char* GetItemIconBitmap_Potion(MMatchItemDesc* pDesc)
{
	if (!pDesc) return "";

	switch (pDesc->m_nEffectId)
	{
	case MMIEI_POTION_HEAL_INSTANT:		return "slot_icon_hp_capsule";
	case MMIEI_POTION_REPAIR_INSTANT:	return "slot_icon_ap_capsule";
	case MMIEI_POTION_HEAL_OVERTIME:	return "slot_icon_hp_ampulla";
	case MMIEI_POTION_REPAIR_OVERTIME:	return "slot_icon_ap_ampulla";
	case MMIEI_POTION_HASTE:			return "slot_icon_haste_ampulla";
	default:
		_ASSERT(0);
	}
	return "";
}

const char* GetItemIconBitmap_Trap(MMatchItemDesc* pDesc)
{
	if (!pDesc) return "";

	switch (pDesc->m_nDamageType.Ref())
	{
	case MMDT_FIRE:		return "slot_icon_trap_fire";
	case MMDT_COLD:		return "slot_icon_trap_cold";
	default:
		{
			MMatchDamageType type = pDesc->m_nDamageType.Ref();
			_ASSERT(0);
		}
	}
	return "";
}

MBitmap* GetItemThumbnailBitmap(MMatchItemDesc* pDesc)
{
	// 아이템의 썸네일 파일을 로딩
	if (!pDesc) return NULL;

	MBitmap* pBitmap = ZGetGameInterface()->GetItemThumbnailMgr()->Get(pDesc->m_nID);
	if (pBitmap) return pBitmap;

	char szAliasName[32];
	char szFilePath[256];
	sprintf(szAliasName, "%d", pDesc->m_nID);
	sprintf(szFilePath, "interface/loadable/itemicon%d.dds", pDesc->m_nID);
	MBitmapR2* pNewBitmap = new MBitmapR2;
	if (!pNewBitmap->Create(szAliasName, RGetDevice(), szFilePath)) {
		delete pNewBitmap;
		return NULL;
	}

	ZGetGameInterface()->GetItemThumbnailMgr()->Add(pDesc->m_nID, pNewBitmap);
	return pNewBitmap;
}