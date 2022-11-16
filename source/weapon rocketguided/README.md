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

Open(ZWeapon.cpp)

    /////////////////////////////////////////////////////////////////////////////
    // Guided Missle
    MImplementRTTI(ZWeaponGuidedRocket,ZMovingWeapon);
    ZWeaponGuidedRocket::ZWeaponGuidedRocket() :ZMovingWeapon() {

    }
    ZWeaponGuidedRocket::~ZWeaponGuidedRocket() {

    }
    void ZWeaponGuidedRocket::Create(RMesh* pMesh,rvector &pos, rvector &dir,ZObject* pOwner, ZObject* pCharacter) 
    {

        ZWeapon::Create(pMesh);

        m_Position=pos;
        m_Velocity=dir*ROCKET_VELOCITY_GUIDED;

        m_fStartTime = ZGetGame()->GetTime();
        m_fLastAddTime = ZGetGame()->GetTime();

        m_Dir=dir;
        m_Up=rvector(0,0,1);

        if(pCharacter == NULL)	
            return;

        m_uidTarget=pCharacter->GetUID();

        if(pOwner == NULL)	
            return;

        m_uidOwner=pOwner->GetUID();
        m_nTeamID=pOwner->GetTeamID();
        MMatchItemDesc* pDesc = NULL;

        if (pOwner->GetItems())
        {
            if (pOwner->GetItems()->GetSelectedWeapon())
            {
                pDesc = pOwner->GetItems()->GetSelectedWeapon()->GetDesc();
                //m_nItemParts = pOwner->GetItems()->GetSelectedWeaponParts();
            }
        }
        if (pDesc == NULL)
        {
            return;
        }

        m_fDamage=pDesc->m_nDamage.Ref();

        if( Z_VIDEO_DYNAMICLIGHT ) 
        {
            m_SLSid = ZGetStencilLight()->AddLightSource( m_Position, 2.0f );
        }
        CHECK_RETURN_CALLSTACK(Create);
    }
    bool ZWeaponGuidedRocket::Update(float fElapsedTime)
    {
        ZObject *pTargetO = ZGetObjectManager()->GetObject(m_uidOwner);
        if (pTargetO)
        {
            if (pTargetO->IsDie())
            {
                Explosion();
                return false;
            }
        }

        ZObject *pTarget = ZGetObjectManager()->GetObject(m_uidTarget);
        if (pTarget) 
        {
            if (pTarget->IsDie())
            {
                Explosion();
                return false;
            }

            float fCurrentSpeed = Magnitude(m_Velocity);
            rvector currentDir = m_Velocity;
            Normalize(currentDir);

            rvector dir = (pTarget->GetPosition()  rvector(0, 0, 100)) - m_Position;

            Normalize(dir);

            float fCos = DotProduct(dir,currentDir);
            float fAngle = acos(fCos);
            if(fAngle>0.01f) 
            {
                #define ANGULAR_VELOCITY	0.01f		
                float fAngleDiff = min(1000.f*fElapsedTime*ANGULAR_VELOCITY,fAngle);

                rvector newDir = InterpolatedVector(m_Dir,dir,fAngleDiff/fAngle);
                m_Dir = newDir;

                m_Velocity = fCurrentSpeed * newDir;
            }
        }



        rvector oldPos = m_Position;

        //if (ZGetGame()->GetTime() - m_fStartTime > GUIDEDROCKET_LIFE)
        if (ZGetGame()->GetTime() - m_fStartTime > ROCKET_LIFE)
        {
            Explosion();

            if (Z_VIDEO_DYNAMICLIGHT && m_SLSid) {
                ZGetStencilLight()->DeleteLightSource(m_SLSid);
                m_SLSid = 0;
            }

            return false;
        }

        const DWORD dwPickPassFlag = RM_FLAG_ADDITIVE | RM_FLAG_HIDE | RM_FLAG_PASSROCKET;
        {
            rvector diff = m_Velocity * fElapsedTime;
            rvector dir = diff;
            Normalize(dir);

            float fDist = Magnitude(diff);

            rvector pickpos;
            ZPICKINFO zpi;
            bool bPicked = ZGetGame()->Pick(ZGetObjectManager()->GetObject(m_uidOwner), m_Position, dir, &zpi, dwPickPassFlag);
            if (bPicked)
            {
                if (zpi.bBspPicked)
                    pickpos = zpi.bpi.PickPos;
                else
                    if (zpi.pObject)
                        pickpos = zpi.info.vOut;

            }

            if (bPicked && fabsf(Magnitude(pickpos - m_Position)) < fDist)
            {
                Explosion();

                if (Z_VIDEO_DYNAMICLIGHT && m_SLSid)
                {
                    ZGetStencilLight()->DeleteLightSource(m_SLSid);
                    m_SLSid = 0;
                    ZGetStencilLight()->AddLightSource(pickpos, 3.0f, 1300);
                }

                return false;
            }
            else
                m_Position = diff;
        }

        rmatrix mat;
        rvector dir = m_Velocity;
        Normalize(dir);
        MakeWorldMatrix(&mat, m_Position, m_Dir, m_Up);

        m_pVMesh->SetWorldMatrix(mat);

        float this_time = ZGetGame()->GetTime();

        if (this_time > m_fLastAddTime  0.02f)
        {
    #define _ROCKET_RAND_CAP 10

            rvector add = rvector(RANDOMFLOAT - 0.5f, RANDOMFLOAT - 0.5f, RANDOMFLOAT - 0.5f);
            rvector pos = m_Position  20.f * add;

            ZGetEffectManager()->AddRocketSmokeEffect(pos);
            ZGetWorld()->GetFlags()->CheckSpearing(oldPos, pos, ROCKET_SPEAR_EMBLEM_POWER);
            m_fLastAddTime = this_time;
        }

        if (Z_VIDEO_DYNAMICLIGHT)
            ZGetStencilLight()->SetLightSourcePosition(m_SLSid, m_Position);

        return true;
    }
    void ZWeaponGuidedRocket::Render()
    {
        ZWeapon::Render();
    }
    void ZWeaponGuidedRocket::Explosion()
    {
        rvector v = m_Position;

        rvector dir = -RealSpace2::RCameraDirection;
        ZGetEffectManager()->AddRocketEffect(v, dir);

        ZGetGame()->OnExplosionGrenade(m_uidOwner, v, m_fDamage, /*m_nItemParts,*/ ROCKET_SPLASH_RANGE, ROCKET_MINIMUM_DAMAGE, ROCKET_KNOCKBACK_CONST, m_nTeamID);

        ZGetSoundEngine()->PlaySound("fx_explosion01", v);

        ZGetWorld()->GetFlags()->SetExplosion(v, EXPLOSION_EMBLEM_POWER);

    }

Open(ZWeapon.h)

    ///////////////////////////////////////////////////////////////////////
    class ZEffectGuidedRocket;
    class ZWeaponGuidedRocket : public ZMovingWeapon {
    public:
        MDeclareRTTI;

        ZWeaponGuidedRocket();
        ~ZWeaponGuidedRocket();

        void Create(RMesh* pMesh, rvector& pos, rvector& dir, ZObject* pOwner, ZObject* pCharacter);
        void Render();
        void Explosion();

        bool Update(float fElapsedTime);

        float	m_fStartTime;
        float	m_fLastAddTime;
    protected:
        MUID		m_uidTarget;
    };


Open(ZWeaponMgr.cpp)


    void ZWeaponMgr::AddGuidedRocket(rvector &pos,rvector &dir,ZObject* pC,ZObject* pCharacter)
    {
        ZWeaponGuidedRocket* pWeapon = new ZWeaponGuidedRocket;

        RMesh* pMesh = ZGetWeaponMeshMgr()->Get("rocketguided");
        if(!pMesh) return;

        pWeapon->Create(pMesh, pos, dir, pC, pCharacter);
        Add(pWeapon);
    }









Credits to Nick.
