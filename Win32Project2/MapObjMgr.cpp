#include "stdafx.h"
#include "MapObjMgr.h"

#include "DownSword.h"
#include "MoveTri.h"
#include "MapTriangle.h"
#include "Totem.h"

IMPLEMENT_SINGLETON(CMapObjMgr)
CMapObjMgr::CMapObjMgr()
{
}


CMapObjMgr::~CMapObjMgr()
{
}

// 이미지를 불러올겁니다
HRESULT CMapObjMgr::Ready_MapObj()
{
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Terrain/MapObject/DownSword/DownSword0%d.png", L"MapObject", L"DownSword", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Terrain/MapObject/MoveTri/Triangle0%d.png", L"MapObject", L"MoveTri", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Terrain/MapObject/Totem/Totem0%d.png", L"MapObject", L"Totem", 5);
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Terrain/MapObject/Totem/Totemloop0%d.png", L"MapObject", L"Totemloop", 3);
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Terrain/MapObject/Triangle/Triangle0%d.png", L"MapObject", L"Triangle", 2);

	return S_OK;
}

CObj * CMapObjMgr::Create_MapObj(EDITID::ID _eID, float _fx, float _fy)
{
	CObj* pObj = nullptr;

	switch (_eID)
	{
	case EDITID::ID::MAPSWORD:
		pObj = CAbstractFactory<CDownSword>::Create(_fx, _fy);
		break;
	case EDITID::MAPMOVETRI:
		pObj = CAbstractFactory<CMoveTri>::Create(_fx, _fy);
		break;
	case EDITID::MAPTRI:
		pObj = CAbstractFactory<CMapTriangle>::Create(_fx, _fy);
		break;
	case EDITID::MAPTOTEM:
		pObj = CAbstractFactory<CTotem>::Create(_fx, _fy);
		break;
	default:
		break;
	}

	if (!pObj)
		return nullptr;

	return pObj;

}
