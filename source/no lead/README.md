Open(MSharedCommandTable.cpp) <br>

Find: <br>

		C(MC_PEER_BUFF_INFO, "Peer.BuffInfo", "BuffInfo", MCDT_PEER2PEER)
			P(MPT_BLOB, "Info")

Add under <br>

	C(MC_PEER_NOLEAD, "Peer.NoLead", "NoLead", MCDT_PEER2PEER)
		P(MPT_UID, "Victim")
		P(MPT_UID, "Attacker")
		P(MPT_VECTOR, "Source")
		P(MPT_INT, "DamageType")
		P(MPT_INT, "WeaponType")
		P(MPT_FLOAT, "Damage")
		P(MPT_FLOAT, "PiercingRatio")
		P(MPT_INT, "MeleeType")


Open(MSharedCommandTable.h) <br>
Find <br>

    #define MC_PEER_BUFF_INFO			10056

Add under <br>

    #define MC_PEER_NOLEAD				50070



Open(ZCharacter.cpp) <br>

Find <br>

    void ZCharacter::OnDamaged(ZObject* pAttacker, rvector srcPos, ZDAMAGETYPE damageType, MMatchWeaponType weaponType, float fDamage, float fPiercingRatio, int nMeleeType)

Replace <br>

    void ZCharacter::OnDamaged(ZObject* pAttacker, rvector srcPos, ZDAMAGETYPE damageType, MMatchWeaponType weaponType, float fDamage, float fPiercingRatio, int nMeleeType)
    {
      if (m_bInitialized == false)
        PROTECT_DEBUG_REGISTER(m_bInitialized_DebugRegister == false)
        return;
      bool bDebugRegister = !IsVisible() || IsDie();
      if (!IsVisible() || IsDie())
        PROTECT_DEBUG_REGISTER(bDebugRegister)
        return;


      MMatchStageSetting* stageSetting = ZGetGameClient()->GetMatchStageSetting();
      if ((!strstr(ZGetGameClient()->GetChannelName(), "[LEAD]")) &&
        ((damageType == ZD_BULLET) || (damageType == ZD_BULLET_HEADSHOT)) &&
        (stageSetting->GetGameType() != MMATCH_GAMETYPE_QUEST) &&
        (stageSetting->GetGameType() != MMATCH_GAMETYPE_SURVIVAL) &&
        (pAttacker == ZGetGame()->m_pMyCharacter) &&
        (this != ZGetGame()->m_pMyCharacter)


        ) {


        ZPostNoLead(this->GetUID(), pAttacker->GetUID(), srcPos, damageType, weaponType, fDamage, fPiercingRatio, nMeleeType);
        fDamage = 0;
      }

      bool bCanAttack = ZGetGame()->CanAttack(pAttacker, this) || (pAttacker == this && (damageType == ZD_EXPLOSION || damageType == ZD_FALLING));
      bDebugRegister = ZGetGame()->CanAttack(pAttacker, this) || (pAttacker == this && (damageType == ZD_EXPLOSION || damageType == ZD_FALLING));
      bool bReturnValue = ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_DEATHMATCH_TEAM2;


      if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_DEATHMATCH_TEAM2)
      {
        PROTECT_DEBUG_REGISTER(bReturnValue)
        {
          if (damageType != ZD_FALLING)
          {
            bCanAttack &= !isInvincible();
            bDebugRegister &= !isInvincible();
          }
        }
      }

      rvector dir = GetPosition() - srcPos;
      Normalize(dir);

      m_damageInfo.CheckCrc();
      m_damageInfo.Ref().m_LastDamageDir = dir;
      m_damageInfo.Ref().m_LastDamageType = damageType;
      m_damageInfo.Ref().m_LastDamageWeapon = weaponType;
      m_damageInfo.Ref().m_LastDamageDot = DotProduct(m_Direction, dir);
      m_damageInfo.Ref().m_LastDamageDistance = Magnitude(GetPosition() - srcPos);
      m_damageInfo.MakeCrc();

      if (!bCanAttack)
        PROTECT_DEBUG_REGISTER(!bDebugRegister)
        return;

      ZObject::OnDamaged(pAttacker, srcPos, damageType, weaponType, fDamage, fPiercingRatio, nMeleeType);


      if (damageType == ZD_MELEE) OnDamagedAnimation(pAttacker, nMeleeType);


      m_dwStatusBitPackingValue.Ref().m_bDamaged = true;


    #ifdef _CHATOUTPUT_ENABLE_CHAR_DAMAGE_INFO_
      char szDamagePrint[256];
      sprintf(szDamagePrint, "%s??°? ??????[%2.1f], ???? HP[%2.1f] AP[%2.1f]", GetUserName(), fDamage, GetHP(), GetAP());
      ZChatOutput(MCOLOR(255, 100, 100), szDamagePrint);
    #endif 
    }


