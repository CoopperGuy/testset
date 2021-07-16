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

	void Run_Jump();

private:
	GRAVITY m_tRunG;

};

