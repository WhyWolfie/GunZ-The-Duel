#ifndef __ZSCREENEFFECTMANAGER_H
#define __ZSCREENEFFECTMANAGER_H

#include "ZEffectManager.h"
#include "RMeshUtil.h"


enum ZCOMBOLEVEL {
	ZCL_NONE = 0,
	ZCL_GOOD,
	ZCL_NICE,
	ZCL_GREAT,
	ZCL_WONDERFUL
};



class ZScreenEffect : public ZEffect{	// 화면좌표계에 뿌려지는 이펙트 (UI 관련)
protected:
	RealSpace2::RVisualMesh m_VMesh;	
	rvector	m_Offset;

public:
	ZScreenEffect(RMesh* pMesh,rvector offset=rvector(0,0,0));
	virtual bool Draw(unsigned long int nTime);
	virtual void Update();
	virtual bool IsDeleteTime();
	bool DrawCustom(unsigned long int nTime, rvector& offset, float fAngle=0.0f);
	RealSpace2::RVisualMesh *GetVMesh() { return &m_VMesh; }
	void SetOffset(rvector& offset) { m_Offset = offset; }
};


class ZScreenEffectLetterBox : public ZScreenEffect{
public:
	ZScreenEffectLetterBox(RMesh *pMesh,rvector offset=rvector(0,0,0))
		:ZScreenEffect(pMesh,offset) {}
	virtual bool Draw(unsigned long int nTime);
};


class ZComboEffect : public ZScreenEffect {
public:
	bool bDelete;
	float fDeleteTime;
	ZComboEffect(RMesh* pMesh,rvector offset=rvector(0,0,0));
	virtual bool Draw(unsigned long int nTime);
	void SetFrame(int nFrame);
	void DeleteAfter(float fTime=0.f);
};

class ZBossGaugeEffect : public ZScreenEffect {
private:
	int			m_nVisualValue;
	bool		m_bShocked;
	float		m_fShockStartTime;
	float		m_fShockPower;
	float		m_fLastTime;
	rvector		m_ShockOffset;
	rvector		m_ShockVelocity;
public:
	ZBossGaugeEffect(RMesh* pMesh,rvector offset=rvector(0,0,0));
	void Shock(float fPower);
	virtual bool Draw(unsigned long int nTime);
};

class ZKOEffect : public ZScreenEffect {
public:
	ZKOEffect(RMesh* pMesh,rvector offset=rvector(0,0,0));
	void SetFrame(int nFrame);
	void InitFrame();
	int GetFrame();
};

class ZTDMBlinkEffect : public ZScreenEffect
{
public:
	ZTDMBlinkEffect(RMesh* pMesh,rvector offset=rvector(0,0,0));
	void SetAnimationSpeed(int nKillsDiff);
};



class ZScreenEffectManager : public ZEffectList {
private:
	RMeshMgr*		m_pEffectMeshMgr;
	RMeshMgr*		m_pQuestEffectMeshMgr;
	list<ZEffectList::iterator>	m_eraseQueue;

	ZCOMBOLEVEL m_CurrentComboLevel;

	RMesh*	m_pHit;
	RMesh*	m_pComboBeginEffect;
	RMesh*	m_pComboEndEffect;
	RMesh*	m_pComboNumberEffect[10];
	RMesh*	m_pExpPlusEffect;
	RMesh*	m_pExpMinusEffect;
	RMesh*	m_pExpNumberEffect[10];

	RBaseTexture*  m_pexpGaugeTexture;
	RBaseTexture*  m_peexpGaugeTexture;
	RBaseTexture*  m_peAPGaugeTexture;
	RBaseTexture*  m_pAPGaugeTexture;
	RBaseTexture*  m_pHPGaugeTexture;
	RBaseTexture*  m_peHPGaugeTexture;

	RMesh*	m_pPraiseEffect[ZCI_END];

	/*
	RMesh*	m_pExcellentEffect;
	RMesh*	m_pAllkillEffect;
	RMesh*	m_pHeadshotEffect;
	RMesh*	m_pFantasticEffect;
	RMesh*	m_pUnbelievableEffect;
	*/

	RMesh*	m_pGoodEffect;
	RMesh*	m_pNiceEffect;
	RMesh*	m_pGreatEffect;
	RMesh*	m_pWonderfullEffect;

	RMesh*	m_pCoolEffect;

	RMesh*	m_pAlertEffect[4];

	ZScreenEffect*	m_pHPPanel;
	ZScreenEffect*	m_pScorePanel;
	ZScreenEffect*	m_pBuffPanel;

	ZScreenEffect*	m_pScorePanelTeam;
	ZScreenEffect*	m_pScorePanelSolo;
	ZScreenEffect*	m_pScorePanelCW;

	ZScreenEffect*	m_pWeaponIcons[MWT_END];

	ZScreenEffect*	m_pScoreZombieTeam;
	ZScreenEffect*	m_pWeaponRaceIcons[MMS_MAX_RACE];
	/*ZScreenEffect*	m_pHumanDefeat;
	ZScreenEffect*	m_pHumanVictory;*/

	
	// 포션류(앰플,캡슐)와 트랩류는 따로 관리한다
	typedef map<MMatchItemEffectId, ZScreenEffect*>		MapWeaponIconPotion;
	typedef MapWeaponIconPotion::iterator				ItorWeaponIconPotion;
	MapWeaponIconPotion m_mapWeaponIconPotion;
	
