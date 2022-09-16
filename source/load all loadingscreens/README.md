Find <br>

    bool ZGameInterface::OnGameCreate(void) 
    
     switch ( nBitmap)
      {
          case ( 0) :
              strcpy( szFileName, "Interface/Default/LOADING/loading_dash.jpg");
              break;
          case ( 1) :
              strcpy( szFileName, "Interface/Default/LOADING/loading_gaurd.jpg");
              break;
          case ( 2) :
              strcpy( szFileName, "Interface/Default/LOADING/loading_ksa.jpg");
              break;
          case ( 3) :
              strcpy( szFileName, "Interface/Default/LOADING/loading_safefall.jpg");
              break;
          case ( 4) :
              strcpy( szFileName, "Interface/Default/LOADING/loading_tumbling.jpg");
              break;
          case ( 5) :
              strcpy( szFileName, "Interface/Default/LOADING/loading_wallhang.jpg");
              break;
          case ( 6) :
              strcpy( szFileName, "Interface/Default/LOADING/loading_walljump.jpg");
              break;
          case ( 7) :
              strcpy( szFileName, "Interface/Default/LOADING/loading_wallrun01.jpg");
              break;
          case ( 8) :
              strcpy( szFileName, "Interface/Default/LOADING/loading_wallrun02.jpg");
              break;
          default :
              strcpy( szFileName, "");
              break;
      }
      switch ( rand() % 3)
      {
      case ( 0) :
          strcpy( szFileName, "Interface/Default/LOADING/loading_1.jpg");
          break;
      case ( 1) :
          strcpy( szFileName, "Interface/Default/LOADING/loading_2.jpg");
          break;
      case ( 2) :
          strcpy( szFileName, "Interface/Default/LOADING/loading_3.jpg");
          break;
      }
      } 
      
Replace with <br>

    /*    switch ( nBitmap)
        {
            case ( 0) :
                strcpy( szFileName, "Interface/Default/LOADING/loading_dash.jpg");
                break;
            case ( 1) :
                strcpy( szFileName, "Interface/Default/LOADING/loading_gaurd.jpg");
                break;
            case ( 2) :
                strcpy( szFileName, "Interface/Default/LOADING/loading_ksa.jpg");
                break;
            case ( 3) :
                strcpy( szFileName, "Interface/Default/LOADING/loading_safefall.jpg");
                break;
            case ( 4) :
                strcpy( szFileName, "Interface/Default/LOADING/loading_tumbling.jpg");
                break;
            case ( 5) :
                strcpy( szFileName, "Interface/Default/LOADING/loading_wallhang.jpg");
                break;
            case ( 6) :
                strcpy( szFileName, "Interface/Default/LOADING/loading_walljump.jpg");
                break;
            case ( 7) :
                strcpy( szFileName, "Interface/Default/LOADING/loading_wallrun01.jpg");
                break;
            case ( 8) :
                strcpy( szFileName, "Interface/Default/LOADING/loading_wallrun02.jpg");
                break;
            default :
                strcpy( szFileName, "");
                break;
        }
        switch ( rand() % 3)
        {
        case ( 0) :
            strcpy( szFileName, "Interface/Default/LOADING/loading_1.jpg");
            break;
        case ( 1) :
            strcpy( szFileName, "Interface/Default/LOADING/loading_2.jpg");
            break;
        case ( 2) :
            strcpy( szFileName, "Interface/Default/LOADING/loading_3.jpg");
            break;
        }*/

        strcpy( szFileName, "Interface/Default/LOADING/loading_" );
        strcat( szFileName, ZGetGameClient()->GetMatchStageSetting()->GetMapName() );
        strcat( szFileName, ".jpg" ); 
