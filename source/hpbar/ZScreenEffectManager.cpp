#include "stdafx.h"

#include "ZGame.h"
#include "ZScreenEffectManager.h"
#include "RealSpace2.h"
#include "MDebug.h"
#include "Mint.h"
#include "ZApplication.h"
#include "ZSoundEngine.h"
#include "ZMyInfo.h"
#include "ZQuest.h"
#include "ZRuleDuel.h"

void DrawGauge(float x,float y,float fWidth,float fHeight,float fLeanDir,DWORD color);

ZScreenEffect::ZScreenEffect(RMesh *pMesh,rvector offset)
{
	m_nDrawMode = ZEDM_NONE ;
	m_fDist = 0.f;

	m_Offset=offset;

	//	m_VMesh.m_bRenderInstantly = true;
	m_VMesh.Create(pMesh);
	m_VMesh.SetAnimation("play");
	m_VMesh.SetCheckViewFrustum(false);

}

bool ZScreenEffect::Draw(unsigned long int nTime)
{

	return DrawCustom(nTime, m_Offset);
}

void ZScreenEffect::Update()
{
	m_VMesh.Frame();
}

bool ZScreenEffect::IsDeleteTime()
{
	if(m_VMesh.isOncePlayDone())
		return true;
	return false;
}

bool ZScreenEffect::DrawCustom(unsigned long int nTime, rvector& vOffset, float fAngle)
{
	RGetDevice()->SetRenderState(D3DRS_ZENABLE, FALSE);
	RGetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	rmatrix World;
	D3DXMatrixIdentity(&World);

	if (fAngle != 0.0f)
	{
		D3DXMatrixRotationZ(&World, fAngle);
	}

	rmatrix View, Offset;
	if (RGetIsWidthScreen())
	{
		const rvector eye(0,0,-780),at(0,0,0),up(0,1,0);
		D3DXMatrixLookAtLH(&View,&eye,&at,&up);
	}
	else
	{
		const rvector eye(0, 0, -650), at(0, 0, 0), up(0, 1, 0);
		D3DXMatrixLookAtLH(&View, &eye, &at, &up);
	}
	D3DXMatrixTranslation(&Offset, vOffset.x, vOffset.y, vOffset.z);

	View = Offset*View;

	RGetDevice()->SetTransform(D3DTS_VIEW, &View);

	m_VMesh.SetWorldMatrix(World);
	m_VMesh.Render();

	if (m_VMesh.isOncePlayDone()) {
		return false;
	}

	return true;
}






///////////////////////////////////////////////////////////////////////////////////////
// ZScreenEffectLetterBox ///////////////////////////////////////////////////////////////////////
bool ZScreenEffectLetterBox::Draw(unsigned long int nTime)
{
	RGetDevice()->SetRenderState(D3DRS_ZENABLE, FALSE);
	RGetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	rmatrix World;
	D3DXMatrixIdentity(&World);

	rmatrix View,Offset;

#ifndef _EXTRESOLUTION
	if(RGetIsWidthScreen())
	{
		const rvector eye(0,0,-780),at(0,0,0),up(0,1,0);
		D3DXMatrixLookAtLH(&View,&eye,&at,&up);
		m_VMesh.SetScale(rvector(5,1,1));
	}
	else
#endif
	{
		const rvector eye(0,0,-650),at(0,0,0),up(0,1,0);
		D3DXMatrixLookAtLH(&View,&eye,&at,&up);
	}

	RGetDevice()->SetTransform( D3DTS_VIEW, &View );

	m_VMesh.SetWorldMatrix(World);
	//	m_VMesh.Frame();
	m_VMesh.Render();

	if(m_VMesh.isOncePlayDone()) {
		return false;
	}

	return true;
}


///////////////////////////////////////////////////////////////////////////////////////
// ZComboEffect ///////////////////////////////////////////////////////////////////////

ZComboEffect::ZComboEffect(RMesh *pMesh,rvector offset)
:ZScreenEffect(pMesh,offset)
{
	bDelete=false;
	// ÃÖ¼ÒÇÑ ÀÌÆåÆ® ±æÀÌ´Â 10ÃÊ´Â ³ÑÁö¾Ê´Â´Ù
	fDeleteTime=ZGetGame()->GetTime()+10.f;
}

void ZComboEffect::SetFrame(int nFrame)
{
	AniFrameInfo* pInfo = GetVMesh()->GetFrameInfo(ani_mode_lower);

	pInfo->m_nFrame =
		//		max(min(GetVMesh()->m_nFrame[0],2400),nFrame);
		max(min(pInfo->m_nFrame,2400),nFrame);
	fDeleteTime=ZGetGame()->GetTime()+10.f;
}

bool ZComboEffect::Draw(unsigned long int nTime)
{
	if(bDelete && ZGetGame()->GetTime()>=fDeleteTime)
		return false;

	ZScreenEffect::Draw(nTime);
	return true;
}

void ZComboEffect::DeleteAfter(float fTime)
{
	bDelete=true;
	fDeleteTime=ZGetGame()->GetTime()+fTime;
}

///////////////////////////////////////////////////////////////////////////////////////
// ZBossGaugeEffect ///////////////////////////////////////////////////////////////////


ZBossGaugeEffect::ZBossGaugeEffect(RMesh *pMesh,rvector offset)
:ZScreenEffect(pMesh,offset), m_bShocked(false), m_fShockStartTime(0.0f),
m_fShockPower(0.0f), m_fLastTime(0.0f), m_ShockOffset(0.0f, 0.0f, 0.0f), m_ShockVelocity(0.0f, 0.0f, 0.0f),
m_nVisualValue(-1)
{


}


void ZBossGaugeEffect::Shock(float fPower)
{
	m_bShocked = true;

	m_fShockStartTime=ZGetGame()->GetTime();
	m_fLastTime = ZGetGame()->GetTime();
	m_fShockPower = max((min(20.0f, 20.0f + fPower)), 70.0f);
}

bool ZBossGaugeEffect::Draw(unsigned long int nTime)
{
	MUID uidBoss = ZGetQuest()->GetGameInfo()->GetBoss();
	if (uidBoss == MUID(0,0)) return true;

	const float fShockDuration=	0.5f;
	const rvector ShockOffset=rvector(0,0,0);
	const rvector ShockVelocity=rvector(0,0,0);

	rvector offset = rvector(0.0f, 0.0f, 0.0f);

	float fElapsed = ZGetGame()->GetTime() - m_fLastTime;

	if (m_bShocked)
	{
		float fA=RandomNumber(0.0f, 1.0f)*2*pi;
		float fB=RandomNumber(0.0f, 1.0f)*2*pi;
		rvector velocity=rvector(cos(fA)*cos(fB), sin(fA)*sin(fB), 0.0f);

		float fPower=(ZGetGame()->GetTime() - m_fShockStartTime) / fShockDuration;
		if(fPower>1.f)
		{
			m_bShocked=false;
		}
		else
		{
			fPower=1.f-fPower;
			fPower=pow(fPower,1.5f);
			m_ShockVelocity = (RandomNumber(0.0f, 1.0f) * m_fShockPower * velocity);
			m_ShockOffset += fElapsed * m_ShockVelocity;
			offset = fPower * m_ShockOffset;
			/*
			char text[256];
			sprintf(text, "%.3f, %.3f\n", offset.x, offset.y);
			OutputDebugString(text);
			*/
		}
	}

	m_fLastTime = ZGetGame()->GetTime();
	offset.z = 0.0f;


	bool ret = ZScreenEffect::DrawCustom(0, offset);

	// HP°ÔÀÌÁö
	ZObject* pBoss = ZGetObjectManager()->GetObject(uidBoss);
	if ((pBoss) && (pBoss->IsNPC()))
	{
		ZActor* pBossActor = (ZActor*)pBoss;
		// AP´Â ³²°í HP´Â 0ÀÌµÅ º¸½º°¡ Á×´Â°æ¿ì°¡ »ý°Ü AP¸¦ ¾Æ¿¹ ±×·ÁÁÖÁö ¾Ê´Â´Ù.
		int nMax = pBossActor->GetActualMaxHP()/* + pBossActor->GetActualMaxAP()*/;
		int nCurr = min(pBossActor->GetActualHP()/* + pBossActor->GetAP()*/, nMax);

		if ((m_nVisualValue < 0) || (m_nVisualValue > nCurr) || (nCurr - m_nVisualValue > 100))
		{
			m_nVisualValue = nCurr;
		}

		if (m_nVisualValue > 0)
		{
			const int width = 433+1;
			const int height = 12;

			int x = (800 - width) * 0.5f;
			int y = 600 * 0.028f;

			float fGaugeWidth = width * (m_nVisualValue / (float)nMax);

			DWORD color = D3DCOLOR_ARGB(255, 0xBB, 0, 0);

			RGetDevice()->SetFVF( D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE );
			RGetDevice()->SetTexture(0,NULL);

			float fx = 183.0f/800.0f + offset.x/980.0f;
			float fy = 574.0f/600.0f - offset.y/720.0f;

			DrawGauge(fx, fy, fGaugeWidth/800.0f, 7.0f/600.0f, 0.0f, color);
		}
	}


	return ret;
}


