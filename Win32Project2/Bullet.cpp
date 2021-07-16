#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

bool CBullet::IsFarFromPlayer()
{
	D3DXVECTOR3 _player = CObjMgr::Get_Instance()->Get_Player()->Get_Pos();
	if (m_tInfo.vPos.x < _player.x - WINCX || m_tInfo.vPos.x > _player.x + WINCX
		|| m_tInfo.vPos.y < _player.y - WINCY || m_tInfo.vPos.y > _player.y + WINCY)
	{
		return true;
	}

	return false;
}
