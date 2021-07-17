#include "stdafx.h"
#include "MyMenu.h"


CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	//uiÃß°¡
}

void CMyMenu::Update()
{
	CUIMgr::Get_Instance()->Update();

}

void CMyMenu::Late_Update()
{
}

void CMyMenu::Render(HDC _DC)
{
	CUIMgr::Get_Instance()->Render(_DC);
}

void CMyMenu::Release()
{
	CUIMgr::Get_Instance()->Delete_UI(UIID::MENUUI);
}
