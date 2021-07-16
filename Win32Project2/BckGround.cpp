#include "stdafx.h"
#include "BckGround.h"
#include "ScrollMgr.h"

CBckGround::CBckGround()
{
}


CBckGround::~CBckGround()
{
	Release();
}

HRESULT CBckGround::Initialize()
{
	m_tInfo.vDir = { -1.0f, 0.f, 0.f };
	m_tInfo.vPos = { WINCX >> 1,WINCY >> 1,0.f };
	m_tInfo.vSize = { 800 , 600 , 0.f };

	return S_OK;
}

int CBckGround::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_tInfo.vPos.x + CScrollMgr::Get_Instance()->Get_ScrollX()< m_tInfo.vSize.x * -0.5f)
		m_bDead = true;

	return OBJ_NOEVENT;
}

void CBckGround::Late_Update()
{
}

void CBckGround::Render(HDC _DC)
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"BackGround");
	if (nullptr == pTexInfo)
		return;
	float fCenterX = (float)(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = (float)(pTexInfo->tImageInfo.Height >> 1);
	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tInfo.vPos.y, 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


}

void CBckGround::Release()
{
}
