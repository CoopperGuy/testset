#pragma once
#ifndef __DATAMGR_H__
#define __DATAMGR_H__

class CDataMgr
{
	DECLARE_SINGLETON(CDataMgr)
private:
	CDataMgr();
	~CDataMgr();
public:
	void Initialize();
	void Render(HDC _DC);
	void Release();

public:
	void Save_Data();
	void Load_Data();

private:

};

#endif // !__DATAMGR_H__
