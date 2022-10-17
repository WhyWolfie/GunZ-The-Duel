Open(ZChat_Cmds.cpp) <br>

    void ChatCmd_Senditem(const char* line, const int argc, char **const argv);

Part 2

	_CC_AC("item", &ChatCmd_Senditem, CCF_ADMIN | CCF_ALL, ARGVNoMin, 3, true, "/item <charname> <itemid> <rentdays>", "");

Part 3

    void ChatCmd_Senditem(const char* line, const int argc, char **const argv)
    {
      if (!ZGetMyInfo()->IsAdminGrade()) {
        return;
      }

      if (argc < 4) {
        OutputCmdWrongArgument(argv[0]);
        return;
      }

      int nItemId = atoi(argv[2]);
      int nDays = atoi(argv[3]);

      if (nItemId == 0 || nDays < 0) {
        OutputCmdWrongArgument(argv[0]);
        return;
      }

      ZPostAdminSendItem(argv[1], nItemId, nDays);
    }


Open(ZPost.h) <br>

    inline void ZPostAdminSendItem(char* pszTargetName, int nItemId, int nDays)
    {
      ZPOSTCMD3(MC_ADMIN_SENDITEM, MCmdParamStr(pszTargetName), MCommandParameterInt(nItemId), MCommandParameterInt(nDays));
    }


Open(MSharedCommandTable.h) <br>

    #define MC_ADMIN_SENDITEM					    60026


Open(MMatchServer_OnCommand.cpp) <br>

    case MC_ADMIN_SENDITEM:
    {
      char szPlayer[128] = "";
      int nItemID;
      int nDays;

      pCommand->GetParameter(&szPlayer, 0, MPT_STR, sizeof(szPlayer));
      pCommand->GetParameter(&nItemID, 1, MPT_INT);
      pCommand->GetParameter(&nDays, 2, MPT_INT);

      OnAdminSendItem(pCommand->GetSenderUID(), szPlayer, nItemID, nDays);
    }
    break;


Open(MSharedCommandTable.cpp) <br>

			C(MC_ADMIN_SENDITEM, "Admin.SendItem", "Send Item To Player", MCDT_MACHINE2MACHINE)
				P(MPT_STR, "szPlayer")
				P(MPT_INT, "nItemId")
				P(MPT_INT, "nDays")

Open(MMatchServer.h) <br>
Find

    void OnAdminPingToAll(const MUID& uidAdmin);

Add

	void OnAdminSendItem(const MUID& uidAdmin, const char* szPlayer, const int nItemId, const int nDays);

Open(MMatchServer_Admin.cpp) <br>

    void MMatchServer::OnAdminSendItem(const MUID& uidAdmin, const char* szPlayer, const int nItemId, const int nDays)
    {
      MMatchObject* pObj = GetObject(uidAdmin);
      if (pObj == NULL || !IsAdminGrade(pObj)) return;

      if (strlen(szPlayer) < 2) {
        Announce(pObj, "Player name must be longer.");
        return;
      }

      if (nDays < 0) {
        Announce(pObj, "RentDays must be 0 or more.");
        return;
      }

      MMatchObject* pTargetObj = GetPlayerByName(szPlayer);

      int nCID = 0;
      if (m_MatchDBMgr.GetCharCID(szPlayer, &nCID) == false)
      {
        Announce(pObj, "Could not find player.");
        return;
      }

      MMatchItemDesc* pItemDesc = MGetMatchItemDescMgr()->GetItemDesc(nItemId);
      if (pItemDesc == NULL)
      {
        Announce(pObj, "Could not find item.");
        return;
      }

      if (!pItemDesc->IsSpendableItem())
      {
        unsigned long int nNewCIID = 0;
        if (!m_MatchDBMgr.InsertDistributeItem(nCID, nItemId, nDays != 0, nDays * 24, &nNewCIID)) {
          Announce(pObj, "Could not send item.");
          return;
        }

        if (pTargetObj != NULL) {
          MUID uidNew = MMatchItemMap::UseUID();
          pTargetObj->GetCharInfo()->m_ItemList.CreateItem(uidNew, nNewCIID, nItemId, nDays != 0, nDays * 24 * 60, nDays * 24);

          UpdateCharItemDBCachingData(pTargetObj);

          ResponseCharacterItemList(pTargetObj->GetUID());

          Announce(pTargetObj, "You have received an item!");
        }
      }
      else {
        Announce(pObj, "Cannot send items of this type.");
        return;
      }

      Announce(pObj, "Sent item to player.");
    }


Rebuild MatchServer & Gunz.

