#include "stdafx.h"
#include "LineMgr.h"
#include "Line.h"
#include "ScrollMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;
CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize()
{
	for (int i = 0; i < TILEX; ++i)
	{
		CLine* temp = new CLine(LINEPOS{i*100.f, 500.f}, LINEPOS{ (i+1) * 100.f, 500.f });
		m_listLine.emplace_back(temp);
	}
}

void CLineMgr::Render(HDC _DC)
{
	for (auto& pLine : m_listLine)
		pLine->Render(_DC);
}

void CLineMgr::Release()
{
	for_each(m_listLine.begin(), m_listLine.end(), Safe_Delete<CLine*>);
	m_listLine.clear();
}

bool CLineMgr::Collision_Line(float _x, float _y1, float* _y, bool* _bG)
{
	if (m_listLine.empty())
		return false;
	CLine* templ = nullptr;
	float ymin = 9999999.f;
	for (auto& pLine : m_listLine)
	{
		if (pLine->Get_Info().tLeftPos.fX <= _x
			&& pLine->Get_Info().tRightPos.fX >= _x
			)
		{
			if (abs(pLine->Get_LineY(_x) - _y1) <= ymin) {
				if (_y1 - 10.f <= pLine->Get_LineY(_x)) {
					templ = pLine;
					ymin = (pLine->Get_LineY(_x) - _y1);
				}
			}
		}
	}

	if (nullptr != templ) {

		float x1 = templ->Get_Info().tLeftPos.fX;
		float y1 = templ->Get_Info().tLeftPos.fY;
		float x2 = templ->Get_Info().tRightPos.fX;
		float y2 = templ->Get_Info().tRightPos.fY;

		*_y = ((y2 - y1) / (x2 - x1)) * (_x - x1) + y1;

		if (*_y - _y1 > 65.f) {
			*_bG = true;
		}

		return true;
	}


	return false;
}

void CLineMgr::Picking_Line()
{
	POINT	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	int x = (pt.x / TILECX)*100;

	
	for (auto& iter = m_listLine.begin(); iter != m_listLine.end(); ++iter)
	{
		if ((*iter)->Get_Info().tLeftPos.fX == x)
		{
			m_listLine.erase(iter);
			return;
		}
	}
	CLine* temp = new CLine(LINEPOS{ (float)x, 500.f }, LINEPOS{ x + 100.f, 500.f });
	m_listLine.emplace_back(temp);
}

void CLineMgr::Save_Line()
{
	HANDLE hFile = CreateFile(L"../Data/Line.dat", GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Line 저장 실패!", L"실패", MB_OK);
		return;
	}

	DWORD dwByte = 0;

	for (auto& pLine : m_listLine)
		WriteFile(hFile, &pLine->Get_Info(), sizeof(LINEINFO), &dwByte, NULL);

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Line 저장 성공!", L"성공", MB_OK);

}

void CLineMgr::Load_Line()
{
	HANDLE hFile = CreateFile(L"../Data/Line.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Line 불러오기 실패!", L"실패", MB_OK);
		return;
	}

	Release();

	DWORD		dwByte = 0;
	LINEINFO	tInfo = {};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CLine* pLine = new CLine{ tInfo.tLeftPos, tInfo.tRightPos };

		m_listLine.emplace_back(pLine);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Line 불러오기 성공!", L"성공", MB_OK);

}
