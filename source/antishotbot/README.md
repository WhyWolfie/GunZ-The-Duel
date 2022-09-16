Create file name (antishotbot.cpp) <br>

    #include "StdAfx.h"

    HHOOK MouseHook;

    LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
    {
      if (nCode == HC_ACTION)
      {
        if(wParam == WM_RBUTTONDOWN || wParam == WM_LBUTTONDOWN)
        {
          MSLLHOOKSTRUCT *info=(MSLLHOOKSTRUCT*)lParam;     
          if((info->flags & LLMHF_INJECTED) == LLMHF_INJECTED)
          {
            ExitProcess(-1);
          }
        }
      }
      return CallNextHookEx(MouseHook,nCode,wParam,lParam);
    }


    void AntiShotbotLogger()
    {
        HINSTANCE hInstance = GetModuleHandle(NULL);

        MouseHook = SetWindowsHookEx( WH_MOUSE_LL, MouseHookProc, hInstance, NULL );
        MSG message;
        while (GetMessage(&message,NULL,0,0)) {
            TranslateMessage( &message );
            DispatchMessage( &message );
        }

        UnhookWindowsHookEx(MouseHook);
        return;
    }
    
Open (Main.cpp) | Line 96 <br>
Add <br>

    void AntiShotbotLogger();
    
Find (InitialLoading success) | Line 197 <br>
Add <br>

    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)AntiShotbotLogger, 0, 0, 0);

Credits too Gunblade.
