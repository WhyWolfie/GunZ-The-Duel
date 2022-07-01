<b>Map Texture Command</b><br>

    void ChatCmd_Texture(const char* line, const int argc, char **const argv)
    {
      int maptexture = 0;
      if(argc==2) {
        char szMsg[256];
        maptexture = atoi(argv[1]);
        DWORD flag = 0;
        if (maptexture < 0 || maptexture > 8) {
          ZChatOutput("^2Maptexture list: 0, 1, 2, 3, 4, 5, 6, 7, 8");
          return;
        }
        SetMapTextureLevel(maptexture);
        flag |= RTextureType_Map;
        RChangeBaseTextureLevel(flag);	
        sprintf(szMsg, "^1New MapTexure Level : %d", (int)maptexture);
        ZChatOutput(szMsg);
        return;
      } else {
        ZChatOutput("^2Usage: /maptexture <number>");
        ZChatOutput("^2Maptexture list: 0, 1, 2, 3, 4, 5, 6, 7, 8");
        return;
      }
    }

Credits to: Qet123
