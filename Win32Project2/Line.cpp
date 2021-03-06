#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"

CLine::CLine()
	: m_bDead(false)
{
}


CLine::CLine(LINEPOS& _tLeftPos, LINEPOS& _tRightPos)
	: m_tInfo(_tLeftPos, _tRightPos)
	, m_bDead(false)
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

int CLine::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_tInfo.tRightPos.fX + CScrollMgr::Get_Instance()->Get_ScrollX() < 0)
		m_bDead = true;


	return OBJ_NOEVENT;
}

void CLine::Render(HDC _DC)
{
	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	MoveToEx(_DC, (int)m_tInfo.tLeftPos.fX + ScrollX, (int)m_tInfo.tLeftPos.fY, nullptr);
	LineTo(_DC, (int)m_tInfo.tRightPos.fX + ScrollX, (int)m_tInfo.tRightPos.fY);
}

void CLine::Release()
{

}

float CLine::Get_LineY(float _x) 
{
	float x1 = m_tInfo.tLeftPos.fX;
	float y1 = m_tInfo.tLeftPos.fY;
	float x2 = m_tInfo.tRightPos.fX;
	float y2 = m_tInfo.tRightPos.fY;

	return	((y2 - y1) / (x2 - x1)) * (_x - x1) + y1;

	// TODO: 여기에 반환 구문을 삽입합니다.
}
