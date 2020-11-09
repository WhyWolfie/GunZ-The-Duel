#include "stdafx.h"
#include "MMatchShop.h"
#include "MMatchConfig.h"
#include "MMatchGambleMachine.h"

MMatchShop::MMatchShop()
{

}
MMatchShop::~MMatchShop()
{

}
bool MMatchShop::Create(const char* szDescFileName)
{
	return ReadXml(szDescFileName);

	return true;
}


void MMatchShop::Destroy()
{
	Clear();
}


bool MMatchShop::ReadXml(const char* szFileName)
{
	MXmlDocument	xmlDocument;

	xmlDocument.Create();

	if (!xmlDocument.LoadFromFile(szFileName))
	{
		xmlDocument.Destroy();
		return false;
	}

	MXmlElement rootElement, chrElement, attrElement;
	char szTagName[256];

	rootElement = xmlDocument.GetDocumentElement();

	int iCount = rootElement.GetChildNodeCount();

	for (int i = 0; i < iCount; i++)
	{
		chrElement = rootElement.GetChildNode(i);
		chrElement.GetTagName(szTagName);
		if (szTagName[0] == '#') continue;

		if (!strcmp(szTagName, MTOK_SELL))
		{
			ParseSellItem(chrElement);
		}
	}

	xmlDocument.Destroy();

	return true;
}

void MMatchShop::ParseSellItem(MXmlElement& element)
{
	ShopItemNode *pNewItemNode = new ShopItemNode;

	int nDescID = 0;
	int	nItemCount = 1;

	// 2010-04-01. 일단은 Shop.xml이 완벽하지 않으므로, 주석처리해놓음! 
	// 무조건 ItemCount는 1이다.
	//element.GetAttribute(&nItemCount, MTOK_SELL_ITEM_COUNT);
	if( nItemCount == 0 )	{ pNewItemNode->nItemCount = 1; } 
	else					{ pNewItemNode->nItemCount = nItemCount; }	

	element.GetAttribute(&nDescID, MTOK_SELL_ITEMID);
	element.GetAttribute(&pNewItemNode->nRentPeriodHour, MTOK_SELL_RENT_PERIOD_HOUR, 0);

	pNewItemNode->nItemID = nDescID;
	pNewItemNode->bIsRentItem = (pNewItemNode->nRentPeriodHour > 0);	
	

	MMatchItemDesc* pItemDesc = MGetMatchItemDescMgr()->GetItemDesc(nDescID);
	if (pItemDesc != NULL) {
		
		// 이제 캐쉬 아이템도 판다
		/*// 캐쉬 아이템은 무시
		if (pItemDesc->IsCashItem()) {
			delete pNewItemNode;
			return;
		}*/

		// 아바타 기능 비활성시 바운티 아바타를 판매목록에서 뺀다
#ifndef _AVATAR_ENABLE
		if (pItemDesc->m_nSlot == MMIST_AVATAR)
			return;
#endif

		m_ItemNodeVector.push_back(pNewItemNode);
		m_ItemNodeMap.insert(map<unsigned int, ShopItemNode*>::value_type(pNewItemNode->nItemID, pNewItemNode));
	}
#ifdef _QUEST_ITEM
	else
	{
		if ( QuestTestServer() == false )
		{
			delete pNewItemNode;
			return;
		}

		//MatchItem에서 없을경우 QuestItem에서 다시 한번 검사를 함.
		MQuestItemDesc* pQuestItemDesc = GetQuestItemDescMgr().FindQItemDesc( nDescID );
		if( 0 == pQuestItemDesc )
		{
			delete pNewItemNode;
			return;
		}

		m_ItemNodeVector.push_back( pNewItemNode );
		m_ItemNodeMap.insert( map<unsigned int, ShopItemNode*>::value_type(pNewItemNode->nItemID, pNewItemNode) );
	}
#endif
}

void MMatchShop::Clear()
{
	int nVectorSize = (int)m_ItemNodeVector.size();
	for (int i = 0; i < nVectorSize; i++)
	{
		ShopItemNode* pNode = m_ItemNodeVector[i];
		delete pNode;
	}

	m_ItemNodeVector.clear();
	m_ItemNodeMap.clear();
}


MMatchShop* MMatchShop::GetInstance()
{
	static MMatchShop g_stMatchShop;
	return &g_stMatchShop;
}

bool MMatchShop::IsSellItem(const unsigned long int nItemID)
{
	map<unsigned int, ShopItemNode*>::iterator itor = m_ItemNodeMap.find(nItemID);
	if (itor != m_ItemNodeMap.end()) {
		return true;
	}

	return false;
}

