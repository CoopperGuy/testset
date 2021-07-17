#include "stdafx.h"
#include "MainGame.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

HRESULT CMainGame::Initialize()
{
	CGraphic_Device::Get_Instance()->Ready_Graphic_Device();

	m_hDC = GetDC(g_hWnd);
	CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::STAGE);

	return S_OK;
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();

}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();

}

void CMainGame::Render()
{
	CGraphic_Device::Get_Instance()->Render_Begin();

	//Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	CSceneMgr::Get_Instance()->Render(m_hDC);

	CGraphic_Device::Get_Instance()->Render_End();
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
	CObjMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
}

