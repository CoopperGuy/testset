#pragma once
#ifndef __BCKGROUND_H__
#define __BCKGROUND_H__

#include "MapObj.h"
class CBckGround :
	public CMapObj
{
public:
	explicit CBckGround();
	virtual ~CBckGround();

public:
	// CMapObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

#endif // !__BCKGROUND_H__
