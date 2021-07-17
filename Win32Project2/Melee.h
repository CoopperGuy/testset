#pragma once

#ifndef __CMELEE_H__
#define __CMELEE_H__

#include "Bullet.h"
class CMelee :
	public CBullet
{
public:
	CMelee();
	virtual ~CMelee();
public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
public:
	virtual void Update_State();
public:
	static CObj* Create(D3DXVECTOR3 _pos);
};


#endif // !__CMELEE_H__
