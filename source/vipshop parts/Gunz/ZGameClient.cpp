#include "stdafx.h"

#include <winsock2.h>
#include "MErrorTable.h"
#include "ZConfiguration.h"
#include "ZGameClient.h"
#include "MSharedCommandTable.h"
#include "ZConsole.h"
#include "MCommandLogFrame.h"
#include "ZIDLResource.h"
#include "MBlobArray.h"
#include "ZInterface.h"
#include "ZApplication.h"
#include "ZGameInterface.h"
#include "MMatchGlobal.h"
#include "MMatchChannel.h"
#include "MMatchStage.h"
#include "ZCommandTable.h"
#include "ZPost.h"
#include "ZPostLocal.h"
#include "MMatchNotify.h"
#include "ZMatch.h"
#include "MComboBox.h"
#include "MTextArea.h"
#include "ZCharacterViewList.h"
#include "ZCharacterView.h"
#include "MDebug.h"
#include "ZScreenEffectManager.h"
#include "ZNetmarble.h"
#include "ZRoomListBox.h"
#include "ZPlayerListBox.h"
#include "ZChat.h"
#include "ZWorldItem.h"
#include "ZChannelRule.h"
#include "ZNetRepository.h"
#include "ZMyInfo.h"
#include "MToolTip.h"
#include "ZColorTable.h"
#include "ZClan.h"
#include "ZSecurity.h"
#include "ZItemDesc.h"
#include "ZCharacterSelectView.h"
#include "ZChannelListItem.h"
#include "ZCombatInterface.h"
#include "ZLocale.h"
#include "ZMap.h"
#include "UPnP.h"
#include "MMD5.h"
#include "ZPlayerManager.h"


												// Update sgk 0760 end


#ifdef LOCALE_NHNUSA
#include "ZNHN_USA.h"
#include "ZNHN_USA_Report.h"
#endif

#ifdef _GAMEGUARD
#include "ZGameGuard.h"
#endif



bool GetUserGradeIDColor(MMatchUserGradeID gid,MCOLOR& UserNameColor,char* sp_name);

MCommand* ZNewCmd(int nID)
{
	MCommandDesc* pCmdDesc = ZGetGameClient()->GetCommandManager()->GetCommandDescByID(nID);

	MUID uidTarget;
	if (pCmdDesc->IsFlag(MCDT_PEER2PEER)==true)
		uidTarget = MUID(0,0);
	else
		uidTarget = ZGetGameClient()->GetServerUID();

	MCommand* pCmd = new MCommand(nID, 
								  ZGetGameClient()->GetUID(), 
								  uidTarget, 
								  ZGetGameClient()->GetCommandManager());
	return pCmd;
}


bool GetUserInfoUID(MUID uid,MCOLOR& _color,char* sp_name,MMatchUserGradeID& gid)
{
	if( ZGetGameClient() == NULL)
		return false;

//	MMatchUserGradeID gid = MMUG_FREE;

	MMatchObjCache* pObjCache = ZGetGameClient()->FindObjCache(uid);

	if(pObjCache) {
		gid = pObjCache->GetUGrade();
	}

	return GetUserGradeIDColor(gid,_color,sp_name);
}


extern MCommandLogFrame* m_pLogFrame;
extern ZIDLResource	g_IDLResource;



bool ZPostCommand(MCommand* pCmd) 
{
	// Replay 중에는 아래 나열한 커맨드만 전송 허용
	if (ZGetGame() && ZGetGame()->IsReplay())
	{
		switch(pCmd->GetID())
		{
		case MC_CLOCK_SYNCHRONIZE:
		case MC_MATCH_USER_WHISPER:
		case MC_MATCH_CHATROOM_JOIN:
		case MC_MATCH_CHATROOM_LEAVE:
		case MC_MATCH_CHATROOM_SELECT_WRITE:
		case MC_MATCH_CHATROOM_INVITE:
		case MC_MATCH_CHATROOM_CHAT:
		case MC_MATCH_CLAN_MSG:
		case MC_HSHIELD_PONG:
	
		case MC_RESPONSE_GAMEGUARD_AUTH:
			break;
		default:
			delete pCmd;
			CHECK_RETURN_CALLSTACK(ZPostCommand);
			return false;
		};
		CHECK_RETURN_CALLSTACK(ZPostCommand);
		return ZGetGameClient()->Post(pCmd);
	} 
	else
	{
		// 평상시 모든 커맨드 전송 허용
		CHECK_RETURN_CALLSTACK(ZPostCommand);
		bool bRet = ZGetGameClient()->Post(pCmd); 

		// 미국핵 대응 메인스레드에서 보내져야 하는 커맨드들의 스레드 검사
		// Post()이전에 검사하면 Post()로 바로 점프할 수 있으므로 뒤에다 두어야 한다
		// (그러나 ZGameClient::Post()를 바로 호출해버리면 아래 방어코드가 소용없게 된다..그땐 따로 대응해야 한다.)
		int cmdId = pCmd->GetID();
		if (cmdId == MC_ADMIN_ANNOUNCE ||
			cmdId == MC_ADMIN_REQUEST_SERVER_INFO ||
			cmdId == MC_ADMIN_SERVER_HALT ||
			cmdId == MC_ADMIN_REQUEST_UPDATE_ACCOUNT_UGRADE ||
			cmdId == MC_ADMIN_REQUEST_KICK_PLAYER ||
			cmdId == MC_ADMIN_REQUEST_MUTE_PLAYER ||
			cmdId == MC_ADMIN_REQUEST_BLOCK_PLAYER ||
			cmdId == MC_ADMIN_PING_TO_ALL ||
			cmdId == MC_ADMIN_REQUEST_SWITCH_LADDER_GAME ||
			cmdId == MC_ADMIN_HIDE ||
			cmdId == MC_ADMIN_RESET_ALL_HACKING_BLOCK ||
			cmdId == MC_ADMIN_RELOAD_GAMBLEITEM ||
			cmdId == MC_ADMIN_DUMP_GAMBLEITEM_LOG ||
			cmdId == MC_ADMIN_ASSASIN ||

			cmdId == MC_MATCH_GAME_KILL ||
			cmdId == MC_MATCH_GAME_REQUEST_SPAWN ||

			cmdId == MC_MATCH_REQUEST_SUICIDE ||
			cmdId == MC_MATCH_REQUEST_OBTAIN_WORLDITEM ||
			cmdId == MC_MATCH_REQUEST_SPAWN_WORLDITEM ||
			cmdId == MC_MATCH_SET_OBSERVER ||

			cmdId == MC_MATCH_REQUEST_CREATE_CHAR ||
			cmdId == MC_MATCH_REQUEST_DELETE_CHAR ||

			cmdId == MC_MATCH_REQUEST_BUY_ITEM ||
			cmdId == MC_MATCH_REQUEST_SELL_ITEM ||
			cmdId == MC_MATCH_REQUEST_EQUIP_ITEM ||
			cmdId == MC_MATCH_REQUEST_TAKEOFF_ITEM ||

			cmdId == MC_MATCH_REQUEST_GAMBLE ||

			cmdId == MC_QUEST_REQUEST_NPC_DEAD ||
			cmdId == MC_MATCH_QUEST_REQUEST_DEAD ||

			cmdId == MC_QUEST_PEER_NPC_BASICINFO ||
			cmdId == MC_QUEST_PEER_NPC_HPINFO ||
			cmdId == MC_QUEST_PEER_NPC_DEAD ||
			cmdId == MC_QUEST_PEER_NPC_BOSS_HPAP ||
			cmdId == MC_QUEST_REQUEST_MOVETO_PORTAL ||
			cmdId == MC_QUEST_TEST_REQUEST_NPC_SPAWN ||
			cmdId == MC_QUEST_TEST_REQUEST_CLEAR_NPC ||
			cmdId == MC_QUEST_TEST_REQUEST_SECTOR_CLEAR ||
			cmdId == MC_QUEST_TEST_REQUEST_FINISH ||

			cmdId == MC_PEER_MOVE ||
			cmdId == MC_PEER_ATTACK ||
			cmdId == MC_PEER_DAMAGE ||
			cmdId == MC_PEER_SHOT ||
			cmdId == MC_PEER_SHOT_SP ||
			cmdId == MC_PEER_SKILL ||
			cmdId == MC_PEER_SHOT_MELEE ||
			cmdId == MC_PEER_DIE ||
			cmdId == MC_PEER_SPAWN ||
			cmdId == MC_PEER_DASH ||
			cmdId == MC_PEER_CHAT)
		{
			extern DWORD g_dwMainThreadID;
			if (g_dwMainThreadID != GetCurrentThreadId())
			{
#ifdef _DEBUG
				mlog("CMD THREAD MISMATCH : cmdId(%d), mainId(%d), currId(%d)\n", cmdId, g_dwMainThreadID, GetCurrentThreadId());
#endif
				_ASSERT(0);
				MCommand* pC=ZNewCmd(MC_REQUEST_GIVE_ONESELF_UP);
				ZPostCommand(pC);
			}

			return bRet;
		}
	}
	return true;
}

ZGameClient::ZGameClient() : MMatchClient() , m_pUPnP(NULL)
{
	m_pUPnP = new UPnP;

	m_uidPlayer = MUID(0,0);
	m_nClockDistance = 0;
	m_fnOnCommandCallback = NULL;
	m_nPrevClockRequestAttribute = 0;
	m_nBridgePeerCount = 0;
	m_tmLastBridgePeer = 0;	
	m_bForcedEntry = false;

	m_szChannel[0] = NULL;
	m_szStageName[0] = NULL;
	m_szChatRoomInvited[0] = NULL;
	SetChannelRuleName("");

	m_nRoomNo = 0;
	m_nStageCursor = 0;

	m_nCountdown = 0;
	m_tmLastCountdown = 0;
	m_nRequestID = 0;
	m_uidRequestPlayer = MUID(0,0);
	m_nProposalMode = MPROPOSAL_NONE;
	m_bLadderGame = false;

	m_CurrentChannelType = MCHANNEL_TYPE_PRESET;

	SetRejectWhisper(true);
	SetRejectInvite(true);

	SetVoteInProgress(false);
	SetCanVote(false);


	m_EmblemMgr.Create();
	m_EmblemMgr.PrepareCache();

	memset(&m_dtCharInfo, 0, sizeof(m_dtCharInfo));
	memset(&m_dtCharInfoPrev, 0, sizeof(m_dtCharInfoPrev));

	// HShield Init
// #ifdef _HSHIELD
//	MPacketHShieldCrypter::Init();
//#endif

#ifdef _LOCATOR // -by 추교성. Locator에 접속해서 커맨드를 받으려면 m_This의 UID가 (0,0)이 아니어야 함.
	m_This = MUID(0, 1);
#endif

	m_UPDCommadHackShield.Init();
}


ZGameClient::~ZGameClient()
{
	DestroyUPnP();
	m_EmblemMgr.Destroy();

	ZGetMyInfo()->Clear();

#ifdef LOCALE_NHNUSA
	GetNHNUSAReport().ReportCloseGame();
#endif
}

void ZGameClient::PriorityBoost(bool bBoost)
{
#ifdef _GAMEGUARD
	return;
#endif

	if (bBoost) {
		SetPriorityClass(GetCurrentProcess(),ABOVE_NORMAL_PRIORITY_CLASS);
		m_bPriorityBoost = true;
		OutputDebugString("<<<<  BOOST ON  >>>> \n");
	} else {
		SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS);
		m_bPriorityBoost = false;
		OutputDebugString("<<<<  BOOST OFF  >>>> \n");
	}
}


void ZGameClient::OnRegisterCommand(MCommandManager* pCommandManager)
{
	MMatchClient::OnRegisterCommand(pCommandManager);
	ZAddCommandTable(pCommandManager);
}

void ZGameClient::OnPrepareCommand(MCommand* pCommand)
{
#ifndef _PUBLISH
	m_pLogFrame->AddCommand(GetGlobalClockCount(), pCommand);
#endif

}

int ZGameClient::OnResponseMatchLogin(const MUID& uidServer, int nResult, const char* szServerName, const MMatchServerMode nServerMode,
									  const char* szAccountID, const MMatchUserGradeID nUGradeID, const MMatchPremiumGradeID nPGradeID, int nECoins,
									  const MUID& uidPlayer, bool bEnabledSurvivalMode, bool bEnabledDuelTournament, unsigned char* pbyGuidReqMsg)
{
	int nRet = MMatchClient::OnResponseMatchLogin(uidServer, nResult, szServerName, nServerMode,
												  szAccountID, nUGradeID, nPGradeID, nECoins, uidPlayer, bEnabledSurvivalMode, bEnabledDuelTournament, pbyGuidReqMsg);

	ZGetMyInfo()->InitAccountInfo(szAccountID, nUGradeID, nPGradeID, nECoins);

	if ((nResult == 0) && (nRet == MOK)) {	// Login successful
		mlog("Login Successful. \n");

#ifdef _HSHIELD
		int dwRet = _AhnHS_MakeGuidAckMsg(pbyGuidReqMsg,        // [in]
										  ZGetMyInfo()->GetSystemInfo()->pbyGuidAckMsg // [out]
										 );
		if( dwRet != ERROR_SUCCESS )
			mlog("Making Guid Ack Msg Failed. (Error code = %x)\n", dwRet);
#endif

		// 여기서 AccountCharList를 요청한다.
		ZApplication::GetGameInterface()->ChangeToCharSelection();
	} else {								// Login failed
		mlog("Login Failed.(ErrCode=%d) \n", nResult);


#ifdef LOCALE_NHNUSA
		 if(nResult == 10003)
		{	// 만약 인원수가 꽉찾는데 계속 로그인 시도 한다면 10초정도 딜레이를 준다.
			ZApplication::GetGameInterface()->SetErrMaxPlayer(true);
			ZApplication::GetGameInterface()->SetErrMaxPlayerDelayTime(timeGetTime()+7000);
		}
		else 
		{
			ZPostDisconnect();
			if(nResult != MOK)
				ZApplication::GetGameInterface()->ShowErrorMessage( nResult );
		}
#else
		ZPostDisconnect();

		if (nResult != MOK)
		{
			ZApplication::GetGameInterface()->ShowErrorMessage( nResult );
		}
#endif
		return MOK;
	}

	ZApplication::GetGameInterface()->ShowWidget("NetmarbleLogin", false);

	StartBridgePeer();

	return MOK;
}


