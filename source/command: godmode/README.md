Command: Godmode <br>

Open(ZChat_Cmds.cpp) <br>

    void ChatCmd_GOD(const char* line, const int argc, char **const argv);

Part 2

	_CC_AC("god",                     &ChatCmd_GOD,                           CCF_ADMIN|CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/god", "");

Part 3

    void ChatCmd_GOD(const char* line, const int argc, char **const arv)
    {
        GunzState state = ZApplication::GetGameInterface()->GetState();
        ZCharacter* pCharacter = ZGetGame()->m_pMyCharacter;

        char szMsg[256];

        if(state == GUNZ_GAME)
        {
            if(pCharacter->GetStatus().Ref().isGOD == 0)
            {
                pCharacter->GetStatus().CheckCrc();
                pCharacter->GetStatus().Ref().isGOD = 1;
                pCharacter->GetStatus().MakeCrc();
                sprintf(szMsg, "^1God mode enabled!");
            }
            else if(pCharacter->GetStatus().Ref().isGOD == 1)
            {
                pCharacter->GetStatus().CheckCrc();
                pCharacter->GetStatus().Ref().isGOD = 0;
                pCharacter->GetStatus().MakeCrc();
                sprintf(szMsg, "^1God mode disabled!");
            }
        }
        else
        {
            sprintf(szMsg, "^1You must be in-game!");
        }
            ZChatOutput(szMsg);
    }

Open(ZCharacter.h - ZCharacterStatus) <br>

    int         isGOD;

Part 2

    isGOD(0),


Open(Zmodule_HPAP.cpp - ZModule_HPAP::OnDamage)

	if(uidAttacker.Low == ZGetGame()->m_pMyCharacter->GetLastAttacker().Low)
    {
        ZCharacter* pCharacter = ZGetGame()->m_pMyCharacter;
        if(pCharacter->GetStatus().Ref().isGOD == 1) return;
    }
