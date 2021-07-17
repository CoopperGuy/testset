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
	for (int i = 0; i < UIID::END; i++) {
		for (auto& iter : m_listUI[i]) {
			iter->Update_UI();
		}
	}
}

void CUIMgr::Render(HDC _DC)
{
	for (int i = 0; i < UIID::END; i++) {
		for (auto& iter : m_listUI[i]) {
			iter->Render_UI(_DC);
		}
	}

}

void CUIMgr::Release()
{
}
