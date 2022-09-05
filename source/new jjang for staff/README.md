Open: (ZGame.h) and search: 

    void OnEventUpdateJjang(const MUID& uidChar, bool bJjang);
    
Under this add

    void OnUpdateJjangStaff(const MUID& uidChar, bool bJjangStaff);

Search : ZGame.cpp

    void ZGame::OnEventUpdateJjang(const MUID& uidChar, bool bJjang)
    {
    ZCharacter* pCharacter = m_CharacterManager.Find(uidChar);
    if (pCharacter == NULL) return;

    if (bJjang)
    ZGetEffectManager()->AddStarEffect(pCharacter);
    }

Under this add

    void ZGame::OnUpdateJjangStaff(const MUID& uidChar, bool bJjangStaff)
    {
    ZCharacter* pCharacter = m_CharacterManager.Find(uidChar);
    if (pCharacter == NULL) return;

    if (bJjangStaff)
    ZGetEffectManager()->AddStaffEffect(pCharacter);
    }

Search : ZCharacter.cpp

    void ZCharacter::InitRound()
    {
    // ¿Â°ÔÀÓ³ÝÀÇ ¿äÃ»À¸·Î Â¯ ¾ÆÀÌÄÜÀ» ´Þ¾ÆÁØ´Ù. initround½Ã¿¡, ³­ÀÔÇÒ¶§ ´Þ¾ÆÁØ´Ù
    if(GetUserGrade()==MMUG_STAR) {
    ZGetEffectManager()->AddStarEffect(this);
    }
    }

Read code and ADD

    if(GetUserGrade()==MMUG_ADMIN) {
    ZGetEffectManager()->AddStaffEffect(this);
    }
    if(GetUserGrade()==MMUG_DEVELOPER) {
    ZGetEffectManager()->AddStaffEffect(this);
    }
    if(GetUserGrade()==MMUG_EVENTMASTER) {
    ZGetEffectManager()->AddStaffEffect(this);
    }

    void ZCharacter::InitRound()
    {
    if(GetUserGrade()==MMUG_STAR) {
    ZGetEffectManager()->AddStarEffect(this);
    }
    if(GetUserGrade()==MMUG_ADMIN) {
    ZGetEffectManager()->AddStaffEffect(this);
    }
    if(GetUserGrade()==MMUG_DEVELOPER) {
    ZGetEffectManager()->AddStaffEffect(this);
    }
    if(GetUserGrade()==MMUG_EVENTMASTER) {
    ZGetEffectManager()->AddStaffEffect(this);
    }
    }

Search : ZEffectManager.cpp

    class ZEffectIconLoopStar : public ZEffectIconLoop {
    // ¸â¹ö¸¦ Ãß°¡ÇÏ¸é ¿¡·¯
    private:
    public:
    ZEffectIconLoopStar(RMesh* pMesh, ZObject* pObj)
    : ZEffectIconLoop(pMesh,pObj)
    {}

    virtual bool Draw(unsigned long int nTime)
    {
    MMatchObjCache* pCache = ZGetGameClient()->FindObjCache(m_uid);
    if (pCache && pCache->GetUGrade() != MMUG_STAR)
    return false;

    bool DidDraw = ZEffectIconLoop::Draw(nTime);

    return DidDraw;
    }
    };

Add Under this

    class ZEffectIconLoopStaff : public ZEffectIconLoop {

    private:
    public:
    ZEffectIconLoopStaff(RMesh* pMesh, ZObject* pObj)
    : ZEffectIconLoop(pMesh,pObj)
    {}

    virtual bool Draw(unsigned long int nTime)
    {
    MMatchObjCache* pCache = ZGetGameClient()->FindObjCache(m_uid);
    if (pCache && pCache->GetUGrade() != MMUG_ADMIN)
    if (pCache && pCache->GetUGrade() != MMUG_DEVELOPER)
    if (pCache && pCache->GetUGrade() != MMUG_EVENTMASTER)
    return false;

    bool DidDraw = ZEffectIconLoop::Draw(nTime);

    return DidDraw;
    }
    };

NEXT Search

    void ZEffectManager::AddStaffEffect( ZObject *pObj )
    {
    ZEffect* pNew = NULL;
    pNew = new ZEffectIconLoopStaff(m_pEffectMeshMgr->Get("event_ongame_jjang"),pObj);
    ((ZEffectIconLoop*)pNew)->SetAlignType(1);
    ((ZEffectIconLoop*)pNew)->m_type = eq_parts_pos_info_Spine2;
    Add(pNew);
    /*
    ZEffect* pNew = NULL;
    pNew = new ZEffectIconLoop(m_pEffectMeshMgr->Get("event_ongame_jjang"),pObj, rvector(0,0,90));
    ((ZEffectIconLoop*)pNew)->SetAlignType(2);
    ((ZEffectIconLoop*)pNew)->m_type = eq_parts_pos_info_Spine1;
    Add(pNew);
    */
    }

Add more

    void ZEffectManager::AddStaffEffect( ZObject *pObj )
    {
    ZEffect* pNew = NULL;
    pNew = new ZEffectIconLoopStaff(m_pEffectMeshMgr->Get("event_admini_jjang"),pObj);
    ((ZEffectIconLoop*)pNew)->SetAlignType(1);
    ((ZEffectIconLoop*)pNew)->m_type = eq_parts_pos_info_Spine2;
    Add(pNew);
    }

Decompile (SFX.mrs) and find: Effect_list.xml

    <AddEffectElu name="event_ongame_jjang">
    <AddBaseModel name="event_ongame_jjang" filename="ef_event_ongame_jjang.elu" />
    <AddAnimation name="play" filename="ef_event_ongame_jjang.elu.ani" motion_type="0" motion_loop_type="loop" />
    </AddEffectElu>

Under this add

    <AddEffectElu name="event_admini_jjang">
    <AddBaseModel name="event_admini_jjang" filename="ef_event_admin_jjang.elu" />
    <AddAnimation name="play" filename="ef_event_admin_jjang.elu.ani" motion_type="0" motion_loop_type="loop" />
    </AddEffectElu>

    
