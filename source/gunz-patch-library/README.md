Apparently, people still enjoy exploiting this game. Just don't... it deserves to rest in peace.

Here's a full list of exploits that are covered in this library:

1. MC_NET_CLEAR exploit
This packet can be used to crash the server by using a non-existing MUID.<br>
2. MC_NET_ECHO exploit
This packet can be used to send a message to a player if routed as peer packet.<br>
3. MC_MATCH_LOGIN_FROM_DBAGENT_FAILED exploit
If a valid MUID is provided, that player will be disconnected.<br>
4. MC_PEER_BUFF_INFO exploit
This will create a large loop resulting into a stack overflow.<br>
5. MC_MATCH_REGISTERAGENT exploit
Can be used to crash the MatchServer if the IP parameter is malformed.<br>
6. MC_NET_BANPLAYER_FLOODING exploit
See exploit #3<br>
7. MC_MATCH_DUELTOURNAMENT_REQUEST_JOINGAME exploit
Allows a hacker to send any player to join a duel tournament.<br>
8. MC_MATCH_DUELTOURNAMENT_REQUEST_CANCELGAME exploit
Allows a hacker to remove any player from a dual tournament.<br>
9. MC_MATCH_DUELTOURNAMENT_REQUEST_SIDERANKING_INFO exploit
Harmless.<br>
10. MC_MATCH_DUELTOURNAMENT_GAME_PLAYER_STATUS exploit<br>
Allows a hacker to retreive the current status of any player. This exploit can be used together with exploit #7 and #8.<br>
11. MC_MATCH_CHANNEL_REQUEST_PLAYER_LIST exploit<br>
Harmless.<br>
12. MC_MATCH_REQUEST_MY_SIMPLE_CHARINFO exploit<br>
Allows a hacker to retreive character information on any character.<br>
13. MC_NET_DISCONNECT exploit<br>
If this packet is routed as a peer packet, it will disconnect the player.<br>
14. MC_LOCAL_ECHO exploit<br>
See exploit #2<br>
15. MC_MATCH_LOGIN exploit<br>
Allows a hacker to crash your MatchServer by malforming the MD5 client hash.<br>
16. ZGame exploit
Allows a hacker to crash another player's client. <br>
17 - 27 SQL exploits
Allows a hacker to take full control over your database. <br>
<br>

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

Find:

        case MC_MATCH_REGISTERAGENT:
            {
                char szIP[128];
                int nTCPPort, nUDPPort;

                if (pCommand->GetParameter(&szIP, 0, MPT_STR, sizeof(szIP) ) == false) break;
                if (pCommand->GetParameter(&nTCPPort, 1, MPT_INT) == false) break;
                if (pCommand->GetParameter(&nUDPPort, 2, MPT_INT) == false) break;

                OnRegisterAgent(pCommand->GetSenderUID(), szIP, nTCPPort, nUDPPort);
            } 

Replace with:

        case MC_MATCH_REGISTERAGENT:
            {
                char szIP[128];
                int nTCPPort, nUDPPort;

                if (pCommand->GetParameter(&szIP, 0, MPT_STR, sizeof(szIP) ) == false) break;
                if (pCommand->GetParameter(&nTCPPort, 1, MPT_INT) == false) break;
                if (pCommand->GetParameter(&nUDPPort, 2, MPT_INT) == false) break;

                // Not the best way to patch, but working for now
                if (strstr(szIP, "%")) {
                    break;
                }
                
                OnRegisterAgent(pCommand->GetSenderUID(), szIP, nTCPPort, nUDPPort);
            } 

