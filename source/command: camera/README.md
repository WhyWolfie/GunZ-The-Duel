Open(ZChat_Cmds.cpp)

    void ChatCmd_Camera(const char* line, const int argc, char **const argv);

Part 2

	_CC_AC("camera",            &ChatCmd_Camera,                CCF_ALL, ARGVNoMin, 1, true, "/camera", "");

Part 3


    void ChatCmd_Camera(const char* line, const int argc, char **const argv)
    {
       if (argc < 2) 
       {
           ZChatOutput("Use: /camera Valor (or default)", ZChat::CMT_SYSTEM);
           return;
       }

       if(!ZGetGame())
       {
           ZChatOutput("You must be in-game!!", ZChat::CMT_SYSTEM);
           return;
       }

       float fDist = 0.0f;
       char szMsg[512] = "";

       if(strcmp(strlwr(argv[1]), "default") == 0)
           fDist = CAMERA_DEFAULT_DISTANCE;
       else
       {
           fDist = atoi(argv[1]);

           if((int)fDist < 150 || (int)fDist > 1000)
           {
               ZChatOutput("Must be between 150 and 1000!", ZChat::CMT_SYSTEM);
               return;
           }
       }

       ZCamera* pCamera = ZGetGameInterface()->GetCamera();
       pCamera->m_fDist = fDist;

       sprintf(szMsg, "Camera changed to %i!", (int)fDist);
       ZChatOutput(szMsg, ZChat::CMT_SYSTEM); }




![camera](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/command%3A%20camera/camera.jpg)







