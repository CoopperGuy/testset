#include "stdafx.h"
#include "Stage.h"


CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	CObjMgr::Get_Instance()->Add_Object(CPlayer::Create(), OBJID::PLAYER);
	CBckMgr::Get_Instance()->Initialize();
	CDataMgr::Get_Instance()->Load_Data();
	CUIMgr::Get_Instance()->Add_Object(CLife::Create({ 100.f,100.f,0.f }, { 50.f,50.f,0.f }), UIID::STAGEUI);

	//CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CJump_Monster>::Create(1000, 350), OBJID::MONSTER);
}

void CStage::Update()
{
	CBckMgr::Get_Instance()->Update();
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
	CLineMgr::Get_Instance()->Render(_DC);
	CUIMgr::Get_Instance()->Render(_DC);
}

void CStage::Release()
{
}
