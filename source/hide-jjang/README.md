<b>Hide JJang</b><br>
This code is used for nothing else to hide the jjang in the game, obviously it will not be removed forever, it will only hide it for a while, you can activate or deactivate it whenever you want.

Includes sound effects when activating the command.

Change

    if (!ZGetMyInfo()->IsEventGrade())
    {
    //return;
    }

replace

    if (ZGetMyInfo()->GetUGradeID() == MMUG_STAR)
    {
    //return;
    }

struct ZCharacterStatus add these

ZCharacter.h

    int isJjang;

    isJjang(0), 
    
ZChat_Cmds.cpp

    void ChatCmd_HideJjangJork(const char* line, const int argc, char** const argv); 


    _CC_AC("hj",                   &ChatCmd_HideJjangJork,         CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/hj", ""); 
    

    void ChatCmd_HideJjangJork(const char* line, const int argc, char** const argv)
    {
        char szMsg[256];
        if (!ZGetMyInfo()->IsEventGrade())
        {
            //return;
        }
        if (ZGetGame()->m_pMyCharacter->GetStatus().Ref().isJjang == 0)
        {
            ZGetGame()->m_pMyCharacter->GetStatus().CheckCrc();
            ZGetGame()->m_pMyCharacter->GetStatus().Ref().isJjang = 1;
            ZGetGame()->m_pMyCharacter->GetStatus().MakeCrc();
            ZGetEffectManager()->Clear();
            ZGetSoundEngine()->PlaySound("fx_whoosh02");
            sprintf(szMsg, "^2Hide Jjang: Off");
        }
        else if (ZGetGame()->m_pMyCharacter->GetStatus().Ref().isJjang == 1)
        {
            ZGetGame()->m_pMyCharacter->GetStatus().CheckCrc();
            ZGetGame()->m_pMyCharacter->GetStatus().Ref().isJjang = 0;
            ZGetGame()->m_pMyCharacter->GetStatus().MakeCrc();
            if (ZGetGame())
                ZGetGame()->GetJjang();
            ZGetSoundEngine()->PlaySound("fx_whoosh02");
            sprintf(szMsg, "^1Hide Jjang: On");
        }
        ZChatOutput(szMsg);
    } 
    
Credits to: Jorklenis2 (preview: https://streamable.com/pu1m74)
