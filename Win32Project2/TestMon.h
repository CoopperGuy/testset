#pragma once

#ifndef __CTESTMON_H__
#define __CTESTMON_H__


#include "Monster.h"
class CTestMon :
	public CMonster
{
public:
	CTestMon();
	virtual ~CTestMon();
public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
public:
	static CObj* Create();

};

#endif // !__CTESTMON_H__
