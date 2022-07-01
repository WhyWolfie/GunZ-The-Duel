<b>Item Search Shop</b><br>

I will leave you a search for items by name.I
will not give support because the area is very toxic.

So, good luck. 

ZGameInterface.cpp

    SetListenerWidget("Item_Search", ZGetShopItemSearchInputListener());

ZInterfaceListener.cpp

    class MShopItemSearchInputListener : public MListener{
    public:
        virtual bool OnCommand(MWidget* pWidget, const char* szMessage){
      if (pWidget->IsVisible())
      {
       ZGetShop()->SerializeSearch();
      }
      return false;
        }
    };
    MShopItemSearchInputListener    g_ShopItemSearchInputListener;
    MListener* ZGetShopItemSearchInputListener()
    {
        return &g_ShopItemSearchInputListener;
    }

ZInterfaceListener.h

    MListener* ZGetShopItemSearchInputListener();
    DECLARE_LISTENER(ZGetItemSearchCallerButtonListener);

ZShop.cpp

    void ZShop::SerializeSearch()
    {
        ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
        MMultiColListBox* pListBox = (MMultiColListBox*)pResource->FindWidget("AllEquipmentList");

        if (!pListBox) { _ASSERT(0); return; }
        pListBox->RemoveAll();

        if (m_ListFilter == zshop_item_filter_all || m_ListFilter == zshop_item_filter_gamble)
        {
      for (int i = 0; i<(int)m_vGItemList.size(); i++)
      {
       const ZGambleItemDefine* pDesc = ZGetGambleItemDefineMgr().GetGambleItemDefine(m_vGItemList[i]->nItemID);
       if (pDesc == NULL) { _ASSERT(0); continue; }

       ZShopEquipItem_Gamble* pGItem = new ZShopEquipItem_Gamble(pDesc);
       ZShopEquipItemHandle_PurchaseGamble* pHandle =
        new ZShopEquipItemHandle_PurchaseGamble(pGItem);

       pGItem->SetHandlePurchase(pHandle);

       ZShopEquipListItem* pListItem = new ZShopEquipListItem(pGItem);
       pListBox->Add(pListItem);
      }
        }

        for (int i = 0; i<GetItemCount(); i++)
        {
      ZShopEquipItem* pWrappedItem = NULL;

      if (MMatchItemDesc* pDesc = MGetMatchItemDescMgr()->GetItemDesc(m_vShopItem[i]->nItemID))
      {
       if (CheckTypeWithListFilter(pDesc->m_nSlot, pDesc->IsEnchantItem()) == false) continue;
       if (pDesc->m_nResSex.Ref() != -1 && pDesc->m_nResSex.Ref() != int(ZGetMyInfo()->GetSex())) continue;

       MEdit* pWidget = (MEdit*)pResource->FindWidget("Item_Search");

       if ((strlen(pWidget->GetText()) > 0) && (strlen(pWidget->GetText()) <= 32))
       {
        if (StrStrIA(pDesc->m_pMItemName->Ref().m_szItemName, pWidget->GetText()) == NULL) continue;
       }

       ZShopEquipItem_Match* pMItem = new ZShopEquipItem_Match(pDesc);
       ZShopEquipItemHandle_PurchaseMatch* pHandle =
        new ZShopEquipItemHandle_PurchaseMatch(pMItem);
       pWrappedItem = pMItem;
       pWrappedItem->SetHandlePurchase(pHandle);
      }
      else if (MQuestItemDesc* pDesc = GetQuestItemDescMgr().FindQItemDesc(m_vShopItem[i]->nItemID))
      {
       if (m_ListFilter != zshop_item_filter_all && m_ListFilter != zshop_item_filter_quest) continue;

       MEdit* pWidget = (MEdit*)pResource->FindWidget("Item_Search");

       if ((strlen(pWidget->GetText()) > 0) && (strlen(pWidget->GetText()) <= 32))
       {
        if (StrStrIA(pDesc->m_szQuestItemName, pWidget->GetText()) == NULL) continue;
       }

       MUID uidItem = MUID(0, i + 1);
       ZShopEquipItem_Quest* pQItem = new ZShopEquipItem_Quest(pDesc);
       ZShopEquipItemHandle_PurchaseQuest* pHandle =
        new ZShopEquipItemHandle_PurchaseQuest(pQItem);
       pWrappedItem = pQItem;
       pWrappedItem->SetHandlePurchase(pHandle);
      }

      if (!pWrappedItem) { _ASSERT(0); continue; }

      ZShopEquipListItem* pListItem = new ZShopEquipListItem(pWrappedItem);
      pListBox->Add(pListItem);
        }
    }

ZShop.h

    void SerializeSearch();

xml

     <EDIT item="Item_Search" parent="Shop">
      <EDITLOOK>NullEditLook</EDITLOOK>
      <BOUNDS>
       <X>625</X>
       <Y>116</Y>
       <W>153</W>
       <H>21</H>
      </BOUNDS>
      <MAXLENGTH>32</MAXLENGTH>
        </EDIT> 








