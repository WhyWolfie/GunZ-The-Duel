#ifndef _MMATCHITEM_H
#define _MMATCHITEM_H

#include "winsock2.h"
#include "MXml.h"
#include "MUID.h"
#include "MSync.h"
#include "MBaseItem.h"
#include "MMemoryProxy.h"
#include <map>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

class MZFileSystem;
class MMatchCRC32XORCache;


/// 아이템 타입
enum MMatchItemType
{
	MMIT_MELEE = 0,
	MMIT_RANGE,
	MMIT_EQUIPMENT,
	MMIT_CUSTOM,
	MMIT_TICKET,
	MMIT_AVATAR,
	MMIT_COMMUNITY,
	MMIT_LONGBUFF,
	MMIT_END
};

/// 아이템 슬롯 타입
enum MMatchItemSlotType
{
	MMIST_NONE = 0,
	MMIST_MELEE,
	MMIST_RANGE,
	MMIST_CUSTOM,
	MMIST_HEAD,
	MMIST_CHEST,
	MMIST_HANDS,
	MMIST_LEGS,
	MMIST_FEET,
	MMIST_FINGER,
	MMIST_EXTRA,
	MMIST_AVATAR,
	MMIST_COMMUNITY,
	MMIST_LONGBUFF,
	MMIST_END
};

//핵 방지용.....
#define MMATCH_PARTS_ITEM		100
#define MMATCH_PARTS_PRIMARY	108
#define MMATCH_PARTS_SECONDARY	109
#define MMATCH_PARTS_CUSTOM1	110
#define MMATCH_PARTS_CUSTOM2	111

/// 장비부위 
// MMCIP_END의 값과 각 enum에 배정된 값이 바뀌면 리플레이 로딩에 영향을 미치므로 수정하려면 주의가 필요함..
// 특히 MMCIP_END는 MTD_CharInfo의 크기를 변화시키므로 리플레이 로딩 코드를 수정해주어야 합니다.
// 그리고 추가 할때는 절대로 맨 끝에만 해야합니다. 중간에 넣으면 MMatchCharItemParts 사용하는 커맨드 코드를 기존 리플레이용으로 사용할 수 없게 됨
enum MMatchCharItemParts
{
	MMCIP_HEAD		= 0,
	MMCIP_CHEST		= 1,
	MMCIP_HANDS  	= 2,
	MMCIP_LEGS		= 3,
	MMCIP_FEET		= 4,
	MMCIP_FINGERL	= 5,
	MMCIP_FINGERR	= 6,
	MMCIP_MELEE		= 7,
	MMCIP_PRIMARY	= 8,
	MMCIP_SECONDARY	= 9,
	MMCIP_CUSTOM1	= 10,	
	MMCIP_CUSTOM2	= 11,
	MMCIP_AVATAR	= 12,
	MMCIP_COMMUNITY1	= 13,
	MMCIP_COMMUNITY2	= 14,
	MMCIP_LONGBUFF1	= 15,
	MMCIP_LONGBUFF2	= 16,
	MMCIP_END
};

// 커스텀 아이템 타입
enum MMatchCustomItemType
{
	MMCIT_MED_KIT		= 0,
	MMCIT_REPAIR_KIT,
	MMCIT_BULLET_KIT,
	MMCIT_DYNAMITE,
	MMCIT_REMOTE_CHARGE,
	MMCIT_DEMOLITION_TOOLS,
	MMCIT_FLASH_BANG,
	MMCIT_FRAGMENTATION,
	MMCIT_SMOKE_GRENADE,
	MMCIT_TEARGAS_GRENADE,
	MMCIT_FOOD,

	MMCIT_ENCHANT_FIRE,			// 인챈트 아이템 - fire
	MMCIT_ENCHANT_COLD,			// 인챈트 아이템 - cold
	MMCIT_ENCHANT_LIGHTNING,	// 인챈트 아이템 - lightning
	MMCIT_ENCHANT_POISON,		// 인챈트 아이템 - poison

	MMCIT_POTION,				// 소모성 아이템 중 회복 계열 + 가속 포션

	MMCIT_END
};

enum MMatchMeleeItemType
{
	MIT_DAGGER			= 0,
	MIT_DUAL_DAGGER		= 1,
	MIT_KATANA			= 2,
	MIT_GREAT_SWORD		= 3,
	MIT_DOUBLE_KATANA	= 4,

