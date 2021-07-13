#pragma once


#ifndef __CSTAGE_H__
#define __CSTAGE_H__
#include "Scene.h"
class CStage :
	public CScene
{
public:
	CStage();
	virtual ~CStage();
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

};

#endif //__CSTAGE_H__