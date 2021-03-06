#include "stdafx.h"
#include "ObjMgr.h"

#include "Obj.h"
#include "Player.h"
#include "Monster.h"
#include "MapObj.h"

#include "MonObjMgr.h"
#include "MapObjMgr.h"
#include "ItemObjMgr.h"
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

	CCollisionMgr::COllision_Bulllet_Monster(m_listObj[OBJID::PLAYERBULLET], m_listObj[OBJID::MONSTER]);
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
	// Item 面倒
	CCollisionMgr::Collision_Player_Item(m_listObj[OBJID::PLAYER], m_listObj[OBJID::ITEM]);
	// Monster 面倒
	CCollisionMgr::Collision_Player_Monster(m_listObj[OBJID::PLAYER], m_listObj[OBJID::MONSTER]);
	// MapObj 面倒
	CCollisionMgr::Collision_Player_Obstacle(m_listObj[OBJID::PLAYER], m_listObj[OBJID::MAPOBJ]);
	// Player Bullet 面倒
	CCollisionMgr::COllision_Bulllet_Monster(m_listObj[OBJID::PLAYERBULLET], m_listObj[OBJID::MONSTER]);
	// Boss Bullet 面倒
	CCollisionMgr::COllision_Player_BossThing(m_listObj[OBJID::PLAYER], m_listObj[OBJID::BOSSBULLET]);
	CCollisionMgr::COllision_Player_BossThing(m_listObj[OBJID::PLAYER], m_listObj[OBJID::BOSSTHROW]);
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
	
	//Player
	case EDITID::PLAYER:
	{
		if (!m_listObj[OBJID::PLAYER].empty())
		{
			Safe_Delete(m_listObj[OBJID::PLAYER].front());
			m_listObj[OBJID::PLAYER].clear();
		}
		CObj* pObj = CPlayer::Create((float)x, (float)y);
		m_listObj[OBJID::PLAYER].emplace_back(pObj);
	}
	break;

	// Monster
	case EDITID::NORMAL_MONSTER:
	case EDITID::JUMP_MONSTER:
	case EDITID::BOSS:
		if (_editid == EDITID::JUMP_MONSTER)
			y -= 20;
	{
		CObj* pObj = CMonObjMgr::Get_Instance()->Create_Monster(_editid, (float)x, (float)y);
		m_listObj[OBJID::MONSTER].emplace_back(pObj);
	}
	break;
	case EDITID::MONSTERDEL:
	{
		for (auto& iter = m_listObj[OBJID::MONSTER].begin(); iter != m_listObj[OBJID::MONSTER].end(); ++iter)
		{
			if ((*iter)->Get_Pos().x == x && (*iter)->Get_Pos().y == y || ((*iter)->Get_Pos().y == y - 20))
			{
				Safe_Delete(*iter);
				m_listObj[OBJID::MONSTER].erase(iter);
				return;
			}
		}
	}
	break;

	// MapObj
	case EDITID::ID::MAPTOTEM:
		y += 50;
	case EDITID::ID::MAPSWORD:
	case EDITID::ID::MAPMOVETRI:
	case EDITID::ID::MAPTRI:
	{
		CObj* pObj = CMapObjMgr::Get_Instance()->Create_MapObj(_editid, (float)x, (float)y);
		m_listObj[OBJID::MAPOBJ].emplace_back(pObj);
	}
		break;
	case EDITID::MAPDEL:
	{
		for (auto& iter = m_listObj[OBJID::MAPOBJ].begin(); iter != m_listObj[OBJID::MAPOBJ].end(); ++iter)
		{
			if (((*iter)->Get_Pos().x == x) && (((*iter)->Get_Pos().y == y) || ((*iter)->Get_Pos().y == y +50 )))
			{
				Safe_Delete(*iter);
				m_listObj[OBJID::MAPOBJ].erase(iter);
				return;
			}
		}
	}
	break;
	case EDITID::ID::PITEM:
	case EDITID::ID::GUNITEM:
	case EDITID::ID::GUIDEITEM:
	{
		int x = (pt.x / (TILECX >> 1))* (TILECX >> 1) + (TILECX >> 1);
		int y = (pt.y / (TILECY >> 1))* (TILECY >> 1) + (TILECY >> 1);

		CObj* pObj = CItemObjMgr::Get_Instance()->Create_ItemObj(_editid, (float)x, (float)y);
		m_listObj[OBJID::ITEM].emplace_back(pObj);
		}
		break;
	case EDITID::ITEMDEL:
	{
		int x = (pt.x / (TILECX >> 1))* (TILECX >> 1) + (TILECX >> 1);
		int y = (pt.y / (TILECY >> 1))* (TILECY >> 1) + (TILECY >> 1);

		for (auto& iter = m_listObj[OBJID::ITEM].begin(); iter != m_listObj[OBJID::ITEM].end(); ++iter)
		{
			if (((*iter)->Get_Pos().x == x) && (((*iter)->Get_Pos().y == y)))
			{
				Safe_Delete(*iter);
				m_listObj[OBJID::ITEM].erase(iter);
				return;
			}
		}
	}
	// Item

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
		MessageBox(g_hWnd, L"Player 历厘 角菩!", L"角菩", MB_OK);
		return;
	}

	DWORD dwByte = 0;

	for (auto& pPlayer : m_listObj[OBJID::PLAYER])
	{
		WriteFile(hFile, &pPlayer->Get_Info(), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &pPlayer->Get_ObjInfo(), sizeof(OBJINFO), &dwByte, NULL);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Player 历厘 己傍!", L"己傍", MB_OK);
}

