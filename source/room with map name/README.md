Open(ZRoomListBox.cpp) <br>
Find <br>

    void ZRoomListBox::OnDraw( MDrawContext* pDC )
    
Replace <br>

    void ZRoomListBox::OnDraw( MDrawContext* pDC )
    {
      MBitmap* pBitmap;
      MRECT		rect;
      map<string, MBitmap*>::iterator iter;
      map<MMATCH_GAMETYPE, MBitmap*>::iterator iterIcon;
      int pressed_reposition = 0;

      int index = 0;

      for( int i = 0; i < NUM_DISPLAY_ROOM; ++i )
      {
        bool	bRoomFull = false;

        if( m_Selection == i )			pressed_reposition = 1; 
        else							pressed_reposition = 0;

        const char*	mapName = MGetMapDescMgr()->GetBannerName( m_pMapInfo[i].map_name);
        if( m_pMapInfo[i].IsEmpty )
        {
          continue;
        }
        rect = GetInitialClientRect();

        int width  = (int)( m_iGapWidth + ( m_RoomWidth + m_iGapWidth*2 + m_iGapCenter ) * ( index%2 ) );
        int height = (int)( m_iGapHeight + ( m_RoomHeight + m_iGapHeight ) * (int)(index*0.5f));

        if( m_pMapInfo[i].nPeople >= m_pMapInfo[i].nMaxPeople )
        {
          bRoomFull = true;
        }

        iter = find_if( m_pMapImage.begin(), m_pMapImage.end(), string_key_equal<string, MBitmap*>(mapName));
        if( iter != m_pMapImage.end() )
        {
          pBitmap	= iter->second;
          if( pBitmap != 0 )
          {
          if( ( m_pMapInfo[i].roomState == GMAE_CLOSED ) || bRoomFull )	
            pDC->SetBitmapColor(125,125,125,255);
          else					
            pDC->SetBitmapColor(255,255,255,255);

          pDC->SetBitmap( pBitmap ); 
          pDC->Draw( width + pressed_reposition, height + pressed_reposition, m_RoomWidth, m_RoomHeight );
        }

        if(m_pRoomFrame!=0)
        {
          pDC->SetBitmap(m_pRoomFrame);
          pDC->Draw(width + pressed_reposition, height + pressed_reposition, m_RoomWidth * 0.75, m_RoomHeight, 0, 0, 512, 32 );
        }
      }


      // infomation ±×¸®±â
      char szBuf[128];
      MRECT r;

      // ¹æ¹øÈ£
      r.x = width + m_RoomWidth*0.01f	+ pressed_reposition;
      r.y = height + m_RoomHeight*0.1f + pressed_reposition;
      r.w = m_RoomWidth*0.1;
      r.h = m_RoomHeight *0.5;
        sprintf(szBuf,"%03d", m_pMapInfo[i].RoomNumber);

      pDC->SetFont( MFontManager::Get("FONTc8b") );
      pDC->SetColor( 0,0,0);
      pDC->Text( MRECT( r.x+1, r.y+1, r.w, r.h), szBuf);
      if(  m_pMapInfo[i].roomState == GMAE_CLOSED || bRoomFull )
        pDC->SetColor( 115,146,173 );
      else
        pDC->SetColor( 181, 247, 66 );
      pDC->Text( r, szBuf );

      // ÀÎ¿ø¼ö
      r.x = width + m_RoomWidth*0.01f + pressed_reposition;
      r.y = height + m_RoomHeight*0.5f + pressed_reposition;
      r.w = m_RoomWidth*0.1f;
      r.h = m_RoomHeight*0.5f;
      sprintf(szBuf,"%d/%d", m_pMapInfo[i].nPeople, m_pMapInfo[i].nMaxPeople );

      pDC->SetColor( 0,0,0);
      pDC->Text( MRECT( r.x+1, r.y+1, r.w, r.h), szBuf);
      if(  m_pMapInfo[i].roomState == GMAE_CLOSED || bRoomFull )
        pDC->SetColor( 115,146,173 );
      else
        pDC->SetColor( 181, 247, 66 );
      pDC->Text( r, szBuf );

      pDC->SetFont(MFontManager::Get("FONTc8b"));
      r.x = width + m_RoomWidth*0.12 + pressed_reposition;
      r.y = height - m_RoomHeight*0.15 + pressed_reposition;
      r.w = m_RoomWidth*0.75;
      r.h = m_RoomHeight/**0.85*/;

      MFont * pFont = pDC->GetFont();
      char szBufTemp[SMI_MAPNAME_LENGTH];
      int strLength = 0;
      int RoomWidth = pFont->GetWidth(m_pMapInfo[i].room_name);
      if (RoomWidth > m_RoomWidth*0.7)
      {
        while (strLength < 29)
        {
          if (m_pMapInfo[i].map_name[strLength] == '0') // ÀÌ¸§ÀÇ ³¡
            strcpy(szBufTemp, m_pMapInfo[i].room_name);
          if (((unsigned char)m_pMapInfo[i].room_name[strLength]) > 127)
            strLength += 2;
          else
            ++strLength;
        }
        strncpy(szBufTemp, m_pMapInfo[i].room_name, strLength*sizeof(char));
        szBufTemp[strLength] = '\0';
        strcat(szBufTemp, "...");

        pDC->SetColor(0, 0, 0);
        pDC->Text(MRECT(r.x + 1, r.y + 1, r.w, r.h), szBufTemp, MAM_LEFT);
        if (m_pMapInfo[i].roomState == GMAE_CLOSED || bRoomFull)
          pDC->SetColor(115, 146, 173);
        else
          pDC->SetColor(255, 255, 255);
        pDC->Text(r, szBufTemp, MAM_LEFT);
      }
      else
      {
        pDC->SetColor(0, 0, 0);
        pDC->Text(MRECT(r.x + 1, r.y + 1, r.w, r.h), m_pMapInfo[i].room_name, MAM_LEFT);
        if (m_pMapInfo[i].roomState == GMAE_CLOSED || bRoomFull)
          pDC->SetColor(115, 146, 173);
        else
          pDC->SetColor(255, 255, 255);
        pDC->Text(r, m_pMapInfo[i].room_name, MAM_LEFT);
      }

      // ¹æ ÀÌ¸§
      pDC->SetFont(MFontManager::Get("FONTc8b"));
      r.x = width + m_RoomWidth*0.12 + pressed_reposition;
      r.y = height + m_RoomHeight*0.2 + pressed_reposition;
      r.w = m_RoomWidth*0.75;
      r.h = m_RoomHeight/**0.85*/;

      int RoomWidth1 = pFont->GetWidth(m_pMapInfo[i].map_name);
      if (RoomWidth1 > m_RoomWidth*0.7)
      {
        while (strLength < 29)
        {
          if (m_pMapInfo[i].map_name[strLength] == '0') // ÀÌ¸§ÀÇ ³¡
            strcpy(szBufTemp, m_pMapInfo[i].map_name);
          if (((unsigned char)m_pMapInfo[i].map_name[strLength]) > 127)
            strLength += 2;
          else
            ++strLength;
        }
        strncpy(szBufTemp, m_pMapInfo[i].map_name, strLength*sizeof(char));
        szBufTemp[strLength] = '\0';
        strcat(szBufTemp, "...");

        pDC->SetColor(0, 0, 0);
        pDC->Text(MRECT(r.x + 1, r.y + 1, r.w, r.h), szBufTemp, MAM_LEFT);
        if (m_pMapInfo[i].roomState == GMAE_CLOSED || bRoomFull)
          pDC->SetColor(115, 146, 173);
        else
          pDC->SetColor(255, 255, 255);
        pDC->Text(r, szBufTemp, MAM_LEFT);
      }
      else
      {
        pDC->SetColor(0, 0, 0);
        pDC->Text(MRECT(r.x + 1, r.y + 1, r.w, r.h), m_pMapInfo[i].map_name, MAM_LEFT);
        if (m_pMapInfo[i].roomState == GMAE_CLOSED || bRoomFull)
          pDC->SetColor(115, 146, 173);
        else
          pDC->SetColor(255, 255, 255);
        pDC->Text(r, m_pMapInfo[i].map_name, MAM_LEFT);
      }


      //·¹º§Á¦ÇÑ
      r.x = width + m_RoomWidth*0.75f + pressed_reposition;
      r.y = height + pressed_reposition;
      r.w = m_RoomWidth * 0.2f ;
      r.h = m_RoomHeight;

      if( m_pMapInfo[i].bLimitLevel )
      {
        char szBufTemp[64];
        sprintf( szBufTemp, "%d~%d", max(m_pMapInfo[i].nMasterLevel - m_pMapInfo[i].nLimitLevel,1), m_pMapInfo[i].nMasterLevel + m_pMapInfo[i].nLimitLevel);

        pDC->SetColor( 0,0,0);
        pDC->Text( MRECT( r.x+1, r.y+1, r.w, r.h), szBufTemp);
        if( m_pMapInfo[i].roomState == GMAE_CLOSED || bRoomFull )
          pDC->SetColor( 100, 100, 100 );
        else
          pDC->SetColor( 181, 247, 66 );
        pDC->Text( r, szBufTemp );
      }

      if (m_pMapInfo[i].bPrivate)
      {
        // ºñ¹Ð¹æÀÌ¸é °ÔÀÓ¸ðµå ¾ÆÀÌÄÜ´ë½Å ¿­¼è¾ÆÀÌÄÜÀÌ ³ª¿Â´Ù.
        // ¿­¼è¾ÆÀÌÄÜÀº ÇÏµåÄÚµåµÊ. ³ªÁß¿¡ ÀÏ¹ÝÈ­ÇØ¼­ xml·Î »©³ö¾ßÇÒ µí..

        #define FN_ROOMLIST_PRIVATE_KEY		"in_key.png"
        pBitmap = MBitmapManager::Get(FN_ROOMLIST_PRIVATE_KEY);
        if (pBitmap != NULL) 
        {
          float x, y;
          x = width + m_RoomWidth*0.9 + pressed_reposition;
          y = height + pressed_reposition + ((m_RoomHeight-pBitmap->GetHeight())/2);
          pDC->SetBitmap( pBitmap );
          pDC->Draw(x, y, pBitmap->GetWidth(), pBitmap->GetHeight());
        }
      }
      else
      {
        iterIcon = m_pIconImage.find( m_pMapInfo[i].nGame_Type );
        if( iterIcon != m_pIconImage.end() )
        {
          pBitmap = iterIcon->second;
          if( pBitmap != 0)
          {
            r.x = width + m_RoomWidth*0.9 + pressed_reposition;
            r.y = height + m_RoomHeight/4.7 + pressed_reposition;

            // ¾ÆÀÌÄÜ
            if( m_pMapInfo[i].roomState == GMAE_CLOSED || bRoomFull )
            {
              pDC->SetBitmapColor(100,100,100,100);
            }
            else
            {
                pDC->SetBitmapColor(255,255,255,255);
            }

            pDC->SetBitmap( pBitmap );
            pDC->Draw(r.x, height + pressed_reposition, m_RoomHeight, m_RoomHeight);
          }			
        }
      }


      // ÇÃ·¹ÀÌ ÁßÀÌ¸é ÇÃ·¹ÀÌ ¾ÆÀÌÄÜÀ» Ç¥½ÃÇÑ´Ù.
      if ( m_pMapInfo[i].roomState == GAME_PLAYING)
      {
        // ¿ª½Ã ÇÃ·¹ÀÌ ¾ÆÀÌÄÜµµ ÇÏµåÄÚµù... -_-;
        #define FN_ROOMLIST_PLAYICON		"icon_play.tga"
        pBitmap = MBitmapManager::Get( FN_ROOMLIST_PLAYICON);
        if (pBitmap != NULL) 
        {
          float x, y;
          x = width  + (m_RoomWidth  * 0.955) + pressed_reposition;
          y = height + (m_RoomHeight * 0.54)  + pressed_reposition;
          pDC->SetBitmap( pBitmap );
          pDC->Draw(x, y, (m_RoomHeight * 0.5), (m_RoomHeight * 0.5));
        }
      }

      //¿Ó±¸(Å×µÎ¸®)
      if( i == m_Selection)
      {
        if( m_pMapInfo[i].roomState == GMAE_CLOSED || bRoomFull) pDC->SetColor(115,146,173);
        else pDC->SetColor( 181, 247, 66 );
      }
      else pDC->SetColor(128,128,128,255);
      pDC->Rectangle(width+pressed_reposition, height+pressed_reposition, m_RoomWidth, m_RoomHeight );

      ++index;
    }
    pDC->SetOpacity( 255 );
    pDC->SetBitmapColor(255,255,255,255);
    }












