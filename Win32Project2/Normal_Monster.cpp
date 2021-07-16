#include "stdafx.h"
#include "Normal_Monster.h"


CNormal_Monster::CNormal_Monster()
{
}

CNormal_Monster::~CNormal_Monster()
{
	Release();
}

HRESULT CNormal_Monster::Initialize()
{
	m_tInfo.vPos = { 800.f, 400.f, 0.f };
	m_tInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(150.f, 100.f, 0.f);

	m_tObjInfo.hp = 1;
	m_tObjInfo.atk = 1;
	m_tObjInfo.spd = 5.f;
	m_tObjInfo.agl = 0.f;
/*
	m_dwTime = GetTickCount();
	m_dwDelayTime = 100;
*/
	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	return S_OK;
}

int CNormal_Monster::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	if (m_eState == RUN)
	{
		m_tInfo.vPos.x -= m_tObjInfo.spd;
	}
	else if(m_eState == HIT)
	{
		if (!m_tG.m_bJump)
		{
			m_tG.m_fJumpY = m_tInfo.vPos.y;
			m_tG.m_bJump = true;

		}
		m_fAngle -= 5.f;
		Hit_Jump();
	}

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);
	}

	if (IsOutside())
	{
		m_bDead = OBJ_DEAD;
	}

	return OBJ_NOEVENT;
}

void CNormal_Monster::Late_Update()
{
}

void CNormal_Monster::Render(HDC _DC)
{
	MoveToEx(_DC, m_vQ[0].x, m_vQ[0].y, nullptr);

	for (int i = 1; i < 4; ++i)
	{
		LineTo(_DC, m_vQ[i].x, m_vQ[i].y);
	}

	LineTo(_DC, m_vQ[0].x, m_vQ[0].y);
}

void CNormal_Monster::Release()
{
}
