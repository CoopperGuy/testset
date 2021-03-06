#pragma once
#ifndef __MAPOBJ_H__
#define __MAPOBJ_H__

#include "Obj.h"
class CMapObj : public CObj
{
public:
	explicit CMapObj();
	virtual ~CMapObj();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC _DC) PURE;
	virtual void Release() PURE;

public:
	void Set_Animation(int, int, bool _bReset = false);

public:
	const int& Get_DrawID() { return m_iDrawID; }
	const EDITID::ID& Get_ID() { return m_eID; }
public:
	void Set_DrawID(int _iID = 0) { m_iDrawID = _iID; }
	void Set_ID(EDITID::ID _eID) { m_eID = _eID; }
protected:
	EDITID::ID	m_eID;
	int			m_iDrawID;
};

#endif // !__MAPOBJ_H__
