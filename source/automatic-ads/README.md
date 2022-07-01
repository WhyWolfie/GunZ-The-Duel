<b>Automatic Ads</b><br>
Hi, I've been months without giving a small contribution to the community that I love so much, here I bring you a small code whose function is to announce through the chat staff, only you have to wait for a time of 10 minutes and it will be automatically received. An announcement to the lobby and game, I hope you put it to good use.

we will add correctly, it is always good to get used to working with switches, so we have the possibility to activate or deactivate code that we add without needing to replace game codes.

We are going to: MFeaturesDefine.h

    //RandomNotice
    #define _RANDOMNOTICE 1 // add //turn off and remove // turn on

    #define _RANDOMNOTICETIME (10 * 60 * 1000) // = Minutes* Seconds* milliseconds
    #define _RANDOMNOTICEMSG1 "Now you can receive items while playing Clan War."
    #define _RANDOMNOTICEMSG2 "Ahora puedes recibir items mientras juegas al clan war."
    #define _RANDOMNOTICEMSG3 "Enjoy the best types of games here at GUNZ!"
    #define _RANDOMNOTICEMSG4 "Use the ^5/commands^2 command to see the list."
    #define _RANDOMNOTICEMSG5 "Disfruta de los mejores tipos de juegos aquí en GUNZ!"
    #define _RANDOMNOTICEMSG6 "We are preparing a Tournament very soon so get ready!"
    #define _RANDOMNOTICEMSG7 "Batalha de torneios muito em breve, prepare-se agora!"
    #define _RANDOMNOTICEMSG8 "É novo? Faça um tour de suas equipes de personagens pela surpresa que lhe trazemos."
    #define _RANDOMNOTICEMSG9 "¿Eres nuevo? No te preocupes compra una Blue Box y canjealo ya!"
    #define _RANDOMNOTICEMSG10 "Daily events performed by the staff."
    #define _RANDOMNOTICEMSG11 "Eventos diarios realizado por los staff."
    
We are going to: MMatchServer.cpp

    #ifdef _RANDOMNOTICE
      static unsigned long RandomNotice = nGlobalClock;
      static unsigned int nMsg;
      if (nGlobalClock - RandomNotice > _RANDOMNOTICETIME)
      {
        string szMsg;

        if (nMsg == 0){
          szMsg = _RANDOMNOTICEMSG1;
          nMsg = 1;
        }
        else if (nMsg == 1){
          szMsg = _RANDOMNOTICEMSG2;
          nMsg = 2;
        }
        else if (nMsg == 2){
          szMsg = _RANDOMNOTICEMSG3;
          nMsg = 3;
        }
        else if (nMsg == 3){
          szMsg = _RANDOMNOTICEMSG4;
          nMsg = 4;
        }
        else if (nMsg == 4){
          szMsg = _RANDOMNOTICEMSG5;
          nMsg = 5;
        }
        else if (nMsg == 5){
          szMsg = _RANDOMNOTICEMSG6;
          nMsg = 6;
        }
        else if (nMsg == 6){
          szMsg = _RANDOMNOTICEMSG7;
          nMsg = 7;
        }
        else if (nMsg == 7){
          szMsg = _RANDOMNOTICEMSG8;
          nMsg = 8;
        }
        else if (nMsg == 8){
          szMsg = _RANDOMNOTICEMSG9;
          nMsg = 0;
        }
        else if (nMsg == 9){
          szMsg = _RANDOMNOTICEMSG10;
          nMsg = 0;
        }
        else if (nMsg == 10){
          szMsg = _RANDOMNOTICEMSG11;
          nMsg = 0;
        }
        else if (nMsg == 11){
          szMsg = _RANDOMNOTICEMSG11;
          nMsg = 0;
        }

        MCommand* pCmd = CreateCommand(MC_ADMIN_ANNOUNCE, MUID(0, 0));
        pCmd->AddParameter(new MCmdParamUID(MUID(0, 0)));
        pCmd->AddParameter(new MCmdParamStr(szMsg.c_str()));
        pCmd->AddParameter(new MCmdParamUInt(ZAAT_CHAT));
        RouteToAllClient(pCmd);
        RandomNotice = nGlobalClock;
      }
    #endif
    
    
    







