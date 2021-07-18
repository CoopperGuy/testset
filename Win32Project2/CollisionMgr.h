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
	static void Collision_Player_Item(list<CObj*> _Dst, list<CObj*> _Src);
	static void Collision_Player_Monster(list<CObj*> _Dst, list<CObj*> _Src);
	static void Collision_Player_Obstacle(list<CObj*> _Dst, list<CObj*> _Src);
	static void COllision_Bulllet_Monster(list<CObj*> _Dst, list<CObj*> _src);
	static void COllision_Player_BossThing(list<CObj*> _Dst, list<CObj*> _src);
public:
	static D3DXVECTOR3 HeightVec(CObj *pObj);
	static D3DXVECTOR3 WidthVec(CObj *pObj);
	static D3DXVECTOR3 Get_Unit(D3DXVECTOR3 unit);
public:
	static bool Collision_OBB(CObj* _Dst, CObj* _Src);
};


#endif // !__CCOLLISIONMGR_H__
