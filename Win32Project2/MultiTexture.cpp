#include "stdafx.h"
#include "MultiTexture.h"


CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	Release_Texture();
}

HRESULT CMultiTexture::Insert_Texture(
	const wstring & wstrFilePath,
	const wstring & wstrStateKey,
	const DWORD dwCount)
{
	auto& iter = m_mapMultiTexture.find(wstrStateKey);
	if (iter == m_mapMultiTexture.end())
	{
		TEXINFO* pTexInfo = nullptr;
		TCHAR szFileFullPath[MAX_PATH] = L"";
		for (DWORD i = 0; i < dwCount; ++i)
		{
			swprintf_s(szFileFullPath, wstrFilePath.c_str(), i);
			pTexInfo = new TEXINFO;
			if (FAILED(D3DXGetImageInfoFromFile(szFileFullPath, &pTexInfo->tImageInfo)))
				return E_FAIL;
			
			if (FAILED(D3DXCreateTextureFromFileEx(CGraphic_Device::Get_Instance()->Get_Device(),
				szFileFullPath,
				pTexInfo->tImageInfo.Width,
				pTexInfo->tImageInfo.Height,
				pTexInfo->tImageInfo.MipLevels,
				0,
				pTexInfo->tImageInfo.Format,
				D3DPOOL_MANAGED,
				D3DX_DEFAULT,
				D3DX_DEFAULT,
				0,
				nullptr,
				nullptr,
				&pTexInfo->pTexture)))
				return E_FAIL;
			m_mapMultiTexture[wstrStateKey].emplace_back(pTexInfo);
		}
		return S_OK;
	}
	return S_OK;
}

HRESULT CMultiTexture::Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey, const DWORD dwCount, const float _CX, const float _CY)
{
	auto& iter = m_mapMultiTexture.find(wstrStateKey);
	if (iter == m_mapMultiTexture.end())
	{
		TEXINFO* pTexInfo = nullptr;
		TCHAR szFileFullPath[MAX_PATH] = L"";
		for (DWORD i = 0; i < dwCount; ++i)
		{
			swprintf_s(szFileFullPath, wstrFilePath.c_str(), i);
			pTexInfo = new TEXINFO;
			if (FAILED(D3DXGetImageInfoFromFile(szFileFullPath, &pTexInfo->tImageInfo)))
				return E_FAIL;

			if (FAILED(D3DXCreateTextureFromFileEx(CGraphic_Device::Get_Instance()->Get_Device(),
				szFileFullPath,
				_CX,
				_CY,
				pTexInfo->tImageInfo.MipLevels,
				0,
				pTexInfo->tImageInfo.Format,
				D3DPOOL_MANAGED,
				D3DX_DEFAULT,
				D3DX_DEFAULT,
				0,
				nullptr,
				nullptr,
				&pTexInfo->pTexture)))
				return E_FAIL;
			m_mapMultiTexture[wstrStateKey].emplace_back(pTexInfo);
		}
		return S_OK;
	}
	return S_OK;
}

const TEXINFO * CMultiTexture::Get_TexInfo_Texture(const wstring & wstrStateKey, const DWORD & dwIndex)
{
	map<wstring, vector<TEXINFO*>>::iterator iter = m_mapMultiTexture.find(wstrStateKey);
	if (iter == m_mapMultiTexture.end() || iter->second.size() <= dwIndex)
		return nullptr;
	return iter->second[dwIndex];
	//return m_mapMultiTexture[wstrStateKey][dwIndex]; 
}

void CMultiTexture::Release_Texture()
{
	for (auto& rPair : m_mapMultiTexture)
	{
		for (auto& pTexInfo : rPair.second)
		{
			if (pTexInfo->pTexture)
				pTexInfo->pTexture->Release();
			Safe_Delete(pTexInfo);
		}
		rPair.second.clear();
		rPair.second.swap(vector<TEXINFO*>());
	}
	m_mapMultiTexture.clear();
}
