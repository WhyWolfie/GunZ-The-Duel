Gamemode: Spymode <br>
Not Done. <br>
Add(CSCommon/SpyMode.h-cpp) <br>
Add(CSCommon/MMatchRuleSpyMode.h-cpp) <br>
Add(Gunz/MMatchRuleSpyMode.h-cpp) <br>

Open(MBaseGameType.h) <br>
Find <br>

    enum MMATCH_GAMETYPE {

Add <br>

	MMATCH_GAMETYPE_SPYMODE				=25,
  

Open(MBaseGameType.cpp) <br>
Find <br>

    _InitGameType(MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO,	MMATCH_GAMETYPE_DEATHMATCH_SOLO_STR,  1.0f,			1.0f,					0.0f);


Add <br>

    _InitGameType(MMATCH_GAMETYPE_SPYMODE, MMATCH_GAMETYPE_SPYMODE, "SpyMode", 1.0f, 1.0f, 0.0f);

Open(MMatchRule.cpp) <br>
Find <br>

    if (nLimitTime <= STAGESETTING_LIMITTIME_UNLIMITED) return false;

Add <br>

	if (GetGameType() == MMATCH_GAMETYPE_SPYMODE)
		nLimitTime = MGetSpyMode()->GetSpyMap(GetStage()->GetStageSetting()->GetMapIndex()).timeLimit * 1000;
	else
		nLimitTime = GetStage()->GetStageSetting()->GetLimitTime() * 60 * 1000;

Open(MMatchServer_Stage.cpp) <br>
Find <br>

	pObj->SetStageUID(uidStage);
	pObj->SetStageState(MOSS_NONREADY);
	pObj->SetTeam(pStage->GetRecommandedTeam());

Replace <br>

	if (pStage->GetStageSetting()->GetGameType() == MMATCH_GAMETYPE_SPYMODE)
		pObj->SetTeam(MMT_BLUE);
	else
		pObj->SetTeam(pStage->GetRecommandedTeam());

Find <br>

		CopyCharInfoForTrans(&pNode->CharInfo, pObj->GetCharInfo(), pObj);
		pNode->ExtendInfo.nPlayerFlags = pObj->GetPlayerFlags();

Add under <br>

	pNode->ExtendInfo.nPlayerFlags = pObj->GetPlayerFlags();
	if (pStage->GetStageSetting()->GetGameType() == MMATCH_GAMETYPE_SPYMODE)
	{
		pStage->PlayerTeam(uidPlayer, MMT_BLUE);
		pNode->ExtendInfo.nTeam = (char)MMT_BLUE;
	}
	else
	{
		if (pStage->GetStageSetting()->IsTeamPlay())	pNode->ExtendInfo.nTeam = (char)pObj->GetTeam();
		else											pNode->ExtendInfo.nTeam = 0;
	}

Find <br>

	if (!MGetGameTypeMgr()->IsTeamGame(pNode->nGameType))
	{
		pNode->bAutoTeamBalancing = true;
	}

Replace <br>

	if (!MGetGameTypeMgr()->IsTeamGame(pNode->nGameType))
	{
		pNode->bAutoTeamBalancing = true;
	}
	if (pNode->nGameType == MMATCH_GAMETYPE_SPYMODE)
	{
		pNode->bAutoTeamBalancing = false;
	}

Open(MMatchServer_Stage.cpp) <br>
Find <br>

    void MMatchServer::OnRequestSpawnWorldItem(const MUID& uidPlayer, const int nItemID, const float x, const float y, const float z, float fDropDelayTime)
    {
      MMatchObject* pObj = GetObject(uidPlayer);
      if (pObj == NULL) return;
      MMatchStage* pStage = FindStage(pObj->GetStageUID());
      if (pStage == NULL) return;

Add <br>

	if (pStage->GetStageSetting()->GetGameType() == MMATCH_GAMETYPE_SPYMODE)
	{
		if (nItemID != 601005)
		{
			mlog("%s is possibly hacking, UserID is %s", pObj->GetCharInfo()->m_szName, pObj->GetAccountInfo()->m_szUserID);
		}
		pStage->RequestSpawnWorldItem(pObj, nItemID, x, y, z, fDropDelayTime);
		return;
	}

Open(MMatchStage.cpp) <br>
Find <br>

	case MMATCH_GAMETYPE_DUEL:
		{
			return (new MMatchRuleDuel(this));
		}
		break;

Add <br>

	case MMATCH_GAMETYPE_SPYMODE:
	{
		return (new MMatchRuleSpyMode(this));
	}
	break;

Find <br>

    void MMatchStage::ShuffleTeamMembers()

Replace <br>

	// ·¡´õ°ÔÀÓÀÌ³ª ÆÀ°ÔÀÓÀÌ ¾Æ´Ï¸é ÇÏÁö ¾Ê´Â´Ù.
	if ((m_nStageType == MST_LADDER) || (m_StageSetting.IsTeamPlay() == false) ||
		(m_StageSetting.GetGameType() == MMATCH_GAMETYPE_SPYMODE)) return;
	if (m_ObjUIDCaches.empty()) return;

Open(ZCombatInterface.cpp) <br>
Find <br>

		// ´©Àûµ¥¹ÌÁö Àû¿ë(µà¾óÅä³Ê¸ÕÆ®ÀÏ½Ã OK½ÂÀÌ Èûµé¶§ ´©Àûµ¥¹ÌÁö·Î ÆÇÁ¤½Â Ã³¸®¿ë)
		ZGetGame()->m_pMyCharacter->EnableAccumulationDamage(true);
	}

Add <br>

	if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_SPYMODE)
	{
		pWidget = (MWidget*)ZGetGameInterface()->GetIDLResource()->FindWidget("CombatSpyInfo");
		if (pWidget)
		{
			pWidget->Show(true);
		}
	}



