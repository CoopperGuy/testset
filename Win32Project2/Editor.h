#pragma once
#ifndef __EDITOR_H__
#define __EDITOR_H__

#include "Scene.h"
class CEditor :
	public CScene
{
	enum EDITKEY { TILE, PLAYER, MONSTER, MAPOBJ, LINE, END };
public:
	explicit CEditor();
	virtual ~CEditor();

public:
	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	EDITID::ID			m_eID;
	EDITKEY				m_eKey;
};

#endif // !__EDITOR_H__
