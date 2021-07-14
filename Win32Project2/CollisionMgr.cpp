#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

D3DXVECTOR3 CCollisionMgr::HeightVec(CObj * pObj)
{
	D3DXVECTOR3 Look = { 1.f,0.f,0.f };
	D3DXVECTOR3 dir{};
	D3DXVECTOR3 size = pObj->Get_Size();
	float rad = D3DXVec3Dot((&dir,&pObj->Get_Dir()), &Look) / (D3DXVec3Length(&dir) * D3DXVec3Length(&Look));
	return D3DXVECTOR3((size.y * cosf(D3DXToDegree(rad) - 90)) * 0.5f, (size.y * sinf(D3DXToDegree(rad) - 90))*0.5f, 0.f);
}

D3DXVECTOR3 CCollisionMgr::WidthVec(CObj * pObj)
{
	D3DXVECTOR3 Look = { 1.f,0.f,0.f };
	D3DXVECTOR3 dir{};
	D3DXVECTOR3 size = pObj->Get_Size();
	float rad = D3DXVec3Dot((&dir, &pObj->Get_Dir()), &Look) / (D3DXVec3Length(&dir) * D3DXVec3Length(&Look));
	return D3DXVECTOR3((size.x * cosf(D3DXToDegree(rad))) * 0.5f, (size.x * sinf(D3DXToDegree(rad)))*0.5f, 0.f);
}

bool CCollisionMgr::Collision_OBB(CObj * _Dst, CObj * _Src)
{
	D3DXVECTOR3 dist = (_Dst->Get_Pos() - _Src->Get_Pos()) * 1.25f;
	D3DXVECTOR3 vec[4] = { HeightVec(_Dst) ,HeightVec(_Src)  , WidthVec(_Dst), WidthVec(_Src) };
	D3DXVECTOR3 unit;

	for (int i = 0; i < 4; i++) {
		float sum = 0;
		D3DXVec3Normalize(&unit,&vec[i]);
		for (int j = 0; j < 4; j++) {
			sum += abs(D3DXVec3Dot(&vec[j] , &unit));
		}
		if (abs(D3DXVec3Dot(&dist, &unit)) >= sum) {
			return false;
		}
	}
	return true;
}
