#pragma once
#ifndef __MAPTRIANGLE_H__
#define __MAPTRIANGLE_H__

#include "MapObj.h"
class CMapTriangle :
	public CMapObj
{
public:
	CMapTriangle();
	~CMapTriangle();
public:
	// CMapObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

#endif // !__MAPTRIANGLE_H__
