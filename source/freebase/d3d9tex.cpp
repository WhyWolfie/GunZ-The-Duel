/*	Direct3D9 Texture */

#include <windows.h>

#include "d3d9.h"

HRESULT APIENTRY hkIDirect3DTexture9::QueryInterface(REFIID riid, void** ppvObj)
{
	return m_D3Dtex->QueryInterface(riid, ppvObj);
}

ULONG APIENTRY hkIDirect3DTexture9::AddRef()
{
	return m_D3Dtex->AddRef();
}

ULONG APIENTRY hkIDirect3DTexture9::Release()
{
	return m_D3Dtex->Release();
}

HRESULT APIENTRY hkIDirect3DTexture9::GetDevice(IDirect3DDevice9** ppDevice)
{
	*ppDevice = m_D3Ddev;
	return D3D_OK;
}

HRESULT APIENTRY hkIDirect3DTexture9::SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
{
	return m_D3Dtex->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

HRESULT APIENTRY hkIDirect3DTexture9::GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData)
{
	return m_D3Dtex->GetPrivateData(refguid, pData, pSizeOfData);
}

HRESULT APIENTRY hkIDirect3DTexture9::FreePrivateData(REFGUID refguid)
{
	return m_D3Dtex->FreePrivateData(refguid);
}

DWORD APIENTRY hkIDirect3DTexture9::SetPriority(DWORD PriorityNew)
{
	return m_D3Dtex->SetPriority(PriorityNew);
}

DWORD APIENTRY hkIDirect3DTexture9::GetPriority()
{
	return m_D3Dtex->GetPriority();
}

void APIENTRY hkIDirect3DTexture9::PreLoad()
{
	m_D3Dtex->PreLoad();
}

D3DRESOURCETYPE APIENTRY hkIDirect3DTexture9::GetType()
{
	return m_D3Dtex->GetType();
}

DWORD APIENTRY hkIDirect3DTexture9::SetLOD(DWORD LODNew)
{
	return m_D3Dtex->SetLOD(LODNew);
}

DWORD APIENTRY hkIDirect3DTexture9::GetLOD()
{
	return m_D3Dtex->GetLOD();
}

DWORD APIENTRY hkIDirect3DTexture9::GetLevelCount()
{
	return m_D3Dtex->GetLevelCount();
}

HRESULT APIENTRY hkIDirect3DTexture9::SetAutoGenFilterType(D3DTEXTUREFILTERTYPE FilterType)
{
	return m_D3Dtex->SetAutoGenFilterType(FilterType);
}

D3DTEXTUREFILTERTYPE APIENTRY hkIDirect3DTexture9::GetAutoGenFilterType()
{
	return m_D3Dtex->GetAutoGenFilterType();
}

void APIENTRY hkIDirect3DTexture9::GenerateMipSubLevels()
{
	m_D3Dtex->GenerateMipSubLevels();
}

HRESULT APIENTRY hkIDirect3DTexture9::GetLevelDesc(UINT Level,D3DSURFACE_DESC *pDesc)
{
	return m_D3Dtex->GetLevelDesc(Level, pDesc);
}

HRESULT APIENTRY hkIDirect3DTexture9::GetSurfaceLevel(UINT Level,IDirect3DSurface9** ppSurfaceLevel)
{
	return m_D3Dtex->GetSurfaceLevel(Level, ppSurfaceLevel);
}

HRESULT APIENTRY hkIDirect3DTexture9::LockRect(UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags)
{
	return m_D3Dtex->LockRect(Level, pLockedRect, pRect, Flags);
}

HRESULT APIENTRY hkIDirect3DTexture9::UnlockRect(UINT Level)
{
	return m_D3Dtex->UnlockRect(Level);
}

HRESULT APIENTRY hkIDirect3DTexture9::AddDirtyRect(CONST RECT* pDirtyRect)
{
	return m_D3Dtex->AddDirtyRect(pDirtyRect);
}

//////////////////////////////
// Useful Functions
//////////////////////////////
DWORD QuickChecksum(DWORD *pData, int size)
{
	if(!pData) { return 0x0; }

	DWORD sum;
	DWORD tmp;
	sum = *pData;

	for(int i = 1; i < (size/4); i++)
	{
		tmp = pData[i];
		tmp = (DWORD)(sum >> 29) + tmp;
		tmp = (DWORD)(sum >> 17) + tmp;
		sum = (DWORD)(sum << 3)  ^ tmp;
	}

	return sum;
}