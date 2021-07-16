#include "stdafx.h"
#include "Linear_Bullet.h"


Linear_Bullet::Linear_Bullet()
{
}

Linear_Bullet::~Linear_Bullet()
{
	Release();
}

HRESULT Linear_Bullet::Initialize()
{
	return E_NOTIMPL;
}

int Linear_Bullet::Update()
{
	return 0;
}

void Linear_Bullet::Late_Update()
{
}

void Linear_Bullet::Render(HDC _DC)
{
}

void Linear_Bullet::Release()
{
}

void Linear_Bullet::Set_Position(const D3DXVECTOR3 & _vPos)
{
	m_tInfo.vPos.x = _vPos.x;
	m_tInfo.vPos.y = _vPos.y;
}