6. CSCommon > MMatchServer__OnCommand.cpp
Find:

        case MC_NET_BANPLAYER_FLOODING :
            {
                MUID uidPlayer;
                
                pCommand->GetParameter(&uidPlayer, 0, MPT_UID);
                if (MGetServerConfig()->IsUseBlockFlooding())
                {
                    MMatchObject* pObj = GetObject( uidPlayer );
                    if( pObj && pObj->GetDisconnStatusInfo().GetStatus() == MMDS_CONNECTED)
                    {
                        if( pObj->GetAccountName() ) {
                            LOG(LOG_PROG,"Ban Player On Flooding - (MUID:%d%d, ID:%s)"
                                , uidPlayer.High, uidPlayer.Low, pObj->GetAccountName());
                        } else {
                            LOG(LOG_PROG,"Ban Player On Flooding - (MUID:%d%d, ID:%s)"
                                , uidPlayer.High, uidPlayer.Low);
                        }
                        
                        pObj->DisconnectHacker( MMHT_COMMAND_FLOODING );
                    }
                    else
                    {
                        LOG(LOG_PROG,"Ban Player On Flooding - Can't Find Object");
                    }
                }
            }
            break; 

Replace with:

        case MC_NET_BANPLAYER_FLOODING :
            {
                /*MUID uidPlayer;
                
                pCommand->GetParameter(&uidPlayer, 0, MPT_UID);
                if (MGetServerConfig()->IsUseBlockFlooding())
                {
                    MMatchObject* pObj = GetObject( uidPlayer );
                    if( pObj && pObj->GetDisconnStatusInfo().GetStatus() == MMDS_CONNECTED)
                    {
                        if( pObj->GetAccountName() ) {
                            LOG(LOG_PROG,"Ban Player On Flooding - (MUID:%d%d, ID:%s)"
                                , uidPlayer.High, uidPlayer.Low, pObj->GetAccountName());
                        } else {
                            LOG(LOG_PROG,"Ban Player On Flooding - (MUID:%d%d, ID:%s)"
                                , uidPlayer.High, uidPlayer.Low);
                        }
                        
                        pObj->DisconnectHacker( MMHT_COMMAND_FLOODING );
                    }
                    else
                    {
                        LOG(LOG_PROG,"Ban Player On Flooding - Can't Find Object");
                    }
                }*/
            }
            break; 

7. CSCommon > MMatchServer__OnCommand.cpp
Find:

        case MC_MATCH_DUELTOURNAMENT_REQUEST_JOINGAME :
            {
                MUID uidPlayer;
                MDUELTOURNAMENTTYPE nType;

                pCommand->GetParameter(&uidPlayer, 0, MPT_UID);
                pCommand->GetParameter(&nType, 1, MPT_INT);

                if( MGetServerConfig()->IsEnabledDuelTournament() )    {
                    ResponseDuelTournamentJoinChallenge(uidPlayer, nType);
                }

            }
            break; 

Replace with:

        case MC_MATCH_DUELTOURNAMENT_REQUEST_JOINGAME :
            {
                //MUID uidPlayer;
                MDUELTOURNAMENTTYPE nType;

                //pCommand->GetParameter(&uidPlayer, 0, MPT_UID);
                pCommand->GetParameter(&nType, 1, MPT_INT);

                if( MGetServerConfig()->IsEnabledDuelTournament() )    {
                    ResponseDuelTournamentJoinChallenge(pCommand->GetSenderUID(), nType);
                }

            }
            break;


8. CSCommon > MMatchServer__OnCommand.cpp
Find: 

        case MC_MATCH_DUELTOURNAMENT_REQUEST_CANCELGAME :
            {
                MUID uidPlayer;
                MDUELTOURNAMENTTYPE nType;

                pCommand->GetParameter(&uidPlayer, 0, MPT_UID);
                pCommand->GetParameter(&nType, 1, MPT_INT);

                if( MGetServerConfig()->IsEnabledDuelTournament() )    {
                    ResponseDuelTournamentCancelChallenge(uidPlayer, nType);
                }
            }
            break; 

Replace with:

        case MC_MATCH_DUELTOURNAMENT_REQUEST_CANCELGAME :
            {
                //MUID uidPlayer;
                MDUELTOURNAMENTTYPE nType;

                //pCommand->GetParameter(&uidPlayer, 0, MPT_UID);
                pCommand->GetParameter(&nType, 1, MPT_INT);

                if( MGetServerConfig()->IsEnabledDuelTournament() )    {
                    ResponseDuelTournamentCancelChallenge(pCommand->GetSenderUID(), nType);
                }
            }
            break; 
            
            
