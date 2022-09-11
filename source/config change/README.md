Open(ZConfiguration.cpp) <br>
Find <br>

     void ZConfiguration::Init()
     
Change too <br>

	m_Video.bFullScreen = true;//false
	m_Video.nWidth = 1920;//1024
	m_Video.nHeight = 1080;//768
	m_Video.nColorBits = 32;
	m_Video.nGamma = 255;
	m_Video.bShader		= true;
	m_Video.nAntiAlias = 2;
	m_Video.bLightMap	= false;
	m_Video.bReflection	= true;
	m_Video.nCharTexLevel = 0;
	m_Video.nMapTexLevel = 0;
	m_Video.nEffectLevel = Z_VIDEO_EFFECT_HIGH;
	m_Video.nTextureFormat = 1;
	m_Video.bTerrible = false;
	m_MovingPicture.iResolution = 0;
	m_MovingPicture.iFileSize = 0;

	m_Audio.fEffectVolume = 1.0f;
	m_Audio.bBGMEnabled = true;
	m_Audio.fBGMVolume	= 0.3f;
	m_Audio.bBGMMute	= false;
	m_Audio.bEffectMute = false;
	m_Audio.b3DSound	= true;
	m_Audio.b8BitSound	= false;
	m_Audio.bInverse	= false;
	m_Audio.bHWMixing	= false;
	m_Audio.bHitSound	= true;
	m_Audio.bNarrationSound	= true;
  
  
Automatically change too <br>
- 1920x1080
- effect sound enabled
- fullscreen default true
