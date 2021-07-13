#pragma once

#ifndef __COBJ_H__
#define __COBJ_H__

class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	virtual HRESULT Initialize() = 0;
	virtual int Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;
protected:
	D3DXVECTOR3 m_vQ[4];
	D3DXVECTOR3 m_vP[4];
	INFO m_tInfo;
	OBJINFO m_tObjInfo;
	DWORD m_dwTime;
	DWORD m_dwDelayTime;
	bool	m_bDead;

};

#endif // !__COBJ_H__
