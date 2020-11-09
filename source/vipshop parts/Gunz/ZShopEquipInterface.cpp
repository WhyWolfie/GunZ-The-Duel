#include "stdafx.h"
#include "ZShopEquipInterface.h"
#include "ZShopEquipListbox.h"
#include "ZConfiguration.h"
#include "ZShop.h"
#include "ZItemSlotView.h"

static ZIDLResource* GetIDLResource() {
	return ZGetGameInterface()->GetIDLResource();
}

// 버튼에 마우스오버할때 나타나는 초록빛이 사라지지 않아서 이렇게 해둔것 같다. 이코드가 여기저기 많아서 함수로 만들어버렸음
void WidgetHideDisableShow(const char* szWidget)
{
	MWidget* pWidget = GetIDLResource()->FindWidget( szWidget);
	if ( pWidget)
	{
		pWidget->Show( false);
		pWidget->Enable( false);
		pWidget->Show( true);
	}
}
// 이렇게 된 곳도 있는데 이건 왜 숨기기만 하는지 모르겠다 -_-;
void WidgetHideDisable(const char* szWidget)
{
	MWidget* pWidget = GetIDLResource()->FindWidget( szWidget);
	if ( pWidget)
	{
		pWidget->Show( false);
		pWidget->Enable( false);
		//pWidget->Show( true);
	}
}

void WidgetEnableShow(const char* szWidget, bool bEnable, bool bShow)
{
	MWidget* pWidget = GetIDLResource()->FindWidget( szWidget);
	if (pWidget)
	{
		pWidget->Enable(bEnable);
		pWidget->Show(bShow);
	}
}


//##################################################################################################

ZShopEquipInterface::ZShopEquipInterface()
{
	m_nShopTabNum = 0;
	m_nEquipTabNum = 0;

	m_idxArmorWeaponTab = 1;

	m_pItemDescriptionClient = 0;

	m_pItemCountDlg = new ZItemCountDlg;
	m_pSimpleConfirmDlg = new ZSimpleConfirmDlg;
	m_pSellCashItemConfirmDlg = new ZSellCashItemConfirmDlg;
};

ZShopEquipInterface::~ZShopEquipInterface()
{
	delete m_pItemCountDlg;
	delete m_pSimpleConfirmDlg;
	delete m_pSellCashItemConfirmDlg;
}

void ZShopEquipInterface::ConfirmBuySimple()
{

}

ZShopEquipListItem* ZShopEquipInterface::GetListCurSelItem(const char* szListWidget)
{
	ZShopEquipListbox* pListbox = (ZShopEquipListbox*)ZGetGameInterface()->GetIDLResource()->FindWidget( szListWidget);
	if (pListbox)
		return (ZShopEquipListItem*)pListbox->GetSelItem();
	return NULL;
}

void ZShopEquipInterface::OnSellButton(void)
{
	static unsigned long int st_LastRequestTime = 0;	///< 막 누르는 것 방지
	unsigned long int nNowTime = timeGetTime();
	if ((nNowTime - st_LastRequestTime) < 1000) return;

	st_LastRequestTime = nNowTime;

	ZShopEquipListItem* pListItem = (ZShopEquipListItem*)GetListCurSelItem("MyAllEquipmentList");
	if (!pListItem) {
		ZApplication::GetGameInterface()->ShowErrorMessage( MERR_NO_SELITEM ); 
		return;
	}

	if (pListItem->GetItemData()->GetHandleSell())
		pListItem->GetItemData()->GetHandleSell()->Sell();
}

void ZShopEquipInterface::OnBuyButton(void)
{
	static unsigned long int st_LastRequestTime = 0;	///< 막 누르는 것 방지
	unsigned long int nNowTime = timeGetTime();
	if ((nNowTime - st_LastRequestTime) < 1000) return;

	st_LastRequestTime = nNowTime;

	ZShopEquipListItem* pListItem = (ZShopEquipListItem*)GetListCurSelItem("AllEquipmentList");
	if (!pListItem) {
		ZApplication::GetGameInterface()->ShowErrorMessage( MERR_NO_SELITEM ); 
		return;
	}

	if (pListItem->GetItemData()->GetHandlePurchase())
		pListItem->GetItemData()->GetHandlePurchase()->Buy();
}

