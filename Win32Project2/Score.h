#pragma once

#ifndef __CSCORE_H__
#define __CSCORE_H__

#include "UI.h"
class CScore :
	public CUI
{
public:
	CScore();
	virtual ~CScore();
public:
	virtual void Initialize() override;
	virtual void Update_UI() override;
	virtual void Render_UI(HDC _DC) override;
	virtual void Release() override;
public:
	static CUI* Create(D3DXVECTOR3 _pos, D3DXVECTOR3 _size);
private:
	int score = 0;
};


#endif // !__CSCORE_H__