void ZGameClient::OnAnnounce(unsigned int nType, char* szMsg)
{
	ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();

	if (strncmp(szMsg, MTOK_ANNOUNCE_PARAMSTR, strlen(MTOK_ANNOUNCE_PARAMSTR)) == 0)
	{
		const char* szId = szMsg + strlen(MTOK_ANNOUNCE_PARAMSTR);
		int idErrMsg = 0;
		if (1 == sscanf(szId, "%d", &idErrMsg)) {
			char szTranslated[256];
			const char* szErrStr = ZErrStr(idErrMsg);
			const char* szArg = "";

			// 인자 파싱 : 급하니 일단 인자 0개 또는 1 개뿐이라고 가정하고 구현;
			const char* pSeperator = strchr(szMsg, '\a');
			if (pSeperator) {
				szArg = pSeperator + 1;
			}

			sprintf(szTranslated, szErrStr, szArg);
			ZChatOutput(szTranslated, ZChat::CMT_SYSTEM);
			return;
		}
	}
	
	ZChatOutput(szMsg, ZChat::CMT_SYSTEM);
}

void ZGameClient::OnBridgePeerACK(const MUID& uidChar, int nCode)
{
	SetBridgePeerFlag(true);
}

void ZGameClient::OnObjectCache(unsigned int nType, void* pBlob, int nCount)
{
	MMatchClient::OnObjectCache(nType, pBlob, nCount);

	ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
	ZPlayerListBox* pList = (ZPlayerListBox*)pResource->FindWidget("StagePlayerList_");

	vector< int > vecClanID;
	
	// 인터페이스 업데이트
	if(pList)
	{
		if (nType == MATCHCACHEMODE_UPDATE) {
			pList->RemoveAll();
			ZGetPlayerManager()->Clear();
			for(int i=0; i<nCount; i++){
				MMatchObjCache* pCache = (MMatchObjCache*)MGetBlobArrayElement(pBlob, i);
				if (pCache->CheckFlag(MTD_PlayerFlags_AdminHide) == false) {	//  Skip on AdminHide
					pList->AddPlayer(pCache->GetUID(),MOSS_NONREADY,pCache->GetLevel(),
									pCache->GetName(),pCache->GetClanName(),pCache->GetCLID(),false,MMT_ALL, pCache->GetDTGrade());
					
					// Emblem // 클랜 URL이 없으면 Vector에 쌓는다
					if (m_EmblemMgr.CheckEmblem(pCache->GetCLID(), pCache->GetEmblemChecksum())) {
						// Begin Draw
					} 
					else if (pCache->GetEmblemChecksum() != 0) {
						vecClanID.push_back( pCache->GetCLID() );
					}

					ZGetPlayerManager()->AddPlayer( pCache->GetUID(), pCache->GetName(), pCache->GetRank(), pCache->GetKillCount(), pCache->GetDeathCount());
				}
			}
		} else if (nType == MATCHCACHEMODE_ADD) {
			for(int i=0; i<nCount; i++){
				MMatchObjCache* pCache = (MMatchObjCache*)MGetBlobArrayElement(pBlob, i);
				if (pCache->CheckFlag(MTD_PlayerFlags_AdminHide) == false) {	//  Skip on AdminHide
					pList->AddPlayer(pCache->GetUID(),MOSS_NONREADY,pCache->GetLevel(),
									 pCache->GetName(),pCache->GetClanName(),pCache->GetCLID(),false,MMT_ALL, pCache->GetDTGrade());
					
					// Emblem // 클랜 URL이 없으면 Vector에 쌓는다
					if (m_EmblemMgr.CheckEmblem(pCache->GetCLID(), pCache->GetEmblemChecksum())) {
						// Begin Draw
					} 
					else if (pCache->GetEmblemChecksum() != 0) {
						vecClanID.push_back( pCache->GetCLID() );
					}

					ZGetPlayerManager()->AddPlayer( pCache->GetUID(), pCache->GetName(), pCache->GetRank(), pCache->GetKillCount(), pCache->GetDeathCount());
				}
			}
		} else if (nType == MATCHCACHEMODE_REMOVE) {
			for(int i=0; i<nCount; i++){
				MMatchObjCache* pCache = (MMatchObjCache*)MGetBlobArrayElement(pBlob, i);
				pList->DelPlayer(pCache->GetUID());

				ZGetPlayerManager()->RemovePlayer( pCache->GetUID());
			}

			// 추방 후에 청/홍팀의 사람 수를 다시 구한다.(동화니가 추가)
			ZApplication::GetGameInterface()->UpdateBlueRedTeam();
		}

		//// Emblem // 클랜 URL이 없는 vector를 서버에 보낸다.
		if(vecClanID.size() > 0)
		{
			void* pBlob = MMakeBlobArray(sizeof(int), (int)vecClanID.size()); /// nOneBlobSize만큼 nBlobCount갯수만큼 배열한 블럭 만들기
			int nCount = 0;
			for(vector<int>::iterator it = vecClanID.begin(); it != vecClanID.end(); it++, nCount++)
			{
				int *nClanID = (int*)MGetBlobArrayElement(pBlob, nCount);
				*nClanID = *it;
			}

			ZPostRequestEmblemURL(pBlob);
			MEraseBlobArray(pBlob);
			vecClanID.clear();
		}
	}

//	ZCharacterView* pCharView = (ZCharacterView*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Stage_Charviewer");
//	if( pCharView != NULL && !pCharView->GetDrawInfo())
//	{
//		pCharView->SetCharacter( ZGetMyUID());
//	}
}

void ZGameClient::OnChannelResponseJoin(const MUID& uidChannel, MCHANNEL_TYPE nChannelType, const char* szChannelName, bool bEnableInterface)
{
	ZApplication::GetGameInterface()->SetState(GUNZ_LOBBY);

	m_uidChannel = uidChannel;
	strcpy(m_szChannel, szChannelName);
	m_CurrentChannelType = nChannelType;
	m_bEnableInterface = bEnableInterface;

	char szText[256];

	ZGetGameInterface()->GetChat()->Clear(ZChat::CL_LOBBY);
//	wsprintf(szText, "당신은 채널 '%s'에 입장하셨습니다.", szChannelName);
	//wsprintf(szText, "당신은 채널 '%s'에 입장하셨습니다.", szChannelName);
	ZTransMsg( szText, MSG_LOBBY_JOIN_CHANNEL, 1, szChannelName );

	ZChatOutput(szText, ZChat::CMT_SYSTEM, ZChat::CL_LOBBY);

	switch (GetServerMode())
	{
	case MSM_MATCH:
		{
//			wsprintf(szText, "레벨제한을 원치 않으시면 자유채널을 이용해 주시기 바랍니다.");
			wsprintf( szText, 
				ZMsg(MSG_LOBBY_LIMIT_LEVEL) );
			ZChatOutput(szText, ZChat::CMT_SYSTEM, ZChat::CL_LOBBY);
		}
		break;
	case MSM_LADDER:
		{
//			wsprintf(szText, "리그게임은 채널에 상관없이 모든사용자들과 겨루게 됩니다.");
			wsprintf( szText, 
				ZMsg(MSG_LOBBY_LEAGUE) );
			ZChatOutput(szText, ZChat::CMT_SYSTEM, ZChat::CL_LOBBY);
		}
		break;
	case MSM_TEST:
	case MSM_CLAN:
		{
			if (nChannelType == MCHANNEL_TYPE_CLAN)
			{
/*
				{
					static bool bUsed = false;
					if (!bUsed)
					{
/*						wsprintf(szText, "[공지] 당분간 공유기를 사용하시는 유저분들은 클랜전을 원활히 즐기실 수 없습니다.");
						ZChatOutput(szText, ZChat::CMT_SYSTEM, ZChat::CL_LOBBY);
						wsprintf(szText, "[공지] 빠른 시간내에 복구하도록 하겠습니다. 불편을 끼쳐드려 죄송합니다.");
						ZChatOutput(szText, ZChat::CMT_SYSTEM, ZChat::CL_LOBBY);

						bUsed = true;
					}
				}
*/


				ZPostRequestClanInfo(GetPlayerUID(), szChannelName);
			}
		}
		break;
	}


	ZRoomListBox* pRoomList = 
		(ZRoomListBox*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Lobby_StageList");
	if (pRoomList) pRoomList->Clear();

	// 
	ZApplication::GetGameInterface()->SetRoomNoLight(1);

	ZGetGameInterface()->InitLobbyUIByChannelType();

#ifdef LOCALE_NHNUSA
	GetNHNUSAReport().ReportJoinChannel();
#endif

#ifdef LIMIT_ACTIONLEAGUE
	// 임시로 액션리그 
	bool bActionLeague = (strstr(szChannelName,"액션")!=NULL) || (nChannelType==MCHANNEL_TYPE_USER);

	ZGetGameInterface()->InitLadderUI(bActionLeague);
#endif
}

void ZGameClient::OnChannelChat(const MUID& uidChannel, char* szName, char* szChat,int nGrade)
{
	if (GetChannelUID() != uidChannel)		return;
	if ((szChat[0]==0) || (szName[0] == 0))	return;

//	MUID uid = GetObject(szName);
//	MMatchObjectCache* pObjCache = FindObjCache(uid);
	MCOLOR _color = MCOLOR(0,0,0);

	MMatchUserGradeID gid = (MMatchUserGradeID) nGrade;
//	gid = MMUG_DEVELOPER;

	char sp_name[256];

	bool bSpUser = GetUserGradeIDColor(gid,_color,sp_name);

	char szText[512];

	if(bSpUser)	// 특수유저
	{
		wsprintf(szText, "%s : %s", sp_name , szChat);
		ZChatOutput(szText, ZChat::CMT_NORMAL, ZChat::CL_LOBBY,_color);
	}
	else if ( !ZGetGameClient()->GetRejectNormalChat() ||				// 일반 유저
			  (strcmp( szName, ZGetMyInfo()->GetCharName()) == 0))
	{
		wsprintf(szText, "^4%s^9 : %s", szName, szChat);
		ZChatOutput(szText, ZChat::CMT_NORMAL, ZChat::CL_LOBBY);
	}
}

void ZGameClient::OnChannelList(void* pBlob, int nCount)
{
	ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
	MListBox* pWidget = (MListBox*)pResource->FindWidget("ChannelList");
	if (pWidget == NULL) {
		ZGetGameClient()->StopChannelList();
		return;
	}

	int nStartIndex = pWidget->GetStartItem();
	int nSelIndex = pWidget->GetSelIndex();
	const char* szChannelName = NULL;
	pWidget->RemoveAll();
	for(int i=0; i<nCount; i++){
		MCHANNELLISTNODE* pNode = (MCHANNELLISTNODE*)MGetBlobArrayElement(pBlob, i);

		// 공식채널의 경우 스트링리소스ID를 받아서 사용자가 선택한 언어로 번역된 스트링을 보여주자
		if (pNode->szChannelNameStrResId[0] != 0){
			szChannelName = ZGetStringResManager()->GetStringFromXml(pNode->szChannelNameStrResId);
		} else {
			szChannelName = pNode->szChannelName;
		}

		pWidget->Add(
			new ZChannelListItem(pNode->uidChannel, (int)pNode->nNo, szChannelName,
								 pNode->nChannelType, (int)pNode->nPlayers, (int)pNode->nMaxPlayers)
		);
	}
	pWidget->SetStartItem(nStartIndex);
	pWidget->SetSelIndex(nSelIndex);
}

void ZGameClient::OnChannelResponseRule(const MUID& uidchannel, const char* pszRuleName)
{
	MChannelRule* pRule = ZGetChannelRuleMgr()->GetRule(pszRuleName);
	if (pRule == NULL)
		return;

	SetChannelRuleName(pszRuleName);

	// 임시 처리?
	MComboBox* pCombo = (MComboBox*)ZGetGameInterface()->GetIDLResource()->FindWidget("MapSelection");
	if(pCombo != NULL)
	{
		InitMaps(pCombo); 
		MListBox* pList = (MListBox*)ZGetGameInterface()->GetIDLResource()->FindWidget("MapList");
		pList->RemoveAll();
		if( pList != NULL )
		{
			for( int i = 0 ; i < pCombo->GetCount(); ++i )
			{
				pList->Add(pCombo->GetString(i));
			}
		}
	}


	bool bEnable = GetEnableInterface();

	MWidget* pWidget = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "StageJoin");
	if ( pWidget)		pWidget->Enable( bEnable);

	pWidget = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "StageCreateFrameCaller");
	if ( pWidget)		pWidget->Enable( bEnable);
	
	pWidget = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "QuickJoin");
	if ( pWidget)		pWidget->Enable( bEnable);
	
	pWidget = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "QuickJoin2");
	if ( pWidget)		pWidget->Enable( bEnable);
	
	pWidget = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "ArrangedTeamGame");
	if ( pWidget)		pWidget->Enable( bEnable);

	pWidget = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "ChannelChattingInput");
	if ( pWidget)		pWidget->Enable( bEnable);

	pWidget = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "Lobby_StageList");
	if ( pWidget)		pWidget->Enable( bEnable);
}

