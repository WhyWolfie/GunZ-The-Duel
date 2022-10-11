Open ZChat_Cmds.cpp <br>
Add <br>

Part 1

    void ChatCmd_Spawn(const char* line, const int argc, char **const argv);

Part 2

    _CC_AC("admin_spawn",&ChatCmd_Spawn,CCF_ALL, ARGVNoMin, 1 , true,"/admin_spawn <¸Þ½ÃÁö>", "");

Part 3

    void ChatCmd_Spawn(const char* line, const int argc, char **const argv)
    {

          ZMyCharacter* m_pMyCharacter = ZGetGame()->m_pMyCharacter;
          MCommand *pNewCmd = ZGetGameClient()->CreateCommand(MC_PEER_SPAWN, MUID(0,0));
          pNewCmd->AddParameter(new MCommandParameterPos(m_pMyCharacter->GetPosition().x, m_pMyCharacter->GetPosition().y, m_pMyCharacter->GetPosition().z));
          pNewCmd->AddParameter(new MCommandParameterDir(m_pMyCharacter->GetDirection().x, m_pMyCharacter->GetDirection().y, m_pMyCharacter->GetDirection().z));
          ZGetGameClient()->Post(pNewCmd);
          ZGetGame()->ReleaseObserver();
          ZPACKEDSHOTINFO ShotInfo;
          ShotInfo.fTime = (float)timeGetTime();
          ShotInfo.posx = 0;
          ShotInfo.posy = 0;
          ShotInfo.posz = 0;
          ShotInfo.tox = 0;
          ShotInfo.toy = 0;
          ShotInfo.toz = 0;
          ShotInfo.sel_type = 0;
          pNewCmd = ZGetGameClient()->CreateCommand(MC_PEER_SHOT, MUID(0,0));
          pNewCmd->AddParameter(new MCommandParameterBlob(&ShotInfo, sizeof(ZPACKEDSHOTINFO)));
          ZGetGameClient()->Post(pNewCmd);
          return;
    }
