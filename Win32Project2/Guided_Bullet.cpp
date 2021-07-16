#include "stdafx.h"
#include "Guided_Bullet.h"
#include "ObjMgr.h"
#include "Obj.h"


CGuided_Bullet::CGuided_Bullet()
	: m_fAngle(0.f)
{
}

CGuided_Bullet::~CGuided_Bullet()
{
}

HRESULT CGuided_Bullet::Initialize()
{
	m_tInfo.vPos = { 100.f, 100.f, 0.f };
	m_tInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(100.f, 100.f, 0.f);

	m_tObjInfo.hp = 1;
	m_tObjInfo.atk = 1;
	m_tObjInfo.spd = 30.f;
	m_tObjInfo.agl = 0.f;

	/*m_dwTime = GetTickCount();
	m_dwDelayTime = 100;*/

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	return S_OK;
}

int CGuided_Bullet::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	D3DXVECTOR3 _


	return OBJ_NOEVENT;
}

void CGuided_Bullet::Late_Update()
{
}

void CGuided_Bullet::Render(HDC _DC)
{
	MoveToEx(_DC, m_vQ[0].x, m_vQ[0].y, nullptr);

	for (int i = 1; i < 4; ++i)
	{
		LineTo(_DC, m_vQ[i].x, m_vQ[i].y);
	}

	LineTo(_DC, m_vQ[0].x, m_vQ[0].y);
}

void CGuided_Bullet::Release()
{
}

CObj * CGuided_Bullet::Find_Closest()
{
	list<Obj*>
	return nullptr;
}