// 아이템의 슬롯 정보에 따라 착용할 파츠를 골라준다
// 예를 들어 custom1에 이미 장착된 경우 custom2가 비어있으면 custom2를 골라주고, 둘다 장착중이면 custom1을 골라주는 식
MMatchCharItemParts ZShopEquipInterface::RecommendEquipParts(MMatchItemSlotType slot)
{
	MMatchCharItemParts parts = MMCIP_END;

	if (slot == MMIST_RANGE)
	{
		if (ZGetMyInfo()->GetItemList()->GetEquipedItemID(MMCIP_PRIMARY) == 0)
		{
			parts = MMCIP_PRIMARY;
		}
		else if (ZGetMyInfo()->GetItemList()->GetEquipedItemID(MMCIP_SECONDARY) == 0)
		{
			parts = MMCIP_SECONDARY;
		}
	}
	else if (slot == MMIST_CUSTOM)
	{
		if (ZGetMyInfo()->GetItemList()->GetEquipedItemID(MMCIP_CUSTOM1) == 0)
		{
			parts = MMCIP_CUSTOM1;
		}
		else if (ZGetMyInfo()->GetItemList()->GetEquipedItemID(MMCIP_CUSTOM2) == 0)
		{
			parts = MMCIP_CUSTOM2;
		}
	}
	else if (slot == MMIST_FINGER)
	{
		if (ZGetMyInfo()->GetItemList()->GetEquipedItemID(MMCIP_FINGERL) == 0)
		{
			parts = MMCIP_FINGERL;
		}
		else if (ZGetMyInfo()->GetItemList()->GetEquipedItemID(MMCIP_FINGERR) == 0)
		{
			parts = MMCIP_FINGERR;
		}
	}
	else if (slot == MMIST_AVATAR)
	{
		if (ZGetMyInfo()->GetItemList()->GetEquipedItemID(MMCIP_AVATAR) == 0)
		{
			parts = MMCIP_AVATAR;
		}
	}
	else if (slot == MMIST_COMMUNITY)
	{
		if (ZGetMyInfo()->GetItemList()->GetEquipedItemID(MMCIP_COMMUNITY1) == 0)
		{
			parts = MMCIP_COMMUNITY1;
		}
		else if (ZGetMyInfo()->GetItemList()->GetEquipedItemID(MMCIP_COMMUNITY2) == 0)
		{
			parts = MMCIP_COMMUNITY2;
		}

	}
	else if (slot == MMIST_LONGBUFF)
	{
		if (ZGetMyInfo()->GetItemList()->GetEquipedItemID(MMCIP_LONGBUFF1) == 0)
		{
			parts = MMCIP_LONGBUFF1;
		}
		else if (ZGetMyInfo()->GetItemList()->GetEquipedItemID(MMCIP_LONGBUFF2) == 0)
		{
			parts = MMCIP_LONGBUFF2;
		}
	}

	if (parts == MMCIP_END)
	{
		parts = GetSuitableItemParts(slot);
	}

	return parts;
}

bool ZShopEquipInterface::Equip(void)
{
	static unsigned long int st_LastRequestTime = 0;	///< 막 누르는 것 방지
	unsigned long int nNowTime = timeGetTime();
	if ((nNowTime - st_LastRequestTime) < 1000) return false;

	st_LastRequestTime = nNowTime;

	ZShopEquipListItem* pListItem = GetListCurSelItem("EquipmentList");
	if (!pListItem) 
	{
		ZApplication::GetGameInterface()->ShowErrorMessage( MERR_NO_SELITEM );
		return false;
	}

	// 갬블 아이템
	if (ZSEIT_GAMBLE == pListItem->GetItemData()->GetType())
	{
		ZShopEquipItem_Gamble* pWrapperGItem = (ZShopEquipItem_Gamble*)pListItem->GetItemData();
		const ZGambleItemDefine* pGItemDesc = pWrapperGItem->GetDesc();
		if (pGItemDesc)
		{
			// 이번에 캐시용 겜블아이템 추가로 수정
			// 기존 일본 요청으로 퀘스트용 겜블아이템을 추가했었음 (1000100~1000199사이)
			// 퀘스트용 겜블아이템은 1000100에서 1000200로 제한한다
			if( ZGetGameClient()->GetServerMode() != MSM_TEST && 1000100 <= pGItemDesc->GetGambleItemID()  && pGItemDesc->GetGambleItemID() < 1000200)
			{
				ZApplication::GetGameInterface()->ShowErrorMessage( MERR_CANNOT_CAHNGE_THIS_ITEM );
			}
			else
			{
				if (!pWrapperGItem->GetHandleSell()) { _ASSERT(0); return false; }
				ZPostRequestGamble( pWrapperGItem->GetHandleSell()->GetItemUID() );
				ZPostRequestCharacterItemList( ZGetGameClient()->GetPlayerUID() );
			}
		}
	}

	// 일반 아이템
	if (ZSEIT_MATCH != pListItem->GetItemData()->GetType())
	{
		return false;
	}

	ZShopEquipItem_Match* pWrappedZItem = (ZShopEquipItem_Match*)pListItem->GetItemData();
	if (!pWrappedZItem->GetHandleSell()) { _ASSERT(0); return false; }

	MUID uidItem = pWrappedZItem->GetHandleSell()->GetItemUID();
	MMatchItemDesc* pItemDesc = MGetMatchItemDescMgr()->GetItemDesc(ZGetMyInfo()->GetItemList()->GetItemID(uidItem));
	if (!pItemDesc) return false;

	if (pItemDesc->m_nSlot == MMIST_NONE)
		return false;

	MMatchCharItemParts parts = RecommendEquipParts(pItemDesc->m_nSlot);
	if (parts == MMCIP_END)
		return false;

	WidgetHideDisableShow("Equip");
	WidgetHideDisableShow("SendAccountItemBtn");

	SetKindableItem( MMIST_NONE);

	return Equip(parts, uidItem);
}

