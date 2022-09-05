Fullscreen toggle fix (fixes windows 7 and higher bugs when toggling) <br>
So, i got tired of fg's client requiring you to restart the game if you changed from fullscreen to another window mode, decided i'd fix it and share it here (not that it's realy needed since most peopel dont toggle it, i only toggle it alot b/c of programming). Basically what this does is correct the window sizing issues that were previously there in windows 7 and higher, it also seems to correct the border defaulting to the classic border i think it's called? Anyways, here's the fix:

Realspace2.cpp:<br>

Replace this:<br>

    void RAdjustWindow(const RMODEPARAMS *pModeParams)
    {
      if((GetWindowLong( g_hWnd, GWL_STYLE) & WS_CHILD) !=0)
        return;

      if(pModeParams->bFullScreen)
      {
        SetWindowLong( g_hWnd, GWL_STYLE, WS_POPUP | WS_SYSMENU );
      }
      else
        SetWindowLong( g_hWnd, GWL_STYLE, WS_POPUP | WS_CAPTION | WS_SYSMENU );

      RECT rt;
      GetClientRect(g_hWnd,&rt);

      RECT winrt;
      GetWindowRect(g_hWnd,&winrt);

      MoveWindow(g_hWnd,winrt.left,winrt.top,
        winrt.right-winrt.left+(pModeParams->nWidth-(rt.right-rt.left)),
        winrt.bottom-winrt.top+(pModeParams->nHeight-(rt.bottom-rt.top)),FALSE);
    }

with this:

    void RAdjustWindow(const RMODEPARAMS *pModeParams)
    {
      if((GetWindowLong( g_hWnd, GWL_STYLE) & WS_CHILD) !=0)
        return;

      if(pModeParams->bFullScreen)
      {
        SetWindowLong( g_hWnd, GWL_STYLE, WS_POPUP | WS_SYSMENU );
      }
      else
        SetWindowLong( g_hWnd, GWL_STYLE, WS_POPUP | WS_CAPTION | WS_SYSMENU );

      RECT rt = { 0,0,pModeParams->nWidth,pModeParams->nHeight };
      if (!pModeParams->bFullScreen)
      {
        AdjustWindowRect(&rt, GetWindowLong(g_hWnd, GWL_STYLE), FALSE);
        SetWindowPos(g_hWnd, HWND_NOTOPMOST, 0, 0, rt.right - rt.left, rt.bottom - rt.top, SWP_SHOWWINDOW);
      }
    }
    
    
Thanks too Jetman.
