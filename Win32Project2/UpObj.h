#pragma once
#ifndef __UPOBJ_H__
#define __UPOBJ_H__

#include "MapObj.h"
class CUpObj :
	public CMapObj
{
public:
	explicit CUpObj();
	virtual ~CUpObj();
public:
	// CMapObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

#endif // !__UPOBJ_H__
