#include "stdafx.h"
#include "Player.h"

#include "MonObjMgr.h"
#include "Linear_Bullet.h"
#include "Guided_Bullet.h"
#include "Melee.h"

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
	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	//위치정보
	m_tObjInfo.hp = 3;
	m_tObjInfo.atk = 1;
	m_tObjInfo.spd = 5.f;
	m_tObjInfo.agl = 0.f;
	Inven.emplace_back(BULLET(0, 0, BULLET_MELEE , 200));
	//플레이어 정보
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Character/Run/Run0%d.png", L"Player", L"Run", 4)))
		return S_FALSE;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Character/Jump/Jump0%d.png", L"Player", L"Jump", 3)))
		return S_FALSE;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Character/Jump/DJump0%d.png", L"Player", L"DJump", 6)))
		return S_FALSE;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Character/Attack/Attack0%d.png", L"Player", L"Attack", 12)))
		return S_FALSE;

	m_dwTime = GetTickCount();
	m_dwDelayTime = 100;
	PatternTime = GetTickCount();
	return S_OK;
}

int CPlayer::Update()
{
	if (m_bDead) 
		return OBJ_DEAD;
	
	D3DXMATRIX matScale, matRotZ, matTrans;
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
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		if (m_tG.m_bJump) {
			m_tG.m_bDJump = true;
		}
		if (!m_tG.m_bJump) {
			curState = CPlayer::P_JUMP;
			m_tG.m_fJumpY = m_tInfo.vPos.y;
			m_tG.m_bJump = true;
		}
		if (m_tG.m_bDJump && m_tG.m_bJump) {
			m_tG.m_fJumpY = m_tInfo.vPos.y;
			m_tG.m_fJumpTime = 0.f;
			curState = CPlayer::P_DJUMP;
		}
	}
	
	if (CKeyMgr::Get_Instance()->Key_Down('A'))
	{
		curState = CPlayer::P_ATTACK;

		if (PatternTime + Inven[cur_Weapon].PatternDelay < GetTickCount()) {
			Shut_Bullet();
			PatternTime = GetTickCount();
		}
	}
	for (int i = 0; i < MAX_INVEN; i++) {
		if (CKeyMgr::Get_Instance()->Key_Down(i + '0')) {
			if (Inven.size() > (i - 1))
				cur_Weapon = i;
		}
	}

	////총알 테스트용
	//if (CKeyMgr::Get_Instance()->Key_Down('Z'))
	//{
	//	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CLinear_Bullet>::Create(m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5f, m_tInfo.vPos.y), OBJID::PLAYERBULLET);
	//}
	//if (CKeyMgr::Get_Instance()->Key_Down('X'))
	//{
	//	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CGuided_Bullet>::Create(m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5f, m_tInfo.vPos.y), OBJID::PLAYERBULLET);
	//}

	Drop();
	Jumping();
	Offset();
	Check_State();
	Update_State();
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	if (ImmortalTime + ImmortalDelay < GetTickCount())
		isImmortal = false;
	if (m_tObjInfo.hp <= 0)
		m_bDead = OBJ_DEAD;
}

void CPlayer::Render(HDC _DC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	D3DXMATRIX matScale, matTrans;
	D3DXMatrixScaling(&matScale, 1.0f, 1.0f, 0.f);
	D3DXMatrixTranslation(&matTrans,  (m_tInfo.vPos.x + ScrollX) , m_tInfo.vPos.y ,0.f );
	matWorld = matScale * matTrans;
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"Player", m_tFrame.m_pFrameKey, m_tFrame.CurID);
	float fCenterX = 0;
	float fCenterY = 0;
	if (pTexInfo != nullptr) {
		fCenterX = pTexInfo->tImageInfo.Width >> 1;
		fCenterY = pTexInfo->tImageInfo.Height;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		int alpha = 0;
		switch (isImmortal)
		{
		case true:
			alpha = 255 - (128 * isFlicker);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(alpha, alpha, alpha, alpha));
			break;
		case false:
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		}
	}
	


}

