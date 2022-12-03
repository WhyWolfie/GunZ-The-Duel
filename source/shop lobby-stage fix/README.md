Open(ZGameInterface.cpp) <br>

Find <br>


    MLabel* pLabel = (MLabel*)pResource->FindWidget("Shop_Message");
    sprintf( buf, "%s > %s > %s", ZGetGameClient()->GetServerName(), ZMsg( MSG_WORD_LOBBY), ZMsg( MSG_WORD_SHOP));

Replace <br>

		char buf[256];
		MLabel* pLabel = (MLabel*)pResource->FindWidget("Shop_Message");
		if (ZApplication::GetGameInterface()->GetState() == GUNZ_LOBBY)
			sprintf(buf, "%s > %s > %s", ZGetGameClient()->GetServerName(), ZMsg(MSG_WORD_LOBBY), ZMsg(MSG_WORD_SHOP));
		else
			sprintf(buf, "%s > %s > %s", ZGetGameClient()->GetServerName(), ZMsg(MSG_WORD_STAGE), ZMsg(MSG_WORD_SHOP));

Find <br>

    if (ZApplication::GetGameInterface()->GetState() == GUNZ_LOBBY)

Replace <br>

		if (ZApplication::GetGameInterface()->GetState() == GUNZ_LOBBY)
			ShowWidget("Lobby", true);
		else
			ShowWidget("Stage", true);

