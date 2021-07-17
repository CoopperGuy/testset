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

	

	return S_OK;
}

int CPItem::Update()
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

void CPItem::Late_Update()
{
}

void CPItem::Render(HDC _DC)
{
}

void CPItem::Release()
{
}

CObj * CPItem::Create(D3DXVECTOR3 _pos)
{
	CPItem* pInstance = new CPItem;
	pInstance->Set_Item(ItemTag);
	pInstance->Set_vPos(_pos);
	if (FAILED(pInstance->Initialize()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
