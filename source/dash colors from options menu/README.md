ZEffectManager.h:

find this:

    void AddDashEffect(rvector& Target,rvector& TargetNormal,ZObject* pObj);

replace with this:

    void AddDashEffect(rvector& Target,rvector& TargetNormal,ZObject* pObj,int nDashColor);

ZEffectManager.cpp:

find void ZEffectManager::AddDashEffect function and replace the function with this:

    void ZEffectManager::AddDashEffect(rvector& Target,rvector& TargetNormal,ZObject* pObj,int nDashColor)
    {
    if (!pObj->IsVisible()) return;
    char szDash[255];
    if (nDashColor == 0 || nDashColor < 1 || nDashColor > 7) // 7 b/c roygbiv
    {
    sprintf(szDash, "dash_effect");
    }
    else
    {
    sprintf(szDash, "dash_effect%d", nDashColor);
    }


    ZEffect* pNew = NULL;
    pNew = new ZEffectDash(m_pEffectMeshMgr->Get(szDash), Target, TargetNormal, pObj->GetUID());
    ((ZEffectSlash*)pNew)->SetAlignType(1);
    Add(pNew);
    }

ZGame.cpp:

find this:

    pEM->AddDashEffect(vPos, vTarNormal, pCharacter);

replace with this:

    pEM->AddDashEffect(vPos, vTarNormal, pCharacter,0);

find this:

    ZGetEffectManager()->AddDashEffect(pos,dir,pCharacter);

replace with this:

    ZGetEffectManager()->AddDashEffect(pos,dir,pCharacter,ppdi->nDashColor);

ZPost.h:

find this:

    #define ZPostDash(/*rvector&*/ vPos, /*rvector&*/ vDir, /*unsigned char*/ sel_type) { \
    ZPACKEDDASHINFO pdi; \
    pdi.posx = Roundf(vPos.x); \
    pdi.posy = Roundf(vPos.y); \
    pdi.posz = Roundf(vPos.z); \
    \
    pdi.dirx = vDir.x*32000; \
    pdi.diry = vDir.y*32000; \
    pdi.dirz = vDir.z*32000; \
    \
    pdi.seltype = sel_type; \
    ZPOSTCMD1(CLOAK_CMD_ID(MC_PEER_DASH, 9964),MCommandParameterBlob(&pdi,sizeof(ZPACKEDDASHINFO))); \
    }

replace with this:

    #define ZPostDash(/*rvector&*/ vPos, /*rvector&*/ vDir, /*unsigned char*/ sel_type, /*int*/ nDashColor) { \
    ZPACKEDDASHINFO pdi; \
    pdi.posx = Roundf(vPos.x); \
    pdi.posy = Roundf(vPos.y); \
    pdi.posz = Roundf(vPos.z); \
    \
    pdi.dirx = vDir.x*32000; \
    pdi.diry = vDir.y*32000; \
    pdi.dirz = vDir.z*32000; \
    \
    pdi.seltype = sel_type; \
    pdi.nDashColor = nDashColor; \
    ZPOSTCMD1(CLOAK_CMD_ID(MC_PEER_DASH, 9964),MCommandParameterBlob(&pdi,sizeof(ZPACKEDDASHINFO))); \
    }

find this:

    struct ZPACKEDDASHINFO {
    short posx, posy, posz;
    short dirx, diry, dirz;
    BYTE seltype;
    };

replace with this:

    struct ZPACKEDDASHINFO {
    short posx, posy, posz;
    short dirx, diry, dirz;
    BYTE seltype,nDashColor;
    };
    
zreplay.cpp:

find case mc_peer_dash, replace it with this:

    case MC_PEER_DASH:
    {
    rvector pos, dir;
    int nSelType,nDashColor;

    TempParams[0]->GetValue(&pos);
    TempParams[1]->GetValue(&dir);
    TempParams[2]->GetValue(&nSelType);
    TempParams[3]->GetValue(&nDashColor);

    ZPACKEDDASHINFO pdi;
    pdi.posx = Roundf(pos.x);
    pdi.posy = Roundf(pos.y);
    pdi.posz = Roundf(pos.z);

    pdi.dirx = DirElementToShort(dir.x);
    pdi.diry = DirElementToShort(dir.y);
    pdi.dirz = DirElementToShort(dir.z);

    pdi.seltype = (BYTE)nSelType;
    pdi.nDashColor = (BYTE)nDashColor;
    pCmd->AddParameter(new MCommandParameterBlob(&pdi,sizeof(ZPACKEDDASHINFO)));
    }
    break;

ZConfiguration.h:

add this to ZCONFIG_VIDEO:

    int nDashColor;

add these 2 thigns at th ebottom of the file:

    #define Z_VIDEO_DASH (ZGetConfiguration()->GetVideo()->nDashColor)
    #define ZTOK_VIDEO_DASH "DASHCOLOR"

ZConfiguration.cpp:

add this in loadconfig with the other ztok_video stuff:

    childElement.GetChildContents(&m_Video.nDashColor, ZTOK_VIDEO_DASH);

add this in savetofile:

    // Dash Color
    parentElement.AppendText("\n\t\t");
    aElement = parentElement.CreateChildElement(ZTOK_VIDEO_DASH);
    sprintf(temp, "%d", m_Video.nDashColor);
    aElement.SetContents(temp);

ZOptionInterface.cpp:
add this to initinterfaceoption:

    pComboBox = (MComboBox*)pResource->FindWidget("DashColor")
    if(pComboBox)
    {
    pComboBox->SetSelIndex(Z_VIDEO_DASH);
    }

add this to saveinterfaceoption:

    int nDashColor = 0;
    pComboBox = (MComboBox*)pResource->FindWidget("DashColor")
    if(pComboBox)
    {
    nDashColor = pComboBox->GetSelIndex();
    if(Z_VIDEO_DASH != nDashColor)
    {
    Z_VIDEO_DASH = nDashColor;
    }
    }

ZMyCharacter.cpp:
find both instances of zpostdash in this file, and replace it with this:

    ZPostDash( vPos, vDir, sel_type, Z_VIDEO_DASH );

decompile sfx.mrs, and add 7 folders. (names 1-7). Now, add the ef_dash.elu.ani, ef.dash.elu, both gz_ef dashes, and then open effect_list.xml.

effectlist.xml:
Find this:

    <AddEffectElu name="dash_effect">
    <AddBaseModel name="dash_effect" filename="ef_dash.elu" />
    <AddAnimation name="play" filename="ef_dash.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>
    
add this under it:

    <AddEffectElu name="dash_effect1">
    <AddBaseModel name="dash_effect1" filename="1/ef_dash.elu" />
    <AddAnimation name="play" filename="ef_dash.elu.ani" motion_type="0" motion_loop_type="lastframe" />
    </AddEffectElu>

I'll leave the option xml side of things for you guys to do, just copy an xml that's a combobox, and rename the widget to DashColor, then add the amount of listitem's based on colors. If there's any bugs with it let me know, i rushed this in like 5 minutes.

Thanks too Jetman.