void CObjMgr::Load_Player()
{
	HANDLE hFile = CreateFile(L"../Data/Player.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Player 阂矾坷扁 角菩!", L"角菩", MB_OK);
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

		m_listObj[OBJID::PLAYER].emplace_back(pObj);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Player 阂矾坷扁 己傍!", L"己傍", MB_OK);
}

void CObjMgr::Save_Monster()
{
	HANDLE hFile = CreateFile(L"../Data/Monster/Monster.dat", GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Monster 历厘 角菩!", L"角菩", MB_OK);
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
	MessageBox(g_hWnd, L"Monster 历厘 己傍!", L"己傍", MB_OK);
}

void CObjMgr::Load_Monster()
{
	HANDLE hFile = CreateFile(L"../Data/Monster/Monster.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Monster 阂矾坷扁 角菩!", L"角菩", MB_OK);
		return;
	}

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

		CObj* pObj = CMonObjMgr::Get_Instance()->Create_Monster(eID, tInfo.vPos.x, tInfo.vPos.y);

		if (!pObj)
			return;

		pObj->Set_Info(tInfo);

		m_listObj[OBJID::MONSTER].emplace_back(pObj);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Monster 阂矾坷扁 己傍!", L"己傍", MB_OK);
}

void CObjMgr::Save_MapObj()
{
	HANDLE hFile = CreateFile(L"../Data/MapObj.dat", GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"MapObj 历厘 角菩!", L"角菩", MB_OK);
		return;
	}

	DWORD dwByte = 0;

	for (auto& pMapObj : m_listObj[OBJID::MAPOBJ])
	{
		WriteFile(hFile, &(static_cast<CMapObj*>(pMapObj))->Get_ID(), sizeof(EDITID::ID), &dwByte, NULL);
		WriteFile(hFile, &pMapObj->Get_Info(), sizeof(INFO), &dwByte, NULL);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"MapObj 历厘 己傍!", L"己傍", MB_OK);

}

void CObjMgr::Load_MapObj()
{
	HANDLE hFile = CreateFile(L"../Data/MapObj.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"MapObj 阂矾坷扁 角菩!", L"角菩", MB_OK);
		return;
	}

	DWORD		dwByte = 0;
	EDITID::ID	eID = EDITID::END;
	INFO		tInfo = {};

	while (true)
	{
		ReadFile(hFile, &eID, sizeof(EDITID::ID), &dwByte, NULL);
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CObj* pObj = CMapObjMgr::Get_Instance()->Create_MapObj(eID, tInfo.vPos.x, tInfo.vPos.y);

		if (!pObj)
			return;

		pObj->Set_Info(tInfo);

		m_listObj[OBJID::MAPOBJ].emplace_back(pObj);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"MapObj 阂矾坷扁 己傍!", L"己傍", MB_OK);

}

void CObjMgr::Save_Item()
{
	HANDLE hFile = CreateFile(L"../Data/Item.dat", GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Item 历厘 角菩!", L"角菩", MB_OK);
		return;
	}

	DWORD dwByte = 0;

	for (auto& pItem : m_listObj[OBJID::ITEM])
	{
		WriteFile(hFile, &(static_cast<CItem*>(pItem))->Get_ID(), sizeof(EDITID::ID), &dwByte, NULL);
		WriteFile(hFile, &pItem->Get_Info(), sizeof(INFO), &dwByte, NULL);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Item 历厘 己傍!", L"己傍", MB_OK);

}

void CObjMgr::Load_Item()
{
	HANDLE hFile = CreateFile(L"../Data/Item.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Item 阂矾坷扁 角菩!", L"角菩", MB_OK);
		return;
	}

	DWORD			dwByte = 0;
	EDITID::ID		eID = EDITID::ID::END;
	INFO			tInfo = {};

	while (true)
	{
		ReadFile(hFile, &eID, sizeof(EDITID::ID), &dwByte, NULL);
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CObj* pObj = CItemObjMgr::Get_Instance()->Create_ItemObj(eID, tInfo.vPos.x, tInfo.vPos.y);

		if (!pObj)
			return;

		pObj->Set_Info(tInfo);

		m_listObj[OBJID::ITEM].emplace_back(pObj);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Item 阂矾坷扁 己傍!", L"己傍", MB_OK);
}

CObj* CObjMgr::Get_TargetMonster(CObj * _pObject)
{
	if (m_listObj[OBJID::MONSTER].empty())
	{
		return nullptr;
	}

	CObj* pTarget = nullptr;
	float fDistance = 0.f;

	for (auto& Dst : m_listObj[OBJID::MONSTER])
	{
		if (!(static_cast<CMonster*>(Dst)->IsHit()))
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
	}

	return pTarget;
}

