#pragma once

#ifndef __OBJMGR_H__
#define __OBJMGR_H__

class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	void Add_Object(CObj* _pObj, OBJID::ID _eID) { m_listObj[_eID].emplace_back(_pObj); }
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

public:
	void Picking_Obj(EDITID::ID);

	void Save_Player();
	void Load_Player();

	void Save_Monster();
	void Load_Monster();

public:
	static CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CObjMgr*		m_pInstance;
	list<CObj*>			m_listObj[OBJID::END];

};


#endif // !__OBJMGR_H__
