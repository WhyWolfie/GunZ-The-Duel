Credit : Desperate (There have been some improvements based on the code provided by Desperate.)
--
I was asked to upload it on the board, and also got permission from Desperate.


Of course, if use text, it will be much easier to implement, but if use elu, you will be able to use more diverse designs and animations.

I made a little improvement on this. (dmg floating using elu and ani)
but the problem regarding the horizontal movement of the elu's w2s has not yet been resolved.
Instead, I changed the position data of the elu itself. (It's a little trick. lol)

First of all, please use the attached file's elu.
(To prevent numbers from overlapping)
- We need to figure out how we can do horizontal control to optimize this.

We need your contribution to developing more upgraded codes.

[![Video](https://img.youtube.com/vi/VrpgBPoiLIU/0.jpg)](https://www.youtube.com/watch?v=VrpgBPoiLIU)


Gunz -> ZEffectManager.h
Add

    RMesh* m_pDamageFloat[10];
    RMesh* m_pDamageFloatx[10];
    RMesh* m_pDamageFloatxx[10];

-----

    RMeshMgr* m_pEffectMeshDmg;    RMesh* m_pDamageFloat[10];    RMesh* m_pDamageFloatx[10];    RMesh* m_pDamageFloatxx[10];    void AddDamageEffect(int Dmg, ZObject* pObj, ZObject* pOwner);

Gunz -> ZeffectManager.cpp
Add

    void ZEffectManager::AddDamageEffect(int Dmg, ZObject* pObj, ZObject* pOwner)
    {
        if (Dmg == 0) return;
    
        class ZEffectDmgfloating : public ZEffectIcon {
        public:
            ZEffectDmgfloating(RMesh* pMesh, ZObject* pObj)
                : ZEffectIcon(pMesh, pObj) {
            }
    
            virtual bool Draw(unsigned long int nTime)
            {
                ZObject* pObj = ZGetObjectManager()->GetObject(m_uid);
    
                ZCharacter* pChar = MDynamicCast(ZCharacter, pObj);
    
                if (pChar) {
                    if (!pChar->m_bRendered) return true;
                    if (!pChar->IsVisible()) return true;
                    if (pObj->m_pVMesh) {
                        m_Pos = pObj->GetVisualMesh()->GetHeadPosition() + rvector(0, 0, 50); //  + rvector(0, 0, height)
    
                        RGetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    
                        ZEffectAniMesh::Draw(nTime);
    
                        RGetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
    
                        return true;
                    }
                }
                return false;
            }
        };
    
        ZEffect* pNew = NULL;
    
        char buffer[32];
        sprintf(buffer, "%d", abs(Dmg));
        int nCount = (int)strlen(buffer);
        float fScale, dist;
    
        float dx = pObj->GetPosition().x - pOwner->GetPosition().x;
        float dy = pObj->GetPosition().y - pOwner->GetPosition().y;
        float dz = pObj->GetPosition().z - pOwner->GetPosition().z;
        dist = sqrt(dx * dx + dy * dy + dz * dz);
    
        for (int i = 0; i < nCount; i++)
        {
            if (nCount == 3)
            {
                if (i == 0) {
                    pNew = new ZEffectDmgfloating(m_pDamageFloat[buffer[i] - '0'], pObj);
                    DeleteSameType((ZEffectAniMesh*)pNew);
                }
                if (i == 1)
                    pNew = new ZEffectDmgfloating(m_pDamageFloatx[buffer[i] - '0'], pObj);
                if (i == 2)
                    pNew = new ZEffectDmgfloating(m_pDamageFloatxx[buffer[i] - '0'], pObj);
            }
            if (nCount == 2)
            {
                if (i == 0) {
                    pNew = new ZEffectDmgfloating(m_pDamageFloatx[buffer[i] - '0'], pObj);
                    DeleteSameType((ZEffectAniMesh*)pNew);
                }
                if (i == 1)
                    pNew = new ZEffectDmgfloating(m_pDamageFloatxx[buffer[i] - '0'], pObj);
            }
            if (nCount == 1)
            {
                if (i == 0) {
                    pNew = new ZEffectDmgfloating(m_pDamageFloatx[buffer[i] - '0'], pObj);
                    DeleteSameType((ZEffectAniMesh*)pNew);
                }
            }
    
            fScale = 1.0f + 0.001f * dist; //Size adjustment according to distance
            ((ZEffectDmgfloating*)pNew)->SetScale(rvector(fScale, fScale, fScale));
            Add(pNew);
        }
    }

Find

    bool ZEffectManager::Create(void)

Add inside

    m_pEffectMeshDmg = new RMeshMgr;
    if (m_pEffectMeshDmg->LoadXmlList("SFX/dmg/float_damage.xml") == -1) {
        mlog("float damage sfx loding error\n");
    }

    for (int i = 0; i < 10; i++)
    {
        char meshname[256];
        char meshnamex[256];
        char meshnamexx[256];
        sprintf(meshname, "dmg%d", i);
        m_pDamageFloat[i] = m_pEffectMeshDmg->Get(meshname);
        sprintf(meshnamex, "dmgx%d", i);
        m_pDamageFloatx[i] = m_pEffectMeshDmg->Get(meshnamex);
        sprintf(meshnamexx, "dmgxx%d", i);
        m_pDamageFloatxx[i] = m_pEffectMeshDmg->Get(meshnamexx);
    }

Gunz -> ZCharacter.h
Find

    struct ZCharacterStatus

Add inside And on top of 'nScore;'

    float        nRoundGivenDamage;
----
    nRoundGivenDamage(0),

Gunz -> ZGame.h

Find

    void OnPeerShotgun_Damaged(~~);

Change (Add `int Repeatcount` at the far end of the factor)

    void OnPeerShotgun_Damaged(ZObject* pOwner, float fShotTime, const rvector& pos, rvector& dir, ZPICKINFO pickinfo, DWORD dwPickPassFlag, rvector& v1, rvector& v2, ZItem* pItem, rvector& BulletMarkNormal, bool& bBulletMark, ZTargetType& nTargetType, bool& bHitEnemy, int Repeatcount);

Gunz -> ZGame.cpp

Find

    void ZGame::OnPeerShot_Range_Damaged

Add inside (In the part where you calculate the damage)

    ZGetGame()->m_pMyCharacter->GetStatus().CheckCrc();
    ZGetGame()->m_pMyCharacter->GetStatus().Ref().nRoundGivenDamage = fActualDamage;
     ZGetGame()->m_pMyCharacter->GetStatus().MakeCrc();

Add inside too (OnPeerShot_Range_Damaged's end)

    if ((pObject->GetUID() != ZGetMyUID()) && (pOwner->GetUID() == ZGetMyUID()))
    {
        int nCurrDamage = ZGetGame()->m_pMyCharacter->GetStatus().Ref().nRoundGivenDamage;
        ZGetEffectManager()->AddDamageEffect(nCurrDamage, pObject, pOwner);
    }

Find

    in the 'void ZGame::OnPeerShot_Shotgun'
    OnPeerShotgun_Damaged( pOwnerCharacter, fShotTime, pos, dir, pickinfo, dwPickPassFlag, v1, v2, pItem, BulletMarkNormal, bBulletMark, nTargetType, bHitEnemy);

Change (Add `i` at the far end of the factor)

    OnPeerShotgun_Damaged( pOwnerCharacter, fShotTime, pos, dir, pickinfo, dwPickPassFlag, v1, v2, pItem, BulletMarkNormal, bBulletMark, nTargetType, bHitEnemy, i);

Find

    void ZGame::OnPeerShotgun_Damaged

Change (Add `int Repeatcount` at the far end of the factor)

    void ZGame::OnPeerShotgun_Damaged(ZObject* pOwner, float fShotTime, const rvector& pos, rvector& dir, ZPICKINFO pickinfo, DWORD dwPickPassFlag, rvector& v1, rvector& v2, ZItem *pItem, rvector& BulletMarkNormal, bool& bBulletMark, ZTargetType& nTargetType, bool& bHitEnemy, int Repeatcount)

Add inside

    //Initialize the variable at the first of the iterations of this function
    if (Repeatcount == 0) {
        ZGetGame()->m_pMyCharacter->GetStatus().CheckCrc();
        ZGetGame()->m_pMyCharacter->GetStatus().Ref().nRoundGivenDamage = 0;
        ZGetGame()->m_pMyCharacter->GetStatus().MakeCrc();
    }

Add inside too (In the part where you calculate the SG damage)

    ZGetGame()->m_pMyCharacter->GetStatus().Ref().nRoundGivenDamage += fActualDamage;

Add inside too

    if ((pObject->GetUID() != ZGetMyUID()) && (pOwner->GetUID() == ZGetMyUID()))
    {
         int nCurrDamage = ZGetGame()->m_pMyCharacter->GetStatus().Ref().nRoundGivenDamage;
         ZGetEffectManager()->AddDamageEffect(nCurrDamage, pObject, pOwner);
    }

Melee

    void ZGame::OnPeerShot_Melee

Explosion(rocket, granade)

    void ZGame::OnExplosionGrenade

If you don't want to output when you attack mob, add this to the condition of calling AddDamageEffect.
Verify that the target is npc(mobs).

    !pObject->IsNPC()

SFX.mrs/dmg/float_damage.xml

<!-- 데미지플로팅 -->
    <AddEffectElu name="dmg0">
        <AddBaseModel name="dmg0" filename="dmg/ef_exp_num_0.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_0.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmg1">
        <AddBaseModel name="dmg1" filename="dmg/ef_exp_num_1.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_1.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmg2">
        <AddBaseModel name="dmg2" filename="dmg/ef_exp_num_2.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_2.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmg3">
        <AddBaseModel name="dmg3" filename="dmg/ef_exp_num_3.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_3.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmg4">
        <AddBaseModel name="dmg4" filename="dmg/ef_exp_num_4.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_4.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmg5">
        <AddBaseModel name="dmg5" filename="dmg/ef_exp_num_5.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_5.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmg6">
        <AddBaseModel name="dmg6" filename="dmg/ef_exp_num_6.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_6.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmg7">
        <AddBaseModel name="dmg7" filename="dmg/ef_exp_num_7.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_7.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmg8">
        <AddBaseModel name="dmg8" filename="dmg/ef_exp_num_8.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_8.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmg9">
        <AddBaseModel name="dmg9" filename="dmg/ef_exp_num_9.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_9.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgx0">
        <AddBaseModel name="dmgx0" filename="dmg/ef_exp_num_x0.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_x0.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgx1">
        <AddBaseModel name="dmgx1" filename="dmg/ef_exp_num_x1.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_x1.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgx2">
        <AddBaseModel name="dmgx2" filename="dmg/ef_exp_num_x2.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_x2.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgx3">
        <AddBaseModel name="dmgx3" filename="dmg/ef_exp_num_x3.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_x3.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgx4">
        <AddBaseModel name="dmgx4" filename="dmg/ef_exp_num_x4.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_x4.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgx5">
        <AddBaseModel name="dmgx5" filename="dmg/ef_exp_num_x5.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_x5.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgx6">
        <AddBaseModel name="dmgx6" filename="dmg/ef_exp_num_x6.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_x6.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgx7">
        <AddBaseModel name="dmgx7" filename="dmg/ef_exp_num_x7.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_x7.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgx8">
        <AddBaseModel name="dmgx8" filename="dmg/ef_exp_num_x8.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_x8.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgx9">
        <AddBaseModel name="dmgx9" filename="dmg/ef_exp_num_x9.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_x9.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgxx0">
        <AddBaseModel name="dmgxx0" filename="dmg/ef_exp_num_xx0.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_xx0.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgxx1">
        <AddBaseModel name="dmgxx1" filename="dmg/ef_exp_num_xx1.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_xx1.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgxx2">
        <AddBaseModel name="dmgxx2" filename="dmg/ef_exp_num_xx2.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_xx2.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgxx3">
        <AddBaseModel name="dmgxx3" filename="dmg/ef_exp_num_xx3.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_xx3.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgxx4">
        <AddBaseModel name="dmgxx4" filename="dmg/ef_exp_num_xx4.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_xx4.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgxx5">
        <AddBaseModel name="dmgxx5" filename="dmg/ef_exp_num_xx5.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_xx5.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgxx6">
        <AddBaseModel name="dmgxx6" filename="dmg/ef_exp_num_xx6.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_xx6.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgxx7">
        <AddBaseModel name="dmgxx7" filename="dmg/ef_exp_num_xx7.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_xx7.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgxx8">
        <AddBaseModel name="dmgxx8" filename="dmg/ef_exp_num_xx8.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_xx8.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    <AddEffectElu name="dmgxx9">
        <AddBaseModel name="dmgxx9" filename="dmg/ef_exp_num_xx9.elu" />
        <AddAnimation name="play" filename="dmg/ef_exp_num_xx9.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>


Credits to Kwh2009 & Desperate.
