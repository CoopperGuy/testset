#pragma once

#ifndef __CGUIDEITEM_H__
#define __CGUIDEITEM_H__

#include "Item.h"
class CGuideItem :
	public CItem
{
public:
	CGuideItem();
	virtual ~CGuideItem();
public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
public:
	static CObj* Create(D3DXVECTOR3 _pos);

};


#endif // !__CGUIDEITEM_H__
