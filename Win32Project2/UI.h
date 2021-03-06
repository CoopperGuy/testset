#pragma once

#ifndef __CUI_H__
#define __CUI_H__
#include "ObjMgr.h"
#include "Player.h"
#include "Graphic_Device.h"

class CUI
{
public:
	CUI();
	virtual ~CUI();
public:
	virtual void Initialize()PURE;
	virtual void Update_UI()PURE;
	virtual void Render_UI(HDC _DC)PURE;
	virtual void Release()PURE;
public:
	virtual void Update_State();
public:
	void Set_Pos(D3DXVECTOR3 _pos) { m_tInfo.vPos = _pos; }
	void Set_Size(D3DXVECTOR3 _size) { m_tInfo.vSize = _size; }
protected:
	INFO m_tInfo;
	D3DXMATRIX matScale;
	D3DXMATRIX matTrans; 
	D3DXMATRIX matWorld;
	FRAME m_tFrame;



};

#endif // !__CUI_H__
