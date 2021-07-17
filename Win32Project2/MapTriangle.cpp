#include "stdafx.h"
#include "MapTriangle.h"


CMapTriangle::CMapTriangle()
{
}


CMapTriangle::~CMapTriangle()
{
}

HRESULT CMapTriangle::Initialize()
{
	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_tInfo.vPos = { 0.f, 0.f, 0.f };
	m_tInfo.vSize = { 75.f, 75.f, 0.f };

	m_eID = EDITID::MAPTRI;

	m_dwTime = 0;
	m_dwDelayTime = 50;

	m_iDrawID = rand()%2;

	return S_OK;
}

int CMapTriangle::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	// ав╫ю╢о╢ы
	if (m_tInfo.vPos.x + CScrollMgr::Get_Instance()->Get_ScrollX() + m_tInfo.vSize.x < 0)
		m_bDead = true;

	return OBJ_NOEVENT;
}

void CMapTriangle::Late_Update()
{
}

void CMapTriangle::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"MapObject", L"Triangle", m_iDrawID);
	if (nullptr == pTexInfo)
		return;
	float fCenterX = (float)(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = (float)(pTexInfo->tImageInfo.Height >> 1);
	D3DXMATRIX matScale, matTrans;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tInfo.vPos.y + CScrollMgr::Get_Instance()->Get_ScrollY(), 0.f);
	m_matWorld = matScale * matTrans;
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&m_matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMapTriangle::Release()
{
}