	typedef map<MMatchDamageType, ZScreenEffect*>		MapWeaponIconTrap;
	typedef MapWeaponIconTrap::iterator					ItorWeaponIconTrap;
	MapWeaponIconTrap m_mapWeaponIconTrap;

	ZScreenEffect* GetCurrWeaponImage();

	ZScreenEffectLetterBox*	m_pSpectator;
	
#define COMBOEFFECTS_COUNT	5
	ZComboEffect	*m_pComboEffects[COMBOEFFECTS_COUNT];

	RBaseTexture	*m_pGaugeTexture;

	void DrawGauges();

	float m_fGaugeHP,m_fGaugeAP,m_fGaugeEXP;
	float m_fCurGaugeHP,m_fCurGaugeAP;

	bool m_bGameStart;

	MMatchWeaponType	m_WeaponType;
	MMatchItemDesc*		m_SelectItemDesc;

	int	m_nHpReset;

	ZScreenEffect*	m_pReload;
	ZScreenEffect*	m_pEmpty;

	bool m_bShowReload;
	bool m_bShowEmpty;

	// 퀘스트 관련
	ZBossGaugeEffect*	m_pBossHPPanel;
	ZScreenEffect*		m_pArrow;
	ZKOEffect*			m_pKONumberEffect[10];
	ZKOEffect*			m_pKO;
	int					m_nKO;

	ZScreenEffect*		m_pTDScoreBoard;
	ZTDMBlinkEffect*	m_pTDScoreBlink_R;
	ZTDMBlinkEffect*	m_pTDScoreBlink_B;
protected:
	void DrawCombo();
	void PlaySoundScoreFlyby();
	void PlaySoundScoreGet();
	void DrawQuestEffects();
	void DrawDuelEffects();
	void DrawTDMEffects();
	void DrawArrow(rvector& vTargetPos);
	void DrawKO();
public:
	void DrawEffects();

	ZScreenEffectManager();
	~ZScreenEffectManager();

	bool Create();
	void Destroy();
	bool CreateQuestRes();		// 퀘스트용 리소스 로드
	void DestroyQuestRes();

	int GetCount() { return (int)size();}

	void Clear();

	void Draw();
	void DrawScoreBoard();
	void DrawScoreBoardTeam();
	void DrawScoreBoardSolo();
	void DrawScoreBoardCW();
	void DrawScoreBoardZombieTeam();
	

	void DrawSpectator();
	void DrawMyHPPanal(MDrawContext* pDC);
	void DrawMyWeaponImage();
	void DrawMyBuffImage();

	void ResetSpectator();

	int  DrawResetGauges();

	void UpdateEffects();

	void SetGameStart(bool b) {
		m_bGameStart = b;
	}

	void ReSetHpPanel();

	void SetGauge_HP(float fHP); 
	void SetGauge_AP(float fAP);
	void SetGauge_EXP(float fEXP) {	
		m_fGaugeEXP=fEXP; 
	}

	void SetGaugeExpFromMyInfo();

	void SetWeapon(MMatchWeaponType wtype,MMatchItemDesc* pDesc) {
		m_WeaponType=wtype; 
		m_SelectItemDesc = pDesc;
	}

	void Add(ZEffect *pEffect);

	// screen 레벨 인터페이스의 이펙트들
	void AddScreenEffect(RMesh *pMesh,rvector offset=rvector(0,0,0)) { 
		if(pMesh) Add(new ZScreenEffect(pMesh,offset));	
	}

	void AddScreenEffect(char *szEffectName,rvector offset=rvector(0,0,0)) { 
		AddScreenEffect(m_pEffectMeshMgr->Get(szEffectName),offset);	
	}

	ZScreenEffect* CreateScreenEffect(char *szEffectName,rvector offset=rvector(0,0,0)) { 
		return new ZScreenEffect(m_pEffectMeshMgr->Get(szEffectName),offset); 
	}

	void SetCombo(int nCombo);
	void AddExpEffect(int nExp);

	void AddRoundStart(int nRound);

	void AddFinalRoundStart()	{	AddScreenEffect("finalround");		ZGetGameInterface()->PlayVoiceSound( VOICE_FINAL_ROUND, 1000);	}

	void AddRoundFinish()		{	AddScreenEffect("finishround"); }
	void AddRock();

	void AddWin()				{	AddScreenEffect("win"); }
	void AddLose()				{	AddScreenEffect("lose"); }
	void AddDraw()				{	AddScreenEffect("draw"); }

	void AddHit()				{	AddScreenEffect("hit"); }
	
	void AddHumanVicory()		{	AddScreenEffect("hvictory"); }
	void AddHumanDefeat()		{	AddScreenEffect("hdefeat"); }
	
	void AddPraise(int nPraise);	// Score로 날라가는 이펙트
	void AddGood();
	void AddNice();
	void AddGreat();
	void AddWonderful();
	void AddCool();

	void ShowReload(bool b) {
		m_bShowReload = b;
	}

	void ShowEmpty(bool b) {
		m_bShowEmpty = b;
	}

	void AddAlert(const rvector& vVictimPos, rvector& vVictimDir, rvector& vAttackerPos);
	void AddKO(int nKills=1);
	void SetKO(int nKills);

	void ShockBossGauge(float fPower);

	void UpdateDuelEffects();		// 연승
};

#endif