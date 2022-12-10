Killcam & hpap clanwar <br>
Open(ZGame.cpp) <br>
Find <br>
  
    if(pCharacter==m_pMyCharacter)


Replace <br>

	if(pCharacter==m_pMyCharacter)
	{
		//Killcam
		MMATCH_GAMETYPE gametype = ZGetGameClient()->GetMatchStageSetting()->GetGameType();
		if (gametype == MMATCH_GAMETYPE_DEATHMATCH_SOLO || gametype == MMATCH_GAMETYPE_GLADIATOR_SOLO || gametype == MMATCH_GAMETYPE_TRAINING || gametype == MMATCH_GAMETYPE_BERSERKER)
			ZGetCombatInterface()->SetObserverMode(false);


		m_pMyCharacter->InitSpawn();

		if( isRespawn )	{
			ZGetSoundEngine()->PlaySound("fx_respawn");
		} else {
			ZGetSoundEngine()->PlaySound("fx_whoosh02");
		}

		ZGetScreenEffectManager()->ReSetHpPanel();// hppanel_ani
	}

Find <br>

	else if (pVictim == m_pMyCharacter)
	{
  
Replace <br>


	else if (pVictim == m_pMyCharacter)
	{

		//hpap clanwar
		if (pAttacker && !ZGetGameClient()->IsLadderGame())
		{
			char szTemp[128];
			sprintf(szTemp, " (HP: %.0f/%.0f, AP: %.0f/%.0f)", pAttacker->GetHP(), pAttacker->GetMaxHP(), pAttacker->GetAP(), pAttacker->GetMaxAP());
			ZTransMsg(szMsg, MSG_GAME_LOSE_FROM_WHO, 1, szAttacker);
			strcat(szMsg, szTemp);
		}
		else
		{
			ZTransMsg(szMsg, MSG_GAME_LOSE_FROM_WHO, 1, szAttacker);
			ZChatOutput(MCOLOR(0xFFCF2020), szMsg);
		}
		//killcam
		MMATCH_GAMETYPE gametype = ZGetGameClient()->GetMatchStageSetting()->GetGameType();
		if (gametype == MMATCH_GAMETYPE_DEATHMATCH_SOLO || gametype == MMATCH_GAMETYPE_GLADIATOR_SOLO || gametype == MMATCH_GAMETYPE_TRAINING || gametype == MMATCH_GAMETYPE_BERSERKER)
		{
			ZGetCombatInterface()->SetObserverMode(true);
			ZGetCombatInterface()->GetObserver()->SetTarget(pAttacker->GetUID());
		}
	}















