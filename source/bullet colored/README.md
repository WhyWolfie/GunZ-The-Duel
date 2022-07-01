<b> bullet colored </b> <br>
![map](https://i.imgur.com/mMVqkfp.png) <br>

[search these in ZCombatInterface.cpp]

      MMatchCharItemParts nParts = pCharacter->GetItems()->GetSelectedWeaponParts();
      if (nParts != MMCIP_MELEE && nParts < MMCIP_END)
      {
          sprintf(buffer, "%d / %d", m_nBulletCurrMagazine, m_nBulletSpare);
          TextRelative(pDC, 720.f / 800.f, 585.f / 600.f, buffer);
      } 

[replace to]

      MMatchCharItemParts nParts = pCharacter->GetItems()->GetSelectedWeaponParts();
      if (nParts != MMCIP_MELEE && nParts < MMCIP_END)
      {
          float ColorBullet = (float)m_nBulletCurrMagazine / (float)pCharacter->GetStatus().Ref().nMaxCurrBullet * 100;
          float ColorBullet2 = 0.10 * m_nBulletCurrMagazine / pCharacter->GetStatus().Ref().nMaxCurrBullet;
          if (ColorBullet == 60 || ColorBullet == 55 || ColorBullet >= 45)
              pDC->SetColor(MCOLOR(0xFFFFFFFF));
          else if (ColorBullet >= 35)
              pDC->SetColor(MCOLOR(0xFFFFF000));
          else if (ColorBullet >= 25)
              pDC->SetColor(MCOLOR(0xFFFFF000));
          else if (ColorBullet >= 15)
              pDC->SetColor(MCOLOR(0xFFFF0000));
          else if (ColorBullet >= 5)
              pDC->SetColor(MCOLOR(0xFFFF0000));
          else if (ColorBullet >= 2)
              pDC->SetColor(MCOLOR(0xFFFF0000));
          else if (ColorBullet >= 0)
              pDC->SetColor(MCOLOR(0xFFFF0000));
          else
              pDC->SetColor(MCOLOR(0xFFFFFFFF));
          pDC->FillRectangle((MGetWorkspaceWidth()), MGetWorkspaceHeight(), ColorBullet2 * MGetWorkspaceWidth(), 0);

          sprintf(buffer, "%d / %d", m_nBulletCurrMagazine, m_nBulletSpare);
          TextRelative(pDC, 720.f / 800.f, 585.f / 600.f, buffer);
      } 

[I forgot to tell you that declare nMaxCurrBullet in ZCharacter for "struct ZCharacterStatus"
example]

[example] <br>

      int nMaxCurrBullet 
      
      nMaxCurrBullet(0),
      
      
      
<b> Credits too Jorklenis2 </b>
      

