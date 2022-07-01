<b>Kill Feed</b><br>
As I was scammed I decided to release this because it is useless.
There are some Brazilians who pass themselves off as a person and are scamming others.

Beware of the Brazilians.

these only base.

    #include "stdafx.h"

    #include "ZKillFeed.h"
    #include "ZGameInterface.h"
    #include "ZInterfaceItem.h"
    #include "ZApplication.h"
    #include "ZInterfaceListener.h"
    #include "ZIDLResource.h"
    #include "ZPost.h"
    #include "MChattingFilter.h"
    #include "MTextArea.h"
    #include "ZConfiguration.h"

    #define MAX_CHAT_OUTPUT_LINE 3

    class MCombatChatInputListener : public MListener {
    public:
      virtual bool OnCommand(MWidget* pWidget, const char* szMessage) {
        if (MWidget::IsMsg(szMessage, MEDIT_ENTER_VALUE) == true)
        {
          if (strlen(pWidget->GetText()) >= 256) return false;

          const char* szCommand = pWidget->GetText();
          if (szCommand[0] != '\0')
          {
            char szMsg[512];
            strcpy(szMsg, szCommand);
            strcpy(szMsg, pWidget->GetText());

            if (!ZGetConfiguration()->GetViewGameChat())
            {
              if (ZGetCombatInterface())
              {
                ZGetCombatInterface()->ShowChatOutput(true);
              }
            }
            ZApplication::GetGameInterface()->GetChat()->Input(szMsg);
          }

          pWidget->SetText("");
          if (ZGetCombatInterface())
          {
            ZGetCombatInterface()->EnableInputChat(false);
          }
          return true;
        }
        else if (MWidget::IsMsg(szMessage, MEDIT_ESC_VALUE) == true)
        {
          pWidget->SetText("");
          ZGetCombatInterface()->EnableInputChat(false);
        }
        else if ((MWidget::IsMsg(szMessage, MEDIT_CHAR_MSG) == true) || (MWidget::IsMsg(szMessage, MEDIT_KEYDOWN_MSG) == true))
        {
          ZApplication::GetGameInterface()->GetChat()->FilterWhisperKey(pWidget);
        }

        return false;
      }
    };
    MCombatChatInputListener	g_CombatChatInputListener2;

    MListener* ZGetCombatChatInputListener2(void)
    {
      return &g_CombatChatInputListener2;
    }

    ZKillFeed::ZKillFeed()
    {
      m_bChatInputVisible = true;
      m_nLastChattingMsgTime = 0;
      m_pIDLResource = ZApplication::GetGameInterface()->GetIDLResource();

      m_pChattingOutput = NULL;
      m_pInputEdit = NULL;
      m_pTabPlayerList = NULL;
      m_bTeamChat = false;
      m_bShowOutput = true;
    }

    ZKillFeed::~ZKillFeed()
    {
    }

    bool ZKillFeed::Create(const char* szOutputTxtarea, bool bUsePlayerList)
    {
      MWidget* pWidget = m_pIDLResource->FindWidget(ZIITEM_COMBAT_CHATINPUT);
      if (pWidget != NULL)
      {
        pWidget->SetListener(ZGetCombatChatInputListener2());
      }

      m_pChattingOutput = NULL;
      pWidget = m_pIDLResource->FindWidget(szOutputTxtarea);
      if (pWidget != NULL)
      {
        m_pChattingOutput = ((MTextArea*)pWidget);
      }

      if (m_pChattingOutput != NULL)
      {
        m_pChattingOutput->Clear();
      }

      pWidget = m_pIDLResource->FindWidget(ZIITEM_COMBAT_CHATINPUT);
      if (pWidget != NULL)
      {
        m_pInputEdit = (MEdit*)pWidget;
        m_pInputEdit->Show(false);

        if (bUsePlayerList)
        {
          MWidget* pPivot = m_pInputEdit->GetParent();
          m_pTabPlayerList = new ZTabPlayerList("TabPlayerList", pPivot, ZGetCombatInterface());
          m_pTabPlayerList->Show(false);
          m_pTabPlayerList->SetBounds(m_pInputEdit->GetPosition().x, m_pInputEdit->GetPosition().y - 120 - 5, 150, 120);
          m_pTabPlayerList->SetChatControl(m_pInputEdit);
          m_pInputEdit->SetTabHandler(m_pTabPlayerList);
        }
      }

      MLabel* pLabelToTeam = (MLabel*)m_pIDLResource->FindWidget(ZIITEM_COMBAT_CHATMODE_TOTEAM);
      if (pLabelToTeam) pLabelToTeam->Show(false);
      MLabel* pLabelToAll = (MLabel*)m_pIDLResource->FindWidget(ZIITEM_COMBAT_CHATMODE_TOALL);
      if (pLabelToAll) pLabelToAll->Show(false);

      return true;
    }

    void ZKillFeed::Destroy()
    {
      if (m_pTabPlayerList)
      {
        delete m_pTabPlayerList;
        m_pTabPlayerList = NULL;
      }
      if (m_pInputEdit)
      {
        m_pInputEdit->SetListener(NULL);
      }
      m_pChattingOutput = NULL;
    }

    void ZKillFeed::Update()
    {
      UpdateChattingBox();
      if ((m_pInputEdit) && (m_bChatInputVisible))
      {
        if (!m_pInputEdit->IsFocus())
        {
          if (m_pTabPlayerList && !m_pTabPlayerList->IsFocus())
            EnableInput(false);
        }
      }
    }

    void ZKillFeed::UpdateChattingBox()
    {
      if (m_pChattingOutput == NULL) return;

      if (m_pChattingOutput->GetLineCount() > 0)
      {
        unsigned long int nNowTime = timeGetTime();

    #define CHAT_DELAY_TIME	5000
        if ((nNowTime - m_nLastChattingMsgTime) > CHAT_DELAY_TIME)
        {
          m_pChattingOutput->DeleteFirstLine();
          m_nLastChattingMsgTime = nNowTime;
        }
      }
    }

    void ZKillFeed::EnableInput(bool bEnable, bool bToTeam)
    {
      MLabel* pLabelToTeam = (MLabel*)m_pIDLResource->FindWidget(ZIITEM_COMBAT_CHATMODE_TOTEAM);
      MLabel* pLabelToAll = (MLabel*)m_pIDLResource->FindWidget(ZIITEM_COMBAT_CHATMODE_TOALL);
      if (bEnable == true) {
        SetTeamChat(bToTeam);
        if (bToTeam) {
          if (pLabelToTeam != NULL) pLabelToTeam->Show(true);
          if (pLabelToAll != NULL) pLabelToAll->Show(false);
        }
        else {
          if (pLabelToTeam != NULL) pLabelToTeam->Show(false);
          if (pLabelToAll != NULL) pLabelToAll->Show(true);
        }
      }
      else {
        if (pLabelToTeam != NULL) pLabelToTeam->Show(false);
        if (pLabelToAll != NULL) pLabelToAll->Show(false);
      }

      if (m_pInputEdit)
      {
        m_pInputEdit->Show(bEnable);
      }

      if (bEnable)
      {
        if (m_pInputEdit)
        {
          if (!m_pInputEdit->IsFocus()) m_pInputEdit->SetFocus();
        }
      }
      else
      {
      }

      m_bChatInputVisible = bEnable;

      if (ZGetGame()->m_pMyCharacter == NULL) return;

      if (bEnable)
      {
        ZPostPeerChatIcon(true);
      }
      else
      {
        ZPostPeerChatIcon(false);
      }
    }

    void ZKillFeed::OutputChatMsg(const char* szMsg)
    {
      if (m_pChattingOutput == NULL) return;

      if (m_pChattingOutput->GetLineCount() == 0)
        for (int i = 0; i < (MAX_CHAT_OUTPUT_LINE - 1); i++) m_pChattingOutput->AddText("");
      m_pChattingOutput->AddText(szMsg);

      ProcessChatMsg();
    }

    void ZKillFeed::OutputChatMsg(MCOLOR color, const char* szMsg)
    {
      if (m_pChattingOutput == NULL) return;

      if (m_pChattingOutput->GetLineCount() == 0)
        for (int i = 0; i < (MAX_CHAT_OUTPUT_LINE - 1); i++) m_pChattingOutput->AddText("");
      m_pChattingOutput->AddText(szMsg, color);

      ProcessChatMsg();
    }

    void ZKillFeed::ProcessChatMsg()
    {
      while ((m_pChattingOutput->GetLineCount() > MAX_CHAT_OUTPUT_LINE))
      {
        m_pChattingOutput->DeleteFirstLine();
      }

      if (m_pChattingOutput->GetLineCount() >= 1)
      {
        m_nLastChattingMsgTime = timeGetTime();
      }
    }

    void ZKillFeed::OnDraw(MDrawContext* pDC)
    {
      if (m_pInputEdit)
      {
        if (m_pInputEdit->IsVisible())
        {
          pDC->SetColor(0xFF, 0xFF, 0xFF, 50);
          pDC->FillRectangle(m_pInputEdit->GetScreenRect());
        }
      }

    }

    void ZKillFeed::SetFont(MFont* pFont)
    {
      m_pChattingOutput->SetFont(pFont);
    }

    void ZKillFeed::ShowOutput(bool bShow)
    {
      if (m_pChattingOutput) m_pChattingOutput->Show(bShow);
      m_bShowOutput = bShow;
    }
    
    
    
