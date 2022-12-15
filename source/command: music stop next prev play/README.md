Not done yet. <br>

Open(ZChat_Cmds.cpp) <br>
Find <br>

    void ChatCmd_AdminAssasin( const char* line, const int argc, char **const argv );

Add <br>

    void ChatCmd_Play(const char* line, const int argc, char **const argv);
    void ChatCmd_Next(const char* line, const int argc, char **const argv);
    void ChatCmd_Prev(const char* line, const int argc, char **const argv);
    void ChatCmd_Stop(const char* line, const int argc, char **const argv);

Find <br>

	_CC_AC("admin_commander",				&ChatCmd_AdminAssasin,					CCF_ADMIN|CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/admin_commander", "");
	
Add <br>

	_CC_AC("play", &ChatCmd_Play, CCF_ALL, ARGVNoMin, -1, true, "/play", "");
	_CC_AC("next", &ChatCmd_Next, CCF_ALL, ARGVNoMin, -1, true, "/next", "");
	_CC_AC("prev", &ChatCmd_Prev, CCF_ALL, ARGVNoMin, -1, true, "/prev", "");
	_CC_AC("stop", &ChatCmd_Stop, CCF_ALL, ARGVNoMin, -1, true, "/stop", "");

Find <br>

    void OutputCmdWrongArgument(const char* cmd)
    {
      ZChatOutput(ZMsg(MSG_WRONG_ARGUMENT));
      OutputCmdUsage(cmd);
    }

Add <br>

    void ChatCmd_Play(const char* line, const int argc, char** const argv)
    {
      ZGetSoundEngine()->PlayMusic();
    }

    void ChatCmd_Next(const char* line, const int argc, char** const argv)
    {
      ZGetSoundEngine()->PlayNext();
    }

    void ChatCmd_Prev(const char* line, const int argc, char** const argv)
    {
      ZGetSoundEngine()->PlayPrevious();
    }

    void ChatCmd_Stop(const char* line, const int argc, char** const argv)
    {
      ZGetSoundEngine()->StopMusic();
    }

Open(ZSoundEngine.cpp) <br>
Find <br>

    void ZSoundEngine::MusicEndCallback(void* pCallbackContext)
    {
      ZSoundEngine* pSoundEngine = (ZSoundEngine*)pCallbackContext;
      if (pSoundEngine->m_bBattleMusic)
      {
        pSoundEngine->OpenMusic(BGMID_BATTLE, pSoundEngine->m_pfs);
        pSoundEngine->PlayMusic();
      }
    }

Replace <br>

    void ZSoundEngine::MusicEndCallback(void* pCallbackContext)
    {
      ZSoundEngine* pSoundEngine = (ZSoundEngine*)pCallbackContext;
      if (pSoundEngine->m_bBattleMusic)
      {
        //pSoundEngine->OpenMusic(BGMID_BATTLE, pSoundEngine->m_pfs);
        pSoundEngine->PlayNext();
        pSoundEngine->PlayMusic();
      }
    }

Find <br>

      int nRealBgmIndex = nBgmIndex;
      if ((nBgmIndex >= BGMID_BATTLE) && (nBgmIndex < BGMID_FIN)) nRealBgmIndex = RandomNumber(BGMID_BATTLE, BGMID_FIN-1);
      sprintf(szFileName, "%s%s", BGM_FOLDER, m_stSndFileName[nRealBgmIndex]);

      return szFileName;
    }

Add <br>

    void ZSoundEngine::PlayNext() 
    {
      OpenMusic(++m_nCurrBGMIndex, m_pfs);
      PlayMusic(false);
    }

    void ZSoundEngine::PlayPrevious() 
    {
      OpenMusic(--m_nCurrBGMIndex, m_pfs);
      PlayMusic(false);
    }

Find <br>

    bool ZSoundEngine::OpenMusic(int nBgmIndex, MZFileSystem* pfs)
    {
      if( !m_bSoundEnable ) return false;

      m_pfs=pfs;
      if (nBgmIndex == BGMID_BATTLE) m_bBattleMusic = true;
      else m_bBattleMusic = false;

      char szFileName[256];
      strcpy(szFileName, GetBGMFileName(nBgmIndex));

      return OpenMusic(szFileName, pfs);
    }

Add <br>

    bool ZSoundEngine::OpenMusic(int nBgmIndex, MZFileSystem* pfs)
    {
      if (!m_bSoundEnable) return false;

      m_pfs = pfs;
      if (nBgmIndex == BGMID_BATTLE) m_bBattleMusic = true;
      else m_bBattleMusic = false;

      char szFileName[256];

      if (nBgmIndex < 0) 
      {
        nBgmIndex = (MAX_BGM - 1);
      }
      else if (nBgmIndex > MAX_BGM) 
      {
        nBgmIndex = 0;
      }

      m_nCurrBGMIndex = nBgmIndex;
      strcpy(szFileName, GetBGMFileName(nBgmIndex));

      return OpenMusic(szFileName, pfs);
    }

Open(ZSoundEngine.h) <br>
Find <br>


	void Destroy();
	bool LoadResource( char* pFileName_ ,ZLoadingProgress *pLoading = NULL );
	bool Reload();

Add <br>

	void PlayNext();
	void PlayPrevious();

Open(ZGame.cpp) <br>
Find <br>

    #ifdef _BIRDSOUND
      ZApplication::GetSoundEngine()->OpenMusic(BGMID_BATTLE);
      ZApplication::GetSoundEngine()->PlayMusic();
    #else
      ZApplication::GetSoundEngine()->OpenMusic(BGMID_BATTLE, pfs);
      ZApplication::GetSoundEngine()->PlayMusic();
    #endif

Add <br>

    #ifdef _BIRDSOUND
      ZApplication::GetSoundEngine()->OpenMusic(BGMID_BATTLE);
      ZApplication::GetSoundEngine()->PlayMusic();
    #else
      //ZApplication::GetSoundEngine()->OpenMusic(BGMID_BATTLE, pfs); // old
      ZApplication::GetSoundEngine()->PlayNext();
      ZApplication::GetSoundEngine()->PlayMusic();
    #endif

Open(ZSoundEngine.h) <br>
Find <br>

	MZFileSystem*	m_pfs;
	bool			m_bBattleMusic;
	const char*		GetBGMFileName(int nBgmIndex);

Add <br>

	int				m_nCurrBGMIndex;





