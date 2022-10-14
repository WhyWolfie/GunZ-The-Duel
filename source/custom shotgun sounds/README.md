Open(ZSoundEngine.cpp) <br>

    void ZSoundEngine::PlaySEFire(MMatchItemDesc *pDesc, float x, float y, float z, bool bPlayer)
    {
      if( !m_bSoundEnable || !pDesc )	return;

      if( pDesc->m_nType.Ref() == MMIT_RANGE || pDesc->m_nType.Ref() == MMIT_CUSTOM )
      {
        char* szSndName = pDesc->m_szFireSndName;
        if(bPlayer)
        {
          char szBuffer[64];
          sprintf( szBuffer, "%s_2d", szSndName );
    #ifdef _SOUND_LOG
          mlog("%s stereo 2d sound is played..\n",szBuffer);
    #endif
          char* szDefault;
          if (pDesc->m_nType.Ref() == MMIT_RANGE)
            szDefault = "we_rifle_fire_2d";
          else 
            szDefault = szSndName;

          PlaySoundElseDefault(szBuffer,szDefault,rvector(x,y,z),bPlayer);
          return;
        }
        PlaySoundElseDefault(szSndName,"we_rifle_fire",rvector(x,y,z),bPlayer);
      }
    }
    
Replace with

    void ZSoundEngine::PlaySEFire(MMatchItemDesc *pDesc, float x, float y, float z, bool bPlayer)
    {
      if (!m_bSoundEnable || !pDesc)	return;

      if (pDesc->m_nType.Ref() == MMIT_RANGE || pDesc->m_nType.Ref() == MMIT_CUSTOM)
      {
        char* szSndName = pDesc->m_szFireSndName;
        if (bPlayer)
        {
          char szBuffer[64];
            sprintf(szBuffer, "%s%s", szSndName, "_2d");
    #ifdef _SOUND_LOG
          mlog("%s stereo 2d sound is played..\n", szBuffer);
    #endif
          char* szDefault;
          if (pDesc->m_nType.Ref() == MMIT_RANGE)
            szDefault = szSndName;
          else
            szDefault = szSndName;

          PlaySoundElseDefault(szBuffer, szDefault, rvector(x, y, z), bPlayer);
          return;
        }
        PlaySoundElseDefault(szSndName, "we_rifle_fire", rvector(x, y, z), bPlayer);
      }
    }
    
    
Find

    void ZSoundEngine::PlaySEReload(MMatchItemDesc *pDesc, float x, float y, float z, bool bPlayer)
    {
      if( !m_bSoundEnable || !pDesc )	return;

      if(pDesc->m_nType.Ref() == MMIT_RANGE)
      {
        char* szSndName = pDesc->m_szReloadSndName;
        if(bPlayer)
        {
          char szBuffer[64];
          sprintf( szBuffer, "%s_2d", szSndName );
    #ifdef _SOUND_LOG
          mlog("%s stereo 2d sound is played..\n",szBuffer);
    #endif
          PlaySoundElseDefault(szBuffer,"we_rifle_reload_2d",rvector(x,y,z),bPlayer);
        }
        PlaySoundElseDefault(szSndName,"we_rifle_reload",rvector(x,y,z),bPlayer);
      }
    }

Replace

    void ZSoundEngine::PlaySEReload(MMatchItemDesc *pDesc, float x, float y, float z, bool bPlayer)
    {
      if (!m_bSoundEnable || !pDesc)	return;

      if (pDesc->m_nType.Ref() == MMIT_RANGE)
      {
        char* szSndName = pDesc->m_szReloadSndName;
        if (bPlayer)
        {
          char szBuffer[64];
            sprintf(szBuffer, "%s%s", szSndName, "_2d");
    #ifdef _SOUND_LOG
          mlog("%s stereo 2d sound is played..\n", szBuffer);
    #endif
          PlaySoundElseDefault(szSndName, "we_rifle_reload_2d", rvector(x, y, z), bPlayer);
        }
        PlaySoundElseDefault(szSndName, "we_rifle_reload", rvector(x, y, z), bPlayer);
      }
    }
