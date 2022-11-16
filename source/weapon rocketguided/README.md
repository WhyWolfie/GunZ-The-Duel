Not done yet.


Open(MMatchItem.h - enum MMatchRangeItemType)

    RIT_ROCKETGUIDED	= 12,

Find (enum MMatchWeaponType)

    MWT_ROCKETGUIDED,

Open(MMatchServer.h)

    void OnGuidedMissle(MUID Owner);
    MUID SelectTarget(const MUID& uidStage, const MUID& owner);

Open(MSharedCommandTable.h)

    #define MC_REQUEST_GUIDEDMISSLE					50063	// Request Guided Missle
    #define MC_RESPONSE_GUIDEDMISSLE				50064	// Response Guided Missle

Open(MMatchServer_OnCommand.cpp)

    case MC_REQUEST_GUIDEDMISSLE:
    {
    	//mlog("MC_REQUEST_GUIDEDMISSLE - MMatchServer_OnCommand.cpp\n");
      MUID Owner = pCommand->GetSenderUID();
      // pCommand->GetParameter(&Owner, 0, MPT_UID);
      OnGuidedMissle(Owner);
    }
    break;

Open(MMatchServer_Stage.cpp)

    MUID MMatchServer::SelectTarget(const MUID& uidStage, const MUID& owner)
    {
    	MMatchStage* pStage = FindStage(uidStage);
    	if (pStage == NULL) return MUID(0, 0);
    
    	if (pStage->GetObjCount() == 0)
    		return MUID(0, 0);
    
    	MMatchObject* pOwner = MMatchServer::GetInstance()->GetObject(owner);
    	if (pOwner == NULL)
    		return MUID(0, 0);
    
    	vector<MUID> vtCandidateUIDs;
    
    	for (MUIDRefCache::iterator itor = pStage->GetObjBegin(); itor != pStage->GetObjEnd(); itor++)
    	{
    		MMatchObject* pObj = (MMatchObject*)(*itor).second;
    		//if (stricmp(pObj->GetName(), pOwner->GetName() != 0))
    		//{
    		if (pObj->GetEnterBattle() == false) continue;
    		if (pObj->CheckAlive())
    		{
    			vtCandidateUIDs.push_back((*itor).first);
    		}
    		//}
    	}
    
    	// Probably this will never be size == 0 but for safe.
    	if (vtCandidateUIDs.size() == 0) return MUID(0, 0);
    
    	int nRand = rand() % vtCandidateUIDs.size();
    	return vtCandidateUIDs[nRand];
    }
    
    +void MMatchServer::OnGuidedMissle(MUID Owner)
    {
    	//mlog("OnGuidedMissle - MMatchServer_Stage.cpp\n");
    
    	MUID m_TargetID;
    
    	MMatchObject* pObj = GetObject(Owner);
    	if (pObj == NULL)
    		return;
    
    	MMatchStage* pStage = FindStage(pObj->GetStageUID());
    	if (pStage == NULL)
    		return;
    
    	if (pStage->GetState() != STAGE_STATE_RUN) return;
    
    	m_TargetID = SelectTarget(pStage->GetUID(), Owner);
    	mlog("OnGuidedMissle - MMatchServer_Stage.cpp - Target Name %s\n", pObj->GetName());
    
    	MCommand* pNew = CreateCommand(MC_RESPONSE_GUIDEDMISSLE, MUID(0, 0));
    	pNew->AddParameter(new MCommandParameterUID(Owner));
    	pNew->AddParameter(new MCommandParameterUID(m_TargetID));
    	RouteToStage(pStage->GetUID(), pNew);
     }

Open(MSharedCommandTable.cpp)


  	C(MC_REQUEST_GUIDEDMISSLE, "Request GuidedMissle", "RocketLauncher", MCDT_MACHINE2MACHINE)
  		P(MPT_UID, "Owner")
  
  	C(MC_RESPONSE_GUIDEDMISSLE, "Response GuidedMissle", "RocketLauncher", MCDT_MACHINE2MACHINE)
  		P(MPT_UID, "Owner")
  		P(MPT_UID, "Target")

Open(ZGame.cpp)


    void ZGame::OnGuidedMissle(MUID Owner, MUID Target)
    {
    	ZCharacter* pOwnerCharacter = NULL;
    	ZCharacter* pTargetCharacter = NULL;
    
    	pOwnerCharacter = (ZCharacter*)ZGetGame()->m_CharacterManager.Find(Owner);
    	pTargetCharacter = (ZCharacter*)ZGetGame()->m_CharacterManager.Find(Target);
    
    	if (pOwnerCharacter == NULL) return;
    	if (pTargetCharacter == NULL) return;
    
    	rvector pos = pOwnerCharacter->GetPosition();
    	rvector velocity = pOwnerCharacter->GetDirection();
    
    	pos.z += 125;
    
    	if ((Owner == Target) || (pOwnerCharacter->GetUID() == pTargetCharacter->GetUID()))
    		m_WeaponManager.AddRocket(pos, velocity, pOwnerCharacter);
    	else
    		m_WeaponManager.AddGuidedRocket(pos, velocity, pOwnerCharacter, pTargetCharacter);
     }


Open(ZGame.h)

    void OnGuidedMissle(MUID Owner, MUID Target);


Open(ZGameClient_OnCommand.cpp)


    case MC_RESPONSE_GUIDEDMISSLE:
  	{
  		MUID Owner, Target;
  
  			pCommand->GetParameter(&Owner, 0, MPT_UID);
  			pCommand->GetParameter(&Target, 1, MPT_UID);
  
  			if (ZGetGame() == NULL) break;
  
  			ZGetGame()->OnGuidedMissle(Owner, Target);
  
  		}
  		break;

Open(ZMyCharacter.cpp - ZMyCharacter::ProcessShot())
    
    else if (GetItems()->GetSelectedWeapon()->GetDesc()->m_nID == 4006)
    {
    	if (!GetItems()->GetSelectedWeapon()->Shot()) return;
    	ZPostGuidedMissle(ZGetMyUID());
    }

Open(ZPost.h)

    inline void ZPostGuidedMissle(MUID Target)
    {
      ZPOSTCMD1(MC_REQUEST_GUIDEDMISSLE,
        MCommandParameterUID(Target));
    }



















Credits to Nick.
