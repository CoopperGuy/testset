#pragma once

#ifndef __COBJ_H__
#define __COBJ_H__
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "Graphic_Device.h"

//매니저 추가하면 이쪽에다가 
//대부분의 자식객체가 쓰는 것도 여기다가.
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
public:
	void Set_Dead() { m_bDead = OBJ_DEAD; }
	void Set_Score(int _Point) { m_tObjInfo.score += _Point; }
public:
	int Get_Score() { return m_tObjInfo.score; }
	int Get_Life() { return m_tObjInfo.hp; }
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
