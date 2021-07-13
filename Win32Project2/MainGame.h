#pragma once

#ifndef __CMAINGAME_H__
#define __CMAINGAME_H__

class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	HRESULT Initialize();
	void Update();
	void Late_Update();
	void Render();
	void Release();
private:
	HDC		m_hDC;
};


#endif // !__CMAINGAME_H__
