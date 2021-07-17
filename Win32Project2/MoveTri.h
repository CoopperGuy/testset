#pragma once
#ifndef __MOVETRI_H__
#define __MOVETRI_H__

#include "MapObj.h"
class CMoveTri :
	public CMapObj
{
public:
	CMoveTri();
	~CMoveTri();
public:
	// CMapObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

#endif // !__MOVETRI_H__
