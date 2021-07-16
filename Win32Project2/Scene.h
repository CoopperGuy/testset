#pragma once

#ifndef __SCENE_H__
#define __SCENE_H__

#include "ObjMgr.h"
#include "LineMgr.h"
#include "UIMgr.h"
#include "Obj.h"
#include "Player.h"
#include "TestMon.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;
};


#endif // !__SCENE_H__
