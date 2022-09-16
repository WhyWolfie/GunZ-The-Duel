Open(Main.cpp)<br>
Find<br>


    #ifndef _PUBLISH

      if(g_pDefFont) {
        static char __buffer[256];

        float fMs = 1000.f/g_fFPS;
        float fScore = 100-(fMs-(1000.f/60.f))*2;

        sprintf(__buffer, "FPS : %3.3f %.3fÁ¡ (%.3f ms)",g_fFPS,fScore,fMs);
        g_pDefFont->m_Font.DrawText( MGetWorkspaceWidth()-200,0,__buffer );
    //		OutputDebugString(__buffer);
      }

    #endif
    
    
Replace <br>

    #ifdef _FPSINLOBBY

      if (g_pDefFont)
      {
        static char buffer[256];
        float fMs = 1000.f / g_fFPS;
        float fScore = 100 - (fMs - (1000.f / 60.f)) * 2;
        sprintf(buffer, "FPS : %3.3f", g_fFPS);
        g_pDefFont->m_Font.DrawText(MGetWorkspaceWidth() - 200, 0, buffer);
      }

    #endif
    
Open(MFeatureDefine.h) <br>
Add <br>

    #define _FPSINLOBBY	1

![img](https://i.imgur.com/iQqXzGs.png)

