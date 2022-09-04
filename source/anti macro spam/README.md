Open(ZGameInput.cpp) <br>

Find: <br>

    ZGameInput* ZGameInput::m_pInstance = NULL;

Place under that code

    static DWORD g_dwMacroTime = 0;


Find this code

			if (ZGetConfiguration()) {

					char* str = ZGetConfiguration()->GetMacro()->GetString( sel );

					if(str) {
						if(ZApplication::GetGameInterface())
							if(ZApplication::GetGameInterface()->GetChat())
								ZApplication::GetGameInterface()->GetChat()->Input(str);
					}
				}
				return true;
        
Replace code with

				if (ZGetConfiguration()) {
					char* str = ZGetConfiguration()->GetMacro()->GetString(sel);

					if (str) {
						if (ZApplication::GetGameInterface())
							if (ZApplication::GetGameInterface()->GetChat())
							{
								//Macro spam fix
								if (MEvent::GetShiftState())
									break;

								if (timeGetTime() - g_dwMacroTime > 2000) //Macro Spam Delay here
								{
									ZApplication::GetGameInterface()->GetChat()->Input(str);
									g_dwMacroTime = timeGetTime();
								}
								else
								{
									break; //not sure if this was neccessary but put it in.
								}
							}
					}
				}
				return true;