	MIT_END
};

enum MMatchRangeItemType
{
	RIT_PISTOL			= 0,
	RIT_PISTOLx2		= 1,
	RIT_REVOLVER		= 2,
	RIT_REVOLVERx2		= 3,
	RIT_SMG				= 4,
	RIT_SMGx2			= 5,
	RIT_SHOTGUN			= 6,
	RIT_SAWED_SHOTGUN	= 7,
	RIT_RIFLE			= 8,
	RIT_MACHINEGUN		= 9,
	RIT_ROCKET			= 10,
	RIT_SNIFER			= 11,

	RIT_END
};

// Melee, Range, Custom을 합친 무기 타입 .. 한손 양손의 구분은 없다..
enum MMatchWeaponType
{
	MWT_NONE	= 0,

	// melee
	MWT_DAGGER,
	MWT_DUAL_DAGGER,
	MWT_KATANA,
	MWT_GREAT_SWORD,
	MWT_DOUBLE_KATANA,

	// range
	MWT_PISTOL,
	MWT_PISTOLx2,
	MWT_REVOLVER,
	MWT_REVOLVERx2,
	MWT_SMG,
	MWT_SMGx2,
	MWT_SHOTGUN,
	MWT_SAWED_SHOTGUN,
	MWT_RIFLE,
	MWT_MACHINEGUN,
	MWT_ROCKET,
	MWT_SNIFER,

	// custom
	MWT_MED_KIT,
	MWT_REPAIR_KIT,
	MWT_BULLET_KIT,
	MWT_FLASH_BANG,
	MWT_FRAGMENTATION,
	MWT_SMOKE_GRENADE,
	MWT_FOOD,
	MWT_SKILL,				// NPC용 - skill.xml에 기술되어 있는 걸로 공격한다.

	// custom - enchant
	MWT_ENCHANT_FIRE,			
	MWT_ENCHANT_COLD,
	MWT_ENCHANT_LIGHTNING,
	MWT_ENCHANT_POISON,

	// custom
	MWT_POTION,
	MWT_TRAP,
	MWT_DYNAMITYE,

	MWT_END
};

enum MMatchSpendType
{
	MMCT_NONE,
	MMCT_NORMAL,	// 일반 사용 아이템(다이나마이트. 물약)
	MMCT_LONGBUFF,	// 롱 버프 사용 아이템
	MMCT_SHORTBUFF,	// 숏 버프 사용 아이템
	MMCT_COMMUNITY,	// 커뮤니티 사용 아이템
	MMCT_END
};

enum MMatchDamageType
{
	MMDT_NORMAL,
	MMDT_FIRE,
	MMDT_COLD,
	MMDT_POISION,
	MMDT_LIGHTING,
	MMDT_HEAL,
	MMDT_REPAIR,
	MMDT_HASTE,
	MMDT_END
};

enum MMatchTicketType
{
	MMTT_NONE = 0,
	MMTT_ADMISSION,
	MMIT_CHANGEHEAD,

	MMTT_END,
};

enum MMatchItemEffectId
{
	// zitem.xml에서 아래 상수를 사용하므로 배정된 수치를 임의로 변경하면 안됩니다
	MMIEI_NONE = 0,
	
	// 의료캡슐, 의료앰플, 수리캡슐, 수리앰플 이펙트 구분
	MMIEI_POTION_HEAL_INSTANT		= 100,
	MMIEI_POTION_REPAIR_INSTANT		= 101,
	MMIEI_POTION_HEAL_OVERTIME		= 102,
	MMIEI_POTION_REPAIR_OVERTIME	= 103,

	// 가속캡슐
	MMIEI_POTION_HASTE				= 130,
};

struct MMatchItemEffectDesc
{
	unsigned long int	m_nID;
	char				m_szName[128];
	int					m_nArea;
	unsigned long int	m_nTime;
	int					m_nModHP;
	int					m_nModAP;
	int					m_nModMaxWT;
	int					m_nModSF;
	int					m_nModFR;
	int					m_nModCR;
	int					m_nModPR;
	int					m_nModLR;
	int					m_nResAP;
	int					m_nResFR;
	int					m_nResCR;
	int					m_nResPR;
	int					m_nResLR;
	int					m_nStun;
	int					m_nKnockBack;
	int					m_nSmoke;
	int					m_nFlash;
	int					m_nTear;
	int					m_nFlame;
};

