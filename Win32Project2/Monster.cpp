#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
	: m_eState(RUN)
	, m_tG(50.f, 0.f, 0.f, false, false)
	, m_fAngle(0.f)
{
}


CMonster::~CMonster()
{
}

bool CMonster::IsOutside()
{
	if ((m_tInfo.vPos.x<0 || m_tInfo.vPos.x >WINCX)
		&& (m_tInfo.vPos.y<0 || m_tInfo.vPos.y >WINCY))
	{
		return true;
	}

	return false;
}

void CMonster::Hit_Jump()
{
	m_tInfo.vPos.x += m_tObjInfo.spd;

	m_tInfo.vPos.y = m_tG.m_fJumpY 
		- (m_tG.m_fJumpPower * m_tG.m_fJumpTime 
			- 0.5f * 9.8f * m_tG.m_fJumpTime * m_tG.m_fJumpTime);
	m_tG.m_fJumpTime += 0.2f;
}
