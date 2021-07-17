#include "stdafx.h"
#include "Life.h"


CLife::CLife()
{
}


CLife::~CLife()
{
	Release();
}

void CLife::Initialize()
{
	m_tInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/UI/Hp/Hp%d.png", L"UI", L"Hp", 4)))
		return ;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.CurID = 0;
	m_tFrame.EndId = 4;
	m_tFrame.dwDelayTime = 100;
	m_tFrame.m_pFrameKey = L"Hp";
}

void CLife::Update_UI()
{
	

	if (!CObjMgr::Get_Instance()->Get_PlayerEmpty())
		life = CObjMgr::Get_Instance()->Get_Player()->Get_Life();
}

void CLife::Render_UI(HDC _DC)
{
	Update_State();
	for (int i = 0; i < life; i++) {
		D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + (i * 50.f), m_tInfo.vPos.y, m_tInfo.vPos.z);
		matWorld = matScale  * matTrans;

		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"UI", m_tFrame.m_pFrameKey, m_tFrame.CurID);
		float fCenterX = 0;
		float fCenterY = 0;
		if (pTexInfo != nullptr) {
			fCenterX = pTexInfo->tImageInfo.Width >> 1;
			fCenterY = pTexInfo->tImageInfo.Height >> 1;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
	}
}

void CLife::Release()
{
}
CUI * CLife::Create(D3DXVECTOR3 _pos, D3DXVECTOR3 _size)
{
	CLife* pInstance = new CLife;
	pInstance->Set_Pos(_pos);
	pInstance->Set_Size(_size);
	pInstance->Initialize();
	return pInstance;
}
