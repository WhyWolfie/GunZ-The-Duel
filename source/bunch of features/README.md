Open(ZGame.cpp) <br>
Showing FPS - CTRL+F <br>
Find <br>

    void ZGame::Draw()
    
Place under <br>

	if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('F') & 0x8000))
	{
		char szName[128];
		float fMs = 1000.f / g_fFPS;
		float fScore = 100 - (fMs - (1000.f / 60.f)) * 2;

		sprintf(szName, "^9My FPS is currently : %3.3f", g_fFPS, fScore, fMs);
		ZApplication::GetGameInterface()->GetChat()->Input(szName);
	}
