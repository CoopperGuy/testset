#pragma once

#ifndef __CITEM_H__
#define __CITEM_H__


#include "Obj.h"
class CItem :
	public CObj
{
public:
	enum ITEMTAG{ITEM_POINT,ITEM_END};
public:
	CItem();
	virtual ~CItem();
public:
	virtual HRESULT Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC _DC) PURE;
	virtual void Release() PURE;
public:
	void Set_Item(ITEMTAG _tag) { ItemTag = _tag; }
public:
	ITEMTAG Get_Item() { return ItemTag; }
protected:
	ITEMTAG ItemTag;
};


#endif //__CITEM_H__