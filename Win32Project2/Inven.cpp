#include "stdafx.h"
#include "Inven.h"


CInven::CInven()
{
}


CInven::~CInven()
{
	Release();
}

void CInven::Initialize()
{
	m_tInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_ID::SINGLE_TEX, L"../Texture/Inven/Inven.png", L"Inven");
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_ID::SINGLE_TEX, L"../Texture/Inven/Melee.png", L"MeleeInven");
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_ID::SINGLE_TEX, L"../Texture/Inven/Linear.png", L"LinearInven");
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_ID::SINGLE_TEX, L"../Texture/Inven/Guide.png", L"GuideInven");


}

void CInven::Update_UI()
{
	Inven = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Inven();
}

void CInven::Render_UI(HDC _DC)
{
	for (int i = 0; i < 3; i++) {
		D3DXMATRIX matScale, matTrans, matWorld;
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + (i * 64), m_tInfo.vPos.y, m_tInfo.vPos.z);
		matWorld = matScale  * matTrans;


		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"Inven");
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
	for (int i = 0; i < Inven.size(); i++) {
		D3DXMATRIX matScale, matTrans, matWorld;
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + (i * 64), m_tInfo.vPos.y, m_tInfo.vPos.z);
		matWorld = matScale  * matTrans;

		const TEXINFO* pTexInfo = nullptr;

		switch (Inven[i].BulletID)
		{
		case CPlayer::BULLET_MELEE:
			pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"MeleeInven");
			break;
		case CPlayer::BULLET_NORMAL:
			pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"LinearInven");
			break;
		case CPlayer::BULLET_GUIDE:
			pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"GuideInven");
			break;
		}
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		WCHAR buf[64] = L"";
		swprintf_s(buf, L"%d", Inven[i].cur_magazine);
		D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + (i * 64) + 10, m_tInfo.vPos.y + 20, m_tInfo.vPos.z);
		matWorld = matScale  * matTrans;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matTrans);
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(),
			buf, lstrlen(buf), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
	}
}

void CInven::Release()
{
}
CUI * CInven::Create(D3DXVECTOR3 _pos, D3DXVECTOR3 _size)
{
	CInven* pInstance = new CInven;
	pInstance->Set_Pos(_pos);
	pInstance->Set_Size(_size);
	pInstance->Initialize();
	return pInstance;
}
