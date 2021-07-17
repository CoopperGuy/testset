#pragma once
#ifndef __DOWNSWORD_H__
#define __DOWNSWORD_H__

#include "MapObj.h"
class CDownSword :
	public CMapObj
{
public:
	CDownSword();
	~CDownSword();
public:
	// CMapObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

#endif // !__DOWNSWORD_H__