Find <br>

	// µ¿¿µ»ó Ä¸ÃÄ...2008.10.20
	if (ZGetGameInterface()->GetBandiCapturer() != NULL)
		ZGetGameInterface()->GetBandiCapturer()->DrawCapture(pDC);

Add <br>

	if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_SPYMODE)
	{
		((ZRuleSpyMode*)ZGetGame()->GetMatch()->GetRule())->Draw(pDC);
	}

Find <br>

		if ( ZGetGame()->GetMatch()->GetRoundState() == MMATCH_ROUNDSTATE_PLAY)				// ÇÃ·¹ÀÌ ÁßÀÌ¶ó¸é
		{
			DWORD dwTime = ZGetGame()->GetMatch()->GetRemaindTime();
			DWORD dwLimitTime = ZGetGameClient()->GetMatchStageSetting()->GetStageSetting()->nLimitTime;
			if ( dwLimitTime != 99999)
			{
				dwLimitTime *= 60000;
				if ( dwTime <= dwLimitTime)
				{
					dwTime = (dwLimitTime - dwTime) / 1000;
					sprintf( szText, "%s : %d:%02d", ZMsg( MSG_WORD_REMAINTIME), (dwTime / 60), (dwTime % 60));
				}
				else
					sprintf( szText, "%s :", ZMsg( MSG_WORD_REMAINTIME));
			}
			else
				sprintf( szText, "%s : ---", ZMsg( MSG_WORD_REMAINTIME));
		}




Replace <br>

		if ( ZGetGame()->GetMatch()->GetRoundState() == MMATCH_ROUNDSTATE_PLAY)				// ÇÃ·¹ÀÌ ÁßÀÌ¶ó¸é
		{
			DWORD dwTime = ZGetGame()->GetMatch()->GetRemaindTime();
			DWORD dwLimitTime = ZGetGameClient()->GetMatchStageSetting()->GetStageSetting()->nLimitTime;
			if ( dwLimitTime != 99999)
			{
				if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_SPYMODE)
				{
					dwLimitTime *= 1000;
					if (dwTime <= dwLimitTime)
					{
						dwTime = (dwLimitTime - dwTime);
						sprintf(szText, "%s : %d:%02d", ZMsg(MSG_WORD_REMAINTIME), (dwTime / 1000) / 60, (dwTime /1000) % 60);
					}
					else
						sprintf(szText, "%s :", ZMsg(MSG_WORD_REMAINTIME));
				}
				else
				{
					dwLimitTime *= 60000;

					if (dwTime <= dwLimitTime)
					{
						dwTime = (dwLimitTime - dwTime) / 1000;
						sprintf(szText, "%s : %d:%02d", ZMsg(MSG_WORD_REMAINTIME), (dwTime / 60), (dwTime % 60));
					}
					else
						sprintf(szText, "%s :", ZMsg(MSG_WORD_REMAINTIME));
				}
			}
			else
				sprintf( szText, "%s : ---", ZMsg( MSG_WORD_REMAINTIME));
		}



Find <br>

	else
	{
		x = ITEM_XPOS[2] - .01f;	// Exp
		TextRelative(pDC,x,y, ZMsg(MSG_WORD_EXP));
	}


Add <br>

	else
	{
		x = ITEM_XPOS[2] - .01f;	// Exp
		if (ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_SPYMODE)
		TextRelative(pDC, x, y, ZMsg(MSG_WORD_EXP));
		else
			TextRelative(pDC, x, y, "Score");
	}



Find <br>

		if (ZGetGameTypeManager()->IsQuestDerived(ZGetGame()->GetMatch()->GetMatchType()))
			pItem->nExp = pCharacter->GetStatus().Ref().nKills * 100;
		else
			pItem->nExp = pCharacter->GetStatus().Ref().nExp;


Add <br>

		if (ZGetGameTypeManager()->IsQuestDerived(ZGetGame()->GetMatch()->GetMatchType()))
			pItem->nExp = pCharacter->GetStatus().Ref().nKills * 100;
		else if (ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_SPYMODE)
			pItem->nExp = pCharacter->GetStatus().Ref().nExp;