///////////////////////////////////////////////////////////////////////////////////////
// ZKOEffect //////////////////////////////////////////////////////////////////////////
ZKOEffect::ZKOEffect(RMesh* pMesh, rvector offset) : ZScreenEffect(pMesh, offset)
{

}

void ZKOEffect::InitFrame()
{
	m_VMesh.Stop(ani_mode_lower);
	m_VMesh.m_pMesh->SetFrame(0, 0);
	m_VMesh.Play(ani_mode_lower);
}

void ZKOEffect::SetFrame(int nFrame)
{
	m_VMesh.m_pMesh->SetFrame(nFrame, 0);
}

int ZKOEffect::GetFrame()
{
	AniFrameInfo* pInfo = GetVMesh()->GetFrameInfo(ani_mode_lower);
	return pInfo->m_nFrame;
}

///////////////////////////////////////////////////////////////////////////////////////
// ZTDMBlinkEffect ////////////////////////////////////////////////////////////////////

ZTDMBlinkEffect::ZTDMBlinkEffect(RMesh* pMesh,rvector offset) : ZScreenEffect(pMesh, offset)
{
}

void ZTDMBlinkEffect::SetAnimationSpeed(int nKillsDiff)
{
	float speed = 4.8f;
	if (nKillsDiff > 5)			// Á¨Àå-_-; ÇÏµåÄÚµù
		speed = 9.6f;

	m_VMesh.SetSpeed(speed);
}

///////////////////////////////////////////////////////////////////////////////////////
// ZScreenEffectManager ///////////////////////////////////////////////////////////////
ZScreenEffectManager::ZScreenEffectManager()
{

	m_WeaponType = MWT_NONE;
	m_SelectItemDesc = NULL;

	m_pGaugeTexture = NULL;
	m_pHPGaugeTexture = NULL;
	m_peHPGaugeTexture = NULL;
	m_pAPGaugeTexture = NULL;
	m_peAPGaugeTexture = NULL;
	m_pexpGaugeTexture = NULL;
	m_peexpGaugeTexture = NULL;

	m_pHPPanel = NULL;
	m_pScorePanel = NULL;
	m_pScorePanelTeam = NULL;
	m_pScorePanelSolo = NULL;
	m_pScorePanelCW = NULL;

	m_pBuffPanel = NULL;

	m_pReload = NULL;
	m_pEmpty = NULL;

	for(int i=0;i<MWT_END;i++)
		m_pWeaponIcons[i]=NULL;

	for(int i=0;i<MMS_MAX_RACE;i++)
		m_pWeaponRaceIcons[i]=NULL;

	m_pScoreZombieTeam =	NULL;
	/*m_pHumanDefeat =		NULL;
	m_pHumanVictory =		NULL;*/


	m_pEffectMeshMgr=NULL;

	m_pSpectator = NULL;

	m_bGameStart = false;
	m_nHpReset = 0;

	m_bShowReload = false;
	m_bShowEmpty = false;

	m_pQuestEffectMeshMgr = NULL;
	m_pBossHPPanel = NULL;
	m_pArrow = NULL;
	for (int i = 0; i < 10; i++) m_pKONumberEffect[i] = NULL;
	m_pKO = NULL;
	m_nKO = 0;
}

ZScreenEffectManager::~ZScreenEffectManager()
{
	DestroyQuestRes();
	Destroy();
}

void ZScreenEffectManager::Destroy()
{
	Clear();

	if(m_pGaugeTexture)
	{
		RDestroyBaseTexture(m_pGaugeTexture);
		m_pGaugeTexture=NULL;
	}
	if (m_pHPGaugeTexture) {
		RDestroyBaseTexture(m_pHPGaugeTexture);
		m_pHPGaugeTexture = NULL;
	}
	if (m_peHPGaugeTexture) {
		RDestroyBaseTexture(m_peHPGaugeTexture);
		m_peHPGaugeTexture = NULL;
	}
	if (m_pAPGaugeTexture) {
		RDestroyBaseTexture(m_pAPGaugeTexture);
		m_pAPGaugeTexture = NULL;
	}
	if (m_peAPGaugeTexture) {
		RDestroyBaseTexture(m_peAPGaugeTexture);
		m_peAPGaugeTexture = NULL;
	}
	if (m_pexpGaugeTexture) {
		RDestroyBaseTexture(m_pexpGaugeTexture);
		m_pexpGaugeTexture = NULL;
	}
	if (m_peexpGaugeTexture) {
		RDestroyBaseTexture(m_peexpGaugeTexture);
		m_peexpGaugeTexture = NULL;
	}
	SAFE_DELETE(m_pSpectator);

	SAFE_DELETE(m_pHPPanel);
	SAFE_DELETE(m_pScorePanel);
	SAFE_DELETE(m_pScorePanelTeam);
	SAFE_DELETE(m_pScorePanelSolo);
	SAFE_DELETE(m_pScorePanelCW);
	SAFE_DELETE(m_pBuffPanel);

	SAFE_DELETE(m_pReload);
	SAFE_DELETE(m_pEmpty);

	SAFE_DELETE(m_pWeaponIcons[MWT_DAGGER]);
	SAFE_DELETE(m_pWeaponIcons[MWT_DUAL_DAGGER]);
	SAFE_DELETE(m_pWeaponIcons[MWT_KATANA]);
	SAFE_DELETE(m_pWeaponIcons[MWT_GREAT_SWORD]);
	SAFE_DELETE(m_pWeaponIcons[MWT_DOUBLE_KATANA]);

	SAFE_DELETE(m_pWeaponIcons[MWT_PISTOL]);
	SAFE_DELETE(m_pWeaponIcons[MWT_PISTOLx2]);
	SAFE_DELETE(m_pWeaponIcons[MWT_REVOLVER]);
	SAFE_DELETE(m_pWeaponIcons[MWT_REVOLVERx2]);
	SAFE_DELETE(m_pWeaponIcons[MWT_SMG]);

	SAFE_DELETE(m_pWeaponIcons[MWT_SMGx2]);
	SAFE_DELETE(m_pWeaponIcons[MWT_SHOTGUN]);
	SAFE_DELETE(m_pWeaponIcons[MWT_SAWED_SHOTGUN]);

	SAFE_DELETE(m_pWeaponIcons[MWT_RIFLE]);
	SAFE_DELETE(m_pWeaponIcons[MWT_MACHINEGUN]);
	SAFE_DELETE(m_pWeaponIcons[MWT_ROCKET]);
	SAFE_DELETE(m_pWeaponIcons[MWT_SNIFER]);

	SAFE_DELETE(m_pWeaponIcons[MWT_MED_KIT]);
	SAFE_DELETE(m_pWeaponIcons[MWT_REPAIR_KIT]);
	SAFE_DELETE(m_pWeaponIcons[MWT_BULLET_KIT]);
	SAFE_DELETE(m_pWeaponIcons[MWT_FLASH_BANG]);
	SAFE_DELETE(m_pWeaponIcons[MWT_FRAGMENTATION]);
	SAFE_DELETE(m_pWeaponIcons[MWT_SMOKE_GRENADE]);
	SAFE_DELETE(m_pWeaponIcons[MWT_FOOD]);
	SAFE_DELETE(m_pWeaponIcons[MWT_POTION]);
	SAFE_DELETE(m_pWeaponIcons[MWT_TRAP]);
	SAFE_DELETE(m_pWeaponIcons[MWT_DYNAMITYE]);

	for(int i=0;i<MMS_MAX_RACE;i++)
	{
	SAFE_DELETE(m_pWeaponRaceIcons[i]);
	}

	SAFE_DELETE(m_pScoreZombieTeam );
	/*SAFE_DELETE(m_pHumanDefeat  );
	SAFE_DELETE(m_pHumanVictory  );*/

	for (ItorWeaponIconPotion it=m_mapWeaponIconPotion.begin(); it!=m_mapWeaponIconPotion.end(); ++it)
		delete it->second;
	m_mapWeaponIconPotion.clear();

	for (ItorWeaponIconTrap it=m_mapWeaponIconTrap.begin(); it!=m_mapWeaponIconTrap.end(); ++it)
		delete it->second;
	m_mapWeaponIconTrap.clear();

	SAFE_DELETE(m_pKO);

	for (int i = 0; i < 10; i++) 
	{
		SAFE_DELETE(m_pKONumberEffect[i]);
	}

	SAFE_DELETE(m_pTDScoreBoard);
	SAFE_DELETE(m_pTDScoreBlink_R);
	SAFE_DELETE(m_pTDScoreBlink_B);


	SAFE_DELETE(m_pEffectMeshMgr);	
	SAFE_DELETE(m_pQuestEffectMeshMgr);

	
}

