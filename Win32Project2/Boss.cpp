#include "stdafx.h"
#include "Boss.h"


CBoss::CBoss()
{
}


CBoss::~CBoss()
{
	Release();
}

HRESULT CBoss::Initialize()
{
	return E_NOTIMPL;
}

int CBoss::Update()
{
	return 0;
}

void CBoss::Late_Update()
{
}

void CBoss::Render(HDC _DC)
{
}

void CBoss::Release()
{
}

CObj * CBoss::Create(float _x, float _y)
{
	CBoss* pInstance = new CBoss;
	pInstance->Set_Pos(_x, _y);
	if (FAILED(pInstance->Initialize()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
