Open(ZChat_Cmds.cpp) <br>
Find <br>

    void ChatCmd_AdminPopup(const char* line, const int argc, char **const argv);

Part 2

	_CC_AC("popup",	&ChatCmd_AdminPopup, CCF_ADMIN, ARGVNoMin, 1, true, "/popup <msg>", "");


Part 3

    void ChatCmd_AdminPopup(const char* line, const int argc, char **const argv)
    {
      if (ZGetMyInfo()->GetUGradeID() == MMUG_EVENTMASTER)return;
      else if (ZGetMyInfo()->GetUGradeID() == MMUG_DEVELOPER)return;

      if (argc < 2)
      {
        OutputCmdWrongArgument(argv[0]);
        return;
      }

      char szMsg[256];
      strcpy(szMsg, argv[1]);
      ZPostAdminAnnounce(ZGetGameClient()->GetPlayerUID(), szMsg, ZAAT_MSGBOX);
    }

Open(ZPost.h) <br>
Find <br>

    inline void ZPostAdminAnnounce(const MUID& uidChar, char* szMsg, ZAdminAnnounceType nType)
    {
      ZPOSTCMD3(MC_ADMIN_ANNOUNCE, MCommandParameterUID(uidChar),
        MCommandParameterString(szMsg), MCommandParameterUInt(nType));
    }










