void ZScreenEffectManager::Clear()
{
	m_eraseQueue.clear();
	while(!empty())
	{
		delete *begin();
		pop_front();
	}

	for(int i=0;i<COMBOEFFECTS_COUNT;i++)
		m_pComboEffects[i]=NULL;
}


bool ZScreenEffectManager::Create()
{

	DWORD _begin_time,_end_time;
#define BEGIN_ { _begin_time = timeGetTime(); }
#define END_(x) { _end_time = timeGetTime(); float f_time = (_end_time - _begin_time) / 1000.f; mlog("%s : %f \n", x,f_time ); }

	BEGIN_;

	m_pQuestEffectMeshMgr = new RMeshMgr();
	if(m_pQuestEffectMeshMgr->LoadXmlList("main/combat/screeneffects_quest.xml")==-1) {
		mlog("quest combat list loding error\n");
		SAFE_DELETE(m_pQuestEffectMeshMgr);
		return false;
	}

	m_pEffectMeshMgr = new RMeshMgr;
	if(m_pEffectMeshMgr->LoadXmlList("main/combat/screeneffects.xml")==-1) {
		mlog("combat list loding error\n");
		SAFE_DELETE(m_pEffectMeshMgr);
		return false;
	}

	m_pHPPanel		= new ZScreenEffect(m_pEffectMeshMgr->Get("hppanel"));
	m_pScorePanel	= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_tab.elu"));
	m_pScorePanelTeam	= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_tab_team.elu"));
	m_pScorePanelSolo	= new ZScreenEffect(m_pEffectMeshMgr->Get("SINGLE_ef_in_tab_team.elu"));
	m_pScorePanelCW	= new ZScreenEffect(m_pEffectMeshMgr->Get("Clan_War_ScoreBoard.elu"));

    m_pBuffPanel	= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_tab.elu"));

	m_pSpectator = new ZScreenEffectLetterBox(m_pEffectMeshMgr->Get("spectator"));

	m_pEmpty	= new ZScreenEffect(m_pEffectMeshMgr->Get("empty"));
	m_pReload	= new ZScreenEffect(m_pEffectMeshMgr->Get("reload"));

	m_pWeaponIcons[MWT_DAGGER]			= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_dagger.elu"));
	m_pWeaponIcons[MWT_DUAL_DAGGER]		= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_d_dagger.elu"));
	m_pWeaponIcons[MWT_KATANA]			= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_katana.elu"));
	m_pWeaponIcons[MWT_GREAT_SWORD]		= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_sword.elu"));//±×³É ¿ì¼± °°Àº°Í »ç¿ë
	m_pWeaponIcons[MWT_DOUBLE_KATANA]	= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_blade.elu"));//±×³É ¿ì¼± °°Àº°Í »ç¿ë

	m_pWeaponIcons[MWT_PISTOL]			= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_pistol.elu"));
	m_pWeaponIcons[MWT_PISTOLx2]		= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_d_pistol.elu"));
	m_pWeaponIcons[MWT_REVOLVER]		= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_pistol.elu"));
	m_pWeaponIcons[MWT_REVOLVERx2]		= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_d_pistol.elu"));
	m_pWeaponIcons[MWT_SMG]				= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_smg.elu"));

	m_pWeaponIcons[MWT_SMGx2]			= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_d_smg.elu"));
	m_pWeaponIcons[MWT_SHOTGUN]			= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_shotgun.elu"));
	m_pWeaponIcons[MWT_SAWED_SHOTGUN]	= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_shotgun.elu"));

	m_pWeaponIcons[MWT_RIFLE]			= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_rifle.elu"));
	m_pWeaponIcons[MWT_MACHINEGUN]		= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_machinegun.elu"));
	m_pWeaponIcons[MWT_ROCKET]			= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_rocket.elu"));
	m_pWeaponIcons[MWT_SNIFER]			= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_rifle.elu"));

	m_pWeaponIcons[MWT_MED_KIT]			= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_medikit.elu"));
	m_pWeaponIcons[MWT_REPAIR_KIT]		= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_repairkit.elu"));
	m_pWeaponIcons[MWT_FLASH_BANG]		= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_flashbang.elu"));
	m_pWeaponIcons[MWT_FRAGMENTATION]	= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_grenade.elu"));
	m_pWeaponIcons[MWT_SMOKE_GRENADE]	= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_flashbang.elu"));
	m_pWeaponIcons[MWT_FOOD]			= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_food.elu"));
	m_pWeaponIcons[MWT_BULLET_KIT]		= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_magazine.elu"));

	// Æ÷¼Ç°ú Æ®·¦Àº ´Ù¸¥ ¹è¿­¿¡ °ü¸®ÇÑ´Ù
	m_pWeaponIcons[MWT_POTION]			= NULL;
	m_pWeaponIcons[MWT_TRAP]			= NULL;

	m_pWeaponIcons[MWT_DYNAMITYE]		= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_exgrenade.elu"));

	// Æ÷¼Ç ÃÊ±âÈ­
	m_mapWeaponIconPotion[MMIEI_POTION_HEAL_INSTANT]	= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_hp_capsule.elu"));
	m_mapWeaponIconPotion[MMIEI_POTION_REPAIR_INSTANT]	= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_ap_capsule.elu"));
	m_mapWeaponIconPotion[MMIEI_POTION_HEAL_OVERTIME]	= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_hp_ampulla.elu"));
	m_mapWeaponIconPotion[MMIEI_POTION_REPAIR_OVERTIME]	= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_ap_ampulla.elu"));
	m_mapWeaponIconPotion[MMIEI_POTION_HASTE]			= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_haste_ampulla.elu"));

	// Æ®·¦ ÃÊ±âÈ­
	m_mapWeaponIconTrap[MMDT_FIRE]		= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_firefield.elu"));
	m_mapWeaponIconTrap[MMDT_COLD]		= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_frozenfield.elu"));

	m_pScoreZombieTeam =				  new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_tab_infected.elu"));
	/*m_pHumanDefeat =				  new ZScreenEffect(m_pEffectMeshMgr->Get("human_defeat.elu"));
	m_pHumanVictory =				  new ZScreenEffect(m_pEffectMeshMgr->Get("human_victory.elu"));*/
	m_pWeaponRaceIcons[MMS_ZOMBIE]		= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_normal.elu"));
	m_pWeaponRaceIcons[MMS_ZOMBIE_TANK]		= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_tank.elu"));
	m_pWeaponRaceIcons[MMS_ZOMBIE_NEMESIS]		= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_glimmer.elu"));
	m_pWeaponRaceIcons[MMS_ZOMBIE_GULA]		= new ZScreenEffect(m_pEffectMeshMgr->Get("ef_in_icon_gula.elu"));




	m_pHit = m_pEffectMeshMgr->Get("hit");
	m_pComboBeginEffect = m_pEffectMeshMgr->Get("combo_begin");
	m_pComboEndEffect = m_pEffectMeshMgr->Get("combo_end");
	for(int i=0;i<10;i++)
	{
		char meshname[256];
		sprintf(meshname,"combo%d",i);
		m_pComboNumberEffect[i] = m_pEffectMeshMgr->Get(meshname);

		sprintf(meshname,"exp%d",i);
		m_pExpNumberEffect[i] = m_pEffectMeshMgr->Get(meshname);
	}

	m_pExpPlusEffect = m_pEffectMeshMgr->Get("exp+");
	m_pExpMinusEffect = m_pEffectMeshMgr->Get("exp-");

	for(int i=0;i<COMBOEFFECTS_COUNT;i++)
		m_pComboEffects[i]=NULL;

	m_pPraiseEffect[0] = m_pEffectMeshMgr->Get("allkill");
	m_pPraiseEffect[1] = m_pEffectMeshMgr->Get("unbelievable");
	m_pPraiseEffect[2] = m_pEffectMeshMgr->Get("excellent");
	m_pPraiseEffect[3] = m_pEffectMeshMgr->Get("fantastic");
	m_pPraiseEffect[4] = m_pEffectMeshMgr->Get("headshot");

	m_pGoodEffect = m_pEffectMeshMgr->Get("good");
	m_pNiceEffect = m_pEffectMeshMgr->Get("nice");
	m_pGreatEffect = m_pEffectMeshMgr->Get("great");
	m_pWonderfullEffect = m_pEffectMeshMgr->Get("wonderful");

	m_pCoolEffect = m_pEffectMeshMgr->Get("cool");

	m_pAlertEffect[0] = m_pEffectMeshMgr->Get("alert_front");
	m_pAlertEffect[1] = m_pEffectMeshMgr->Get("alert_right");
	m_pAlertEffect[2] = m_pEffectMeshMgr->Get("alert_back");
	m_pAlertEffect[3] = m_pEffectMeshMgr->Get("alert_left");

	m_CurrentComboLevel=ZCL_NONE;

	m_pHPGaugeTexture = RCreateBaseTexture("main/COMBAT/hpgauge.tga");
	m_peHPGaugeTexture = RCreateBaseTexture("main/COMBAT/e_hpgauge.tga");
	m_pGaugeTexture = RCreateBaseTexture("main/COMBAT/gauge.tga");
	m_pAPGaugeTexture = RCreateBaseTexture("main/COMBAT/apgauge.tga");
	m_peAPGaugeTexture = RCreateBaseTexture("main/COMBAT/e_apgauge.tga");
	m_pexpGaugeTexture = RCreateBaseTexture("main/COMBAT/expgauge.tga");
	m_peexpGaugeTexture = RCreateBaseTexture("main/COMBAT/e_expgauge.tga");


	m_fGaugeHP=m_fGaugeAP=m_fGaugeEXP=0.f;
	m_fCurGaugeHP=m_fCurGaugeAP=-1.f;

	m_pKO = new ZKOEffect(m_pQuestEffectMeshMgr->Get("ko"));
	for (int i = 0; i < 10; i++)
	{
		char name[64];
		sprintf(name, "ko%d", i);
		m_pKONumberEffect[i] = new ZKOEffect(m_pQuestEffectMeshMgr->Get(name));
	}

	m_pTDScoreBoard = new ZScreenEffect(m_pEffectMeshMgr->Get("td_scoreboard"));
	m_pTDScoreBlink_B = new ZTDMBlinkEffect(m_pEffectMeshMgr->Get("td_scoreblink_b"));
	m_pTDScoreBlink_R = new ZTDMBlinkEffect(m_pEffectMeshMgr->Get("td_scoreblink_r"));


	END_("Screen Effect Manager Create");
	return true;
}

