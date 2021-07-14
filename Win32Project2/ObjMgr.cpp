#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "Obj.h"
CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		auto iter = m_listObj[i].begin();
		for (; iter != m_listObj[i].end(); )
		{
			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				SAFE_DELETE(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;
		}
	}
	//	Get_Player()->Update();
}

void CObjMgr::Late_Update()
{

	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
		{
			pObj->Late_Update();

			if (m_listObj[i].empty())
				break;
		}
	}
	

}

void CObjMgr::Render(HDC _DC)
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
			pObj->Render(_DC);
	}
	//테스트용으로 내림 lateupdate로 올려야함
	for (auto& iter : m_listObj[OBJID::MONSTER]) {
		if (CCollisionMgr::Collision_OBB(m_listObj[OBJID::PLAYER].front(), iter)) {
			TextOutW(_DC, 100, 100, L"collision", sizeof("collision"));
		}
		else {
			TextOutW(_DC, 200, 100, L"nocollision", sizeof("nocollision"));

		}
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_listObj[i].begin(), m_listObj[i].end(), Safe_Delete<CObj*>);
		m_listObj[i].clear();
	}
}

