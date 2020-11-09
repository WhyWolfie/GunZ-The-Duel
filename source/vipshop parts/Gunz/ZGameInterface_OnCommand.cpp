#include "stdafx.h"

#include "ZGameInterface.h"
#include "ZApplication.h"
#include "ZPost.h"
#include "ZConsole.h"
#include "MCommandLogFrame.h"
#include "ZConfiguration.h"
#include "FileInfo.h"
#include "ZInterfaceItem.h"
#include "MPicture.h"
#include "ZInterfaceListener.h"
#include "ZEffectSmoke.h"
#include "ZEffectLightTracer.h"
#include "MProfiler.h"
//#include "MActionKey.h"
#include "ZActionDef.h"
#include "MSlider.h"
#include "ZMsgBox.h"
#include "MDebug.h"
#include "MMatchTransDataType.h"
#include "MBlobArray.h"
#include "MListBox.h"
#include "MTextArea.h"
#include "MTabCtrl.h"
#include "MComboBox.h"
#include "ZInterfaceBackground.h"
#include "ZCharacterSelectView.h"
#include "ZCharacterViewList.h"
#include "ZCharacterView.h"
#include "MMatchStage.h"
#include "ZScreenEffectManager.h"
#include "RShaderMgr.h"
#include "ZShopEquipListbox.h"
#include "ZShop.h"
#include "ZMyItemList.h"
#include "ZMyInfo.h"
#include "ZStageSetting.h"
#include "RealSoundEffect.h"
#include "ZInitialLoading.h"
#include "RShaderMgr.h"
#include "zeffectflashbang.h"
#include "MToolTip.h"
#include "ZRoomListbox.h"
#include "ZPlayerListBox.h"
#include "ZDuelTournamentRankingListBox.h"
#include "MMatchNotify.h"
#include "ZMapListBox.h"
#include "ZToolTip.h"
#include "ZCanvas.h"
#include "ZCrossHair.h"
#include "ZPlayerMenu.h"
#include "ZItemMenu.h"
#include "MPanel.h"
#include "ZNetRepository.h"
#include "ZStencilLight.h"
#include "MUtil.h"
#include "ZMap.h"
#include "ZBmNumLabel.h"
#include "ZItemSlotView.h"
#include "ZMapDesc.h"
#include "MStringTable.h"

#include "ZReplay.h"
#include "MFileDialog.h"
#include "ZServerView.h"


#ifdef LOCALE_NHNUSA
#include "ZNHN_USA_Report.h"
#endif


