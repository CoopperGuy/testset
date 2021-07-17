#pragma once

#ifndef __CINVEN_H__
#define __CINVEN_H__


#include "UI.h"
class CInven :
	public CUI
{
public:
	CInven();
	virtual ~CInven();
public:
	virtual void Initialize() override;
	virtual void Update_UI() override;
	virtual void Render_UI(HDC _DC) override;
	virtual void Release() override;
public:
	static CUI* Create(D3DXVECTOR3 _pos, D3DXVECTOR3 _size);
private:
	vector<CPlayer::BULLET> Inven;
};


#endif // !__CINVEN_H__
