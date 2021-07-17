#pragma once
#ifndef __MULTITEXTURE_H__
#define __MULTITEXTURE_H__

#include "Texture.h"
class CMultiTexture final :
	public CTexture
{
public:
	CMultiTexture();
	virtual ~CMultiTexture();
public:
	// CTexture��(��) ���� ��ӵ�
	virtual HRESULT Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey, const DWORD dwCount) override;
	virtual HRESULT Insert_Texture(const wstring& wstrFilePath,
		const wstring& wstrStateKey,
		const DWORD dwCount, const float _CX, const float _CY)override;
	virtual const TEXINFO * Get_TexInfo_Texture(const wstring & wstrStateKey, const DWORD & dwIndex) override;
	virtual void Release_Texture() override;
private:
	// ���⿡���� Ű���� ?? stateKey 
	map<wstring, vector<TEXINFO*>> m_mapMultiTexture;
};

#endif // !__MULTITEXTURE_H__
