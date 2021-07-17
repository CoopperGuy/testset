#include "stdafx.h"
#include "TileMgr.h"
#include "Tile.h"
#include "ScrollMgr.h"

IMPLEMENT_SINGLETON(CTileMgr)
CTileMgr::CTileMgr()
{
	m_vecTile.reserve(TILEX);
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Terrain/Tile/Tile0%d.png", L"Terrain",L"Tile",3)))
		return;

	for (int i = 0; i < TILEX; ++i)
	{
			float	fX = (float)((TILECX >> 1) + (i * TILECX));
			float	fY = (float)(WINCY - (TILECY>>1));

			m_vecTile.emplace_back(CAbstractFactory<CTile>::Create(fX, fY));
	}
}

void CTileMgr::Update()
{
	auto& iter = m_vecTile.begin();
	for (; iter != m_vecTile.end(); )
		{
			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				SAFE_DELETE(*iter);
				iter = m_vecTile.erase(iter);
			}
			else
				++iter;
		}

	if (m_vecTile.size() <= 20)
	{
		CObj* pObj = (CAbstractFactory<CTile>::Create(m_vecTile.back()->Get_Pos().x + m_vecTile.back()->Get_Size().x, (float)(WINCY - (TILECY >> 1))));
		static_cast<CTile*>(pObj)->Set_DrawID(1);

		m_vecTile.emplace_back(pObj);
	}
}




void CTileMgr::Render(HDC _DC)
{
	auto iter = m_vecTile.begin();
	for (; iter != m_vecTile.end();  ++iter)
	{
		(*iter)->Render(_DC);
	}
	
}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
}

void CTileMgr::Picking_Tile(int _iDrawID)
{
	POINT	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	int x = pt.x / TILECX;

	int iIdx = x;

	if (0 > iIdx || m_vecTile.size() <= (size_t)iIdx)
		return;

	static_cast<CTile*>(m_vecTile[iIdx])->Set_DrawID(_iDrawID);
}

void CTileMgr::Save_Tile()
{
	HANDLE hFile = CreateFile(L"../Data/Tile.dat", GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Tile 저장 실패!", L"실패", MB_OK);
		return;
	}

	DWORD dwByte = 0;

	for (auto& pTile : m_vecTile)
	{
		WriteFile(hFile, &pTile->Get_Info(), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &(static_cast<CTile*>(pTile)->Get_DrawID()), sizeof(int), &dwByte, NULL);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile 저장 성공!", L"성공", MB_OK);
}

void CTileMgr::Load_Tile()
{
	HANDLE hFile = CreateFile(L"../Data/Tile.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Tile 불러오기 실패!", L"실패", MB_OK);
		return;
	}

	Release();

	DWORD	dwByte = 0;
	INFO	tInfo = {};
	int		iDrawID = 0;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<CTile>::Create(tInfo.vPos.x, tInfo.vPos.y);
		static_cast<CTile*>(pObj)->Set_DrawID(iDrawID);

		m_vecTile.emplace_back(pObj);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile 불러오기 성공!", L"성공", MB_OK);
}
