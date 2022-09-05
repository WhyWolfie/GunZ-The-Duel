Open (ZMyCharacter.cpp) <br>
Find

		if(!uStatus.m_bWallJump && !uStatus.m_bTumble && !zStatus.m_bSkill && !zStatus.m_bMoveLimit && 
			!uStatus.m_bBlast && !uStatus.m_bBlastFall && !uStatus.m_bBlastAirmove && !(m_bCharging->Ref()) && //mmemory proxy
			!zStatus.m_bSlash && !zStatus.m_bJumpSlash && !zStatus.m_bJumpSlashLanding)
		{
			if(ZIsActionKeyPressed(ZACTION_FORWARD)==true)	m_Accel.Set_CheckCrc(m_Accel.Ref()+forward);
			if(ZIsActionKeyPressed(ZACTION_BACK)==true)		m_Accel.Set_CheckCrc(m_Accel.Ref()-forward);
			if(ZIsActionKeyPressed(ZACTION_LEFT)==true)		m_Accel.Set_CheckCrc(m_Accel.Ref()-right);
			if(ZIsActionKeyPressed(ZACTION_RIGHT)==true)	m_Accel.Set_CheckCrc(m_Accel.Ref()+right);
		}
    
Replace

		if(!uStatus.m_bWallJump && !uStatus.m_bTumble && !zStatus.m_bSkill && !zStatus.m_bMoveLimit &&
			!uStatus.m_bBlast && !uStatus.m_bBlastFall && !uStatus.m_bBlastAirmove /*&& !(m_bCharging->Ref())*/ && //mmemory proxy
			!zStatus.m_bSlash && !zStatus.m_bJumpSlash && !zStatus.m_bJumpSlashLanding)
		{
			if(ZIsActionKeyPressed(ZACTION_FORWARD)==true)	m_Accel.Set_CheckCrc(m_Accel.Ref()+forward);
			if(ZIsActionKeyPressed(ZACTION_BACK)==true)		m_Accel.Set_CheckCrc(m_Accel.Ref()-forward);
			if(ZIsActionKeyPressed(ZACTION_LEFT)==true)		m_Accel.Set_CheckCrc(m_Accel.Ref()-right);
			if(ZIsActionKeyPressed(ZACTION_RIGHT)==true)	m_Accel.Set_CheckCrc(m_Accel.Ref()+right);
		}
