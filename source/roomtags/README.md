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
    
[SGO] = Shotgun Only. My style <br>
So here it is. <br>
Find on ZCharacterItem <br>

	case MMCIP_PRIMARY:
	case MMCIP_SECONDARY:
	{
	if (pDesc->m_nType.Ref() != MMIT_RANGE)
	{
	return false;
	}
	}
	break;
	
Replace to :

    case MMCIP_PRIMARY:
    case MMCIP_SECONDARY:
    {
        if (pDesc->m_nType.Ref() != MMIT_RANGE)
        {
            return false;
        }
        if ((strstr(ZGetGameClient()->GetStageName(), "[sgo]")) || (strstr(ZGetGameClient()->GetStageName(), "[SGO]")))
        {
            MMatchWeaponType pItem = pDesc->m_nWeaponType.Ref();
            if (pItem > 0 && pItem < 18)
            {
                if (pItem != MWT_SHOTGUN)
                    return false;
            }
        }
    }
    break; 
    
Find: ZMyCharacter::WallJump2 [walljump] - random high walljumps<br> 
Add under
    
    	if(strstr(ZGetGameClient()->GetStageName(), "[walljump]"))
	{
		int i = rand() % 6 + 1;

		float fSecondJumpSpeed = WALL_JUMP2_SIDE_VELOCITY;

		rvector right;
		CrossProduct(&right,m_Direction,rvector(0,0,1));

		AddVelocity(rvector(0,0,800));
		
		switch(i)
		{
		case 1:
		case 5:
			m_nWallJump2Dir=7;
			AddVelocity(rvector(0,0,1000));
			break;
		case 2:
		case 6:
			m_nWallJump2Dir=6;
			AddVelocity(rvector(0,0,1000));
			break;
		case 3:
			m_nWallJump2Dir=4;
			AddVelocity(fSecondJumpSpeed*-right);
			AddVelocity(rvector(0,0,1300));
			break;
		case 4:
			m_nWallJump2Dir=5;
			AddVelocity(fSecondJumpSpeed*right);
			AddVelocity(rvector(0,0,1300));
			break;
		}
	}

Find ZModule_Movable::UpdateGravity [gravity] - Gravity <br>
and replace <br>

	void ZModule_Movable::UpdateGravity(float fDelta)
	{
		if(strstr(ZGetGameClient()->GetStageName(),"[gravity]"))
	{
		m_Velocity.z = 
			max( m_Velocity.z - GRAVITY_LOW*fDelta,-MAX_FALL_SPEED);
	}
		else
		{
		m_Velocity.z = 
			max( m_Velocity.z - GRAVITY_CONSTANT*fDelta,-MAX_FALL_SPEED);
		}
	}

Find #define COLLISION_DIST <br>
add under <br>

	#define GRAVITY_LOW     			500.f
	

[ESP] <br>
Find void ZCombatInterface::OnDraw(MDrawContext* pDC) <br>

	if(strstr(ZGetGameClient()->GetStageName(),"[ESP]"))
	{
		bDrawAllPlayerName = true;
		DrawAllPlayerName(pDC);
	}

[NF] - No Flip Tag <br>

Find case ZDW_UPPERCUT & replace (ZMyCharacter.cpp) <br>

	case ZDW_UPPERCUT :
		if(strstr(ZGetGameClient()->GetStageName(),"[NF]"))
				{
					/*if(zStatus.m_bSkill) {
			MMatchWeaponType type = MWT_NONE;

			int sel_type = GetItems()->GetSelectedWeaponParts();
			ZItem* pSItem = GetItems()->GetSelectedWeapon();

			if(pSItem && pSItem->GetDesc())
				type = pSItem->GetDesc()->m_nWeaponType.Ref();

			if(type == MWT_KATANA || type == MWT_DOUBLE_KATANA ) {
				ZPostSkill( /*g_pGame->GetTime(),*//* ZC_SKILL_UPPERCUT , sel_type );
			}
		}*/
		}
		else
							{
		if(zStatus.m_bSkill) {
			MMatchWeaponType type = MWT_NONE;

			int sel_type = GetItems()->GetSelectedWeaponParts();
			ZItem* pSItem = GetItems()->GetSelectedWeapon();

			if(pSItem && pSItem->GetDesc())
				type = pSItem->GetDesc()->m_nWeaponType.Ref();

			if(type == MWT_KATANA || type == MWT_DOUBLE_KATANA ) {
				ZPostSkill( /*g_pGame->GetTime(),*/ ZC_SKILL_UPPERCUT , sel_type );
			}
		}
	}
	break;

[TELE] or [tele] - Teleport (great for skillmaping) - Add at under: ZGameInput::OnEvent -> rvector PlayerPosHotKey; <br>

		case VK_NUMPAD1: 
		{
			if (strstr(ZGetGameClient()->GetStageName(), "[TELE]") || strstr(ZGetGameClient()->GetStageName(), "[tele]"))
				PlayerPosHotKey = pMyCharacter->GetPosition();
		}
		 return true;
		case VK_NUMPAD2: 
		{
			if (strstr(ZGetGameClient()->GetStageName(), "[TELE]") || strstr(ZGetGameClient()->GetStageName(), "[tele]"))
				pMyCharacter->SetPosition(PlayerPosHotKey);
		}
		  return true;

[WF] - Wireframe RoomTag. <br>
Find(ZGame.cpp) <br>

	if(ZGetGameInterface()->GetCombatInterface()->GetObserverMode() || m_bReplaying.Ref())
		OnObserverRun();

	ProcessDelayedCommand();

Add under <br>

	if (StrStrI(ZGetGameClient()->GetStageName(), "[WF]"))
	{
		m_bShowWireframe = true;
	}
	else
		m_bShowWireframe = false;


[noclothes] - no clothes in rooms <br>
Find(ZGame.cpp) <br>

	bool ZGame::Create(MZFileSystem *pfs, ZLoadingProgress *pLoading )
	{

Place under <br>

	if (StrStrI(ZGetGameClient()->GetStageName(), "[noclothes]"))
	{
		ZPostRequestTakeoffItem(ZGetGameClient()->GetPlayerUID(), MMCIP_HEAD);
		ZPostRequestTakeoffItem(ZGetGameClient()->GetPlayerUID(), MMCIP_CHEST);
		ZPostRequestTakeoffItem(ZGetGameClient()->GetPlayerUID(), MMCIP_HANDS);
		ZPostRequestTakeoffItem(ZGetGameClient()->GetPlayerUID(), MMCIP_LEGS);
		ZPostRequestTakeoffItem(ZGetGameClient()->GetPlayerUID(), MMCIP_FEET);
		ZPostRequestTakeoffItem(ZGetGameClient()->GetPlayerUID(), MMCIP_MELEE);
		ZPostRequestTakeoffItem(ZGetGameClient()->GetPlayerUID(), MMCIP_PRIMARY);
		ZPostRequestTakeoffItem(ZGetGameClient()->GetPlayerUID(), MMCIP_SECONDARY);
		ZPostRequestTakeoffItem(ZGetGameClient()->GetPlayerUID(), MMCIP_FINGERL);
		ZPostRequestTakeoffItem(ZGetGameClient()->GetPlayerUID(), MMCIP_FINGERR);
		ZPostRequestTakeoffItem(ZGetGameClient()->GetPlayerUID(), MMCIP_CUSTOM1);
		ZPostRequestTakeoffItem(ZGetGameClient()->GetPlayerUID(), MMCIP_CUSTOM2);
	}







