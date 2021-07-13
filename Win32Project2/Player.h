#pragma once

#ifndef __CPLAYER_H__
#define __CPLAYER_H__

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
private:
	float		m_fJumpPower;
	float		m_fJumpTime;
	float		m_fJumpY;
	bool		m_bJump;
	bool		m_bg;
};


#endif // !__CPLAYER_H__
