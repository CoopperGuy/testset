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
}

void CLife::Update_UI()
{
	if (!CObjMgr::Get_Instance()->Get_PlayerEmpty())
		life = CObjMgr::Get_Instance()->Get_Player()->Get_Life();
}

void CLife::Render_UI()
{
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
