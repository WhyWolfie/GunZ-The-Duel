Part 1

    childElement.GetChildContents(&m_Etc.nTrailColor, ZTOK_TRAIL_COLOR); //Trail Color

Part 2

    //Trail Color
		parentElement.AppendText("\n\t\t");
		aElement = parentElement.CreateChildElement(ZTOK_TRAIL_COLOR);
		sprintf(temp, "%d", m_Etc.nTrailColor);
		aElement.SetContents(temp);

Part 3

    m_Etc.nTrailColor = 0; //Trail Color

Part 4

    int			nTrailColor;		//Trail Color


Part 5

    #define ZTOK_TRAIL_COLOR			"TRAILCOLOR"	//Trail Level

Part 6

    #define Z_TRAIL_COLOR			(ZGetConfiguration()->GetEtc()->nTrailColor) //Trail Color

Part 7

    //Trail Color
		pComboBox = (MComboBox*)pResource->FindWidget("TrailColor");
		if (pComboBox)
		{
			pComboBox->SetSelIndex(Z_TRAIL_COLOR);
		}



Part 8

    //Trail Color
		int nTrailColor = 0;
		pComboBox = (MComboBox*)pResource->FindWidget("TrailColor");
		if (pComboBox)
		{
			nTrailColor = pComboBox->GetSelIndex();
			if (Z_TRAIL_COLOR != nTrailColor)
			{
				Z_TRAIL_COLOR = nTrailColor;
			}
		}


Part 9

    void DrawTracks(bool draw, RVisualMesh* pVWMesh, int mode, rmatrix& m, int nTrailColor);

Part 10

    void GetEnChantColor(DWORD* color, int nTrailColor);

Part 11 Search: void RVisualMesh::RenderWeapon() - Add under

    float vis,vis2;
    int nTrailColor;

Search <br>

     if(btrack_render) {
        DrawTracks(m_bDrawTracks, pVWMesh, 0, m);
        DrawEnchant(pVWMesh,0,m);
    }

Replace <br>

    if(btrack_render) {
    DrawTracks(m_bDrawTracks, pVWMesh, 0, m, nTrailColor);
    DrawEnchant(pVWMesh,0,m);
    }

Search <br>

    if(btrack_render) {
    DrawTracks(m_bDrawTracks, pVWMesh, 0, m);
    DrawEnchant(pVWMesh,0,m);
    }
    }
    }

Replace <br>

    if(btrack_render) {
    DrawTracks(m_bDrawTracks, pVWMesh, 0, m, nTrailColor);
    DrawEnchant(pVWMesh,0,m);
    }
    }
    }

Search : void RVisualMesh::GetEnChantColor(DWORD* color) <br>

Replace <br>

    void RVisualMesh::GetEnChantColor(DWORD* color, int nTrailColor)
    {
      if (!color) return;
      if (m_EnchantType == REnchantType_Fire) {
        color[0] = 0x4fff6666;
        color[1] = 0x0fff6666;
      }
      else if (m_EnchantType == REnchantType_Cold) {
        color[0] = 0x4f6666ff;
        color[1] = 0x0f6666ff;
      }
      else if (m_EnchantType == REnchantType_Lightning) {
        color[0] = 0x4f66ffff;
        color[1] = 0x0f66ffff;
      }
      else if (m_EnchantType == REnchantType_Poison) {
        color[0] = 0x4f66ff66;
        color[1] = 0x0f66ff66;
      }
      switch (nTrailColor = Z_TRAIL_COLOR) {
      case 1: {
        color[0] = 0xffee11ee; //Red Pink
        color[1] = 0xffff0000;
        break;
      }
      case 2: {
        color[0] = 0xff22ffff; // Blue Cyan
        color[1] = 0xff2222ff;
        break;
      }
      case 3: {
        color[0] = 0xff11ee11; // Yellow Green
        color[1] = 0xffffc000;
        break;
      }
      case 4: {
        color[0] = 0xfff39700; //Orange Mint
        color[1] = 0xffff7f50;
        break;
      }
      case 5: {
        color[0] = 0xffbfabff; //Purple Mint
        color[1] = 0xff5500ff;
        break;
      }
      case 6: {
        color[0] = 0xff29cc8b; //Green Light
        color[1] = 0xff3bf900;
        break;
      }
      case 7: {
        color[0] = 0xff5c5aac; // Blue Mint
        color[1] = 0xff0400ff;
        break;
      }
      case 8: {
        color[0] = 0xff643f04; // Brown
        color[1] = 0xff4c1130;
        break;
      }
      case 9:{
        int nCount = ( timeGetTime() / 400)% 8; //9 Color
        for (int i = 0; i < nCount;  i++);
        if(i == 0)
        color[0] = 0x4fb400ff; //Purple
        color[1] = 0x0fb400ff; 
        if(i == 1)
        color[0] = 0x4fff0000; //Red
        color[1] = 0x0fff0000;
        if(i == 2)
        color[0] = 0x4fff00ea; //Pink
        color[1] = 0x0fff00ea;
        if(i == 3)
        color[0] = 0x4f3000ff; //Blue
        color[1] = 0x0f3000ff;
        if(i == 4)
        color[0] = 0x4f00ffea; //Cyan
        color[1] = 0x0f00ffea;
        if(i == 5)
        color[0] = 0x4f00ff54; //Green
        color[1] = 0x0f00ff54;
        if(i == 6)
        color[0] = 0x4fff8400; //Orange
        color[1] = 0x0fff8400;
        if(i == 7)
        color[0] = 0x4fffffff; //Black
        color[1] = 0x0fffffff;
    break;
    }
      case 0: {
        color[0] = 0x7fffffff; // White
    color[1] = 0x7fffffff;
        break;
      }
      default: {
        color[0] = 0x7fffffff; //White
        color[1] = 0x7fffffff;
        break;
      }
      }
    }

Search : void RVisualMesh::DrawTracks(bool draw,RVisualMesh* pVWMesh,int mode,rmatrix& m) <br>

    void RVisualMesh::DrawTracks(bool draw,RVisualMesh* pVWMesh,int mode,rmatrix& m, int nTrailColor)

Search : GetEnChantColor(color) <br>

    GetEnChantColor(color, Z_TRAIL_COLOR)

















