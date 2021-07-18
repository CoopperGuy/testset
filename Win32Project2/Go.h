#pragma once

#ifndef __CGO_H__
#define __CGO_H__

#include "UI.h"
class CGo :
	public CUI
{
public:
	CGo();
	virtual ~CGo();
public:
	virtual void Initialize() override;
	virtual void Update_UI() override;
	virtual void Render_UI(HDC _DC) override;
	virtual void Release() override;
public:
	static CUI* Create(D3DXVECTOR3 _pos, D3DXVECTOR3 _size);
private:
	int alpha = 0;

};


#endif // !__CGO_H__
