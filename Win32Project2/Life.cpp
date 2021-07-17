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

}

void CLife::Update_UI()
{
	

	if (!CObjMgr::Get_Instance()->Get_PlayerEmpty())
		life = CObjMgr::Get_Instance()->Get_Player()->Get_Life();
}

void CLife::Render_UI(HDC _DC)
{
	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	matWorld = matScale  * matTrans;

	WCHAR buf[64] = L"";
	swprintf_s(buf, L"life : %d", life);
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matTrans);
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(),
		buf, lstrlen(buf), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
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
