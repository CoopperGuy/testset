#include "stdafx.h"
#include "MainGame.h"
#include "Graphic_Device.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "SceneMgr.h"
#include "UIMgr.h"
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
	m_hDC = GetDC(g_hWnd);
	if (FAILED(CGraphic_Device::Get_Instance()->Ready_Graphic_Device()))
		return S_FALSE;
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
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	/*CGraphic_Device::Get_Instance()->Render_Begin();
	CGraphic_Device::Get_Instance()->Render_End();*/
	CSceneMgr::Get_Instance()->Render(m_hDC);

}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
	CObjMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CUIMgr::Destroy_Instance();
	CGraphic_Device::Destroy_Instance();

}