bool ZShopEquipInterface::Equip(MMatchCharItemParts parts, MUID& uidItem)
{
	ZPostRequestEquipItem(ZGetGameClient()->GetPlayerUID(), uidItem, parts);
	// 서버에서 자동으로 보내준다.
	// ZPostRequestCharacterItemList(ZGetGameClient()->GetPlayerUID());
	return true;
}

// 장비 아이콘 드래그 앤 드롭 상태일때 장착 가능한 ItemSlot 뷰 설정하기
void ZShopEquipInterface::SetKindableItem( MMatchItemSlotType nSlotType)
{
	ZItemSlotView* itemSlot;
	for ( int i = 0;  i < MMCIP_END;  i++)
	{
		itemSlot = (ZItemSlotView*)GetIDLResource()->FindWidget( GetItemSlotName( "Equip", i));
		if ( itemSlot)
		{
			bool bKindable = IsKindableItem(itemSlot->GetParts(), nSlotType);
			itemSlot->SetKindable( bKindable);
		}
	}
}

bool ZShopEquipInterface::IsKindableItem(MMatchCharItemParts nParts, MMatchItemSlotType nSlotType)
{
	switch (nSlotType)
	{
	case MMIST_MELEE :
		if ( nParts == MMCIP_MELEE)
			return true;
		break;
	case MMIST_RANGE :
		if ( (nParts == MMCIP_PRIMARY) || (nParts == MMCIP_SECONDARY))
			return true;
		break;
	case MMIST_CUSTOM :
		if ( (nParts == MMCIP_CUSTOM1) || (nParts == MMCIP_CUSTOM2) )
			return true;
		break;
	case MMIST_HEAD :
		if ( nParts == MMCIP_HEAD)
			return true;
		break;
	case MMIST_CHEST :
		if ( nParts == MMCIP_CHEST)
			return true;
		break;
	case MMIST_HANDS :
		if ( nParts == MMCIP_HANDS)
			return true;
		break;
	case MMIST_LEGS :
		if ( nParts == MMCIP_LEGS)
			return true;
		break;
	case MMIST_FEET :
		if ( nParts == MMCIP_FEET)
			return true;
		break;
	case MMIST_FINGER :
		if ( (nParts == MMCIP_FINGERL) || (nParts == MMCIP_FINGERR))
			return true;
		break;
	case MMIST_AVATAR :
		if ( nParts == MMCIP_AVATAR)
			return true;
		break;
	case MMIST_COMMUNITY :
		if ( (nParts == MMCIP_COMMUNITY1) || (nParts == MMCIP_COMMUNITY2) )
			return true;
		break;
	case MMIST_LONGBUFF :
		if ( (nParts == MMCIP_LONGBUFF1) || (nParts == MMCIP_LONGBUFF2) )
			return true;
		break;
	}
	return false;
}

int ZShopEquipInterface::_CheckRestrictBringAccountItem()
{
	// Return -1 : Error
	//		  0 : No restriction
	//		  1 : Sex restricted
	//		  2 : Level restricted

	ZShopEquipListItem* pListItem = GetListCurSelItem("AccountItemList");
	if (pListItem == NULL) return -1;

	if (pListItem->GetItemData()->GetHandleBringAccount())
	{
		int nAIID = pListItem->GetItemData()->GetHandleBringAccount()->GetAIID();
		ZMyItemNode* pMyItemNode = ZGetMyInfo()->GetItemList()->GetAccountItemByAIID(nAIID);
		
		if (!pMyItemNode) return 0;

		unsigned long nItemID = pMyItemNode->GetItemID();
		MMatchItemDesc* pItemDesc = MGetMatchItemDescMgr()->GetItemDesc(nItemID);
		if (!pItemDesc)
		{
			if( ZGetGambleItemDefineMgr().GetGambleItemDefine(nItemID) ) {
				return 0;	// 겜블 아이템은 존재만 확인하면 된다.
			} else {
				return -1;				
			}
		}

		if ((pItemDesc->m_nResSex.Ref() != -1) && (ZGetMyInfo()->GetSex() != pItemDesc->m_nResSex.Ref()))
			return 1;	// Sex restricted
		if (ZGetMyInfo()->GetLevel() < pItemDesc->m_nResLevel.Ref())
			return 2;	// Level restricted

	}

	return 0;	// No Restriction
}

bool ZShopEquipInterface::CheckRestrictBringAccountItem()
{
	int nResult = _CheckRestrictBringAccountItem();
	if (nResult == 0 || nResult == 2)	// Restriction Passed
		return true;

	if (nResult == -1)
		ZGetGameInterface()->ShowErrorMessage(  MERR_NO_SELITEM );

	else if (nResult == 1)	// Sex Restrict
		ZGetGameInterface()->ShowErrorMessage( MERR_BRING_ACCOUNTITEM_BECAUSEOF_SEX );

	else
		_ASSERT(FALSE);	// Unknown Restriction

	return false;
}

