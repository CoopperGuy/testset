#include "stdafx.h"
#include "Go.h"


CGo::CGo()
{
}


CGo::~CGo()
{
	Release();
}

void CGo::Initialize()
{
	m_tInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_ID::SINGLE_TEX, L"../Texture/UI/GameOver.png", L"GameOver");
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwDelayTime = 50;

}

void CGo::Update_UI()
{
}

void CGo::Render_UI(HDC _DC)
{
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	matWorld = matScale  * matTrans;

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"GameOver");
	float fCenterX = 0;
	float fCenterY = 0;
	if (alpha >= 200)
		alpha = 200;
	if (m_tFrame.dwTime + m_tFrame.dwDelayTime < GetTickCount())
		alpha++;
	if (pTexInfo != nullptr) {
		fCenterX = pTexInfo->tImageInfo.Width >> 1;
		fCenterY = pTexInfo->tImageInfo.Height >> 1;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	}

}

void CGo::Release()
{
}

CUI * CGo::Create(D3DXVECTOR3 _pos, D3DXVECTOR3 _size)
{
	CGo* pInstance = new CGo;
	pInstance->Set_Pos(_pos);
	pInstance->Set_Size(_size);
	pInstance->Initialize();
	return pInstance;
}
