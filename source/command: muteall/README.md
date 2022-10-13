Open(ZChat_Cmds.cpp)

    void ChatCmd_AdminMuteAll(const char* line, const int argc, char **const argv); 

Part 2

    _CC_AC("muteall",            &ChatCmd_AdminMuteAll,            CCF_ADMIN, ARGVNoMin, 1 , true,"/muteall <num>", ""); 
    
Part 3
    
    void ChatCmd_AdminMuteAll(const char* line, const int argc, char **const argv)
    {
        if( argc < 2 )
        {
            OutputCmdWrongArgument(argv[0]);
            return;
        }

        if( !ZGetGame() )
        {
            ZChatOutput("You're not in game.", ZChat::CMT_SYSTEM);
            return;
        }

        int nValue = atoi(argv[1]);

        if( nValue == 0 )
        {
            ZChatOutput("Room unmuted.", ZChat::CMT_SYSTEM);
        }
        else if( nValue == 1 )
        {
            ZChatOutput("Room muted.", ZChat::CMT_SYSTEM);
        }
        else
        {
            ZChatOutput("Use: /muteall [0-1]", ZChat::CMT_SYSTEM);
            return;
        }

        ZPOSTCMD2(MC_MUTE_ALL, MCmdParamStr(""), MCmdParamInt(nValue));
    } 
    
Open(MMatchServer_OnCommand.cpp)

    case MC_MUTE_ALL:
                {
                    char szAdminName[ MAX_CHARNAME_LENGTH ] = "";
                    int nValue = 0;

                if (!pCommand->GetParameter( szAdminName, 0, MPT_STR, MAX_CHARNAME_LENGTH )) break;
                if (!pCommand->GetParameter( &nValue, 1, MPT_INT )) break;

                MMatchObject* pObj = GetObjectA(pCommand->GetSenderUID());
                
                if (pObj == NULL) break;
                if(!IsAdminGrade(pObj)) break;

                MCommand* pCmd = CreateCommand(MC_MUTE_ALL, MUID(0,0));
                pCmd->AddParameter(new MCmdParamStr(pObj->GetName()));
                pCmd->AddParameter(new MCmdParamInt(nValue));
                RouteToStage(pObj->GetStageUID(), pCmd);
            }
            break; 
            
Open(ZGameClient_OnCommand.cpp)

    case MC_MUTE_ALL:
                {
                    char szAdminName[128] = "";
                    int nValue = 0;
                    char szOutput[111] = "";

                if(ZGetMyInfo()->IsAdminGrade()) break;
                                
                pCommand->GetParameter(szAdminName, 0, MPT_STR, sizeof(szAdminName) );
                pCommand->GetParameter(&nValue, 1, MPT_INT);

                if( nValue == 1 )
                {
                    ZGetGame()->m_pMyCharacter->GetStatus().CheckCrc();
                    ZGetGame()->m_pMyCharacter->GetStatus().Ref().bMuteAll = true;
                    ZGetGame()->m_pMyCharacter->GetStatus().MakeCrc();
                    sprintf( szOutput, "Room muted by %s.", szAdminName );
                }
                else
                {
                    ZGetGame()->m_pMyCharacter->GetStatus().CheckCrc();
                    ZGetGame()->m_pMyCharacter->GetStatus().Ref().bMuteAll = false;
                    ZGetGame()->m_pMyCharacter->GetStatus().MakeCrc();
                    sprintf( szOutput, "Room unmuted by %s.", szAdminName );
                }

                ZChatOutput( szOutput, ZChat::CMT_SYSTEM );
            }
            break; 

Open(MSharedCommandTable.cpp)

    C(MC_MUTE_ALL, "Admin.MuteAll", "", MCDT_MACHINE2MACHINE)
            P(MPT_STR, "AdminName")
            P(MPT_INT, "Value") 
            
Open(MSharedCommandTable.h)

    #define MC_MUTE_ALL    XXXXX //Replace the XXXXX by the following code in the list

Open(ZCharacter.h - ZCharacterStatus)

    int            bMuteAll; 

Find(ZCharacterStatus())

    bMuteAll(0) 

Open(ZPost.h)

    if(ZGetGame()->m_pMyCharacter->GetStatus().Ref().bMuteAll){
            return;
        } 
