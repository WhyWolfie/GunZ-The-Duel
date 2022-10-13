Open(MSharedCommandTable.h)

    #define MC_MATCH_REQUEST_RANDOM_WEAPON			50018	//put your packet number
    #define MC_MATCH_RESPONSE_RANDOM_WEAPON			50019	//same
    
Open(MSharedCommandTable.cpp)

    C( MC_MATCH_REQUEST_RANDOM_WEAPON, "Match.Request.Random.Weapon", "Request Random Weapon.", MCDT_MACHINE2MACHINE )
        P( MPT_UID, "uidPlayer" )

    C( MC_MATCH_RESPONSE_RANDOM_WEAPON, "Match.Response.Random.Weapon", "Response Random Weapon.", MCDT_MACHINE2MACHINE )
        P( MPT_UID, "uidPlayer" )
        
Open(ZPost.h)

    inline void ZPostRequestRandomWeapon( const MUID& uidPlayer )
    {
        ZPOSTCMD1( MC_MATCH_REQUEST_RANDOM_WEAPON, MCmdParamUID(uidPlayer) );
    }
    

Open(ZCharacter.h)

    //in the public part of class ZCharacter : public ZCharacterObject add:
    void InitPropertiesGunGame();

Open(ZCharacter.cpp)


    void ZCharacter::InitPropertiesGunGame()
    {
      for (int i = 0; i < MMCIP_END; i++) 
      {
        m_Items.EquipItem(MMatchCharItemParts(i),  GetCharInfo()->nEquipedItemDesc[i],  GetCharInfo()->nEquipedItemCount[i]);
      }

      srand(time(NULL));
      const long numbersrange[16] = {506003, 504007, 506010, 506001, 507002, 509002, 509004, 505005, 509006, 650019, 9999965, 9999969, 9999968, 506017, 4515, 5010};
      const long numbersmelee[7] = {300017, 300021, 500004, 502011, 502017, 9999962, 9999970};

      m_Items.EquipItem(MMCIP_MELEE, numbersmelee[rand() % 7], 1);
      m_Items.EquipItem(MMCIP_PRIMARY, numbersrange[rand() % 16], 1);
      m_Items.EquipItem(MMCIP_SECONDARY, numbersrange[rand() % 16], 1);
    }
    

Open(ZGameClient.h) 

    void OnResponseRandomWeapon( const MUID& uidPlayer );

Open(ZGameClient.cpp)

    void ZGameClient::OnResponseRandomWeapon(const MUID& uidPlayer)
    {
      ZCharacterManager* pCharMgr = ZGetCharacterManager();
      ZCharacter* pChar = pCharMgr->Find(uidPlayer);
      if (pChar == NULL) return;

      pChar->InitPropertiesGunGame();

      char szText[ 256];
      sprintf( szText, "%s has obtained a new weapon", pChar->GetCharInfo()->szName);
      ZChatOutput( MCOLOR(ZCOLOR_GAME_INFO), szText );
    }


Open(ZGameClient_OnCommand.cpp)

    case MC_MATCH_RESPONSE_RANDOM_WEAPON:
      {
        MUID uid;
        pCommand->GetParameter(&uid, 0, MPT_UID);
        OnResponseRandomWeapon(uid);
      }
      break;

Open(MMatchServer.h)

    void OnRequestRandomWeapon( const MUID& uidPlayer );
    
Open(MMatchServer.cpp)


    void MMatchServer::OnRequestRandomWeapon( const MUID& uidPlayer )
    {
      MMatchObject* pObject = GetObject( uidPlayer );
      if( pObject )
      {
        MCommand* pCmd = CreateCommand( MC_MATCH_RESPONSE_RANDOM_WEAPON, pObject->GetUID() );

        if( pCmd )
        {
          pCmd->AddParameter( new MCmdParamUID( uidPlayer ) );
          MMatchServer::GetInstance()->RouteToBattle( pObject->GetStageUID(), pCmd );
        }
      }
    }
    

Open(MMatchServer_OnCommand.cpp)


    case MC_MATCH_REQUEST_RANDOM_WEAPON:
      {
        MUID uidPlayer;

        pCommand->GetParameter( &uidPlayer, 0, MPT_UID );

        OnRequestRandomWeapon( uidPlayer );
      }
      break;

    
    
    