void ZShopEquipInterface::OnSendAccountButton()
{
	static unsigned long int st_LastRequestTime = 0;	///< 막 누르는 것 방지
	unsigned long int nNowTime = timeGetTime();
	if ((nNowTime - st_LastRequestTime) < 1000) return;

	st_LastRequestTime = nNowTime;

	ZShopEquipListItem* pListItem = GetListCurSelItem("EquipmentList");
	if (!pListItem)
	{
		ZApplication::GetGameInterface()->ShowErrorMessage( MERR_NO_SELITEM ); 
		return;
	}

	if (pListItem->GetItemData()->GetHandleSendAccount())
		pListItem->GetItemData()->GetHandleSendAccount()->Send();

	SetKindableItem(MMIST_NONE);

	WidgetHideDisableShow("SendAccountItemBtn");
	WidgetHideDisableShow("Equip");
}

void ZShopEquipInterface::OnBringAccountButton()
{
	static unsigned long int st_LastRequestTime = 0;	///< 막 누르는 것 방지
	unsigned long int nNowTime = timeGetTime();
	if ((nNowTime - st_LastRequestTime) < 1000) return;

	st_LastRequestTime = nNowTime;

	ZShopEquipListItem* pListItem = GetListCurSelItem("AccountItemList");
	if (!pListItem)
	{
		ZApplication::GetGameInterface()->ShowErrorMessage( MERR_NO_SELITEM ); 
		return;
	}

	if (pListItem->GetItemData()->GetHandleBringAccount())
		pListItem->GetItemData()->GetHandleBringAccount()->Bring();

	SetKindableItem(MMIST_NONE);

	WidgetHideDisableShow("BringAccountItemBtn");
}

void ZShopEquipInterface::SelectShopTab(int nTabIndex)
{
	if (nTabIndex == -1)
		nTabIndex = m_nShopTabNum;

	ZIDLResource* pResource = GetIDLResource();

	// 프리미엄 샵 - 설정되는 국가대로 하나씩 지워나간다
#ifndef _DEBUG
#if defined(LOCALE_BRAZIL) || defined(LOCALE_INDIA) || defined(LOCALE_US) || defined(LOCALE_JAPAN) || defined(LOCALE_KOREA) || defined(LOCALE_NHNUSA)
	{
		if ( nTabIndex == 2)
			return;
	}
#endif
#endif

	MWidget* pWidget = pResource->FindWidget("AllEquipmentList");
	if (pWidget != NULL) pWidget->Show(nTabIndex==0 ? true : false);
	pWidget = pResource->FindWidget("MyAllEquipmentList");
	if (pWidget != NULL) pWidget->Show(nTabIndex==1 ? true : false);
	pWidget = pResource->FindWidget("CashEquipmentList");
	if (pWidget != NULL) pWidget->Show(nTabIndex==2 ? true : false);


	// Set filter
	MComboBox* pComboBox = (MComboBox*)pResource->FindWidget( "Shop_AllEquipmentFilter");
	if(pComboBox) {
		int sel = pComboBox->GetSelIndex();

		ZMyItemList* pil = ZGetMyInfo()->GetItemList();
		if ( pil) {
			pil->m_ListFilter = sel;
			pil->Serialize();
		}
	}

	// 버튼 설정
	MButton* pButton = (MButton*)pResource->FindWidget( "BuyConfirmCaller");
	if ( pButton)
	{
		pButton->Show( false);
		pButton->Enable( false);
	}
	pButton = (MButton*)pResource->FindWidget( "SellConfirmCaller");
	if ( pButton)
	{
		pButton->Show( false);
		pButton->Enable( false);
	}

	if ( nTabIndex == 0)
	{
		pButton = (MButton*)pResource->FindWidget( "BuyConfirmCaller");
		if ( pButton) pButton->Show( true);
	}
	else if ( nTabIndex == 1)
	{
		pButton = (MButton*)pResource->FindWidget( "SellConfirmCaller");
		if ( pButton)
			pButton->Show( true);
	}
	/* 수년전 만들다만 프리미엄 탭(캐쉬템) 코드임. 제거 예정
	else if ( nTabIndex == 2)
	{
		pButton = (MButton*)pResource->FindWidget( "BuyCashConfirmCaller");
		if ( pButton)
			pButton->Show( true);
	}
	*/


	pButton = (MButton*)pResource->FindWidget("AllEquipmentListCaller");
	if (pButton != NULL)
		pButton->Show(nTabIndex!=0 ? true : false);
	pButton = (MButton*)pResource->FindWidget("MyAllEquipmentListCaller");
	if (pButton != NULL)
		pButton->Show(nTabIndex!=1 ? true : false);
	pButton = (MButton*)pResource->FindWidget("CashEquipmentListCaller");
	if (pButton != NULL)
		pButton->Show(nTabIndex!=2 ? true : false);


	// 구입, 판매 라벨
	MPicture* pPicture;
	MBitmap* pBitmap;
	pPicture = (MPicture*)pResource->FindWidget("Shop_FrameTabLabel1");
	if ( pPicture)
		pPicture->Show(nTabIndex==0 ? true : false);
	pPicture = (MPicture*)pResource->FindWidget("Shop_FrameTabLabel2");
	if ( pPicture)
		pPicture->Show(nTabIndex==1 ? true : false);
	pPicture = (MPicture*)pResource->FindWidget("Shop_FrameTabLabel3");
	if ( pPicture)
		pPicture->Show(nTabIndex==2 ? true : false);


	// 프레임 탭
	pPicture = (MPicture*)pResource->FindWidget("Shop_TabLabel");
	if ( pPicture)
	{
/*		if ( nTabIndex == 0)
			pBitmap = MBitmapManager::Get( "framepaneltab1.tga");
		else if ( nTabIndex == 1)
			pBitmap = MBitmapManager::Get( "framepaneltab2.tga");
		else if ( nTabIndex == 2)
			pBitmap = MBitmapManager::Get( "framepaneltab3.tga");
*/
if ( nTabIndex == 0)
			pBitmap = MBitmapManager::Get( "framepaneltab1.png");
		else if ( nTabIndex == 1)
			pBitmap = MBitmapManager::Get( "framepaneltab2.png");
		else if ( nTabIndex == 2)
			pBitmap = MBitmapManager::Get( "framepaneltab3.png");


		if ( pBitmap)
			pPicture->SetBitmap( pBitmap);
	}


	// 프리미엄 샵 - 설정되는 국가대로 하나씩 지워나간다
#ifndef _DEBUG
#if defined(LOCALE_BRAZIL) || defined(LOCALE_INDIA) || defined(LOCALE_US) || defined(LOCALE_JAPAN) || defined(LOCALE_KOREA) || defined(LOCALE_NHNUSA)
	{
		pWidget = pResource->FindWidget( "Shop_TabLabelBg");
		if ( pWidget)  pWidget->Show( false);

		pWidget = pResource->FindWidget( "CashEquipmentListCaller");
		if ( pWidget)  pWidget->Show( false);

		pWidget = pResource->FindWidget( "Shop_FrameTabLabel3");
		if ( pWidget)  pWidget->Show( false);
	}
#endif
#endif

	m_nShopTabNum = nTabIndex;

	DrawCharInfoText();
}


