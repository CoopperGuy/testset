#pragma once
#include "Bullet.h"
class CLinear_Bullet :
	public CBullet
{
public:
	CLinear_Bullet();
	~CLinear_Bullet();

	// CBullet��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

	static CObj* Create(float _x, float _y);

private:

};

