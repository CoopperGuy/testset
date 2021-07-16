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
	const int& Get_DrawID() { return m_iDrawID; }

public:
	void Set_DrawID(int _iID = 0) { m_iDrawID = _iID; }

protected:
	int m_iDrawID;
};

#endif // !__MAPOBJ_H__
