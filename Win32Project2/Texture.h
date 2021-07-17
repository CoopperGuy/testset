#pragma once
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

class CTexture abstract
{
public:
	explicit CTexture();
	virtual ~CTexture();
public:
	virtual HRESULT Insert_Texture(const wstring& wstrFilePath,
		const wstring& wstrStateKey = L"",
		const DWORD dwCount = 0)PURE;
	virtual HRESULT Insert_Texture(const wstring& wstrFilePath,
		const wstring& wstrStateKey,
		const DWORD dwCount, const float _CX, const float _CY )PURE;
	virtual const TEXINFO* Get_TexInfo_Texture(const wstring& wstrStateKey = L"",
		const DWORD& dwIndex = 0)PURE;
	virtual void Release_Texture()PURE;

	//singleTexture, MultiTexture 
	// ObjectKey -> StateKey ->그림 여러장. 


};

#endif // !__TEXTURE_H__
