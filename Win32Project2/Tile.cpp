#include "stdafx.h"
#include "Tile.h"
#include "ScrollMgr.h"

CTile::CTile()
{
}


CTile::~CTile()
{
}

HRESULT CTile::Initialize()
{
	m_tInfo.vDir = { 1.f,0.f,0.f };
	m_tInfo.vPos = { 0.f,0.f,0.f };
	m_tInfo.vSize = { 75.f,75.f,0.f };


	return S_OK;
}

int CTile::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_tInfo.vPos.x + CScrollMgr::Get_Instance()->Get_ScrollX() + m_tInfo.vSize.x < 0)
		m_bDead = true;


	return OBJ_NOEVENT;
}

void CTile::Late_Update()
{
}

void CTile::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"Terrain",L"Tile",m_iDrawID);
	if (nullptr == pTexInfo)
		return;
	float fCenterX = (float)(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = (float)(pTexInfo->tImageInfo.Height >> 1);
	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale,1.f,1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tInfo.vPos.y + CScrollMgr::Get_Instance()->Get_ScrollY(), 0.f);
	matWorld = matScale * matTrans;
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CTile::Release()
{
}
