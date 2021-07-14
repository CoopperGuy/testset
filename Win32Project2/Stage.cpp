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
	CObjMgr::Get_Instance()->Add_Object(CTestMon::Create(), OBJID::MONSTER);
	CLineMgr::Get_Instance()->Initialize();
}

void CStage::Update()
{
	CObjMgr::Get_Instance()->Update();

}

void CStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	
}

void CStage::Render(HDC _DC)
{
	CObjMgr::Get_Instance()->Render(_DC);
	CLineMgr::Get_Instance()->Render(_DC);
}

void CStage::Release()
{
}
