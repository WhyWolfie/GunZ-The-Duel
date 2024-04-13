Hey guys,

I thought I should share these fixes with you guys as these bugfixes are ones that I personally think are essential to having a good playing experience, as these bugs are really annoying to most people and are pretty common in servers. Also I wanted to contribute some code to this forum, so you guys can have this crappy but simple static spread system. Keep in mind, I know that there are better ways to implement these, but my experience is pretty low as im pretty new to this community and I've basically learned C++ by messing around with the gunz source so don't expect anything from me.

Anyways, here is the code:

Sword Reload Fix:
Inside of the "Animation_Reload" Function, replace the line "SetAnimationUpper(ZC_STATE_UPPER_RELOAD);" to

    if (GetItems()->GetSelectedWeapon()->isReloadable())
    SetAnimationUpper(ZC_STATE_UPPER_RELOAD);

Multimonitor Bug Fix (When flicking your mouse, cursor can appear and go to your second monitor and tab you out) :

Find "SetCursorPos(pt.x, pt.y);" in ZGameInput::Update
Put under the line

    RECT rc;
    GetClientRect(g_hWnd, &rc);
    
    POINT pt = { rc.left, rc.top };
    POINT pt2 = { rc.right, rc.bottom };
    ClientToScreen(g_hWnd, &pt);
    ClientToScreen(g_hWnd, &pt2);
    SetRect(&rc, pt.x, pt.y, pt2.x, pt2.y);
    
    ClipCursor(&rc);

Right under in the "else", right above "pMyCharacter->ReleaseButtonState();", add (Edit: Dont forget to add curly brackets for this part for the else)

    ClipCursor(NULL);

Static Spread (Note: This code assumes your SHOTGUN_BULLET_COUNT is 12, and also the spread I put is just a random one, change the return values to change the spread) :

Right Above the "ZGame::OnPeerShot_Shotgun" function, add:

    int fAngleShit = 0; //sorry im bad at naming variables ...
    int fForceShit = 0;
    
    float getfAngle() {
    if (fAngleShit != 12)
    fAngleShit++;
    else
    fAngleShit = 0;
    
    switch (fAngleShit) {
    case 1:
    return 2.610;
    case 2:
    return 1.698;
    case 3:
    return 10.598;
    case 4:
    return 8.235;
    case 5:
    return 18.594;
    case 6:
    return 8.302;
    case 7:
    return 26.247;
    case 8:
    return 7.311;
    case 9:
    return 12.928;
    case 10:
    return 30.150;
    case 11:
    return 7.987;
    case 12:
    fAngleShit = 0;
    return 32.136;
    default:
    mlog("couldnt get a spread for fAngle..?");
    return 0.0;
    }
    }
    
    float getfForce() {
    if (fForceShit != 12)
    fForceShit++;
    else
    fForceShit = 0;
    
    switch (fForceShit) {
    case 1:
    return 0.064;
    case 2:
    return 0.065;
    case 3:
    return 0.027;
    case 4:
    return 0.036;
    case 5:
    return 0.043;
    case 6:
    return 0.068;
    case 7:
    return 0.060;
    case 8:
    return 0.012;
    case 9:
    return 0.022;
    case 10:
    return 0.051;
    case 11:
    return 0.057;
    case 12:
    fForceShit = 0;
    return 0.099;
    default:
    mlog("couldnt get a spread for fForce..?");
    return 0.0;
    }
    }

In "ZGame::OnPeerShot_Shotgun", replace both the fAngle and fForce floats to:

    float fAngle = getfAngle();
    float fForce = getfForce();


Credits to ProLib.