void ZGameClient::OnStageEnterBattle(const MUID& uidChar, MCmdEnterBattleParam nParam)
{    
        if(strstr(ZGetGameClient()->GetStageName(),"[NC]") || strstr(ZGetGameClient()->GetStageName(),"[nc]"))
        {
            char szText[ 100];
            MTD_CharInfo emptyInfo;
            const MTD_CharInfo* pCharInfo[1] = {&emptyInfo};
            ZCharacter* pChar1 = ( ZCharacter*)ZGetCharacterManager()->Find(ZGetMyUID());
            pCharInfo[0] = pChar1->GetCharInfo();


            for (int i = 0; i < MMCIP_END; i++)
            {
                MMatchItemDesc* pItemDesc = MGetMatchItemDescMgr()->GetItemDesc(pCharInfo[0]->nEquipedItemDesc[i]);
                if (pItemDesc)
                {
                    if (pItemDesc->IsCashItem())
                    {
                        sprintf(szText,"Remove your Cash items (Donates and Event items).");
                        ZApplication::GetGameInterface()->ShowMessage( szText);
                        ZApplication::GetGameInterface()->ReserveLeaveBattle();
                            //return MSG_CANNOT_DELETE_CHAR_FOR_CASHITEM;
                    }


                }
            }
        } 
    // 이것은 ZGame 에서 불러준다
    if (uidChar == GetPlayerUID())        // enter한사람이 나자신일 경우
    {
        ZPostRequestGameInfo(ZGetGameClient()->GetPlayerUID(), ZGetGameClient()->GetStageUID());


        // 게임이 시작되면 모든 사람들의 ready를 푼다.
        MStageCharSettingList::iterator itor = m_MatchStageSetting.m_CharSettingList.begin();
        for (; itor != m_MatchStageSetting.m_CharSettingList.end(); ++itor) 
        {
            MSTAGE_CHAR_SETTING_NODE* pCharNode = (*itor);
            pCharNode->nState = MOSS_NONREADY;
        }
    }


    StartUDPTest(uidChar);    
        
}

void ZGameClient::OnStageJoin(const MUID& uidChar, const MUID& uidStage, unsigned int nRoomNo, char* szStageName)
{
//	SetBridgePeerFlag(false);

	if (uidChar == GetPlayerUID()) {
		m_nStageCursor = 0;
		m_uidStage = uidStage;
		m_nRoomNo = nRoomNo;
	
		memset(m_szStageName, 0, sizeof(m_szStageName));
		strcpy(m_szStageName, szStageName);	// Save StageName

		unsigned int nStageNameChecksum = m_szStageName[0] + m_szStageName[1] + m_szStageName[2] + m_szStageName[3];
		InitPeerCrypt(uidStage, nStageNameChecksum);
		CastStageBridgePeer(uidChar, uidStage);
	}

	MCommand* pCmd = new MCommand(m_CommandManager.GetCommandDescByID(MC_MATCH_REQUEST_STAGESETTING), GetServerUID(), m_This);
	pCmd->AddParameter(new MCommandParameterUID(GetStageUID()));
	Post(pCmd);

	if (uidChar == GetPlayerUID())
	{
		ZChangeGameState(GUNZ_STAGE);
	}

	string name = GetObjName(uidChar);
	char szText[256];
	if (uidChar == GetPlayerUID())
	{
		ZGetGameInterface()->GetChat()->Clear(ZChat::CL_STAGE);

		char szTmp[ 256];
		sprintf(szTmp, "(%03d)%s", nRoomNo, szStageName);

		ZTransMsg( szText, MSG_JOINED_STAGE, 1, szTmp);
		ZChatOutput(szText, ZChat::CMT_SYSTEM, ZChat::CL_STAGE);
	}
	else if (GetStageUID() == uidStage)
	{
		char sp_name[256];
		MCOLOR _color;
		MMatchUserGradeID gid = MMUG_FREE;

		char name[ 32];
		char kill[ 32];
		char death[ 32];
		char winning[ 32];

		ZPlayerInfo* pInfo = ZGetPlayerManager()->Find( (MUID)uidChar);
		if ( pInfo != NULL)
		{
			sprintf( kill, "%d %s", pInfo->GetKill(), ZMsg( MSG_CHARINFO_KILL));
			sprintf( death, "%d %s", pInfo->GetDeath(), ZMsg( MSG_CHARINFO_DEATH));
			sprintf( winning, "%.1f%%", pInfo->GetWinningRatio());
		}
		else
		{
			sprintf( kill, "? %s", ZMsg( MSG_CHARINFO_KILL));
			sprintf( death, "? %s", pInfo->GetDeath(), ZMsg( MSG_CHARINFO_DEATH));
			sprintf( winning, "0.0%%");
		}

		if(GetUserInfoUID(uidChar,_color,sp_name,gid))
		{
			MMatchObjCache* pObjCache = ZGetGameClient()->FindObjCache(uidChar);
			if (pObjCache && pObjCache->CheckFlag(MTD_PlayerFlags_AdminHide))
				return;	// Skip on AdminHide

			strcpy( name, sp_name);
			ZTransMsg( szText, MSG_JOINED_STAGE2, 4, name, kill, death, winning);
			ZChatOutput(szText, ZChat::CMT_SYSTEM, ZChat::CL_STAGE);
		}
		else
		{
			strcpy( name, pInfo->GetName());
			ZTransMsg( szText, MSG_JOINED_STAGE2, 4, name, kill, death, winning);
			ZChatOutput(szText, ZChat::CMT_SYSTEM, ZChat::CL_STAGE);
		}
	}
}

void ZGameClient::OnStageLeave(const MUID& uidChar, const MUID& uidStage)
{
	if (uidChar == GetPlayerUID()) {
		m_uidStage = MUID(0,0);
		m_nRoomNo = 0;
	}


	if (uidChar == GetPlayerUID())
	{
		ZChangeGameState(GUNZ_LOBBY);		
	}

	for (MStageCharSettingList::iterator i=m_MatchStageSetting.m_CharSettingList.begin();i!=m_MatchStageSetting.m_CharSettingList.end();i++) {
		if (uidChar == (*i)->uidChar)
		{
			delete (*i);
			m_MatchStageSetting.m_CharSettingList.erase( i );
			break;
		}
	}

	ZGetGameClient()->SetVoteInProgress( false );
	ZGetGameClient()->SetCanVote( false );

	AgentDisconnect();
}

void ZGameClient::OnStageStart(const MUID& uidChar, const MUID& uidStage, int nCountdown)
{
	// 게임 시작시 게임 세팅관련 위젯 비활성화 해줌
	ZApplication::GetStageInterface()->SetEnableWidgetByRelayMap(false);
	SetCountdown(nCountdown);
}

void ZGameClient::OnStageRelayStart()
{
	SetCountdown(3);
}

void ZGameClient::OnStageLaunch(const MUID& uidStage, const char* pszMapName)
{
	m_bLadderGame = false;

	SetAllowTunneling(true);

	m_MatchStageSetting.SetMapName(const_cast<char*>(pszMapName));
	
	if (ZApplication::GetGameInterface()->GetState() != GUNZ_GAME) {
		ZChangeGameState(GUNZ_GAME);		// thread safely
	}
}

void ZGameClient::OnStageFinishGame(const MUID& uidStage, const bool bIsRelayMapUnFinish)
{
	if (ZApplication::GetGameInterface()->GetState() == GUNZ_GAME)
	{
		ZApplication::GetGameInterface()->FinishGame();
//		ZChangeGameState(GUNZ_STAGE);		// thread safely
	} else if( ZApplication::GetGameInterface()->GetState() == GUNZ_STAGE) {

	}
	// 릴레이맵 도중, 나와있을 때 게임 세팅관련 위젯 세팅(게임시작버튼 포함)
	bool bEndRelayMap = !bIsRelayMapUnFinish;
	ZApplication::GetStageInterface()->SetEnableWidgetByRelayMap(bEndRelayMap);

	ZPostRequestStageSetting(ZGetGameClient()->GetStageUID());	
}

void ZGameClient::OnStageMap(const MUID& uidStage, char* szMapName, bool bIsRelayMap)
{
	if (uidStage != GetStageUID()) return;

	m_MatchStageSetting.SetMapName(szMapName);
	m_MatchStageSetting.SetIsRelayMap(strcmp(MMATCH_MAPNAME_RELAYMAP, szMapName) == 0);

	ZApplication::GetGameInterface()->SerializeStageInterface();
}

void ZGameClient::OnStageTeam(const MUID& uidChar, const MUID& uidStage, unsigned int nTeam)
{
	MMatchObjectStageState nStageState = MOSS_NONREADY;
	MSTAGE_CHAR_SETTING_NODE* pCharNode = m_MatchStageSetting.FindCharSetting(uidChar);
	if (pCharNode) 
	{
		nStageState = pCharNode->nState;
	}

	m_MatchStageSetting.UpdateCharSetting(uidChar, nTeam, nStageState);
	ZApplication::GetGameInterface()->SerializeStageInterface();
}

void ZGameClient::OnStagePlayerState(const MUID& uidChar, const MUID& uidStage, MMatchObjectStageState nStageState)
{
	int nTeam = MMT_SPECTATOR;
	MSTAGE_CHAR_SETTING_NODE* pCharNode = m_MatchStageSetting.FindCharSetting(uidChar);
	if (pCharNode != NULL)
	{
		nTeam = pCharNode->nTeam;
	}

	m_MatchStageSetting.UpdateCharSetting(uidChar, nTeam, nStageState);

	// 나 자신이 스테이지에 존재하면 스테이지 인터페이스를 갱신한다. (다른곳에선 호출하지 않는다.)
	GunzState GunzState = ZApplication::GetGameInterface()->GetState();
	if (GunzState == GUNZ_STAGE)
	{
		ZApplication::GetStageInterface()->OnStageCharListSettup();
	} 
}

void ZGameClient::OnStageMaster(const MUID& uidStage, const MUID& uidChar)
{
	int nTeam = MMT_SPECTATOR;
	MMatchObjectStageState nStageState = MOSS_NONREADY;
	MSTAGE_CHAR_SETTING_NODE* pCharNode = m_MatchStageSetting.FindCharSetting(uidChar);
	if (pCharNode) 
	{
		nTeam = pCharNode->nTeam;
		nStageState = pCharNode->nState;
	}

	m_MatchStageSetting.SetMasterUID(uidChar);
	m_MatchStageSetting.UpdateCharSetting(uidChar, nTeam, nStageState);

	ZApplication::GetGameInterface()->SerializeStageInterface();

//	ZChatOutput("방장은 '/kick 이름' 또는 ALT + 해당캐릭터 '오른쪽 클릭'으로 강제퇴장을 시킬수 있습니다.", ZChat::CMT_NORMAL, ZChat::CL_STAGE);
}

void ZGameClient::OnStageChat(const MUID& uidChar, const MUID& uidStage, char* szChat)
{
	if (GetStageUID() != uidStage) return;
	if(szChat[0]==0) return;

/*
	ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
	MListBox* pWidget = (MListBox*)pResource->FindWidget("StageChattingOutput");
*/
		
	string name = GetObjName(uidChar);

	MCOLOR _color = MCOLOR(0,0,0);

	MMatchUserGradeID gid = MMUG_FREE;

	MMatchObjCache* pObjCache = FindObjCache(uidChar);

	if(pObjCache) {
		gid = pObjCache->GetUGrade();
	}

//	gid = MMUG_DEVELOPER;

	char sp_name[256];

	bool bSpUser = GetUserGradeIDColor(gid,_color,sp_name);

	char szText[512];

	if(bSpUser)	// 특수유저
	{
		wsprintf(szText, "%s : %s", sp_name , szChat);
		ZChatOutput(szText, ZChat::CMT_NORMAL, ZChat::CL_STAGE,_color);
	}
	else if ( !ZGetGameClient()->GetRejectNormalChat() ||				// 일반 유저
		(strcmp( pObjCache->GetName(), ZGetMyInfo()->GetCharName()) == 0))
	{
		wsprintf(szText, "^4%s^9 : %s", name.c_str(), szChat);
		ZChatOutput(szText, ZChat::CMT_NORMAL, ZChat::CL_STAGE);
	}
}

