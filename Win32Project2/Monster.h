#pragma once

#ifndef __CMONSTER_H__
#define __CMONSTER_H__


#include "Obj.h"
class CMonster :
	public CObj
{
public:
	enum STATE {RUN, HIT, END};

	CMonster();
	virtual ~CMonster();

public:
	virtual HRESULT Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC _DC) PURE;
	virtual void Release() PURE;

public:
	const EDITID::ID& Get_ID() { return m_eID; }

protected:
	EDITID::ID		m_eID;
	STATE			m_eState;
};


#endif // !__CMONSTER_H__