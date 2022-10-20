Open(ZChat_Cmds.cpp) <br>

    void ChatCmd_Alive(const char* line, const int argc, char **const argv);

Part 2

	_CC_AC("alive",                &ChatCmd_Alive,                    CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/alive", "");  

Part 3

    void ChatCmd_Alive(const char* line, const int argc, char **const argv)
    {
        int nPlayers = 0;
        for (ZCharacterManager::iterator itor = ZGetGame()->m_CharacterManager.begin(); itor != ZGetGame()->m_CharacterManager.end(); ++itor)
        {
            ZCharacter* pCharacter = (*itor).second;
            if(ZGetGame()->GetMatch()->IsTeamPlay())
            {
                if( !pCharacter->IsDie() && pCharacter->GetTeamID() != ZGetGame()->m_pMyCharacter->GetTeamID() )
                {
                    ++nPlayers;
                }
            }
            else if( !pCharacter->IsDie() && pCharacter != ZGetGame()->m_pMyCharacter )
            {
                ++nPlayers;
            }
        }

        char szPlayers[35];
        sprintf( szPlayers, "%d players are alive.", nPlayers);
        ZChatOutput(szPlayers, ZChat::CMT_SYSTEM);
    }



