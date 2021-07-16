#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
public:
	CBullet();
	~CBullet();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC _DC) PURE;
	virtual void Release() PURE;

	void Set_Position(const D3DXVECTOR3& _vPos);

protected:

};

