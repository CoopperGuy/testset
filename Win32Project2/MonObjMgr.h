#pragma once
#ifndef __MONOBJMGR_H__
#define __MONOBJMGR_H__

class CMonObjMgr
{
	DECLARE_SINGLETON(CMonObjMgr)
private:
	CMonObjMgr();
	~CMonObjMgr();

public:
	CObj* Create_Monster(EDITID::ID, float, float);
};

#endif // !__MONOBJMGR_H__
