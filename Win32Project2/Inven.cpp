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
}

void CInven::Update_UI()
{
	if (!CObjMgr::Get_Instance()->Get_PlayerEmpty())
		Inven = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Inven();

}

void CInven::Render_UI()
{
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