void ZShopEquipInterface::SelectEquipmentTab(int nTabIndex)
{
	if (nTabIndex == -1)
		nTabIndex = m_nEquipTabNum;

	ZIDLResource* pResource = GetIDLResource();

	SetKindableItem( MMIST_NONE);

	// Set filter
	MComboBox* pComboBox = (MComboBox*)pResource->FindWidget( "Equip_AllEquipmentFilter");
	if(pComboBox) {
		int sel = pComboBox->GetSelIndex();

		ZMyItemList* pil = ZGetMyInfo()->GetItemList();
		if ( pil) {
			pil->m_ListFilter = sel;
			pil->Serialize();
		}
	}

	// EQUIPMENTLISTBOX
	MWidget* pWidget = pResource->FindWidget("EquipmentList");
	if (pWidget != NULL) pWidget->Show(nTabIndex==0 ? true:false);
	pWidget = pResource->FindWidget("AccountItemList");
	if (pWidget != NULL) pWidget->Show(nTabIndex==0 ? false:true);

	// 탭 버튼
	MButton* pButton = (MButton*)pResource->FindWidget( "Equip");
	if ( pButton)
	{
		pButton->Show( false);
		pButton->Enable( false);
	}

	pButton = (MButton*)pResource->FindWidget( "SendAccountItemBtn");
	if ( pButton)
	{
		pButton->Show( false);
		pButton->Enable( false);
	}

	pButton = (MButton*)pResource->FindWidget( "BringAccountItemBtn");
	if ( pButton)
	{
		pButton->Show( false);
		pButton->Enable( false);
	}

	pButton = (MButton*)pResource->FindWidget( "BringAccountSpendableItemConfirmOpen");
	if ( pButton)
	{
		pButton->Show( false);
		pButton->Enable( false);
	}

	if ( nTabIndex == 0)
	{
		pButton = (MButton*)pResource->FindWidget( "Equip");
		if (pButton) pButton->Show(true);

		pButton = (MButton*)pResource->FindWidget( "SendAccountItemBtn");
		if (pButton) pButton->Show(true);
	}
	else if ( nTabIndex == 1)
	{
		pButton = (MButton*)pResource->FindWidget( "BringAccountItemBtn");
		if ( pButton) pButton->Show( true);

		pButton = (MButton*)pResource->FindWidget( "BringAccountSpendableItemConfirmOpen");
		if ( pButton) pButton->Show( false);
	}

	pButton = (MButton*)pResource->FindWidget("Equipment_CharacterTab");
	if (pButton)
		pButton->Show( nTabIndex==0 ? false : true);
	pButton = (MButton*)pResource->FindWidget("Equipment_AccountTab");
	if (pButton)
		pButton->Show( nTabIndex==1 ? false : true);


	// 탭 라벨
	MLabel* pLabel;
	pLabel = (MLabel*)pResource->FindWidget("Equipment_FrameTabLabel1");
	if ( pLabel)
		pLabel->Show( nTabIndex==0 ? true : false);
	pLabel = (MLabel*)pResource->FindWidget("Equipment_FrameTabLabel2");
	if ( pLabel)
		pLabel->Show( nTabIndex==1 ? true : false);

	// 탭 리스트
	MPicture* pPicture;
	pPicture = (MPicture*)pResource->FindWidget("Equip_ListLabel1");
	if ( pPicture)
		pPicture->Show( nTabIndex==0 ? true : false);
	pPicture = (MPicture*)pResource->FindWidget("Equip_ListLabel2");
	if ( pPicture)
		pPicture->Show( nTabIndex==1 ? true : false);


	// 프레임 탭
	pPicture = (MPicture*)pResource->FindWidget("Equip_TabLabel");
	MBitmap* pBitmap;
	if ( pPicture)
	{
/*		if ( nTabIndex == 0)
			pBitmap = MBitmapManager::Get( "framepaneltab1.tga");
		else
			pBitmap = MBitmapManager::Get( "framepaneltab2.tga");
*/
		if ( nTabIndex == 0)
			pBitmap = MBitmapManager::Get( "framepaneltab1.png");
		else
			pBitmap = MBitmapManager::Get( "framepaneltab2.png");

		if ( pBitmap)
			pPicture->SetBitmap( pBitmap);
	}

	// 중앙은행
	if (nTabIndex == 1)
	{
		ZGetMyInfo()->GetItemList()->ClearAccountItems();
		ZGetMyInfo()->GetItemList()->SerializeAccountItem();
	}

	// 아이템 슬롯 Enable/Disable
	for(int i = 0;  i < MMCIP_END;  i++)
	{
		ZItemSlotView* pItemSlot = (ZItemSlotView*)GetIDLResource()->FindWidget( GetItemSlotName( "Equip", i));
		if( pItemSlot ) pItemSlot->EnableDragAndDrop( nTabIndex==0 ? true : false);
	}

	m_nEquipTabNum = nTabIndex;

	DrawCharInfoText();
}

