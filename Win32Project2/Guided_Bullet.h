#pragma once
#include "Bullet.h"

class CObj;

class CGuided_Bullet :
	public CBullet
{
public:
	CGuided_Bullet();
	~CGuided_Bullet();

	// CBullet을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	float m_fAngle;
	CObj* m_pTarget;
};

