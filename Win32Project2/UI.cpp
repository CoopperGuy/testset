#include "stdafx.h"
#include "UI.h"


CUI::CUI()
{
}


CUI::~CUI()
{
}

void CUI::Update_State()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelayTime < GetTickCount()) {
		m_tFrame.CurID++;
		if (m_tFrame.CurID == m_tFrame.EndId) {
			m_tFrame.CurID = 0;
		}
		m_tFrame.dwTime = GetTickCount();
	}
}
