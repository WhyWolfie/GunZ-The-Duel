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

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
