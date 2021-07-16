#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

HRESULT CBullet::Initialize()
{
	return E_NOTIMPL;
}

int CBullet::Update()
{
	return 0;
}

void CBullet::Late_Update()
{
}

void CBullet::Render(HDC _DC)
{
}

void CBullet::Release()
{
}

void CBullet::Set_Position(const D3DXVECTOR3 & _vPos)
{
	m_tInfo.vPos.x = _vPos.x;
	m_tInfo.vPos.y = _vPos.y;
}

bool CBullet::IsOutside()
{
	if (m_tInfo.vPos.x < 0 || m_tInfo.vPos.x > WINCX
		|| m_tInfo.vPos.y < 0 || m_tInfo.vPos.y > WINCY)
	{
		return true;
	}

	return false;
}
