#include "stdafx.h"
#include "MonObjMgr.h"

#include "TestMon.h"

IMPLEMENT_SINGLETON(CMonObjMgr)
CMonObjMgr::CMonObjMgr()
{
}


CMonObjMgr::~CMonObjMgr()
{
}

CObj * CMonObjMgr::Create_Monster(EDITID::ID _eID, float _fx,  float _fy)
{
	CObj* pObj = nullptr;

	switch (_eID)
	{
	case EDITID::TESTMON:
		pObj = CAbstractFactory<CTestMon>::Create(_fx, _fy);
		break;
	case EDITID::MONSTER2:
		break;
	default:
		break;
	}

	if (!pObj)
		return nullptr;

	return pObj;
}
