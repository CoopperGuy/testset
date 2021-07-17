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

}

void CInven::Update_UI()
{
	Inven = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Inven();
}

void CInven::Render_UI(HDC _DC)
{
	for (int i = 0; i < Inven.size(); i++) {
		D3DXMATRIX matScale, matTrans, matWorld;
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + (i * 300), m_tInfo.vPos.y, m_tInfo.vPos.z);
		matWorld = matScale  * matTrans;

		WCHAR buf[64] = L"";
		swprintf_s(buf, L"%d / %d ", Inven[i].cur_magazine,Inven[i].max_magazine);
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
