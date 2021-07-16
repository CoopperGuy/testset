#pragma once

#ifndef __COBJ_H__
#define __COBJ_H__
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	virtual HRESULT Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC _DC) PURE;
	virtual void Release() PURE;
public:
	D3DXVECTOR3 Get_Pos()  { return m_tInfo.vPos; }
	D3DXVECTOR3 Get_Dir()  { return m_tInfo.vDir; }
	D3DXVECTOR3 Get_Size() { return m_tInfo.vSize; }
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