9. CSCommon > MMatchServer__OnCommand.cpp
Find: 

       case MC_MATCH_DUELTOURNAMENT_REQUEST_SIDERANKING_INFO :
            {
                MUID uidPlayer;

                pCommand->GetParameter(&uidPlayer, 0, MPT_UID);

                if( MGetServerConfig()->IsEnabledDuelTournament() ){
                    ResponseDuelTournamentCharSideRanking(uidPlayer);
                }
            }
            break; 

Replace with:

        case MC_MATCH_DUELTOURNAMENT_REQUEST_SIDERANKING_INFO :
            {
                //MUID uidPlayer;

                //pCommand->GetParameter(&uidPlayer, 0, MPT_UID);

                if( MGetServerConfig()->IsEnabledDuelTournament() ){
                    ResponseDuelTournamentCharSideRanking(pCommand->GetSenderUID());
                }
            }
            break; 

10. CSCommon > MMatchServer__OnCommand.cpp
Find: 

        case MC_MATCH_DUELTOURNAMENT_GAME_PLAYER_STATUS :
            {
                MUID uidPlayer;
                pCommand->GetParameter(&uidPlayer, 0, MPT_UID);

                if( MGetServerConfig()->IsEnabledDuelTournament() ){
                    ResponseDuelTournamentCharStatusInfo(uidPlayer, pCommand);
                }
            }
            break; 

Replace with: 

            case MC_MATCH_DUELTOURNAMENT_GAME_PLAYER_STATUS :
            {
                //MUID uidPlayer;
                //pCommand->GetParameter(&uidPlayer, 0, MPT_UID);

                if( MGetServerConfig()->IsEnabledDuelTournament() ){
                    ResponseDuelTournamentCharStatusInfo(pCommand->GetSenderUID(), pCommand);
                }
            }
            break; 

11. CSCommon > MMatchServer__OnCommand.cpp
Find: 

        case MC_MATCH_CHANNEL_REQUEST_PLAYER_LIST:
            {
                MUID uidPlayer, uidChannel;
                int nPage;

                pCommand->GetParameter(&uidPlayer, 0, MPT_UID);
                pCommand->GetParameter(&uidChannel, 1, MPT_UID);
                pCommand->GetParameter(&nPage, 2, MPT_INT);

                OnChannelRequestPlayerList(uidPlayer, uidChannel, nPage);
            }
            break; 
            
Replace with:

        case MC_MATCH_CHANNEL_REQUEST_PLAYER_LIST:
            {
                MUID /*uidPlayer, */uidChannel;
                int nPage;

                //pCommand->GetParameter(&uidPlayer, 0, MPT_UID);
                pCommand->GetParameter(&uidChannel, 1, MPT_UID);
                pCommand->GetParameter(&nPage, 2, MPT_INT);

                OnChannelRequestPlayerList(pCommand->GetSenderUID(), uidChannel, nPage);
            }
            break; 

12. CSCommon > MMatchServer__OnCommand.cpp
Find: 

        case MC_MATCH_REQUEST_MY_SIMPLE_CHARINFO:
            {
                MUID uidPlayer;
                pCommand->GetParameter(&uidPlayer, 0, MPT_UID);
                OnRequestMySimpleCharInfo(uidPlayer);
            }
            break; 
            
Replace with: 

        case MC_MATCH_REQUEST_MY_SIMPLE_CHARINFO:
            {
                //MUID uidPlayer;
                //pCommand->GetParameter(&uidPlayer, 0, MPT_UID);
                OnRequestMySimpleCharInfo(pCommand->GetSenderUID());
            }
            break; 

13. CSCommon > MClient.cpp
Find:

        case MC_NET_DISCONNECT:
            Disconnect(m_Server);
            break; 
            
Replace with:

        
        case MC_NET_DISCONNECT: 
        {
            if (pCommand->GetSenderUID() != GetUID()) {
                // Packet wasn't generated by our own client
                break;
            }

            Disconnect(m_Server);
            break; 
        } 











Credits to: Solaire
