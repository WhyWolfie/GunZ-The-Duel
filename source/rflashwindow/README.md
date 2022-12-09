Open(MFeatureDefine.h) <br>
Add <br>

    #define _RFLASH

Open(ZGameClient_Ladder.cpp) <br>
Find <br>

    MWidget* pWidget = pResource->FindWidget("ProposalAgreementConfirm");

Replace <br>

      MWidget* pWidget = pResource->FindWidget("ProposalAgreementConfirm");
      if(pWidget!=NULL)
      {
        static ZCOUNTDOWN countDown = {PROPOSAL_AGREEMENT_TIMEOUT_SEC,
                        "ProposalAgreementConfirm_Remain",
                        "ProposalAgreementConfirm",
                        OnAskReplierAgreement_OnExpire};
        countDown.nSeconds=PROPOSAL_AGREEMENT_TIMEOUT_SEC;	// static ÀÌ¹Ç·Î Àç¼³Á¤
        ZApplication::GetTimer()->SetTimerEvent(0, &OnTimer_CountDown, &countDown, true);

        pWidget->Show(true, true);
    #ifdef _RFLASH
        RFlashWindow();
    #endif
      }
    }

Find <br>

    ZPostLadderRequestChallenge(ppMember, nCount, nBalancedMatching, nAntiLead);

Replace <br>

            ZPostLadderRequestChallenge(ppMember, nCount, nBalancedMatching, nAntiLead);
    #ifdef _RFLASH
            RFlashWindow();
    #endif


Find <br>

        ZTransMsg(temp, MSG_LADDER_REPLIER_AGREEMENT_REJECT, 1, szRejecter);
        ZApplication::GetGameInterface()->ShowMessage(temp, NULL, MSG_LADDER_REPLIER_AGREEMENT_REJECT);
      }
    }


Replace <br>

        ZTransMsg(temp, MSG_LADDER_REPLIER_AGREEMENT_REJECT, 1, szRejecter);
        ZApplication::GetGameInterface()->ShowMessage(temp, NULL, MSG_LADDER_REPLIER_AGREEMENT_REJECT);

    #ifdef _RFLASH
        RFlashWindow();
    #endif

      }
    }

Find <br>

    void ZGameClient::OnLadderLaunch
    {

Add under <br>

    #ifdef _RFLASH
      RFlashWindow();
    #endif

Open(ZMyCharacter.cpp) <br>
Find <br>

	ZMyCharaterStatusBitPacking& zStatus = m_statusFlags.Ref();
	zStatus.m_bReserveDashAttacked = false;

Add under <br>

    #ifdef _RFLASH
      RFlashWindow();
    #endif 

Open(RealSpace2.h) <br>
Find <br>

    int		RGetVidioMemory();
    void	RSetWBuffer(bool bEnable);
    //bool	RIsStencilBuffer();


Add under <br>

    #ifdef _RFLASH
    void	RFlashWindow();
    #endif

Open(RealSpace2.cpp) <br>
Find <br> 

    _NAMESPACE_REALSPACE2_END

Add Above <br>

    #ifdef _RFLASH
    void RFlashWindow()
    {
      if (RIsActive())
        return;

      FLASHWINFO info;
      info.cbSize = sizeof(info);
      info.hwnd = g_hWnd;
      info.dwFlags = FLASHW_ALL;
      info.dwTimeout = 0;
      info.uCount = 3;

      FlashWindowEx(&info);
    }
    #endif




