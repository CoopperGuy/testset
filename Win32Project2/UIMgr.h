#pragma once


#ifndef __CUIMGR_H__
#define __CUIMGR_H__


class CUI;
class CUIMgr
{
private:
	CUIMgr();
	~CUIMgr();

public:
	void Add_Object(CUI* _pObj,UIID::ID _id) { m_listUI[_id].emplace_back(_pObj); }
	void Update();
	void Render(HDC _DC);
	void Release();
public:
	void Delete_UI(UIID::ID _id);
public:
	static CUIMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CUIMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CUIMgr*		m_pInstance;
	list<CUI*>			m_listUI[UIID::END];
};


#endif // !__CUIMGR_H__
