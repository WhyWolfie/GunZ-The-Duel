Open(ZServerView.cpp) <br>

go to line 17 and modify <br>

    #ifdef LOCALE_NHNUSA

Change too <br>

    #if defined(LOCALE_NHNUSA) || defined(_DEBUG) || defined(LOCALE_KOREA) || defined(LOCALE_BRAZIL) || defined_(LOCALE_INDIA) || defined(LOCALE_JAPAN) || defined(LOCALE_INTERNATIONAL)

Go to line 95 and modify: <br>

    #ifdef LOCALE_NHNUSA

Change to:

    #if defined(LOCALE_NHNUSA) || defined(_DEBUG) || defined(LOCALE_KOREA) || defined(LOCALE_BRAZIL) || defined_(LOCALE_INDIA) || defined(LOCALE_JAPAN) || defined(LOCALE_INTERNATIONAL)

Move Ping image Courtesy of Hideasu <br>

ZServerView.CPP > ZServerView::PingImageDraw <br>

    ORIGINAL: pDC->Draw(rectBox.x+nMoveImage , rectBox.y, 25 , 16);
    EXEMPLE: pDC->Draw(rectBox.x+nMoveImage , rectBox.y, 21 , 14);

IMPORTANT: <br>
Don't forget to set ip <br>

ZGameInterface.cpp line 6366 <br>

    char* pszAgentIP = "";

Change too <br>

    char* pszAgentIP = "your ip here";

CSCommon -> MMatchConfg -> MMatchConfig.h Line 245 (I forgot the rest of the original IP) <br>

    #define SERVER_CONFIG_DEFAULT_NJ_DBAGENT_IP			"210.X.X.X"

Change too <br>

    #define SERVER_CONFIG_DEFAULT_NJ_DBAGENT_IP			"YOUR IP HERE"



Credits to: OldSchoolGZ / Gregon13

Before 
![serverping2](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/ping%20at%20server%20select/serverping2.jpg)

After
![serverping](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/ping%20at%20server%20select/serverping.jpg)


