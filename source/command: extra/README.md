Open(ZGameClient.h) <br>
Find

    bool					m_bRejectInvite;

Place under

    bool					m_bShowExtra;

Find

    void SetRejectInvite(bool bVal)		{ m_bRejectInvite = bVal; }

Place under

    bool GetExtra()					{ return m_bShowExtra; }
    void SetExtra(bool bVal)			{ m_bShowExtra = bVal; }

Open(ZCombatInterface.cpp) <br>
Find

    ZGetScreenEffectManager()->DrawMyHPPanal(pDC);

below that you will see #ifdef _DEBUG, select from that to the #endif, delete it and put this,


    ZGameClient* pGameClient = ZGetGameClient();

        if (pGameClient->GetExtra())
        {
          ZCharacter* pCharacter = ZGetGame()->m_pMyCharacter;
          if (pCharacter && !pCharacter->IsDie())
          {
            MFont* pFont = GetGameFont();
            pDC->SetFont(pFont);
            pDC->SetColor(MCOLOR(0xFFFFFFFF));

            char szMsg[128];

            sprintf(szMsg, "HP : %i / %i", (int)pCharacter->GetHP(), (int)pCharacter->GetMaxHP());
            TextRelative(pDC, 100.f/800.f, 23.f/600.f, szMsg);

            sprintf(szMsg, "AP : %i / %i", (int)pCharacter->GetAP(), (int)pCharacter->GetMaxAP());
            TextRelative(pDC, 100.f/800.f, 50.f/600.f, szMsg);

            sprintf(szMsg, "FPS : %i", (int)g_fFPS);
            TextRelative(pDC, 700.f/800.f, 23.f/600.f, szMsg);
          }
        }

Open(ZChat_Cmds.cpp) <br>
Find

    void ChatCmd_RemoveJjang(const char* line, const int argc, char **const argv);

Place under

    void ChatCmd_Extra(const char* line, const int argc, char **const argv);

Find

    _CC_AC("admin_dump_gambleitem_log",		&ChatCmd_AdminDumpGambleitemLog,		CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/admin_dump_gambleitem_log", "");

Place under

    _CC_AC("extra",						&ChatCmd_Extra,						CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/extra", "");

Find

    void ChatCmd_QUESTTEST_WeakNPCs(const char* line,const int argc, char **const argv)

Place under

    void ChatCmd_Extra(const char* line, const int argc, char **const argv)
    {
      ZGameClient* pGameClient = ZGetGameClient();
      pGameClient->SetExtra(!pGameClient->GetExtra());
    }