void ZShopEquipInterface::SelectEquipmentFrameList( const char* szName, bool bOpen)
{
	if (szName == NULL)
	{
		SelectEquipmentFrameList("Shop", bOpen);
		SelectEquipmentFrameList("Equip", bOpen);
		return;
	}

	char szTemp[256];

	ZIDLResource* pResource = GetIDLResource();


	// Frame open/close background image
	MPicture* pPicture;
	strcpy( szTemp, szName);
	strcat( szTemp, "_ArmorBGListFrameOpen");
	pPicture = (MPicture*)pResource->FindWidget( szTemp);
	if(pPicture != NULL) {
		if( bOpen && GetArmorWeaponTabIndex() == 0 )  { pPicture->Show(true); } 
		else										{ pPicture->Show(false);}		
	}

	strcpy( szTemp, szName);
	strcat( szTemp, "_ArmorBGListFrameClose");
	pPicture = (MPicture*)pResource->FindWidget( szTemp);
	if(pPicture != NULL) {
		if( !bOpen && GetArmorWeaponTabIndex() == 0 ) { pPicture->Show(true); } 
		else										{ pPicture->Show(false);}		
	}


	// Frame open/close background image
	strcpy( szTemp, szName);
	strcat( szTemp, "_WeaponBGListFrameOpen");
	pPicture = (MPicture*)pResource->FindWidget( szTemp);
	if(pPicture != NULL) {
		if( bOpen && GetArmorWeaponTabIndex() == 1 )  { pPicture->Show(true); } 
		else										{ pPicture->Show(false);}		
	}

	strcpy( szTemp, szName);
	strcat( szTemp, "_WeaponBGListFrameClose");
	pPicture = (MPicture*)pResource->FindWidget( szTemp);
	if(pPicture != NULL) {
		if( !bOpen && GetArmorWeaponTabIndex() == 1 )  { pPicture->Show(true); } 
		else										 { pPicture->Show(false);}		
	}


	// Frame open/close image
	MButton* pButton;
	strcpy( szTemp, szName);
	strcat( szTemp, "_EquipListFrameCloseButton");
	pButton = (MButton*)pResource->FindWidget( szTemp);
	if ( pButton != NULL) pButton->Show( bOpen);

	strcpy( szTemp, szName);
	strcat( szTemp, "_EquipListFrameOpenButton");
	pButton = (MButton*)pResource->FindWidget( szTemp);
	if ( pButton != NULL) pButton->Show( !bOpen);

	// Resize item slot
	char szWidgetName[ 256];
	sprintf( szWidgetName, "%s_EquipmentSlot_Head", szName);
	MWidget* itemSlot = (MWidget*)pResource->FindWidget( szWidgetName);
	if (itemSlot) {
		MRECT rect = itemSlot->GetRect();

		int nWidth;
		if ( bOpen) nWidth = 220.0f * (float)RGetScreenWidth() / 800.0f;
		else		nWidth = min( rect.w, rect.h);

		for ( int i = 0;  i < MMCIP_END;  i++) {
			itemSlot = (MWidget*)pResource->FindWidget( GetItemSlotName( szName, i));

			if (itemSlot) {
				if(GetArmorWeaponTabIndex() == GetArmorWeaponTabIndexContainItemParts((MMatchCharItemParts)i)) {					
					rect = itemSlot->GetRect();

					itemSlot->SetBounds( rect.x, rect.y, nWidth, rect.h);
					itemSlot->Show(true);
				} 
				else {
					itemSlot->Show(false);
				}
			}
		}
	}

	// 상점과 장비창의 탭 버튼 눌림 상태를 동기화해주자 -_-;
	MBmButton* pTabBtn;
	if (GetArmorWeaponTabIndex() == 0)
	{
		pTabBtn = (MBmButton*)pResource->FindWidget("Shop_ArmorEquipmentTab");
		if (pTabBtn) pTabBtn->SetCheck(true);
		pTabBtn = (MBmButton*)pResource->FindWidget("Equip_ArmorEquipmentTab");
		if (pTabBtn) pTabBtn->SetCheck(true);
	}
	else if (GetArmorWeaponTabIndex() == 1)
	{
		pTabBtn = (MBmButton*)pResource->FindWidget("Shop_WeaponEquipmentTab");
		if (pTabBtn) pTabBtn->SetCheck(true);
		pTabBtn = (MBmButton*)pResource->FindWidget("Equip_WeaponEquipmentTab");
		if (pTabBtn) pTabBtn->SetCheck(true);
	}
}

