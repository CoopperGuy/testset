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
	// CTexture을(를) 통해 상속됨
	virtual HRESULT Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey, const DWORD dwCount) override;
	virtual HRESULT Insert_Texture(const wstring& wstrFilePath,
		const wstring& wstrStateKey,
		const DWORD dwCount, const float _CX, const float _CY)override;
	virtual const TEXINFO * Get_TexInfo_Texture(const wstring & wstrStateKey, const DWORD & dwIndex) override;
	virtual void Release_Texture() override;
private:
	// 여기에서의 키값은 ?? stateKey 
	map<wstring, vector<TEXINFO*>> m_mapMultiTexture;
};

#endif // !__MULTITEXTURE_H__