Open(ZGame.cpp) <br>

Find <br>

    case MC_PEER_CHANGE_PARTS:

Add under <br>

	case MC_PEER_NOLEAD:
	{
		MUID victim, attacker;
		D3DXVECTOR3 source;
		int damageType, weaponType;
		float damage, piercingRatio;
		int meleeType;


		pCommand->GetParameter(&victim, 0, MPT_UID);
		pCommand->GetParameter(&attacker, 1, MPT_UID);
		pCommand->GetParameter(&source, 2, MPT_VECTOR);
		pCommand->GetParameter(&damageType, 3, MPT_INT);
		pCommand->GetParameter(&weaponType, 4, MPT_INT);
		pCommand->GetParameter(&damage, 5, MPT_FLOAT);
		pCommand->GetParameter(&piercingRatio, 6, MPT_FLOAT);
		pCommand->GetParameter(&meleeType, 7, MPT_INT);


		if (pCommand->GetSenderUID() != ZGetMyUID())
			OnNoLead(victim, attacker, source, (ZDAMAGETYPE)damageType, (MMatchWeaponType)weaponType, damage, piercingRatio, meleeType);
	}
	break;

Find <br>

    void ZGame::OnChangeParts(MUID& uid,int partstype,int PartsID)


Add under <br>

    void ZGame::OnNoLead(MUID victim, MUID attacker, rvector srcPos, ZDAMAGETYPE damageType, MMatchWeaponType weaponType, float fDamage, float fPiercingRatio, int nMeleeType)
    {
      ZCharacter* pVictim = m_CharacterManager.Find(victim);
      ZCharacter* pAttacker = m_CharacterManager.Find(attacker);


      if ((pVictim == NULL) || (pAttacker == NULL))
        return;


      if (victim != ZGetMyUID())
        return;


      pVictim->OnDamaged(pAttacker, srcPos, damageType, weaponType, fDamage, fPiercingRatio, nMeleeType);
    }


Open(ZGame.h) <br>
Find <br>

    void OnChangeParts(MUID& uid,int partstype,int PartsID);


Add under <br>

	void OnNoLead(MUID victim, MUID attacker, rvector srcPos, ZDAMAGETYPE damageType, MMatchWeaponType weaponType, float fDamage, float fPiercingRatio, int nMeleeType);


Open(ZPost.h) <br>
Find <br>

    inline void ZPostNPCSkillExecute(MUID uidOwner, int nSkill, MUID uidTarget, rvector& targetPos)
    {
      ZPOSTCMD4(MC_QUEST_PEER_NPC_SKILL_EXECUTE, MCommandParameterUID(uidOwner), MCommandParameterInt(nSkill), MCommandParameterUID(uidTarget), MCommandParameterPos(targetPos.x,targetPos.y,targetPos.z) );
    }

Add under <br>

    inline void ZPostNoLead(MUID victim, MUID attacker, rvector source, int damageType, int weaponType, float damage, float piercingRatio, int meleeType)
    {
      ZPOSTCMD7(MC_PEER_NOLEAD,
        MCommandParameterUID(victim),
        MCommandParameterUID(attacker),
        MCommandParameterVector(source.x, source.y, source.z),
        MCommandParameterInt(damageType),
        MCommandParameterInt(weaponType),
        MCommandParameterFloat(damage),
        MCommandParameterFloat(piercingRatio),
        MCommandParameterInt(meleeType));
    }




Rebuild Gunz & MatchServer. <br>
