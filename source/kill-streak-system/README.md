I made a simple Kill Streaks and it works very well, since I'm not going to use it I decided to leave it to you.
Not a 100% finished code but it serves as a basis for you to complement your form.


MSharedCommandTable.cpp
----------------------------------------------------

      C(MC_PEER_KILL_STREAKS, "Peer.Kill.Streaks", "Kill Streaks System", MCDT_PEER2PEER)
          P(MPT_STR, "szName")
          P(MPT_INT, "nStreaks")

MSharedCommandTable.h
-------------------------------------------------   
      #define MC_PEER_KILL_STREAKS                    50000

ZGame.cpp
-------------------------------------------------   
      case MC_PEER_KILL_STREAKS:
          {
             char szName[MAX_CHARNAME_LENGTH];
             int nStreaks;

             if (!pCommand->GetParameter(szName, 0, MPT_STR, sizeof(szName))) break;
             if (!pCommand->GetParameter(&nStreaks, 1, MPT_INT)) break;

             char szMessage[128];

             if (nStreaks == 2)
             {
                sprintf(szMessage, "%s has a double kill! (%d kill streaks)", szName, nStreaks);
                ZChatOutput(MCOLOR(255,255,255), szMessage);
             }
             else if (nStreaks == 3)
             {
                sprintf(szMessage, "%s has a triple kill! (%d kill streaks)", szName, nStreaks);
                ZChatOutput(MCOLOR(255,255,255), szMessage);
             }
             else
             {
                sprintf(szMessage, "");
                ZChatOutput(MCOLOR(255,255,255), szMessage);
             }
          }
      break;

Search: void ZGame::OnPeerDieMessage(ZCharacter* pVictim, ZCharacter* pAttacker)
Line: 5837
------------------------------------------------- 
      nStreaks = 0;

Line: 5883

      nStreaks += 1;
      if (nStreaks == 2)
      {
        ZPostKillStreaks(szAttacker, nStreaks);
      }
      else if (nStreaks == 3)
      {
        ZPostKillStreaks(szAttacker, nStreaks);
      }

ZGlobal.cpp
---------------------------
    int nStreaks = 0;


ZGlobal.h
------------------------
    extern int nStreaks;

ZPost.h
---------------------
    inline void ZPostKillStreaks(const char* szName, int nStreaks)
    {
      ZPOSTCMD2(MC_PEER_KILL_STREAKS, MCmdParamStr(szName), MCommandParameterInt(nStreaks))
    }

Credits to: Tronixz




