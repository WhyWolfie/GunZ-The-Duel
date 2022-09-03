Fix for jur13n (any other old sources)

(source/cscommon/include/realcpnet.h)


find (realcpnet.h) 

    typedef enum RCP_IO_OPERATION {
    
change

    enum RCP_IO_OPERATION {
    
    
(source/cscommon/source/realcpnet.cpp)

find (realcpnet.cpp)

	GetSystemInfo(&systemInfo);
	m_dwThreadCount = systemInfo.dwNumberOfProcessors * 2;

add under

	// Custom: Memory writing past buffer fix. (12 cores [24 threads] will cause this to freak out)
	if (m_dwThreadCount > MAX_WORKER_THREAD)
		m_dwThreadCount = MAX_WORKER_THREAD;
    
    
find

    #ifndef _DEBUG
    __try{
    #endif
        while(TRUE) {
    
replace

     while(TRUE)
     {
     
     
     
remove(1)

      #ifndef _DEBUG
      } __except(pRealCPNet->CrashDump(GetExceptionInformation())) 
      {
      // ¼­¹ö¸¸ ½ÇÇàÇÏµµ·Ï ÇÏ±âÀ§ÇÔÀÌ´Ù.
      #ifndef _PUBLISH
        char szFileName[_MAX_DIR];
        GetModuleFileName(NULL, szFileName, _MAX_DIR);
        HANDLE hProcess = MProcessController::OpenProcessHandleByFilePath(szFileName);
        TerminateProcess(hProcess, 0);
      #endif
      }
      #endif
      
remove(2)

    DWORD MRealCPNet::CrashDump(PEXCEPTION_POINTERS ExceptionInfo)
    {
      mlog("CrashDump Entered 1\n");
      EnterCriticalSection(&m_csCrashDump);
      mlog("CrashDump Entered 2\n");

      if (PathIsDirectory("Log") == FALSE)
        CreateDirectory("Log", NULL);

      time_t		tClock;
      struct tm*	ptmTime;

      time(&tClock);
      ptmTime = localtime(&tClock);

      char szFileName[_MAX_DIR];
      int nFooter = 1;
      while(TRUE)
      {
        wsprintf(szFileName, "Log\\RealCPNet_%02d-%02d-%02d-%d.dmp", ptmTime->tm_year+1900, ptmTime->tm_mon+1, ptmTime->tm_mday, nFooter);
           // sprintf(szFileName, "Log/RealCPNet_%02d-%02d-%02d-%d.dmp", ptmTime->tm_year+1900, ptmTime->tm_mon+1, ptmTime->tm_mday, nFooter);

        if (PathFileExists(szFileName) == FALSE)
          break;

        nFooter++;
        if (nFooter > 100) 
        {
          LeaveCriticalSection(&m_csCrashDump);
          return false;
        }
      }

      DWORD ret = CrashExceptionDump(ExceptionInfo, szFileName, true);

      mlog("CrashDump Leaving\n");
      LeaveCriticalSection(&m_csCrashDump);
      mlog("CrashDump Leaved\n");

      return ret;
    }
