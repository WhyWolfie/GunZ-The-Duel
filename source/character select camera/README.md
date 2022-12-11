Open(ZInterfaceBackground.cpp) <br>
Find <br>

		case  LOGIN_SCENE_SELECTCHAR :
		{
			// Get current clock
			DWORD dwClock = ( timeGetTime() - m_dwClock);
			float fGain = ( cos( dwClock * 0.0012f) + 1.0f) / 2.0f;
			
			
			vCamPos = m_vCamPosEd + ( m_vCamPosSt - m_vCamPosEd) * fGain;
			vCamDir = m_vCamDirEd + ( m_vCamDirSt - m_vCamDirEd) * fGain;

			MPicture* pPicture = (MPicture*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "CharSel_TopScreen");
			if ( pPicture)
			{
				// Set wait time
				if ( dwClock < 2000)
					dwClock = 0;
				else
					dwClock -= 2000;

				// Set opacity of black screen
				int nOpacity = (int)( dwClock / 3.0f);
				if ( nOpacity > 255)
					nOpacity = 255;

				pPicture->SetOpacity( nOpacity);
			}

			// Cleared fog
			fForgDensity = 50000.0f;
			break;
		}
	}
  
Replace <br>

		case  LOGIN_SCENE_SELECTCHAR :
		{
			// Get current clock
			DWORD dwClock = ( timeGetTime() - m_dwClock);
			
			//Don't shift camera position + direction
			float fGain = 1.0f;
			//float fGain = ( cos( dwClock * 0.0012f) + 1.0f) / 2.0f;

			vCamPos = m_vCamPosEd + ( m_vCamPosSt - m_vCamPosEd) * fGain;
			vCamDir = m_vCamDirEd + ( m_vCamDirSt - m_vCamDirEd) * fGain;

			MPicture* pPicture = (MPicture*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "CharSel_TopScreen");
			if ( pPicture)
			{
				// Set wait time
				if ( dwClock < 2000)
					dwClock = 0;
				else
					dwClock -= 2000;

				// Set opacity of black screen
				int nOpacity = (int)( dwClock / 3.0f);
				if ( nOpacity > 255)
					nOpacity = 255;

				pPicture->SetOpacity( nOpacity);
			}

			// Cleared fog
			fForgDensity = 50000.0f;
			break;
		}
	}
