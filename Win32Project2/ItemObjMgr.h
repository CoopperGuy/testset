#pragma once
#ifndef __ITEMOBJMGR_H__
#define __ITEMOBJMGR_H__

class CItemObjMgr
{
public:
	CItemObjMgr();
	~CItemObjMgr();

public:
	CObj* Create_ItemObj(EDITID::ID, float, float);

};

#endif // !__ITEMOBJMGR_H__
