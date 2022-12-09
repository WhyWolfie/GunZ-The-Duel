Open(ZCombatInterface.h) <br>
Find <br>

    void		 DrawPont(MDrawContext* pDC);

Add under <br>

	void	     DrawClanMembersTextInfo(MDrawContext* pDC);


Find <br>

    void DrawEnemyName(MDrawContext* pDC);

Add under <br>

	void DrawAllClanName(MDrawContext* pDC);

Open(ZCombatInterface.cpp) <br>
Find <br>

    void ZCombatInterface::DrawMyNamePont

Add under <br>

    void HpApBarRelative(MDrawContext* pDC, float x, float y, float min, float max, MCOLOR Colour, int cy)
    {
      int width = 50;
      pDC->SetColor( MCOLOR( 0x30000000));
      pDC->FillRectangleW(x, y, width, cy);
      int nValue = (width * (min / max));
      pDC->SetColor( MCOLOR(Colour));
      pDC->FillRectangleW( x, y+1, -width+nValue, cy);

    #ifndef _EXTRESOLUTION
      if (RGetIsWidthScreen())
        x = (x * 800 + 80) / 960.f;
    #endif
      /*int screenx = x*MGetWorkspaceWidth();
      pDC->SetColor(MCOLOR(0x30000000));
      pDC->FillRectangleW(screenx, y*MGetWorkspaceHeight(), 0.08*MGetWorkspaceWidth(), cy);
      float nValue = (0.08 * (min / max));
      pDC->SetColor(Colour);
      pDC->FillRectangleW(screenx, y*MGetWorkspaceHeight() + 1, nValue*MGetWorkspaceWidth(), cy);*/

    }

    void ZCombatInterface::DrawClanMembersTextInfo(MDrawContext* pDC)
    {
      if (ZGetConfiguration()->GetExtra()->bHPAPScoreboard)
      {
        ZCharacter* mCharacter = GetTargetCharacter();
        if (mCharacter == NULL || mCharacter->IsObserverTarget() || ZGetGameClient()->IsLadderGame() == false && ZGetGameClient()->IsPlayerWars() == false)
          return;
        MFont* pFont = GetGameFont();
        pDC->SetFont(pFont);
        float Width = 260.f, HeightMod = 0.f;
        int Counter = 0;
        for (ZCharacterManager::iterator itor = ZGetCharacterManager()->begin(); itor != ZGetCharacterManager()->end(); ++itor)
        {
          ZCharacter* pCharacter = (*itor).second;
          if (mCharacter->GetUID() == pCharacter->GetUID()) continue;
          if (pCharacter && !pCharacter->IsDie() && mCharacter->IsTeam(pCharacter))
          {
            pDC->SetColor(MCOLOR(0xFFFFFFFF));
            TextRelative(pDC, Width / 800.f, (HeightMod + 6.f) / 600.f, pCharacter->GetCharInfo()->szName);
            HpApBarRelative(pDC, Width / 800.f, (HeightMod + 18.f) / 600.f, pCharacter->GetHP(), pCharacter->GetMaxHP(), MCOLOR(0xFFFF0000), 7);
            HpApBarRelative(pDC, Width / 800.f, (HeightMod + 24.f) / 600.f, pCharacter->GetAP(), pCharacter->GetMaxAP(), MCOLOR(0xFF0087FF), 3);
            Width += 65.f;
            Counter++;
            if (Counter == 4)
            {
              Width = 260.f;
              HeightMod += 35.f;
              Counter = 0;
            }
          }
        }
      }
    }

    void ZCombatInterface::DrawAllClanName(MDrawContext* pDC)
    {
      if (!ZGetGame()->m_pMyCharacter->IsAdminName()) return;
      for (ZCharacterManager::iterator itor = ZGetGame()->m_CharacterManager.begin(); itor != ZGetGame()->m_CharacterManager.end(); ++itor)
      {
        rvector pos, screen_pos;
        ZCharacter* pCharacter = (*itor).second;
        if (!pCharacter->m_bRendered || !pCharacter->IsVisible()) continue;
        if (pCharacter->IsDie()) continue;
        pos = pCharacter->GetPosition();
        RVisualMesh* pVMesh = pCharacter->m_pVMesh;
        RealSpace2::rboundingbox box;
        if (pVMesh == NULL) continue;

        const float fIconSize = .2f;
        int nIconSize = fIconSize * MGetWorkspaceWidth();
        box.vmax = pos + rvector(50.f, 50.f, 190.f);
        box.vmin = pos + rvector(-50.f, -50.f, 0.f);
        if (isInViewFrustum(&box, RGetViewFrustum()))
        {
          if (ZGetCamera()->GetLookMode() == ZCAMERA_MINIMAP) {
            rvector pos = pCharacter->GetPosition();
            pos.z = 0;
            screen_pos = RGetTransformCoord(pos);
          }
          else
            screen_pos = RGetTransformCoord(pCharacter->GetVisualMesh()->GetBipTypePosition(eq_parts_pos_info_Spine2) + rvector(0, 0, 15));

          pDC->SetBitmap(NULL);
          char* text = "GunZ";
          int x = screen_pos.x - pDC->GetFont()->GetWidth(text) / 2;
          pDC->SetColor(0, 0, 0);
          pDC->Text(x, screen_pos.y - 12, text);
          MBitmap *pbmp = ZGetEmblemInterface()->GetClanEmblem(pCharacter->GetClanID());
          if (pbmp)
          {
            pDC->SetBitmap(pbmp);
            pDC->Draw(x, screen_pos.y - 17, nIconSize, nIconSize);
          }
        }
      }
    }




















