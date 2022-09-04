Will fix stretched & Refresh rate resolution <br>

Open (RealSpace2.h)<br>

Find<br>

    int     RGetIsWidthScreen();
 
Place under<br>

    int		RGetIs16x9();
    float   RGetWidthScreen();
    
Open (RealSpace2.cpp)

Find<br>

    int RGetScreenHeight()		{ return g_nScreenHeight; }

Place under<br>

    int RGetIs16x9()			{ return (float(g_nScreenHeight) / float(g_nScreenWidth) == 0.5625f) ? 1 : 0; }
    float RGetWidthScreen() { return float(g_nScreenHeight) / float(g_nScreenWidth); }
 
Open (ZPlayerListBox.cpp) <br>

Find
    
    float GetF(float _old,float _new)
    {
      return _old/_new;
    }

    float GetF(float _new)
    {
      return _new/800.f;
    }
    
Replace

    float GetF(float _new)
    {
      float adjustWidth = _new / 800.f;
      if (RGetWidthScreen() != 0.75f)
      {
        if (RGetIsWidthScreen())
          adjustWidth = _new / 960.f;
        if (RGetIs16x9())
          adjustWidth = _new / 1024.f;
      }
      return adjustWidth;
    }
    
Open (ZScreenEffectManager.cpp)<br>

Find ZScreenEffect::DrawCustom<br>

    bool ZScreenEffect::DrawCustom(unsigned long int nTime, rvector& vOffset, float fAngle)
    {
      RGetDevice()->SetRenderState(D3DRS_ZENABLE, FALSE);
      RGetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	rmatrix World;
	D3DXMatrixIdentity(&World);

	if (fAngle != 0.0f)
	{
		D3DXMatrixRotationZ(&World, fAngle);
	}

	rmatrix View,Offset;
	if(RGetIsWidthScreen())
	{
		const rvector eye(0,0,-780),at(0,0,0),up(0,1,0);
		D3DXMatrixLookAtLH(&View,&eye,&at,&up);
	}
	else
	{
		const rvector eye(0,0,-650),at(0,0,0),up(0,1,0);
		D3DXMatrixLookAtLH(&View,&eye,&at,&up);
	}
	D3DXMatrixTranslation(&Offset,vOffset.x,vOffset.y,vOffset.z);

	View=Offset*View;

	RGetDevice()->SetTransform( D3DTS_VIEW, &View );

	m_VMesh.SetWorldMatrix(World);
	//	m_VMesh.Frame();
	m_VMesh.Render();

	if(m_VMesh.isOncePlayDone()) {
		return false;
	}

	return true;
    }
  
Replace complete code with this

    bool ZScreenEffect::DrawCustom(unsigned long int nTime, rvector& vOffset, float fAngle)
    {
      RGetDevice()->SetRenderState(D3DRS_ZENABLE, FALSE);
      RGetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	rmatrix World;
	D3DXMatrixIdentity(&World);

	if (fAngle != 0.0f)
	{
		D3DXMatrixRotationZ(&World, fAngle);
	}

	rmatrix View, Offset, Scale;
	D3DXMatrixIdentity(&Scale);

	if (RGetIsWidthScreen())
	{
		const rvector eye(0, 0, -780), at(0, 0, 0), up(0, 1, 0);
		D3DXMatrixLookAtLH(&View, &eye, &at, &up);
	}
	else if (RGetWidthScreen() != 0.75f)  //Fix Screen resize
	{
		const rvector eye(0, 0, -(975.0f / RGetWidthScreen() / 2)), at(0, 0, 0), up(0, 1, 0);
		D3DXMatrixLookAtLH(&View, &eye, &at, &up);
		D3DXMatrixScaling(&Scale, (float)RGetScreenWidth() / ((float)RGetScreenHeight() * (4.0f / 3.0f)), 1, 1);
	}

	else
	{
		const rvector eye(0, 0, -650), at(0, 0, 0), up(0, 1, 0);
		D3DXMatrixLookAtLH(&View, &eye, &at, &up);
		D3DXMatrixScaling(&Scale, (float)RGetScreenWidth() / ((float)RGetScreenHeight() * (4.0f / 3.0f)), 1, 1);
	}
	D3DXMatrixTranslation(&Offset, vOffset.x, vOffset.y, vOffset.z);

	View = Offset * View;
	View = Scale * View;

	RGetDevice()->SetTransform(D3DTS_VIEW, &View);

	m_VMesh.SetWorldMatrix(World);
	m_VMesh.Render();

	if (m_VMesh.isOncePlayDone()) {
		return false;
	}

	return true;
    }


