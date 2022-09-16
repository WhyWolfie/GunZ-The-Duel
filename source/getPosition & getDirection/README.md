Open (ZChat_Cmds.cpp) <br>
Part 1 <br>

    void getPosition(const char* line, const int argc, char** const argv);
    void getDirection(const char* line, const int argc, char** const argv);
    
Part 2 <br>

	_CC_AC("getpos", &getPosition, CCF_ADMIN | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "", "");
	_CC_AC("getdir", &getDirection, CCF_ADMIN | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "", "");
  
Part 3 <br>

    void getPosition(const char* line, const int argc, char** const argv)
    {
      rvector Pos = ZGetGame()->m_pMyCharacter->GetPosition();
      char output[64];
      sprintf_s(output, "Char Position - (%f %f %f)", Pos.x, Pos.y, Pos.z);
      ZChatOutput(output);
    }

    void getDirection(const char* line, const int argc, char** const argv)
    {
      rvector Pos = ZGetGame()->m_pMyCharacter->GetDirection();
      char output[64];
      sprintf_s(output, "Char Direction - (%f %f %f)", Pos.x, Pos.y, Pos.z);
      ZChatOutput(output);
    }

Credits too Jetman.
