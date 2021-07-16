#include "stdafx.h"
#include "Jump_Monster.h"


CJump_Monster::CJump_Monster()
	: m_tRunG(50.f, 0.f, 0.f, false, false)
{
	m_eID = EDITID::JUMP_MONSTER;
}


CJump_Monster::~CJump_Monster()
{
	Release();
}

HRESULT CJump_Monster::Initialize()
{
	m_tInfo.vPos = { 800.f, 500.f, 0.f };
	m_tInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(50.f, 75.f, 0.f);

	m_tObjInfo.hp = 1;
	m_tObjInfo.atk = 1;
	m_tObjInfo.spd = 3.f;
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

int CJump_Monster::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	if (m_eState == RUN)
	{
		if (!m_tRunG.m_bJump)
		{
			m_tRunG.m_fJumpY = m_tInfo.vPos.y;
			m_tRunG.m_bJump = true;
		}
	
		Run_Jump();
	}
	else if (m_eState == HIT)
	{
		if (!m_tG.m_bJump)
		{
			m_tG.m_fJumpY = m_tInfo.vPos.y;
			m_tG.m_bJump = true;

		}
		//m_fAngle -= 5.f;
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

void CJump_Monster::Late_Update()
{
}

void CJump_Monster::Render(HDC _DC)
{
	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	MoveToEx(_DC, m_vQ[0].x + ScrollX, m_vQ[0].y, nullptr);

	for (int i = 1; i < 4; ++i)
	{
		LineTo(_DC, m_vQ[i].x + ScrollX, m_vQ[i].y);
	}

	LineTo(_DC, m_vQ[0].x + ScrollX, m_vQ[0].y);
}

void CJump_Monster::Release()
{
}

void CJump_Monster::Run_Jump()
{
	m_tInfo.vPos.x -= m_tObjInfo.spd;

	m_tInfo.vPos.y = m_tRunG.m_fJumpY
		- (m_tRunG.m_fJumpPower * m_tRunG.m_fJumpTime
			- 0.5f * 9.8f * m_tRunG.m_fJumpTime * m_tRunG.m_fJumpTime);
	m_tRunG.m_fJumpTime += 0.2f;

	if (m_tInfo.vPos.y > m_tRunG.m_fJumpY)
	{
		m_tInfo.vPos.y = m_tRunG.m_fJumpY;
		m_tRunG.m_bJump = false;
		m_tRunG.m_fJumpTime = 0.f;
	}
}
