#include "stdafx.h"
#include "Player.h"

#include "MonObjMgr.h"
#include "Linear_Bullet.h"
#include "Guided_Bullet.h"


CPlayer::CPlayer() 
	:m_tG( 45.f,0.f, 0.f, false,false)
{


}


CPlayer::~CPlayer()
{
	Release();
}

HRESULT CPlayer::Initialize()
{

	m_tInfo.vPos = { 100.f, 100.f, 0.f };
	m_tInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(100.f, 100.f, 0.f);
	m_tObjInfo.hp = 1;
	m_tObjInfo.atk = 1;
	m_tObjInfo.spd = 5.f;
	m_tObjInfo.agl = 0.f;

	m_dwTime = GetTickCount();
	m_dwDelayTime = 100;
	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	return S_OK;
}

int CPlayer::Update()
{
	if (m_bDead) 
		return OBJ_DEAD;
	
	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(00.f));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		m_tInfo.vPos.x -= m_tObjInfo.spd;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_tInfo.vPos.x += m_tObjInfo.spd;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP)) {
		m_tInfo.vPos.y -= m_tObjInfo.spd;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN)) {
		m_tInfo.vPos.y += m_tObjInfo.spd;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!m_tG.m_bJump)
			m_tG.m_fJumpY = m_tInfo.vPos.y;

		m_tG.m_bJump = true;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('X'))
	{
		CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CLinear_Bullet>::Create(m_tInfo.vPos.x, m_tInfo.vPos.y), OBJID::PLAYERBULLET);
	}
	if (CKeyMgr::Get_Instance()->Key_Down('C'))
	{
		CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CGuided_Bullet>::Create(m_tInfo.vPos.x, m_tInfo.vPos.y), OBJID::PLAYERBULLET);
	}
	Drop();
	Jumping();
	Offset();
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	
	if (m_tObjInfo.hp <= 0)
		m_bDead = OBJ_DEAD;
}

void CPlayer::Render(HDC _DC)
{
	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	MoveToEx(_DC, m_vQ[0].x + ScrollX, m_vQ[0].y, nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(_DC, m_vQ[i].x + ScrollX, m_vQ[i].y);
	LineTo(_DC, m_vQ[0].x + ScrollX, m_vQ[0].y);

}

void CPlayer::Release()
{
}

void CPlayer::Jumping()
{
	float fY = 0.f;
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.vPos.x, m_tInfo.vPos.y, &fY, &m_tG.m_bg);
	float spdY = 0.f;

	if (m_tG.m_bJump || m_tG.m_bg)
	{
		//m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 0.5f * 9.8f * m_fJumpTime * m_fJumpTime;
		if (m_tG.m_bJump) {
			spdY = (m_tG.m_fJumpPower * m_tG.m_fJumpTime - 0.5f * 9.8f * m_tG.m_fJumpTime * m_tG.m_fJumpTime);

			m_tInfo.vPos.y = m_tG.m_fJumpY - spdY;
		}
		else if (m_tG.m_bg) {
			spdY = (4.9f * m_tG.m_fJumpTime);
			if (spdY > 15.f)
				spdY = 15.f;
			m_tInfo.vPos.y = m_tInfo.vPos.y + spdY;
		}

		m_tG.m_fJumpTime += 0.2f;

		if (bLineCol && m_tInfo.vPos.y > (fY - m_tInfo.vSize.y * 0.5f))
		{
			m_tInfo.vPos.y = (fY - m_tInfo.vSize.y * 0.5f);
			m_tG.m_bJump = false;
			m_tG.m_fJumpTime = 0.f;
			m_tG.m_bg = false;
		}
	}
	else if (bLineCol) {
		m_tInfo.vPos.y = fY - m_tInfo.vSize.y * 0.5f;
		return;
	}
	switch (bLineCol)
	{
	case false:
		spdY = (4.9f * m_tG.m_fJumpTime);
		if (spdY > 15.f)
			spdY = 15.f;
		m_tInfo.vPos.y = m_tInfo.vPos.y + spdY;
		m_tG.m_fJumpTime += 0.2f;
		break;
	}

}

void CPlayer::Shut_Bullet()
{
	BULLETTYPE _id = Inven[cur_Weapon].BulletID;
	switch (_id)
	{
	case CPlayer::BULLET_MELEE:
		break;
	case CPlayer::BULLET_NORMAL:
		if (Inven[cur_Weapon].cur_magazine > 0) {
			Inven[cur_Weapon].cur_magazine--;
		}
		break;
	case CPlayer::BULLET_GUIDE:
		if (Inven[cur_Weapon].cur_magazine > 0) {
			Inven[cur_Weapon].cur_magazine--;
		}
		break;
	}
}


CPlayer::BULLET CPlayer::getItemType(CItem::ITEMTAG _tag)
{
	switch (_tag)
	{
	case CItem::ITEM_POINT:
		break;
	case CItem::ITEM_END:
		break;
	}
	return BULLET(0, 0, BULLETTYPE::BULLET_END);
}

void CPlayer::Drop()
{
	if (m_tInfo.vPos.y > WINCY*2.f) {
		m_tInfo.vPos.y = 100.f;
		m_tInfo.vPos.x = 100.f;
	}
}

void CPlayer::Offset()
{
	int OffsetX = (WINCX >> 1) - 200;
	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (OffsetX < (m_tInfo.vPos.x + ScrollX))
		CScrollMgr::Get_Instance()->Set_ScrollX(OffsetX - (m_tInfo.vPos.x + ScrollX));
	if (OffsetX >(m_tInfo.vPos.x + ScrollX))
		CScrollMgr::Get_Instance()->Set_ScrollX(OffsetX - (m_tInfo.vPos.x + ScrollX));
}

void CPlayer::Set_Bullet(CItem::ITEMTAG _tag)
{
	bool isIn = false;
	if (_tag == CItem::ITEMTAG::ITEM_POINT)
		return;
	if (Inven.size() < MAX_INVEN) {
		for (auto& iter : Inven) {
			if (iter.BulletID == _tag) {
				iter = iter + getItemType(_tag);//연산자 오버로딩
				isIn = true;
				break;
			}
		}
		if (!isIn) {
			Inven.emplace_back(getItemType(_tag));
		}
	}

}

CObj * CPlayer::Create()
{
	CPlayer* pInstance = new CPlayer;
	if (FAILED(pInstance->Initialize()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
