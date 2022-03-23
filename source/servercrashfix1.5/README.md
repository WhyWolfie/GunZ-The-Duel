<b> [Will fix the playercount + server enter crash] </b> <br>
<b> replace this code MMatchServer.cpp -> MMatchServer::UpdateServerStatusDB() </b>		
    
    //Wolfie: Server crash fix (playercount)
    /*#ifdef LOCALE_KOREA        
            int nNatePlayer = 0;

        for(MMatchObjectList::iterator iter = m_Objects.begin(); iter != m_Objects.end(); iter++) 
        {
            MMatchObject* pObj = (MMatchObject*)iter->second;
            if( pObj->GetAccountInfo()->m_nCCode == 30 ) { nNatePlayer++; }
        }

        bResult = m_MatchDBMgr.UpdateServerStatus_Netmarble(MGetServerConfig()->GetServerID(), nCurPlayer, nNatePlayer);
    #else*/
            bResult = m_MatchDBMgr.UpdateServerStatus(MGetServerConfig()->GetServerID(), nCurPlayer);
    /*#endif*/ 
