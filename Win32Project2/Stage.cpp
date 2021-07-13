#include "stdafx.h"
#include "Stage.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "Obj.h"
#include "Player.h"
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
