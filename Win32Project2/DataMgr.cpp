#include "stdafx.h"
#include "DataMgr.h"

#include "ObjMgr.h"
#include "TileMgr.h"
#include "LineMgr.h"
IMPLEMENT_SINGLETON(CDataMgr)
CDataMgr::CDataMgr()
{

}


CDataMgr::~CDataMgr()
{
	Release();
}

void CDataMgr::Initialize()
{

}

void CDataMgr::Render(HDC _DC)
{
}

void CDataMgr::Release()
{
}

void CDataMgr::Save_Data()
{
	//1. 라인 저장하고
	CLineMgr::Get_Instance()->Save_Line();

	//2. 타일 저장하고
	CTileMgr::Get_Instance()->Save_Tile();

	//3. 맵 오브젝트 저장하고
	CObjMgr::Get_Instance()->Save_MapObj();

	//4. 몬스터 배치하고
	CObjMgr::Get_Instance()->Save_Monster();

	//5. 플레이어 배치하고
	CObjMgr::Get_Instance()->Save_Player();

}

void CDataMgr::Load_Data()
{
	//1. 라인 로드하고
	CLineMgr::Get_Instance()->Load_Line();

	//2. 타일 로드하고
	CTileMgr::Get_Instance()->Load_Tile();

	//3. 맵 오브젝트 로드하고
	CObjMgr::Get_Instance()->Load_MapObj();

	//4. 몬스터 로드하고
	CObjMgr::Get_Instance()->Load_Monster();
	
	//5. 플레이어 로드하고
	CObjMgr::Get_Instance()->Load_Player();

}