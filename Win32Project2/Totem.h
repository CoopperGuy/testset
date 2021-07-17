#pragma once
#include "MapObj.h"
class CTotem :
	public CMapObj
{
public:
	CTotem();
	~CTotem();
public:
	// CMapObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
private:
	bool		m_bLoop;
};

