#pragma once
#include "Obj.h"
class Linear_Bullet :
	public CObj
{
public:
	Linear_Bullet();
	~Linear_Bullet();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

	void Set_Position(const D3DXVECTOR3& _vPos);

private:

};

