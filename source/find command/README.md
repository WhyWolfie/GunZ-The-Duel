Yeah yeah whatever people, some new members are asking me for these stuff, believe it or not !<br>
So a quick kick off, just no intro, or anything else -.-<br>

ZChat_Cmds.cpp<br>

    void ChatCmd_FindPlayer(const char* line, const int argc, char **const argv);

Part 2

    _CC_AC("find", &ChatCmd_FindPlayer, CCF_ALL, 1, 1, true, "/find <charname>", "");

Part 3

    void ChatCmd_FindPlayer(const char* line,const int argc, char **const argv)
    {
           ZPostWhere(argv[1]);
    }
    
Save > Build > Run.. <br>
Obviously ya'll know what's this, usage: /find <player_name><br>
Done, Peace <br>

Thanks too Tannous<br>
