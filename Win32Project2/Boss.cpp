#include "stdafx.h"
#include "Boss.h"

#include "ObjMgr.h"
#include "Boss_Bullet.h"
#include "Boss_Throw.h"

CBoss::CBoss()
	: m_eBossState(IDLE)
	, m_settled(false)
	, m_pTextureKey(nullptr)
	, m_timeCount(0)
	, m_actionDelay(0.f)
	, m_fIdleAngle(0.f)
	, m_fIdleY(0.f)
{
}


CBoss::~CBoss()
{
	Release();
}

HRESULT CBoss::Initialize()
{
	//보스 텍스처 전부 추가
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::SINGLE_TEX, L"../Texture/Monster/Boss/Boss_Idle.png", L"Boss_Idle");
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::SINGLE_TEX, L"../Texture/Monster/Boss/Boss_Attack_1.png", L"Boss_Attack_1");
	
	m_eID = EDITID::BOSS;

	m_pTextureKey = L"Boss_Idle";
	//투사체, 총알은 클래스 따로 구현

	//m_tInfo.vPos = { 800.f, 400.f, 0.f };
	m_tInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(100.f, 85.f, 0.f);

	m_tObjInfo.hp = 10;
	m_tObjInfo.atk = 1;
	m_tObjInfo.spd = 20.f;
	m_tObjInfo.agl = 0.f;
	/*
	m_dwTime = GetTickCount();
	m_dwDelayTime = 100;
	*/
	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	m_fIdleY = m_tInfo.vPos.y;
	m_timeCount = GetTickCount();

	return S_OK;
}

int CBoss::Update()
{
	if (m_tInfo.vPos.x - CObjMgr::Get_Instance()->Get_Player()->Get_Pos().x > WINCX)
	{
		m_tObjInfo.hp = 10;
		return OBJ_NOEVENT;
	}

	m_tInfo.vPos.x = CObjMgr::Get_Instance()->Get_Player()->Get_Pos().x + 550;

	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	

	if (m_eState == HIT)
	{
		--m_tObjInfo.hp;
		m_eState = RUN;
		m_bIsHit = false;
	}

	//BOSS_STATE에 맞게 if-else
	if (m_eBossState == IDLE)
	{
		if (m_timeCount + 2000 > GetTickCount())
		{
			//2초 동안 위 아래로 움직임
			m_fIdleAngle += 5.f;
			m_tInfo.vPos.y = m_fIdleY - sinf(D3DXToRadian(m_fIdleAngle)) * m_tObjInfo.spd;
		}
		else
		{
			m_eBossState = ATTACK_1;
			m_settled = false;
			m_timeCount = GetTickCount();
			m_patternCount = 0;
		}
	}
	else if (m_eBossState == ATTACK_1)
	{
		m_pTextureKey = L"Boss_Attack_1";

		if (!m_settled)
		{
			//y=400 근처로 이동
			if (!(abs(m_tInfo.vPos.y - 450) < 10))
			{
				if (m_tInfo.vPos.y - 450 > 0)
					m_tInfo.vPos.y -= 1.f;
				else
					m_tInfo.vPos.y += 1.f;
			}
			else
			{
				m_settled = true;
			}
		}
		else
		{
			if ((m_timeCount + 1500) < GetTickCount())
			{
				//총알 발사
				CObjMgr::Get_Instance()->Add_Object(CBoss_Bullet::Create(m_tInfo.vPos.x, m_tInfo.vPos.y), OBJID::BOSSBULLET);

				++m_patternCount;

				if (m_patternCount == 5)
				{
					//이 패턴은 5번
					//5번 끝나면 ATTACK_2
					m_eBossState = ATTACK_2;
					m_patternCount = 0;
					m_settled = false;
				}

				m_timeCount = GetTickCount();
			}
		}
	}
	else if (m_eBossState == ATTACK_2)
	{
		m_pTextureKey = L"Boss_Idle";

		if (!m_settled)
		{
			//조금씩 위로 상승
			m_tInfo.vPos.y -= 3.f;
			//조금씩 Scale + 0.05f
			m_fScale += 0.005f;
			if (abs(m_tInfo.vPos.y - 200.f) < 20)
			{
				m_settled = true;
			}
		}
		else
		{
			if ((m_timeCount + 1500) < GetTickCount())
			{
				//Attack_2 발사
				CObjMgr::Get_Instance()->Add_Object(CBoss_Throw::Create(m_tInfo.vPos.x, m_tInfo.vPos.y), OBJID::BOSSTHROW);

				++m_patternCount;

				if (m_patternCount == 2)
				{
					//이 패턴은 2번
					//끝나면 IDLE
					m_eBossState = IDLE;
					m_patternCount = 0;
					m_settled = false;

					m_fScale = 0.f;
				}

				m_timeCount = GetTickCount();
			}
		}
	}
	//else if (m_eState == DEAD)
	//{
	//	//그 위치에서
	//}

	if (m_tObjInfo.hp <= 0)
	{
		if (!m_tG.m_bJump)
		{
			m_tG.m_fJumpY = m_tInfo.vPos.y;
			m_tG.m_bJump = true;

		}
		m_fAngle += 2.f;
		Hit_Jump();

	}

	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	D3DXMATRIX matScale, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, 1.f + m_fScale, 1.f + m_fScale, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + ScrollX, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &m_matWorld);
	}

	if (IsOutside())
	{
		m_bDead = OBJ_DEAD;
	}

	return OBJ_NOEVENT;
}

void CBoss::Late_Update()
{
}

void CBoss::Render(HDC _DC)
{
	if (m_tInfo.vPos.x - CObjMgr::Get_Instance()->Get_Player()->Get_Pos().x > WINCX)
		return;

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(m_pTextureKey);
	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&m_matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBoss::Release()
{
}

CObj * CBoss::Create(float _x, float _y)
{
	CBoss* pInstance = new CBoss;
	pInstance->Set_Pos(_x, _y);
	if (FAILED(pInstance->Initialize()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
