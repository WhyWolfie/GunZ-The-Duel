Command: admin_pauze (/pauze) <br>

Open(ZChat_Cmds.cpp) <br>

    void ChatCmd_AdminBoss(const char* line, const int argc, char** const argv);

Part 2

    _CC_AC("pause", &ChatCmd_AdminBoss, CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/pause", "");

Part 3

    void ChatCmd_AdminBoss(const char* line, const int argc, char** const argv)
    {
      if (argc < 2)
      {
        OutputCmdWrongArgument(argv[0]);
        return;
      }

      int nTime = 0;

      char* pszTime = argv[1];
      nTime = atoi(pszTime);

      if (nTime == 0 || nTime == 1)
        ZPostChangeBoss(nTime);
    }


Open(ZPost.h)

    inline void ZPostChangeBoss(int State)
    {
      ZPOSTCMD1(MC_PEER_CHANGE_BOSS, MCmdParamInt(State));
    }


Open(MSharedCommandTable.h)

    #define MC_PEER_CHANGE_BOSS						50069


Open(MSharedCommandTable.cpp)

		C(MC_PEER_CHANGE_BOSS, "Peer.BossUID", "BossID", MCDT_PEER2PEER)
			P(MPT_INT, "State");

Open(ZGame.cpp)

		case MC_PEER_CHANGE_BOSS:
		{
			MUID uidAdmin = MUID(0,0);
			ZCharacter* pAdmin = NULL;

			if (ZGetGame() && ZGetGame()->m_pMyCharacter && (ZGetGame()->m_pMyCharacter->IsAdmin() || ZGetGame()->m_pMyCharacter->IsGM() || ZGetGame()->m_pMyCharacter->IsEventMaster()))
				break;

			if(!ZGetCharacterManager()) 
				break;

			uidAdmin = pCommand->GetSenderUID();
			pAdmin = ZGetCharacterManager()->Find(uidAdmin);
			if(pAdmin == NULL)
				break;

			if((!IsAdminGrade(pAdmin->GetCharInfo()->nUGradeID)) && (!IsEventMasterGrade(pAdmin->GetCharInfo()->nUGradeID))) 
				break;

			int state = 0;
			pCommand->GetParameter(&state, 0, MPT_INT);

			m_likeBoss = (bool)state;
			if (m_pMyCharacter)
				rStuckPos = m_pMyCharacter->GetPosition();
		}
		break;

Open(ZCamera.cpp - Replace)

    void ZCamera::Update(float fElapsed)
    {
      if (ZGetGame() == NULL) return;
 
      if (ZGetGame()->m_likeBoss == true)
        return;
 
 Open(ZCharacter.cpp - Replace)
 
     void ZCharacter::OnUpdate(float fDelta)
    {
      if (m_bInitialized==false) return;
      if (!IsVisible()) return;

      if (ZGetGame()->m_likeBoss)
        return;
 
 Open(ZCombatInterface.cpp - Add under ZGetScreenEffectManager()->Draw();)

    if (ZGetGame()->m_likeBoss)
    {
      char paused[128];

      MFont* pFont = GetGameFont();
      pFont = MFontManager::Get("FONTa10_O2Wht");
      pDC->SetFont(pFont);
      pDC->SetColor(MCOLOR(0xFFFFFFFF));

      sprintf(paused, "Game Paused // Juego Pausado // Jogo Pausado");
      TextRelative(pDC, 400.f / 800.f, 300.f / 600.f, paused);
    }

Open(ZGame.cpp - Find: ZGame::ZGame())

	m_bossMUID = MUID(0, 0);
	m_likeBoss = false;
	rStuckPos = rvector(0, 0, 0);

Find (vShots.size() > 0 && !ZGetGameInterface()  & Replace it)

	if (vShots.size() > 0 && !ZGetGameInterface()->GetCombatInterface()->GetObserverMode())
	{
		if (ZGetGame() && !ZGetGame()->m_likeBoss)
		{
			ZCharacter* pCharacter = (ZCharacter*)ZGetCharacterManager()->Find(MUID(0, vShots[0]->nLowId));
			if (pCharacter && pOwnerCharacter->GetUID().Low == ZGetGameClient()->GetPlayerUID().Low)
			{
				if (!GetMatch()->IsTeamPlay())
				{
					pCharacter->OnDamagedAPlayer(pOwnerCharacter, vShots);
				}
				else if (GetMatch()->IsTeamPlay() && ZGetGame()->GetMatch()->GetTeamKillEnabled() && pCharacter->IsTeam(pOwnerCharacter))
				{
					pCharacter->OnDamagedAPlayer(pOwnerCharacter, vShots);
				}
				else if (GetMatch()->IsTeamPlay() && !pCharacter->IsTeam(pOwnerCharacter))
				{
					pCharacter->OnDamagedAPlayer(pOwnerCharacter, vShots);
				}
			}
		}

		vShots.clear();
	}

Open(ZGame.h) & (Find: bool IsExceptedFromNpcTargetting - Add under)

	MUID m_bossMUID;
	bool m_likeBoss;
	rvector rStuckPos;

Open(ZMyCharacter.cpp) & Find(_BP("ZMyCharacter::Update");)

	if (ZGetGame()->m_likeBoss)
		return;
    
Find(uStatus.m_bPlayDone_upper= pAniUp->m_pAniSet==NULL ? false : pAniUp->m_isPlayDone; - Add under)

		if (ZGetGame()->m_likeBoss)
			SetPosition(ZGetGame()->rStuckPos);

Find (pickinfo.pObject->IsNPC() == true || strstr(ZGetGameClient()->GetChannelName(), "Lead") & Replace)

    if (pickinfo.pObject->IsNPC() == true || strstr(ZGetGameClient()->GetChannelName(), "Lead") || (ZGetGame() && !ZGetGame()->m_likeBoss)) //Pause Command
    {
      pickinfo.pObject->OnDamaged(pOwner, pOwner->GetPosition(), dt, pDesc->m_nWeaponType.Ref(), fActualDamage, fRatio );
    }


