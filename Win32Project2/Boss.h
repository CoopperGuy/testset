#pragma once
#include "Monster.h"
class CBoss :
	public CMonster
{
public:
	enum BOSS_STATE { IDLE, ATTACK_1, ATTACK_2, DEAD, END };

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
	BOSS_STATE	m_eState;

	float		m_fIdleY;
	float		m_fIdleAngle;
	float		m_actionDelay;
	DWORD		m_timeCount;
	float		m_fScale;

	int			m_patternCount;
	bool		m_settled;

	const TCHAR* m_pTextureKey;
};

