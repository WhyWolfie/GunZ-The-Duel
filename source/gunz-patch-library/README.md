Apparently, people still enjoy exploiting this game. Just don't... it deserves to rest in peace.

Here's a full list of exploits that are covered in this library:

1. MC_NET_CLEAR exploit
This packet can be used to crash the server by using a non-existing MUID.
2. MC_NET_ECHO exploit
This packet can be used to send a message to a player if routed as peer packet.
3. MC_MATCH_LOGIN_FROM_DBAGENT_FAILED exploit
If a valid MUID is provided, that player will be disconnected.
4. MC_PEER_BUFF_INFO exploit
This will create a large loop resulting into a stack overflow.
5. MC_MATCH_REGISTERAGENT exploit
Can be used to crash the MatchServer if the IP parameter is malformed.
6. MC_NET_BANPLAYER_FLOODING exploit
See exploit #3
7. MC_MATCH_DUELTOURNAMENT_REQUEST_JOINGAME exploit
Allows a hacker to send any player to join a duel tournament.
8. MC_MATCH_DUELTOURNAMENT_REQUEST_CANCELGAME exploit
Allows a hacker to remove any player from a dual tournament.
9. MC_MATCH_DUELTOURNAMENT_REQUEST_SIDERANKING_INFO exploit
Harmless.
10. MC_MATCH_DUELTOURNAMENT_GAME_PLAYER_STATUS exploit
Allows a hacker to retreive the current status of any player. This exploit can be used together with exploit #7 and #8.
11. MC_MATCH_CHANNEL_REQUEST_PLAYER_LIST exploit
Harmless.
12. MC_MATCH_REQUEST_MY_SIMPLE_CHARINFO exploit
Allows a hacker to retreive character information on any character.
13. MC_NET_DISCONNECT exploit
If this packet is routed as a peer packet, it will disconnect the player.
14. MC_LOCAL_ECHO exploit
See exploit #2
15. MC_MATCH_LOGIN exploit
Allows a hacker to crash your MatchServer by malforming the MD5 client hash.
16. ZGame exploit
Allows a hacker to crash another player's client.
17 - 27 SQL exploits
Allows a hacker to take full control over your database.


1. CSCommon > MServer.cpp
Find:

    case MC_NET_CLEAR:
        {
            MUID uid;
            if (pCommand->GetParameter(&uid, 0, MPT_UID)==false) break;
            OnNetClear(uid);
            return true;
        }
        break; 

Replace:

     case MC_NET_CLEAR:
        {
            if (pCommand->GetSenderUID() != MUID(0, 2)) {
                // Not sent by server
                break;
            }

            MUID uid;
            if (pCommand->GetParameter(&uid, 0, MPT_UID)==false) break;
            OnNetClear(uid);
            return true;
        }
        break; 
        

2. CSCommon > MClient.cpp

Find:
       
       case MC_NET_ECHO:
            if(pCommand->GetParameter(szMessage, 0, MPT_STR, sizeof(szMessage) )==false) break;
            OutputMessage(szMessage, MZMOM_LOCALREPLY);
       break;

Replace with:
       
       case MC_NET_ECHO:
            //if(pCommand->GetParameter(szMessage, 0, MPT_STR, sizeof(szMessage) )==false) break;
            //OutputMessage(szMessage, MZMOM_LOCALREPLY);
        break; 

3. CSCommon > MMatchServer__OnCommand.cpp

Find: 

        case MC_MATCH_LOGIN_FROM_DBAGENT_FAILED:
            {
                MUID CommUID;
                int nResult;

                if (pCommand->GetParameter(&CommUID,    0, MPT_UID)==false) break;
                if (pCommand->GetParameter(&nResult,    1, MPT_INT)==false) break;

                OnMatchLoginFailedFromDBAgent(CommUID, nResult);
            }
            break; 

Replace with:

        case MC_MATCH_LOGIN_FROM_DBAGENT_FAILED:
            {
                /*MUID CommUID;
                int nResult;

                if (pCommand->GetParameter(&CommUID,    0, MPT_UID)==false) break;
                if (pCommand->GetParameter(&nResult,    1, MPT_INT)==false) break;

                OnMatchLoginFailedFromDBAgent(CommUID, nResult);*/
            }
            break; 

4. Gunz > ZGame.cpp

Find: 

    void ZGame::OnPeerBuffInfo(const MUID& uidSender, void* pBlobBuffInfo)
    {
        if (uidSender == ZGetMyUID()) return;

        ZCharacter* pSender = ZGetCharacterManager()->Find(uidSender);
        if (!pSender) return;
        if (!pBlobBuffInfo) return;

        MTD_BuffInfo* pBuffInfo = NULL;
        int numElem = MGetBlobArrayCount(pBlobBuffInfo);

        for (int i=0; i<numElem; ++i)
        {
            pBuffInfo = (MTD_BuffInfo*)MGetBlobArrayElement(pBlobBuffInfo, i);

            ApplyPotion(pBuffInfo->nItemId, pSender, (float)pBuffInfo->nRemainedTime);
        }
    } 

Replace with:

    void ZGame::OnPeerBuffInfo(const MUID& uidSender, void* pBlobBuffInfo)
    {
        if (uidSender == ZGetMyUID()) return;

        ZCharacter* pSender = ZGetCharacterManager()->Find(uidSender);
        if (!pSender) return;
        if (!pBlobBuffInfo) return;

        MTD_BuffInfo* pBuffInfo = NULL;
        int numElem = MGetBlobArrayCount(pBlobBuffInfo);

        // patch
        if (MGetBlobArraySize(pBlobBuffInfo) != (8 + (sizeof(MTD_BuffInfo) * numElem))) {
            return;
        }

        for (int i=0; i<numElem; ++i)
        {
            pBuffInfo = (MTD_BuffInfo*)MGetBlobArrayElement(pBlobBuffInfo, i);

            ApplyPotion(pBuffInfo->nItemId, pSender, (float)pBuffInfo->nRemainedTime);
        }
    } 

5. CSCommon > MMatchServer__OnCommand.cpp





Credits to: Solaire

