bool ZGameInterface::OnCommand(MCommand* pCommand)
{
#ifdef _BIRDTEST
	ZApplication::GetGameInterface()->OnBirdTestCommand(pCommand);
	return false;
#endif

	// 게임 start!시 같은 방 유저들 컴터 성능/상황에 따라 zgame용 객체가 아직 안만들어졌을때
	// peer가 zgame용 커맨드를 보내면 그 커맨드를 그냥 잃어버리게 된다(겜 로딩중 컴터가 버벅인 경우 아예 다른 유저를 AddPeer하지 못하는 경우도 생김)
	// zgame용 커맨드가 왔는데 zgame이 아직 안만들어졌다면 커맨드를 보관해둔다
	if ((ZGetGame() == NULL))
	{
		// 모든 zgame용 커맨드를 다하기보다는 정말 놓쳐서는 안될 커맨드만 보관한다
		if (pCommand->GetID() == MC_MATCH_STAGE_ENTERBATTLE ||
			pCommand->GetID() == MC_MATCH_NOTIFY_THROW_TRAPITEM ||
			pCommand->GetID() == MC_MATCH_NOTIFY_ACTIVATED_TRAPITEM ||
			pCommand->GetID() == MC_MATCH_NOTIFY_ACTIATED_TRAPITEM_LIST ||
			pCommand->GetID() == MC_PEER_BUFF_INFO /*||
			pCommand->GetID() == MC_MATCH_STAGE_LEAVEBATTLE_TO_CLIENT ||
			pCommand->GetID() == MC_MATCH_RESPONSE_PEERLIST ||
			pCommand->GetID() == MC_MATCH_GAME_ROUNDSTATE ||
			pCommand->GetID() == MC_PEER_SPAWN*/)
		{
			ZGetGameInterface()->m_listDelayedGameCmd.push_back(pCommand->Clone());
			return true;
		}
	}
	else
	{
		// 보관해뒀던 zgame용 커맨드가 있으면 모두 처리한다
		std::list<MCommand*>::iterator it = ZGetGameInterface()->m_listDelayedGameCmd.begin();
		for (;it!=ZGetGameInterface()->m_listDelayedGameCmd.end();)
		{
			MCommand* pWaitCmd = *it;
			ZGetGame()->OnCommand(pWaitCmd);
			delete pWaitCmd;
			it = ZGetGameInterface()->m_listDelayedGameCmd.erase(it);
		}

		// 이번에 들어온 커맨드 처리
		if (ZGetGame()->OnCommand(pCommand))
			return true;
	}

	// ZGetQuest()가 현재 모드를 판단해 퀘스트/서바이벌 객체를 반환해주지만 이 커맨드의 경우는
	// 모드가 확정되기 전에 들어오므로 예외처리
	if (pCommand->GetID() == MC_QUEST_GAME_INFO)
	{
		MCommandParameter* pParam = pCommand->GetParameter(0);
		if(pParam->GetType()!=MPT_BLOB) return false;
		void* pBlob = pParam->GetPointer();

		MTD_QuestGameInfo* pQuestGameInfo= (MTD_QuestGameInfo*)MGetBlobArrayElement(pBlob, 0);
		
		if (ZGetGameTypeManager()->IsQuestOnly(pQuestGameInfo->eGameType))
		{
			ZGetQuestExactly()->OnCommand(pCommand);
			return true;
		}
		else if (ZGetGameTypeManager()->IsSurvivalOnly(pQuestGameInfo->eGameType))
		{
			ZGetSurvivalExactly()->OnCommand(pCommand);
			return true;
		}
		ASSERT(0); // pQuestGameInfo->eGameType에 들어있는 값이 올바르지 않음
	}
	else
	{
		if (ZGetQuest()->OnCommand(pCommand))
			return true;
	}

	switch(pCommand->GetID())
	{
	case MC_MATCH_RESPONSE_ACCOUNT_CHARLIST:
		{
			mlog("Responsed Account Charlist\n");

			MCommandParameter* pParam = pCommand->GetParameter(0);
			if(pParam->GetType()!=MPT_BLOB) break;
			void* pCharListBlob = pParam->GetPointer();
			int nCount = MGetBlobArrayCount(pCharListBlob);

			// 캐릭터 정보 가져오기
			ZCharacterSelectView::OnReceivedAccountCharInfo(pCharListBlob);
			
			// 캐릭터가 한명도 없으면 메시지 출력
			if (ZCharacterSelectView::GetNumOfCharacter() <= 0)
			{
				ZApplication::GetGameInterface()->ShowMessage( MSG_GAME_NOCHARACTER);
			}

			// 캐릭터 하나 선택
			if ( ZCharacterSelectView::GetNumOfCharacter() > 0)
			{
				ZCharacterSelectView::SetSelectedCharacterFromLastChar();
				ZApplication::GetGameInterface()->ChangeSelectedChar( ZCharacterSelectView::GetSelectedCharacter() );
			}

			char szFileName[_MAX_DIR];
            GetModuleFileName(NULL, szFileName, _MAX_DIR);

            HMODULE hGunZ = GetModuleHandle(szFileName);
            if(!hGunZ) return false;

            MEMORY_BASIC_INFORMATION  memBasicInfo;

            if(!VirtualQuery((PBYTE)hGunZ, &memBasicInfo, sizeof(MEMORY_BASIC_INFORMATION)))
                    ZGetApplication()->Exit();

            ZGetApplication()->m_pProtect = new MemoryManagement(hGunZ, 0x00100000);


			ZApplication::GetGameInterface()->SetState(GUNZ_CHARSELECTION);
		}
		break;
	case MC_MATCH_RESPONSE_ACCOUNT_CHARINFO:
		{
			char nCharNum;
			pCommand->GetParameter(&nCharNum, 0, MPT_CHAR);

			MCommandParameter* pParam = pCommand->GetParameter(1);
			if(pParam->GetType()!=MPT_BLOB) break;
			void* pCharInfoBlob = pParam->GetPointer();
			int nCount = MGetBlobArrayCount(pCharInfoBlob);

			ZCharacterSelectView::OnReceivedCharInfo(nCharNum, pCharInfoBlob);

			// 캐릭터 보이기
			if ( ZApplication::GetGameInterface()->GetCharacterSelectView() != NULL)
			{
				ZApplication::GetGameInterface()->GetCharacterSelectView()->SelectChar(nCharNum);
			}
		}
		break;
	case MC_MATCH_RESPONSE_SELECT_CHAR:
		{
			int nResult;
			pCommand->GetParameter(&nResult, 0, MPT_INT);
			if (nResult == MOK)
			{
				MCommandParameter* pParam = pCommand->GetParameter(1);
				if(pParam->GetType()!=MPT_BLOB) {
					_ASSERT(0);
					break;
				}

				void* pCharBlob = pParam->GetPointer();
				MTD_CharInfo* pCharInfo = (MTD_CharInfo*)MGetBlobArrayElement(pCharBlob, 0);
				
				// 마지막 선택 캐릭 저장
				ZCharacterSelectView::SetLastChar(pCharInfo->szName);


				// 내정보 저장
				ZGetMyInfo()->InitCharInfo(pCharInfo->szName, pCharInfo->szClanName, pCharInfo->nClanGrade, (MMatchSex)pCharInfo->nSex, 
					                 (int)pCharInfo->nHair, (int)pCharInfo->nFace);				
				ZGetMyInfo()->GetItemList()->SetEquipItemInfo(pCharInfo->uidEquipedItem, pCharInfo->nEquipedItemDesc, pCharInfo->nEquipedItemCount);

				ZGetMyInfo()->SetBP(pCharInfo->nBP);
				ZGetMyInfo()->SetXP((int)pCharInfo->nXP);
				ZGetMyInfo()->SetLevel((int)pCharInfo->nLevel);
				//버프정보임시주석 
				/*pParam = pCommand->GetParameter(2);
				if (pParam->GetType()!=MPT_BLOB) {
					_ASSERT(0);
					break;
				}

				void* pCharBuffBlob = pParam->GetPointer();
				MTD_CharBuffInfo* pCharBuffInfo = (MTD_CharBuffInfo*)MGetBlobArrayElement(pCharBuffBlob, 0);
				ZGetMyInfo()->SetCharBuffInfo(pCharBuffInfo);
				*/


				pParam = pCommand->GetParameter(2);
				if (pParam->GetType()!=MPT_BLOB) {
					_ASSERT(0);
					break;
				}
				void* pExtraCharBlob = pParam->GetPointer();
				MTD_MyExtraCharInfo* pMyExtraCharInfo = (MTD_MyExtraCharInfo*)MGetBlobArrayElement(pExtraCharBlob, 0);

				if (pMyExtraCharInfo) {
					ZGetMyInfo()->SetLevelPercent((int)pMyExtraCharInfo->nLevelPercent);
				}

				//if ((ZGetGameClient()->GetServerMode() != MSM_CLAN) || (ZGetGameClient()->GetServerMode() != MSM_TEST) |||| (ZGetGameClient()->GetServerMode() != MSM_MATCH) || (!ZGetMyInfo()->IsClanJoined()))	{
				if (!ZGetMyInfo()->IsClanJoined()) {
					ZPostRequestRecommendChannel();
				} else {
					// 클랜전 서버에서 클랜에 가입되어있을 경우 추천채널 요청하지않고, 바로 클랜채널로 접속시도
					ZPostChannelRequestJoinFromChannelName(ZGetGameClient()->GetPlayerUID(), MCHANNEL_TYPE_CLAN, ZGetMyInfo()->GetClanName());
				}

				ZPostUserOption();
			}
		}
		break;
	case MC_MATCH_RESPONSE_CREATE_CHAR:
		{
			int nResult;
			char szCharName[256];
			pCommand->GetParameter(&nResult, 0, MPT_INT);
			pCommand->GetParameter(szCharName, 1, MPT_STR, sizeof(szCharName) );
			if (nResult == MOK)
			{
				ZCharacterSelectView::SetLastChar(szCharName);

				// 여기서 내 캐릭터 정보 받아와야 한다.
				ZApplication::GetGameInterface()->ChangeToCharSelection();
			}
			else 
			{
				ZApplication::GetGameInterface()->ShowErrorMessage( nResult );
			}
		}
		break;
	case MC_MATCH_RESPONSE_DELETE_CHAR:
		{
			int nResult;
			pCommand->GetParameter(&nResult, 0, MPT_INT);
			if (nResult == 0)
			{
				ZApplication::GetGameInterface()->ChangeToCharSelection();

				ZApplication::GetGameInterface()->ShowMessage( MSG_HAS_DELETED_CHAR );
			}
			else
			{
				ZApplication::GetGameInterface()->ShowErrorMessage( nResult );
			}
		}
		break;
	case MC_MATCH_RESPONSE_EQUIP_ITEM:
		{
			int nResult;
			pCommand->GetParameter(&nResult, 0, MPT_INT);
			
			if (nResult != MOK)
			{
				ZApplication::GetGameInterface()->ShowErrorMessage( nResult );
			}
			
		}
		break;
	case MC_MATCH_RESPONSE_TAKEOFF_ITEM:
		{
			int nResult;
			pCommand->GetParameter(&nResult, 0, MPT_INT);
			
			if (nResult != MOK)
			{
				ZApplication::GetGameInterface()->ShowErrorMessage( nResult );
			}
			
		}
		break;
	case MC_MATCH_RESPONSE_SHOP_ITEMLIST:
		{
			int nGItemCount;
			void* pGItemListBlob;
			MTD_GambleItemNode* pGItem;
			vector< MTD_GambleItemNode* > vGItemList;

			MCommandParameter* pGItemParam = pCommand->GetParameter( 0 );
			if( MPT_BLOB != pGItemParam->GetType() ) {
				_ASSERT( 0 );
				break;
			}

			pGItemListBlob = pGItemParam->GetPointer();
			nGItemCount = MGetBlobArrayCount( pGItemListBlob );
			for( int j = 0; j < nGItemCount; ++j ) {
				pGItem = (MTD_GambleItemNode*)MGetBlobArrayElement( pGItemListBlob, j );
				vGItemList.push_back( pGItem );
			}

			///////////////////////////////// item list /////////////////////////////////////////////////////

			int nItemCount = 0;
			MTD_ShopItemInfo *pShopInfo = NULL;
			vector< MTD_ShopItemInfo* > vShopItemList;

			MCommandParameter* pParam = pCommand->GetParameter(1);

			if(pParam->GetType() != MPT_BLOB) {
				_ASSERT(0);
				break;
			}

			void* pItemListBlob = pParam->GetPointer();
			nItemCount = MGetBlobArrayCount(pItemListBlob);
			vShopItemList.clear();

			for (int i = 0; i < nItemCount; i++) {
				pShopInfo = (MTD_ShopItemInfo*)MGetBlobArrayElement(pItemListBlob, i);
				vShopItemList.push_back( pShopInfo );
			}

			ZApplication::GetGameInterface()->OnResponseShopItemList( vShopItemList, vGItemList );
		}
		break;

	case MC_MATCH_RESPONSE_CHARACTER_ITEMLIST:
		{
			int nBounty = 0;
			int nECoins = 0;
			MUID uidEquipItems[MMCIP_END];
			int nItemCount = 0, nEquipItemCount = 0;

			pCommand->GetParameter(&nBounty, 0, MPT_INT);
			ZGetMyInfo()->SetBP(nBounty);

			pCommand->GetParameter(&nECoins, 1, MPT_INT);
			ZGetMyInfo()->SetECoins(nECoins);

			MCommandParameter* pParam = pCommand->GetParameter(2);
			if(pParam->GetType()!=MPT_BLOB) 
			{
				_ASSERT(0);
				break;
			}
			void* pEquipItemListBlob = pParam->GetPointer();
			nEquipItemCount = MGetBlobArrayCount(pEquipItemListBlob);
			if (nEquipItemCount != MMCIP_END)
			{
				_ASSERT(0);
				break;
			}

			for (int i = 0; i < MMCIP_END; i++) {
				uidEquipItems[i] = *(MUID*)MGetBlobArrayElement(pEquipItemListBlob, i);
			}


			// 갖고 있는 아이템
			pParam = pCommand->GetParameter(3);
			void* pItemListBlob = pParam->GetPointer();
			nItemCount = MGetBlobArrayCount(pItemListBlob);
			MTD_ItemNode* pItemNodes = new MTD_ItemNode[nItemCount];

			for (int i = 0; i < nItemCount; i++)
			{
				pItemNodes[i] = *(MTD_ItemNode*)MGetBlobArrayElement(pItemListBlob, i);
			}

			// gambleitem
			pParam = pCommand->GetParameter(4);
			void* pGItemListBlob = pParam->GetPointer();
			int nGItemCount = MGetBlobArrayCount(pGItemListBlob);
			MTD_GambleItemNode* pGItemNodes = new MTD_GambleItemNode[nGItemCount];
			MTD_GambleItemNode* pTmpGItem;

			for (int i = 0; i < nGItemCount; i++)
			{
				pTmpGItem = (MTD_GambleItemNode*)MGetBlobArrayElement(pGItemListBlob, i);

				pGItemNodes[i].uidItem = pTmpGItem->uidItem;
				pGItemNodes[i].nItemID = pTmpGItem->nItemID;
				pGItemNodes[i].nItemCnt = pTmpGItem->nItemCnt;
			}

			ZApplication::GetGameInterface()->OnResponseCharacterItemList(uidEquipItems, pItemNodes, nItemCount, pGItemNodes, nGItemCount);

			delete[] pItemNodes;
			delete[] pGItemNodes;
		}
		break;
	case MC_MATCH_RESPONSE_ACCOUNT_ITEMLIST:
		{
			MCommandParameter* pParam = pCommand->GetParameter(0);
			void* pItemListBlob = pParam->GetPointer();
			int nItemCount = MGetBlobArrayCount(pItemListBlob);

			MTD_AccountItemNode* pItemNodes = new MTD_AccountItemNode[nItemCount];

			ZGetMyInfo()->GetItemList()->ClearAccountItems();

			for (int i = 0; i < nItemCount; i++)
			{
				pItemNodes[i] = *(MTD_AccountItemNode*)MGetBlobArrayElement(pItemListBlob, i);
				ZGetMyInfo()->GetItemList()->AddAccountItem(pItemNodes[i].nAIID, pItemNodes[i].nItemID, pItemNodes[i].nCount, pItemNodes[i].nRentMinutePeriodRemainder);
			}

			delete[] pItemNodes;

			ZGetMyInfo()->GetItemList()->SerializeAccountItem();
		}
		break;
	case MC_MATCH_RESPONSE_BRING_ACCOUNTITEM:
		{
			int nResult;
			pCommand->GetParameter(&nResult, 0, MPT_INT);
			if (nResult == MOK)
			{
				ZGetMyInfo()->GetItemList()->ClearAccountItems();
				ZGetMyInfo()->GetItemList()->SerializeAccountItem();

				ZPostRequestAccountItemList(ZGetGameClient()->GetPlayerUID());
				//ZApplication::GetGameInterface()->ShowMessage(MSG_GAME_BRINGITEM);
			}
			else 
			{
				ZApplication::GetGameInterface()->ShowMessage(MSG_GAME_NOTBRINGITEM);
			}			
		}
		break;

	case MC_MATCH_RESPONSE_BUY_ITEM:
		{
			int nResult;
			pCommand->GetParameter(&nResult, 0, MPT_INT);
			if (nResult == MOK)
			{
				//ZApplication::GetGameInterface()->ShowMessage(MSG_GAME_BUYITEM);
			}
			else if ((nResult == MERR_TOO_EXPENSIVE_BOUNTY) || (nResult == MERR_TOO_MANY_ITEM))
			{
				ZApplication::GetGameInterface()->ShowErrorMessage( nResult );
			}
			else
			{
				ZApplication::GetGameInterface()->ShowMessage(MSG_GAME_NOTBUYITEM);
			}
		}
		break;
	case MC_MATCH_RESPONSE_SELL_ITEM:
		{
			int nResult;
			pCommand->GetParameter(&nResult, 0, MPT_INT);
			if (nResult == MOK)
			{
				//ZApplication::GetGameInterface()->ShowMessage(MSG_GAME_SELLITEM);
			}
			else
			{
				ZApplication::GetGameInterface()->ShowErrorMessage( nResult );
			}
		}
		break;
	case MC_MATCH_RESPONSE_STAGE_JOIN:
		{
			int nResult;
			pCommand->GetParameter(&nResult, 0, MPT_INT);
			if (nResult != MOK)
			{
				ZApplication::GetGameInterface()->ShowErrorMessage( nResult );
			}
			
			ZApplication::GetGameInterface()->EnableLobbyInterface(true);

#ifdef LOCALE_NHNUSA
			GetNHNUSAReport().ReportJoinRoom();
#endif
		}
		break;
	case MC_MATCH_STAGE_REQUIRE_PASSWORD:
		{
			// MC_MATCH_RESPONSE_STAGE_FOLLOW 대신 이 커맨드가 날라올 수도 있다.
			MUID uidStage = MUID(0,0);
			char szStageName[256];
			pCommand->GetParameter(&uidStage, 0, MPT_UID);
			pCommand->GetParameter(szStageName, 1, MPT_STR, sizeof(szStageName) );

			ZRoomListBox* pRoomList;
			pRoomList = (ZRoomListBox*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "Lobby_StageList" );
			if ( pRoomList != NULL ) pRoomList->SetPrivateStageUID(uidStage);

			ZApplication::GetGameInterface()->ShowPrivateStageJoinFrame(szStageName);
		}
		break;
	case MC_MATCH_RESPONSE_STAGE_CREATE:
		{
			int nResult;
			pCommand->GetParameter(&nResult, 0, MPT_INT);
			if (nResult != MOK)
			{
				ZApplication::GetGameInterface()->ShowErrorMessage( nResult );
			}

			ZApplication::GetGameInterface()->EnableLobbyInterface(true);
		}
		break;
	case MC_MATCH_RESPONSE_MY_SIMPLE_CHARINFO:
		{
			MCommandParameter* pParam = pCommand->GetParameter(0);
			void* pMySimpleCharInfoBlob = pParam->GetPointer();

			MTD_MySimpleCharInfo* pCharInfo;
			pCharInfo = (MTD_MySimpleCharInfo*)MGetBlobArrayElement(pMySimpleCharInfoBlob, 0);

			ZGetMyInfo()->SetLevel(pCharInfo->nLevel);
			ZGetMyInfo()->SetXP(pCharInfo->nXP);
			ZGetMyInfo()->SetBP(pCharInfo->nBP);
	
			ZGetMyInfo()->Serialize();
		}
		break;
	case MC_MATCH_STAGE_RESPONSE_QUICKJOIN:
		{
			if (ZApplication::GetGameInterface()->GetState() == GUNZ_LOBBY)
			{
				int nResult;
				pCommand->GetParameter(&nResult, 0, MPT_INT);
				if (nResult != MOK)
				{
					ZApplication::GetGameInterface()->ShowErrorMessage( nResult );
				}

				MUID uidStage;
				pCommand->GetParameter(&uidStage, 1, MPT_UID);

				ZPostRequestStageJoin(ZGetGameClient()->GetPlayerUID(), uidStage);
			}
		}
		break;
#ifdef _DUELTOURNAMENT
		// 듀얼 토너먼트
	case MC_MATCH_DUELTOURNAMENT_RESPONSE_SIDERANKING_INFO:
		{
			MCommandParameter* pParam = pCommand->GetParameter(0);
			if (!pParam) { _ASSERT(0); break; }
			void* pBlob = pParam->GetPointer();
			int nCount = MGetBlobArrayCount( pBlob);
			
			_ASSERT(nCount <= NUM_DISPLAY_DUELTOURNAMENT_RANKING);

			ZIDLResource* pRes = ZApplication::GetGameInterface()->GetIDLResource();
			MWidget* pWidget = pRes->FindWidget( "Lobby_DuelTournamentRankingList" );
			if (!pWidget) { _ASSERT(0); break; }

			ZDuelTournamentRankingListBox* pRankingList = (ZDuelTournamentRankingListBox*)pWidget;
			pRankingList->ClearAll();

			for (int i=0; i<nCount; ++i)
			{
				DTRankingInfo *pRankInfo = reinterpret_cast<DTRankingInfo*>(MGetBlobArrayElement(pBlob, i));
				if (!pRankInfo) { _ASSERT(0); break; }
				
				ZDUELTOURNAMENTRANKINGITEM tempItem;
				tempItem.bEmptyItem		= false;
				tempItem.nFluctuation	= pRankInfo->m_nRankingIncrease;
				tempItem.nLosses		= pRankInfo->m_nLoses;
				tempItem.nWins			= pRankInfo->m_nWins;
				tempItem.nWinners		= pRankInfo->m_nFinalWins;
				tempItem.nPoint			= pRankInfo->m_nTP;
				tempItem.nRank			= pRankInfo->m_nRanking;
				tempItem.nGrade			= pRankInfo->m_nGrade;
				strcpy(tempItem.szCharName, pRankInfo->m_szCharName);

				// DB에서 무효값으로 10억을 사용한다, 여기서는 변동없음으로 출력
				if(tempItem.nFluctuation == 1000000000)
					tempItem.nFluctuation = 0;

				pRankingList->SetRankInfo(i, tempItem);
			}

			// 다음 순위까지 남은 포인트 출력
			int myRankIndex = -1;
			for (int i=0; i<nCount; ++i)
			{
				DTRankingInfo *pRankInfo = reinterpret_cast<DTRankingInfo*>(MGetBlobArrayElement(pBlob, i));
				if (!pRankInfo) { _ASSERT(0); break; }

				if (0 == strcmp(pRankInfo->m_szCharName, ZGetMyInfo()->GetCharName())) {
					myRankIndex = i;
					break;
				}
			}

			pRankingList->SetMyRankIndex(myRankIndex);

			DTRankingInfo *pMyRankInfo = reinterpret_cast<DTRankingInfo*>(MGetBlobArrayElement(pBlob, myRankIndex));
			DTRankingInfo *pCloseRankInfo = reinterpret_cast<DTRankingInfo*>(MGetBlobArrayElement(pBlob, myRankIndex - 1));

			// '다음 순위까지 xx포인트 남았습니다' 출력
			pWidget = pRes->FindWidget("Lobby_DuelTournamentNeedPointNextRank");
			if (pWidget)
			{
				char szNeedPointToNextRank[32] = "";

				char szBuffer[256] = "";
				if (pMyRankInfo && pCloseRankInfo)
				{
					sprintf(szNeedPointToNextRank, "%d", pCloseRankInfo->m_nTP - pMyRankInfo->m_nTP);
					ZTransMsg(szBuffer, MSG_LOBBY_DUELTOURNAMENT_NEEDPOINT_TONEXTRANK, 1, szNeedPointToNextRank);
				}
				else
				{
					// 내가 1등이라서 내 상위 랭커가 없거나, 내가 이번주에 처음 토너먼트를 하는거라 랭킹에 없을 경우
					// 이 목록이 상위 1~5등을 나타내고 있음을 설명
					ZTransMsg(szBuffer, MSG_LOBBY_DUELTOURNAMENT_NEEDPOINT_TOPSIDERANKLIST);
				}

				pWidget->SetText(szBuffer);
				((MLabel*)pWidget)->SetAlignment(MAM_RIGHT);
			}
		}
		break;
#endif //_DUELTOURNAMENT

#ifdef _QUEST_ITEM
		// ZQuest로 옮겨야 함.
	case MC_MATCH_RESPONSE_CHAR_QUEST_ITEM_LIST :
		{
			MCommandParameter*	pParam			= pCommand->GetParameter(0);
			void*				pQuestItemBlob	= pParam->GetPointer();
			int					nQuestItemCount	= MGetBlobArrayCount( pQuestItemBlob );
			MTD_QuestItemNode*	pQuestItemNode	= new MTD_QuestItemNode[ nQuestItemCount ];

			for( int i = 0; i < nQuestItemCount; ++i )
			{
				pQuestItemNode[ i ] = *(reinterpret_cast<MTD_QuestItemNode*>(MGetBlobArrayElement(pQuestItemBlob, i)));
			}

			ZApplication::GetGameInterface()->OnResponseCharacterItemList_QuestItem( pQuestItemNode, nQuestItemCount );

			delete [] pQuestItemNode;
		}
		break;

	case  MC_MATCH_RESPONSE_DROP_SACRIFICE_ITEM :
		{
			int		nResult;
			MUID	uidRequester;
			int		nSlotIndex;
			int		nItemID;

			pCommand->GetParameter( &nResult, 0, MPT_INT );
			pCommand->GetParameter( &uidRequester, 1, MPT_UID );
			// pCommand->GetParameter( &uidWasOwner, 2, MPT_UID );
			pCommand->GetParameter( &nSlotIndex, 2, MPT_INT );
			pCommand->GetParameter( &nItemID, 3, MPT_INT );

			ZApplication::GetStageInterface()->OnResponseDropSacrificeItemOnSlot( nResult, uidRequester, nSlotIndex, nItemID );
		}
		break;

	case  MC_MATCH_RESPONSE_CALLBACK_SACRIFICE_ITEM :
		{
			int		nResult;
			MUID	uidRequester;
			int		nSlotIndex;
			int		nItemID;

			pCommand->GetParameter( &nResult, 0, MPT_INT );
			pCommand->GetParameter( &uidRequester, 1, MPT_UID );
			// pCommand->GetParameter( &uidWasOwner, 2, MPT_UID );
			pCommand->GetParameter( &nSlotIndex, 2, MPT_INT );
			pCommand->GetParameter( &nItemID, 3, MPT_INT );

			ZApplication::GetStageInterface()->OnResponseCallbackSacrificeItem( nResult, uidRequester, nSlotIndex, nItemID );
		}
		break;

	case MC_MATCH_RESPONSE_BUY_QUEST_ITEM :
		{
			int nResult;
			int nBP;
            
			pCommand->GetParameter( &nResult, 0, MPT_INT );
			pCommand->GetParameter( &nBP, 1, MPT_INT );

			ZApplication::GetGameInterface()->OnResponseBuyQuestItem( nResult, nBP );
		}
		break;

	case MC_MATCH_RESPONSE_SELL_QUEST_ITEM :
		{
			int nResult;
			int nBP;
			pCommand->GetParameter( &nResult, 0, MPT_INT );
			pCommand->GetParameter( &nBP, 1, MPT_INT );

			ZApplication::GetGameInterface()->OnResponseSellQuestItem( nResult, nBP );

		}
		break;

	case MC_QUEST_RESPONSE_QL :
		{
			int nQL;
			pCommand->GetParameter( &nQL, 0, MPT_INT );

			ZApplication::GetStageInterface()->OnResponseQL( nQL );
		}
		break;

	case MC_MATCH_RESPONSE_SLOT_INFO :
		{
			MUID	uidOwner1;
			MUID	uidOwner2;
			int		nItemID1;
			int		nItemID2;

			pCommand->GetParameter( &uidOwner1, 0, MPT_UID );
			pCommand->GetParameter( &nItemID1, 1, MPT_INT );
			pCommand->GetParameter( &uidOwner2, 2, MPT_UID );
			pCommand->GetParameter( &nItemID2, 3, MPT_INT );

			ZApplication::GetStageInterface()->OnResponseSacrificeSlotInfo( uidOwner1, nItemID1, uidOwner2, nItemID2 );
		}
		break;

	case MC_GAME_START_FAIL :
		{
			int nType;
			MUID uidParam;

			pCommand->GetParameter( &nType, 0, MPT_INT );
			pCommand->GetParameter( &uidParam, 1, MPT_UID );

			ZApplication::GetStageInterface()->OnStartFail( nType, uidParam );
		}
		break;

	case MC_QUEST_STAGE_GAME_INFO :
		{
			char nQL, nMapsetID;
			unsigned int nScenarioID;
			pCommand->GetParameter( &nQL,			0, MPT_CHAR );
			pCommand->GetParameter( &nMapsetID,		1, MPT_CHAR );
			pCommand->GetParameter( &nScenarioID,	2, MPT_UINT );

			ZApplication::GetStageInterface()->OnResponseQL( nQL );
			ZApplication::GetStageInterface()->OnStageGameInfo((int)nQL, (int)nMapsetID, nScenarioID);
		}
		break;

	case MC_MATCH_VOTE_STOP :
		{
			ZApplication::GetStageInterface()->OnStopVote();
		}
		break;

#endif // _QUEST_ITEM

#ifdef _LOCATOR
	case MC_RESPONSE_SERVER_LIST_INFO :
		{
			MCommandParameter* pParam = pCommand->GetParameter(0);
			if(pParam->GetType()!=MPT_BLOB) 
				return false;

			void* pBlob = pParam->GetPointer();
			if( 0 == pBlob ) 
				return false;

			int nCount = MGetBlobArrayCount(pBlob);

			if( 0 < nCount )
				ZApplication::GetGameInterface()->OnResponseServerStatusInfoList( nCount, pBlob );
		}
		break;

	case MC_RESPONSE_BLOCK_COUNTRY_CODE_IP :
		{
			char szCountryCode[ 8 ];
			char szRoutingURL[ 65 ];
			pCommand->GetParameter( szCountryCode, 0, MPT_STR, 7 );
			pCommand->GetParameter( szRoutingURL, 1, MPT_STR, 65 );

			if( 3 > strlen(szCountryCode) )
				return false;

			ZApplication::GetGameInterface()->OnResponseBlockCountryCodeIP( szCountryCode, szRoutingURL );
		}
		break;

	case MC_RESPONSE_BLOCK_COUNTRYCODE :
		{
			int test = 0;
		}
		break;
#endif

	

	case MC_MATCH_DISCONNMSG :
		{
			DWORD dwMsgID;
			pCommand->GetParameter( &dwMsgID, 0, MPT_UINT );

			ZApplication::GetGameInterface()->OnDisconnectMsg( dwMsgID );
		}
		break;

	case MC_MATCH_CLAN_ACCOUNCE_DELETE :
		{
			char szDeleteDate[ 128 ] = {0,};
			pCommand->GetParameter( szDeleteDate, 0, MPT_STR, 128 );

			ZApplication::GetGameInterface()->OnAnnounceDeleteClan( szDeleteDate );
		}
		break;

#ifdef _GAMEGUARD
	case MC_REQUEST_GAMEGUARD_AUTH :
	case MC_REQUEST_FIRST_GAMEGUARD_AUTH :
		{
			DWORD dwIndex;
			DWORD dwValue1;
			DWORD dwValue2;
			DWORD dwValue3;

			pCommand->GetParameter( &dwIndex, 0, MPT_UINT );
			pCommand->GetParameter( &dwValue1, 1, MPT_UINT );
			pCommand->GetParameter( &dwValue2, 2, MPT_UINT );
			pCommand->GetParameter( &dwValue3, 3, MPT_UINT );

			ZApplication::GetGameInterface()->OnRequestGameguardAuth( dwIndex, dwValue1, dwValue2, dwValue3 );
		}
		break;
#endif

	case MC_RESPONSE_GAMBLEITEMLIST :
		{
			vector< MTD_DBGambleItmeNode* >	vGItemList;
			MCommandParameter*				pParam;
			void*							pGItemArray;
			DWORD							dwGItemCount;

			pParam = pCommand->GetParameter(0);
			if( MPT_BLOB != pParam->GetType() )
				break;

			pGItemArray = pParam->GetPointer();
			if( NULL == pGItemArray )
				break;

			dwGItemCount = MGetBlobArrayCount( pGItemArray );

			ZApplication::GetGameInterface()->OnSendGambleItemList( pGItemArray, dwGItemCount );
		}
		break;

	case MC_RESPONSE_RESOURCE_CRC32 :
		{
			// enter battle을 모두 처리해야 해서 여기로 함... - by SungE 2008-01-09

			_ASSERT( 0 );

			ZPostResponseResourceCRC32( 0,0 );
		}
		break;

	default :
		{
			// 정의되지 않은 커맨드 처리.
#ifdef _DEBUG
			// mlog( "ZGameInterface::OnCommand::default (%d) - 정의되지 않은 Command처리.\n", pCommand->GetID() );
			// ASSERT( 0 );
#endif
		}
		break;

	}


	return false;
}