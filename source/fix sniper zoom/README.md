Open (ZMyCharacter.cpp) and find: ZMyCharacter::OnGadget_Snifer()

    void ZMyCharacter::OnGadget_Snifer()
        {
        ZMyCharaterStatusBitPacking & zStatus = m_statusFlags.Ref();


        zStatus.m_bSniferMode = !zStatus.m_bSniferMode;


        ZCombatInterface* ci=ZGetCombatInterface();
        if (ci)
        {
            if (zStatus.m_bSniferMode)
            {
                ci->OnGadget(MWT_SNIFER);
            }
            else
            {
                ci->OnGadgetOff();
            }
        }

    }
    
And replace with this code
   
    unsigned long g_dwLastSniperUpdate = 0;

    void ZMyCharacter::OnGadget_Snifer()
    {
        unsigned long dwTime = timeGetTime();

        if (g_dwLastSniperUpdate == 0 || g_dwLastSniperUpdate <= (dwTime - 200))
        {
            ZMyCharaterStatusBitPacking & zStatus = m_statusFlags.Ref();

            zStatus.m_bSniferMode = !zStatus.m_bSniferMode;

            ZCombatInterface* ci=ZGetCombatInterface();

            if (ci)
            {
                if (zStatus.m_bSniferMode)
                {
                    ci->OnGadget(MWT_SNIFER);
                }
                else
                {
                    ci->OnGadgetOff();
                }
            }    

            g_dwLastSniperUpdate = dwTime;
        }
    }
   