Find <br>

	else if ( ZGetGameTypeManager()->IsSurvivalOnly(ZGetGame()->GetMatch()->GetMatchType()))	// ¼­¹ÙÀÌ¹úÀÌ¸é...
	{



Add <br>

	else if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_SPYMODE)
	{
		strcpy_s(szFileName, "interface/loadable/rstbg_deathmatch.jpg");

		pWidget = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("SpyResult");
		if (pWidget)
			pWidget->Show(true);

		MPicture* finishPics = (MPicture*)ZGetGameInterface()->GetIDLResource()->FindWidget("SpyResult_Finish");
		if (finishPics)
			finishPics->Show(true);

		MPicture* finishHeader = (MPicture*)ZGetGameInterface()->GetIDLResource()->FindWidget("SpyResult_Finish");
		if (finishHeader)
			finishHeader->Show(true);

		MLabel* label = (MLabel*)ZGetGameInterface()->GetIDLResource()->FindWidget("SpyResult_PlayerNameListLabel");
		if (label)
			label->Show(true);

		label = (MLabel*)ZGetGameInterface()->GetIDLResource()->FindWidget("SpyResult_PlayerScoreListLabel");
		if (label)
			label->Show(true);
	}

Open(ZGame.cpp) <br>
Find <br>

	if (ZGetGameTypeManager()->IsTeamExtremeGame(GetMatch()->GetMatchType()))
		pCharacter->SetInvincibleTime( 5000);

Replace <br>

	if (ZGetGameTypeManager()->IsTeamExtremeGame(GetMatch()->GetMatchType()) || GetMatch()->GetMatchType() == MMATCH_GAMETYPE_SPYMODE)
		pCharacter->SetInvincibleTime(5000);

Find <br>

	else if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_DUELTOURNAMENT)
	{


Add <br>

	else if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_SPYMODE) {
		ZRuleSpyMode* pRule = dynamic_cast<ZRuleSpyMode*>(ZGetGame()->GetMatch()->GetRule());

		size_t Count = pRule->GetSpies().size();
		nWritten = zfwrite(&Count, sizeof(int), 1, m_pReplayFile);
		if (nWritten == 0)
			goto RECORDING_FAIL;

		nWritten = zfwrite(&pRule->GetSpies(), sizeof(MUID),Count, m_pReplayFile);
		if (nWritten == 0)
			goto RECORDING_FAIL;

		size_t spyItemCount = pRule->GetSpyItems().size();
		nWritten = zfwrite(&spyItemCount, sizeof(int), 1, m_pReplayFile);
		if (nWritten == 0)
			goto RECORDING_FAIL;

		nWritten = zfwrite(&pRule->GetSpyItems(), sizeof(MTD_SpyItems), spyItemCount, m_pReplayFile);
		if (nWritten == 0)
			goto RECORDING_FAIL;
	}