void ZGameClient::OnStageList(int nPrevStageCount, int nNextStageCount, void* pBlob, int nCount)
{
#ifdef _DEBUG
	char szTemp[256];
	sprintf(szTemp, "OnStageList (nPrevStageCount = %d , nNextStageCount = %d , nCount = %d\n",
		nPrevStageCount, nNextStageCount, nCount);
	OutputDebugString(szTemp);
#endif
	ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
	ZRoomListBox* pRoomListBox = (ZRoomListBox*)pResource->FindWidget("Lobby_StageList");
	if (pRoomListBox == NULL) 
	{
		ZGetGameClient()->StopStageList();
		return;
	}

	pRoomListBox->Clear();
	for(int i=0; i<nCount; i++) {

		MTD_StageListNode* pNode = (MTD_StageListNode*)MGetBlobArrayElement(pBlob, i);

		// log debug
		if( pNode ) 
		{
			bool bForcedEntry = false, bPrivate = false, bLimitLevel = false;
			int nLimitLevel = 0;
			if (pNode->nSettingFlag & MSTAGENODE_FLAG_FORCEDENTRY_ENABLED) bForcedEntry = true;
			if (pNode->nSettingFlag & MSTAGENODE_FLAG_PRIVATE) bPrivate = true;
			if (pNode->nSettingFlag & MSTAGENODE_FLAG_LIMITLEVEL) bLimitLevel = true;
			
			char szMapName[256] = "";
			for (int tt = 0; tt < MMATCH_MAP_COUNT; tt++)
			{
				if (MGetMapDescMgr()->GetMapID(tt) == pNode->nMapIndex)
				{
					strcpy(szMapName, MGetMapDescMgr()->GetMapName(tt) );
					break;
				}
			}

			ZRoomListBox::_RoomInfoArg roominfo;
			roominfo.nIndex = i;
			roominfo.nRoomNumber = (int)pNode->nNo;
			roominfo.uidStage = pNode->uidStage;
			roominfo.szRoomName = pNode->szStageName;
			roominfo.szMapName = szMapName;
			roominfo.nMaxPlayers = pNode->nMaxPlayers;
			roominfo.nCurrPlayers = pNode->nPlayers;
			roominfo.bPrivate = bPrivate;
			roominfo.bForcedEntry = bForcedEntry;
			roominfo.bLimitLevel = bLimitLevel;
			roominfo.nMasterLevel = pNode->nMasterLevel;
			roominfo.nLimitLevel = pNode->nLimitLevel;
			roominfo.nGameType = pNode->nGameType;
			roominfo.nStageState = pNode->nState;
			pRoomListBox->SetRoom(&roominfo);
		}
	}
	pRoomListBox->SetScroll(nPrevStageCount, nNextStageCount);

	MWidget* pBtn = pResource->FindWidget("StageBeforeBtn");
	if (nPrevStageCount != -1)
	{
		if (nPrevStageCount == 0)
		{
			if (pBtn) pBtn->Enable(false);
		}
		else
		{
			if (pBtn) pBtn->Enable(true);
		}
	}

	pBtn = pResource->FindWidget("StageAfterBtn");
	if (nNextStageCount != -1)
	{
		if (nNextStageCount == 0)
		{
			if (pBtn) pBtn->Enable(false);
		}
		else
		{
			if (pBtn) pBtn->Enable(true);
		}
	}

}

ZPlayerListBox* GetProperFriendListOutput()
{
	ZIDLResource* pIDLResource = ZApplication::GetGameInterface()->GetIDLResource();

	GunzState nState = ZApplication::GetGameInterface()->GetState();
	switch(nState) {
	case GUNZ_LOBBY:
		{
			ZPlayerListBox* pList = (ZPlayerListBox*)pIDLResource->FindWidget("LobbyChannelPlayerList");
			if (pList && pList->GetMode() == ZPlayerListBox::PLAYERLISTMODE_CHANNEL_FRIEND)
				return pList;
			else
				return NULL;
		}
		break;
	case GUNZ_STAGE:	
		{
			ZPlayerListBox* pList = (ZPlayerListBox*)pIDLResource->FindWidget("StagePlayerList_");
			if (pList && pList->GetMode() == ZPlayerListBox::PLAYERLISTMODE_STAGE_FRIEND)
				return pList;
			else
				return NULL;
		}
		break;
	};
	return NULL;
}

void ZGameClient::OnResponseFriendList(void* pBlob, int nCount)
{
	ZPlayerListBox* pList = GetProperFriendListOutput();
	if (pList)
		pList->RemoveAll();

	char szBuf[128];
	for(int i=0; i<nCount; i++){
		MFRIENDLISTNODE* pNode = (MFRIENDLISTNODE*)MGetBlobArrayElement(pBlob, i);

		ePlayerState state;
		switch (pNode->nState)
		{
		case MMP_LOBBY: state = PS_LOBBY; break;
		case MMP_STAGE: state = PS_WAIT; break;
		case MMP_BATTLE: state = PS_FIGHT; break;
		default: state = PS_LOGOUT;
		};
		
		if (pList) {
			pList->AddPlayer(state, pNode->szName, pNode->szDescription);
//			pList->AttachToolTip(new MToolTip("ToolTipTest", pList));	// 툴팁을 붙이면 BMButton이 맛감
		} else {
			if (ZApplication::GetGameInterface()->GetState() != GUNZ_LOBBY )
			{
				sprintf(szBuf, "    %s (%s)", pNode->szName, pNode->szDescription);
				ZChatOutput(szBuf,  ZChat::CMT_NORMAL, ZChat::CL_CURRENT);
			}
		}
	}
}

void ZGameClient::OnChannelPlayerList(int nTotalPlayerCount, int nPage, void* pBlob, int nCount)
{
	ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
	ZPlayerListBox* pPlayerListBox = (ZPlayerListBox*)pResource->FindWidget("LobbyChannelPlayerList");

	if (!pPlayerListBox) return;
	if(pPlayerListBox->GetMode()!=ZPlayerListBox::PLAYERLISTMODE_CHANNEL) return;

	MUID selUID = pPlayerListBox->GetSelectedPlayerUID();

	int nStartIndex = pPlayerListBox->GetStartItem();

	if(nCount) {
		pPlayerListBox->RemoveAll();
	} else {//아무내용도 없다면~
		return;
	}

	pPlayerListBox->m_nTotalPlayerCount = nTotalPlayerCount;
	pPlayerListBox->m_nPage	= nPage;

	ZLobbyPlayerListItem* pItem = NULL;

	vector< int > vecClanID;

	for(int i=0; i<nCount; i++) 
	{
		MTD_ChannelPlayerListNode* pNode = (MTD_ChannelPlayerListNode*)MGetBlobArrayElement(pBlob, i);
		if( pNode ) 
		{
			ePlayerState state;
			switch (pNode->nPlace)
			{
			case MMP_LOBBY: state = PS_LOBBY; break;
			case MMP_STAGE: state = PS_WAIT; break;
			case MMP_BATTLE: state = PS_FIGHT; break;
			default: state = PS_LOBBY;
			};

			if ((pNode->nPlayerFlags & MTD_PlayerFlags_AdminHide) == true) {
				//  Skip on AdminHide
			} else {

				// 채널창에서 플레이어 리스트에 클랜마크가 안보인다..... 20090216...by kammir
				// 이곳에서 클랜마크가 내 컴퓨터에 저장되어 있는지 확인후에 없으면 서버에 요청한다.
				if (m_EmblemMgr.CheckEmblem(pNode->nCLID, pNode->nEmblemChecksum)) {		// 클랜 URL이 없으면 Vector에 쌓는다
					// Begin Draw
				} 
				else if (pNode->nEmblemChecksum != 0) {
					vecClanID.push_back( pNode->nCLID );
				}

				pPlayerListBox->AddPlayer(pNode->uidPlayer, state, pNode->nLevel, pNode->szName, pNode->szClanName, pNode->nCLID, 
					(MMatchUserGradeID)pNode->nGrade, pNode->nDTLastWeekGrade);
			}
		}
	}

	//// Emblem // 클랜 URL이 없는 vector를 서버에 보낸다.
	if(vecClanID.size() > 0)
	{
		void* pBlob = MMakeBlobArray(sizeof(int), (int)vecClanID.size()); /// nOneBlobSize만큼 nBlobCount갯수만큼 배열한 블럭 만들기
		int nCount = 0;
		for(vector<int>::iterator it = vecClanID.begin(); it != vecClanID.end(); it++, nCount++)
		{
			int *nClanID = (int*)MGetBlobArrayElement(pBlob, nCount);
			*nClanID = *it;
		}

		ZPostRequestEmblemURL(pBlob);
		MEraseBlobArray(pBlob);
		vecClanID.clear();
	}

	pPlayerListBox->SetStartItem(nStartIndex);
	pPlayerListBox->SelectPlayer(selUID);

	pPlayerListBox->AddTestItems();
}

void ZGameClient::OnChannelAllPlayerList(const MUID& uidChannel, void* pBlob, int nBlobCount)
{
	ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();

	MListBox* pListBox = NULL;

	// 클랜생성창인지 팀게임 선택 창인지 찾아본다.

	MWidget *pDialog = pResource->FindWidget("ClanCreateDialog");
	if(pDialog && pDialog->IsVisible())
		pListBox = (MListBox*)pResource->FindWidget("ClanSponsorSelect");

	pDialog = pResource->FindWidget("ArrangedTeamGameDialog");
	if(pDialog && pDialog->IsVisible())
		pListBox = (MListBox*)pResource->FindWidget("ArrangedTeamSelect");

	if(pListBox && pListBox->IsVisible())  {
		pListBox->RemoveAll();
		for(int i=0;i<nBlobCount;i++)
		{
			MTD_ChannelPlayerListNode* pNode = (MTD_ChannelPlayerListNode*)MGetBlobArrayElement(pBlob, i);
			if( pNode ) 
			{
				if (pNode->uidPlayer != GetPlayerUID())
					pListBox->Add(pNode->szName);
			}
		}
	}
}

void ZGameClient::UpdateStageSetting(MSTAGE_SETTING_NODE* pSetting, STAGE_STATE nStageState, const MUID& uidMaster)
{
	//m_MatchStageSetting.ShiftHeapPos();
	m_MatchStageSetting.UpdateStageSetting(pSetting);
	m_MatchStageSetting.SetMasterUID(uidMaster);
	m_MatchStageSetting.SetStageState(nStageState);
	
	bool bForceEntry = false;
	if (nStageState != STAGE_STATE_STANDBY)
	{
		bForceEntry = true;
	}
	m_bForcedEntry = bForceEntry;

	ZApplication::GetGameInterface()->SerializeStageInterface();
}

void ZGameClient::OnStageRelayMapListUpdate(int nRelayMapType, int nRelayMapRepeatCount, void* pStageRelayMapListBlob)
{
	MComboBox* pCBRelayMapType = (MComboBox*)ZGetGameInterface()->GetIDLResource()->FindWidget( "Stage_RelayMapType" );
	if(pCBRelayMapType)
		pCBRelayMapType->SetSelIndex(nRelayMapType);
	MComboBox* pCBRelayMapRepeatCount = (MComboBox*)ZGetGameInterface()->GetIDLResource()->FindWidget( "Stage_RelayMapRepeatCount" );
	if(pCBRelayMapRepeatCount)
		pCBRelayMapRepeatCount->SetSelIndex(nRelayMapRepeatCount);

	MListBox* pRelaMapListBox = (MListBox*)ZGetGameInterface()->GetIDLResource()->FindWidget("Stage_RelayMapListbox");
	if(pRelaMapListBox == NULL) return;

	RelayMap relayMapList[MAX_RELAYMAP_LIST_COUNT];
	for (int i = 0; i < MAX_RELAYMAP_LIST_COUNT; i++)
		relayMapList[i].nMapID = -1;
	// 기존 릴레이맵 리스트를 모두 지워준다.
	pRelaMapListBox->RemoveAll();
	int nRelayMapListCount = MGetBlobArrayCount(pStageRelayMapListBlob);
	for( int i = 0 ; i < nRelayMapListCount; ++i )
	{// 릴레이맵 리스트에 데이터를 추가해준다.
		MTD_RelayMap* pNode = (MTD_RelayMap*)MGetBlobArrayElement(pStageRelayMapListBlob, i);
		RelayMapList* pRelayMapList = new RelayMapList( MGetMapDescMgr()->GetMapName(MGetMapDescMgr()->GetMapID(pNode->nMapID)), MBitmapManager::Get( "Mark_X.bmp"));
		pRelaMapListBox->Add( pRelayMapList);
		relayMapList[i].nMapID = MGetMapDescMgr()->GetMapID(pNode->nMapID);
	}

	ZGetGameClient()->GetMatchStageSetting()->SetRelayMapListCount(nRelayMapListCount);
	ZGetGameClient()->GetMatchStageSetting()->SetRelayMapList(relayMapList);

	// 화면 상단의 맵 이미지 설정하기
	ZApplication::GetStageInterface()->SetStageRelayMapImage();
}

void ZGameClient::OnStageRelayMapElementUpdate(int nRelayMapType, int nRelayMapRepeatCount)
{
	MComboBox* pCombo = (MComboBox*)ZGetGameInterface()->GetIDLResource()->FindWidget( "Stage_RelayMapType" );
	if ( pCombo)
		pCombo->SetSelIndex(nRelayMapType);
	pCombo = (MComboBox*)ZGetGameInterface()->GetIDLResource()->FindWidget( "Stage_RelayMapRepeatCount" );
	if ( pCombo)
		pCombo->SetSelIndex(nRelayMapRepeatCount);
}

void ZGameClient::OnResponseStageSetting(const MUID& uidStage, void* pStageBlob, int nStageCount, void* pCharBlob, 
										 int nCharCount, STAGE_STATE nStageState, const MUID& uidMaster)
{
	if (GetStageUID() != uidStage) return;
	if (nStageCount <= 0 || nCharCount<=0) return;

	MSTAGE_SETTING_NODE* pNode = (MSTAGE_SETTING_NODE*)MGetBlobArrayElement(pStageBlob, 0);
	UpdateStageSetting(pNode, nStageState, uidMaster);

	// Char Setting
	m_MatchStageSetting.ResetCharSetting();
	for(int i=0; i<nCharCount; i++){
		MSTAGE_CHAR_SETTING_NODE* pCharSetting = (MSTAGE_CHAR_SETTING_NODE*)MGetBlobArrayElement(pCharBlob, i);
		m_MatchStageSetting.UpdateCharSetting(pCharSetting->uidChar, pCharSetting->nTeam, pCharSetting->nState);
	}	

	ZApplication::GetGameInterface()->SerializeStageInterface();
}

