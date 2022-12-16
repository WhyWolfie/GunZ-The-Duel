Gamemode: Gungame (Client & Serverside)<br>

Add (CSCommon/MMatchRuleGunGame.h) <br>
Add (CSCommon/GunGame.h) <br>
Add (CSCommon/GunGame.cpp) <br>
Add (CSCommon/MMatchRuleGunGame.cpp) <br>
Add (CSCommon/MMatchRuleGunGame.h) <br>

Add (Gunz/ZRuleGunGame.cpp) <br>
Add (Gunz/ZRuleGunGame.h) <br>

gungame.xml in Matchserver folder <br>

Open(MBaseGameType.h) <br>
Find <br>

	enum MMATCH_GAMETYPE {

Add <br>

	MMATCH_GAMETYPE_GUNGAME				=23,

Open(MMatchRule.h) <br>
Find <br>

	inline bool IsGameRuleDeathMatch(MMATCH_GAMETYPE nGameType)
	{


Add <br>

	(nGameType == MMATCH_GAMETYPE_GUNGAME) ||



Open(MMatchTransDataType.h) <br>
Find <br>

	#pragma pack(push, old)
	#pragma pack(1)

Add <br>

	//Gungame
	struct GGWeaponSet
	{
		UINT WeaponSet[3];
	};

Open(MSharedCommandTable.h) <br>
Find <br>

	#define MC_MATCH_REPORT                         50019

Add <br>

	//Packets
	#define MC_MATCH_GUNGAME_SEND_NEW_WEAPON		50078
	#define MC_MATCH_GUNGAME_SET					50079

Open(MBaseGameType.cpp) <br>
Find <br>

	#define MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR		"Death Match(Solo)"

Add <br>

	#define MMATCH_GAMETYPE_GUNGAME_STR				"GunGame"


Find <br>

	const char* MMatchGameTypeAcronym[MMATCH_GAMETYPE_MAX] = {

Add <br>

	"QSTC",		//GUNGAME


Find <br>

	_InitGameType(MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR,  1.0f,			1.0f,					0.0f);


Add <br>

	_InitGameType(MMATCH_GAMETYPE_GUNGAME,			MMATCH_GAMETYPE_GUNGAME,			MMATCH_GAMETYPE_GUNGAME_STR,		  1.0f,			1.0f,					0.0f);

Open(MMatchServer.cpp) <br>
Find <br>

	#include "MAsyncDBJob_GetBRDescription.h"
	#include "MAsyncDBJob_InsertCharBRInfo.h"
	#include "MAsyncDBJob_UpdateCharBRInfo.h"
	#include "MAsyncDBJob_RewardCharBR.h"

Add <br>

	#include "GunGame.h"


Find <br>

	if (!MGetChannelRuleMgr()->ReadXml(FILENAME_CHANNELRULE))
	{
		Log(LOG_PROG, "Load ChannelRule.xml Failed\n");
		return false;
	}

Add <br>

	if (!MGetChannelRuleMgr()->ReadXml(FILENAME_CHANNELRULE))
	{
		Log(LOG_PROG, "Load ChannelRule.xml Failed\n");
		return false;
	}

Open(MMatchStage.cpp) <br>
Find <br>

	#include "MMatchRuleBerserker.h"
	#include "MMatchRuleDuel.h"
	#include "MMatchRuleDuelTournament.h"
	#include "MMatchCRC32XORCache.h"

Add <br>

	#include "MMatchRuleGunGame.h"

Find <br>

	case MMATCH_GAMETYPE_DUEL:
		{
			return (new MMatchRuleDuel(this));
		}
		break;

Add <br>

	case MMATCH_GAMETYPE_GUNGAME:
		{
			return (new MMatchRuleGunGame(this));
		}
		break;

Open(MSharedCommandTable.cpp) <br>
Find <br>


	C(MC_MATCH_DUELTOURNAMENT_GAME_PLAYER_STATUS, "Match.DuelTournament.Game Player Status Info", "Duel Tournament Game Player Status Info", MCDT_MACHINE2MACHINE)
		P(MPT_UID, "PlayerUID")
		P(MPT_FLOAT, "PlayerAttackPoint")
		P(MPT_FLOAT, "PlayerHealthPoint")
		P(MPT_FLOAT, "PlayerAmorPoint");

Add <br>

	//Gungame
	C(MC_MATCH_GUNGAME_SEND_NEW_WEAPON, "New.GG.Weap", "New GG Weap", MCDT_MACHINE2MACHINE)
		P(MPT_UID, "uidAttacker")
		P(MPT_UINT, "Weapon1")
		P(MPT_UINT, "Weapon2")
		P(MPT_UINT, "Weapon3")
		P(MPT_BOOL, "suicide")
	C(MC_MATCH_GUNGAME_SET, "Set.ID", "Set ID", MCDT_MACHINE2MACHINE)
		P(MPT_BLOB, "itemSets")

Open(ZCombatInterface.cpp) <br>
Find <br>

	DrawSoloSpawnTimeMessage(pDC);

Add <br>

			if (ZGetGame()->GetMatch()->GetMatchType()== MMATCH_GAMETYPE_GUNGAME)
				{
				 char buffer[256];
				 sprintf(buffer,"[Level %d / %d ]", ZGetGame()->m_pMyCharacter->GetKils(), ZGetGame()->GetMatch()->GetRoundCount());
				 TextRelative(pDC,660.f/800.f,480.f/600.f,buffer);
				}

Find <br>

	void ZCombatInterface::Update(float fElapsed)

Add Above <br>

	void ZCombatInterface::GunGame(ZCharacter* pCharacter,const int Level)
	{

	}


Open(ZCombatInterface.h) <br>
Find <br>

	bool IsTeamChat() { return m_Chat.IsTeamChat(); }
	bool IsMenuVisible() { return m_bMenuVisible; }

Add <br>


	 void GunGame(ZCharacter* pCharacter, int GunLevel);
		int AddGunLevel(){return m_nGunLevel++;};


Open(ZCommandUDPHackShield.cpp) <br>
Find <br>

	AddDeniedCommand(MC_MATCH_FLAG_EFFECT);
	AddDeniedCommand(MC_MATCH_FLAG_CAP);
	AddDeniedCommand(MC_MATCH_FLAG_STATE);

Add <br>

	AddDeniedCommand(MC_MATCH_GUNGAME_SET);
	AddDeniedCommand(MC_MATCH_GUNGAME_SEND_NEW_WEAPON);

Open(ZGame.cpp) <br>
Find <br>

	#include "ZRuleDuel.h"
	#include "ZRuleDeathMatch.h"
	#include "ZMyCharacter.h"
	#include "MMatchCRC32XORCache.h"
	#include "MMatchObjCache.h"

Add <br>

	#include "ZRuleGunGame.h"

Find <br>

	else if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_DUELTOURNAMENT)
	{

Add <br>

	else if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_GUNGAME) {
		ZRuleGunGame* pRule = (ZRuleGunGame*)ZGetGame()->GetMatch()->GetRule();
		int itemCount = (int)pRule->GetMatchSet().size();
		nWritten = zfwrite(&itemCount, sizeof(int), 1, m_pReplayFile);
		if (nWritten == 0)
			goto RECORDING_FAIL;

		const vector<GGWeaponSet> items = pRule->GetMatchSet();
		nWritten = zfwrite((void*)&items[0], sizeof(GGWeaponSet), itemCount, m_pReplayFile);
		if (nWritten == 0) goto RECORDING_FAIL;
	}

Find <br>

	bool ZGame::OnRuleCommand(MCommand* pCommand)
	{
	#ifdef _QUEST
		if (ZGetGame()->GetMatch()->IsQuestDrived())
		{
			if (ZGetQuest()->OnGameCommand(pCommand))
				return true;
		}
	#endif


Add <br>

	switch (m_Match.GetMatchType())
	{
	case MMATCH_GAMETYPE_GUNGAME:
	{
		return m_Match.OnCommand(pCommand);
	}
	break;
	default:
		break;
	}

Open(ZGameInterface.cpp) <br>
Find <br>

	SetBitSet(quick_join_param.nModeEnum, MMATCH_GAMETYPE_ASSASSINATE);

Add <br>

	SetBitSet(quick_join_param.nModeEnum, MMATCH_GAMETYPE_GUNGAME);


Open(ZReplay.cpp) <br>
Find <br>

	#include "ZRuleDuel.h"
	#include "ZRuleDuelTournament.h"
	#include "ZRuleDeathMatch.h"
	#include "ZWorldItem.h"

Add <br>

	#include "ZRuleGunGame.h"

Find <br>

		if(m_StageSetting.nGameType==MMATCH_GAMETYPE_DUELTOURNAMENT)


Add <br>

	if (m_StageSetting.nGameType == MMATCH_GAMETYPE_GUNGAME)
	{
		ZRuleGunGame* pRule = (ZRuleGunGame*)ZGetGameInterface()->GetGame()->GetMatch()->GetRule();
		
		int itemCount;
		int Read = zfread(&itemCount, sizeof(int), 1, file);
		if (Read == 0)
			return false;
		
		GGWeaponSet itemSet;
		for (int i = 0; i < itemCount; ++i)
		{
			Read = zfread(&itemSet, sizeof(GGWeaponSet), 1, file);
			pRule->matchSet.push_back(itemSet);
		}
	}


Open(ZRule.cpp) <br>
Find <br>

	#include "ZRuleDuel.h"
	#include "ZRuleDuelTournament.h"


Add <br>

	#include "ZRuleGunGame.h"

Open(ZStageInterface.cpp) <br>
Find <br>

	case MMATCH_GAMETYPE_DEATHMATCH_SOLO:
			color = SDM_COLOR;
			break;

Add <br>

	case MMATCH_GAMETYPE_GUNGAME:


Find <br>

	MAnimation* pAniMapImg = (MAnimation*)pResource->FindWidget( "Stage_MapNameBG");
	bool bQuestUI = false, bSpyUI = false;

Add <br>

	(pSetting->nGameType == MMATCH_GAMETYPE_GUNGAME) ||

Find<br>

	MWidget* pWidget = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "StageRoundCountLabel");
	if ( pWidget)

Add <br>

	(pSetting->nGameType == MMATCH_GAMETYPE_GUNGAME) ||


Open(ZGameInterface.cpp) <br>
Find <br>

	ZGetGameTypeManager()->SetGameTypeStr( MMATCH_GAMETYPE_DUEL, ZMsg( MSG_MT_DUEL));

Add <br>

	ZGetGameTypeManager()->SetGameTypeStr(MMATCH_GAMETYPE_GUNGAME, "GunGame");


Open(ZCharacterItem.cpp) <br>
Find <br>

	if (pDesc == NULL) { _ASSERT(0); return false; }

Replace <br>

	if (pDesc == NULL) { _ASSERT(0); return false; }

Find <br>

	//_ASSERT( (parts == MMCIP_MELEE)   || (parts == MMCIP_PRIMARY) || (parts == MMCIP_SECONDARY) 
			//|| (parts == MMCIP_CUSTOM1) || (parts == MMCIP_CUSTOM2) );


Replace <br>

	_ASSERT( (parts == MMCIP_MELEE)   || (parts == MMCIP_PRIMARY) || (parts == MMCIP_SECONDARY) 
			|| (parts == MMCIP_CUSTOM1) || (parts == MMCIP_CUSTOM2) );

Find <br>

	size_t n;
	for(int i=0;i<numCharItemParts;i++)
	{
		int idxParts = Converter::convert(i, nReplayVersion);
		ZItem *pItem=GetItem(MMatchCharItemParts(idxParts));
		int nBullet;
		n=zfread(&nBullet,sizeof(nBullet),1,file);
		pItem->SetBulletSpare(nBullet);
		if(n!=1) return false;

		int nBulletCurrMagazine;
		n=zfread(&nBulletCurrMagazine,sizeof(nBulletCurrMagazine),1,file);
		pItem->SetBulletCurrMagazine(nBulletCurrMagazine);
		if(n!=1) return false;
	}


Replace <br>

	//size_t n;
	for(int i=0;i<numCharItemParts;i++)
	{
		int idxParts = Converter::convert(i, nReplayVersion);
		ZItem *pItem=GetItem(MMatchCharItemParts(idxParts));
		int nBullet;
		int n=zfread(&nBullet,sizeof(nBullet),1,file);
		pItem->SetBulletSpare(nBullet);
		if(n!=1) return false;

		int nBulletCurrMagazine;
		n=zfread(&nBulletCurrMagazine,sizeof(nBulletCurrMagazine),1,file);
		pItem->SetBulletCurrMagazine(nBulletCurrMagazine);
		if(n!=1) return false;
	}

Open(ZCharacter.h) <br>
Find <br>

	const char *GetUserName()			{ return m_pMUserAndClanName->Ref().m_szUserName;	}

Add <br>

	const char *GetCharName()			{ return m_pMUserAndClanName->Ref().m_szUserName;	}

System/Matchserver (ChannelRule.xml) <br>

		<GAMETYPE id="23" />


System/Matchserver (Gametypecfg.xml) <br>

	<GAMETYPE id="23">	<!-- GAMETYPE_GUNGAME -->
		<ROUNDS    round="10"	str="10" />
		<ROUNDS    round="20"	str="20" />
		<ROUNDS    round="30"	str="30" />
		<ROUNDS    round="50"	str="50" default="true" />
		<ROUNDS    round="70"	str="70" />
		<ROUNDS    round="100"	str="100" />
		<LIMITTIME sec="99999"	str="STR:GAMETYPECFG_LIMITTIME_INFINITE" />
		<LIMITTIME sec="10"	str="STR:GAMETYPECFG_LIMITTIME_10MIN" />
		<LIMITTIME sec="20"	str="STR:GAMETYPECFG_LIMITTIME_20MIN" />
		<LIMITTIME sec="30"	str="STR:GAMETYPECFG_LIMITTIME_30MIN" default="true" />
		<LIMITTIME sec="40"	str="STR:GAMETYPECFG_LIMITTIME_40MIN" />
		<LIMITTIME sec="50"	str="STR:GAMETYPECFG_LIMITTIME_50MIN" />
		<LIMITTIME sec="60"	str="STR:GAMETYPECFG_LIMITTIME_60MIN" />
		<MAXPLAYERS player="4"  str="4" />
		<MAXPLAYERS player="8"  str="8" default="true" />
		<MAXPLAYERS player="12" str="12" />
		<MAXPLAYERS player="16" str="16" />
	</GAMETYPE>


Credits To Jetman. <br>
