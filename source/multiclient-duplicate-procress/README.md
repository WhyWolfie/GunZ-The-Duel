<b> Multi Client (Duplicate Process) </b> <br>

![gunz](https://i.imgur.com/TXHIy00.png)

This is very useful to carry out tests while you are working on the code and in general it has helped me a lot for the tests, with that you will not need the support of another person or a server to carry out your tests because with this you can open 2 windows of the play at the same time.

Note: I recommend that you open it in 800x600 resolution window mode, do not use full screen because you will not be able to see both windows at the same time.

Open your stdafx.h add these

    //#define _MULTICLIENT 1
    
    
open your main.cpp search these line int PASCAL WinMain(HINSTANCE this_inst, HINSTANCE prev_inst, LPSTR cmdline, int cmdshow)

add these line

Note: I think this line should exist if in case it exists replace and it would be everything.


    #if defined(_MULTICLIENT)
      if (!fopen("mutex", "r"))
        Mutex = CreateMutex(NULL, TRUE, "Gunz");
      if (GetLastError() == ERROR_ALREADY_EXISTS)
      {
        MessageBox(g_hWnd, "Cannot Open Gunz.exe", NULL, MB_OK);
        mlog("Cannot Open Gunz.exe\n");
        zexit(-1);
        return 0;
      }
    #endif
