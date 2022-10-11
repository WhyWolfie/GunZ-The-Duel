Open(ZChat_cmds.cpp) <br>
Find <br>
Part 1

    void ChatCmd_Damaged(const char* line, const int argc, char **const argv); 

Part 2

    _CC_AC("Damage", &ChatCmd_Damaged, CCF_ALL, ARGVNoMin, ARGVNoMax, true,"/Damage", ""); 


Part 3

    void ChatCmd_Damaged(const char* line, const int argc, char **const argv)
    {
        GunzState state = ZApplication::GetGameInterface()->GetState();
        ZMyCharacter* m_pMyCharacter = ZGetGame()->m_pMyCharacter;
        ZCharacterStatus dInfo = m_pMyCharacter->GetStatus().Ref();

        char szPrint[256];

        if(state == GUNZ_GAME)
        {
            sprintf(szPrint, "Damage Done: %i / Damage Received: %i", dInfo.nDamageCaused, dInfo.nDamageTaken);
            ZApplication::GetGameInterface()->GetChat()->Input(szPrint);
        }
    } 
