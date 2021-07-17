#include "stdafx.h"
#include "Obj.h"

CObj::CObj() :m_bDead(OBJ_NOEVENT), m_tObjInfo(1, 0,0, 5.f, 0.f)
{
	ZeroMemory(m_vP, sizeof(D3DXVECTOR3) * 4);
	ZeroMemory(m_vQ, sizeof(D3DXVECTOR3) * 4);
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_matWorld, sizeof(D3DXMATRIX));
}


CObj::~CObj()
{
}

void CObj::Check_State()
{
}

void CObj::Update_State()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelayTime < GetTickCount()) {
		m_tFrame.CurID++;
		if (m_tFrame.CurID == m_tFrame.EndId) {
			m_tFrame.CurID = 0;
		}
		m_tFrame.dwTime = GetTickCount();
	}
}
