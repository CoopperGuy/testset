#include "stdafx.h"
#include "BckMgr.h"
#include "BckGround.h"

IMPLEMENT_SINGLETON(CBckMgr)
CBckMgr::CBckMgr()
{
	m_vBck.shrink_to_fit();
}


CBckMgr::~CBckMgr()
{
	Release();
}

HRESULT CBckMgr::Initialize()
{
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::SINGLE_TEX, L"../Texture/Stage/Terrain/Back/Back.png", L"BackGround");

	m_vBck.emplace_back(CAbstractFactory<CBckGround>::Create(WINCX >> 1, WINCY >> 1));
	
	m_vBck.emplace_back(CAbstractFactory<CBckGround>::Create((WINCX >> 1) + m_vBck[0]->Get_Size().x, WINCY>>1));
	
	m_vBck.emplace_back(CAbstractFactory<CBckGround>::Create( WINCX + m_vBck[1]->Get_Pos().x, WINCY >> 1));

	return S_OK;
}

void CBckMgr::Update()
{
	for (auto Bck : m_vBck)
		Bck->Update();

	if(m_vBck.front()->Get_Dead())
	{
		m_vBck.erase(m_vBck.begin());
		m_vBck.emplace_back(CAbstractFactory<CBckGround>::Create(m_vBck.back()->Get_Pos().x + m_vBck.back()->Get_Size().x, WINCY >> 1));
	}

	return ;
}

void CBckMgr::Render(HDC _DC)
{
	for (auto Bck : m_vBck)
		Bck->Render(_DC);
}

void CBckMgr::Release()
{
	m_vBck.clear();
}
