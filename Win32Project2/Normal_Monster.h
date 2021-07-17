#pragma once
#include "Monster.h"
class CNormal_Monster :
	public CMonster
{
public:
	CNormal_Monster();
	~CNormal_Monster();

	// CMonster��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	int m_iDrawID;
	int m_iMaxDrawID;
};