void ZScreenEffectManager::Add(ZEffect *pEffect)
{	
	push_back(pEffect); 
}



void DrawGauge(float x, float y, float fWidth, float fHeight, float fLeanDir, DWORD color)
{
#ifndef _EXTRESOLUTION
	if (RGetIsWidthScreen())
	{
		x = (x * 800 + 80) / 960;
		fWidth = fWidth * 800 / 960;
	}
#endif

	struct TLVERTEX {
		float x, y, z, w;
		DWORD color;
		float u, v;
	};

	TLVERTEX ver[4];

#define SETVERTEX(_a,_x,_y,_z,_u,_v,_color) { ver[_a].x=_x;ver[_a].y=_y;ver[_a].z=_z;ver[_a].u=_u;ver[_a].v=_v;ver[_a].color=_color;  ver[_a].w=.1f; }

	float fLean = fHeight*(float)MGetWorkspaceHeight()*fLeanDir;

	int x1, y1, x2, y2;
	x1 = x*(float)MGetWorkspaceWidth();
	y1 = y*(float)MGetWorkspaceHeight();
	x2 = (x + fWidth)*(float)MGetWorkspaceWidth();
	y2 = (y + fHeight)*(float)MGetWorkspaceHeight();

	SETVERTEX(0, x1, y1, 0, 0, 0, color);
	SETVERTEX(1, x2, y1, 0, 1, 0, color);
	SETVERTEX(2, x1 + fLean, y2, 0, 0, 1, color);
	SETVERTEX(3, x2 + fLean, y2, 0, 1, 1, color);

	HRESULT hr = RGetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, ver, sizeof(TLVERTEX));
}
void DrawEXPGauge(float x, float y, float fWidth, float fHeight, float fLeanDir, DWORD color, float currexp)
{
#ifndef _EXTRESOLUTION
	if (RGetIsWidthScreen())
	{
		x = (x * 800 + 80) / 960;
		fWidth = fWidth * 800 / 960;
	}
#endif

	struct TLVERTEX {
		float x, y, z, w;
		DWORD color;
		float u, v;
	};

	TLVERTEX ver[4];

#define SETVERTEX(_a,_x,_y,_z,_u,_v,_color) { ver[_a].x=_x;ver[_a].y=_y;ver[_a].z=_z;ver[_a].u=_u;ver[_a].v=_v;ver[_a].color=_color;  ver[_a].w=.1f; }

	float fLean = fHeight*(float)MGetWorkspaceHeight()*fLeanDir;

	int x1, y1, x2, y2;
	x1 = x*(float)MGetWorkspaceWidth();
	y1 = y*(float)MGetWorkspaceHeight();
	x2 = (x + fWidth)*(float)MGetWorkspaceWidth();
	y2 = (y + fHeight)*(float)MGetWorkspaceHeight();

	SETVERTEX(0, x1, y1, 0, 0, 0, color);
	SETVERTEX(1, x2, y1, 0, currexp, 0, color);
	SETVERTEX(2, x1 + fLean, y2, 0, 0, 1, color);
	SETVERTEX(3, x2 + fLean, y2, 0, currexp, 1, color);

	HRESULT hr = RGetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, ver, sizeof(TLVERTEX));
}

void DrawHPGauge(float x, float y, float fWidth, float fHeight, float fLeanDir, DWORD color, float currhp)
{
#ifndef _EXTRESOLUTION
	if (RGetIsWidthScreen())
	{
		x = (x * 800 + 80) / 960;
		//fWidth = fWidth * 800 / 960;
	}
#endif

	struct TLVERTEX {
		float x, y, z, w;
		DWORD color;
		float u, v;
	};

	TLVERTEX ver[4];

#define SETVERTEX(_a,_x,_y,_z,_u,_v,_color) { ver[_a].x=_x;ver[_a].y=_y;ver[_a].z=_z;ver[_a].u=_u;ver[_a].v=_v;ver[_a].color=_color;  ver[_a].w=.1f; }

	float fLean = fHeight*(float)MGetWorkspaceHeight()*fLeanDir;
	float fLeanTop = fHeight*(float)MGetWorkspaceWidth()*(-1.f / 4);
	float fYTop = fHeight*(float)MGetWorkspaceWidth()*(-1.f / 14);

	int x1, y1, x2, y2;
	x1 = x*(float)MGetWorkspaceWidth();
	y1 = y*(float)MGetWorkspaceHeight();
	x2 = (x + fWidth)*(float)MGetWorkspaceWidth(); // (x + fWidth)*(float)MGetWorkspaceWidth();
	y2 = (y + fHeight)*(float)MGetWorkspaceHeight();

	SETVERTEX(0, x1, y1, 0, 0, 0, color); //top left corner
	SETVERTEX(1, x2, y1, 0, currhp, 0, color); //top right corner
	SETVERTEX(2, x1 + fLean, y2, 0, 0, 1, color); //bottom left corner
	SETVERTEX(3, x2 + fLean, y2, 0, currhp, 1, color); //bottom right corner, texture gets centered instead of far left
	RGetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true); // Alpha mother fucker, fixed but wrecked the colors
	RGetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	RGetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	RGetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	RGetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	RGetDevice()->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	RGetDevice()->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	HRESULT hr = RGetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, ver, sizeof(TLVERTEX));
}
// draw ap gauge
void DrawAPGauge(float x, float y, float fWidth, float fHeight, float fLeanDir, DWORD color, float currap)
{
#ifndef _EXTRESOLUTION
	if (RGetIsWidthScreen())
	{
		x = (x * 800 + 80) / 960;
		fWidth = fWidth * 800 / 960;
	}
#endif

	struct TLVERTEX {
		float x, y, z, w;
		DWORD color;
		float u, v;
	};

	TLVERTEX ver[4];

#define SETVERTEX(_a,_x,_y,_z,_u,_v,_color) { ver[_a].x=_x;ver[_a].y=_y;ver[_a].z=_z;ver[_a].u=_u;ver[_a].v=_v;ver[_a].color=_color;  ver[_a].w=.1f; }

	float fLeanFront = fHeight*(float)MGetWorkspaceHeight()*(-1.f / 1.5); // -0.5.f
	float fLeanBack = fHeight*(float)MGetWorkspaceHeight()*fLeanDir; // -1.f 
	float fLeanBottom = fHeight*(float)MGetWorkspaceWidth()*(1.f / 2.2);
	float fLeanTop = fHeight*(float)MGetWorkspaceWidth()*(1.f / 2.2);
	float maxWidth = 1.f* 165.f / 800.f;
	float fYBottom = (maxWidth - fWidth)*(float)MGetWorkspaceWidth() * (1.f / 25);

	int x1, y1, x2, y2;
	x1 = x*(float)MGetWorkspaceWidth();
	y1 = y*(float)MGetWorkspaceHeight();
	x2 = (x + fWidth)*(float)MGetWorkspaceWidth();
	y2 = (y + fHeight)*(float)MGetWorkspaceHeight();

	SETVERTEX(0, x1, y1, 0, 0, 0, color);
	SETVERTEX(1, x2, y1, 0, currap, 0, color);
	SETVERTEX(2, x1, y2, 0, 0, 1, color);
	SETVERTEX(3, x2 + fLeanBack, y2, 0, currap, 1, color);

	HRESULT hr = RGetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, ver, sizeof(TLVERTEX));
}

