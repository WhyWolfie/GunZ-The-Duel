Open(ZMyCharacter.cpp) <br>
Find <br>

	if( m_pVMesh->m_SelectWeaponMotionType==eq_ws_dagger )
	{ // dagger
		if(m_AniState_Upper.Ref()==ZC_STATE_UPPER_SHOT)
			return;
      
Replace <br>

	if( m_pVMesh->m_SelectWeaponMotionType==eq_wd_dagger ||
		m_pVMesh->m_SelectWeaponMotionType==eq_ws_dagger ) 
	{ // dagger
		if(m_AniState_Upper.Ref()==ZC_STATE_UPPER_SHOT)
			return;

Find <br>

    void ZMyCharacter::ProcessDelayedWork()

Replace <br>

    void ZMyCharacter::ProcessDelayedWork()
    {
      //Iterator increment fix
      for (ZDELAYEDWORKLIST::iterator i = m_DelayedWorkList.begin(); i != m_DelayedWorkList.end();)
      {
        ZDELAYEDWORKITEM *pItem = *i;

        if (ZGetGame()->GetTime() > pItem->fTime)
        {
          OnDelayedWork(pItem);
          i = m_DelayedWorkList.erase(i);
          delete pItem;
        }
        else
          ++i;
      }
    }

Find <br>

    float ZMyCharacter::GetGravityConst()

Replace <br>

    float ZMyCharacter::GetGravityConst()
    {
      ZCharaterStatusBitPacking & uStatus = m_dwStatusBitPackingValue.Ref();
      ZMyCharaterStatusBitPacking & zStatus = m_statusFlags.Ref();

      if(zStatus.m_bWallHang && zStatus.m_bHangSuccess) return 0;
      if(zStatus.m_bShot) return 0;

      if(uStatus.m_bBlastFall) return .7f;

      if(uStatus.m_bWallJump)
      {
        if(m_nWallJumpDir.Ref()==1 || GetVelocity().z<0)
          return 0;
        else
          return .1f;
      }

      if(zStatus.m_bSlash)
      {
        //Bug fix (No item crash)
        if (GetItems()->GetItem(MMCIP_MELEE) == NULL)
        {
          return 1.f;
        }

        MMatchItemDesc *pDesc = GetItems()->GetItem(MMCIP_MELEE)->GetDesc();
        //Bug fix (pDesc NULL check)
        if (pDesc != NULL && pDesc->m_nWeaponType.Ref()==MWT_DOUBLE_KATANA) {
          AniFrameInfo* pAniLow = m_pVMesh->GetFrameInfo(ani_mode_lower);
          if( pAniLow->m_nFrame < 160*11) return 0;
        }
      }

      if(zStatus.m_bSkill) {
        //Bug fix (No item crash)
        if (GetItems()->GetItem(MMCIP_MELEE) == NULL)
        {
          return 1.f;
        }

        MMatchItemDesc *pDesc = GetItems()->GetItem(MMCIP_MELEE)->GetDesc();
        //Bug fix (pDesc NULL check)
        if (pDesc != NULL && pDesc->m_nWeaponType.Ref() == MWT_DOUBLE_KATANA) {
          AniFrameInfo* pAniLow = m_pVMesh->GetFrameInfo(ani_mode_lower);
          if (pAniLow->m_nFrame < 160 * 20) return 0;
        }
      }

      return 1.f;
    }
















