#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "Player.h"
#include "Item.h"
#include "Monster.h"
CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Player_Item(list<CObj*> _Dst, list<CObj*> _Src)
{
	for (auto& diter : _Dst) {
		for (auto& siter : _Src) {
			if (Collision_OBB(diter, siter)) {
				diter->Set_Score(siter->Get_Score());
				static_cast<CPlayer*>(diter)->Set_Bullet(static_cast<CItem*>(siter)->Get_Item());
				siter->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::COllision_Bulllet_Monster(list<CObj*> _Dst, list<CObj*> _src)
{
	for (auto& diter :_Dst)
	{
		for (auto& siter : _src)
		{
			if (Collision_OBB(diter, siter))
			{
				diter->Set_Dead();
				static_cast<CMonster*>(siter)->Set_Hit();
			}
		}
	}
}




//#####################################################################################//
//�浹 ���� �Լ�
D3DXVECTOR3 CCollisionMgr::HeightVec(CObj * pObj)
{
	D3DXVECTOR3 Look = { 1.f,0.f,0.f };
	D3DXVECTOR3 dir = pObj->Get_Dir();
	D3DXVECTOR3 size = pObj->Get_Size();
	float rad = D3DXVec3Dot(&dir, &Look) / (D3DXVec3Length(&dir) * D3DXVec3Length(&Look));
	rad = acosf(rad);
	return D3DXVECTOR3((size.y  * 0.5f * cosf(rad - D3DXToRadian(90.f))), (size.y  * 0.5f * sinf(rad - D3DXToRadian(90.f))), 0.f);
}

D3DXVECTOR3 CCollisionMgr::WidthVec(CObj * pObj)
{
	D3DXVECTOR3 Look = { 1.f,0.f,0.f };
	D3DXVECTOR3 dir = pObj->Get_Dir();
	D3DXVECTOR3 size = pObj->Get_Size();
	float rad = D3DXVec3Dot(&dir, &Look) / (D3DXVec3Length(&dir) * D3DXVec3Length(&Look));
	rad = acosf(rad);
	return D3DXVECTOR3((size.x  * 0.5f * cosf(rad)), (size.x  * 0.5f * sinf(rad)), 0.f);
}

D3DXVECTOR3 CCollisionMgr::Get_Unit(D3DXVECTOR3 unit)
{
	D3DXVECTOR3 temp;
	float size = sqrt(D3DXVec3Dot(&unit, &unit));
	temp = { unit.x / size ,unit.y / size,0.f };
	return temp;
}
//�浹 ���� �Լ�
//#####################################################################################//



/*#######################################################################################*/
//OBB�浹����
bool CCollisionMgr::Collision_OBB(CObj * _Dst, CObj * _Src)
{
	D3DXVECTOR3 dist = (_Src->Get_Pos() - _Dst->Get_Pos());
	D3DXVECTOR3 vec[4] = { HeightVec(_Dst) ,HeightVec(_Src)  , WidthVec(_Dst), WidthVec(_Src) };

	D3DXVECTOR3 unit;
	//d

	for (int i = 0; i < 4; i++) {
		float sum = 0;
		unit = Get_Unit(vec[i]);
		for (int j = 0; j < 4; j++) {
			sum += abs(D3DXVec3Dot(&vec[j] , &unit));
		}
		float temp = abs(D3DXVec3Dot(&dist, &unit));
		if (temp >= sum) {
			return false;
		}
	}
	return true;
}
//OBB�浹����
/*#######################################################################################*/