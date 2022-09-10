Open (ZOptionInterface.cpp)

Fix: Iterator crash fix, in case resolution isn't supported

Find

    map< int, D3DDISPLAYMODE>::iterator iter = find_if( gDisplayMode.begin(), gDisplayMode.end(), value_equals<int, D3DDISPLAYMODE>(ddm));
    
Place under

			if (iter != gDisplayMode.end())
				pWidget->SetSelIndex(iter->first);
			else
				pWidget->SetSelIndex(0);
    
Open (RVisualMesh.cpp)

Find

	DEL(m_pCloth);
    
Replace

	 SAFE_DELETE_ARRAY(m_pCloth);
    
    
Open (MCommandBuilder.h)

Changed buffer size to fix shop list issues.

Find

	#define COMMAND_BUFFER_LEN	16384
    
Replace

	#define COMMAND_BUFFER_LEN	65535 
	
Open(MMatchConfig.h)

Find

	#define SERVER_CONFIG_DEFAULT_NJ_DBAGENT_IP ""
	
Replace

	#define SERVER_CONFIG_DEFAULT_NJ_DBAGENT_IP "YOUR IP"

Open(MAsyncDBJob_GetLoginInfo.cpp) <br>
It's an SQLi pretty much. It allows for remote execution of queries on the server machine. Any and all queries can be run through it as long as the user account has access.
Find

    // ¿ø·¡ °èÁ¤Àº ³Ý¸¶ºí¿¡ ÀÖÀ¸¹Ç·Î ÇØ´ç °èÁ¤ÀÌ ¾øÀ¸¸é »õ·Î »ý¼ºÇÑ´Ù. 
    if (!pDBMgr->GetLoginInfo(m_szUserID, &m_nAID, m_szDBPassword))
    {
        int nGunzSex;    // °ÇÁîµðºñÀÇ ¼ºº°°ªÀº ³Ý¸¶ºí ¼ºº°°ª°ú ¹Ý´ëÀÌ´Ù.
        if (m_nSex == 0) nGunzSex = 1; else nGunzSex = 0;

        int nCert = 0;
        if (strlen(m_szCertificate) > 0)
        {
            if (m_szCertificate[0] == '1') nCert =1;
        }

        pDBMgr->CreateAccount(m_szUserID, m_szUniqueID, nCert, m_szName, m_nAge, nGunzSex);
        pDBMgr->GetLoginInfo(m_szUserID, &m_nAID, m_szDBPassword);
    } 

Replace

    // ¿ø·¡ °èÁ¤Àº ³Ý¸¶ºí¿¡ ÀÖÀ¸¹Ç·Î ÇØ´ç °èÁ¤ÀÌ ¾øÀ¸¸é »õ·Î »ý¼ºÇÑ´Ù. 
    if (!pDBMgr->GetLoginInfo(m_szUserID, &m_nAID, m_szDBPassword))
    {
        /*int nGunzSex;    // °ÇÁîµðºñÀÇ ¼ºº°°ªÀº ³Ý¸¶ºí ¼ºº°°ª°ú ¹Ý´ëÀÌ´Ù.
        if (m_nSex == 0) nGunzSex = 1; else nGunzSex = 0;

        int nCert = 0;
        if (strlen(m_szCertificate) > 0)
        {
            if (m_szCertificate[0] == '1') nCert =1;
        }

        pDBMgr->CreateAccount(m_szUserID, m_szUniqueID, nCert, m_szName, m_nAge, nGunzSex);
        pDBMgr->GetLoginInfo(m_szUserID, &m_nAID, m_szDBPassword);*/
        
        SetResult(MASYNC_RESULT_FAILED);
        return;        
    } 

Open(ZGameInterface.cpp) <br>
Find

	char* pszAgentIP = "";

Change

	char* pszAgentIP = "YOUR IP";

Open(MPdb.cpp)
Find

	if (!g_pfnEnumerateLoadedModules(hProcess, EnumLoadedModulesCallback, (PVOID)hProcess))

Change

	if (!EnumerateLoadedModules(hProcess, (PENUMLOADED_MODULES_CALLBACK)EnumLoadedModulesCallback, (PVOID)hProcess))
	


