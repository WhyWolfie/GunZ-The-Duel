Open(ZGameInterface.cpp) <br>
Find

    #ifdef LOCALE_KOREA
      if ( timeGetTime() >= m_dwTimeCount)
      {
        m_dwTimeCount += 3600000;
        m_dwHourCount++;

        char szText[ 256];
        if ( m_dwHourCount > 3)
          sprintf( szText, "%d ½Ã°£ÀÌ °æ°úÇß½À´Ï´Ù. Àá½Ã ÈÞ½ÄÀ» ÃëÇÏ½Ã±â ¹Ù¶ø´Ï´Ù.", m_dwHourCount);
        else
          sprintf( szText, "%d ½Ã°£ÀÌ °æ°ú ÇÏ¿´½À´Ï´Ù.", m_dwHourCount);
        ZChatOutput( MCOLOR(ZCOLOR_CHAT_SYSTEM), szText);


        ZChatOutput( MCOLOR(ZCOLOR_CHAT_SYSTEM), "º» °ÔÀÓÀº 15¼¼ ÀÌ¿ë°¡·Î¼­ ¸¸ 15¼¼ ¹Ì¸¸Àº ÀÌ¿ëÇÒ ¼ö ¾ø½À´Ï´Ù.");
      }
    #endif

      __EP(11);
    }

Change too

    #ifdef LOCALE_KOREA
      if ( timeGetTime() >= m_dwTimeCount)
      {
        m_dwTimeCount += 3600000;
        m_dwHourCount++;

        char szText[ 256];
        if ( m_dwHourCount > 3)
          sprintf( szText, "^4I hope you enjoy Gunz", m_dwHourCount);
        else
          sprintf( szText, "^4Welcome to Gunz.", m_dwHourCount);
        ZChatOutput( MCOLOR(ZCOLOR_CHAT_SYSTEM), szText);
      }
    #endif

      __EP(11);
    }

    