Find <br>

    void ZGame::OnResetTeamMembers(MCommand* pCommand)
    {
      if (!m_Match.IsTeamPlay()) return;

Add <br>

	if (ZGetGame()->GetMatch()->GetMatchType() != MMATCH_GAMETYPE_SPYMODE)
	{
		ZChatOutput(MCOLOR(ZCOLOR_GAME_INFO), ZMsg(MSG_GAME_MAKE_AUTO_BALANCED_TEAM));
	}

Open(ZGameInterface.cpp) <br>
Find <br>

    void ZGameInterface::UpdateBlueRedTeam( void)
    {
      MButton* pBlueTeamBtn  = (MButton*)m_IDLResource.FindWidget("StageTeamBlue");
      MButton* pBlueTeamBtn2 = (MButton*)m_IDLResource.FindWidget("StageTeamBlue2");
      MButton* pRedTeamBtn  = (MButton*)m_IDLResource.FindWidget("StageTeamRed");
      MButton* pRedTeamBtn2 = (MButton*)m_IDLResource.FindWidget("StageTeamRed2");
      if ((pRedTeamBtn == NULL) || (pBlueTeamBtn == NULL) || (pRedTeamBtn2 == NULL) || (pBlueTeamBtn2 == NULL))
        return;

Add <br>

	if (GetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_SPYMODE)
	{
		pRedTeamBtn->Show(false);
		pRedTeamBtn2->Show(false);
		pBlueTeamBtn->Show(false);
		pBlueTeamBtn2->Show(false);
		return;
	}

Open(ZInitialLoading.cpp) <br>
Find <br>

    extern MFontR2*		g_pDefFont;
    extern MDrawContextR2* g_pDC;
    void	ZInitialLoading::DrawTips()
    {
    //	return;			// ÇöÀç Àû¿ë¾ÈµÊ

      const float fTipYRatio = 0.83f;

Replace <br>

    extern MFontR2*		g_pDefFont;
    extern MDrawContextR2* g_pDC;
    void	ZInitialLoading::DrawTips()
    {
    //	return;			// ÇöÀEÀû¿EÈµÊ

      if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_SPYMODE)
        return;

      const float fTipYRatio = 0.83f;


Open(ZInterfaceListener.cpp) <br>
Find <br>

    class MGameStartListener : public MListener{

Replace <br>

    class MGameStartListener : public MListener{
    public:
      virtual bool OnCommand(MWidget* pWidget, const char* szMessage){
        if(MWidget::IsMsg(szMessage, MBTN_CLK_MSG)==true){

          const MSTAGE_SETTING_NODE* pStageSetting = ZGetGameClient()->GetMatchStageSetting()->GetStageSetting();
          int nPlayerCnt = (int)ZGetGameClient()->GetMatchStageSetting()->m_CharSettingList.size();
          if(nPlayerCnt > pStageSetting->nMaxPlayers && nPlayerCnt!=0 && pStageSetting->nMaxPlayers!=0)
          {
            // ÃÖ´ëÀÎ¿øº¸´Ù ¹æÀÎ¿øÀÌ ¸¹À»½Ã Ã³¸®
            char szText[128] = {0,};
            sprintf(szText, "%s\n", ZErrStr(MERR_PERSONNEL_TOO_MUCH));
            ZGetGameInterface()->ShowMessage(szText);
            return false;
          }

          // ¸Ê µî·ÏÀÌ ¾ÈµÇ¾î ÀÖÀ¸¸é °ÔÀÓ ½ÃÀÛÀº ÇØÁÖÁö ¾Ê´Â´Ù.
          if(!ZApplication::GetStageInterface()->GetIsRelayMapRegisterComplete())
          {
            ZGetGameInterface()->ShowMessage(MSG_GAME_RELAYMAP_CONFIRM_BUTTON_PUSH);
            return true;
          }

          // ¸ÊÀÌ °ñ¶óÁ³À»¶§ ½ÃÀÛ °¡´É.
          if (ZGetGameClient()->GetMatchStageSetting()->GetGameType() == MMATCH_GAMETYPE_SPYMODE)
          {
            ZPostStageStartSpy(ZGetGameClient()->GetPlayerUID(), ZGetGameClient()->GetStageUID());
            return true;
          }
          else
          {
            if (ZGetGameClient()->GetMatchStageSetting()->GetMapName()[0] != 0)
            {
              ZApplication::GetStageInterface()->ChangeStageEnableReady(true);

              ZPostStageStart(ZGetGameClient()->GetPlayerUID(), ZGetGameClient()->GetStageUID());
            }
            else
            {
              ZGetGameInterface()->ShowMessage("¼±ÅÃÇÏ½Å ¸ÊÀÌ ¾ø½À´Ï´Ù. ¸ÊÀ» ¼±ÅÃÇØ ÁÖ¼¼¿ä.");
            }
          }

          return true;
        }
        return false;
      }
    };
    MGameStartListener	g_GameStartListener;

Open(ZMatch.h) <br>
Find <br>

    inline ZRule* ZMatch::GetRule() 
    { 
      return m_pRule; 
    }

Add <br>

    inline bool ZMatch::isSpecialTeamsGame()
    {
      return ((GetMatchType() == MMATCH_GAMETYPE_SPYMODE));
    }

Open(ZReplay.cpp) <br>
Find <br>

	if(m_StageSetting.nGameType==MMATCH_GAMETYPE_DUELTOURNAMENT)
	{

Add <br>

	if (m_StageSetting.nGameType == MMATCH_GAMETYPE_SPYMODE)
	{
		ZRuleSpyMode* pRule = dynamic_cast<ZRuleSpyMode*>(ZGetGame()->GetMatch()->GetRule());

		int spyCount = 0;

		int	Read = zfread(&spyCount, sizeof(int), 1, file);
		if (Read == 0)
			return false;

		vector<MUID> Spies = {};
		MUID Spy;
		for (int i = 0; i < spyCount; ++i)
		{
			Read = zfread(&Spy, sizeof(MUID), 1, file);
			if (Read == 0)
				mlog("error reading spies\n");

			Spies.push_back(Spy);
		}
		pRule->SetSpies(Spies);

		int spyItemCount = 0;
		Read = zfread(&spyItemCount, sizeof(int), 1, file);
		if (Read == 0)
			return false;

		vector<MTD_SpyItems> spyItems = {};
		MTD_SpyItems item;
		for (int i = 0; i < spyItemCount; ++i)
		{
			Read = zfread(&item, sizeof(MTD_SpyItems), 1, file);
			spyItems.push_back(item);
		}

		pRule->SetSpyItems(spyItems);

	}

Find <br>

	if(IsGameRuleCTF(m_StageSetting.nGameType))
	{

Add <br>

	if (m_StageSetting.nGameType == MMATCH_GAMETYPE_SPYMODE)
	{
		ZRuleSpyMode* pRule = dynamic_cast<ZRuleSpyMode*>(ZGetGame()->GetMatch()->GetRule());

		int spyCount = 0;

		int	Read = zfread(&spyCount, sizeof(int), 1, file);
		if (Read == 0)
			return false;

		vector<MUID> Spies = {};
		MUID Spy;
		for (int i = 0; i < spyCount; ++i)
		{
			Read = zfread(&Spy, sizeof(MUID), 1, file);
			if (Read == 0)
				mlog("error reading spies\n");

			Spies.push_back(Spy);
		}
		pRule->SetSpies(Spies);

		int spyItemCount = 0;
		Read = zfread(&spyItemCount, sizeof(int), 1, file);
		if (Read == 0)
			return false;

		vector<MTD_SpyItems> spyItems = {};
		MTD_SpyItems item;
		for (int i = 0; i < spyItemCount; ++i)
		{
			Read = zfread(&item, sizeof(MTD_SpyItems), 1, file);
			spyItems.push_back(item);
		}

		pRule->SetSpyItems(spyItems);

	}

Open(ZRule.cpp) <br>
Find <br>

	case MMATCH_GAMETYPE_DUELTOURNAMENT:
		{
			return (new ZRuleDuelTournament(pMatch));
		}
		break;

Add <br>

	case MMATCH_GAMETYPE_SPYMODE:
	{
		return (new ZRuleSpyMode(pMatch));
	}
	break;

Open(ZStageInterface.cpp) <br>
Find <br>

		ZApplication::GetGameInterface()->EnableWidget( "StageSettingCaller",		false);
		ZApplication::GetGameInterface()->EnableWidget( "Stage_RelayMap_OK_Button", false);
		ZApplication::GetGameInterface()->EnableWidget( "Stage_RelayMapType",		false);
		ZApplication::GetGameInterface()->EnableWidget( "Stage_RelayMapRepeatCount", false);
	}

Replace <br>

		ZApplication::GetGameInterface()->EnableWidget( "StageSettingCaller",		false);
		ZApplication::GetGameInterface()->EnableWidget( "Stage_RelayMap_OK_Button", false);
		ZApplication::GetGameInterface()->EnableWidget( "Stage_RelayMapType",		false);
		ZApplication::GetGameInterface()->EnableWidget( "Stage_RelayMapRepeatCount", false);
	}
	if (ZGetGameClient()->GetMatchStageSetting()->GetStageSetting()->nGameType == MMATCH_GAMETYPE_SPYMODE)
	{
		ZApplication::GetGameInterface()->EnableWidget("MapSelection", false);		// ¸Ê¼±ÅÃ ÄÞº¸¹Ú½º
		ZApplication::GetGameInterface()->EnableWidget("StageMaxPlayer", false);		// ÃÖ´ëÀÎ¿ø ÄÞº¸¹Ú½º

	}

Find <br>

		case MMATCH_GAMETYPE_DEATHMATCH_TEAM:
		case MMATCH_GAMETYPE_DEATHMATCH_TEAM2:
		case MMATCH_GAMETYPE_CTF:
			color = TDM_COLOR;
			break;

Add <br>

		case MMATCH_GAMETYPE_DEATHMATCH_TEAM:
		case MMATCH_GAMETYPE_DEATHMATCH_TEAM2:
		case MMATCH_GAMETYPE_SPYMODE:
		case MMATCH_GAMETYPE_CTF:
			color = TDM_COLOR;
			break;


Find <br>

	else if ( pSetting->nGameType == MMATCH_GAMETYPE_QUEST)						// Äù½ºÆ® ¸ðµåÀÌ¸é...
	{
		// ¸Ê ÀÌ¸§ ¹è°æ ÀÌ¹ÌÁö º¯È¯
		if ( pAniMapImg)
			pAniMapImg->SetCurrentFrame( 2);

		// Äù½ºÆ® UI º¸ÀÓ
		bQuestUI = true;
	}



Add <br>

	else if (pSetting->nGameType == MMATCH_GAMETYPE_SPYMODE)
	{
		if (pAniMapImg)
			pAniMapImg->SetCurrentFrame(4);
		bQuestUI = false;
		bChallengeQuestUI = false;
	}

Find <br>

	// ¸Ê¼±ÅÃ½Ã ¸±·¹ÀÌ¸ÊÀÌ¸é ¸±·¹ÀÌ¸Ê ¸®½ºÆ® ¹Ú½º¸¦ ¿­¾îÁØ´Ù.
	 if(pSetting->bIsRelayMap)
		OpenRelayMapBox();
	else
		HideRelayMapBox();

Add <br>

	 if (pSetting->nGameType == MMATCH_GAMETYPE_SPYMODE)
		 OpenSpyBanBox();
	 else
		 HideSpyBanBox();

Find <br>

	MComboBox* pMapCombo = (MComboBox*)pResource->FindWidget( "MapSelection");
	if ( pMapCombo)
	{

Replace <br>

      MComboBox* pMapCombo = (MComboBox*)pResource->FindWidget( "MapSelection");
      if ( pMapCombo)
      {
        // ÀÏ´Ü ÀÓ½Ã ÇÏµåÄÚµù(¿ì¿¡¿¨~ ¤Ð.¤Ð)
    //		if ( m_nGameType == MMATCH_GAMETYPE_QUEST)
    //			pMapCombo->SetText( "Mansion");
    //		else
        if (m_nGameType == MMATCH_GAMETYPE_SPYMODE)
          pMapCombo->SetText("Random Map");
        else
          pMapCombo->SetText(szMapName);
      }

Open(ZWeapon.cpp) <br>
Find <br>

    bool ZWeaponFlashBang::Update( float fElapsedTime )
    {
      rvector oldPos = m_Position;

      float lap	= ZGetGame()->GetTime() - m_fStartTime;

      if( lap >= FLASHBANG_LIFE )
      {
        Explosion();
        return false;
      }


Replace <br>

    bool ZWeaponFlashBang::Update( float fElapsedTime )
    {
      rvector oldPos = m_Position;

      float lap	= ZGetGame()->GetTime() - m_fStartTime;

      if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_SPYMODE)
      {
        if (mbLand) {
          Explosion();
          return false;
        }
      }

      if( lap >= FLASHBANG_LIFE )
      {
        Explosion();
        return false;
      }

Add(CSCommon/SpyMode.h-cpp)

Open(MMatchTransDataType.h) <br>
Find <br>

    #include "MMatchObject.h"
    #include "MMatchRule.h"		// MMATCH_GAMETYPE, MMATCH_ROUNDSTATE, MMATCH_ROUNDRESULT ÂüÁ¶ -> Á¤¸®¿ä¸Á
    #include "MMatchStageSetting.h"
    #include "MMatchGameType.h"
    #include "MMatchGlobal.h"

    #pragma pack(push, old)
    #pragma pack(1)

Add <br>

    struct MTD_SpyItems {
      UINT id;
      int count;
      char desc[8];
    };

Open(MMatchRule.cpp) <br>
Find <br>

    #include "MMatchConfig.h"
    #include "MMatchEventFactory.h"

Add <br>

    #include "SpyMode.h"

Open(MSharedCommandTable.h) <br>
Find <br>

    #define MC_LOCAL_UPDATE_CUSTOM_IP				50008
    #define MC_LOCAL_UPDATE_ACCEPT_INVALID_IP		50009


Add <br>


    //Spymode
    #define MC_MATCH_SPY_INFO					60051
    #define MC_MATCH_SPY_TEAMS					60052
    #define MC_MATCH_STAGE_START_SPY			60053
    #define MC_MATCH_SPY_BONUS					60054
    #define MC_MATCH_SPY_ROUNDREWARD			60055

Open(MSharedCommandTable.cpp) <br>
Find <br>

	C( MC_MATCH_RESPONSE_BUY_QUEST_ITEM, "Quest item", "Response buy quest item", MCDT_MACHINE2MACHINE )
		P( MPT_INT, "Result" )
		P( MPT_INT, "Player Bounty" )

Add <br>

	//spymode
	C(MC_MATCH_STAGE_START_SPY,"","",MCDT_MACHINE2MACHINE)
		P(MPT_UID,"player")
		P(MPT_UID,"stage")

	C(MC_MATCH_SPY_ROUNDREWARD,"","",MCDT_MACHINE2MACHINE)
		P(MPT_UID,"targetPlayer")
		P(MPT_UCHAR,"scoreValue")

	C(MC_MATCH_SPY_TEAMS, "", "", MCDT_MACHINE2MACHINE)
		P(MPT_BLOB, "teamBlob")
		P(MPT_INT, "hpap")
	C(MC_MATCH_SPY_INFO, "", "", MCDT_MACHINE2MACHINE)
		P(MPT_BLOB, "weapons")

Open(ZCommandUDPHackShield.cpp) <br>
Find <br>

    AddDeniedCommand(MC_MATCH_REQUEST_SLOT_INFO);

Add <br>

	AddDeniedCommand(MC_MATCH_SPY_INFO);
	AddDeniedCommand(MC_MATCH_SPY_TEAMS);
	AddDeniedCommand(MC_MATCH_SPY_BONUS);
	AddDeniedCommand(MC_MATCH_SPY_ROUNDREWARD);

Open(ZGame.cpp) <br>
Find <br>

	switch (pCommand->GetID())
	{
	case MC_MATCH_ASSIGN_COMMANDER:
	case MC_MATCH_ASSIGN_BERSERKER:
	case MC_MATCH_FLAG_EFFECT:


Add <br>

	case MC_MATCH_SPY_ROUNDREWARD:

Open(MMatchStage.cpp) <br>
Find <br>

    #include "MMatchRuleDuel.h"
    #include "MMatchRuleDuelTournament.h"
    #include "MMatchCRC32XORCache.h"

Add <br>

    #include "MMatchRuleSpyMode.h"

Open(MMatchRule.h) <br>
Find <br>

    virtual void OnRoundCountdown();

Replace <br>

    virtual void OnRoundCountDown();

Open(MMatchRule.cpp) <br>
Find <br>

    void MMatchRule::OnRoundCountdown()
    {

    }

Replace <br>

    void MMatchRule::OnRoundCountDown()
    {

    }

Find <br>

	if (nState == MMATCH_ROUNDSTATE_FINISH)	OnRoundEnd();
	else if (nState == MMATCH_ROUNDSTATE_PLAY) OnRoundBegin();
	else if (nState == MMATCH_ROUNDSTATE_COUNTDOWN) OnRoundCountdown();


Replace <br>

	if (nState == MMATCH_ROUNDSTATE_FINISH)	OnRoundEnd();
	else if (nState == MMATCH_ROUNDSTATE_PLAY) OnRoundBegin();
	else if (nState == MMATCH_ROUNDSTATE_COUNTDOWN) OnRoundCountDown();

Open(ZCombatInterface.cpp) <br>
Find <br>

    #include "ZRuleDuel.h"
    #include "ZRuleDuelTournament.h"
    #include "ZInput.h"

Add <br>

    #include "ZRuleSpy.h"
    #include "ZRuleSpyMode.h"

Open(ZGame.cpp) <br>
Find <br>

    #include "ZRuleDuel.h"
    #include "ZRuleDeathMatch.h"
    #include "ZMyCharacter.h"
    #include "MMatchCRC32XORCache.h"
    #include "MMatchObjCache.h"

Add <br>

    #include "ZRuleSpy.h"
    #include "ZRuleSpyMode.h"

Open(ZReplay.cpp) <br>
Find <br>

    #include "ZRuleDuel.h"
    #include "ZRuleDuelTournament.h"
    #include "ZRuleDeathMatch.h"
    #include "ZWorldItem.h"

Add <br>

    #include "ZRuleSpyMode.h"

Open(ZInterfaceListener.cpp) <br>
Find <br>

    BEGIN_IMPLEMENT_LISTENER( ZGetRelayMapOKButtonListener, MBTN_CLK_MSG)
      ZApplication::GetStageInterface()->PostRelayMapInfoUpdate();
    END_IMPLEMENT_LISTENER();

Add <br>

    BEGIN_IMPLEMENT_LISTENER(ZGetSpyBanMapBoxOpen, MBTN_CLK_MSG)
      ZApplication::GetStageInterface()->OpenSpyBanBox();
    END_IMPLEMENT_LISTENER();

    BEGIN_IMPLEMENT_LISTENER(ZGetSpyBanMapBoxClose, MBTN_CLK_MSG)
      ZApplication::GetStageInterface()->CLoseSpyBanBox();
    END_IMPLEMENT_LISTENER();


Find <br>

    void ZStageInterface::SetRelayMapBoxPos( int nBoxPos)

Add <br>

    //Custom: spymode
    // ¸±·¹ÀÌ¸Ê ÀÎÅÍÆäÀÌ½º
    /***********************************************************************
    OpenRelayMapBox : public

    desc : ¸±·¹ÀÌ¸Ê ¼±ÅÃ Ã¢ ¿­±â
    arg  : none
    ret  : none
    ************************************************************************/
    void ZStageInterface::OpenSpyBanBox(void)
    {
      ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();

      MButton* pButton = (MButton*)pResource->FindWidget("Stage_SpyBanMapBoxOpen");
      if (pButton)
        pButton->Show(false);
      pButton = (MButton*)pResource->FindWidget("Stage_SpyBanMapBoxClose");
      if (pButton)
        pButton->Show(true);

      SetSpyBanBoxPos(2);

      ///TODO: create spymaps 
      // ¸®ÇÃ·¹ÀÌ ¹Ú½º¿¡ ¸Ê¸®½ºÆ®¸¦ »ý¼º
      //ZApplication::GetStageInterface()->RelayMapCreateMapList();
      CreateSpyBanMapList();
    }

    /***********************************************************************
    CloseRelayMapBox : public

    desc : ¸±·¹ÀÌ¸Ê ¼±ÅÃ Ã¢ ´Ý±â
    arg  : none
    ret  : none
    ************************************************************************/
    void ZStageInterface::CLoseSpyBanBox(void)
    {
      ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();

      MButton* pButton = (MButton*)pResource->FindWidget("Stage_SpyBanMapBoxClose");
      if (pButton)
        pButton->Show(false);
      pButton = (MButton*)pResource->FindWidget("Stage_SpyBanMapBoxOpen");
      if (pButton)
        pButton->Show(true);

      MWidget* pWidget = pResource->FindWidget("Stage_CharacterInfo");
      if (pWidget)
        pWidget->Enable(true);

      SetSpyBanBoxPos(1);
    }

    /***********************************************************************
    HideRelayMapBox : public

    desc : ¸±·¹ÀÌ¸Ê ¼±ÅÃ Ã¢ °¨Ãß±â
    arg  : none
    ret  : none
    ************************************************************************/
    void ZStageInterface::HideSpyBanBox(void)
    {
      ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();

      MButton* pButton = (MButton*)pResource->FindWidget("Stage_SpyBanMapBoxClose");
      if (pButton)
        pButton->Show(false);
      pButton = (MButton*)pResource->FindWidget("Stage_SpyBanMapBoxOpen");
      if (pButton)
        pButton->Show(true);

      MWidget* pWidget = pResource->FindWidget("Stage_CharacterInfo");
      if (pWidget)
        pWidget->Enable(true);

      SetSpyBanBoxPos(0);
    }

    /***********************************************************************
    GetRelayMapBoxPos : public

    desc : ¸±·¹ÀÌ¸Ê ¼±ÅÃ Ã¢ À§Ä¡ ±¸ÇÏ±â
    arg  : none
    ret  : none
    ************************************************************************/
    void ZStageInterface::SetSpyBanBoxPos(int nBoxPos)
    {
      MWidget* pWidget = ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Stage_SpyBanMapListView");
      if (pWidget)
      {
        MRECT rect;

        switch (nBoxPos)
        {
        case 0:		// Hide
          rect = pWidget->GetRect();
          m_spyMapListFramePos = -rect.w;
          break;

        case 1:		// Close
          rect = pWidget->GetRect();
          m_spyMapListFramePos = -rect.w + (rect.w * 0.14);
          break;

        case 2:		// Open
          m_spyMapListFramePos = 0;
          break;
        }
      }
    }

Open(ZStageInterface.h) <br>
Find <br>

	void SetEnableWidgetByRelayMap(bool b);
	void SetStageRelayMapImage();
  
Add <br>

	void OpenSpyBanBox(void);
	void CLoseSpyBanBox(void);
	void HideSpyBanBox(void);
	void SetSpyBanBoxPos(int nBoxPos);
	void CreateSpyBanMapList(void);

Open(ZRule.cpp) <br>
Find <br>

    #include "ZRuleBerserker.h"
    #include "ZRuleDuel.h"
    #include "ZRuleDuelTournament.h"

Add <br>

    #include "ZRuleSpy.h"
    #include "ZRuleSpyMode.h"

Open(ZPost.h) <br>
Find <br>

    inline void ZPostStageStart(const MUID& uidChar, const MUID& uidStage)
    {
      ZPOSTCMD3(MC_MATCH_STAGE_START, MCommandParameterUID(uidChar), MCommandParameterUID(uidStage), MCommandParameterInt(3));
    }

Add <br>

    inline void ZPostStageStartSpy(const MUID& uidChar, const MUID& uidStage)
    {
      ZPOSTCMD2(MC_MATCH_STAGE_START_SPY, MCmdParamUID(uidChar), MCmdParamUID(uidStage));
    }

Open(MMatchServer_OnCommand.cpp) <br>
Find <br>

		case MC_MATCH_STAGE_START:
			{
				MUID uidPlayer, uidStage;
				int nCountdown;
				uidPlayer = pCommand->GetSenderUID();

				//pCommand->GetParameter(&uidPlayer, 0, MPT_UID);
				pCommand->GetParameter(&uidStage, 1, MPT_UID);
				pCommand->GetParameter(&nCountdown, 2, MPT_INT);

				OnStageStart(uidPlayer, uidStage, nCountdown);
			}
			break;

Add <br>

		case MC_MATCH_STAGE_START_SPY:
		{
			MUID uidPlayer, uidStage;
			pCommand->GetParameter(&uidPlayer, 0, MPT_UID);
			pCommand->GetParameter(&uidStage, 1, MPT_UID);
			OnStageStartSpy(uidPlayer, uidStage);
		}break;

Open(MMatchServer.h) <br>
Find <br>

    void OnStageRelayStart(const MUID& uidStage);

Add <br>

	void OnStageStartSpy(const MUID& uidPlayer, const MUID& uidStage);

Open(MMatchServer_Stage.cpp) <br>
Find <br>

    void MMatchServer::OnStageRelayStart(const MUID& uidStage)

Add <br>

    void MMatchServer::OnStageStartSpy(const MUID& uidPlayer, const MUID& uidStage)
    {
      MMatchStage* pStage = FindStage(uidStage);
      if (!pStage)
        return;

      if (pStage->GetMasterUID() != uidPlayer)
        return;

      vector<SpyMap> mapList = {};
      int playerCount = pStage->GetPlayers();
      for (auto Obj : MGetSpyMode()->GetSpyMapList())
      {
        if (playerCount >= Obj.minPlayers && playerCount <= Obj.maxPlayers)
          mapList.push_back(Obj);
      }
      //a size of 0 means either too many players, or not enough players
      if (mapList.size() == 0)
      {
        MCommand* pCmd = MGetMatchServer()->CreateCommand(MC_MATCH_ANNOUNCE, MUID(0, 0));
        pCmd->AddParameter(new MCmdParamUInt(0));
        pCmd->AddParameter(new MCmdParamStr("Unable to start game, no maps are available."));
        MGetMatchServer()->RouteToStage(pStage->GetUID(), pCmd);
        return;
      }
      auto map = mapList.begin();
      std::advance(map, rand() % mapList.size());

      pStage->GetStageSetting()->SetMapIndex(map->id);
      pStage->GetStageSetting()->SetLimitTime(map->timeLimit * 1000);
      pStage->GetStageSetting()->SetMapName(map->name);

      if (pStage->StartGame(MGetServerConfig()->IsUseResourceCRC32CacheCheck()) == true) {
        MCommand* pNew = new MCommand(m_CommandManager.GetCommandDescByID(MC_MATCH_STAGE_START), MUID(0, 0), m_This);
        pNew->AddParameter(new MCommandParameterUID(uidPlayer));
        pNew->AddParameter(new MCommandParameterUID(uidStage));
        pNew->AddParameter(new MCommandParameterInt(3));
        RouteToStage(uidStage, pNew);

        SaveGameLog(uidStage);
      }
    }

Find <br>

    #include "MMatchRuleQuest.h"
    #include "MMatchRuleBerserker.h"
    #include "MMatchRuleDuel.h"
    #include "MCrashDump.h"

Add <br>

    #include "SpyMode.h"


Open(ZStageInterface.h) <br>
Find <br>

    int				m_nRelayMapListFramePos;

Add <br>

	int				m_spyMapListFramePos;

Open(ZGameInterface.cpp) <br>
Find <br>

		// ¸±·¹ÀÌ¸Ê ¸®½ºÆ® ÇÁ·¹ÀÓ ¿òÁ÷ÀÓ
		pWidget = pRes->FindWidget("Stage_RelayMapListView");
		if (!pWidget)
			return;

Add <br>

        //spymode
        pWidget = pRes->FindWidget("Stage_SpyBanMapListView");
        if (!pWidget)
          return;

        nEndPos = ZApplication::GetStageInterface()->m_spyMapListFramePos;
        rect = pWidget->GetRect();
        if (rect.x != nEndPos)
        {
          int nNewPos = rect.x + (nEndPos - rect.x) * 0.25;
          if (nNewPos == rect.x)		// not changed
            rect.x = nEndPos;
          else						// changed
            rect.x = nNewPos;

          pWidget->SetBounds(rect);

          if (rect.x == 0)
          {
            pWidget = pRes->FindWidget("Stage_CharacterInfo");
            if (pWidget)
              pWidget->Enable(false);
          }
        }

      }
    }







