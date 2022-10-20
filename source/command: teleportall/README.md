Open(ZChat_Cmds.cpp) <br>

    void ChatCmd_AdminOverHereAll(const char* line, const int argc, char **const argv);

Part 2

	_CC_AC("tpall",        &ChatCmd_AdminOverHereAll,        CCF_ADMIN, ARGVNoMin,-1 , true,"/tpall", "");

Part 3

    void ChatCmd_AdminOverHereAll(const char* line, const int argc, char **const argv)
    {
        if( !ZGetGame() )
        {
            ZChatOutput("You're not in game.", ZChat::CMT_SYSTEM);
            return;
        }

        ZPOSTCMD1(MC_OVERHERE_ALL, MCmdParamStr(""));
    }


Open(MSharedCommandTable.h) <br>

    #define MC_OVERHERE_ALL                         50025
    
Open(MMatchServer_OnCommand.cpp) <br>

	case MC_OVERHERE_ALL:
            {
                
                char szAdminName[128] = "";

                if (!pCommand->GetParameter( szAdminName, 0, MPT_STR )) break;

                MMatchObject* pObj = GetObjectA(pCommand->GetSenderUID());
                
                if (pObj == NULL) break;
                if(!IsAdminGrade(pObj)) break;

                MCommand* pCmd = CreateCommand(MC_OVERHERE_ALL, MUID(0,0));
                pCmd->AddParameter(new MCmdParamStr(pObj->GetName()));
                RouteToStage(pObj->GetStageUID(), pCmd);

                Announce( pObj->GetUID(), "Room teleported to your position." );
            }
            break;

Open(MSharedCommandTable.cpp) <br>

    C(MC_OVERHERE_ALL, "Admin.OverHereAll", "", MCDT_MACHINE2MACHINE)
        P(MPT_STR, "AdminName")	


Open(ZGameClient_OnCommand.cpp)

	    case MC_OVERHERE_ALL:
            {
                char szAdminName[128] = "";
                char szOutput[512] = "";

                if( ZGetMyInfo()->IsAdminGrade() ) break;

                pCommand->GetParameter(szAdminName, 0, MPT_STR, sizeof(szAdminName) );

                ZCharacterManager *pZCharacterManager = ZGetCharacterManager();
    
                if (pZCharacterManager != NULL) 
                {
                    for (ZCharacterManager::iterator itor = pZCharacterManager->begin(); itor != pZCharacterManager->end(); ++itor) 
                    {
                        ZCharacter* pCharacter = (*itor).second; 

                        if (!strcmp(pCharacter->GetProperty()->GetName(), szAdminName))
                            ZGetGame()->m_pMyCharacter->SetPosition(pCharacter->GetPosition());
                    }
                }
            

                ZChatOutput("Room has been teleport by staff.");
            }
            break;



    
