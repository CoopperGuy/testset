#include "stdafx.h"
#include "PItem.h"


CPItem::CPItem()
{
}


CPItem::~CPItem()
{
	Release();
}

HRESULT CPItem::Initialize()
{
	ItemTag = CItem::ITEMTAG::ITEM_POINT;
	m_tInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(10.f, 10.f, 0.f);
	m_tObjInfo.hp = 1;
	m_tObjInfo.atk = 0;
	m_tObjInfo.score = 100;

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	return S_OK;
}

int CPItem::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(00.f));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);
	}

	return OBJ_DEAD;
}

void CPItem::Late_Update()
{
}

void CPItem::Render(HDC _DC)
{
}

void CPItem::Release()
{
}

CObj * CPItem::Create()
{
	CPItem* pInstance = new CPItem;
	if (FAILED(pInstance->Initialize()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
