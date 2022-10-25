Custom Dashes: [Custom Dashes](https://github.com/Durial06/GunZ-The-Duel-Items/tree/main/dash) <br>
Open(ZConfiguration.cpp) <br>

				childElement.GetChildContents(&m_Extra.nDashColor, ZTOK_EXTRA_DASH);


Part 2 -> parentElement = aRootElement.CreateChildElement(ZTOK_EXTRA);

			parentElement.AppendText("\n\t\t");
			aElement = parentElement.CreateChildElement(ZTOK_EXTRA_DASH);
			sprintf(temp, "%d", m_Extra.nDashColor);
			aElement.SetContents(temp);


Part 3 -> ZConfiguration::Init()

	m_Extra.nDashColor   = 0;

Open(ZConfiguration.h - struct ZCONFIG_EXTRA) <br>

	int         nDashColor;


Find (Z_ETC_CROSSHAIR - Place under)

    #define Z_EXTRA_DASH            (ZGetConfiguration()->GetExtra()->nDashColor)

Open(ZEffectManager.cpp - AddDashEffect replace all)

    void ZEffectManager::AddDashEffect(rvector& Target, rvector& TargetNormal, ZObject* pObj,int nDashColor)
    {
      if (!pObj->IsVisible()) return;
      char szDash[255];
      if (nDashColor == 0 || nDashColor < 1 || nDashColor > 20)
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
    #pragma optimize ( "", on)


Open(ZEffectManager.h - replace all)

	void AddDashEffect(rvector& Target, rvector& TargetNormal, ZObject* pObj, int nDashColor);

Open(ZGame.cpp) <br>

    ZGetEffectManager()->AddDashEffect(pos,dir,pCharacter);

Replace
  
    ZGetEffectManager()->AddDashEffect(pos, dir, pCharacter, ppdi->nDashColor);

Find(pEM->AddDashEffect)

    pEM->AddDashEffect(vPos, vTarNormal, pCharacter);

Replace

    pEM->AddDashEffect(vPos, vTarNormal, pCharacter, 0);

Open(ZOptionInterface.cpp - ZOptionInterface::SaveInterfaceOption(void) - Add all the way at the top)


	ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();

	int nDashColor = 0;
	MComboBox* pComboBox = (MComboBox*)pResource->FindWidget("DashColor");
	if (pComboBox)
	{
		nDashColor = pComboBox->GetSelIndex();
		if (Z_EXTRA_DASH != nDashColor)
		{
			Z_EXTRA_DASH = nDashColor;
		}
	}

Open(ZPost.h)

    struct ZPACKEDDASHINFO {
      short	posx, posy, posz;
      short	dirx, diry, dirz;
      BYTE	seltype;
    };

Replace

    struct ZPACKEDDASHINFO {
      short	posx, posy, posz;
      short	dirx, diry, dirz;
      BYTE	seltype, nDashColor;
    };

Find(ZPostDash)

    #define ZPostDash(/*rvector&*/ vPos, /*rvector&*/ vDir, /*unsigned char*/ sel_type) { 	\
      ZPACKEDDASHINFO pdi;		\
      pdi.posx = Roundf(vPos.x);	\
      pdi.posy = Roundf(vPos.y);	\
      pdi.posz = Roundf(vPos.z);	\
                    \
      pdi.dirx = vDir.x*32000;	\
      pdi.diry = vDir.y*32000;	\
      pdi.dirz = vDir.z*32000;	\
                    \
      pdi.seltype = sel_type;		\
                    \
      ZPOSTCMD1(CLOAK_CMD_ID(MC_PEER_DASH, 9964),MCommandParameterBlob(&pdi,sizeof(ZPACKEDDASHINFO)));	\
    }

Replace

    inline void ZPostDash(rvector& vPos, rvector& vDir, unsigned char sel_type, int nDashColor) {
      \
      ZPACKEDDASHINFO pdi;	\
      pdi.posx = Roundf(vPos.x);	\
      pdi.posy = Roundf(vPos.y);	\
      pdi.posz = Roundf(vPos.z);	\
      \
      pdi.dirx = vDir.x*32000;	\
      pdi.diry = vDir.y*32000;	\
      pdi.dirz = vDir.z*32000;	\
      \
      pdi.seltype = sel_type;		\
      pdi.nDashColor = nDashColor; \
      ZPOSTCMD1(CLOAK_CMD_ID(MC_PEER_DASH, 9964),MCommandParameterBlob(&pdi,sizeof(ZPACKEDDASHINFO)));	\
    }

Open(ZReplay.cpp)

	case MC_PEER_DASH:
		{
			rvector pos, dir;
			int nSelType;

			TempParams[0]->GetValue(&pos);
			TempParams[1]->GetValue(&dir);
			TempParams[2]->GetValue(&nSelType);

			ZPACKEDDASHINFO pdi;
			pdi.posx = Roundf(pos.x);
			pdi.posy = Roundf(pos.y);
			pdi.posz = Roundf(pos.z);

			pdi.dirx = DirElementToShort(dir.x);
			pdi.diry = DirElementToShort(dir.y);
			pdi.dirz = DirElementToShort(dir.z);

			pdi.seltype = (BYTE)nSelType;

			pCmd->AddParameter(new MCommandParameterBlob(&pdi,sizeof(ZPACKEDDASHINFO)));
		}
		break;

Replace

	case MC_PEER_DASH:
		{
			rvector pos, dir;
			int nSelType, nDashColor;

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

Open(ZConfiguration.h - #define ZTOK_EXTRA)

    #define ZTOK_EXTRA_DASH        "DASHCOLOR"

Open(ZMyCharacter.cpp)

    ZPostDash(vPos,vDir,sel_type);

Replace

    ZPostDash(vPos, vDir, sel_type, Z_EXTRA_DASH);


Open(ZEffectManager.cpp - m_pDashEffect) <br>

	m_pDashEffect				= m_pEffectMeshMgr->Get("dash_effect");
	m_pDashEffect2				= m_pEffectMeshMgr->Get("dash_effect2");
	
Example keep adding till 20 m_pDashEffect / m_pDashEffect20

	m_pDashEffect3				= m_pEffectMeshMgr->Get("dash_effect3");
	m_pDashEffect4				= m_pEffectMeshMgr->Get("dash_effect4");

Open(ZEffectManager.h - RMesh*	m_pDashEffect;)

	RMesh*	m_pDashEffect;
	RMesh*	m_pDashEffect2;

Example keep adding till 20 m_pDashEffect / m_pDashEffect20

	RMesh*	m_pDashEffect3;
	RMesh*	m_pDashEffect4;

Open(SFX.mrs -> Effect_List.xml)

	<AddEffectElu name="dash_effect">
		<AddBaseModel name="dash_effect" filename="ef_dash.elu" />
		<AddAnimation name="play" filename="ef_dash.elu.ani" motion_type="0" motion_loop_type="lastframe" />
	</AddEffectElu>
	
Add under (make a folder 'dash' add your files there)

	<AddEffectElu name="dash_effect2">
		<AddBaseModel name="dash_effect2" filename="dash/ef_dash.elu" />
		<AddAnimation name="play" filename="dash/ef_dash.elu.ani" motion_type="0" motion_loop_type="lastframe" />
	</AddEffectElu>

Example for next (folder 'dash3')

	<AddEffectElu name="dash_effect3">
		<AddBaseModel name="dash_effect3" filename="dash3/ef_dash.elu" />
		<AddAnimation name="play" filename="dash3/ef_dash.elu.ani" motion_type="0" motion_loop_type="lastframe" />
	</AddEffectElu>

Open(Default.mrs -> Option.xml And Add)

	<!-- DashColor Option --> 
	  <LABEL item="Label" parent="ExtraOptionGroup">
			<FONT>FONTa9</FONT>
			<TEXTCOLOR>
				<R>205</R>
				<G>205</G>
				<B>205</B>
			</TEXTCOLOR>
			<BOUNDS>
				<X>2</X>
				<Y>0</Y>
				<W>300</W>
				<H>24</H>
			</BOUNDS>
			<TEXT>Color Dash</TEXT>
		</LABEL>
		<COMBOBOX item="DashColor" parent="ExtraOptionGroup">
			<LISTBOXLOOK>CustomListBoxLook</LISTBOXLOOK>
			<BUTTONLOOK>ListBoxButtonLook</BUTTONLOOK>
			<FONT>FONTa9</FONT>
			<TEXTCOLOR>
				    <R>205</R>
				    <G>205</G>
				    <B>205</B>
			</TEXTCOLOR>
			<TEXTALIGN>
			<VALIGN>center</VALIGN>
			<HALIGN>center</HALIGN>
			</TEXTALIGN>
			<BOUNDS>
					<X>2</X>
					<Y>0</Y>
					<W>90</W>
					<H>24</H>
			</BOUNDS>
			<ALIGN>
			<HALIGN>right</HALIGN>
			</ALIGN>
			<LISTITEM selected="true">Normal</LISTITEM>
			<LISTITEM>Dash 1</LISTITEM>
			<LISTITEM>Dash 2</LISTITEM>
			<LISTITEM>Dash 3</LISTITEM>
					<LISTITEM>Dash 4</LISTITEM>
					<LISTITEM>Dash 5</LISTITEM>
					<LISTITEM>Dash 6</LISTITEM>
					<LISTITEM>Dash 7</LISTITEM>				
					<LISTITEM>Dash 8</LISTITEM>	
					<LISTITEM>Dash 9</LISTITEM>	 
					<LISTITEM>Dash 10</LISTITEM>
					<LISTITEM>Dash 11</LISTITEM> 
					<LISTITEM>Dash 12</LISTITEM>
					<LISTITEM>Dash 13</LISTITEM>
					<LISTITEM>Dash 14</LISTITEM>
					<LISTITEM>Dash 15</LISTITEM>
					<LISTITEM>Dash 16</LISTITEM>
					<LISTITEM>Dash 17</LISTITEM>
					<LISTITEM>Dash 18</LISTITEM>
					<LISTITEM>Dash 19</LISTITEM>
					<LISTITEM>Dash 20</LISTITEM>
			<DROPSIZE>500</DROPSIZE>
			<COMBOTYPE>1</COMBOTYPE>
			</COMBOBOX>	   

