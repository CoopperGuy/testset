#include "stdafx.h"
#include "Boss_Throw.h"


CBoss_Throw::CBoss_Throw()
	: m_bTargetLock(false)
	, m_fAngle(0.f)
	, m_vTargetDir({0.f, 0.f, 0.f})
{
}


CBoss_Throw::~CBoss_Throw()
{
	Release();
}

HRESULT CBoss_Throw::Initialize()
{
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_ID::SINGLE_TEX, L"../Texture/Monster/Boss/Boss_Throw.png", L"Boss_Throw");

	//m_tInfo.vPos = { 100.f, 100.f, 0.f };
	m_tInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(108.f, 120.f, 0.f);

	m_tObjInfo.hp = 1;
	m_tObjInfo.atk = 1;
	m_tObjInfo.spd = 10.f;
	m_tObjInfo.agl = 0.f;

	/*m_dwTime = GetTickCount();
	m_dwDelayTime = 100;*/

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	return S_OK;
}

int CBoss_Throw::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	m_fAngle += 5.f;

	if (!m_bTargetLock)
	{
		D3DXVECTOR3 _player = CObjMgr::Get_Instance()->Get_Player()->Get_Pos();
		m_vTargetDir.x = float(_player.x - m_tInfo.vPos.x);
		m_vTargetDir.y = float(_player.y + 300 - m_tInfo.vPos.y);
		D3DXVec3Normalize(&m_vTargetDir, &m_vTargetDir);
		m_bTargetLock = true;
	}
	else
	{
		m_tInfo.vPos.x += m_vTargetDir.x * m_tObjInfo.spd;
		m_tInfo.vPos.y += m_vTargetDir.y * m_tObjInfo.spd;
	}




	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	D3DXMATRIX matScale, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(-m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + ScrollX, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &m_matWorld);
	}

	if (IsFarFromPlayer())
	{
		m_bDead = OBJ_DEAD;
	}

	return OBJ_NOEVENT;
}

void CBoss_Throw::Late_Update()
{
}

void CBoss_Throw::Render(HDC _DC)
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"Boss_Throw");
	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&m_matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBoss_Throw::Release()
{
}

CObj * CBoss_Throw::Create(float _x, float _y)
{
	CBoss_Throw* pInstance = new CBoss_Throw;
	if (FAILED(pInstance->Initialize()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	pInstance->Set_Pos(_x, _y);
	
	return pInstance;
}
