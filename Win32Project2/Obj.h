#pragma once

#ifndef __COBJ_H__
#define __COBJ_H__
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
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
	const bool& Get_Dead() { return m_bDead; }
	const INFO& Get_Info() { return m_tInfo; }
	const OBJINFO& Get_ObjInfo() { return m_tObjInfo; }
	const DWORD& Get_Time() { return m_dwTime; }
	const DWORD& Get_Delaytime() { return m_dwDelayTime; }
public:
	virtual void Check_State();
	virtual void Update_State();
public:
	void Set_Dead() { m_bDead = OBJ_DEAD; }
	void Set_Score(int _Point) { m_tObjInfo.score += _Point; }
	void Set_Life(int life) { m_tObjInfo.hp += life; }
public:
	int Get_Score() { return m_tObjInfo.score; }
	int Get_Life() { return m_tObjInfo.hp; }
public:
	void Set_Pos(float _fx, float _fy) { m_tInfo.vPos = { _fx, _fy, 0.f }; }
	void Set_Dir(float _fx, float _fy) {m_tInfo.vDir = { _fx, _fy, 0.f }; }
	void Set_Size(float _fx, float _fy) { m_tInfo.vSize = { _fx, _fy ,0.f }; }

	void Set_vPos(D3DXVECTOR3 _pos) { m_tInfo.vPos = _pos; }
	void Set_Info(INFO _tInfo) { m_tInfo = _tInfo; }
	void Set_ObjInfo(OBJINFO _tobj) { m_tObjInfo = _tobj; }

	void Set_Time(DWORD _dwtime) { m_dwTime = _dwtime; }
	void Set_DelayTime(DWORD _dwDelayTime) { m_dwDelayTime = _dwDelayTime; }
protected:
	D3DXVECTOR3 m_vQ[4];
	D3DXVECTOR3 m_vP[4];
	D3DXMATRIX matWorld;
	INFO m_tInfo;
	OBJINFO m_tObjInfo;
	FRAME m_tFrame;
	DWORD m_dwTime;
	DWORD m_dwDelayTime;
	bool	m_bDead;
	D3DXMATRIX m_matWorld;
};

#endif // !__COBJ_H__
