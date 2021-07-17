#pragma once
#ifndef __MAPOBJMGR_H__
#define __MAPOBJMGR_H__

class CMapObjMgr
{
	DECLARE_SINGLETON(CMapObjMgr)
private:
	CMapObjMgr();
	~CMapObjMgr();

public:
	HRESULT Ready_MapObj();

	CObj* Create_MapObj(EDITID::ID, float, float);

};


#endif // !__MAPOBJMGR_H__