ShopItemNode* MMatchShop::GetSellItemByIndex(int nListIndex)
{
	if ((nListIndex < 0) || (nListIndex >= GetCount())) return NULL;

	return m_ItemNodeVector[nListIndex];
}

ShopItemNode* MMatchShop::GetSellItemByItemID(int nItemID)
{
	map<unsigned int, ShopItemNode*>::iterator itor = m_ItemNodeMap.find(nItemID);
	if (itor == m_ItemNodeMap.end()) {
		return NULL;
	}

	return (ShopItemNode*)(itor->second);
}

#ifdef _DEBUG
void MMatchShop::MakeShopXML()
{
	char szTemp[4096];
	FILE* fp;	
	int nCount;

	nCount = 0;
	fp = fopen("ShopProduct.sql", "wt");
	map<unsigned int, ShopItemNode*>::iterator it = m_ItemNodeMap.begin();
	for( ; it != m_ItemNodeMap.end(); it++) 
	{
		ShopItemNode* pNode = it->second;
		memset(szTemp, 0, 4096);

		MMatchItemDesc* pDesc;
		const MMatchGambleItem* pGamble;
		MQuestItemDesc* pQuest;
		if( (pDesc = MGetMatchItemDescMgr()->GetItemDesc(pNode->nItemID)) != NULL ) 
		{
			int nSex;
			switch(pDesc->m_nResSex.Ref()) {
				case 0 :	nSex = 1;
				case 1 :	nSex = 2;
				case -1 :	nSex = 3;
			}
			/*
			sprintf(szTemp, "INSERT ShopProduct(PID, Name, [Desc], Type_Code, Sex_Code, Level, RegDate, IsOpen, ItemID, CSID) ");
			sprintf(szTemp, "%s VALUES(%d, '%s', '%s', 1, %d, %d, GETDATE(), 1, %d, 0)\n", 
				szTemp, 10000 + (++nCount), pDesc->m_pMItemName->Ref().m_szItemName, pDesc->m_szDesc, nSex, pDesc->m_nResLevel.Ref(), pNode->nItemID);
			*/
			sprintf(szTemp, "INSERT ShopProduct(PID, Name, [Desc], Type_Code, Sex_Code, Level, RegDate, ItemID, CSID) ");
			sprintf(szTemp, "%s VALUES(%d, '%s', '%s', 1, %d, %d, GETDATE(), %d, 0)\n", 
				szTemp, 10000 + (++nCount), pDesc->m_pMItemName->Ref().m_szItemName, pDesc->m_szDesc, nSex, pDesc->m_nResLevel.Ref(), pNode->nItemID);
			fputs(szTemp, fp);
		} 
		else if( (pGamble = MGetMatchServer()->GetGambleMachine().GetGambleItemByGambleItemID(pNode->nItemID)) != NULL ) 
		{
			if( pGamble->IsCash() ) continue;
			/*
			sprintf(szTemp, "INSERT ShopProduct(PID, Name, [Desc], Type_Code, Sex_Code, Level, RegDate, IsOpen, ItemID, CSID) ");
			sprintf(szTemp, "%s VALUES(%d, '%s', '%s', 1, 3, 0, GETDATE(), 1, %d, 0)\n", szTemp, 10000 + (++nCount), pGamble->GetName().c_str(), pGamble->GetDescription().c_str(), pNode->nItemID);
			*/
			sprintf(szTemp, "INSERT ShopProduct(PID, Name, [Desc], Type_Code, Sex_Code, Level, RegDate, ItemID, CSID) ");
			sprintf(szTemp, "%s VALUES(%d, '%s', '%s', 1, 3, 0, GETDATE(), %d, 0)\n", szTemp, 10000 + (++nCount), pGamble->GetName().c_str(), pGamble->GetDescription().c_str(), pNode->nItemID);
			fputs(szTemp, fp);
		}
		else if( (pQuest = GetQuestItemDescMgr().FindQItemDesc(pNode->nItemID)) != NULL ) 
		{	
			/*
			sprintf(szTemp, "INSERT ShopProduct(PID, Name, [Desc], Type_Code, Sex_Code, Level, RegDate, IsOpen, ItemID, CSID) ");
			sprintf(szTemp, "%s VALUES(%d, '%s', '%s', 1, 3, %d, GETDATE(), 1, %d, 0)\n", 
				szTemp, 10000 + (++nCount), pQuest->m_szQuestItemName, pQuest->m_szDesc, pQuest->m_nLevel, pNode->nItemID);
			*/
			sprintf(szTemp, "INSERT ShopProduct(PID, Name, [Desc], Type_Code, Sex_Code, Level, RegDate, ItemID, CSID) ");
			sprintf(szTemp, "%s VALUES(%d, '%s', '%s', 1, 3, %d, GETDATE(), %d, 0)\n", 
				szTemp, 10000 + (++nCount), pQuest->m_szQuestItemName, pQuest->m_szDesc, pQuest->m_nLevel, pNode->nItemID);
			fputs(szTemp, fp);
		}
		else {
			_ASSERT(0);
		}
	}
	fclose(fp);	

	
	nCount = 0;
	fp = fopen("ShopProductCategory.sql", "wt");
	for(it = m_ItemNodeMap.begin(); it != m_ItemNodeMap.end(); it++) 
	{
		ShopItemNode* pNode = it->second;
		memset(szTemp, 0, 4096);

		MMatchItemDesc* pDesc;
		const MMatchGambleItem* pGamble;
		MQuestItemDesc* pQuest;
		if( (pDesc = MGetMatchItemDescMgr()->GetItemDesc(pNode->nItemID)) != NULL ) 
		{			
			sprintf(szTemp, "INSERT ShopProductCategory(Category_Code, PID, FromDate, EndDate, RegDate, IsOpen) VALUES");
			sprintf(szTemp, "%s (%d, %d, '2010-10-01', '9999-12-31', GETDATE(), 1)\n", szTemp, pDesc->m_nSlot, 10000 + (++nCount));
			fputs(szTemp, fp);
		} 
		else if( (pGamble = MGetMatchServer()->GetGambleMachine().GetGambleItemByGambleItemID(pNode->nItemID)) != NULL ) 
		{
			if( pGamble->IsCash() ) continue;

			sprintf(szTemp, "INSERT ShopProductCategory(Category_Code, PID, FromDate, EndDate, RegDate, IsOpen) VALUES");
			sprintf(szTemp, "%s (200, %d, '2010-10-01', '9999-12-31', GETDATE(), 1)\n", szTemp, 10000 + (++nCount));
			fputs(szTemp, fp);
		}
		else if( (pQuest = GetQuestItemDescMgr().FindQItemDesc(pNode->nItemID)) != NULL ) 
		{	
			sprintf(szTemp, "INSERT ShopProductCategory(Category_Code, PID, FromDate, EndDate, RegDate, IsOpen) VALUES");
			sprintf(szTemp, "%s (300, %d, '2010-10-01', '9999-12-31', GETDATE(), 1)\n", szTemp, 10000 + (++nCount));
			fputs(szTemp, fp);
		}
		else {
			_ASSERT(0);
		}
	}
	fclose(fp);	


	nCount = 0;
	fp = fopen("ShopProductPrice.sql", "wt");	
	for(it = m_ItemNodeMap.begin(); it != m_ItemNodeMap.end(); it++) 
	{
		ShopItemNode* pNode = it->second;
		memset(szTemp, 0, 4096);

		MMatchItemDesc* pDesc;
		const MMatchGambleItem* pGamble;
		MQuestItemDesc* pQuest;
		if( (pDesc = MGetMatchItemDescMgr()->GetItemDesc(pNode->nItemID)) != NULL ) 
		{			
			sprintf(szTemp, "INSERT ShopProductPrice(PID, Sell_Code, Price_Code, DefaultPriceFlag, FromDate, EndDate, Price) VALUES");
			sprintf(szTemp, "%s (%d, 1, 2, 1, '2010-10-01', '9999-12-31', %d)\n", szTemp, 10000 + (++nCount), pDesc->m_nBountyPrice.Ref());
			fputs(szTemp, fp);
		} 
		else if( (pGamble = MGetMatchServer()->GetGambleMachine().GetGambleItemByGambleItemID(pNode->nItemID)) != NULL ) 
		{
			if( pGamble->IsCash() ) continue;

			sprintf(szTemp, "INSERT ShopProductPrice(PID, Sell_Code, Price_Code, DefaultPriceFlag, FromDate, EndDate, Price) VALUES");
			sprintf(szTemp, "%s (%d, 1, 2, 1, '2010-10-01', '9999-12-31', %d)\n", szTemp, 10000 + (++nCount), pGamble->GetPrice());
			fputs(szTemp, fp);
		}
		else if( (pQuest = GetQuestItemDescMgr().FindQItemDesc(pNode->nItemID)) != NULL ) 
		{	
			sprintf(szTemp, "INSERT ShopProductPrice(PID, Sell_Code, Price_Code, DefaultPriceFlag, FromDate, EndDate, Price) VALUES");
			sprintf(szTemp, "%s (%d, 1, 2, 1, '2010-10-01', '9999-12-31', %d)\n", szTemp, 10000 + (++nCount), pQuest->m_nPrice);
			fputs(szTemp, fp);
		}
		else {
			_ASSERT(0);
		}
	}
	fclose(fp);	
}
#endif