#pragma once

#ifndef __SCENEMGR_H__
#define __SCENEMGR_H__
class CScene;
class CSceneMgr
{
public:
	enum SCENEID { MENU, STAGE, GAMEOVER, EDIT, END };

private:
	CSceneMgr();
	~CSceneMgr();
public:
	void Scene_Change(SCENEID _eID);
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();
public:
	static CSceneMgr*	Get_Instance() {
		if (!m_Instance)
			m_Instance = new CSceneMgr;
		return m_Instance;
	}
	static void Destroy_Instance() {
		SAFE_DELETE(m_Instance);
	}
private:
	static CSceneMgr*	m_Instance;

	SCENEID		m_ePreScene;
	SCENEID		m_eCurScene;
	CScene*		m_pScene;
};


#endif // !__SCENEMGR_H__
