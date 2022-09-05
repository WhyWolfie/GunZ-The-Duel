Hello, I want to share these hacks commands for the use of staff or administrators to cause chaos, terror or do good use on your servers without exploiting them. 

in ZChat_Cmds.cpp add these.

    #include "ZCommandHack.h" 
    
in ZChat_Cmds.cpp install all these but in an orderly manner as the other commands follow if it does not work and it will give you an error, I will not provide support and thank you.

    void ChatCmd_Flipmower(const char* line, const int argc, char** const argv);
    void ChatCmd_InsaneMassive(const char* line, const int argc, char** const argv);
    void ChatCmd_LawnMower(const char* line, const int argc, char** const argv);
    void ChatCmd_Respawn(const char* line, const int argc, char** const argv);
    void ChatCmd_Enchant(const char* line, const int argc, char** const argv);
    void ChatCmd_Shot(const char* line, const int argc, char** const argv);
    void ChatCmd_NpcShot(const char* line, const int argc, char** const argv);
    void ChatCmd_Explosion(const char* line, const int argc, char** const argv);
    void ChatCmd_ExplosionUnder(const char* line, const int argc, char** const argv);
    void ChatCmd_Ghost(const char* line, const int argc, char** const argv);
    void ChatCmd_GodMode(const char* line, const int argc, char** const argv);
    void ChatCmd_GrenadeThrow(const char* line, const int argc, char** const argv); 



    //Commands Hacks
    _CC_AC("jork_esp", &ChatCmd_AdminEsp, CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/jork_esp", "");
    _CC_AC("jork_quest", &ChatCmd_NpcShot, CCF_ADMIN | CCF_ADMIN | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_quest", "");
    _CC_AC("jork_flip", &ChatCmd_Flipmower, CCF_ADMIN | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_flip", "");
    _CC_AC("jork_masive", &ChatCmd_InsaneMassive, CCF_ADMIN | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_masive", "");
    _CC_AC("jork_lawn", &ChatCmd_LawnMower, CCF_ADMIN | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_lawn", "");
    _CC_AC("jork_respawn", &ChatCmd_Respawn, CCF_ADMIN | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_respawn", "");
    _CC_AC("jork_enchant", &ChatCmd_Enchant, CCF_ADMIN | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_enchant", "");
    _CC_AC("jork_shot", &ChatCmd_Shot, CCF_ADMIN | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_shot", "");
    _CC_AC("jork_boom", &ChatCmd_Explosion, CCF_ADMIN | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_boom", "");
    _CC_AC("jork_boomu", &ChatCmd_ExplosionUnder, CCF_ADMIN | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_boomu", "");
    _CC_AC("jork_wallhack", &ChatCmd_Ghost, CCF_ADMIN | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_wallhack", "");
    _CC_AC("jork_granade", &ChatCmd_GrenadeThrow, CCF_ADMIN | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_granade", ""); 


    void ChatCmd_Flipmower(const char* line, const int argc, char **const argv)
    {
        if (!ZGetMyInfo()->IsAdminGrade()) {
            return;//By Jorklenis2
        }
        if (!ZGetGame())
        {
            ZChatOutput("You're NOT in game.", ZChat::CMT_SYSTEM);
            return;
        }
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&fm, 0, 0, 0);
    }
    void ChatCmd_InsaneMassive(const char* line, const int argc, char **const argv)
    {
        if (!ZGetMyInfo()->IsAdminGrade()) {
            return;//By Jorklenis2
        }
        if (!ZGetGame())
        {
            ZChatOutput("You're NOT in game.", ZChat::CMT_SYSTEM);
            return;
        }
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&im, 0, 0, 0);
    }
    void ChatCmd_LawnMower(const char* line, const int argc, char **const argv)
    {
        if (!ZGetMyInfo()->IsAdminGrade()) {
            return;//By Jorklenis2
        }
        if (!ZGetGame())
        {
            ZChatOutput("You're NOT in game.", ZChat::CMT_SYSTEM);
            return;
        }
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&lm, 0, 0, 0);
    }
    void ChatCmd_Respawn(const char* line, const int argc, char **const argv)
    {
        if (!ZGetMyInfo()->IsAdminGrade()) {
            return;//By Jorklenis2
        }
        if (!ZGetGame())
        {
            ZChatOutput("You're NOT in game.", ZChat::CMT_SYSTEM);
            return;
        }
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&rp, 0, 0, 0);
    }
    void ChatCmd_Enchant(const char* line, const int argc, char **const argv)
    {
        if (!ZGetMyInfo()->IsAdminGrade()) {
            return;//By Jorklenis2
        }
        if (!ZGetGame())
        {
            ZChatOutput("You're NOT in game.", ZChat::CMT_SYSTEM);
            return;
        }
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&en, 0, 0, 0);
    }
    void ChatCmd_Shot(const char* line, const int argc, char **const argv)
    {
        if (!ZGetMyInfo()->IsAdminGrade()) {
            return;//By Jorklenis2
        }
        if (!ZGetGame())
        {
            ZChatOutput("You're NOT in game.", ZChat::CMT_SYSTEM);
            return;
        }
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&sh, 0, 0, 0);
    }
    void ChatCmd_NpcShot(const char* line, const int argc, char **const argv)
    {
        if (!ZGetMyInfo()->IsAdminGrade()) {
            return;//By Jorklenis2
        }
        if (!ZGetGame())
        {
            ZChatOutput("You're NOT in game.", ZChat::CMT_SYSTEM);
            return;
        }
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&ns, 0, 0, 0);
    }
    void ChatCmd_Explosion(const char* line, const int argc, char **const argv)
    {
        if (!ZGetMyInfo()->IsAdminGrade()) {
            return;//By Jorklenis2
        }
        if (!ZGetGame())
        {
            ZChatOutput("You're NOT in game.", ZChat::CMT_SYSTEM);
            return;
        }
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&ex, 0, 0, 0);
    }
    void ChatCmd_ExplosionUnder(const char* line, const int argc, char **const argv)
    {
        if (!ZGetMyInfo()->IsAdminGrade()) {
            return;//By Jorklenis2
        }
        if (!ZGetGame())
        {
            ZChatOutput("You're NOT in game.", ZChat::CMT_SYSTEM);
            return;
        }
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&ex2, 0, 0, 0);
    }
    void ChatCmd_Ghost(const char* line, const int argc, char **const argv)
    {
        if (!ZGetMyInfo()->IsAdminGrade()) {
            return;//By Jorklenis2
        }
        if (!ZGetGame())
        {
            ZChatOutput("You're NOT in game.", ZChat::CMT_SYSTEM);
            return;
        }
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&wall, 0, 0, 0);
    }
    void ChatCmd_GrenadeThrow(const char* line, const int argc, char **const argv)
    {
        if (!ZGetMyInfo()->IsAdminGrade()) {
            return;//By Jorklenis2
        }
        if (!ZGetGame())
        {
            ZChatOutput("You're NOT in game.", ZChat::CMT_SYSTEM);
            return;
        }
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&gt, 0, 0, 0);
    }

    void ChatCmd_GodMode(const char* line, const int argc, char **const argv)
    {
    if (!ZGetMyInfo()->IsAdminGrade()) {
    return;//By Jorklenis2
    }
    if (!ZGetGame())
    {
    ZChatOutput("You're NOT in game.", ZChat::CMT_SYSTEM);
    return;
    }
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&gm, 0, 0, 0);
    } 






Thanks too: Androide28, Jorklenis2
