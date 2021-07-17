#pragma once
#include "Monster.h"
class CBoss :
	public CMonster
{
public:
	enum BOSS_STATE { IDLE, ATTACK_1, ATTACK_2, END };

	CBoss();
	~CBoss();

	// CMonster을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

	static CObj* Create(float _x, float _y);

private:

};

