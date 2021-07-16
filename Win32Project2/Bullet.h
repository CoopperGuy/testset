#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
public:
	CBullet();
	~CBullet();

	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC _DC) PURE;
	virtual void Release() PURE;

	bool IsFarFromPlayer();

protected:

};

