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
		if (m_listUI[i].empty())
			continue;
		for (auto& iter : m_listUI[i]) {
			iter->Update_UI();
		}
	}
}

void CUIMgr::Render(HDC _DC)
{
	for (int i = 0; i < UIID::END; i++) {
		if (m_listUI[i].empty())
			continue;
		for (auto& iter : m_listUI[i]) {
			iter->Render_UI(_DC);
		}
	}

}

void CUIMgr::Release()
{
	for (int i = 0; i < UIID::END; ++i)
	{
		for_each(m_listUI[i].begin(), m_listUI[i].end(), Safe_Delete<CUI*>);
		m_listUI[i].clear();
	}
}

void CUIMgr::Delete_UI(UIID::ID _id)
{
	for_each(m_listUI[_id].begin(), m_listUI[_id].end(), Safe_Delete<CUI*>);
	m_listUI[_id].clear();
}