void ZScreenEffectManager::ReSetHpPanel()
{
	if(m_pHPPanel->GetVMesh()) {

		AniFrameInfo* pAni = m_pHPPanel->GetVMesh()->GetFrameInfo( ani_mode_lower );

		pAni->m_nFrame = 0;

		if( pAni->m_isPlayDone ) {
			pAni->m_isPlayDone = false;
		}

		pAni->m_pAniSet = NULL;

		m_pHPPanel->GetVMesh()->SetAnimation("play");
	}

	m_nHpReset = 1;
}

void ZScreenEffectManager::SetGauge_HP(float fHP) 
{
	if(m_fCurGaugeHP==-1)
		m_fCurGaugeHP = fHP;

	m_fGaugeHP=fHP; 

	if( m_fCurGaugeHP < m_fGaugeHP) {
		m_fCurGaugeHP = fHP;
	}
}

void ZScreenEffectManager::SetGauge_AP(float fAP)	
{
	if(m_fCurGaugeAP==-1)
		m_fCurGaugeAP = fAP;

	m_fGaugeAP=fAP; 

	if( m_fCurGaugeAP < m_fGaugeAP) {
		m_fCurGaugeAP = fAP;
	}
}

ZScreenEffect* ZScreenEffectManager::GetCurrWeaponImage()
{
	if(m_WeaponType == MWT_NONE) return NULL;

	if(m_WeaponType == MWT_POTION && m_SelectItemDesc)
	{
		ItorWeaponIconPotion it = m_mapWeaponIconPotion.find(m_SelectItemDesc->m_nEffectId);
		if (it != m_mapWeaponIconPotion.end())
			return it->second;
	}

	if(m_WeaponType == MWT_TRAP && m_SelectItemDesc)
	{
		ItorWeaponIconTrap it = m_mapWeaponIconTrap.find(m_SelectItemDesc->m_nDamageType.Ref());
		if (it != m_mapWeaponIconTrap.end())
			return it->second;
	}

	if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_INFECTION &&
		ZGetGameInterface()->GetCombatInterface()->GetTargetCharacter()->GetTeamID()==MMT_RED) {
		 return	m_pWeaponRaceIcons[ZGetGameInterface()->GetCombatInterface()->GetTargetCharacter()->forcedRaceChar];
	}else{
		return m_pWeaponIcons[m_WeaponType];
	}
}


int ZScreenEffectManager::DrawResetGauges()
{
	RGetDevice()->SetFVF( D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE );

	DWORD color = 0xffffffff;

	static float _hp = 0.f;
	static float _ap = 0.f;
	static DWORD _backtime = timeGetTime();

	DWORD newtime = timeGetTime();

	if(_backtime==0)
		_backtime = newtime;

	DWORD delta = newtime - _backtime;

	_hp += 0.002f * delta;
	_ap += 0.002f * delta;

	_backtime = newtime;

	////////////////////////////////////////////

	// ÇÏµåÄÚµå HP °ÔÀÌÁö !
	if(m_pGaugeTexture)
		RGetDevice()->SetTexture(0,m_pGaugeTexture->GetTexture());
	else
		RGetDevice()->SetTexture(0,NULL);


	color = D3DCOLOR_ARGB(255, 238, 71, 55);
	DrawHPGauge(112.f / 800.f, 33.f / 600.f, min(1.f, m_fGaugeHP) * 199.f / 800.f, 13.f / 600.f, 0.f, color, min(1.f, m_fGaugeHP));// ?,? ,?,height 

	color = D3DCOLOR_ARGB(255, 12, 139, 216);
	DrawAPGauge(112.f / 800.f, 49.f / 600.f, min(1.f, m_fGaugeAP) * 199.f / 800.f, 13.f / 600.f, 0.f, color, min(1.f, m_fGaugeAP));


	if(_hp > 1.0f) // Á¾·á
	{
		_hp = 0.f;
		_ap = 0.f;
		_backtime = 0;

		return 0;
	}

	return 1;
}

void ZScreenEffectManager::DrawGauges()
{
	RGetDevice()->SetFVF( D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE );

	DWORD color = 0xffffffff;

	bool render_cur_hp = false;
	bool render_cur_ap = false;

	////////////////////////////////////////////

	if(m_fCurGaugeHP > 1.0f)
		m_fCurGaugeHP = 1.0f;

	if(m_fCurGaugeAP > 1.0f)
		m_fCurGaugeAP = 1.0f;

	if(m_fCurGaugeHP > m_fGaugeHP ) {
		render_cur_hp = true;
		m_fCurGaugeHP -= 0.01f;// * (m_fCurGaugeHP / m_fGaugeHP);
	}
	else {
		m_fCurGaugeHP = m_fGaugeHP;
	}

	////////////////////////////////////////////

	if(m_fCurGaugeAP > m_fGaugeAP ) {
		render_cur_ap = true;
		m_fCurGaugeAP -= 0.01f;// * (m_fCurGaugeAP / m_fGaugeAP);
	}
	else {
		m_fCurGaugeAP = m_fGaugeAP;
	}
	if (m_pGaugeTexture)
		RGetDevice()->SetTexture(0, m_pGaugeTexture->GetTexture());
	else
		RGetDevice()->SetTexture(0, NULL);
	if (m_fGaugeHP == 1.0f)		color = D3DCOLOR_ARGB(255, 238, 71, 55);
	else if (m_fGaugeHP > 0.7f)	color = D3DCOLOR_ARGB(255, 238, 71, 55);
	else if (m_fGaugeHP > 0.3f)	color = D3DCOLOR_ARGB(255, 238, 71, 55);
	else
	color = D3DCOLOR_ARGB(255, 238, 71, 55);
	DrawHPGauge(112.f/800.f , 33.f/600.f , min(1.f,m_fGaugeHP) * 199.f/800.f, 13.f/600.f , 0.f ,color, min(1.f,m_fGaugeHP));// ?,? ,?,height 

	color = D3DCOLOR_ARGB(255, 12, 139, 216);
	DrawAPGauge(112.f/800.f , 49.f/600.f , min(1.f,m_fGaugeAP) * 199.f/800.f , 13.f/600.f , 0.f ,color, min(1.f,m_fGaugeAP));


	RGetDevice()->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE);
	RGetDevice()->SetRenderState( D3DRS_SRCBLEND,   D3DBLEND_SRCALPHA );
	RGetDevice()->SetRenderState( D3DRS_DESTBLEND,  D3DBLEND_INVSRCALPHA );
	RGetDevice()->SetTextureStageState( 0, D3DTSS_ALPHAARG1 , D3DTA_TEXTURE ); //Added to draw alpha, alpha doesn't work for some reason ~ Monckey100
	RGetDevice()->SetTextureStageState( 0, D3DTSS_ALPHAARG2 , D3DTA_DIFFUSE );
	RGetDevice()->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	RGetDevice()->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	RGetDevice()->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	RGetDevice()->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 );
	RGetDevice()->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE );

	//RGetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE,	TRUE);
	if(render_cur_hp) {

		color = 0x60ef0000;

		float x = min(1.f,m_fGaugeHP) * 200.f/800.f;
		float w = (m_fCurGaugeHP-m_fGaugeHP) * 200.f/800.f;

		DrawHPGauge(112.f/800.f , 33.f/600.f , min(1.f,m_fGaugeHP) * 199.f/800.f, 13.f/600.f , 0.f ,color, m_fCurGaugeHP);// ?,? ,?,height 
	}	

	if(render_cur_ap) {

		color = 0x600c8bd8;
		float x = min(1.f, m_fGaugeAP) * 199.f / 800.f;
		float w = (m_fCurGaugeAP - m_fGaugeAP) * 199.f / 800.f;

		//DrawAPGauge(112.f / 800.f + x, 49.f / 600.f, w, 13.f / 600.f, -1.f, color, (m_fCurGaugeHP - m_fGaugeHP));
		DrawAPGauge(112.f / 800.f, 49.f / 600.f, min(1.f, m_fGaugeAP) * 199.f / 800.f, 13.f / 600.f, 0.f, color, m_fCurGaugeAP);// ?,? ,?,height 

	}

	RGetDevice()->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE);

}


