#include "stdafx.h"
#include "Line.h"


CLine::CLine()
{
}


CLine::CLine(LINEPOS& _tLeftPos, LINEPOS& _tRightPos)
	: m_tInfo(_tLeftPos, _tRightPos)
{

}

CLine::~CLine()
{
	Release();
}

HRESULT CLine::Initialize()
{
	return S_OK;
}

void CLine::Render(HDC _DC)
{
	MoveToEx(_DC, (int)m_tInfo.tLeftPos.fX, (int)m_tInfo.tLeftPos.fY, nullptr);
	LineTo(_DC, (int)m_tInfo.tRightPos.fX, (int)m_tInfo.tRightPos.fY);
}

void CLine::Release()
{
}

const float & CLine::Get_LineY(float _x) const
{
	float x1 = m_tInfo.tLeftPos.fX;
	float y1 = m_tInfo.tLeftPos.fY;
	float x2 = m_tInfo.tRightPos.fX;
	float y2 = m_tInfo.tRightPos.fY;

	return	((y2 - y1) / (x2 - x1)) * (_x - x1) + y1;

	// TODO: 여기에 반환 구문을 삽입합니다.
}
