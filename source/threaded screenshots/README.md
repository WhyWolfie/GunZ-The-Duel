Got tired of screenshots using d3d and causing jitter, so i removed all d3d calls and detached a thread to make the screenshots smooth (ive tested and it seems stable, but I can't guarantee that the thread will execute before the if statement at the end of the screenshot function, thus prompting th euser the screenshot failed when it didn't).Anyways, onto the code:

Find ZGameInterface::SaveScreenShot()

replace the entire function with this:

    void ZGameInterface::SaveScreenShot()
    {
      static unsigned long int st_nLastTime = 0;
      unsigned long int nNowTime = timeGetTime();
    #define SCREENSHOT_DELAY		2000


      if ((nNowTime-st_nLastTime) < SCREENSHOT_DELAY)	return;
      st_nLastTime = nNowTime;


      char szPath[_MAX_PATH];
      char szFilename[_MAX_PATH];
      char szFilenameSafe[_MAX_PATH];

      TCHAR szMyDocPath[MAX_PATH];
      if(GetMyDocumentsPath(szMyDocPath)) {
        strcpy(szPath,szMyDocPath);
        strcat(szPath,GUNZ_FOLDER);
        CreatePath( szPath );
        strcat(szPath,SCREENSHOT_FOLDER);
        CreatePath( szPath );
        strcat(szPath, "/");
      }


      SYSTEMTIME t;
      GetLocalTime( &t );
      char szCharName[MATCHOBJECT_NAME_LENGTH];
      ValidateFilename(szCharName, ZGetMyInfo()->GetCharName(), '_');

      sprintf(szFilename,"%s_%4d%02d%02d_%02d%02d%02d",  
        szCharName, t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);

      sprintf(szFilenameSafe,"nocharname_%4d%02d%02d_%02d%02d%02d",  
        t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);

      RECT rect;
            ///Note: if you want the entire window, use GetWindowRect instead.
      ::GetClientRect(g_hWnd, &rect);
      char szFullPath[_MAX_PATH];	
      char szFullPathToNotify[_MAX_PATH];
      sprintf(szFullPath,"%s%s", szPath, szFilename);
      sprintf(szFullPathToNotify,"/Gunz/Screenshots/%s.jpg", szFilename);
      bool bSuccess = false;

      std::thread th(RScreenShot, std::ref(bSuccess), g_hWnd, rect.right - rect.left, rect.bottom - rect.top, szFullPath);
      th.detach();

      if (bSuccess = false)
        ZChatOutput(MCOLOR(ZCOLOR_CHAT_SYSTEM), ZMsg(MSG_SCREENSHOT_CANT_SAVE));
      else {
        char szOutput[256];
        ZTransMsg(szOutput, MSG_SCREENSHOT_SAVED, 1, szFullPathToNotify);
        ZChatOutput(MCOLOR(ZCOLOR_CHAT_SYSTEM), szOutput);
      }
    }
    
    
Next, open realspace2.h

find bool rscreenshot and replace it with this:

    void RScreenShot(bool& result,HWND wnd,int x,int y,const char *szFilename);
    
Now open realspace2.cpp and replace rscreenshot there with this:

    void RScreenShot(bool& result,HWND wnd,int x,int y,const char *szFilename)
    {
      char szFullFileName[_MAX_DIR];

      #ifdef _USE_GDIPLUS
        sprintf(szFullFileName, "%s.jpg", szFilename);
        RSaveAsJpeg(result,wnd,x, y, szFullFileName);
      #else
        sprintf(szFullFileName, "%s.bmp", szFilename);
        return RSaveAsBmp(x, y, data, szFullFileName);
      #endif
    }

Lastly, find rsaveasjpeg, and replace the whole function with this one:

	void RSaveAsJpeg(bool& result,HWND wnd,int x,int y,const char *szFilename)
	{
		HDC scrdc, memdc;
		HBITMAP membit;
		scrdc = GetDC(wnd);
		int Height = y;
		int Width = x;
		memdc = CreateCompatibleDC(scrdc);
		membit = CreateCompatibleBitmap(scrdc, Width, Height);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(memdc, membit);
		BitBlt(memdc, 0, 0, Width, Height, scrdc, 0, 0, SRCCOPY);

		Gdiplus::Bitmap bitmap(membit, NULL);
		CLSID clsid;
		EncoderParameters encoderParameters;
		ULONG             quality = 100;
		encoderParameters.Count = 1;

		encoderParameters.Parameter[0].Guid = EncoderQuality;
		encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
		encoderParameters.Parameter[0].NumberOfValues = 1;
		encoderParameters.Parameter[0].Value = &quality;

		// Make WFileName
		WCHAR wstrName[256];
		int nNameLen = strlen(szFilename) + 1;
		MultiByteToWideChar(CP_ACP, 0, szFilename, -1, wstrName, nNameLen - 1);
		wstrName[nNameLen - 1] = 0;

		// Save Bitmap
		CLSID  Clsid;
		int ret = GetCodecClsid(L"image/jpeg", &Clsid);

		if (bitmap.Save(wstrName, &Clsid, &encoderParameters) == Ok) {

			SelectObject(memdc, hOldBitmap);

			DeleteObject(memdc);

			DeleteObject(membit);

			ReleaseDC(wnd, scrdc);

			result = true;
		}
		else {
			result = false;
		}
    
You should now have very smooth screenshots (if the screenshot size is too large for you, reduce the quality variable in rsaveasjpeg to 50 instead of 100.

Thanks too Jetman.




    