Part 2
    
    #pragma once

    #include "ZInterface.h"

    class MEdit;
    class MTextArea;

    class ZKillFeed
    {
    private:
    protected:
      ZIDLResource* m_pIDLResource;
      MEdit* m_pInputEdit;
      ZTabPlayerList* m_pTabPlayerList;
      bool				m_bChatInputVisible;
      unsigned long int	m_nLastChattingMsgTime;
      bool				m_bTeamChat;
      bool				m_bShowOutput;

      void SetTeamChat(bool bVal) { m_bTeamChat = bVal; }
      void UpdateChattingBox();
      void ProcessChatMsg();
    public:
      MTextArea* m_pChattingOutput;

      ZKillFeed();
      virtual ~ZKillFeed();
      bool Create(const char* szOutputTxtarea, bool bUsePlayerList);
      void Destroy();

      void Update();
      void EnableInput(bool bEnable, bool bToTeam = false);
      void OutputChatMsg(const char* szMsg);
      void OutputChatMsg(MCOLOR color, const char* szMsg);

      void OnDraw(MDrawContext* pDC);
      bool IsChat() { return m_bChatInputVisible; }
      bool IsTeamChat() { return m_bTeamChat; }
      bool IsShow()
      {
        if (m_pInputEdit == NULL) return false;
        return m_pInputEdit->IsVisible();
      }
      void SetFont(MFont* pFont);

      void ShowOutput(bool bShow);
    };
    
    
    
Credits to: megol
