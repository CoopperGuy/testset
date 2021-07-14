#pragma once

#ifndef __CCOLLISIONMGR_H__
#define __CCOLLISIONMGR_H__

class CObj;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();
public:
	static D3DXVECTOR3 HeightVec(CObj *pObj);
	static D3DXVECTOR3 WidthVec(CObj *pObj);
	static D3DXVECTOR3 Get_Unit(D3DXVECTOR3 unit);
public:
	static bool Collision_OBB(CObj* _Dst, CObj* _Src);
};


#endif // !__CCOLLISIONMGR_H__
