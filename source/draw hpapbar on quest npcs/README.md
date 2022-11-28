Open(ZCombatInterface.h) <br>
Find: <br>

    void DrawNPCName(MDrawContext* pDC);

Add under

    void DrawHPAPNPC(MDrawContext* pDC);

Open(ZCombatInterface.cpp) <br>
Find: <br>

    DrawMyWeaponPont(pDC);

Add under

    DrawHPAPNPC(pDC);

Find: <br>

    void ZCombatInterface::DrawNPCName(MDrawContext* pDC)

Add under <br>

    void ZCombatInterface::DrawHPAPNPC(MDrawContext* pDC)
    {
      for (ZObjectManager::iterator itor = ZGetObjectManager()->begin();
        itor != ZGetObjectManager()->end(); ++itor)
      {
        rvector pos, screen_pos;
        ZObject* pObject = (*itor).second;
        ZActor* pActor = (ZActor*)pObject;
        if (!pObject->IsVisible()) continue;
        if (pObject->IsDie()) continue;
        if (!pObject->IsNPC()) continue;

        pos = pObject->GetPosition();
        RVisualMesh* pVMesh = pObject->m_pVMesh;
        RealSpace2::rboundingbox box;

        if (pVMesh == NULL) continue;

        box.vmax = pos + rvector(50.f, 50.f, 190.f);
        box.vmin = pos + rvector(-50.f, -50.f, 0.f);

        if (isInViewFrustum(&box, RGetViewFrustum()))
        {
          screen_pos = RGetTransformCoord(pVMesh->GetHeadPosition() + rvector(0, 0, 35.f));

          MFont* pFont = NULL;
          pFont = pActor->CheckFlag(AF_MY_CONTROL) ? MFontManager::Get("FONTa12_O1Blr") : MFontManager::Get("FONTa12_O1Red");
          pDC->SetColor(MCOLOR(0xFFFF0000));
          pDC->SetBitmap(NULL);
          pDC->SetFont(pFont);

          int x = screen_pos.x - pDC->GetFont()->GetWidth(pActor->m_szOwner) / 2;

          MCOLOR color;
          const int BAR_HEIGHT = 4;
          const int BAR_WIDTH = 70;

          int nMax = pActor->GetActualMaxHP();
          int nCurr = min(pActor->GetActualHP(), nMax);

          int nHP = nCurr;
          if (nHP == 0 && !pActor->IsDie())
            nHP += 1;
          int bar_hp_width = (int)(BAR_WIDTH * ((int)nHP / nMax));
          color = MCOLOR(0xFF0091FF);
          int screeny = screen_pos.y - 50;
          int screenx = x;
          int bar_y = screeny + pFont->GetHeight() + 2;
          pDC->SetColor(color);
          pDC->FillRectangle(screenx, bar_y, bar_hp_width, BAR_HEIGHT);
          pDC->Rectangle(screenx, bar_y, BAR_WIDTH, BAR_HEIGHT);
        }
      }
    }

![1](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/draw%20hpapbar%20on%20quest%20npcs/1.jpg)

![2](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/draw%20hpapbar%20on%20quest%20npcs/2.jpg)

![3](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/draw%20hpapbar%20on%20quest%20npcs/3.jpg)




Credits to ZER0NIS
