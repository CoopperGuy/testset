#include "stdafx.h"
#include "SingleTexture.h"


CSingleTexture::CSingleTexture()
	:m_tTexInfo({})
{
}


CSingleTexture::~CSingleTexture()
{
	Release_Texture();
}

HRESULT CSingleTexture::Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey /*= L""*/, const DWORD dwCount /*= 0*/)
{
	if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_tTexInfo.tImageInfo)))
		return E_FAIL;

	if (FAILED(D3DXCreateTextureFromFileEx(CGraphic_Device::Get_Instance()->Get_Device(),
		wstrFilePath.c_str(),
		m_tTexInfo.tImageInfo.Width,
		m_tTexInfo.tImageInfo.Height,
		m_tTexInfo.tImageInfo.MipLevels,
		0,
		m_tTexInfo.tImageInfo.Format,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		nullptr,
		nullptr,
		&m_tTexInfo.pTexture)))
		return E_FAIL;

	return S_OK;
}

const TEXINFO * CSingleTexture::Get_TexInfo_Texture(const wstring & wstrStateKey /*= L""*/, const DWORD & dwIndex /*= 0*/)
{
	return &m_tTexInfo;
}

void CSingleTexture::Release_Texture()
{
	if (m_tTexInfo.pTexture)
		m_tTexInfo.pTexture->Release();
}

