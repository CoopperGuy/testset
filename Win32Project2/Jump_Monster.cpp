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
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_ID::SINGLE_TEX, L"../Texture/Monster/Jump_Monster/Jump_Monster.png", L"Jump_Monster");

	m_tInfo.vPos = { 800.f, 500.f, 0.f };
	m_tInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(50.f, 75.f, 0.f);

	m_tObjInfo.hp = 1;
	m_tObjInfo.atk = 1;
	m_tObjInfo.spd = 1.f;
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
		m_fAngle -= 5.f;
		Hit_Jump();
	}

	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	D3DXMATRIX matScale, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + ScrollX, m_tInfo.vPos.y, m_tInfo.vPos.z);
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
	
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"Jump_Monster");
	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
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
