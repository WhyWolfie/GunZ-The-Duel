Open(ZMyCharacter.cpp) <br>
Find <br>

	// ´Ü°Ë
	if( m_pVMesh->m_SelectWeaponMotionType==eq_wd_dagger ||
		m_pVMesh->m_SelectWeaponMotionType==eq_ws_dagger ) 
	{ // dagger
		if(m_AniState_Upper.Ref()==ZC_STATE_UPPER_SHOT)
			return;

Replace <br>

	// ´Ü°Ë
	if( //m_pVMesh->m_SelectWeaponMotionType==eq_wd_dagger ||
		m_pVMesh->m_SelectWeaponMotionType==eq_ws_dagger ) 
	{ // dagger
		if(m_AniState_Upper.Ref()==ZC_STATE_UPPER_SHOT)
			return;
      
Or 

	// ´Ü°Ë
	if( //m_pVMesh->GetSelectWeaponMotionType()==eq_wd_dagger ||
		m_pVMesh->GetSelectWeaponMotionType()==eq_ws_dagger ) 
	{ // dagger
		if(m_AniState_Upper.Ref()==ZC_STATE_UPPER_SHOT)
			return;
