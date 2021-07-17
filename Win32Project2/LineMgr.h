#pragma once

#ifndef __CLINEMGR_H__
#define __CLINEMGR_H__

class CLine;
class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void Add_Line(CLine* _line) { m_listLine.emplace_back(_line); }
	void Initialize();
	void Update();
	void Render(HDC _DC);
	void Release();

public:
	bool Collision_Line(float _x, float _y1, float* _y, bool* _bG);

public:
	void Picking_Line();

public:
	void Save_Line();
	void Load_Line();

public:
	static CLineMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}


private:
	static CLineMgr*	m_pInstance;
	list<CLine*>		m_listLine;
};


#endif // !__LINEMGR_H__