void ZGameClient::OnAgentError(int nError)
{
	if (ZGetGame()) {
		const MCOLOR ChatColor = MCOLOR(0xffffffff);
		ZChatOutput(ChatColor, "Agent Error : Agent not available");
	}
}

void ZGameClient::OnMatchNotify(unsigned int nMsgID)
{
	string strMsg;
	NotifyMessage(nMsgID, &strMsg);

	if ( (nMsgID == MATCHNOTIFY_GAME_SPEEDHACK) ||
		 (nMsgID == MATCHNOTIFY_GAME_MEMORYHACK) ) 
	{
		ZGetGameInterface()->ShowMessage(strMsg.c_str());
	}

	ZChatOutput(MCOLOR(255,70,70),strMsg.data());


	/*
	GunzState nState = ZApplication::GetGameInterface()->GetState();
	ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
	
	switch(nState) {
	case GUNZ_LOBBY:
		{
			MListBox* pWidget = (MListBox*)pResource->FindWidget("ChannelChattingOutput");
			if (pWidget) pWidget->Add(strMsg.data(), MCOLOR(255,70,70));
		}
		break;
	case GUNZ_STAGE:
		{
			MListBox* pWidget = (MListBox*)pResource->FindWidget("StageChattingOutput");
			if (pWidget) pWidget->Add(strMsg.data(), MCOLOR(255,70,70));
		}
		break;
	case GUNZ_GAME:
		{
			ZApplication::GetGameInterface()->OutputChatMsg(strMsg.data());
		}
		break;
	};
	*/
}


void ZGameClient::OutputMessage(const char* szMessage, MZMOMType nType)
{
	OutputToConsole(szMessage);
	ZChatOutput(MCOLOR(0xFFFFC600), szMessage);
}

int ZGameClient::OnConnected(SOCKET sock, MUID* pTargetUID, MUID* pAllocUID, unsigned int nTimeStamp)
{
	mlog("Server Connected\n");

	int ret = MMatchClient::OnConnected(sock, pTargetUID, pAllocUID, nTimeStamp);

	if (sock == m_ClientSocket.GetSocket()) {
		if ( (ZApplication::GetInstance()->GetLaunchMode() == ZApplication::ZLAUNCH_MODE_NETMARBLE) ||
			 (ZApplication::GetInstance()->GetLaunchMode() == ZApplication::ZLAUNCH_MODE_GAMEON))
		{	

			ZGetLocale()->PostLoginViaHomepage(pAllocUID);

		} else {
			char szID[256];
			char szPassword[256];
			ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
			MWidget* pWidget = pResource->FindWidget("LoginID");
			if(pWidget==NULL) return true;
			strcpy(szID, pWidget->GetText());
			pWidget = pResource->FindWidget("LoginPassword");
			if(pWidget==NULL) return true;
			strcpy(szPassword, pWidget->GetText());

			#ifdef _BIRDTEST
				ZChangeGameState(GUNZ_BIRDTEST);
				return ret;
			#endif

//			unsigned long nChecksum = ZGetMZFileChecksum(FILENAME_ZITEM_DESC);
//			unsigned long nChecksum = MGetMatchItemDescMgr()->GetChecksum();
			unsigned long nChecksum = ZGetApplication()->GetFileListCRC();
			nChecksum = nChecksum ^ (*pAllocUID).High ^ (*pAllocUID).Low;

			/*
			 * Steven: Hwid
			 */
			char szHwid[MAX_HWID_LEN];
			GetHwidValue(szHwid);
			// 접속되면 바로 로그인한다
			// Gunz.exe 실행파일의 MD5 값을 구해서 암호화하여 패킷에 담아 보낸다.			// update sgk 0724
			char szEncryptMD5Value[MAX_MD5LENGH] = {0, };
			GetEncryptMD5HashValue(szEncryptMD5Value);


#ifdef LOCALE_NHNUSA
			ZPostNHNUSALogin(const_cast<char*>(((ZNHN_USAAuthInfo*)ZGetLocale()->GetAuthInfo())->GetUserID().c_str()), 
								const_cast<char*>(((ZNHN_USAAuthInfo*)ZGetLocale()->GetAuthInfo())->GetAuthStr()), 
								nChecksum, szEncryptMD5Value);
#else
			ZPostLogin(szID, szPassword, nChecksum, szEncryptMD5Value, szHwid);
#endif


#ifdef _GAMEGUARD
			ZGameguard::m_IsResponseFirstGameguardAuth = false;
#endif

			mlog("Login Posted\n");
		}
	} else if (sock == m_AgentSocket.GetSocket()) {
		
	}

	return ret;
}

#pragma comment(lib, "rpcrt4.lib")
void ZGameClient::GetHwidValue(char* szHwid) 
{
	char Hwid[MAX_HWID_LEN];
	DWORD dwStandard = 0; 
	DWORD dwFeature = 0; 
	_asm 
	{ 
		mov eax, 1 
        cpuid 
        mov dwStandard, eax 
        mov dwFeature, edx 
	}
    DWORD cpuid = ((UINT64)(dwFeature) << 32) | (UINT64)(dwStandard);
	char MACData[5];
	UUID uuid;
    UuidCreateSequential( &uuid );
    for (int i=2; i<8; i++)
	{
		MACData[i - 2] = uuid.Data4[i];
    }
	sprintf(Hwid,"%u-%02X%02X%02X%02X%02X%02X", cpuid, MACData[0], MACData[1], MACData[2], MACData[3], MACData[4], MACData[5]);
	memcpy(szHwid, Hwid, MAX_HWID_LEN);
}

void ZGameClient::GetEncryptMD5HashValue(char* szEncryptMD5Value)							// update sgk 0724
{
	char filePath[MAX_PATH] = {0, };
	GetModuleFileName(NULL, filePath, MAX_PATH);

	unsigned char szMD5Value[ MAX_MD5LENGH ] = {0, };
	MMD5 *pMD5 = new MMD5;
	if (pMD5->md5_file(filePath, szMD5Value) != 0)
	{
		return;
	}
	delete pMD5;

	char szEncryptValue[ MAX_MD5LENGH ] = {0, };
	memcpy( szEncryptValue, szMD5Value, MAX_MD5LENGH );

	m_ServerPacketCrypter.Encrypt( szEncryptValue, MAX_MD5LENGH, (MPacketCrypterKey *)m_ServerPacketCrypter.GetKey() );

	memcpy( szEncryptMD5Value, szEncryptValue, MAX_MD5LENGH );
}

bool ZGameClient::OnSockConnect(SOCKET sock)
{
	ZPOSTCMD0(MC_NET_ONCONNECT);
	return MMatchClient::OnSockConnect(sock);
}

bool ZGameClient::OnSockDisconnect(SOCKET sock)
{
	if (sock == m_ClientSocket.GetSocket()) {
		AgentDisconnect();

		// 로그아웃 버튼클릭시 서버리스트로 이동(넷마블도 변경)
		ZChangeGameState(GUNZ_LOGIN);
		ZPOSTCMD0(MC_NET_ONDISCONNECT);

		ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
		MButton* pWidget = (MButton*)pResource->FindWidget("LoginOK");
		if (pWidget) pWidget->Enable(true);
		MWidget* pLogin = pResource->FindWidget("LoginFrame");
		if (pLogin) pLogin->Show(true);
		pLogin = pResource->FindWidget("Login_ConnectingMsg");
		if (pLogin) pLogin->Show(false);

		ZGetGameInterface()->m_bLoginTimeout = false;

	} else if (sock == m_AgentSocket.GetSocket()) {
	}

	return true;
}

void ZGameClient::OnSockError(SOCKET sock, SOCKET_ERROR_EVENT ErrorEvent, int &ErrorCode)
{
	MMatchClient::OnSockError(sock, ErrorEvent, ErrorCode);

	ZPOSTCMD1(MC_NET_ONERROR, MCmdParamInt(ErrorCode));

	if (ZApplication::GetInstance()->GetLaunchMode() == ZApplication::ZLAUNCH_MODE_NETMARBLE) {	
		// 넷마블에서 로그인
		ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
		MLabel* pLabel = (MLabel*)pResource->FindWidget("NetmarbleLoginMessage");
		if (pLabel) {
//			pLabel->SetText(MGetErrorString(MERR_CLIENT_CONNECT_FAILED));
			pLabel->SetText(
				ZErrStr(MERR_CLIENT_CONNECT_FAILED) );
			pLabel->Show();
		}
	} else {
		ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
		MButton* pWidget = (MButton*)pResource->FindWidget("LoginOK");
		if (pWidget) pWidget->Enable(true);
		MWidget* pLogin = pResource->FindWidget("LoginFrame");
		if (pLogin) pLogin->Show(true);
		pLogin = pResource->FindWidget("Login_ConnectingMsg");
		if (pLogin) pLogin->Show(false);

		MLabel* pLabel = (MLabel*)pResource->FindWidget("LoginError");
		if (pLabel) {
//			pLabel->SetText(MGetErrorString(MERR_CLIENT_CONNECT_FAILED));
			pLabel->SetText( ZErrStr(MERR_CLIENT_CONNECT_FAILED) );

		}

		ZGetGameInterface()->m_bLoginTimeout = false;
	}
}

#include "MListBox.h"
class MCharListItem : public MListItem {
	MUID	m_uid;
	char	m_szName[32];
public:
	MCharListItem(MUID uid, char* szName) { 
		m_uid = uid; strcpy(m_szName, szName); 
	}
	virtual ~MCharListItem()			{}
	virtual const char* GetString(void)	{ return m_szName; }
	MUID GetUID()						{ return m_uid; }
	char* GetName()						{ return m_szName; }

public:

};

int ZGameClient::FindListItem(MListBox* pListBox, const MUID& uid)
{
	for (int i=0; i<pListBox->GetCount(); i++) {
		MCharListItem* pItem = (MCharListItem*)pListBox->Get(i);
		if (pItem->GetUID() == uid) return i;			
	}
	return -1;
}

unsigned long int ZGameClient::GetGlobalClockCount(void)
{
	unsigned long int nLocalClock = GetClockCount();
	if (m_bIsBigGlobalClock) return (nLocalClock + m_nClockDistance);
	else return (nLocalClock - m_nClockDistance);
}

unsigned long int ZGetClockDistance(unsigned long int nGlobalClock, unsigned long int nLocalClock)
{
	if(nGlobalClock>nLocalClock){
		return nGlobalClock - nLocalClock;
	}
	else{
		return nLocalClock + (UINT_MAX - nGlobalClock + 1);
	}
}

void ZGameClient::StartBridgePeer()
{
	SetBridgePeerFlag(false);
	SetBridgePeerCount(10);

	UpdateBridgePeerTime(0);
}

void ZGameClient::Tick(void)
{
    m_MatchStageSetting.AntiHack_CheckCrc();

	unsigned long int nClock = GetGlobalClockCount();

	m_EmblemMgr.Tick(nClock);

	if ((GetBridgePeerCount() > 0) && (GetBridgePeerFlag()==false)) {
		#define CLOCK_BRIDGE_PEER	200
		if (nClock-m_tmLastBridgePeer > CLOCK_BRIDGE_PEER) {
			SetBridgePeerCount(GetBridgePeerCount()-1);
			UpdateBridgePeerTime(nClock);
			CastStageBridgePeer(GetPlayerUID(), GetStageUID());
		}
	}

	if (GetUDPTestProcess()) {
		#define CLOCK_UDPTEST	500
		static unsigned long nUDPTestTimer = 0;
		if (nClock - nUDPTestTimer > CLOCK_UDPTEST) {
			nUDPTestTimer = nClock;

			MMatchPeerInfoList* PeerList = GetPeers();
			for (MMatchPeerInfoList::iterator i=PeerList->begin(); i!= PeerList->end(); i++) {
				MMatchPeerInfo* pPeer = (*i).second;
				if (pPeer->GetProcess()) {
					MCommand* pCmd = CreateCommand(MC_PEER_UDPTEST, pPeer->uidChar);
					SendCommandByUDP(pCmd, pPeer->szIP, pPeer->nPort);
					delete pCmd;
				}
			}

			UpdateUDPTestProcess();
		}
	}

	if ((GetAgentPeerCount() > 0) && (GetAgentPeerFlag()==false)) {
		static unsigned long tmLastAgentPeer = 0;
		#define CLOCK_AGENT_PEER	200
		if (nClock-tmLastAgentPeer > CLOCK_AGENT_PEER) {
			SetAgentPeerCount(GetAgentPeerCount()-1);
			CastAgentPeerConnect();
			tmLastAgentPeer = nClock;
		}
	}

	if (ZApplication::GetGameInterface()->GetState() == GUNZ_STAGE) {
/*		if (GetCountdown() > 0) {
			if (Countdown(nClock) == true) {
				ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
				MListBox* pWidget = (MListBox*)pResource->FindWidget("StageChattingOutput");
				char szMsg[256];
				sprintf(szMsg, "    %d", GetCountdown()+1);
				pWidget->Add(szMsg);
			}
		}*/
	}
/*
#define CLOCK_REQUEST_ATTRIBUTE		1000	// CLOCK_REQUEST_ATTRIBUTE msec 마다 한번씩 요청
	if(nClock-m_nPrevClockRequestAttribute>CLOCK_REQUEST_ATTRIBUTE){
		m_nPrevClockRequestAttribute = nClock;
		ZPOSTCMD1(MC_OBJECT_REQUEST_BASICATTR, MCommandParameterUID(g_MyChrUID));
	}
*/
}

