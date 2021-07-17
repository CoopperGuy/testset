#include "stdafx.h"
#include "ObjMgr.h"

#include "Obj.h"
#include "Player.h"
#include "Monster.h"

#include "MonObjMgr.h"
#include "MapObjMgr.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"

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

	//CCollisionMgr::COllision_Bulllet_Monster(m_listObj[OBJID::PLAYERBULLET], m_listObj[OBJID::MONSTER]);
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
	CCollisionMgr::Collision_Player_Item(m_listObj[OBJID::PLAYER], m_listObj[OBJID::ITEM]);
	CCollisionMgr::Collision_Player_Monster(m_listObj[OBJID::PLAYER], m_listObj[OBJID::MONSTER]);
	CCollisionMgr::COllision_Bulllet_Monster(m_listObj[OBJID::PLAYERBULLET], m_listObj[OBJID::MONSTER]);

}

void CObjMgr::Render(HDC _DC)
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
			pObj->Render(_DC);
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

void CObjMgr::Picking_Obj(EDITID::ID _editid)
{
	POINT	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	int x = (pt.x / TILECX)* TILECX + (TILECX >> 1);
	int y = (pt.y / TILECY)* TILECY + (TILECY >> 1);

	switch (_editid)
	{
	case EDITID::PLAYER:
	{
		if (!m_listObj[OBJID::PLAYER].empty())
		{
			Safe_Delete(m_listObj[OBJID::PLAYER].front());
			m_listObj[OBJID::PLAYER].clear();
		}
		CObj* pObj = CAbstractFactory<CPlayer>::Create((float)pt.x, (float)pt.y);
		m_listObj[OBJID::PLAYER].emplace_back(pObj);
	}
	break;
	case EDITID::TESTMON:
	{
		CObj* pObj = CMonObjMgr::Get_Instance()->Create_Monster(_editid, (float)x, (float)y);
		m_listObj[OBJID::MONSTER].emplace_back(pObj);
	}
	break;
	case EDITID::MONSTERDEL:
	{
		for (auto& iter = m_listObj[OBJID::MONSTER].begin(); iter != m_listObj[OBJID::MONSTER].end(); ++iter)
		{
			if ((*iter)->Get_Pos().x == x && (*iter)->Get_Pos().y == y)
			{
				Safe_Delete(*iter);
				m_listObj[OBJID::MONSTER].erase(iter);
				return;
			}
		}
	}
	break;
	default:
		break;
	}
}

void CObjMgr::Save_Player()
{
	HANDLE hFile = CreateFile(L"../Data/Player.dat", GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Player 저장 실패!", L"실패", MB_OK);
		return;
	}

	DWORD dwByte = 0;

	for (auto& pPlayer : m_listObj[OBJID::PLAYER])
	{
		WriteFile(hFile, &pPlayer->Get_Info(), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &pPlayer->Get_ObjInfo(), sizeof(OBJINFO), &dwByte, NULL);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Player 저장 성공!", L"성공", MB_OK);
}

void CObjMgr::Load_Player()
{
	HANDLE hFile = CreateFile(L"../Data/Player.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Player 불러오기 실패!", L"실패", MB_OK);
		return;
	}

	DWORD		dwByte = 0;
	INFO		tInfo = {};
	OBJINFO		tObjInfo = {0, 0, 0, 0.f, 0.f};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &tObjInfo, sizeof(OBJINFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<CPlayer>::Create(tInfo.vPos.x, tInfo.vPos.y);
		pObj->Set_ObjInfo(tObjInfo);

		m_listObj[OBJID::PLAYER].emplace_back(pObj);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Player 불러오기 성공!", L"성공", MB_OK);
}

void CObjMgr::Save_Monster()
{
	HANDLE hFile = CreateFile(L"../Data/Monster.dat", GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Monster 저장 실패!", L"실패", MB_OK);
		return;
	}

	DWORD dwByte = 0;

	for (auto& pMonster : m_listObj[OBJID::MONSTER])
	{
		WriteFile(hFile, &(static_cast<CMonster*>(pMonster))->Get_ID(), sizeof(EDITID::ID), &dwByte, NULL);
		WriteFile(hFile, &pMonster->Get_Info(), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &pMonster->Get_ObjInfo(), sizeof(OBJINFO), &dwByte, NULL);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Monster 저장 성공!", L"성공", MB_OK);
}

void CObjMgr::Load_Monster()
{
	HANDLE hFile = CreateFile(L"../Data/Monster.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Monster 불러오기 실패!", L"실패", MB_OK);
		return;
	}

	Release();

	DWORD		dwByte = 0;
	EDITID::ID	eID = EDITID::END;
	INFO		tInfo = {};
	OBJINFO		tObjInfo = { 0, 0, 0, 0.f, 0.f };

	while (true)
	{
		ReadFile(hFile, &eID, sizeof(EDITID::ID), &dwByte, NULL);
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &tObjInfo, sizeof(OBJINFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CObj* pObj = nullptr;

		switch (eID)
		{
		case EDITID::TESTMON:
			pObj = CMonObjMgr::Get_Instance()->Create_Monster(eID, tInfo.vPos.x, tInfo.vPos.y);
			break;
		case EDITID::MONSTER2:
			break;
		case EDITID::END:
			break;
		default:
			break;
		}
		if (!pObj)
			return;

		pObj->Set_ObjInfo(tObjInfo);

		m_listObj[OBJID::MONSTER].emplace_back(pObj);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Monster 불러오기 성공!", L"성공", MB_OK);
}

CObj * CObjMgr::Get_Target(CObj * _pObject, OBJID::ID _eID)
{
	if (m_listObj[_eID].empty())
	{
		return nullptr;
	}

	CObj* pTarget = nullptr;
	float fDistance = 0.f;

	for (auto& Dst : m_listObj[_eID])
	{
		float fX = Dst->Get_Pos().x - _pObject->Get_Pos().x;
		float fY = Dst->Get_Pos().y - _pObject->Get_Pos().y;
		float fDia = sqrtf(fX * fX + fY * fY);

		if (fDistance > fDia || !pTarget)
		{
			pTarget = Dst;
			fDistance = fDia;
		}
	}

	return pTarget;
}