enum MMatchItemBonusType
{
	MIBT_SOLO = 0,
	MIBT_TEAM = 1,
	MIBT_QUEST = 2
};

struct MMatchItemBonus
{
	float				m_fXP_SoloBonus;
	float				m_fXP_TeamBonus;
	float				m_fXP_QuestBonus;

	float				m_fBP_SoloBonus;
	float				m_fBP_TeamBonus;
	float				m_fBP_QuestBonus;
};

struct MMatchItemName
{
	char m_szItemName[128];
	char m_szMeshName[128];
};

struct MMatchAvatarMeshName
{
	char m_szHeadMeshName[128];
	char m_szChestMeshName[128];
	char m_szHandMeshName[128];
	char m_szLegsMeshName[128];
	char m_szFeetMeshName[128];	
};

struct MMatchItemDesc
{
	unsigned long int		m_nID;
//	char					m_szItemName[128];
	MProtectValue<MMatchItemName>* m_pMItemName;
	MProtectValue<int>		m_nTotalPoint;
	MProtectValue<MMatchWeaponType>	m_nWeaponType;
	MProtectValue<MMatchItemType>	m_nType;
	MProtectValue<int>		m_nResSex;
	MProtectValue<int>		m_nResLevel;
	MMatchItemSlotType		m_nSlot;
	
	MProtectValue<int>		m_nWeight;
	MProtectValue<int>		m_nBountyPrice;
	bool					m_bIsCashItem;	
	bool					m_bIsStaffItem;
	MProtectValue<int>		m_nDelay;
	MMatchItemEffectDesc*	m_pEffect;
	MMatchItemEffectId		m_nEffectId;
	MProtectValue<int>		m_nControllability;
	MProtectValue<int>		m_nMagazine;
	MProtectValue<int>		m_nMaxBullet;
	MProtectValue<int>		m_nReloadTime;
	bool					m_bSlugOutput;
	MProtectValue<int>		m_nGadgetID;
	MProtectValue<int>		m_nHP;
	MProtectValue<int>		m_nAP;
	MProtectValue<int>		m_nMaxWT;
	MProtectValue<int>		m_nSF;
	MProtectValue<int>		m_nFR;
	MProtectValue<int>		m_nCR;
	MProtectValue<int>		m_nPR;
	MProtectValue<int>		m_nLR;
	MProtectValue<int>		m_nLimitSpeed;
	MProtectValue<int>		m_nLimitJump;
	MProtectValue<int>		m_nLimitTumble;
	MProtectValue<int>		m_nLimitWall;
	MProtectValue<int>		m_nRange;		// melee무기 공격범위
	MProtectValue<int>		m_nAngle;		// melee무기 공격각도
	MProtectValue<int>		m_nEffectLevel;


	MProtectValue<int>				m_nDamage;			// 무기류의 공격력
	MProtectValue<int>				m_nItemPower;		// 소모성 아이템의 데미지 또는 회복량
	MProtectValue<int>				m_nDamageTime;		// 도트 형태의 데미지나 회복이 들어가는 시간(0일 경우, 한 방만 들어간다)
	MProtectValue<MMatchDamageType>	m_nDamageType;		// 소모성 아이템의 데미지 타입 (데미지 속성 혹은 회복 속성)
	MProtectValue<int>		m_nLifeTime;				// 작동 시간 (현재는 트랩의 작동시간에만 사용)

	char					m_szDesc[8192];	// 설명

	bool								m_bIsSpendableItem;
	MProtectValue<MMatchSpendType>		m_nSpendType;

	MProtectValue<MMatchAvatarMeshName>*		m_pAvatarMeshName;

	unsigned long int		m_nColor;
	int						m_nImageID;
	int						m_nBulletImageID;
	int						m_nMagazineImageID;
	char					m_szReloadSndName[256];
	char					m_szFireSndName[256];
	char					m_szDryfireSndName[256];
	char					m_szWeaponByFiber[256];		// melee 무기의 재질에 따른 소리

