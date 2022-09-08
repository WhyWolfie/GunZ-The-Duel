Open (ZGame.cpp) <br>
Find <br>

    case ZC_WEAPON_SP_ROCKET

Replace

	case ZC_WEAPON_SP_ROCKET : 
		{
			unsigned long int nID = pDesc->m_nID;
			if (nID == 9001 || nID == 9002)
			{
				m_WeaponManager.AddGrenade(pos, velocity, pOwnerCharacter);
			}
			else
			{
				m_WeaponManager.AddRocket(pos, dir, pOwnerCharacter);
			}

			if(Z_VIDEO_DYNAMICLIGHT) {
				ZGetStencilLight()->AddLightSource( pos, 2.0f, 100 );
			}
		}
		break;
    
- Not 100% perfect, but fix by yourself :) <br>
- Change ID (9001 / 9002) with ur Rocket weapon ID

