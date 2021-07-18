#include "stdafx.h"
#include "ItemObjMgr.h"

#include "PItem.h"
#include "GunItem.h"
#include "GuideItem.h"

IMPLEMENT_SINGLETON(CItemObjMgr)
CItemObjMgr::CItemObjMgr()
{
}


CItemObjMgr::~CItemObjMgr()
{
}

CObj* CItemObjMgr::Create_ItemObj(EDITID::ID _eID, float _fx, float _fy)
{
	CObj* pObj = nullptr;

	switch (_eID)
	{
	case EDITID::ID::PITEM:
		pObj = CPItem::Create({ _fx,_fy,0.f });
		break;
	case EDITID::ID::GUNITEM:
		pObj = CGunItem::Create({ _fx,_fy,0.f });
		break;
	case EDITID::ID::GUIDEITEM:
		pObj = CGuideItem::Create({ _fx,_fy,0.f });
		break;
	default:
		break;
	}
	if (!pObj)
		return nullptr;

	return pObj;
}