void CPlayer::Release()
{
}

void CPlayer::Check_State()
{
	if (curState != preState) {
		switch (curState)
		{
		case CPlayer::P_RUN:
			m_tFrame.CurID = 0;
			m_tFrame.EndId = 4;
			m_tFrame.dwDelayTime = 100;
			m_tFrame.m_pFrameKey = L"Run";
			break;
		case CPlayer::P_JUMP:
			m_tFrame.CurID = 0;
			m_tFrame.EndId = 3;
			m_tFrame.dwDelayTime = 100;
			m_tFrame.m_pFrameKey = L"Jump";
			break;
		case CPlayer::P_DJUMP:
			m_tFrame.CurID = 0;
			m_tFrame.EndId = 6;
			m_tFrame.dwDelayTime = 100;
			m_tFrame.m_pFrameKey = L"DJump";
			break;
		case CPlayer::P_ATTACK:
			m_tFrame.CurID = 0;
			m_tFrame.EndId = 11;
			m_tFrame.dwDelayTime = 50;
			m_tFrame.m_pFrameKey = L"Attack";
			break;
		}
		preState = curState;
	}
}

void CPlayer::Update_State()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelayTime < GetTickCount()) {
		m_tFrame.CurID++;
		isFlicker = (isFlicker + 1) % 2;
		if (m_tFrame.CurID == m_tFrame.EndId) {
			switch (curState)
			{
			case CPlayer::P_RUN:
				m_tFrame.CurID = 0;
				break;
			case CPlayer::P_JUMP:
				m_tFrame.CurID = 1;
				break;
			case CPlayer::P_DJUMP:
				m_tFrame.CurID = m_tFrame.EndId - 1;
				break;
			case CPlayer::P_ATTACK:
				curState = CPlayer::P_RUN;
				m_tFrame.CurID=0;
				break;
			}
		}
		m_tFrame.dwTime = GetTickCount();
	}
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
			m_tG.m_bDJump = false;
			curState = CPlayer::P_RUN;
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
		CObjMgr::Get_Instance()->Add_Object(CMelee::Create({m_tInfo.vPos.x + m_tInfo.vSize.x * 0.75f , m_tInfo.vPos.y , m_tInfo.vPos.z}), OBJID::PLAYERBULLET);
		break;
	case CPlayer::BULLET_NORMAL:
		if (Inven[cur_Weapon].cur_magazine > 0) {
			Inven[cur_Weapon].cur_magazine--;
			CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CLinear_Bullet>::Create(m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5f, m_tInfo.vPos.y), OBJID::PLAYERBULLET);
		}
		break;
	case CPlayer::BULLET_GUIDE:
		if (Inven[cur_Weapon].cur_magazine > 0) {
			Inven[cur_Weapon].cur_magazine--;
			CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CGuided_Bullet>::Create(m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5f, m_tInfo.vPos.y), OBJID::PLAYERBULLET);
		}
		break;
	}
}


CPlayer::BULLET CPlayer::getItemType(CItem::ITEMTAG _tag)
{

	switch (_tag)
	{
	case CItem::ITEM_GUN:
		return BULLET(30, 200, BULLET_NORMAL , 300);
		break;
	case CItem::ITEM_GUIDE:
		return BULLET(10, 100, BULLET_GUIDE , 400);
		break;

	}
	return BULLET(0, 0, BULLETTYPE::BULLET_END , 0);
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
	else {
		for (auto& iter : Inven) {
			if (iter.BulletID == _tag) {
				iter = iter + getItemType(_tag);//연산자 오버로딩
				isIn = true;
				break;
			}
		}
	}

}

CObj * CPlayer::Create(float _x,float _y)
{
	CPlayer* pInstance = new CPlayer;
	pInstance->Set_Pos(_x, _y);
	if (FAILED(pInstance->Initialize()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
