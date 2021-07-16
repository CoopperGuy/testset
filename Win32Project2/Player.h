#pragma once

#ifndef __CPLAYER_H__
#define __CPLAYER_H__
//현재 만들어야 되는거
//점수,라이프,무기 스왑?
#include "Obj.h"
class CPlayer :
	public CObj
{
private:
	CPlayer();
public:
	virtual ~CPlayer();
public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
public:
	void Jumping();
	static CObj* Create();
public:
	void Set_Point(int _point) { m_tObjInfo.score += _point; }
public:
	int Get_Point() { return m_tObjInfo.score; }
private:
	GRAVITY m_tG;
	CObj* CurrentWeapon;

	//test
};


#endif // !__CPLAYER_H__
