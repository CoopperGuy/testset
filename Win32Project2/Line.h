#pragma once

#ifndef __LINE_H__
#define __LINE_H__


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
	const float& Get_LineY(float _x) const;

private:
	LINEINFO	m_tInfo;
};


#endif // !__LINE_H__