void ZScreenEffectManager::Draw()
{
	ZCharacter *pTargetCharacter = ZGetGameInterface()->GetCombatInterface()->GetTargetCharacter();
	if(!pTargetCharacter || !pTargetCharacter->GetInitialized()) return;

	if(!ZGetCombatInterface()->GetObserverMode() && !ZGetCombatInterface()->IsSkupUIDraw())
	{
		RGetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE,	FALSE);
		RGetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

		if(pTargetCharacter) 
		{
			ZItem* pSelectedItem = pTargetCharacter->GetItems()->GetSelectedWeapon();

			if(pSelectedItem){
				if( pSelectedItem->GetItemType() != MMIT_MELEE ) {
					if (pSelectedItem->GetBulletCurrMagazine() <= 0) {
						if(pSelectedItem->isReloadable()==false) {
							m_bShowReload = false;
							m_bShowEmpty = true;
						}
						else {
							m_bShowReload = true;
							m_bShowEmpty = false;
						}
					}
					else {
						m_bShowReload = false;
						m_bShowEmpty = false;
					}
				}
				else {
					m_bShowReload = false;
					m_bShowEmpty = false;
				}
			}
		}

		if( m_bShowReload ) {
			if(m_pReload)
			{
				m_pReload->Update();
				m_pReload->Draw(0);
			}
		}
		else if(m_bShowEmpty) {
			if(m_pEmpty)
			{
				m_pEmpty->Update();
				m_pEmpty->Draw(0);
			}
		}
	}

	LPDIRECT3DDEVICE9 pd3dDevice=RGetDevice();
	pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	if ( !ZGetGame()->IsReplay() || ZGetGame()->IsShowReplayInfo())
	{
		if(ZGetCombatInterface()->IsShowUI())
			DrawEffects(); // ÄÞº¸ ¿¡´Ï¸ÞÀÌ¼Ç µå·Î¿ì

		// ÄÞº¸ÀÌÆåÆ®´Â Á÷Á¢°ü¸®ÇØÁà¾ßÇÑ´Ù
		DrawCombo();
	}

	if(ZGetCombatInterface()->IsShowUI())
	{
		DrawQuestEffects(); // Äù½ºÆ®½Ã K.O ÀÌ¹ÌÁö
		DrawDuelEffects();
		DrawTDMEffects();
	}
}

void ZScreenEffectManager::DrawMyWeaponImage()
{
	if(ZGetGameInterface()->GetCombatInterface()->GetObserverMode()) return;
	if(!ZGetCombatInterface()->IsShowUI()) return;

	// ¹«±â ÀÌ¹ÌÁö
	ZScreenEffect* pWeaponIcon = GetCurrWeaponImage();
	if( pWeaponIcon )
	{
		pWeaponIcon->Update();
		pWeaponIcon->Draw(0);
	}
}

void ZScreenEffectManager::DrawMyBuffImage()
{
	if(ZGetGameInterface()->GetCombatInterface()->GetObserverMode()) return;

	ZCharacter *pTargetCharacter = ZGetGameInterface()->GetCombatInterface()->GetTargetCharacter();
	if(!pTargetCharacter || !pTargetCharacter->GetInitialized()) return;

	// TodoH(»ó) - ÀÚ½ÅÀÇ ¹öÇÁ È¿°ú ¾ÆÀÌÄÜÀ» ±×·Á¾ß ÇÕ´Ï´Ù. ¸®¼Ò½ºµµ ÇÊ¿äÇÕ´Ï´Ù.
}

void ZScreenEffectManager::DrawMyHPPanal(MDrawContext* pDC)
{
	if(ZGetGameInterface()->GetCombatInterface()->GetObserverMode()) return;

	ZCharacter *pTargetCharacter = ZGetGameInterface()->GetCombatInterface()->GetTargetCharacter();
	if(!pTargetCharacter || !pTargetCharacter->GetInitialized()) return;

	if(ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_DUELTOURNAMENT)
	{
		if ( (ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_DUEL) || ( !pTargetCharacter->IsObserverTarget()))
		{
			//		if(g_pGame&&(g_pGame->GetReadyState()==ZGAME_READYSTATE_RUN)) {
			m_pHPPanel->Update();

			if(!ZGetCombatInterface()->IsShowUI())
				return;

			m_pHPPanel->Draw(0);		// Ä³¸¯ÅÍ »óÅÂÃ¢

			bool bDrawGauges = false;
			// ¿¡´Ï¸ÞÀÌ¼ÇÀÌ ³¡³­ÈÄ¿¡~
			if(m_pHPPanel->GetVMesh())
				if( m_pHPPanel->GetVMesh()->GetFrameInfo(ani_mode_lower)->m_isPlayDone )
					bDrawGauges = true;

			if(bDrawGauges) 
			{
				if(m_nHpReset) 	m_nHpReset = DrawResetGauges();
				else  			DrawGauges();		
			}

		}

	}
	else
	{
		ZObserver* pObserver = ZGetGameInterface()->GetCombatInterface()->GetObserver();
		pObserver->DrawPlayerDuelHPAPBar(pDC);
	}
}

void ZScreenEffectManager::DrawSpectator()
{
	// admin ½ºÆåÀº ÁÙÀÌ ¾ø´Ù
	if(!ZGetMyInfo()->IsAdminGrade())
	{
		m_pSpectator->Update();
		m_pSpectator->Draw(timeGetTime());
	}

	ZScreenEffect* pWeaponIcon = GetCurrWeaponImage();
	if( pWeaponIcon )
		pWeaponIcon->DrawCustom(0, rvector(0.0f, 80.0f, 0.0f));

	DrawEffects();
}

void ZScreenEffectManager::ResetSpectator()
{
	m_pSpectator->GetVMesh()->ClearFrame();
}

void ZScreenEffectManager::DrawEffects()
{
	ZEffect* pEffect = NULL;

	for( iterator i=begin(); i!=end();i++)
	{
		pEffect = *i;
		pEffect->Draw(0);
	}

	/*
	for( iterator i=begin(); i!=end();)
	{
	pEffect = *i;

	if(pEffect->Draw(0)==false) {

	delete pEffect;
	i = erase(i);
	} else {
	i++;
	}
	}
	*/
}

void ZScreenEffectManager::UpdateEffects()
{
	for( list<ZEffectList::iterator>::iterator i = m_eraseQueue.begin(); i!=m_eraseQueue.end();i++)
	{
		ZEffectList::iterator ieffect = *i;
		delete *ieffect;
		erase(ieffect);
	}
	m_eraseQueue.clear();

	ZEffect* pEffect = NULL;

	for( iterator i=begin(); i!=end(); ++i)
	{
		pEffect = *i;

		pEffect->Update();
		if(pEffect->IsDeleteTime())
			m_eraseQueue.push_back(i);
	}

	if (!ZGetGameTypeManager()->IsQuestDerived(ZGetGameClient()->GetMatchStageSetting()->GetGameType())) return;

	if (m_pBossHPPanel)
	{
		m_pBossHPPanel->Update();
	}

	// ½ºÆÑÀÌ¸é KO¶û È­»ìÇ¥´Â ±×¸®Áö ¾Ê´Â´Ù.
	if(ZGetGameInterface()->GetCombatInterface())
	{ // ZGetGameInterface()->GetCombatInterface() <- NULLÀÏ °æ¿ì°¡ µé¾î¿Ã¶§°¡ ÀÖÀ½
		if(!ZGetGameInterface()->GetCombatInterface()->GetObserverMode())
		{
			for (int i=0; i<10; i++)
			{
				m_pKONumberEffect[i]->Update();
			}
			m_pKO->Update();
		}
	}
}


void ZScreenEffectManager::AddRoundStart(int nRound)
{
#define ROUND_NUMBER_SPACE	60.f

	if(nRound<0) return;

	ZEffect* pNew = NULL;

	char buffer[32];
	sprintf(buffer,"%d",nRound);
	int nCount=(int)strlen(buffer);

	int nOver=max(nCount-2,0);

	for(int i=0;i<nCount;i++)
	{
		char meshname[256];
		sprintf(meshname,"round%d",buffer[i]-'0');
		RMesh *pMesh = m_pEffectMeshMgr->Get(meshname);
		if(pMesh)
			Add(new ZScreenEffect(pMesh , rvector(ROUND_NUMBER_SPACE*(float)(i-nCount+1+nOver),0,0)));
	}

	RMesh *pMesh = m_pEffectMeshMgr->Get("round");
	if(pMesh)
		Add(new ZScreenEffect(pMesh));

	ZGetGameInterface()->PlayVoiceSound( VOICE_GET_READY, 1300);
}

void ZScreenEffectManager::DrawCombo()
{
	int nFrame,nLastDigit=0;
	for(int i=0;i<COMBOEFFECTS_COUNT;i++)
	{
		if(m_pComboEffects[i]) {

			nLastDigit=i;

			//			nFrame = m_pComboEffects[i]->GetVMesh()->m_nFrame[0];
			nFrame = m_pComboEffects[i]->GetVMesh()->GetFrameInfo(ani_mode_lower)->m_nFrame;

			if(m_pComboEffects[i]->GetVMesh()->isOncePlayDone()) {

				m_pComboEffects[i]->DeleteAfter();
				m_pComboEffects[i]=NULL;
				if(i==0)
				{
					if(m_pComboEffects[1])
						m_pComboEffects[1]->DeleteAfter();
					m_pComboEffects[1]=new ZComboEffect(m_pComboEndEffect);
					Add(m_pComboEffects[1]);
				}
			}
		}
	}

	// °°Àº Å¸ÀÌ¹Ö¿¡ »ç¶óÁöµµ·Ï ÇÏ±â À§ÇØ ¾ÕÀÇ ¼ýÀÚµéµµ 
	// ¸¶Áö¸· ÀÚ¸®¼öÀÇ ÇÁ·¹ÀÓÀÌ¶û °°Àº ÇÁ·¹ÀÓÀ¸·Î µ¹·Á³õ´Â´Ù

	for(int i=2;i<nLastDigit;i++) {
		if(m_pComboEffects[i]) {
			m_pComboEffects[i]->SetFrame(nFrame);
		}
	}
}

