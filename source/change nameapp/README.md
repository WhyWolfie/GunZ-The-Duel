Open(ZGlobal.h) <br>
Find <br>

    #ifdef LOCALE_BRAZIL
    #define APPLICATION_NAME		"The Duel"
    #else
    #define APPLICATION_NAME		"Gunz"
    #endif

    #ifdef LOCALE_BRAZIL
    #define GUNZ_FOLDER			"/The Duel"
    #elif LOCALE_JAPAN
    #define GUNZ_FOLDER			"/GUNZWEI"
    #else
    #define GUNZ_FOLDER			"/Gunz"
    #endif
    
Replace <br>

    #ifdef LOCALE_BRAZIL
    #define APPLICATION_NAME		"The Duel"
    #elif defined(_NAMEAPP)
    #define APPLICATION_NAME		_NAMEAPP
    #else
    #define APPLICATION_NAME		"Gunz"
    #endif

    #ifdef LOCALE_BRAZIL
    #define GUNZ_FOLDER			"/The Duel"
    #elif LOCALE_JAPAN
    #define GUNZ_FOLDER			"/GUNZWEI"
    #elif defined(_NAMEAPPFOLDER)
    #define GUNZ_FOLDER			"/" _NAMEAPPFOLDER
    #else
    #define GUNZ_FOLDER			"/Gunz"
    #endif


Open(MFeatureDefine.h) <br>
Add <br>

    #define _NAMEAPP "Gunz"	
    #define _NAMEAPPFOLDER "Gunz The Duel"




