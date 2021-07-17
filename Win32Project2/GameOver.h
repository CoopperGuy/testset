#pragma once

#ifndef __CGAMEOVER_H__
#define __CGAMEOVER_H__

#include "Scene.h"
class CGameOver :
	public CScene
{
public:
	CGameOver();
	virtual ~CGameOver();
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__CGAMEOVER_H__
