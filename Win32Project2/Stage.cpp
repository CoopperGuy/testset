#include "stdafx.h"
#include "Stage.h"
#include "MapObjMgr.h"

CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	CBckMgr::Get_Instance()->Initialize();
	CLineMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Initialize();
	CMapObjMgr::Get_Instance()->Ready_MapObj();
	CDataMgr::Get_Instance()->Load_Data();

	CObjMgr::Get_Instance()->Add_Object(CPlayer::Create(100.f,100.f), OBJID::PLAYER);
	CUIMgr::Get_Instance()->Add_Object(CLife::Create({ 100.f,100.f,0.f }, { 50.f,50.f,0.f }), UIID::STAGEUI);
	//CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CJump_Monster>::Create(800, 350), OBJID::MONSTER);
}

void CStage::Update()
{
	CBckMgr::Get_Instance()->Update();
	CLineMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();
}

void CStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	
}

void CStage::Render(HDC _DC)
{
	CBckMgr::Get_Instance()->Render(_DC);
	CTileMgr::Get_Instance()->Render(_DC);
	CObjMgr::Get_Instance()->Render(_DC);
	CUIMgr::Get_Instance()->Render(_DC);
}

void CStage::Release()
{
}
