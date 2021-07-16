#pragma once

#ifndef __LINE_H__
#define __LINE_H__
#include "ScrollMgr.h"

class CLine
{
public:
	CLine();
	CLine(LINEPOS& _tLeftPos, LINEPOS& _tRightPos);
	~CLine();

public:
	HRESULT Initialize();
	void Render(HDC _DC);
	void Release();

public:
	const LINEINFO& Get_Info() const { return m_tInfo; }
	float Get_LineY(float _x);

private:
	LINEINFO	m_tInfo;
};


#endif // !__LINE_H__