	MMatchItemBonus			m_Bonus;
	MMatchTicketType		m_TicketType;
	MProtectValue<int>		m_nMaxRentPeriod;	// 기간제 바운티 아이템의 최대 기간 정보 (날짜단위)

	bool					m_bIsEnableMoveToAccountItem;

	MMatchItemDesc();
	~MMatchItemDesc();

	int GetSellBountyValue(int nCnt = 1) { return int(m_nBountyPrice.Ref() * 0.25) * nCnt; }

    bool IsCashItem()		{ if ((m_bIsCashItem)) return true; return false; }
	bool IsStaffItem()		{ if (m_bIsStaffItem) return true; return false; }
	bool IsEnchantItem()	{ if (m_nWeaponType.Ref() >= MWT_ENCHANT_FIRE && m_nWeaponType.Ref() <= MWT_ENCHANT_POISON) return true; 
								return false; }
	bool IsUnLimitItem()		{ return RENT_PERIOD_UNLIMITED == m_nMaxRentPeriod.Ref(); }	
	bool IsSpendableItem()		{ return m_bIsSpendableItem; }


	void CacheCRC32( MMatchCRC32XORCache& crc );

	void ShiftFugitiveValues();

	void DumpBinary(FILE* fp);
	void LoadBinary(FILE* fp);
};


struct MMatchItemDescForDatabase
{
	unsigned long int m_nID;

	int m_nResSex;
	int	m_nResLevel;

	MMatchItemSlotType	m_nSlot;

	int m_nWeight;
	int m_nBountyPrice;
	int m_nDamage;
	int m_nDelay;

	int m_nControllability;
	int m_nMaxBullet;
	int m_nMagazine;
	int m_nReloadTime;	
	
	int m_nHP;
	int m_nAP;

	bool m_bIsCashItem;
	bool m_bIsStaffItem;
	bool m_bIsSpendableItem;
};

// 슬롯과 파츠가 적합한지 체크
bool IsSuitableItemSlot(MMatchItemSlotType nSlotType, MMatchCharItemParts nParts);
MMatchCharItemParts GetSuitableItemParts(MMatchItemSlotType nSlotType);
MMatchItemSlotType	GetSuitableItemSlot(MMatchCharItemParts nParts);
bool IsWeaponItemSlotType(MMatchItemSlotType nSlotType);
bool IsWeaponCharItemParts(MMatchCharItemParts nParts);

char* GetItemSlotTypeStr(MMatchItemSlotType nSlotType);
char* GetCharItemPartsStr(MMatchCharItemParts nParts);

// 무기타입 알아내기
MMatchWeaponType GetWeaponType(MMatchMeleeItemType nMeleeItemType);
MMatchWeaponType GetWeaponType(MMatchRangeItemType nRangeItemType);
MMatchWeaponType GetWeaponType(MMatchCustomItemType nCustomItemType);

// 인챈트아이템인지 확인
bool IsEnchantItem(MMatchItemDesc* pItemDesc);

/*
class MMatchItemEffectDescMgr : public map<int, MMatchItemEffectDesc*>
{
protected:
	void ParseEffect(MXmlElement& element);
public:
	MMatchItemEffectDescMgr();
	virtual ~MMatchItemEffectDescMgr();
	bool ReadXml(const char* szFileName);
	bool ReadXml(MZFileSystem* pFileSystem, const char* szFileName);
	void Clear();
	MMatchItemEffectDesc* GetEffectDesc(int nID);
	static MMatchItemEffectDescMgr* GetInstance();
};

inline MMatchItemEffectDescMgr* MGetMatchItemEffectDescMgr() { return MMatchItemEffectDescMgr::GetInstance(); }
*/

class MMatchItemDescMgr : public map<int, MMatchItemDesc*>
{
	unsigned long m_nChecksum;

	int m_nextItemIdToMemoryShift;
	
protected:
	bool ParseItem(MXmlElement& element);
public:
	MMatchItemDescMgr();
	virtual ~MMatchItemDescMgr();
	bool ReadXml(const char* szFileName);
	bool ReadXml(MZFileSystem* pFileSystem, const char* szFileName);
	void Clear();
	MMatchItemDesc* GetItemDesc(unsigned long int nID);
	static MMatchItemDescMgr* GetInstance();

	unsigned long GetChecksum() { return m_nChecksum; }

	void ShiftMemoryGradually();

