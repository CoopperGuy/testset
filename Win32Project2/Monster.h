#pragma once

#ifndef __CMONSTER_H__
#define __CMONSTER_H__


#include "Obj.h"
class CMonster :
	public CObj
{
public:
	enum STATE { RUN, HIT, END };

	CMonster();
	virtual ~CMonster();

public:
	virtual HRESULT Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC _DC) PURE;
	virtual void Release() PURE;

	void Set_Hit() { m_eState = HIT; }
	bool IsOutside();
	void Hit_Jump();

protected:
	STATE m_eState;
	GRAVITY m_tG;

	float m_fAngle;
};


#endif // !__CMONSTER_H__