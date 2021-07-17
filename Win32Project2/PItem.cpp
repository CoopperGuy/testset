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
	m_tInfo.vSize = D3DXVECTOR3(30.f, 30.f, 0.f);

	m_tObjInfo.hp = 1;
	m_tObjInfo.atk = 0;
	m_tObjInfo.score = 100;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Item/PItem0%d.png", L"Item", L"PItem", 3 , m_tInfo.vSize.x,m_tInfo.vSize.y)))
		return S_FALSE;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.CurID = 0;
	m_tFrame.EndId = 3;
	m_tFrame.dwDelayTime = 100;
	m_tFrame.m_pFrameKey = L"PItem";

	return S_OK;
}

int CPItem::Update()
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

void CPItem::Late_Update()
{
}

void CPItem::Render(HDC _DC)
{
	Update_Frame();
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"Item", m_tFrame.m_pFrameKey, m_tFrame.CurID);
 	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CPItem::Release()
{
}

void CPItem::Update_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelayTime < GetTickCount()) {
		m_tFrame.CurID++;
		if (m_tFrame.CurID == m_tFrame.EndId) {
			m_tFrame.CurID = 0;
		}
		m_tFrame.dwTime = GetTickCount();
	}
}

CObj * CPItem::Create(D3DXVECTOR3 _pos)
{
	CPItem* pInstance = new CPItem;
	pInstance->Set_vPos(_pos);
	if (FAILED(pInstance->Initialize()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
