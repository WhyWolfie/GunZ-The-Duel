Open(MFeatureDefine.h) <br>
Add <br>

    #define _MIPING		1
    

Open(MMatchClient.h) <br>
Find <br>

    virtual MUID GetSenderUIDBySocket(SOCKET socket);

Add under <br>

    #ifdef _MIPING
      int MiPing;
    #endif

Open(ZCombatInterface.cpp) <br>
Find <br>

    int nCount = 0;
    
Add under <br>

    #ifdef _MIPING
      int MiPing = 0;
      int total = 0;
    #endif
    
Find <br>

		x=ITEM_XPOS[4];
		sprintf(szText,"%d",pItem->nDeaths);
		TextRelative(pDC,x,texty,szText,true);
    
Add under <br>

    #ifdef _MIPING
        int p = pItem->nPing;
        if (p != 999 && p > 0 && !pItem->bMyChar)
        {
          MiPing += p;
          total++;
        }
        if (pItem->uidUID == ZGetGameClient()->GetPlayerUID())
          pItem->nPing = ZGetGameClient()->MiPing;

        sprintf(szText, "%d", ((pItem->bMyChar && ZGetGameClient()->MiPing != NULL) ? ZGetGameClient()->MiPing : pItem->nPing));
    #endif
    
Find <br>

      while(!items.empty())
      {
        delete *items.begin();
        items.erase(items.begin());
      }
    
    
Add above <br>

    #ifdef _MIPING
      if (total > 2)
        MiPing = (int)MiPing / total;
      ZGetGameClient()->MiPing = MiPing;
    #endif
