File: Source\RealSpace2\Source\RealSpace2.cpp <br>
Search:  float g_fFPS=0; <br>
Paste <br>

    double CurrentTime = timeGetTime();

Search: void RFlip()
Replace <br>

    void RFlip()
    {
      REndScene();

    //	if (g_rsbRenderStarted == true) REndScene();
      g_pd3dDevice->Present( NULL, NULL, NULL, NULL );

      if(g_rsnRenderFlags & RRENDER_CLEAR_BACKBUFFER)
      {
        //if(g_bStencilBuffer)
          //g_pd3dDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER |D3DCLEAR_STENCIL ,g_clear_color,1.0f ,0L);
        //else
          g_pd3dDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,g_clear_color,1.0f ,0L);
      }
      else
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER ,g_clear_color,1.0f ,0);

      //RBeginScene();	

      //FPS Fix
      RBeginScene();
      {
        g_nFrameCount++;		double fFrameLimit = 0;
        if (g_nFrameLimitValue > 0) {
          fFrameLimit = 1000.0 / g_nFrameLimitValue;
        }
        double NewTime = timeGetTime();
        double FrameTime = NewTime - CurrentTime;
        double WaitTime = fFrameLimit - FrameTime;
        if (FrameTime > 100.0)
        {
          CurrentTime = timeGetTime() + fFrameLimit;
        }
        while (WaitTime > 0.0) {
          double DeltaTime = min(WaitTime, fFrameLimit);
          Sleep(DeltaTime);
          WaitTime -= DeltaTime;
        }
        CurrentTime += fFrameLimit;
        double CurrentTimeFPS = timeGetTime();
        if (g_dwLastFPSTime + FPS_INTERVAL < CurrentTimeFPS) {
          g_fFPS = (g_nFrameCount - g_nLastFrameCount) * (float)FPS_INTERVAL / ((float)(CurrentTimeFPS - g_dwLastFPSTime) * (FPS_INTERVAL / 1000.f));
          g_dwLastFPSTime = CurrentTimeFPS;
          g_nLastFrameCount = g_nFrameCount;
        }
      }
    }

