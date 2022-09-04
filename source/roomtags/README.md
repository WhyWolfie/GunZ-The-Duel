[R] - Instant Reload <br>
Open: ZGame.cpp and find -> void ZGame::OnPeerReload(MUID& uid)<br>

    void ZGame::OnPeerReload(MUID& uid)
    {
      ZCharacter* pCharacter = m_CharacterManager.Find(uid);
      //	if (uid == ZGetGameClient()->GetUID()) pCharacter = m_pMyCharacter;

      if (pCharacter == NULL || pCharacter->IsDie() ) return;

      // ÀÓ½Ã.. ¹º°¡ »óÃ¼¾Ö´Ï¸ÞÀÌ¼ÇÀÌ ÀÖÀ¸¸é Äµ½½.. ¸®·Îµå/¼¦ µûÀ§
      //	if(pCharacter->m_pVMesh->m_pAniSet[ani_mode_upper]!=NULL) return;

      // ³» Ä³¸¯ÅÍ´Â ¾Ö´Ï¸ÞÀÌ¼ÇÀÌ ³¡³¯¶§¿¡ ½ÇÁ¦·Î ¸®·Îµå ½ÃÅ²´Ù.
      if(pCharacter==m_pMyCharacter)
      {
        if(ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_QUEST && ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_SURVIVAL)
        {
          if(strstr(ZGetGameClient()->GetStageName(), "[R]") || strstr(ZGetGameClient()->GetStageName(), "[r]") || strstr(ZGetGameClient()->GetStageName(), "[reload]"))
            pCharacter->GetItems()->Reload();
        }
          m_pMyCharacter->Animation_Reload();
      }
      else
        OnReloadComplete(pCharacter);

      // Sound Effect
      if(pCharacter->GetItems()->GetSelectedWeapon()!=NULL) {
        rvector p = pCharacter->GetPosition()+rvector(0,0,160.f);
        ZApplication::GetSoundEngine()->PlaySEReload(pCharacter->GetItems()->GetSelectedWeapon()->GetDesc(), p.x, p.y, p.z, (pCharacter==m_pMyCharacter));
      }
    }
    
    
[IA] - Infinite Ammo  <br>
Open: ZItem.cpp and find -> bool ZItem::Reload()<br>

    bool ZItem::Reload()
    {
      if (m_pDesc == NULL)
      {
        //_ASSERT(0);
        return false;
      }
      //_ASSERT(GetItemType() == MMIT_RANGE);


      int nAddedBullet = m_pDesc->m_nMagazine.Ref() - m_nBulletCurrMagazine.Ref();
      if (nAddedBullet > m_nBulletSpare.Ref()) nAddedBullet = m_nBulletSpare.Ref();
      if (nAddedBullet <= 0) return false;

      m_nBulletCurrMagazine.Set_CheckCrc(m_nBulletCurrMagazine.Ref() + nAddedBullet);
      if(!strstr(strlwr((char*)ZGetGameClient()->GetStageName()), "[ia]"))
      {
        m_nBulletSpare.Set_CheckCrc(m_nBulletSpare.Ref() - nAddedBullet);
      }

      return true;
    }
    
F9 (showing HP/AP) <br>
Open: ZGameInput.cpp and find -> VK_F9

			case VK_F9:
				char szName[128];
				{
					if(ZGetGame()->GetMatch()->IsTeamPlay())
					{
						sprintf(szName, "!(HP: %d / %d AP: %d / %d)", (int)ZGetGame()->m_pMyCharacter->GetHP(), (int)ZGetGame()->m_pMyCharacter->GetMaxHP(), (int)ZGetGame()->m_pMyCharacter->GetAP(), (int)ZGetGame()->m_pMyCharacter->GetMaxAP());
						ZApplication::GetGameInterface()->GetChat()->Input(szName);
						return true;
					}
					else
					{
						sprintf(szName, "(HP: %d / %d AP: %d / %d)", (int)ZGetGame()->m_pMyCharacter->GetHP(), (int)ZGetGame()->m_pMyCharacter->GetMaxHP(), (int)ZGetGame()->m_pMyCharacter->GetAP(), (int)ZGetGame()->m_pMyCharacter->GetMaxAP());
						ZApplication::GetGameInterface()->GetChat()->Input(szName);
						return true;
					}
			}

				return true;
    
    