void ZGameClient::OnResponseRecommandedChannel(const MUID& uidChannel)
{
	RequestChannelJoin(uidChannel);
}

void ZGameClient::OnBirdTest()
{
#ifdef _PUBLISH
	return;
#endif

	char szText[256];
	char szList[256]; szList[0] = '\0';
	

	int nCount = (int)m_ObjCacheMap.size();
	for (MMatchObjCacheMap::iterator itor = m_ObjCacheMap.begin(); itor != m_ObjCacheMap.end(); ++itor)
	{
		MMatchObjCache* pObj = (*itor).second;
		strcat(szList, pObj->GetName());
		strcat(szList, ", ");
	}

	sprintf(szText, "BirdTest: %d, %s", nCount, szList);
	MClient::OutputMessage(MZMOM_LOCALREPLY, szText);

	ZCharacterViewList* pWidget = ZGetCharacterViewList(GUNZ_STAGE);
	pWidget->RemoveAll();

	pWidget = ZGetCharacterViewList(GUNZ_LOBBY);
	pWidget->RemoveAll();

}

void ZGameClient::OnForcedEntryToGame()
{
	m_bLadderGame = false;
	m_bForcedEntry = true;
	SetAllowTunneling(true); //TUNEGLEGE
	ZChangeGameState(GUNZ_GAME);
}

void ZGameClient::ClearStageSetting()
{
	m_bForcedEntry = false;

	m_MatchStageSetting.Clear();
}



void ZGameClient::OnLoadingComplete(const MUID& uidChar, int nPercent)
{
	if (ZGetGame())
	{
		ZCharacter* pCharacter = ZGetGame()->m_CharacterManager.Find(uidChar);
		if (pCharacter != NULL)
		{
			MEMBER_SET_CHECKCRC(pCharacter->GetStatus(), nLoadingPercent, nPercent);
		}
	}
}


void ZGameClient::OnResponsePeerRelay(const MUID& uidPeer)
{
	string strNotify = "Unknown Notify";
	NotifyMessage(MATCHNOTIFY_NETWORK_NAT_ESTABLISH, &strNotify);

	char* pszName = "UnknownPlayer";
	MMatchPeerInfo* pPeer = FindPeer(uidPeer);
	if (pPeer) pszName = pPeer->CharInfo.szName;

	char szMsg[128];
	sprintf(szMsg, "%s : from %s", strNotify.c_str(), pszName);


	ZCharacter* pChar = ZGetCharacterManager()->Find( uidPeer);
	if ( pChar && pChar->IsAdminHide())
		return;

	ZChatOutput(szMsg, ZChat::CMT_SYSTEM);
}

void ZGameClient::StartStageList()
{
	MCommand* pCmd = new MCommand(m_CommandManager.GetCommandDescByID(MC_MATCH_STAGE_LIST_START), GetServerUID(), m_This);	
	Post(pCmd);
}

void ZGameClient::StopStageList()
{
	MCommand* pCmd = new MCommand(m_CommandManager.GetCommandDescByID(MC_MATCH_STAGE_LIST_STOP), GetServerUID(), m_This);	
	Post(pCmd);
}

/*
void ZGameClient::SetChannelType(MCHANNEL_TYPE type)
{
	m_CurrentChannelType = type;
}
*/

void ZGameClient::StartChannelList(MCHANNEL_TYPE nChannelType)
{
	ZPostStartChannelList(GetPlayerUID(), (int)nChannelType);
}

void ZGameClient::StopChannelList()
{
	ZPostStopChannelList(GetPlayerUID());
}

void ZGameClient::ReleaseForcedEntry()
{
	m_bForcedEntry = false;
}

void ZGameClient::OnAdminAnnounce(const char* szMsg, const ZAdminAnnounceType nType)
{
	switch (nType)
	{
	case ZAAT_CHAT:
		{
			char szText[512];
//			sprintf(szText, "%s : %s", "관리자", szMsg);
			ZTransMsg( szText, MSG_ADMIN_ANNOUNCE, 1, szMsg );
			ZChatOutput(szText, ZChat::CMT_SYSTEM);
		}
		break;
	case ZAAT_MSGBOX:
		{
			if (ZApplication::GetGameInterface()->GetState() != GUNZ_GAME)
			{
				ZApplication::GetGameInterface()->ShowMessage(szMsg);
			}
			else
			{
				ZChatOutput(szMsg);
			}
		}
		break;
	}
}
//RONNY: Staff Command
void ZGameClient::OnStaffHelp(const char* szTitle, const char* szMsg)
{
	ZChatOutput(szTitle, ZChat::CMT_SYSTEM);
	ZChatOutput(szMsg, ZChat::CMT_STAFFHELP);
}

void ZGameClient::OnGameLevelUp(const MUID& uidChar)
{
	if (ZGetGame())
	{
		ZCharacter* pCharacter = ZGetGame()->m_CharacterManager.Find(uidChar);
		if (pCharacter) {
			pCharacter->LevelUp();

			char temp[256] = "";
			ZTransMsg(temp, MSG_GAME_LEVEL_UP, 1, pCharacter->GetUserAndClanName());
			ZChatOutput(MCOLOR(ZCOLOR_GAME_INFO), temp);
		}
	}
}

void ZGameClient::OnGameLevelDown(const MUID& uidChar)
{
	if (ZGetGame())
	{
		ZCharacter* pCharacter = ZGetGame()->m_CharacterManager.Find(uidChar);
		if (pCharacter) {
			pCharacter->LevelDown();

			char temp[256] = "";
			ZTransMsg(temp, MSG_GAME_LEVEL_DOWN, 1, pCharacter->GetUserAndClanName());
			ZChatOutput(MCOLOR(ZCOLOR_GAME_INFO), temp);
		}
	}
}

void ZGameClient::OnResponseGameInfo(const MUID& uidStage, void* pGameInfoBlob, void* pRuleInfoBlob, void* pPlayerInfoBlob)
{
	if (ZGetGame() == NULL) return;

	// Game Info
	int nGameInfoCount = MGetBlobArrayCount(pGameInfoBlob);
	if (nGameInfoCount > 0) {
		MTD_GameInfo* pGameInfo = (MTD_GameInfo*)MGetBlobArrayElement(pGameInfoBlob, 0);
		ZGetGame()->GetMatch()->SetTeamScore(MMT_RED, pGameInfo->nRedTeamScore);
		ZGetGame()->GetMatch()->SetTeamScore(MMT_BLUE, pGameInfo->nBlueTeamScore);
		ZGetGame()->GetMatch()->SetTeamKills(MMT_RED, pGameInfo->nRedTeamKills);
		ZGetGame()->GetMatch()->SetTeamKills(MMT_BLUE, pGameInfo->nBlueTeamKills);
	}

	// Player Info
	int nPlayerCount = MGetBlobArrayCount(pPlayerInfoBlob);

	for(int i=0; i<nPlayerCount; i++) 
	{
		MTD_GameInfoPlayerItem* pPlayerInfo = (MTD_GameInfoPlayerItem*)MGetBlobArrayElement(pPlayerInfoBlob, i);
		ZCharacter* pCharacter = ZGetGame()->m_CharacterManager.Find(pPlayerInfo->uidPlayer);
		if (pCharacter == NULL) continue;

		if (pPlayerInfo->bAlive == true)
		{
//			pCharacter->SetVisible(true);	// RAONHAJE: PeerOpened TEST
			pCharacter->Revival();
		} 
		else
		{
			if ((ZGetGame()->GetMatch()->IsTeamPlay()) && (ZGetGame()->GetMatch()->GetRoundState() != MMATCH_ROUNDSTATE_FREE))
			{
				// 팀플일 경우 죽어있으면 그냥 보여주지 않는다. 
				// - 함께 난입한 사람 0,0,0에 서있는것 안보이게 하려고..
				pCharacter->ForceDie();
				pCharacter->SetVisible(false);
			}
		}			

		pCharacter->GetStatus().CheckCrc();
		pCharacter->GetStatus().Ref().nKills = pPlayerInfo->nKillCount;
		pCharacter->GetStatus().Ref().nDeaths = pPlayerInfo->nDeathCount;
//		pCharacter->GetStatus()->nScore = (pPlayerInfo->nKillCount-pPlayerInfo->nDeathCount)*1000;
		pCharacter->GetStatus().MakeCrc();
	}


	// Rule Info
	// RuleInfo는 PlayerInfo 다 세팅한 다음에 세팅한다. - 룰에따라 플레이어 정보를 바꿔주기 때문..
	int nRuleCount = MGetBlobArrayCount(pRuleInfoBlob);
	if (nRuleCount > 0) {
		MTD_RuleInfo* pRuleInfoHeader = (MTD_RuleInfo*)MGetBlobArrayElement(pRuleInfoBlob, 0);

		ZGetGame()->GetMatch()->OnResponseRuleInfo(pRuleInfoHeader);
	}
	CHECK_RETURN_CALLSTACK(OnResponseGameInfo);
}

void ZGameClient::OnObtainWorldItem(const MUID& uidChar, const int nItemUID)
{
	if (ZGetGame() == NULL) return;

	ZCharacter* pCharacter = ZGetGame()->m_CharacterManager.Find(uidChar);
	if (pCharacter)
	{
		ZGetWorldItemManager()->ApplyWorldItem( nItemUID, pCharacter );

		ZWeapon* pWeapon = ZGetGame()->m_WeaponManager.GetWorldItem(nItemUID);

		ZWeaponItemKit* pItemKit = MDynamicCast(ZWeaponItemKit, pWeapon);
		if( pItemKit ) { pItemKit->m_bDeath = true; }
	}
}

void ZGameClient::OnSpawnWorldItem(void* pBlob)
{
	if (ZGetGame() == NULL) return;

	int nWorldItemCount = MGetBlobArrayCount(pBlob);

	ZWeaponItemKit*		pItemKit  = NULL;

	ZMovingWeapon* pMWeapon	= NULL;
	ZWorldItem* pWorldItem	= NULL;

	for(int i=0; i<nWorldItemCount; i++) 
	{
		MTD_WorldItem* pWorldItemNode = (MTD_WorldItem*)MGetBlobArrayElement(pBlob, i);

		pWorldItem = ZGetWorldItemManager()->AddWorldItem( pWorldItemNode->nUID, pWorldItemNode->nItemID, 
			(MTD_WorldItemSubType)pWorldItemNode->nItemSubType,
			rvector( (float)pWorldItemNode->x, (float)pWorldItemNode->y, (float)pWorldItemNode->z) );

		pMWeapon = ZGetGame()->m_WeaponManager.UpdateWorldItem(pWorldItemNode->nItemID,rvector( pWorldItemNode->x, pWorldItemNode->y, pWorldItemNode->z));
		
		if( pWorldItem && (pItemKit = MDynamicCast(ZWeaponItemKit, pMWeapon)) ) 
		{
			pItemKit->SetItemUID(pWorldItemNode->nUID);
			pWorldItem->m_bisDraw = false;
		}
	}
}

void ZGameClient::OnRemoveWorldItem(const int nItemUID)
{
	if (ZGetGame() == NULL) return;

	ZGetWorldItemManager()->DeleteWorldItem( nItemUID, true );

	ZWeapon* pWeapon = ZGetGame()->m_WeaponManager.GetWorldItem(nItemUID);
	ZWeaponItemKit* pItemKit = MDynamicCast(ZWeaponItemKit,pWeapon);
	if( pItemKit ) { pItemKit->m_bDeath = true; }
}

void ZGameClient::OnNotifyActivatedTrapItemList(void* pBlob)
{
	if (ZGetGame() == NULL) return;

	// 서버가 난입한 유저에게 현재 맵상에 발동되어 있는 트랩 목록을 알려주는 커맨드 핸들러

	int numTrap = MGetBlobArrayCount(pBlob);

	rvector pos;
	ZObject* pOwner;
	for(int i=0; i<numTrap; i++) 
	{
		MTD_ActivatedTrap* pTrap = (MTD_ActivatedTrap*)MGetBlobArrayElement(pBlob, i);

		pos.x = (float)pTrap->x;
		pos.y = (float)pTrap->y;
		pos.z = (float)pTrap->z;

		pOwner = ZGetCharacterManager()->Find(pTrap->uidOwner);
		if (pOwner == NULL)
			continue;
		// 구현상 아쉬운 부분이지만, 트랩을 던져놓고 나가버린 플레이어의 트랩은 생략하자. 난입한 유저에 한해 그 트랩은 존재하지 않는 것이 된다.

		float fTimeActivated = ZGetGame()->GetTime() - pTrap->nTimeElapsed*0.001f;

		ZGetGame()->m_WeaponManager.AddTrapAlreadyActivated(pos, fTimeActivated, pTrap->nItemID, pOwner);
	}
}

