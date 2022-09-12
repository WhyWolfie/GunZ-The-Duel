Hi! I'm bringing another easy fix for you guys (I seem to be getting good at those, huh). <br>

Some of you may remember that back in the '05 and maybe '08 clients we used to be able to use the taunt commands even after the round was over. So, if you killed the last guy on the other team and won the Clan War, you could laugh at his corpse and be a douche. Well, I found the code that prevented this from happening in 1.5 and I'd like to share it with you guys.<br>

Tbh I don't use this, but my friends like making fun of each other and they also enjoy blasting their ego here and there, so...<br>

Open Gunz solution, then Game -> ZGame.cpp.<br>
Find <br>

    void ZGame::PostSpMotion(ZC_SPMOTION_TYPE mtype){
        if(m_pMyCharacter==NULL) return;
        if(m_Match.GetRoundState() != MMATCH_ROUNDSTATE_PLAY) return;
        
Change <br>

    void ZGame::PostSpMotion(ZC_SPMOTION_TYPE mtype){
        if(m_pMyCharacter==NULL) return;
        if(m_Match.GetRoundState() != MMATCH_ROUNDSTATE_PLAY && m_Match.GetRoundState() != MMATCH_ROUNDSTATE_FINISH) return;
        
