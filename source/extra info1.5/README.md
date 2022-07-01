<b> Extra Info [1.5] </b> <br>
ZCombatInterface.cpp:
Look for void ZCombatInterface :: OnDraw (MDrawContext * pDC)
Beneath DrawMyWeaponPont(pDC); added DrawHPAPInfo(pDC);

Just below add:

    void ZCombatInterface::DrawHPAPInfo(MDrawContext* pDC)
    {
        ZCharacter* pCharacter = GetTargetCharacter();

        if (pCharacter == NULL || pCharacter->IsObserverTarget())
            return;

        float fRx = (float)MGetWorkspaceWidth();
        float fRy = (float)MGetWorkspaceHeight();

        float fX = (155.0f / 1024.0f) * fRx;
        float fY = (30.0f / 768.0f) * fRy;
        float fY_AP = (34.0f / 768.0f) * fRy;

        char szMsg[128] = { 0, };
        pDC->SetFont(GetGameFont());
        MFont *pFont = MFontManager::Get("FONTa6_O2Wht");

        if (pFont == NULL)
            pDC->SetFont(GetFont());
        else
            pDC->SetFont(pFont);

        pDC->SetColor(MCOLOR(0xFFFFFFFF));
        pDC->SetOpacity(255);
        {
        if (ZGetGame())
        {
        pDC->SetFont(MFontManager::Get("FONTHP"));
        char szMsg[70];
        int hp = (int)pCharacter->GetHP();
        if (hp <= 1 && !pCharacter->IsDie()) hp = 1;
        sprintf(szMsg, " %d", hp,(int)pCharacter->GetMaxHP());
        pDC->SetColor(MCOLOR(0xFF1E90FF));
        TextRelative(pDC, 30.f / 800.f, 18.f / 600.f, szMsg);
        pDC->SetFont(MFontManager::Get("FONTAP"));
        sprintf(szMsg, " %d",(int)pCharacter->GetAP());
        pDC->SetColor(MCOLOR(0xFFFF0000));
        TextRelative(pDC, 40.f / 800.f, 48.f / 600.f, szMsg);
        }
        pDC->SetFont(GetGameFont());
        }

    }
    
Now let's ZCombatInterface.h: We look for: void DrawMyNamePont(MDrawContext* pDC);
Underneath added: 

    void DrawHPAPInfo(MDrawContext* pDC);

    