	// 버프 관련된 Validation Check
	bool ValidateItemBuff();

	bool ReadCache();
	void WriteCache();
};
inline MMatchItemDescMgr* MGetMatchItemDescMgr() { return MMatchItemDescMgr::GetInstance(); }



typedef struct _DBCharItemCachingData
{
	bool	bNeedDBUpdate;
	int		nAddedItemCount;

	void Reset() { 
		nAddedItemCount = 0; 
		bNeedDBUpdate = false;
	}

	void IncCnt(int nVal) { 
		nAddedItemCount += nVal; 
		bNeedDBUpdate = true; 
	}

	void DecCnt(int nVal) {
		nAddedItemCount -= nVal; 
		bNeedDBUpdate = true; 
	}
	
	bool IsNeedDBUpdate() { return bNeedDBUpdate; }
} DBCharItemCachingData;


class MMatchItem : public MBaseItem
{
private:
protected:
	MUID				m_uidItem;	
	MMatchItemDesc*		m_pDesc;					///< 디스크립터
	bool				m_bEquiped;					///< 장비하고 있는지 여부
	unsigned long int	m_nRentItemRegTime;			///< 기간제 아이템일 경우 등록한 시간. 이 시간은 서버에 등록되는 시간임.

	// 상용하는 중간에 description이 NULL이 되는지 검사하기 위해서.
	unsigned int		m_nItemID;

	WORD				m_nCountOfNonDestroyItem;		///< 사용하면 수량은 줄지만 사라지지는 않는 아이템의 최대 사용 수량(ex 수리킷).
	WORD				m_nUseCountOfNonDestroyItem;	///< 사용하면 수량은 줄지만 사라지지는 않는 아이템의 사용된 수량(ex 수리킷).


	unsigned long int	m_nCIID;					///< DB에 들어가는 CIID

	DBCharItemCachingData m_CharItemCachingData;

protected:
	void SetDesc(MMatchItemDesc* pDesc) { m_pDesc = pDesc; }

public:
	MMatchItem();
	virtual ~MMatchItem();

	bool Create( const MUID& uid, MMatchItemDesc* pDesc, const WORD nCountOfNonDesctroyItem, int nCount = 1);
	void Destroy();

	MUID				GetUID() const								{ return m_uidItem; }
	unsigned long int	GetCIID() const								{ return m_nCIID; }
	unsigned long int	GetDescID() const;
	
	unsigned long int	GetRentItemRegTime() const					{ return m_nRentItemRegTime; }
	MMatchItemDesc*		GetDesc() const;
	MMatchItemType		GetItemType();
	
	void				SetCIID(unsigned long int nCIID)			{ m_nCIID = nCIID; }	
	void				SetEquiped(bool bIsEquiped)					{ m_bEquiped = bIsEquiped; }
	void				SetRentItemRegTime(unsigned long int nTime)	{ m_nRentItemRegTime = nTime; }	

	bool				IsEmpty()									{ return (((m_pDesc == NULL) || (m_nCount <= 0)) ? true : false); }
	bool				IsEquiped() const							{ return m_bEquiped; }			

	const WORD			GetCountOfNonDestroyItem()					{ return m_nCountOfNonDestroyItem; }
	const WORD			GetUseCountOfNonDestroyItem()				{ return m_nUseCountOfNonDestroyItem; }
	void				ResetUseCountOfNonDestroyItem()				{ m_nUseCountOfNonDestroyItem = 0; }
	void				IncreaseUseCountOfNonDestroyItem();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// DB Caching을 위하여 만들어진 멤버 함수들..	
	void				IncreaseCount(int nVal);
	void				DecreaseCount(int nVal);
	void				DecreaseCountWithCaching(int nVal);

	bool				IsNeedDBUpdate()							{ return m_CharItemCachingData.IsNeedDBUpdate(); }
	void				DBUpdateDone()								{ m_CharItemCachingData.Reset(); }	
	DBCharItemCachingData* GetItemCachingData()						{ return &m_CharItemCachingData; }
};


class MMatchItemMap;
class MMatchCharInfo;

typedef struct _EquipedParts
{
	MUID	uidParts;
	int		nItemCount;
} EquipedParts;

