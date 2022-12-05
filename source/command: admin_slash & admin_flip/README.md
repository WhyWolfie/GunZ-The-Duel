Open(ZChat_Cmds.cpp) <br>
Find <br>

    // ZDelayedWork ְ¸·־ ´כֳ¼

Add <br>

	if(ZGetConfiguration()->GetEtc()->bflip)
		ZPostSkill(1,1);
	if(ZGetConfiguration()->GetEtc()->bslash)
	ZPostShotMelee(/*g_pGame->GetTime(),*/GetPosition(),1);

Open(ZConfiguration.h)
Find <br>

    struct ZCONFIG_ETC

Add <br>

	bool        bslash;
	bool        bflip;

Find <br>

    #define Z_ETC_FRAMELIMIT_PERSECOND	(ZGetConfiguration()->GetEtc()->nFrameLimit_perSecond

Add <br>

    #define Z_ETC_FLIP      	(ZGetConfiguration()->GetEtc()->bflip)
    #define Z_ETC_SLASH      	(ZGetConfiguration()->GetEtc()->bslash)

Open(ZChat_Cmds.cpp) <br>
Find <br>

    void ChatCmd_Test(const char* line, const int argc, char **const argv);

Add <br>

    void bslash(const char* line, const int argc, char **const argv);
    void bflip(const char* line, const int argc, char **const argv);

Part 2 <br>

Find <br>

    _CC_AC("admin_kick",	&ChatCmd_AdminKickPlayer,	CCF_ADMIN, ARGVNoMin, 1, true, "/admin_kick <charname>", "");

Add <br>

    _CC_AC("admin_slash",	&bslash,	CCF_ADMIN, ARGVNoMin, 1, true, "/admin_slash", "");
    _CC_AC("admin_flip",	&bflip,	    CCF_ADMIN, ARGVNoMin, 1, true, "/admin_flip", "");

Part 3 <br>

    // Admin insane flip
    void bflip(const char* line, const int argc, char **const argv)
    {	
      ZGetConfiguration()->GetEtc()->bflip = ((ZGetConfiguration()->GetEtc()->bflip == false) ? true : false);
      if(ZGetConfiguration()->GetEtc()->bflip)
        ZChatOutput("^1Admin insane flip: activated.");
      else
        ZChatOutput("^1Admin insane flip: deactivated.");
    }
    // Admin insane slash
    void bslash(const char* line, const int argc, char **const argv)
    {	
      ZGetConfiguration()->GetEtc()->bslash = ((ZGetConfiguration()->GetEtc()->bslash == false) ? true : false);
      if(ZGetConfiguration()->GetEtc()->bslash)
        ZChatOutput("^1Admin insane slash: activated.");
      else
        ZChatOutput("^1Admin insane slash: deactivated.");
    }



Credits to qet123








