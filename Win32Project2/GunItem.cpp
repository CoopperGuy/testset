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
	m_tInfo.vSize = D3DXVECTOR3(100.f, 100.f, 0.f);
	m_tObjInfo.hp = 1;
	m_tObjInfo.atk = 0;
	m_tObjInfo.score = 50;
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_ID::SINGLE_TEX, L"../Texture/Item/LinearItem.png", L"LinearItem");

	return S_OK;
}

int CGunItem::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	D3DXMATRIX matScale, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, (m_tInfo.vPos.x + ScrollX), m_tInfo.vPos.y, 0.f);
	matWorld = matScale * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);
	}

	return OBJ_NOEVENT;
}

void CGunItem::Late_Update()
{
}

void CGunItem::Render(HDC _DC)
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"LinearItem");
	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CGunItem::Release()
{
}

CObj * CGunItem::Create(D3DXVECTOR3 _pos)
{
	CGunItem* pInstance = new CGunItem;
	pInstance->Set_vPos(_pos);
	if (FAILED(pInstance->Initialize()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
