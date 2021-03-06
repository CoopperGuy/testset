#include "stdafx.h"
#include "Texture_Manager.h"
#include "SingleTexture.h"
#include "MultiTexture.h"

IMPLEMENT_SINGLETON(CTexture_Manager)
CTexture_Manager::CTexture_Manager()
{
}


CTexture_Manager::~CTexture_Manager()
{
	Release_Texture();
}

HRESULT CTexture_Manager::Insert_Texture(TEX_ID eID, const wstring & wstrFilePath, const wstring & wstrObjectKey, const wstring & wstrStateKey, const DWORD dwCount)
{
	auto& iter_find = m_mapTexture.find(wstrObjectKey);
	CTexture* pTexture = nullptr;
	if (iter_find == m_mapTexture.end())
	{
		switch (eID)
		{
		case CTexture_Manager::SINGLE_TEX:
			pTexture = new CSingleTexture;
			break;
		case CTexture_Manager::MULTI_TEX:
			pTexture = new CMultiTexture;
			break;
		default:
			break;
		}
		if (FAILED(pTexture->Insert_Texture(wstrFilePath, wstrStateKey, dwCount)))
		{
			ERR_MSG(L"Insert Texture Failed - Texture_Manager");
			return E_FAIL;
		}
		m_mapTexture.emplace(wstrObjectKey, pTexture);
	}
	else if (MULTI_TEX == eID)
	{
		if (FAILED(m_mapTexture[wstrObjectKey]->Insert_Texture(wstrFilePath, wstrStateKey, dwCount)))
			return E_FAIL;
	}
	return S_OK;
}

HRESULT CTexture_Manager::Insert_Texture(TEX_ID eID, const wstring & wstrFilePath, const wstring & wstrObjectKey, const wstring & wstrStateKey, const DWORD dwCount, const float _CX, const float _CY)
{
	auto& iter_find = m_mapTexture.find(wstrObjectKey);
	CTexture* pTexture = nullptr;
	if (iter_find == m_mapTexture.end())
	{
		switch (eID)
		{
		case CTexture_Manager::SINGLE_TEX:
			pTexture = new CSingleTexture;
			break;
		case CTexture_Manager::MULTI_TEX:
			pTexture = new CMultiTexture;
			break;
		default:
			break;
		}
		if (FAILED(pTexture->Insert_Texture(wstrFilePath, wstrStateKey, dwCount,_CX,_CY)))
		{
			ERR_MSG(L"Insert Texture Failed - Texture_Manager");
			return E_FAIL;
		}
		m_mapTexture.emplace(wstrObjectKey, pTexture);
	}
	else if (MULTI_TEX == eID)
	{
		if (FAILED(m_mapTexture[wstrObjectKey]->Insert_Texture(wstrFilePath, wstrStateKey, dwCount, _CX, _CY)))
			return E_FAIL;
	}
	return S_OK;
}

const TEXINFO * CTexture_Manager::Get_TexInfo_Texture(const wstring & wstrObjectKey, const wstring & wstrStateKey, const DWORD & dwIndex)
{
	auto& iter_find = m_mapTexture.find(wstrObjectKey);
	if (m_mapTexture.end() == iter_find)
		return nullptr;

	return iter_find->second->Get_TexInfo_Texture(wstrStateKey, dwIndex);
}

void CTexture_Manager::Release_Texture()
{
	for (auto& rPair : m_mapTexture)
		Safe_Delete(rPair.second);
	m_mapTexture.clear();
}
