#include "stdafx.h"
#include "Normal_Monster.h"
#include "Texture_Manager.h"


CNormal_Monster::CNormal_Monster()
	: m_iDrawID(0)
	, m_iMaxDrawID(3)
{
	m_eID = EDITID::NORMAL_MONSTER;
}

CNormal_Monster::~CNormal_Monster()
{
	Release();
}

HRESULT CNormal_Monster::Initialize()
{
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Monster/Normal_Monster/Normal_Monster%d.png", L"Normal_Monster", L"Run", 4);

	m_tInfo.vPos = { 800.f, 400.f, 0.f };
	m_tInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(100.f, 85.f, 0.f);

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
	else if (m_eState == HIT)
	{
		if (!m_tG.m_bJump)
		{
			m_tG.m_fJumpY = m_tInfo.vPos.y;
			m_tG.m_bJump = true;

		}
		m_fAngle += 2.f;
		Hit_Jump();
	}

	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	D3DXMATRIX matScale, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + ScrollX, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &m_matWorld);
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
	//int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	++m_iDrawID;
	if (m_eState == HIT || m_iDrawID > m_iMaxDrawID)
	{
		m_iDrawID = 0;
	}

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"Normal_Monster", L"Run", m_iDrawID);
	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&m_matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	
}

void CNormal_Monster::Release()
{
}
