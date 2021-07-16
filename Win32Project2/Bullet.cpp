#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
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
