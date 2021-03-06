#pragma once


#ifndef __CPITEM_H__
#define __CPITEM_H__

#include "Item.h"
class CPItem :
	public CItem
{
private:
	CPItem();
public:
	virtual ~CPItem();
public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
public:
	void Update_Frame();
public:
	static CObj* Create(D3DXVECTOR3 _pos);
	FRAME m_tFrame;
};


#endif // !__CPITEM_H__