// 인자로 주어진 아이템파츠를 담는 아이템슬롯이 있는 탭 인덱스를 알려준다
int ZShopEquipInterface::GetArmorWeaponTabIndexContainItemParts(MMatchCharItemParts parts)
{
	// 방어구탭
	if (parts < MMCIP_MELEE || parts == MMCIP_AVATAR)
		return 0;
	// 무기탭
	if (parts >= MMCIP_MELEE && parts < MMCIP_LONGBUFF2 + 1 && parts != MMCIP_AVATAR)
		return 1;

	_ASSERT(0);
	return 0;
}

bool ZShopEquipInterface::IsEquipmentFrameListOpened( const char* szName)
{
	ZIDLResource* pResource = GetIDLResource();

	char szTemp[256];
	MPicture* pPicture;
	strcpy( szTemp, szName);
	if (GetArmorWeaponTabIndex() == 0)
	{
		strcat( szTemp, "_ArmorBGListFrameOpen");
		pPicture = (MPicture*)pResource->FindWidget( szTemp);
		if (pPicture) 
			return pPicture->IsVisible();
	}
	else if (GetArmorWeaponTabIndex() == 1)
	{
		strcat( szTemp, "_WeaponBGListFrameOpen");
		pPicture = (MPicture*)pResource->FindWidget( szTemp);
		if (pPicture) 
			return pPicture->IsVisible();
	}
	return false;
}

// 주어진 슬롯타입을 담고 있는 탭을 선택해준다 - 리스트에서 어떤 아이템을 선택한 경우 그 아이템에 맞는 방어구/무기탭을 자동변경해주는 기능을 위해
void ZShopEquipInterface::SelectArmorWeaponTabWithSlotType(MMatchItemSlotType nSlotType)
{
	ZItemSlotView* pItemSlot;
	for ( int i = 0;  i < MMCIP_END;  i++)
	{
		pItemSlot = (ZItemSlotView*)GetIDLResource()->FindWidget( GetItemSlotName( "Equip", i));
		if ( pItemSlot)
		{
			if (IsKindableItem(pItemSlot->GetParts(), nSlotType))
			{
				int tabIndex = GetArmorWeaponTabIndexContainItemParts(pItemSlot->GetParts());
				
				bool bOpened = ZGetGameInterface()->GetShopEquipInterface()->IsEquipmentFrameListOpened();
				ZGetGameInterface()->GetShopEquipInterface()->SetArmorWeaponTabIndex(tabIndex);
				ZGetGameInterface()->GetShopEquipInterface()->SelectEquipmentFrameList(NULL, bOpened);

				return;
			}
		}
	}
}

void ZShopEquipInterface::OnArmorWeaponTabButtonClicked(int nTab)
{
	bool bOpened = IsEquipmentFrameListOpened();
	SetArmorWeaponTabIndex(nTab);
	SelectEquipmentFrameList(NULL, bOpened);
}

void ZShopEquipInterface::ShowItemDescription(bool bShow, MTextArea* pTextArea, void* pCaller)
{
	if (!pTextArea) return;

	if (bShow)
	{
		pTextArea->Show(true);
		m_pItemDescriptionClient = pCaller;
	}
	else if (!bShow && pCaller==m_pItemDescriptionClient)
	{
		// 툴팁을 끄려고 할때는 자신이 켰었어야 한다. 도중에 다른 곳에서 툴팁을 점유했다면 끌 권한이 없음
		pTextArea->Show(false);
	}
}

void ZShopEquipInterface::DrawCharInfoText()
{
	// 현재 내 상태로 초기화
	DrawCharInfoText(NULL, 0,
		ZGetMyInfo()->GetItemList()->GetEquipedTotalWeight(),
		ZGetMyInfo()->GetItemList()->GetMaxWeight(),
		ZGetMyInfo()->GetHP(),
		ZGetMyInfo()->GetAP(),
		0, 0);
}

