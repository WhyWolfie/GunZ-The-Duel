<b>Live Player in the event channel </b><br>
![orby](https://i.imgur.com/TqjCeqf.jpg)

Since I was there these days I decided to make this contribution, I made this code for you to add in your sources.
This code shows when live players are inside the room.
Making it even easier for you who likes to give event.

Go to ZCombatInterface.cpp

    Alive(pDC);


    void ZCombatInterface::Alive(MDrawContext* pDC)
    {
        ZCharacter* pCharacter = GetTargetCharacter();

        if (pCharacter == NULL || pCharacter->IsObserverTarget())
            return;

        char szAlive[64]; // alive
        pDC->SetFont(GetGameFont()); // default font
        pDC->SetColor(MCOLOR(255, 255, 255)); // color

        if (strstr(ZGetGameClient()->GetChannelName(), "Channel (Event)") && ZGetMyInfo()->IsAdminGrade()) // channel
        {
            int nPlayers = 0;
            for (ZCharacterManager::iterator itor = ZGetGame()->m_CharacterManager.begin(); itor != ZGetGame()->m_CharacterManager.end(); ++itor)
            {
                ZCharacter* pCharacter = (*itor).second;
                if (ZGetGame()->GetMatch()->IsTeamPlay())
                {
                    if (!pCharacter->IsDie() && pCharacter->GetTeamID() != ZGetGame()->m_pMyCharacter->GetTeamID())
                    {
                        ++nPlayers;
                    }
                }
                else if (!pCharacter->IsDie() && pCharacter != ZGetGame()->m_pMyCharacter)
                {
                    ++nPlayers;
                }
            }
            sprintf(szAlive, "%d Live players in the room", nPlayers);
            TextRelative(pDC, 10.f / 800.f, 100.f / 600.f, szAlive);
        }
    }
    
    
    
Go to ZCombatInterface.h

    void         Alive(MDrawContext* pDC);


Credits to Orby
