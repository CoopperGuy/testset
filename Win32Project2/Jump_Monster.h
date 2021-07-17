#pragma once
#include "Monster.h"
class CJump_Monster :
	public CMonster
{
public:
	CJump_Monster();
	~CJump_Monster();

	// CMonster��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

	static CObj* Create(float _x, float _y);

	void Run_Jump();

private:
	GRAVITY m_tRunG;

};

