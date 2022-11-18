Open(ZChat_Cmds.cpp)

    void ChatCmd_AdminSlap(const char* line, const int argc, char **const argv);

Part 2

	_CC_AC("admin_slap", &ChatCmd_AdminSlap, CCF_ADMIN | CCF_GAME, 1, ARGVNoMax, true, "/admin_slap","");


Part 3

    void ChatCmd_AdminSlap(const char* line, const int argc, char **const argv)
    {

      if (!ZGetGame())
        return;

      if (argc < 2)
      {
        ZChatOutput("Usage: /admin_slap <player>", ZChat::CMT_SYSTEM);
        return;
      }

      if (!ZGetMyInfo()->IsAdminGrade())
        return;

      char* targetName = argv[1];

      if (_stricmp(targetName, "all") == 0)
      {
        for (auto itor = ZGetCharacterManager()->begin(); itor != ZGetCharacterManager()->end(); ++itor)
        {
          ZCharacter* player = (ZCharacter*)(*itor).second;
          if (player->GetUID() == ZGetGame()->m_pMyCharacter->GetUID())
            continue;

          ZPostAdminRequestSlap(ZGetMyUID(), player->GetUID());
        }
      }
      else
      {
        for (auto itor = ZGetCharacterManager()->begin(); itor != ZGetCharacterManager()->end(); ++itor)
        {
          ZCharacter* player = (ZCharacter*)(*itor).second;
          if (_stricmp(player->GetUserName(), targetName) == 0)
          {
            ZPostAdminRequestSlap(ZGetMyUID(), player->GetUID());
          }
        }
      }
    }

Open(ZPost.h)

    inline void ZPostAdminRequestSlap(const MUID& admin, const MUID& target)
    {
      ZPOSTCMD2(MC_ADMIN_REQUEST_SLAP, MCmdParamUID(admin), MCmdParamUID(target));
    }


Open(MSharedCommandTable.h)

    #define MC_ADMIN_REQUEST_SLAP					50066

Open(MMatchServer_Admin.cpp)

    void MMatchServer::OnResponseAdminSlap(const MUID& admin, const MUID& target)
    {
      MMatchObject* adminObj = MGetMatchServer()->GetObject(admin);
      if (!IsEnabledObject(adminObj))
        return;

      MMatchObject* targetObj = MGetMatchServer()->GetObject(target);
      if (!IsEnabledObject(targetObj))
        return;

      if (IsAdminGrade(targetObj))
        return;

      if (targetObj->CheckAlive() == false)
        return;

      MUID stageUID = adminObj->GetStageUID();
      if (stageUID != targetObj->GetStageUID())
        return;

      MMatchStage* stage = MGetMatchServer()->FindStage(stageUID);
      if (stage == nullptr)
        return;

      //stage->OnGameKill(adminObj->GetUID(), targetObj->GetUID());


      this->PostGameDeadOnGameKill(stageUID, adminObj, targetObj, 0, 0);


      MCommand* cmd = MGetMatchServer()->CreateCommand(MC_ADMIN_REQUEST_SLAP, MUID(0, 0));
      cmd->AddParameter(new MCmdParamUID(adminObj->GetUID()));
      cmd->AddParameter(new MCmdParamUID(targetObj->GetUID()));

      MGetMatchServer()->RouteToStage(stageUID, cmd);
    }

Open(MMatchServer_OnCommand.cpp)

		case MC_ADMIN_REQUEST_SLAP:
		{
			MUID admin, player;
			pCommand->GetParameter(&admin, 0, MPT_UID);
			pCommand->GetParameter(&player, 1, MPT_UID);

			OnResponseAdminSlap(admin, player);
		}break;


Open(MSharedCommandTable.cpp)


	C(MC_ADMIN_REQUEST_SLAP, "", "", MCDT_MACHINE2MACHINE)
		P(MPT_UID,"admin")
		P(MPT_UID,"target")

Open(ZGameInterface_OnCommand.cpp)

	case MC_ADMIN_REQUEST_SLAP:
	{
		MUID admin, player;

		pCommand->GetParameter(&admin, 0, MPT_UID);
		pCommand->GetParameter(&player, 1, MPT_UID);

		ZCharacter* adminObj = dynamic_cast<ZCharacter*>(ZGetCharacterManager()->Find(admin));
		ZCharacter* playerObj = dynamic_cast<ZCharacter*>(ZGetCharacterManager()->Find(player));
		if (adminObj == nullptr || playerObj == nullptr)
			break;

		std::string outputMsg = adminObj->GetUserName();//
		outputMsg.append(" Has Slapped ");
		outputMsg.append(playerObj->GetUserName());

		ZChatOutput(outputMsg.c_str());

		if (playerObj->GetUID() == ZGetMyUID())
		{
			ZPostDie(admin);
			ZPostGameKill(admin);
		}
	}

Open(MMatchServer.h - Find: OnAdminRequestBlockPlayer)

	void OnResponseAdminSlap(const MUID& admin, const MUID& target);


Credits to Jetman.
