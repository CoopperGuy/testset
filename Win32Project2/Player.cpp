#include "stdafx.h"
#include "Player.h"
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
	if (CKeyMgr::Get_Instance()->Key_Down('Z'))
	{
		CObj* pObject = new CLinear_Bullet;
		CObjMgr::Get_Instance()->Add_Object(pObject, OBJID::BULLET);
		pObject->Initialize();
		static_cast<CLinear_Bullet*>(pObject)->Set_Position(this->Get_Pos());
	}
	if (CKeyMgr::Get_Instance()->Key_Down('X'))
	{
		CObj* pObject = new CGuided_Bullet;
		CObjMgr::Get_Instance()->Add_Object(pObject, OBJID::BULLET);
		pObject->Initialize();
		static_cast<CGuided_Bullet*>(pObject)->Set_Position(this->Get_Pos());
	}

	//Jumping();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	
	if (m_tObjInfo.hp <= 0)
		m_bDead = OBJ_DEAD;
}

void CPlayer::Render(HDC _DC)
{
	MoveToEx(_DC, m_vQ[0].x, m_vQ[0].y, nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(_DC, m_vQ[i].x, m_vQ[i].y);
	LineTo(_DC, m_vQ[0].x, m_vQ[0].y);

}

void CPlayer::Release()
{
}

void CPlayer::Jumping()
{
	float fY = 0.f;
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.vPos.x, m_tInfo.vPos.y, &fY, &m_tG.m_bg);
	switch (bLineCol)
	{
	case false:
		m_tInfo.vPos.y = m_tInfo.vPos.y + (0.1f * 9.8f * m_tG.m_fJumpTime * m_tG.m_fJumpTime);
		m_tG.m_fJumpTime += 0.2f;
		break;
	}
	if (m_tG.m_bJump || m_tG.m_bg)
	{
		//m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 0.5f * 9.8f * m_fJumpTime * m_fJumpTime;
		if (m_tG.m_bJump)
			m_tInfo.vPos.y = m_tG.m_fJumpY - (m_tG.m_fJumpPower * m_tG.m_fJumpTime - 0.5f * 9.8f * m_tG.m_fJumpTime * m_tG.m_fJumpTime);
		else if (m_tG.m_bg)
			m_tInfo.vPos.y = m_tInfo.vPos.y + (0.1f * 9.8f * m_tG.m_fJumpTime * m_tG.m_fJumpTime);

		m_tG.m_fJumpTime += 0.2f;

		if (bLineCol && m_tInfo.vPos.y > fY)
		{
			m_tInfo.vPos.y = fY;
			m_tG.m_bJump = false;
			m_tG.m_fJumpTime = 0.f;
			m_tG.m_bg = false;
		}
	}
	else if (bLineCol)
		m_tInfo.vPos.y = fY;
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
