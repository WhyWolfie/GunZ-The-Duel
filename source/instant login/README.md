Open (ZInterfaceBackground) - instant login / also disabling maiet logo at login screen <br>
Find <br>

    ZInterfaceBackground::SetScene
    
Replace

    if ( (nSceneNumber == LOGIN_SCENE_MAIN) || (nSceneNumber == LOGIN_SCENE_SELECTCHAR))
        m_dwClock = timeGetTime();

    //	if( nSceneNumber == LOGIN_SCENE_FALLDOWN)
    //		ZGetScreenEffectManager()->AddScreenEffect( "maiet_logo");
