#pragma once
#ifndef __TILE_H__
#define __TILE_H__

#include "MapObj.h"
class CTile :
	public CMapObj
{
public:
	explicit CTile();
	virtual ~CTile();
public:
	// CMapObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

};

#endif // !__TILE_H__
