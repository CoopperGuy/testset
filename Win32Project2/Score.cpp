#include "stdafx.h"
#include "Score.h"


CScore::CScore()
{
}


CScore::~CScore()
{
	Release();
}

void CScore::Initialize()
{
	m_tInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);

}

void CScore::Update_UI()
{

	if (!CObjMgr::Get_Instance()->Get_PlayerEmpty())
		score = CObjMgr::Get_Instance()->Get_Player()->Get_Score();

}

void CScore::Render_UI(HDC _DC)
{
	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	matWorld = matScale  * matTrans;
	WCHAR buf[64] = L"";
	swprintf_s(buf, L"Score : %d", score);
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matTrans);
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(),
		buf, lstrlen(buf), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
}

void CScore::Release()
{
}

CUI * CScore::Create(D3DXVECTOR3 _pos, D3DXVECTOR3 _size)
{
	CScore* pInstance = new CScore;
	pInstance->Set_Pos(_pos);
	pInstance->Set_Size(_size);
	pInstance->Initialize();
	return pInstance;
}