void ZShopEquipInterface::DrawCharInfoText(char* szShopOrEquip, int nReqLevel, int nNewWT, int nNewMaxWT, int nNewHP, int nNewAP, int nReqBounty, int nReqCash)
{
	if (szShopOrEquip == NULL) 
	{
		DrawCharInfoText("Shop", nReqLevel, nNewWT, nNewMaxWT, nNewHP, nNewAP, nReqBounty, nReqCash);
		DrawCharInfoText("Equip", nReqLevel, nNewWT, nNewMaxWT, nNewHP, nNewAP, nReqBounty, nReqCash);
		return;
	}

	if (0!=strcmp(szShopOrEquip, "Shop") && 0!=strcmp(szShopOrEquip, "Equip")) return;

	MTextArea* pTextArea[3];
	char sz1[256], sz2[256], szTextArea[64];
	const char* szRed	= "^1";
	const char* szGreen	= "^2";
	const char* szGray	= "^9";
	const char* szColor	= NULL;

	// prefix에 따라서 "Shop_MyInfo1" "Shop_MyInfo2" "Shop_MyInfo3" "Equip_MyInfo1" "Equip_MyInfo2" "Equip_MyInfo3"의 이름을 구성
	// (가로로 늘어놓은 TextArea 세개에 나눠서 표시하기 때문에..)
	for (int i=0; i<3; ++i)
	{
		sprintf(szTextArea, "%s_MyInfo%d", szShopOrEquip, i+1);
		pTextArea[i] = (MTextArea*)GetIDLResource()->FindWidget(szTextArea);
		if (NULL == pTextArea[i])
		{
			_ASSERT(0);
			return;	// 하나라도 못찾으면 리턴해버리자
		}

		pTextArea[i]->Clear();
	}

	// 첫번째 TextArea (레벨, 무게)
	szColor = szGray;
	if (nReqLevel > ZGetMyInfo()->GetLevel())
		szColor = szRed;
	sprintf(sz1, "^9%s : %s%d ^9%s", ZMsg(MSG_CHARINFO_LEVEL), szColor, ZGetMyInfo()->GetLevel(), ZMsg(MSG_CHARINFO_LEVELMARKER));
	pTextArea[0]->AddText(sz1);

	int nCurrMaxWT = ZGetMyInfo()->GetItemList()->GetMaxWeight();
	sprintf(sz1, "^9%s : ", ZMsg(MSG_CHARINFO_WEIGHT));
	szColor = (nNewWT > nNewMaxWT) ? szRed : szGray;
	sprintf(sz2, "%s%d", szColor, nNewWT);
	strcat(sz1, sz2);
	sprintf(sz2, "^9/%d", nCurrMaxWT);
	strcat(sz1, sz2);
	int nDiffMaxWT = nNewMaxWT - nCurrMaxWT;
	if (nDiffMaxWT != 0)
	{
		szColor = (nDiffMaxWT > 0) ? szGreen : szRed;
		sprintf(sz2, "%s%+d", szColor, nDiffMaxWT);
		strcat(sz1, sz2);
	}
	pTextArea[0]->AddText(sz1);



	// 두번째 TextArea (체력, 방어)
	sprintf(sz1, "^9%s : %d ", ZMsg(MSG_CHARINFO_HP), ZGetMyInfo()->GetHP());
	int nDiffHP = nNewHP - ZGetMyInfo()->GetHP();
	if (nDiffHP != 0)
	{
		szColor = (nDiffHP > 0) ? szGreen : szRed;
		sprintf(sz2, "%s%+d", szColor, nDiffHP);
		strcat(sz1, sz2);
	}
	pTextArea[1]->AddText(sz1);

	sprintf(sz1, "^9%s : %d ", ZMsg(MSG_CHARINFO_AP), ZGetMyInfo()->GetAP());
	int nDiffAP = nNewAP - ZGetMyInfo()->GetAP();
	if (nDiffAP != 0)
	{
		szColor = (nDiffAP > 0) ? szGreen : szRed;
		sprintf(sz2, "%s%+d", szColor, nDiffAP);
		strcat(sz1, sz2);
	}
	pTextArea[1]->AddText(sz1);


	// 세번째 TextArea (바운티, 캐시)
	sprintf(sz1, "^9%s : ", ZMsg(MSG_CHARINFO_BOUNTY));
	szColor = (nReqBounty > ZGetMyInfo()->GetBP()) ? szRed : szGray;
	sprintf(sz2, "%s%d", szColor, ZGetMyInfo()->GetBP());
	strcat(sz1, sz2);
	pTextArea[2]->AddText(sz1);

	sprintf(sz1, "^9%s : ", ZMsg(MSG_CHARINFO_CASH));
	szColor = (nReqBounty > ZGetMyInfo()->GetECoins()) ? szRed : szGray;
	sprintf(sz2, "%s%d", szColor, ZGetMyInfo()->GetECoins());
	strcat(sz1, sz2);
	pTextArea[2]->AddText(sz1);

/*	보유 캐쉬는 캐쉬템 구입이 가능해질때 보여주자
	sprintf(sz1, "^9%s : ", ZMsg(MSG_CHARINFO_CASH));
	szColor = (nReqCash > ZGetMyInfo()->GetCash()) ? szRed : szGray;
	sprintf(sz2, "%s%d", szColor, ZGetMyInfo()->GetCash());
	strcat(sz1, sz2);
	pTextArea[2]->AddText(sz1);
	*/
}

void ZShopEquipInterface::Update()
{
	if (m_pSellCashItemConfirmDlg)
		m_pSellCashItemConfirmDlg->Update();
}