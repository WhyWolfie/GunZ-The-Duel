Open(ZGame.cpp) <br>

    if ( ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_DUEL)    
    {
           if ( !m_pMyCharacter->IsDie() && pChar->IsDie())
             {
                       ChatColor = MCOLOR(0xFF808080);
            strcpy( szMsg, "^0. . . . .")
              }
    } 
    
Replace <br>

    /*if ( ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_DUEL)    
    {
           if ( !m_pMyCharacter->IsDie() && pChar->IsDie())
             {
                       ChatColor = MCOLOR(0xFF808080);
            strcpy( szMsg, "^0. . . . .")
              }
    }*/ 
    
Credits to Nick.
