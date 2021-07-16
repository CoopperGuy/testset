#include "stdafx.h"
#include "UIMgr.h"
#include "UI.h"
#include "Inven.h"
#include "Life.h"
#include "Score.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
{
}


CUIMgr::~CUIMgr()
{
}

void CUIMgr::Update()
{
	for (auto& iter : m_listUI) {
		(iter)->Update_UI();
	}
}

void CUIMgr::Render(HDC _DC)
{
	for (auto& iter : m_listUI) {
		(iter)->Render_UI();
	}
}

void CUIMgr::Release()
{
}