void ZGameClient::OnUserWhisper(char* pszSenderName, char* pszTargetName, char* pszMessage)
{
	char szText[256];
	ZTransMsg( szText, MSG_GAME_WHISPER, 2, pszSenderName, pszMessage );

	//if ( ZGetGame())
	//{
		//if ( (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_DUEL)	&& !ZGetGame()->m_pMyCharacter->IsDie())
			//ZTransMsg( szText, MSG_GAME_WHISPER, 2, pszSenderName, ". . . . .");
	//}


	ZChatOutput(MCOLOR(ZCOLOR_CHAT_WHISPER), szText, ZChat::CL_CURRENT);

	// 마지막에 귓속말을 보낸사람을 기억한다.
	ZGetGameInterface()->GetChat()->SetWhisperLastSender(pszSenderName);	

	// 만약 게임중에 채팅창보기 옵션이 꺼져있을 경우 다시 켜준다.
	if ((ZApplication::GetGameInterface()->GetState() == GUNZ_GAME) && (ZGetGame()))
	{
		if (ZGetCombatInterface())
		{
			if (!ZGetConfiguration()->GetViewGameChat())
			{
				ZGetCombatInterface()->ShowChatOutput(true);
			}
		}
	}
	
}

void ZGameClient::OnChatRoomJoin(char* pszPlayerName, char* pszChatRoomName)
{
	char szText[256];
//	sprintf(szText, "채팅방 '%s'에 '%s'님이 입장하셨습니다.", pszChatRoomName, pszPlayerName);
	ZTransMsg( szText, MSG_LOBBY_WHO_CHAT_ROMM_JOIN, 2, pszChatRoomName, pszPlayerName );
	ZChatOutput(szText, ZChat::CMT_NORMAL, ZChat::CL_CURRENT);
}

void ZGameClient::OnChatRoomLeave(char* pszPlayerName, char* pszChatRoomName)
{
	char szText[256];
//	sprintf(szText, "채팅방 '%s'에서 '%s'님이 퇴장하셨습니다.", pszChatRoomName, pszPlayerName);
	ZTransMsg( szText, MSG_LOBBY_WHO_CHAT_ROOM_EXIT, 2, pszChatRoomName, pszPlayerName );
	ZChatOutput(szText, ZChat::CMT_NORMAL, ZChat::CL_CURRENT);
}

void ZGameClient::OnChatRoomSelectWrite(char* pszChatRoomName)
{
	char szText[256];
// 	sprintf(szText, "채팅방 '%s'로 전환합니다.", pszChatRoomName);
	ZTransMsg( szText, MSG_LOBBY_CHAT_ROOM_CHANGE, 1, pszChatRoomName );
	ZChatOutput(szText, ZChat::CMT_NORMAL, ZChat::CL_CURRENT);
}

void ZGameClient::OnChatRoomInvite(char* pszSenderName, char* pszRoomName)
{
	char szLog[256];
//	sprintf(szLog, "'%s' 님이 채팅방 '%s'로 초대하셨습니다.", pszSenderName, pszRoomName);
	ZTransMsg( szLog, MSG_LOBBY_WHO_INVITATION, 2, pszSenderName, pszRoomName );
	ZChatOutput(szLog, ZChat::CMT_NORMAL, ZChat::CL_CURRENT);

	SetChatRoomInvited(pszRoomName);
}

void ZGameClient::OnChatRoomChat(char* pszChatRoomName, char* pszPlayerName, char* pszChat)
{
	char szText[256];
//	sprintf(szText, "채팅방(%s) %s : %s", pszChatRoomName, pszPlayerName, pszChat);
	ZTransMsg( szText, MRESULT_CHAT_ROOM, 3, pszChatRoomName, pszPlayerName, pszChat );
	ZChatOutput(MCOLOR(ZCOLOR_CHAT_ROOMCHAT), szText, ZChat::CL_CURRENT);
}

