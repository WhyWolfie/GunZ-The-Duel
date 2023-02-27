#include <windows.h>

#include "d3d9.h"


tDirect3DCreate9 oDirect3DCreate9;

IDirect3D9 *APIENTRY hkDirect3DCreate9(UINT SDKVersion)
{
	IDirect3D9 *d3dint = oDirect3DCreate9(SDKVersion);


		hkIDirect3D9 *ret = new hkIDirect3D9(&d3dint);

	return d3dint;
}