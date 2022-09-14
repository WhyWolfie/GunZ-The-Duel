the crash i am talking about is this https://www.youtube.com/watch?t=23&v=zRVdIO29f78,  <br>
i had this fix for very long time, and seeing it being abused on hg made me decide to post this.  <br>

the only code i could have found of this patch was in a ugg hack i made, so its your job to integrate it into your client source.  <br>

    int IsNan(double x)
    {
        union { unsigned __int64 u; double f; } ieee754;
        ieee754.f = x;

        return ((unsigned)(ieee754.u >> 32) & 0x7fffffff) + ((unsigned)ieee754.u != 0) > 0x7ff00000;
    }

    int IsInf(double x)
    {
        union { unsigned __int64 u; double f; } ieee754;
        ieee754.f = x;

        return ((unsigned)(ieee754.u >> 32) & 0x7fffffff) == 0x7ff00000 && ((unsigned)ieee754.u == 0);
    }

    bool MC_PEER_SHOT_SP_Handler(MCommand* pCommand)            // check if values can cause us crash
    {
        unsigned long spType;
        GVector Position;
        GVector Direction;

        GCommand Cmd = GCommand(pCommand);

        if (Cmd.GetParam(&spType, 3, GCommand::EPARAM_TYPE::PARAM_INT) && spType  == 6)        // if type is KIT
        {
            if (Cmd.GetParam(&Position, 1, GCommand::EPARAM_TYPE::PARAM_POS) && Cmd.GetParam(&Direction, 2, GCommand::EPARAM_TYPE::PARAM_VECTOR))
            {
                if (IsNan(Position.x) || IsNan(Position.y) || IsNan(Position.z) || IsNan(Direction.x) || IsNan(Direction.y) || IsNan(Direction.z) ||
                    IsInf(Position.x) || IsInf(Position.y) || IsInf(Position.z) || IsInf(Direction.x) || IsInf(Direction.y) || IsInf(Direction.z))
                {
                    return false;
                }
            }
        }

        return true;
    } 
    
    
basicly for MC_PEER_SHOT_SP command check if the values of the position + direction are in the "ok" range, if not simply drop the command. <br>

credits to someone from stackoverflow for the nan/inf functions & justnoob123 <br>
