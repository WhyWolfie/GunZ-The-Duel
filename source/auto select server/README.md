Open(ZGameInterface.cpp) <br>
Find <br>

    pServerList->SetCurrSel( nCurrSel);

Replace <br>

    pServerList->SetCurrSel( 0 );


Or

Open(MFeatureDefine.h) <br>
Add <br>

     #define AUTO_SELECT_SERVER

Open(ZGameInterface.cpp) <br>
Find <br>

    pServerList->SetCurrSel( nCurrSel);

Replace <br>

	#ifdef AUTO_SELECT_SERVER
		pServerList->SetCurrSel(0);
	#else
		pServerList->SetCurrSel(nCurrSel);
	#endif
    
Enable 

    #define AUTO_SELECT_SERVER
    
Disable 

    //#define AUTO_SELECT_SERVER
