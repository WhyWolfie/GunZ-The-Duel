<b> Simple LevelUp Sound </b><br>

I know its so simple.

ZGameClient.cpp:

find "void ZGameClient::OnGameLevelUp"

replace

    if (ZGetGame())
    {
        ZCharacter* pCharacter = ZGetGame()->m_CharacterManager.Find(uidChar);
        if (pCharacter) {
            pCharacter->LevelUp();

            char temp[256] = "";
            ZTransMsg(temp, MSG_GAME_LEVEL_UP, 1, pCharacter->GetUserAndClanName());
            ZChatOutput(MCOLOR(ZCOLOR_GAME_INFO), temp);
        }
    } 
    
with

    if (ZGetGame())
    {
        ZCharacter* pCharacter = ZGetGame()->m_CharacterManager.Find(uidChar);
        if (pCharacter) {
            pCharacter->LevelUp();

            char temp[256] = "";
            ZTransMsg(temp, MSG_GAME_LEVEL_UP, 1, pCharacter->GetUserAndClanName());
            ZChatOutput(MCOLOR(ZCOLOR_GAME_INFO), temp);
            ZGetSoundEngine()->PlaySound( "nar/level_up", pCharacter->GetPosition()); //Levelup sound
        }
    } 
    
    
    
Credits to: skhan
