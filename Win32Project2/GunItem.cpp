#include "stdafx.h"
#include "GunItem.h"


CGunItem::CGunItem()
{
}


CGunItem::~CGunItem()
{
}

HRESULT CGunItem::Initialize()
{
	ItemTag = CItem::ITEMTAG::ITEM_GUN;
	m_tInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(10.f, 10.f, 0.f);
	m_tObjInfo.hp = 1;
	m_tObjInfo.atk = 0;
	m_tObjInfo.score = 50;

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	return S_OK;
}

int CGunItem::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	matWorld = matScale  * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);
	}

	return OBJ_DEAD;
}

void CGunItem::Late_Update()
{
}

void CGunItem::Render(HDC _DC)
{
}

void CGunItem::Release()
{
}

CObj * CGunItem::Create(D3DXVECTOR3 _pos)
{
	CGunItem* pInstance = new CGunItem;
	pInstance->Set_Item(ItemTag);
	pInstance->Set_vPos(_pos);
	if (FAILED(pInstance->Initialize()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
