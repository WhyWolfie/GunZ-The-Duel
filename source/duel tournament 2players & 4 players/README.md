Open(ZInterfaceListener.cpp) <br>
Find <br>

    #ifdef _PUBLISH
      ZPostDuelTournamentRequestCancelGame( ZGetMyUID(), MDUELTOURNAMENTTYPE_QUATERFINAL);
    #else
      switch (g_lastPressedDuelTournamentGameBtn) {
        case 2 : ZPostDuelTournamentRequestCancelGame( ZGetMyUID(), MDUELTOURNAMENTTYPE_FINAL); break;
        case 4 : ZPostDuelTournamentRequestCancelGame( ZGetMyUID(), MDUELTOURNAMENTTYPE_SEMIFINAL); break;
        default : ZPostDuelTournamentRequestCancelGame( ZGetMyUID(), MDUELTOURNAMENTTYPE_QUATERFINAL); break;
      }
    #endif
    
Change <br>

    //#ifdef _PUBLISH
      ZPostDuelTournamentRequestCancelGame( ZGetMyUID(), MDUELTOURNAMENTTYPE_QUATERFINAL);
    //#else
      switch (g_lastPressedDuelTournamentGameBtn) {
        case 2 : ZPostDuelTournamentRequestCancelGame( ZGetMyUID(), MDUELTOURNAMENTTYPE_FINAL); break;
        case 4 : ZPostDuelTournamentRequestCancelGame( ZGetMyUID(), MDUELTOURNAMENTTYPE_SEMIFINAL); break;
        default : ZPostDuelTournamentRequestCancelGame( ZGetMyUID(), MDUELTOURNAMENTTYPE_QUATERFINAL); break;
      }
    //#endif
  
Open(ZGameInterface.cpp) <br>
Find: <br>

    #ifdef _PUBLISH
      pWidget= m_IDLResource.FindWidget( "DuelTournamentGame_2Test" );
      if(pWidget) pWidget->Show(false);
      pWidget= m_IDLResource.FindWidget( "DuelTournamentGame_4Test" );
      if(pWidget) pWidget->Show(false);
    #else	// 테스트용 2,4인 듀얼토너먼트 참가 버튼
      pWidget= m_IDLResource.FindWidget( "DuelTournamentGame_2Test" );
      if(pWidget) pWidget->Show(bEnableDuelTournamentUI);
      pWidget= m_IDLResource.FindWidget( "DuelTournamentGame_4Test" );
      if(pWidget) pWidget->Show(bEnableDuelTournamentUI);
    #endif
  
Change <br>

    //#ifdef _PUBLISH
      pWidget= m_IDLResource.FindWidget( "DuelTournamentGame_2Test" );
      if(pWidget) pWidget->Show(false);
      pWidget= m_IDLResource.FindWidget( "DuelTournamentGame_4Test" );
      if(pWidget) pWidget->Show(false);
    //#else	// 테스트용 2,4인 듀얼토너먼트 참가 버튼
      pWidget= m_IDLResource.FindWidget( "DuelTournamentGame_2Test" );
      if(pWidget) pWidget->Show(bEnableDuelTournamentUI);
      pWidget= m_IDLResource.FindWidget( "DuelTournamentGame_4Test" );
      if(pWidget) pWidget->Show(bEnableDuelTournamentUI);
    //#endif  
  
  
OR

Open(MFeatureDefine.h) <br>
Add <br>

    #define _DUEL1VS1TEST

Open(ZGameInterface.cpp) <br>
Replace <br>

    #ifdef _DUEL1VS1TEST
        pWidget = m_IDLResource.FindWidget("DuelTournamentGame_2Test");
        if (pWidget) pWidget->Show(false);
        pWidget = m_IDLResource.FindWidget("DuelTournamentGame_4Test");
        if (pWidget) pWidget->Show(false);
    #else
        pWidget = m_IDLResource.FindWidget("DuelTournamentGame_2Test");
        if (pWidget) pWidget->Show(bEnableDuelTournamentUI);
        pWidget = m_IDLResource.FindWidget("DuelTournamentGame_4Test");
        if (pWidget) pWidget->Show(bEnableDuelTournamentUI);
    #endif

Open(ZInterfaceListener.cpp) <br>
Replace <br>

    #ifdef _DUEL1VS1TEST
        ZPostDuelTournamentRequestCancelGame( ZGetMyUID(), MDUELTOURNAMENTTYPE_QUATERFINAL);
    #else
        switch (g_lastPressedDuelTournamentGameBtn) {
            case 2 : ZPostDuelTournamentRequestCancelGame( ZGetMyUID(), MDUELTOURNAMENTTYPE_FINAL); break;
            case 4 : ZPostDuelTournamentRequestCancelGame( ZGetMyUID(), MDUELTOURNAMENTTYPE_SEMIFINAL); break;
            default : ZPostDuelTournamentRequestCancelGame( ZGetMyUID(), MDUELTOURNAMENTTYPE_QUATERFINAL); break;
        }
    #endif
  
  
![img](https://i.imgur.com/NCQ4QQw.jpg)
  
Credits too MAIET SOURCE & ArenBunny.
