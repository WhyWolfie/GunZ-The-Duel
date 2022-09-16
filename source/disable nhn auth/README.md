Open (Main.cpp) <br>
Find <br>


    #ifdef LOCALE_NHNUSA
      BYTE SHA_HanAuthForClient[20] = {0x29,0xc0,0x7e,0x6b,0x8d,0x1d,0x30,0xd2,0xed,0xac,0xaf,0xea,0x78,0x16,0x51,0xf0,0x50,0x52,0x26,0x91};
      BYTE SHA_hanpollforclient[20] = {0x09,0x04,0x51,0x9d,0x95,0xbb,0x66,0x2a,0xfb,0x93,0x87,0x2d,0x21,0xa2,0x93,0x1d,0x6a,0xcb,0xa5,0x4f};
      BYTE SHA_HanReportForClient[20] = {0x4c,0x62,0xaf,0x4d,0x5b,0x54,0xb8,0x96,0x46,0x66,0x8f,0x1e,0x12,0xe7,0xf2,0xd7,0xe4,0x58,0x65,0xc9}; 
      if(!CheckDll("hanauthforclient.dll", SHA_HanAuthForClient) || 
         !CheckDll("hanpollforclient.dll", SHA_hanpollforclient) ||
         !CheckDll("hanreportforclient.dll", SHA_HanReportForClient) )
      {
        MessageBox(g_hWnd,"Dll Hacking detected",  NULL, MB_OK);
        return false;
      }

      if( !InitReport() ) 
        return 0;


      if ( !InitPoll())
        return 0;
    #endif


Change <br>

    //Disable NHN Auth
      /*
    #ifdef LOCALE_NHNUSA
      BYTE SHA_HanAuthForClient[20] = {0x29,0xc0,0x7e,0x6b,0x8d,0x1d,0x30,0xd2,0xed,0xac,0xaf,0xea,0x78,0x16,0x51,0xf0,0x50,0x52,0x26,0x91};
      BYTE SHA_hanpollforclient[20] = {0x09,0x04,0x51,0x9d,0x95,0xbb,0x66,0x2a,0xfb,0x93,0x87,0x2d,0x21,0xa2,0x93,0x1d,0x6a,0xcb,0xa5,0x4f};
      BYTE SHA_HanReportForClient[20] = {0x4c,0x62,0xaf,0x4d,0x5b,0x54,0xb8,0x96,0x46,0x66,0x8f,0x1e,0x12,0xe7,0xf2,0xd7,0xe4,0x58,0x65,0xc9}; 
      if(!CheckDll("hanauthforclient.dll", SHA_HanAuthForClient) || 
         !CheckDll("hanpollforclient.dll", SHA_hanpollforclient) ||
         !CheckDll("hanreportforclient.dll", SHA_HanReportForClient) )
      {
        MessageBox(g_hWnd,"Dll Hacking detected",  NULL, MB_OK);
        return false;
      }

      if( !InitReport() ) 
        return 0;


      if ( !InitPoll())
        return 0;
    #endif
      */

Find <br>

    #ifdef LOCALE_NHNUSA
        GetNHNUSAReport().ReportInitGameGuard();
    #endif

Change <br>

    #ifdef LOCALE_NHNUSA
        //Disable NHN related
        //GetNHNUSAReport().ReportInitGameGuard();
    #endif

Find <br>

    #ifdef LOCALE_NHNUSA
        mlog( "Poll Process\n" );
        int nRetPoll = GetNHNUSAPoll().ZHanPollProcess( NULL);
    #endif
    
Change <br>

    #ifdef LOCALE_NHNUSA
        //Disable NHN poll
        //mlog( "Poll Process\n" );
        //int nRetPoll = GetNHNUSAPoll().ZHanPollProcess( NULL);
    #endif

Find <br>

    #ifdef LOCALE_NHNUSA
            GetNHNUSAReport().ReportCrashedGame();
    #endif
    
Change <br>

    #ifdef LOCALE_NHNUSA
            //Disable NHN related
            //GetNHNUSAReport().ReportCrashedGame();
    #endif

