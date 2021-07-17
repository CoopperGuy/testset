#include "stdafx.h"
#include "TileMgr.h"
#include "Tile.h"
#include "ScrollMgr.h"

IMPLEMENT_SINGLETON(CTileMgr)
CTileMgr::CTileMgr()
{
	m_vecTile.reserve(TILEX * TILEY);
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Terrain/Tile/Tile0%d.png", L"Terrain",L"Tile",3)))
		return;

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float	fX = (float)((TILECX >> 1) + (j * TILECX));
			float	fY = (float)((TILECY >> 1) + (i * TILECY));

			m_vecTile.emplace_back(CAbstractFactory<CTile>::Create(fX, fY));
		}
	}
}

void CTileMgr::Render(HDC _DC)
{
	int	iCullX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX() / TILECX);
	int	iCullY = 0;

	int iCullEndX = iCullX + (WINCX / TILECX) + 2;
	int iCullEndY = iCullY + (WINCY / TILECY) + 2;

	for (int i = iCullY; i < iCullEndY; ++i)
	{
		for (int j = iCullX; j < iCullEndX; ++j)
		{
			int iIdx = i * TILEX + j;

			if (0 > iIdx || m_vecTile.size() <= (size_t)iIdx)
				continue;

			m_vecTile[iIdx]->Render(_DC);
		}
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
	int y = pt.y / TILECY;

	int iIdx = y * TILEX + x;

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
