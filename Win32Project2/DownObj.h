#pragma once
#ifndef __DOWNOBJ_H__
#define __DOWNOBJ_H__

#include "MapObj.h"
class CDownObj :
	public CMapObj
{
public:
	explicit CDownObj();
	virtual ~CDownObj();
public:
	// CMapObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

#endif // !__DOWNOBJ_H__
