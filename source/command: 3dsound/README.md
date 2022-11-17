Command: 3DSound (/sound)

Open(ZChat_Cmds.cpp)

    void ChatCmd_SHOTGUN3DSOUND(const char* line, const int argc, char **const argv);

Part 2

    _CC_AC("sound",	            &ChatCmd_SHOTGUN3DSOUND,	    CCF_ALL, ARGVNoMin, 1, true, "/sound", "");

Part 3


    void ChatCmd_SHOTGUN3DSOUND(const char* line, const int argc, char **const argv)
    {	
      ZGetConfiguration()->GetExtra()->bShotgunSound = ((ZGetConfiguration()->GetExtra()->bShotgunSound == false) ? true : false);
      if(ZGetConfiguration()->GetExtra()->bShotgunSound)
        ZChatOutput("^23D Sound mode has been enabled.");
      else
        ZChatOutput("^23D Sound mode has been disabled.");
      ZGetOptionInterface()->SaveInterfaceOption();
    }

Open(ZConfiguration.cpp - just add at ZTOK_EXTRA)

		if (parentElement.FindChildNode(ZTOK_EXTRA, &childElement))
		{
			childElement.GetChildContents(&m_Extra.bShotgunSound, ZTOK_EXTRA_SHOTGUN3DSOUND);
		}

Part 2 (follow aRootElement.CreateChildElement(ZTOK_EXTRA); add under )

	  parentElement.AppendText("\n\t\t");
		aElement = parentElement.CreateChildElement(ZTOK_EXTRA_SHOTGUN3DSOUND);
		sprintf(temp, "%s", m_Extra.bShotgunSound?"TRUE":"FALSE");
		aElement.SetContents(temp);


Open(ZConfiguration.h - struct ZCONFIG_EXTRA)

    bool bShotgunSound;


Open(ZSoundEngine.cpp) & Find (ZSoundEngine::PlaySEFire) And Replace. <br>

    void ZSoundEngine::PlaySEFire(MMatchItemDesc *pDesc, float x, float y, float z, bool bHero)
    {
      if( !pDesc ) return;

      if( pDesc->m_nType == MMIT_RANGE || pDesc->m_nType == MMIT_CUSTOM  )
      {
        char* szSndName = pDesc->m_szFireSndName;

        rvector pos = rvector(x,y,z);
        PlaySoundCharacter(szSndName, pos, bHero, 200);
        return;

        // ÀÚ±â ÀÚ½ÅÀÌ¸é ÃÑ¼Ò¸®´Â 2d·Î ³½´Ù.
        if (bHero)
        {
          char szFireSndName[256];
          if(ZGetConfiguration()->GetExtra()->bShotgunSound == false) {
          sprintf(szFireSndName, "%s%s", szSndName, "_2d");
          } else if(ZGetConfiguration()->GetExtra()->bShotgunSound == true) {
          sprintf(szFireSndName, "%s%s", szSndName, "_optional_2d"); 
          }
          char key[256] = "";
          GetSoundName(szFireSndName, key);

          RealSound2::PlaySound(key, 200);
        }
        else
        {
          rvector pos = rvector(x,y,z);
          PlaySoundCharacter(szSndName, pos, bHero, 200);
        }
      }

    }

Find (ZSoundEngine::PlaySEReload) And Replace.

    void ZSoundEngine::PlaySEReload(MMatchItemDesc *pDesc, float x, float y, float z, bool bHero)
    {
      if(!pDesc )	return;

      if(pDesc->m_nType == MMIT_RANGE)
      {
        char* szSndName = pDesc->m_szReloadSndName;
        if(bHero)
        {
          char szBuffer[64];
          if(ZGetConfiguration()->GetExtra()->bShotgunSound == false) {
          sprintf(szBuffer, "%s%s", szSndName, "_2d");
          } else if(ZGetConfiguration()->GetExtra()->bShotgunSound == true) {
          sprintf(szBuffer, "%s%s", szSndName, "_optional_2d"); 
          }
          char key[256] = "";
          GetSoundName(szBuffer, key);

          RealSound2::PlaySound(key, 200);
        }
        else
        {
          rvector pos = rvector(x,y,z);
          PlaySoundCharacter(szSndName, pos, bHero, 200);
        }
        //PlaySoundElseDefault(szSndName,"we_rifle_reload",rvector(x,y,z),bPlayer);
      }

    }


Find(ZSoundEngine::PlaySEFire) And Replace.

    void ZSoundEngine::PlaySEFire(MMatchItemDesc *pDesc, float x, float y, float z, bool bPlayer)
    {
      if( !m_bSoundEnable || !pDesc )	return;

      if( pDesc->m_nType.Ref() == MMIT_RANGE || pDesc->m_nType.Ref() == MMIT_CUSTOM )
      {
        char* szSndName = pDesc->m_szFireSndName;
        if(bPlayer)
        {
          char szBuffer[64];


          if(ZGetConfiguration()->GetExtra()->bShotgunSound == false) {
          sprintf(szBuffer, "%s%s", szSndName, "_2d");
          } else if(ZGetConfiguration()->GetExtra()->bShotgunSound == true) {
          sprintf(szBuffer, "%s%s", szSndName, "_optional_2d"); 
          }
    #ifdef _SOUND_LOG
          mlog("%s stereo 2d sound is played..\n",szBuffer);
    #endif
          char* szDefault;
          if (pDesc->m_nType.Ref() == MMIT_RANGE)
            szDefault = szSndName;
          else 
            szDefault = szSndName;



          PlaySoundElseDefault(szBuffer,szDefault,rvector(x,y,z),bPlayer);
          return;
        }
        PlaySoundElseDefault(szSndName,"we_rifle_fire",rvector(x,y,z),bPlayer);
      }
    }

Find(ZSoundEngine::PlaySEReload) And Replace.

    void ZSoundEngine::PlaySEReload(MMatchItemDesc *pDesc, float x, float y, float z, bool bPlayer)
    {
      if( !m_bSoundEnable || !pDesc )	return;

      if(pDesc->m_nType.Ref() == MMIT_RANGE)
      {
        char* szSndName = pDesc->m_szReloadSndName;
        if(bPlayer)
        {
          char szBuffer[64];
          if(ZGetConfiguration()->GetExtra()->bShotgunSound == false) {
          sprintf(szBuffer, "%s%s", szSndName, "_2d");
          } else if(ZGetConfiguration()->GetExtra()->bShotgunSound == true) {
          sprintf(szBuffer, "%s%s", szSndName, "_optional_2d"); 
          }

    #ifdef _SOUND_LOG
          mlog("%s stereo 2d sound is played..\n",szBuffer);
    #endif
          PlaySoundElseDefault(szSndName,"we_rifle_reload_2d",rvector(x,y,z),bPlayer);
        }
        PlaySoundElseDefault(szSndName,"we_rifle_reload",rvector(x,y,z),bPlayer);
      }
    }






    

