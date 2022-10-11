Open(ZChat_Cmds.cpp) <br>

(ColourList)

    void ChatCmd_ColorList(const char* line, const int argc, char** const argv);
    
(Mods)
    
    void ChatCmd_Mods(const char* line,const int argc, char **const argv);

(Commands)

    void ChatCmd_Commands(const char* line,const int argc, char **const argv);

Part 2

(ColourList)

	_CC_AC("colors", &ChatCmd_ColorList, CCF_ALL, ARGVNoMin, ARGVNoMax, true, "/colors", "Lists all colors");
	
(Mods)
	
	_CC_AC("mods", &ChatCmd_Mods,CCF_ALL, ARGVNoMin, ARGVNoMax, true, "/mods", "Lists all room modifiers");

(Commands)

	_CC_AC("commands",&ChatCmd_Commands,CCF_ALL, ARGVNoMin, ARGVNoMax, true, "/commands", "Lists all commands");

Part 3

(ColourList)

    void ChatCmd_ColorList(const char* line, const int argc, char** const argv)
    {
      ZChatOutput("^00 ^11 ^22 ^33 ^44 ^55 ^66 ^77 ^88 ^99");
      ZChatOutput("^AA ^BB ^CC ^DD ^EE ^FF ^GG");
    }

(Mods)

	void ChatCmd_Mods(const char* line, const int argc, char **const argv)
	{
	#define zco(x) ZChatOutput( MCOLOR(ZCOLOR_CHAT_BROADCAST), x );
		ZChatOutput( MCOLOR(ZCOLOR_CHAT_LOBBY_DEFALT), "> Game Room Modifiers" );
		ZChatOutput( MCOLOR(ZCOLOR_CHAT_SYSTEM), ">> Place these modifiers in your room name." );
		zco( "* [LEAD] - Disables the Anti-Lead system" );
		zco( "* [VAMP] - Vampire mode. You hunger for blood and 33% of damage dealt to others becomes your HP/AP!" )
		zco( "* [SH] - Shield mode. Damage goes to your AP first. If Shield breaks completely, damage goes to your HP. Else, it recharges." )
		zco( "* [V] - Vanilla Mode. HP/AP is capped to default (125/100)." )
		zco( "* [R] / [IA] - Instant reloading / Infinite Ammo" )
		zco( "* [EX] - Explosions deal no damage." )
		zco( "* [WF] / [ESP]: Enables Wireframe / Enables ESP" )
		zco( "* [G?] - Gravity. (eg [G50], values: 0-300)" )
		zco( "* [S?] - Speed. (eg [S200], values: 0-300)" )
		zco( "* [J?] - Jump. (eg [J150], values: 0-300)" )
		zco( "* [IB] - Infinite blocking of swords." )
		zco( "* [N] - Ninja mode. Just jump!" )
		zco( "* [FPS] - FPS mode. Press shift to sprint!" )
		zco( "* [DMG?] - Damage Multiplier. Only available in Infected (eg [DMG2], values: 2-3)" )
		zco( "* [SGO] / [SNO] - Shotguns only / Snipers only" )
		zco( "* [F] / [M] / [KS] - No flipping / No massives / No K-Style" )
		zco( "* [NC] / [NR] / [NS] - No clothes / No rings / No swords" )
		zco( "* [NG] / [NI] - No guns / No items (medikits/potions/etc)" )
		zco( "* [RTD] - Roll The Dice mode." )
		//zco( "** [LEAD] - Disables the Anti-Lead system" );
		//zco( "** [VAMP] - Vampire mode. You hunger for blood and 33% of damage dealt to others becomes your HP/AP!" )
		//zco( "** [R] - Instant reloading." )
		//zco( "** [IA] - Infinite ammo." )
		//zco( "** [EX] - Explosions deal no damage." )
		//zco( "** [G?] - Gravity. (eg [G50], values: 0-300)" )
		//zco( "** [S?] - Speed. (eg [S200], values: 0-300)" )
		//zco( "** [J?] - Jump. (eg [J150], values: 0-300)" )
		//zco( "** [F] - No flipping." )
		//zco( "** [M] - No massives." )
		//zco( "** [IB] - Infinite blocking of swords." )
		//zco( "** [N] - Ninja mode. Just jump!" )
		//zco( "** [SH] - Shield mode. Damage goes to your AP. If Shield breaks completely, damage goes to your HP. Else, it recharges." )
		//zco( "** [FPS] - FPS mode. Press shift to sprint!" )
		//zco( "** [V] - Vanilla Mode. HP/AP is capped to default (125/100)" )
		//zco( "** [SGO] - Shotguns only." )
		//zco( "** [SNO] - Snipers only." )
		//zco( "** [KS] - No K-Styling." )
		//zco( "** [DMG?] - Damage Multiplier (values: 2 or 3)" )
		//zco( "** [NC] - No clothes." )
		//zco( "** [NR] - No rings." )
		//zco( "** [NS] - No swords." )
		//zco( "** [NG] - No guns." )
		//zco( "** [NI] - No items (medikits/potions/etc)." )

	#undef zco
	}
	
(Commands)

	void ChatCmd_Commands(const char* line, const int argc, char **const argv)
	{
		ZChatOutput( MCOLOR(ZCOLOR_CHAT_LOBBY_DEFALT), "> In-Game Commands" );
		ZChatOutput( MCOLOR(ZCOLOR_CHAT_BROADCAST), "** /credits - Self-explanatory" );
		ZChatOutput( MCOLOR(ZCOLOR_CHAT_BROADCAST), "** /mods - View our room modifiers" );
		ZChatOutput( MCOLOR(ZCOLOR_CHAT_BROADCAST), "** /find <player> - Finds a player" );
		ZChatOutput( MCOLOR(ZCOLOR_CHAT_BROADCAST), "** /ignore <player> - Ignore a player" );
		ZChatOutput( MCOLOR(ZCOLOR_CHAT_BROADCAST), "** /unignore <player> - Unignore a player" );
		ZChatOutput( MCOLOR(ZCOLOR_CHAT_BROADCAST), "** /ignorelist - View ignore list" );
		ZChatOutput( MCOLOR(ZCOLOR_CHAT_BROADCAST), "** /cw <enable/disable/admins/status> - Allows clan wars for everyone/no-one/admins-only." );
		ZChatOutput( MCOLOR(ZCOLOR_CHAT_BROADCAST), "** /colors - Outputs all the available '^' colors.");
	}

![img](https://i.imgur.com/dZ5nksV.png)