void ZScreenEffectManager::SetCombo(int nCombo)
{
	static int combonumbers[COMBOEFFECTS_COUNT]={0,};

	if (nCombo > MAX_COMBO) nCombo = MAX_COMBO;		// 99 ³ÑÀ¸¸é ¿¡·¯³­´Ù

	ZCOMBOLEVEL thislevel;
	if(nCombo<5) thislevel=ZCL_NONE;else
		if(nCombo<10) thislevel=ZCL_GOOD;else
			if(nCombo<15) thislevel=ZCL_NICE;else
				if(nCombo<20) thislevel=ZCL_GREAT;else
					thislevel=ZCL_WONDERFUL;

	if(thislevel>m_CurrentComboLevel)
	{
		switch(thislevel) {
		case ZCL_GOOD	: AddGood();	
			break;
		case ZCL_NICE	: AddNice();
			break;
		case ZCL_GREAT	: AddGreat();
			break;
		case ZCL_WONDERFUL: AddWonderful();
			break;
		}
		m_CurrentComboLevel=thislevel;
	}

	if(thislevel==ZCL_NONE)
		m_CurrentComboLevel=ZCL_NONE;

	if(nCombo<3) return;

	// 0¹øÀº ¾Õ¿¡ "combo" ±ÛÀÚ°¡ ³ªÅ¸³ª´Â ÀÌÆåÆ®
	// 1¹øÀº »ç¶óÁö´Â ÀÌÆåÆ® 2ºÎÅÍ Ã¹¹øÂ° ÀÚ¸® ¼ýÀÚ
	if(m_pComboEffects[0]==NULL)
	{
		m_pComboEffects[0]=new ZComboEffect(m_pComboBeginEffect);
		Add(m_pComboEffects[0]);
	}

	char buffer[32];
	sprintf(buffer,"%d",nCombo);
	int nCount=(int)strlen(buffer);

	for(int i=0;i<nCount;i++)
	{
		int ncurrent=buffer[i]-'0';
		if(combonumbers[i]!=ncurrent || m_pComboEffects[i+2]==NULL)
		{
			combonumbers[i]=ncurrent;

			// ±× ÀÚ¸®¿¡ ¼ýÀÚ°¡ ÀÌ¹Ì ÀÖÀ¸¸é ÇÁ·¹ÀÓÀ» µÚÂÊÀ¸·Î µ¹·Á °ð »ç¶óÁöµµ·Ï ¸¸µç´Ù
			if(m_pComboEffects[i+2]!=NULL)
			{
				RVisualMesh *pMesh=m_pComboEffects[i+2]->GetVMesh();

				if (pMesh)
				{
					AniFrameInfo* pInfo = pMesh->GetFrameInfo(ani_mode_lower);

					if(pInfo->m_pAniSet)
						pInfo->m_nFrame = pInfo->m_pAniSet->GetMaxFrame() - 4800.f*.2f;
				}

				m_pComboEffects[i+2]->DeleteAfter(1.f);
			}

			// ¼ýÀÚ¸¦ Ãß°¡ÇÑ´Ù
			m_pComboEffects[i+2]=new ZComboEffect(m_pComboNumberEffect[ncurrent],rvector(-10.f+40.f*float(i-1),0,0));
			Add(m_pComboEffects[i+2]);
		}
	}
}

void ZScreenEffectManager::AddExpEffect(int nExp)
{
#define EXP_NUMBER_SPACE	30.f

	if(nExp==0) return;
	if (nExp > 0) PlaySoundScoreGet();

	ZEffect* pNew = NULL;

	char buffer[32];
	sprintf(buffer,"%d",abs(nExp));
	int nCount=(int)strlen(buffer);


	for(int i=0;i<nCount;i++)
	{
		float fOffset=EXP_NUMBER_SPACE*(float)(i-nCount+2);
		Add(new ZScreenEffect(m_pExpNumberEffect[buffer[i]-'0'], rvector(fOffset,0,0)));
	}

	float fOffset=EXP_NUMBER_SPACE*(float)(3-nCount);
	Add(new ZScreenEffect(nExp>0 ? m_pExpPlusEffect : m_pExpMinusEffect , rvector(fOffset,0,0)));
}

void ZScreenEffectManager::DrawScoreBoard()
{
	m_pScorePanel->Draw(0);
}

void ZScreenEffectManager::DrawScoreBoardTeam()
{
	m_pScorePanelTeam->Draw(0);
}

void ZScreenEffectManager::DrawScoreBoardZombieTeam()
{
	m_pScoreZombieTeam->Draw(0);
}

void ZScreenEffectManager::DrawScoreBoardSolo()
{
	m_pScorePanelSolo->Draw(0);
}

void ZScreenEffectManager::DrawScoreBoardCW()
{
	m_pScorePanelCW->Draw(0);
}

void ZScreenEffectManager::AddAlert(const rvector& vVictimPos, rvector& vVictimDir, rvector& vAttackerPos)
{
	rvector my_dir = vVictimDir;
	rvector my_pos = vVictimPos;
	rvector attackPos = vAttackerPos;

	my_pos.z = 0.0f;
	attackPos.z = 0.0f;

	Normalize(my_dir);

	rvector dir = attackPos - my_pos;
	Normalize(dir);


	rvector vector1 = my_dir, vector2 = dir;
	vector1.y = -vector1.y;
	vector2.y = -vector2.y;
	float cosAng1 = DotProduct(vector1, vector2);

	float r;
	if (-vector1.y*vector2.x + vector1.x*vector2.y > 0.0f)
	{
		r = (float)(acos(cosAng1));
	}
	else
	{
		r = -(float)(acos(cosAng1));
	}

	float t = (pi / 4.0f);

	int nIndex = -1;
	if (((r > 0) && (r < t)) || ((r <= 0) && (r > -t))) nIndex = 0;
	else if ((r <= -t) && (r > -t * 3)) nIndex = 1;
	else if (((r >= t * 3) && (r <= t * 4)) || ((r <= -t * 3) && (r > -t * 4))) nIndex = 2;
	else if ((r >= t) && (r < t * 3)) nIndex = 3;

	if ((nIndex >= 0) && (nIndex < 4))
	{
		for (iterator itor = begin(); itor != end(); ++itor)
		{
			ZScreenEffect* pEffect = (ZScreenEffect*)(*itor);
			if(pEffect->GetVMesh()->m_pMesh == m_pAlertEffect[nIndex]) return;
		}

		Add(new ZScreenEffect(m_pAlertEffect[nIndex]));
	}

}

void ZScreenEffectManager::PlaySoundScoreFlyby()
{
#ifdef _BIRDSOUND
	ZGetSoundEngine()->PlaySound("if_score_flyby");		// ¾ÆÁ÷ µô·¹ÀÌ Àû¿ë¾ÈµÇ¾î ÀÖÀ½ 
#else
	ZGetSoundEngine()->PlaySound("if_score_flyby",false, 2000);
#endif
}

void ZScreenEffectManager::PlaySoundScoreGet()
{
	ZGetSoundEngine()->PlaySound("if_score_get");
}

void ZScreenEffectManager::AddPraise(int nPraise)
{
	if(nPraise<0 || nPraise>=ZCI_END) return;

	PlaySoundScoreFlyby(); 

	AddScreenEffect(m_pPraiseEffect[nPraise]);

	switch (nPraise)
	{
	case ZCI_ALLKILL:
		ZGetGameInterface()->PlayVoiceSound( VOICE_KILLEDALL, 2000);
		break;
	case ZCI_UNBELIEVABLE:
		ZGetGameInterface()->PlayVoiceSound( VOICE_UNBELIEVABLE, 1300);
		break;
	case ZCI_EXCELLENT:
		ZGetGameInterface()->PlayVoiceSound( VOICE_EXCELLENT, 1000);
		break;
	case ZCI_FANTASTIC:
		ZGetGameInterface()->PlayVoiceSound( VOICE_FANTASTIC, 1500);
		break;
	case ZCI_HEADSHOT:
		ZGetGameInterface()->PlayVoiceSound( VOICE_HEADSHOT, 700);
		break;
	};

}

void ZScreenEffectManager::SetGaugeExpFromMyInfo()
{
	int nExpPercent = ZGetMyInfo()->GetLevelPercent();
	float fRatio = (float)(nExpPercent) / 100.0f;
	SetGauge_EXP(fRatio);
}

void ZScreenEffectManager::AddGood()
{	
	AddScreenEffect(m_pGoodEffect); 
}
void ZScreenEffectManager::AddNice()
{	
	AddScreenEffect(m_pNiceEffect); 
	//	ZGetGameInterface()->PlayVoiceSound( VOICE_NICE, 1000);

}
void ZScreenEffectManager::AddGreat()
{	
	AddScreenEffect(m_pGreatEffect); 
	//	ZGetGameInterface()->PlayVoiceSound( VOICE_GREAT, 800);
}

