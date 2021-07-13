#include "stdafx.h"
#include "LineMgr.h"
#include "Line.h"

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
	LINEPOS		tTemp[4] = { { 100.f, 500.f },{ 300.f, 500.f },{ 500.f, 300.f },{ 700.f, 300.f } };

	m_listLine.emplace_back(new CLine(tTemp[0], tTemp[1]));
	m_listLine.emplace_back(new CLine(tTemp[1], tTemp[2]));
	m_listLine.emplace_back(new CLine(tTemp[2], tTemp[3]));
	LINEPOS temp[2] = { { 120.f,100.f } ,{ 280.f,390.f } };

	m_listLine.emplace_back(new CLine(temp[0], temp[1]));
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