void ZGameClient::RequestPrevStageList()
{
	int nStageCursor;
	ZRoomListBox* pRoomList = 
		(ZRoomListBox*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Lobby_StageList");
	if (!pRoomList) return;

	nStageCursor = pRoomList->GetFirstStageCursor() - NUM_DISPLAY_ROOM;
	if (nStageCursor < 0) nStageCursor = 0;

	ZPostRequestStageList(m_uidPlayer, m_uidChannel, nStageCursor);

	int nPage = (nStageCursor/TRANS_STAGELIST_NODE_COUNT)+1;
	ZApplication::GetGameInterface()->SetRoomNoLight(nPage);
}

void ZGameClient::RequestNextStageList()
{
	int nStageCursor;
	ZRoomListBox* pRoomList = 
		(ZRoomListBox*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Lobby_StageList");
	if (!pRoomList) return;

	nStageCursor = pRoomList->GetLastStageCursor() + 1;
	if (nStageCursor > 100) nStageCursor = 100;

	ZPostRequestStageList(m_uidPlayer, m_uidChannel, nStageCursor);

	int nPage = (nStageCursor/TRANS_STAGELIST_NODE_COUNT)+1;
	ZApplication::GetGameInterface()->SetRoomNoLight(nPage);
}

void ZGameClient::RequestStageList(int nPage)
{
	int nStageCursor;

	nStageCursor = (nPage-1) * TRANS_STAGELIST_NODE_COUNT;
	if (nStageCursor < 0) nStageCursor = 0;
	else if (nStageCursor > 100) nStageCursor = 100;

	ZPostRequestStageList(m_uidPlayer, m_uidChannel, nStageCursor);
}

void ZGameClient::OnLocalReport119()
{
/*
	ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
	MEdit* pReasonEdit = (MEdit*)pResource->FindWidget("112_ConfirmEdit");
	if (pReasonEdit)
	{
		pReasonEdit->SetText("");
		pReasonEdit->SetFocus();
	}

	MWidget* pWidget = pResource->FindWidget("112Confirm");
	if(pWidget!=NULL)
	{
		pWidget->Show(true);
//		ZApplication::GetGameInterface()->SetCursorEnable(true);
	}
*/
	ZApplication::GetGameInterface()->Show112Dialog( true);
}

int ZGameClient::ValidateRequestDeleteChar()
{
	ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();

	int nCharIndex = ZCharacterSelectView::GetSelectedCharacter();
	if ( (nCharIndex < 0) || (nCharIndex >= MAX_CHAR_COUNT)) return ZERR_UNKNOWN;

	ZSelectCharacterInfo* pSelectCharInfo = &ZCharacterSelectView::m_CharInfo[ nCharIndex ];
	MTD_AccountCharInfo* pAccountCharInfo = &pSelectCharInfo->m_AccountCharInfo;
	MTD_CharInfo* pCharInfo = &pSelectCharInfo->m_CharInfo;

	// 아직 캐릭터 정보를 못받아왔으면 삭제할 수 없다.
	if (!pSelectCharInfo->m_bLoaded) return ZERR_UNKNOWN;

	// 클랜에 가입되어 있으면 캐릭터를 삭제할 수 없다.
	if (pCharInfo->szClanName[0] != 0)
		return MSG_CLAN_PLEASE_LEAVE_FROM_CHAR_DELETE;

	// 캐쉬아이템이 있으면 삭제할 수 없다
	for (int i = 0; i < MMCIP_END; i++)
	{
		MMatchItemDesc* pItemDesc = MGetMatchItemDescMgr()->GetItemDesc(pCharInfo->nEquipedItemDesc[i]);
		if (pItemDesc)
		{
			if (pItemDesc->IsCashItem()) return MSG_CANNOT_DELETE_CHAR_FOR_CASHITEM;
		}
	}

	return ZOK;
}

void ZGameClient::RequestChannelJoin(const MUID& uidChannel)
{
	ZPostChannelRequestJoin(GetPlayerUID(), uidChannel);
}

void ZGameClient::RequestChannelJoin(const MCHANNEL_TYPE nChannelType, char* szChannelName)
{
	ZPostChannelRequestJoinFromChannelName(GetPlayerUID(), (int)nChannelType, szChannelName);
}

void ZGameClient::RequestGameSuicide()
{
	ZGame* pGame = ZGetGameInterface()->GetGame();
	if (!pGame) return;

	ZMyCharacter* pMyCharacter = pGame->m_pMyCharacter;
	if (!pMyCharacter) return;

	if ((!pMyCharacter->IsDie()) &&  (pGame->GetMatch()->GetRoundState() == MMATCH_ROUNDSTATE_PLAY))
	{
		pMyCharacter->SetLastDamageType(ZD_NONE);//폭탄에 패배 했다고만 안나오면됨~

		ZPostRequestSuicide(ZGetGameClient()->GetPlayerUID());
	}
}

void ZGameClient::OnResponseResult(const int nResult)
{
	if (nResult != MOK)
	{
		if (ZApplication::GetGameInterface()->GetState() == GUNZ_GAME)
		{
			ZChatOutput(MCOLOR(ZCOLOR_CHAT_SYSTEM), ZErrStr(nResult) );
		}
		else 
		{
			ZApplication::GetGameInterface()->ShowErrorMessage( nResult );
		}
		
	}
}

// 나중에 삭제 요망
void blog(const char *pFormat,...)
{
	char szBuf[256];

	va_list args;
	va_start(args,pFormat);
	vsprintf(szBuf, pFormat, args);
	va_end(args);

	strcat(szBuf, "\n");

//	OutputDebugString(szBuf);
	if ( ZApplication::GetGameInterface()->GetState() == GUNZ_LOBBY)
		ZChatOutput(szBuf, ZChat::CMT_SYSTEM, ZChat::CL_LOBBY);
	else if ( ZApplication::GetGameInterface()->GetState() == GUNZ_STAGE)
		ZChatOutput(szBuf, ZChat::CMT_SYSTEM, ZChat::CL_STAGE);
}


// 다른 플레이어 정보 보기
void ZGameClient::OnResponseCharInfoDetail(void* pBlob)
{
#ifndef _DEBUG	// 완성될때까지
	return;
#endif

	MWidget* pWidget= ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Characterinfo");
	if(pWidget)
		pWidget->Show();

	int nCount = MGetBlobArrayCount(pBlob);
	if (nCount != 1) return;

	MTD_CharInfo_Detail* pCharInfoDetail = (MTD_CharInfo_Detail*)MGetBlobArrayElement(pBlob, 0);

/*
  == 플레이어 정보 다이알로그에 들어가야 하는 것들 ==
   * 버튼: 귓말, 따라가기, 친구추가, 닫기
   * 캐릭터 코스튬 화면
   * 일반정보탭, 장비정보탭
*/
	
	// 일반정보 탭
	blog("^9%s", ZMsg( MSG_CHARINFO_TITLE));
	blog("^9%s : ^1%s^9(%s)",   ZMsg( MSG_CHARINFO_NAME),
								pCharInfoDetail->szName,
								ZGetSexStr(MMatchSex(pCharInfoDetail->nSex), true));
	char sztemp[256];
	if ( strcmp( pCharInfoDetail->szClanName, "") == 0)
		strcpy( sztemp, "---");
	else
		sprintf( sztemp, "%s(%s)", pCharInfoDetail->szClanName, ZGetClanGradeStr(pCharInfoDetail->nClanGrade));
	blog("^9%s : %s", ZMsg( MSG_CHARINFO_CLAN), sztemp);
	blog("^9%s : %d %s", ZMsg( MSG_CHARINFO_LEVEL), pCharInfoDetail->nLevel, ZMsg(MSG_CHARINFO_LEVELMARKER));
	int nWinPercent = (int)( (float)pCharInfoDetail->nKillCount / (float)(pCharInfoDetail->nKillCount + pCharInfoDetail->nDeathCount) * 100.0f);
	blog("^9%s : %d%s/%d%s(%d%%)",  ZMsg( MSG_CHARINFO_WINPERCENT),
									pCharInfoDetail->nKillCount,
									ZMsg( MSG_CHARINFO_WIN),
									pCharInfoDetail->nDeathCount,
									ZMsg( MSG_CHARINFO_LOSE),
									nWinPercent);
	ZGetTimeStrFromSec( sztemp, pCharInfoDetail->nConnPlayTimeSec);
	blog("^9%s : %s", ZMsg( MSG_CHARINFO_CONNTIME), sztemp);
	blog("");

//	blog("이름: %s", pCharInfoDetail->szName);
//	blog("클랜: %s", pCharInfoDetail->szClanName);
//	blog("클랜직책: %s", ZGetClanGradeStr(pCharInfoDetail->nClanGrade));
//	blog("성별: %s", ZGetSexStr(MMatchSex(pCharInfoDetail->nSex), true));
//	blog("레벨: %d", pCharInfoDetail->nLevel);
//	blog("경험치: %d", pCharInfoDetail->nXP);
//	blog("바운티: %d", pCharInfoDetail->nBP);
//	blog("Kill/Death: %d/%d", pCharInfoDetail->nKillCount, pCharInfoDetail->nDeathCount);

//	char sztemp[256];
//	ZGetTimeStrFromSec(sztemp, pCharInfoDetail->nConnPlayTimeSec);
//	blog("현재접속시간: %s", sztemp);

//	ZGetTimeStrFromSec(sztemp, pCharInfoDetail->nTotalPlayTimeSec);
//	blog("총접속시간: %s", sztemp);

	// 장비정보 탭
//	blog("=장비정보탭=================");
	
//	blog(" 각 부위별 아이템 이름 나열...");
}

void ZGameClient::OnNotifyCallVote(const char* pszDiscuss, const char* pszArg)
{
//	ZGetGameInterface()->GetCombatInterface()->GetVoteInterface()->ShowVote(true);

	SetVoteInProgress(true);
	SetCanVote(true);
	
	char szText[256] = "";
	if ( stricmp(pszDiscuss, "joke") == 0 ) {
		ZTransMsg( szText, MSG_VOTE_START, 1, pszArg );
		ZChatOutput(szText, ZChat::CMT_SYSTEM, ZChat::CL_CURRENT);
	}
	else if ( stricmp(pszDiscuss, "kick") == 0 ) {
		sprintf( m_szVoteText, ZMsg(MSG_VOTE_KICK), pszArg );
		ZChatOutput(szText, ZChat::CMT_SYSTEM, ZChat::CL_CURRENT);
	}
}

void ZGameClient::OnNotifyVoteResult(const char* pszDiscuss, int nResult)
{
	if (ZGetGameInterface()->GetCombatInterface() == NULL)
		return;

	ZGetGameInterface()->GetCombatInterface()->GetVoteInterface()->ShowTargetList(false);

	SetVoteInProgress(false);
	SetCanVote(false);

//	char szText[256] = "";
	if (nResult == 0) {
		ZChatOutput( ZMsg(MSG_VOTE_REJECTED), ZChat::CMT_SYSTEM, ZChat::CL_CURRENT);
	}
	else if (nResult == 1) {
		ZChatOutput( ZMsg(MSG_VOTE_PASSED), ZChat::CMT_SYSTEM, ZChat::CL_CURRENT );
	}
}

void ZGameClient::OnVoteAbort( const int nMsgCode )
{
	ZChatOutput( ZMsg(nMsgCode), ZChat::CMT_SYSTEM, ZChat::CL_CURRENT );	
}

void ZGameClient::RequestOnLobbyCreated()
{
	ZPostRequestStageList(GetPlayerUID(), GetChannelUID(), 0);
	ZPostRequestChannelPlayerList(GetPlayerUID(), GetChannelUID(), 0);
}

void ZGameClient::RequestOnGameDestroyed()
{
	// 새로 바뀐 내정보를 요청한다.
	ZPostRequestMySimpleCharInfo(ZGetGameClient()->GetPlayerUID());

	// 새로 바뀐 클랜 정보도 요청한다.
	if ((GetChannelType() == MCHANNEL_TYPE_CLAN))
	{
		ZPostRequestClanInfo(GetPlayerUID(), m_szChannel);
	}
}

// 따라가기 요청에 대한 응답이 있을시 응답을 채팅창에 출력해줌.
// [ IN ] : 출력할 메시지.
void ZGameClient::OnFollowResponse( const int nMsgID )
{
	ZGetGameInterface()->GetChat()->Clear(ZChat::CL_LOBBY);
	const char* pszMsg = ZErrStr( nMsgID );
	if( 0 == pszMsg )
		return;

	ZChatOutput(pszMsg, ZChat::CMT_SYSTEM, ZChat::CL_LOBBY);
}// OnFollowResponse

void ZGameClient::OnClanResponseEmblemURL(unsigned int nCLID, unsigned int nEmblemChecksum, const char* szEmblemURL)
{
	char szFullURL[2048]="";
	//sprintf(szFullURL, "http://cwfile.netmarble.com%s", szEmblemURL);

#ifdef LOCALE_NHNUSA

	if ( ((ZNHN_USAAuthInfo*)(ZGetLocale()->GetAuthInfo()))->IsAlpha())
		sprintf( szFullURL, "%s%s", Z_LOCALE_TEMBLEM_URL, szEmblemURL);
	else
		sprintf( szFullURL, "%s%s", Z_LOCALE_EMBLEM_URL, szEmblemURL);
#else
	sprintf( szFullURL, "%s%s", Z_LOCALE_EMBLEM_URL, szEmblemURL);
#endif

#ifdef _DEBUG
	mlog( "ZGameClient::OnClanResponseEmblemURL. full url : %s\n", szFullURL );
#endif

	// 엠블렘 url이 빈 상태로 오는 경우가 있는 것 같다.
	// 그러면 주소 뒷부분이 완성이 안되기 때문에 폴더리스트 전체를 요청하게 되는데 이러면 엠블렘파일서버 부하가 커진다고 한다..
	if (0 == strlen(szEmblemURL)) {
		mlog("Emblem url is null! clanID(%d)\n", nCLID);
		return;
	}

	m_EmblemMgr.ProcessEmblem(nCLID, szFullURL, nEmblemChecksum);
}

void ZGameClient::OnClanEmblemReady(unsigned int nCLID, const char* szURL)
{
	ZGetEmblemInterface()->ReloadClanInfo(nCLID);

	if(ZGetNetRepository()->GetClanInfo()->nCLID == nCLID) {
		ZIDLResource* pRes = ZApplication::GetGameInterface()->GetIDLResource();
		MPicture* pPicture= (MPicture*)pRes->FindWidget( "Lobby_ClanInfoEmblem" );
		if ( pPicture)
			pPicture->SetBitmap( ZGetEmblemInterface()->GetClanEmblem( nCLID));
	}
}


void ZGameClient::OnExpiredRentItem(void* pBlob)
{
	int nBlobSize = MGetBlobArrayCount(pBlob);

	char szText[1024];
	sprintf(szText, "%s\n", ZMsg( MSG_EXPIRED));

	for(int i=0; i < nBlobSize; i++)
	{
		unsigned long int* pExpiredItemID = (unsigned long int*)MGetBlobArrayElement(pBlob, i);

		char szItemText[256];

		MMatchItemDesc* pItemDesc = MGetMatchItemDescMgr()->GetItemDesc(*pExpiredItemID);
		if (pItemDesc)
		{
			sprintf(szItemText, "[%d] %s\n", i+1, pItemDesc->m_pMItemName->Ref().m_szItemName);
			if ((strlen(szText) + strlen(szItemText)) <= 1022) strcat(szText, szItemText);
		}
	}

	ZApplication::GetGameInterface()->ShowMessage(szText);
}


bool ZGameClient::CreateUPnP(unsigned short nUDPPort)
{
	if(!m_pUPnP)
		m_pUPnP = new UPnP;

	//////////////////////////////////////////////////////////////////////////
	/// UPnP Enable
	// Activate Port
	if(m_pUPnP->Create(nUDPPort))
	{
		TRACE("UPnP: Port: %d\n", nUDPPort);
		mlog("%d upnp port forward initialized.\n",nUDPPort);
		return true;
	}
	else
	{
		// Failed: Use Default Port
		TRACE("UPnP: Failed to forward port\n");
//		Sleep(1000);
	}
	return false;
}

bool ZGameClient::DestroyUPnP()
{
	if(m_pUPnP)
	{
		m_pUPnP->Destroy();
		delete m_pUPnP;
	}

	return true;
}



//////////////////////////////////////////////////////////////////////////


void ZGameClient::OnBroadcastDuelRenewVictories(const char* pszChampionName, const char* pszChannelName, int nRoomno, int nVictories)
{
	char szText[256];
	char szVic[32], szRoomno[32];

	sprintf(szVic, "%d", nVictories);
	sprintf(szRoomno, "%d", nRoomno);

	ZTransMsg(szText, MSG_DUEL_BROADCAST_RENEW_VICTORIES, 4, pszChampionName, pszChannelName, szRoomno, szVic);

	ZChatOutput(szText, ZChat::CMT_BROADCAST);
}

void ZGameClient::OnBroadcastDuelInterruptVictories(const char* pszChampionName, const char* pszInterrupterName, int nVictories)
{
	char szText[256];
	char szVic[32];
	sprintf(szVic, "%d", nVictories);
	ZTransMsg(szText, MSG_DUEL_BROADCAST_INTERRUPT_VICTORIES, 3, pszChampionName, pszInterrupterName, szVic);

	ZChatOutput(szText, ZChat::CMT_BROADCAST);
}



void ZGameClient::ChangeQuestStage()
{
	// 퀘스트 서버의 퀘스트 채널이면 셋팅을 퀘스트 모드로 설정 함.
	if( (0 != ZGetGameClient()) && 
		(MSM_TEST == ZGetGameClient()->GetServerMode()) &&
		(0 == stricmp(MCHANNEL_RULE_QUEST_STR, ZGetGameClient()->GetChannelRuleName())) &&
		(!ZGetGameTypeManager()->IsQuestDerived(ZGetGameClient()->GetMatchStageSetting()->GetGameType())) && 
		//(MMATCH_GAMETYPE_QUEST != ZGetGameClient()->GetMatchStageSetting()->GetGameType()) && 
		ZGetGameClient()->AmIStageMaster() )
	{
		MSTAGE_SETTING_NODE StageSetting;

		StageSetting.bAutoTeamBalancing = true;
		StageSetting.bForcedEntryEnabled = true;
		//StageSetting.bObserverEnabled = false;
		StageSetting.bTeamKillEnabled = false;
		StageSetting.bTeamWinThePoint = false;
		//StageSetting.bVoteEnabled = true;
		StageSetting.nGameType = MMATCH_GAMETYPE_QUEST;
		StageSetting.nLimitLevel = 0;
		StageSetting.nLimitTime = 20;
		StageSetting.nMapIndex = 0;
		StageSetting.nMaxPlayers = 8;
		StageSetting.nRoundMax = 10;
		memset( StageSetting.szMapName, 0, 32 );
		strncpy( StageSetting.szMapName, "Mansion", 7 );
		StageSetting.uidStage = ZGetGameClient()->GetStageUID();

		// 퀘스트일때에 릴레이맵은 닫아준다.
		StageSetting.bIsRelayMap = false;
		StageSetting.nRelayMapListCount = 0;
		StageSetting.nRelayMapType = RELAY_MAP_TURN;
		StageSetting.nRelayMapRepeatCount = RELAY_MAP_3REPEAT;

		ZPostStageSetting(ZGetGameClient()->GetUID(), ZGetGameClient()->GetStageUID(), &StageSetting );
	}
}


void ZGameClient::OnRecieveGambleItem( unsigned int nRecvItem, unsigned int nCnt, unsigned int nTime)
{
	char szText[ 256];
	char szName[ 256];
	if(nCnt < 1){nCnt = 1;}
	MMatchItemDesc* pItemDesc = MGetMatchItemDescMgr()->GetItemDesc( nRecvItem);
	if ( pItemDesc)
	{
		sprintf(szName, "%s (x%d)", pItemDesc->m_pMItemName->Ref().m_szItemName, nCnt);
	}
	MQuestItemDesc* pQuestItemDesc = GetQuestItemDescMgr().FindQItemDesc( nRecvItem);
	if ( pQuestItemDesc)
	{
		sprintf(szName, "%s (x%d)", pQuestItemDesc->m_szQuestItemName, nCnt);
	}

	if (!pItemDesc && !pQuestItemDesc)
		return;

	ZTransMsg( szText, MSG_RECEIVE_GAMBLE_ITEM, 1, szName);
	ZApplication::GetGameInterface()->ShowMessage( szText);
}


void ZGameClient::OnResponseUpdateStageEquipLook( const MUID& uidPlayer, const int nParts, const int nItemID )
{
	MMatchObjCacheMap::iterator itFind = m_ObjCacheMap.find( uidPlayer );
	if( m_ObjCacheMap.end() == itFind )
	{
		return;
	}

	MMatchObjCache* pObjCache = itFind->second;

	pObjCache->GetCostume()->nEquipedItemID[ nParts ] = nItemID;

#ifdef _DEBUG
	mlog( "update stage look : parts(%d), itemid(%d)\n"
		, nParts
		, nItemID );
#endif
}

void ZGameClient::OnPrepareRun( void )
{
}

bool ZGameClient::IsUDPCommandValidationCheck(int nCommandID)
{
	return !m_UPDCommadHackShield.IsDeniedCommand(nCommandID);
}

void ZGameClient::OnAdminResponseKickPlayer(int nResult)
{
	if( IsAdminGrade( ZGetMyInfo()->GetUGradeID() ) ) 
	{
		if( nResult != MOK ) {
			const char *strError = ZErrStr( nResult );
			if( strError ) {
				ZChatOutput(strError, ZChat::CMT_NORMAL, ZChat::CL_LOBBY, MCOLOR(255,128, 64));
			}
		}	
		else {
#ifdef _DEBUG
			ZChatOutput("성공", ZChat::CMT_NORMAL, ZChat::CL_LOBBY, MCOLOR(255,128, 64));
#endif
		}
	}	
}

void ZGameClient::OnAdminResponseBlockPlayer(int nResult)
{
	if( IsAdminGrade( ZGetMyInfo()->GetUGradeID() ) ) 
	{
		if( nResult != MOK ) {
			const char *strError = ZErrStr( nResult );
			if( strError ) {
				ZChatOutput(strError, ZChat::CMT_NORMAL, ZChat::CL_LOBBY, MCOLOR(255, 128, 64));
			}
		} 
		else {
#ifdef _DEBUG
			ZChatOutput("성공", ZChat::CMT_NORMAL, ZChat::CL_LOBBY, MCOLOR(255, 128, 64));
#endif
		}
	}
}

void ZGameClient::OnAdminResponseMutePlayer(int nResult)
{
	if( IsAdminGrade( ZGetMyInfo()->GetUGradeID() ) ) {
		if( nResult != MOK ) {
			const char *strError = ZErrStr( nResult );
			if( strError ) {
				ZChatOutput(strError, ZChat::CMT_NORMAL, ZChat::CL_LOBBY, MCOLOR(255, 128, 64));
			}
		} 
		else {
#ifdef _DEBUG
			ZChatOutput("성공", ZChat::CMT_NORMAL, ZChat::CL_LOBBY, MCOLOR(255, 128, 64));
#endif
		}
	}
	else {
		if( nResult == MOK ) {
			const char *strMsg = ZMsg( MSG_CHAT_MUTE_BY_ADMIN );
			if( strMsg ) {
				ZChatOutput(strMsg, ZChat::CMT_NORMAL, ZChat::CL_LOBBY);
			}
		}
	}	
}