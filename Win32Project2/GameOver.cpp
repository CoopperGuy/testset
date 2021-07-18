#include "stdafx.h"
#include "GameOver.h"
#include "SceneMgr.h"
#include "Go.h"
CGameOver::CGameOver()
{
}


CGameOver::~CGameOver()
{
	Release();
}

void CGameOver::Initialize()
{
	CUIMgr::Get_Instance()->Add_Object(CGo::Create({ WINCX>>1,WINCY>>1,0.f }, { 100.f,100.f,0.f }), UIID::OVERUI);
}

void CGameOver::Update()
{
	CUIMgr::Get_Instance()->Update();
	if (CKeyMgr::Get_Instance()->Key_Down('R')) //
		CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::STAGE);
}

void CGameOver::Late_Update()
{
}

void CGameOver::Render(HDC _DC)
{
	CBckMgr::Get_Instance()->Render(_DC);
	CTileMgr::Get_Instance()->Render(_DC);
	CObjMgr::Get_Instance()->Render(_DC);
	CLineMgr::Get_Instance()->Render(_DC);
	CUIMgr::Get_Instance()->Render(_DC);
}

void CGameOver::Release()
{
	CUIMgr::Get_Instance()->Delete_UI(UIID::OVERUI);
	CBckMgr::Destroy_Instance();
	CTileMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
}
