#pragma once
#include "Bullet.h"
class CBoss_Throw :
	public CBullet
{
public:
	CBoss_Throw();
	~CBoss_Throw();

	// CBullet을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

	static CObj* Create(float _x, float _y);

private:
	D3DXVECTOR3 m_vTargetDir;
	float m_fAngle;
	bool m_bTargetLock;
};

