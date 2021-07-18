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
	Release();
}

HRESULT CGuided_Bullet::Initialize()
{
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_ID::SINGLE_TEX, L"../Texture/Bullet/Guided_Bullet.png", L"Guided_Bullet");

	m_tInfo.vPos = { 100.f, 100.f, 0.f };
	m_tInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(70.f, 49.f, 0.f);

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

int CGuided_Bullet::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	CObj* m_pTarget = CObjMgr::Get_Instance()->Get_TargetMonster(this);

	if (m_pTarget == nullptr)
	{
		m_tInfo.vPos.x += m_tObjInfo.spd;
	}
	else
	{
		float rad = acosf((m_pTarget->Get_Pos().x - m_tInfo.vPos.x)
			/ sqrtf((m_pTarget->Get_Pos().x - m_tInfo.vPos.x) * (m_pTarget->Get_Pos().x - m_tInfo.vPos.x)
				+ (m_pTarget->Get_Pos().y - m_tInfo.vPos.y) * (m_pTarget->Get_Pos().y - m_tInfo.vPos.y)));

		if (m_tInfo.vPos.y < m_pTarget->Get_Pos().y)
		{
			rad *= -1.f;
		}
		m_fAngle = rad * 180 / 3.141592f;

		m_tInfo.vPos.x += cosf(m_fAngle * 3.141592f / 180.f) * m_tObjInfo.spd;
		m_tInfo.vPos.y -= sinf(m_fAngle * 3.141592f / 180.f) * m_tObjInfo.spd;
	}

	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	D3DXMATRIX matScale, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
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

void CGuided_Bullet::Late_Update()
{
}

void CGuided_Bullet::Render(HDC _DC)
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"Guided_Bullet");
	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);
	
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&m_matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CGuided_Bullet::Release()
{
}

CObj * CGuided_Bullet::Create(float _x, float _y)
{
	CGuided_Bullet* pInstance = new CGuided_Bullet;
	if (FAILED(pInstance->Initialize()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	pInstance->Set_Pos(_x, _y);

	return pInstance;
}
