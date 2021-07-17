#pragma once

#ifndef __CGUNITEM_H__
#define __CGUNITEM_H__

#include "Item.h"
class CGunItem :
	public CItem
{
public:
	CGunItem();
	virtual ~CGunItem();
public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
public:
	CObj* Create(D3DXVECTOR3 _pos);

};


#endif // !__CGUNITEM_H__
