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
	//1. ���� �����ϰ�
	CLineMgr::Get_Instance()->Save_Line();

	//2. Ÿ�� �����ϰ�
	CTileMgr::Get_Instance()->Save_Tile();

	//3. �� ������Ʈ �����ϰ�
	CObjMgr::Get_Instance()->Save_MapObj();

	//4. ���� ��ġ�ϰ�
	CObjMgr::Get_Instance()->Save_Monster();

	//5. �÷��̾� ��ġ�ϰ�
	CObjMgr::Get_Instance()->Save_Player();

}

void CDataMgr::Load_Data()
{
	//1. ���� �ε��ϰ�
	CLineMgr::Get_Instance()->Load_Line();

	//2. Ÿ�� �ε��ϰ�
	CTileMgr::Get_Instance()->Load_Tile();

	//3. �� ������Ʈ �ε��ϰ�
	CObjMgr::Get_Instance()->Load_MapObj();

	//4. ���� �ε��ϰ�
	CObjMgr::Get_Instance()->Load_Monster();
	
	//5. �÷��̾� �ε��ϰ�
	CObjMgr::Get_Instance()->Load_Player();

}