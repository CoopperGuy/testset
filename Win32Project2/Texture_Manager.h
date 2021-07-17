#pragma once
#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

class CTexture;
class CTexture_Manager
{
	DECLARE_SINGLETON(CTexture_Manager)
public:
	enum TEX_ID { SINGLE_TEX, MULTI_TEX };
private:
	CTexture_Manager();
	~CTexture_Manager();
public:
	HRESULT Insert_Texture(TEX_ID eID, const wstring& wstrFilePath,
		const wstring& wstrObjectKey,
		const wstring& wstrStateKey = L"",
		const DWORD dwCount = 0);
	HRESULT Insert_Texture(TEX_ID eID, const wstring& wstrFilePath,
		const wstring& wstrObjectKey,
		const wstring& wstrStateKey ,
		const DWORD dwCount,
		const float _CX,
		const float _CY);
	const TEXINFO* Get_TexInfo_Texture(const wstring& wstrObjectKey,
		const wstring& wstrStateKey = L"",
		const DWORD& dwIndex = 0);
	void Release_Texture();
private:
	// ObjectKey 
	map<wstring, CTexture*> m_mapTexture;
};

#endif // !__TEXTURE_MANAGER_H__