Find <br>

    bool InitReport()
    {
    #ifdef LOCALE_NHNUSA
        mlog( "Init report start\n" );
        if( !GetNHNUSAReport().InitReport(((ZNHN_USAAuthInfo*)(ZGetLocale()->GetAuthInfo()))->GetUserID().c_str(),
            ((ZNHN_USAAuthInfo*)(ZGetLocale()->GetAuthInfo()))->GetGameStr()) )
        {
            mlog( "Init nhn report fail.\n" );
            return false;
        }
        GetNHNUSAReport().ReportStartGame();
        mlog( "Init report success.\n" );
    #endif

        return true;
    }
    
Change <br>

    bool InitReport()
    {
        return true;

        //Disable NHN Auth
        /*
    #ifdef LOCALE_NHNUSA
        mlog( "Init report start\n" );
        if( !GetNHNUSAReport().InitReport(((ZNHN_USAAuthInfo*)(ZGetLocale()->GetAuthInfo()))->GetUserID().c_str(),
            ((ZNHN_USAAuthInfo*)(ZGetLocale()->GetAuthInfo()))->GetGameStr()) )
        {
            mlog( "Init nhn report fail.\n" );
            return false;
        }
        GetNHNUSAReport().ReportStartGame();
        mlog( "Init report success.\n" );
    #endif

        return true;
        */
    }
    
Find <br>

    bool InitPoll()
    {
    #ifdef LOCALE_NHNUSA
        mlog( "Init poll start\n" );

        ((ZNHN_USAAuthInfo*)(ZGetLocale()->GetAuthInfo()))->ZUpdateGameString();

        if( !GetNHNUSAPoll().ZHanPollInitGameString( ((ZNHN_USAAuthInfo*)(ZGetLocale()->GetAuthInfo()))->GetGameStr()) )
            return false;
    #endif

        return true;
    }
    
Change <br>

    bool InitPoll()
    {
        return true;

        //Disable NHN Auth
        /*
    #ifdef LOCALE_NHNUSA
        mlog( "Init poll start\n" );

        ((ZNHN_USAAuthInfo*)(ZGetLocale()->GetAuthInfo()))->ZUpdateGameString();

        if( !GetNHNUSAPoll().ZHanPollInitGameString( ((ZNHN_USAAuthInfo*)(ZGetLocale()->GetAuthInfo()))->GetGameStr()) )
            return false;
    #endif

        return true;
        */
    }

Find <br>

        // restore user id
    #ifdef LOCALE_NHNUSA
        pUSAAuthInfo = (ZNHN_USAAuthInfo*)ZGetLocale()->GetAuthInfo();
        pUSAAuthInfo->SetUserID(strUserID);
    #endif
    
Change <br>

	//Disable NHN Auth
	// restore user id
    //#ifdef LOCALE_NHNUSA
    //	pUSAAuthInfo = (ZNHN_USAAuthInfo*)ZGetLocale()->GetAuthInfo();
    //	pUSAAuthInfo->SetUserID(strUserID);
    //#endif
    
Find <br>

	// save user id
    #ifdef LOCALE_NHNUSA
        ZNHN_USAAuthInfo* pUSAAuthInfo = (ZNHN_USAAuthInfo*)ZGetLocale()->GetAuthInfo();
        string strUserID = pUSAAuthInfo->GetUserID();
    #endif
    
Change <br>

	//Disable NHN Auth
	// save user id
    //#ifdef LOCALE_NHNUSA
    //	ZNHN_USAAuthInfo* pUSAAuthInfo = (ZNHN_USAAuthInfo*)ZGetLocale()->GetAuthInfo();
    //	string strUserID = pUSAAuthInfo->GetUserID();
    //#endif
    
Find <br>

    #ifdef LOCALE_NHNUSA
    #include "ZNHN_USA.h"
    #include "ZNHN_USA_Report.h"
    #include "ZNHN_USA_Poll.h"
    #endif
    
Change <br>

    //Disable NHN auth
    //#ifdef LOCALE_NHNUSA
    //#include "ZNHN_USA.h"
    //#include "ZNHN_USA_Report.h"
    //#include "ZNHN_USA_Poll.h"
    //#endif