void ZScreenEffectManager::AddWonderful()
{	
	AddScreenEffect(m_pWonderfullEffect); 
	//	ZGetGameInterface()->PlayVoiceSound( VOICE_WONDERFUL, 1200);
}

void ZScreenEffectManager::AddCool()
{	
	AddScreenEffect(m_pCoolEffect); 
	//	ZGetGameInterface()->PlayVoiceSound( VOICE_COOL, 700);
}

void ZScreenEffectManager::AddRock()
{	
	AddScreenEffect("rock"); 
	ZGetGameInterface()->PlayVoiceSound( VOICE_LETS_ROCK, 1100);
}


bool ZScreenEffectManager::CreateQuestRes()
{
	m_nKO = 0;

	m_pBossHPPanel = new ZBossGaugeEffect(m_pQuestEffectMeshMgr->Get("boss_hppanel"));
	m_pArrow = new ZScreenEffect(m_pQuestEffectMeshMgr->Get("arrow"));

	return true;
}

void ZScreenEffectManager::DestroyQuestRes()
{
	if (m_pBossHPPanel)
	{
		SAFE_DELETE(m_pBossHPPanel);
	}
	if (m_pArrow)
	{
		SAFE_DELETE(m_pArrow);
	}
	//	if (m_pKO)
	//	{
	//		SAFE_DELETE(m_pKO);
	//	}

	//	for (int i = 0; i < 10; i++) 
	//	{
	//		if (m_pKONumberEffect[i]) SAFE_DELETE(m_pKONumberEffect[i]);
	//	}

	/*	if (m_pQuestEffectMeshMgr)
	{
	SAFE_DELETE(m_pQuestEffectMeshMgr);
	}*/
}


void ZScreenEffectManager::DrawQuestEffects()
{
	if (!ZGetGameTypeManager()->IsQuestDerived(ZGetGameClient()->GetMatchStageSetting()->GetGameType())) return;

	if (m_pBossHPPanel)
	{
		if(ZGetCombatInterface()->IsShowUI())
			m_pBossHPPanel->Draw(0);
	}

	// ½ºÆÑÀÌ¸é KO¶û È­»ìÇ¥´Â ±×¸®Áö ¾Ê´Â´Ù.
	if(!ZGetGameInterface()->GetCombatInterface()->GetObserverMode())
	{
		DrawKO();

		if ( ZGetQuest()->IsRoundClear() )
		{
			rvector to = ZGetQuest()->GetGameInfo()->GetPortalPos();
			DrawArrow(to);
		}
	}	
}

void ZScreenEffectManager::AddKO(int nKills)
{
	m_nKO += nKills;

	for (int i = 0; i < 10; i++)
	{
		m_pKONumberEffect[i]->InitFrame();
	}
}

void ZScreenEffectManager::SetKO(int nKills)
{
	m_nKO = nKills;
}

void ZScreenEffectManager::DrawKO()
{
	if ((m_pKO == NULL) || (m_nKO <= 0)) return;

	char buffer[32];
	sprintf(buffer,"%d", m_nKO);
	int nCount=(int)strlen(buffer);


	unsigned int nNowTime = timeGetTime();

	int nFirstNumberFrame = -1;

	for(int i=0;i<nCount;i++)
	{
		int nIndex = buffer[i]-'0';


		if (i > 0)
		{
			// ÇÁ·¹ÀÓÀ» ¸ÂÃá´Ù.
			AniFrameInfo* pInfo = m_pKONumberEffect[nIndex]->GetVMesh()->GetFrameInfo(ani_mode_lower);
			pInfo->m_nFrame = nFirstNumberFrame;

		}

		float fOffset= 40 * (float)(i-nCount+2) - 40;
		m_pKONumberEffect[nIndex]->DrawCustom(nNowTime, rvector(fOffset, 0.0f, 0.0f));

		if (i == 0)
		{
			nFirstNumberFrame = m_pKONumberEffect[nIndex]->GetFrame();
		}

		m_pKONumberEffect[nIndex]->InitFrame();
	}

	AniFrameInfo* pInfo = m_pKONumberEffect[buffer[0]-'0']->GetVMesh()->GetFrameInfo(ani_mode_lower);
	pInfo->m_nFrame = nFirstNumberFrame;

	m_pKO->Draw(nNowTime);
}

void ZScreenEffectManager::DrawArrow(rvector& vTargetPos)
{
	ZCharacter *pTargetCharacter = ZGetGameInterface()->GetCombatInterface()->GetTargetCharacter();
	if(!pTargetCharacter || !pTargetCharacter->GetInitialized()) return;

	rvector at = pTargetCharacter->GetPosition();
	rvector to = vTargetPos;

	rvector dir1, dir2;
	dir1 = pTargetCharacter->GetDirection();
	dir2 = to - at;

	float fAng = GetAngleOfVectors(dir2, dir1);

	const float fOffsetY = 285.0f;

	if (m_pArrow)
	{
		m_pArrow->DrawCustom(0, rvector(0.0f, fOffsetY, 0.0f), fAng);
	}
}

void ZScreenEffectManager::ShockBossGauge(float fPower)
{
	if (m_pBossHPPanel) m_pBossHPPanel->Shock(fPower);
}


void ZScreenEffectManager::DrawDuelEffects()
{
	if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() != MMATCH_GAMETYPE_DUEL) return;

	if (ZGetCombatInterface()->GetObserver()->IsVisible()) return;

	if (ZGetGame()->m_pMyCharacter->GetKils() > 0)
	{
		char buffer[32];
		sprintf(buffer,"%d", ZGetGame()->m_pMyCharacter->GetKils());
		int nCount=(int)strlen(buffer);

		unsigned int nNowTime = timeGetTime();

		int nFirstNumberFrame = -1;

		for(int i=0;i<nCount;i++)
		{
			int nIndex = buffer[i]-'0';

			if (i > 0)
			{
				// ÇÁ·¹ÀÓÀ» ¸ÂÃá´Ù.
				AniFrameInfo* pInfo = m_pKONumberEffect[nIndex]->GetVMesh()->GetFrameInfo(ani_mode_lower);
				pInfo->m_nFrame = nFirstNumberFrame;

			}

			float fOffset= 40 * (float)(i-nCount+2) - 40;
			m_pKONumberEffect[nIndex]->Update();
			m_pKONumberEffect[nIndex]->DrawCustom(nNowTime, rvector(fOffset, 0.0f, 0.0f));


			if (i == 0)
			{
				nFirstNumberFrame = m_pKONumberEffect[nIndex]->GetFrame();
			}

			m_pKONumberEffect[nIndex]->InitFrame();
		}

		AniFrameInfo* pInfo = m_pKONumberEffect[buffer[0]-'0']->GetVMesh()->GetFrameInfo(ani_mode_lower);
		pInfo->m_nFrame = nFirstNumberFrame;

		m_pKO->Update();
		m_pKO->Draw(nNowTime);	
	}
	// KOÃâ·Â
}

void ZScreenEffectManager::UpdateDuelEffects()
{
	for (int i = 0; i < 10; i++)
	{
		m_pKONumberEffect[i]->InitFrame();
	}

	ZRuleDuel* pDuel = (ZRuleDuel*)ZGetGame()->GetMatch()->GetRule();

	//	if (pDuel->QInfo.m_nVictory + 1 >= 3)
	{
		char buffer[32];
		sprintf(buffer,"%d", pDuel->QInfo.m_nVictory);
		int nCount=(int)strlen(buffer);

		for(int i=0;i<nCount;i++)
		{
			char meshname[256];
			sprintf(meshname,"duel%d",buffer[i]-'0');
			RMesh *pMesh = m_pEffectMeshMgr->Get(meshname);
			if(pMesh)
				Add(new ZScreenEffect(pMesh , rvector(60*(float)(i-nCount+2),0,0)));
		}
	}
}


void ZScreenEffectManager::DrawTDMEffects()
{
	if (ZGetGameTypeManager()->IsTeamExtremeGame(ZGetGameClient()->GetMatchStageSetting()->GetGameType())) return;

	unsigned int nNowTime = timeGetTime();

	m_pTDScoreBoard->Update();
	m_pTDScoreBoard->Draw(nNowTime);

	int nBlueKills = ZGetGame()->GetMatch()->GetTeamKills(MMT_BLUE);
	int nRedKills = ZGetGame()->GetMatch()->GetTeamKills(MMT_RED);
	int diff = abs(nRedKills - nBlueKills);


	if (nBlueKills > nRedKills)
	{
		m_pTDScoreBlink_B->SetAnimationSpeed(diff);
		m_pTDScoreBlink_B->Update();
		m_pTDScoreBlink_B->Draw(nNowTime);
	}
	else if (nRedKills > nBlueKills)
	{
		m_pTDScoreBlink_R->SetAnimationSpeed(diff);
		m_pTDScoreBlink_R->Update();
		m_pTDScoreBlink_R->Draw(nNowTime);
	}

}