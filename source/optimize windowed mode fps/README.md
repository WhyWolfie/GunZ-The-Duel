Normally the fps in windowed mode is 60 with this change you could have full fps like fullscreen. <br>
Find:

    g_d3dpp.PresentationInterval = params->bFullScreen ? D3DPRESENT_INTERVAL_IMMEDIATE : D3DPRESENT_INTERVAL_DEFAULT; 

Replace With:

    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; 
    
    
    
Cheers,
HeroBanana