/// 장비하고있는 아이템
class MMatchEquipedItem
{
protected:
	// MMatchItem*		m_pParts[MMCIP_END];
	//EquipedParts	m_Parts[MMCIP_END];
	MUID			m_uidParts[ MMCIP_END ];	
	
	MMatchCharInfo*	m_pOwner;

public:
	MMatchEquipedItem() 
	{ 
		// memset(m_pParts, 0, sizeof(m_pParts)); 
		memset( m_uidParts, 0, sizeof(m_uidParts) );
		// memset(m_Parts, 0, sizeof(EquipedParts) * MMCIP_END);


		m_pOwner = NULL;
	}

	virtual ~MMatchEquipedItem() 
	{ 
		m_pOwner = NULL;
	}
public:
	// bool SetItem(MMatchCharItemParts parts, MMatchItem* pMatchItem);
	bool SetItem( MMatchCharItemParts parts, const MUID& uidItem, MMatchItem* pItem );

	MMatchItem* GetItem(MMatchCharItemParts parts); //  { return m_pParts[parts]; }
	void Remove(MMatchCharItemParts parts);
	void Remove(const MUID& uidParts);
	// bool IsEmpty(MMatchCharItemParts parts) { if (m_pParts[parts] != NULL) return false; return true; }
	bool IsEmpty(MMatchCharItemParts parts); //  { if (m_pParts[parts] != NULL) return false; return true; }
	void GetTotalWeight(int* poutWeight, int* poutMaxWeight);
	// bool IsEquipedItem(MMatchItem* pCheckItem, MMatchCharItemParts& outParts); // 해당 아이템이 장비중인지 체크
	bool IsEquipedItem(const MUID& uidItem, MMatchCharItemParts& outParts); // 해당 아이템이 장비중인지 체크
	void Clear();
	void SetOwner( MMatchCharInfo* pOwner ) { _ASSERT( NULL != pOwner ); m_pOwner = pOwner; }


private :
	// MMatchItem* GetMyItem( MMatchCharItemParts parts );
};

/// 캐릭터가 갖고 있는 아이템들
class MMatchItemMap : public map<MUID, MMatchItem*>
{
private:
protected:
	static MUID				m_uidGenerate;
	static MCriticalSection	m_csUIDGenerateLock;
	bool					m_bDoneDbAccess;		// 디비에서 정보를 가져왔었는지 여부

	/// 기간제 아이템이 하나라도 있는지 여부
	/// 주의 - 기간제 아이템이 하나라도 없더라도 true일 수도 있다. 
	bool					m_bHasRentItem;			

public:
	MMatchItemMap();
	virtual ~MMatchItemMap();
	bool IsEmpty() const { return empty(); }
	int GetCount() const { return (int)size(); }
	virtual bool CreateItem( const MUID& uid
		, int nCIID
		, int nItemDescID
		, bool bRentItem = false
		, DWORD dwRentMinutePeriodRemainder = RENT_MINUTE_PERIOD_UNLIMITED
		, const WORD wRentHourPeriod = RENT_PERIOD_UNLIMITED
		, int nCount = 1);
	bool			RemoveItem(const MUID& uidItem);

	virtual void	Clear();
	MMatchItem*		GetItem(const MUID& uidItem) const;
	MMatchItem*		GetItemByItemID(const DWORD dwItemID) const;		//< 여러개의 ItemID가 있어도, 1개만 돌려준다(Spendable 때문에 구현)
																		//< 좀 모호한 감이 있지만, 그래도 사용하자..

	MMatchItem*		GetItemByCIID(const DWORD dwCIID) const;


	bool			IsDoneDbAccess() const			{ return m_bDoneDbAccess; }
	void			SetDbAccess(bool bVal)			{ m_bDoneDbAccess = bVal; }
	bool			HasRentItem() const				{ return m_bHasRentItem; }
	const bool		IsHave( const DWORD dwItemID ) const;

	int	 GetItemCount(const MUID& uidItem);

public:
	static MUID UseUID() {
		m_csUIDGenerateLock.Lock();
			m_uidGenerate.Increase();	
		m_csUIDGenerateLock.Unlock();
		return m_uidGenerate;
	}
};


bool IsExpiredRentItem( const MMatchItem* pMItem, const DWORD dwTick );

#include "../StringLiteral/cxr_MMatchItem.h"

#endif