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
}

void CScore::Update_UI()
{
	if (!CObjMgr::Get_Instance()->Get_PlayerEmpty())
		score = CObjMgr::Get_Instance()->Get_Player()->Get_Score();

}

void CScore::Render_UI()
{
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
