#include "stdafx.h"
#include "Stage.h"

#include "LineMgr.h"
#include "TileMgr.h"
#include "BckMgr.h"
#include "DataMgr.h"

#include "Normal_Monster.h"
#include "Jump_Monster.h"

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

	//CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CJump_Monster>::Create(800, 350), OBJID::MONSTER);
}

void CStage::Update()
{
	CBckMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
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
}

void CStage::Release()
{
}
