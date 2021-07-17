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
	CObjMgr::Get_Instance()->Add_Object(CPlayer::Create(100.f,100.f), OBJID::PLAYER);
	CBckMgr::Get_Instance()->Initialize();
	CDataMgr::Get_Instance()->Load_Data();
	CUIMgr::Get_Instance()->Add_Object(CLife::Create({ 100.f,100.f,0.f }, { 50.f,50.f,0.f }), UIID::STAGEUI);

	////출력 테스트
	//CObjMgr::Get_Instance()->Add_Object(CNormal_Monster::Create(1000.f, 450.f), OBJID::MONSTER);
	//CObjMgr::Get_Instance()->Add_Object(CJump_Monster::Create(1000.f, 300.f), OBJID::MONSTER);
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