Open (ZOptionInterface)

Find

	static	map< int, D3DDISPLAYMODE> gDisplayMode;
	
Place under

	auto find_ddm(const D3DDISPLAYMODE& ddm)
	{
		return std::find_if(gDisplayMode.begin(), gDisplayMode.end(),
			[&](auto& val) { return val.second == ddm; });
	}



Find <br>

		MComboBox *pWidget = (MComboBox*)pResource->FindWidget("ScreenResolution");
    
Replace

		MComboBox *pWidget = (MComboBox*)pResource->FindWidget("ScreenResolution");
		if(pWidget)
		{
			pWidget->RemoveAll();
			gDisplayMode.clear();

			int dmIndex = 0;
			char szBuf[256];

			D3DDISPLAYMODE ddm;

			D3DFORMAT Formats[] =
			{
				D3DFMT_X8R8G8B8
			};

			for (auto& Format : Formats)
			{
				int nDM = RGetAdapterModeCount(Format);

				mlog("Number of display mode for format %d: %d\n", Format, nDM);

				for( int idm = 0 ; idm < nDM; ++idm )
				{
					if (REnumAdapterMode(D3DADAPTER_DEFAULT, Format, idm, &ddm))
					{
						ddm.RefreshRate = DEFAULT_REFRESHRATE;

						if (ddm.Format == D3DFMT_X8R8G8B8)
						{
							auto iter_ = find_ddm(ddm);
							if (iter_ == gDisplayMode.end())
							{
								gDisplayMode.insert({ dmIndex++, ddm });
								sprintf(szBuf, "%d x %d %dbpp", ddm.Width, ddm.Height,
									ddm.Format == D3DFMT_X8R8G8B8 ? 32 : 16);
								pWidget->Add(szBuf);
							}
						}
					}
				}
			}

			// ¸¸¾à µî·ÏµÈ ÇØ»óµµ°¡ ÇÏ³ªµµ ¾øÀ»°æ¿ì °­Á¦·Î µî·Ï
			if (gDisplayMode.size() == 0)
			{
				for (int i = 0; i < 10; ++i)
				{
					ddm.Width = widths[i / 2];
					ddm.Height = heights[i / 2];
					ddm.RefreshRate = DEFAULT_REFRESHRATE;
					ddm.Format = ((i % 2 == 1) ? D3DFMT_X8R8G8B8 : D3DFMT_R5G6B5);

					int bpp = (i % 2 == 1) ? 32 : 16;
					gDisplayMode.insert(map<int, D3DDISPLAYMODE>::value_type(i, ddm));
					sprintf(szBuf, "%dx%d  %d bpp", ddm.Width, ddm.Height, bpp);
					pWidget->Add(szBuf);
				}
			}
			ddm.Width = RGetScreenWidth();
			ddm.Height = RGetScreenHeight();
			ddm.RefreshRate = DEFAULT_REFRESHRATE;
			ddm.Format	= RGetPixelFormat();
			map< int, D3DDISPLAYMODE>::iterator iter = find_if( gDisplayMode.begin(), gDisplayMode.end(), value_equals<int, D3DDISPLAYMODE>(ddm));
			
			//Iterator crash fix, in case resolution isn't supported
			if (iter != gDisplayMode.end())
				pWidget->SetSelIndex(iter->first);
			else
				pWidget->SetSelIndex(0);
		}
    
    
    
    
    
    
    
    
    
    
    
    
    
