#pragma once
#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

class CBckGround;
class CBckMgr
{
	DECLARE_SINGLETON(CBckMgr)
private:
	CBckMgr();
	~CBckMgr();

public:
	HRESULT Initialize();
	void Update();
	void Render(HDC _DC);
	void Release();

private:
	vector<CObj*>		m_vBck;

};

#endif // !__BACKGROUND_H__
