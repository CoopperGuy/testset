#include "stdafx.h"
#include "MonObjMgr.h"

#include "Normal_Monster.h"
#include "Jump_Monster.h"

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
	case EDITID::NORMAL_MONSTER:
		pObj = CAbstractFactory<CNormal_Monster>::Create(_fx, _fy);
		break;
	case EDITID::JUMP_MONSTER:
		pObj = CAbstractFactory<CJump_Monster>::Create(_fx, _fy);
		break;
	default:
		break;
	}

	if (!pObj)
		return nullptr;

	return pObj;
}
