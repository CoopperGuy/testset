#include "stdafx.h"
#include "Linear_Bullet.h"


CLinear_Bullet::CLinear_Bullet()
{
}

CLinear_Bullet::~CLinear_Bullet()
{
	Release();
}

HRESULT CLinear_Bullet::Initialize()
{
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_ID::SINGLE_TEX, L"../Texture/Bullet/Linear_Bullet.png", L"Linear_Bullet");

	//m_tInfo.vPos = { 100.f, 100.f, 0.f };
	m_tInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(68.f, 34.f, 0.f);

	m_tObjInfo.hp = 1;
	m_tObjInfo.atk = 1;
	m_tObjInfo.spd = 15.f;
	m_tObjInfo.agl = 0.f;

	/*m_dwTime = GetTickCount();
	m_dwDelayTime = 100;*/

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	return S_OK;
}

int CLinear_Bullet::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	m_tInfo.vPos.x += m_tObjInfo.spd;

	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	D3DXMATRIX matScale, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.f));
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

void CLinear_Bullet::Late_Update()
{
}

void CLinear_Bullet::Render(HDC _DC)
{
	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"Linear_Bullet");
	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);
	
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&m_matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CLinear_Bullet::Release()
{
}

CObj * CLinear_Bullet::Create(float _x, float _y)
{
	CLinear_Bullet* pInstance = new CLinear_Bullet;
	pInstance->Set_Pos(_x, _y);
	if (FAILED(pInstance->Initialize()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
