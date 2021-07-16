#pragma once

#ifndef __CLIFE_H__
#define __CLIFE_H__

#include "UI.h"
class CLife :
	public CUI
{
public:
	CLife();
	virtual ~CLife();
public:
	virtual void Initialize() override;
	virtual void Update_UI() override;
	virtual void Render_UI() override;
	virtual void Release() override;
public:
	static CUI* Create(D3DXVECTOR3 _pos, D3DXVECTOR3 _size);
private:
	int life;
};


#endif // !__CLIFE_H__
