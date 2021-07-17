#pragma once

#ifndef __TILEMGR_H__
#define __TILEMGR_H__

class CObj;
class CTileMgr
{
	DECLARE_SINGLETON(CTileMgr)
private:
	CTileMgr();
	~CTileMgr();

public:
	void Initialize();
	void Update();
	void Render(HDC _DC);
	void Release();

public:
	void Save_Tile();
	void Load_Tile();

public:
	void Picking_Tile(int _iDrawID);

private:
	vector<CObj*>		m_vecTile;
};


#endif // !__TILEMGR_H__
