#include "stdafx.h"
#include "Editor.h"
#include "Tile.h"

#include "MapObjMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "TileMgr.h"
#include "BckMgr.h"
#include "DataMgr.h"

CEditor::CEditor()
	:m_eID(EDITID::END)
	,m_eKey(EDITKEY::END)
{
}


CEditor::~CEditor()
{
	Release();
}

void CEditor::Initialize()
{
	CGraphic_Device::Get_Instance()->Ready_Graphic_Device();
	CMapObjMgr::Get_Instance()->Ready_MapObj();

	CBckMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Initialize();
	CLineMgr::Get_Instance()->Initialize();
}

void CEditor::Update()
{
	//CLineMgr::Get_Instance()->Update();
	CBckMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(15.f);
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-15.f);

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		switch (m_eID)
		{
		case EDITID::TILE0:
			CTileMgr::Get_Instance()->Picking_Tile(0);
			break;
		case EDITID::TILE1:
			CTileMgr::Get_Instance()->Picking_Tile(1);
			break;
		case EDITID::TILE2:
			CTileMgr::Get_Instance()->Picking_Tile(2);
			break;
		case EDITID::LINE:
			CLineMgr::Get_Instance()->Picking_Line();
			break;

		//ObjMgr
		case EDITID::ID::PLAYER:
		case EDITID::ID::NORMAL_MONSTER:
		case EDITID::ID::JUMP_MONSTER:
		case EDITID::ID::MONSTERDEL:
		case EDITID::ID::MAPSWORD:
		case EDITID::ID::MAPMOVETRI:
		case EDITID::ID::MAPTRI:
		case EDITID::ID::MAPTOTEM:
		case EDITID::ID::MAPDEL:
			CObjMgr::Get_Instance()->Picking_Obj(m_eID);
			break;

		case EDITID::END:
			break;
		default:
			break;
		}
	}

	// 카테고리 선택
	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		m_eKey = EDITKEY::TILE;
		m_eID = EDITID::END;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('W'))
	{
		m_eKey = EDITKEY::PLAYER;
		m_eID = EDITID::PLAYER;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('E'))
	{
		m_eID = EDITID::END;
		m_eKey = EDITKEY::MONSTER;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('R'))
	{
		m_eID = EDITID::END;
		m_eKey = EDITKEY::MAPOBJ;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('T'))
	{
		m_eKey = EDITKEY::LINE;
		m_eID = EDITID::LINE;
	}


	// TilePicking
	if (m_eKey == EDITKEY::TILE)
	{
		if (CKeyMgr::Get_Instance()->Key_Down('1'))
			m_eID = EDITID::TILE0;
		if (CKeyMgr::Get_Instance()->Key_Down('2'))
			m_eID = EDITID::TILE1;
		if (CKeyMgr::Get_Instance()->Key_Down('3'))
			m_eID = EDITID::TILE2;
	}
	// Monster Picking
	else if (m_eKey == EDITKEY::MONSTER)
	{
		if (CKeyMgr::Get_Instance()->Key_Down('1'))
			m_eID = EDITID::NORMAL_MONSTER;
		if (CKeyMgr::Get_Instance()->Key_Down('2'))
			m_eID = EDITID::JUMP_MONSTER;
		if (CKeyMgr::Get_Instance()->Key_Down('5'))
			m_eID = EDITID::MONSTERDEL;
	}
	// MapObj Picking
	else if (m_eKey == EDITKEY::MAPOBJ)
	{
		if (CKeyMgr::Get_Instance()->Key_Down('1'))
			m_eID = EDITID::MAPSWORD;
		if (CKeyMgr::Get_Instance()->Key_Down('2'))
			m_eID = EDITID::MAPMOVETRI;
		if (CKeyMgr::Get_Instance()->Key_Down('3'))
			m_eID = EDITID::MAPTRI;
		if (CKeyMgr::Get_Instance()->Key_Down('4'))
			m_eID = EDITID::MAPTOTEM;
		if (CKeyMgr::Get_Instance()->Key_Down('5'))
			m_eID = EDITID::MAPDEL;
	}


	if (CKeyMgr::Get_Instance()->Key_Down('S'))
		CDataMgr::Get_Instance()->Save_Data();
	if (CKeyMgr::Get_Instance()->Key_Down('L'))
		CDataMgr::Get_Instance()->Load_Data();

	//CObjMgr::Get_Instance()->Update();

}

void CEditor::Late_Update()
{
}

void CEditor::Render(HDC _DC)
{
	CBckMgr::Get_Instance()->Render(_DC);
	CTileMgr::Get_Instance()->Render(_DC);
	CObjMgr::Get_Instance()->Render(_DC);
	CLineMgr::Get_Instance()->Render(_DC);
}

void CEditor::Release()
{
	CBckMgr::Destroy_Instance();
	CTexture_Manager::Destroy_Instance();
	CGraphic_Device::Destroy_Instance();
}
