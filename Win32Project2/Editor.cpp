#include "stdafx.h"
#include "Editor.h"
#include "Tile.h"

#include "ObjMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "TileMgr.h"
#include "BckMgr.h"
#include "DataMgr.h"

CEditor::CEditor()
	:m_eID(EDITID::END)
{
}


CEditor::~CEditor()
{
	Release();
}

void CEditor::Initialize()
{
	CGraphic_Device::Get_Instance()->Ready_Graphic_Device();


	CBckMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Initialize();
	CLineMgr::Get_Instance()->Initialize();
}

void CEditor::Update()
{
	CBckMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);

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
		case EDITID::PLAYER:
			CObjMgr::Get_Instance()->Picking_Obj(m_eID);
			break;
		case EDITID::MONSTERDEL:
			CObjMgr::Get_Instance()->Picking_Obj(m_eID);
			break;
		case EDITID::TESTMON:
			CObjMgr::Get_Instance()->Picking_Obj(m_eID);
			break;

		case EDITID::END:
			break;
		default:
			break;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('0'))
		m_eID = EDITID::END;
	
	// TilePicking
	if (CKeyMgr::Get_Instance()->Key_Down('1'))
		m_eID = EDITID::TILE0;
	if (CKeyMgr::Get_Instance()->Key_Down('2'))
		m_eID = EDITID::TILE1;
	if (CKeyMgr::Get_Instance()->Key_Down('3'))
		m_eID = EDITID::TILE2;
	// LinePicking
	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
		m_eID = EDITID::LINE;
	// OBJPicking
	if (CKeyMgr::Get_Instance()->Key_Down('W'))
		m_eID = EDITID::PLAYER;
	if (CKeyMgr::Get_Instance()->Key_Down('E'))
		m_eID = EDITID::MONSTERDEL;
	if (CKeyMgr::Get_Instance()->Key_Down('R'))
		m_eID = EDITID::TESTMON;
//	if (CKeyMgr::Get_Instance()->Key_Down('T'))
		


	if (CKeyMgr::Get_Instance()->Key_Down('S'))
		CDataMgr::Get_Instance()->Save_Data();
	if (CKeyMgr::Get_Instance()->Key_Down('L'))
		CDataMgr::Get_Instance()->Load_Data();




}

void CEditor::Late_Update()
{
}

void CEditor::Render(HDC _DC)
{
	CBckMgr::Get_Instance()->Render(_DC);
	CTileMgr::Get_Instance()->Render(_DC);
	CLineMgr::Get_Instance()->Render(_DC);
	CObjMgr::Get_Instance()->Render(_DC);
}

void CEditor::Release()
{
	CBckMgr::Destroy_Instance();
	CTexture_Manager::Destroy_Instance();
	CGraphic_Device::Destroy_Instance();
}
