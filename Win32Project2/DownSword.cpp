#include "stdafx.h"
#include "DownSword.h"


CDownSword::CDownSword()
{
}


CDownSword::~CDownSword()
{
}

HRESULT CDownSword::Initialize()
{
	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_tInfo.vPos = { 0.f, 0.f, 0.f };
	m_tInfo.vSize = { 55.f, 190.f, 0.f };

	m_eID = EDITID::MAPSWORD;

	m_dwTime = 0;
	m_dwDelayTime = 50;

	return S_OK;
}

int CDownSword::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	// 화면에 나타나면 슝 나옵니다.
	if (m_tInfo.vPos.x + CScrollMgr::Get_Instance()->Get_ScrollX() <= WINCX)
	{
		if (m_dwTime == 0)
		{
			m_dwTime = GetTickCount();
		}

		if (m_dwTime + m_dwDelayTime <= GetTickCount())
		{
			Set_Animation(0, 3);
			m_dwTime = GetTickCount();
		}
	}

	// 죽습니다
	if (m_tInfo.vPos.x + CScrollMgr::Get_Instance()->Get_ScrollX() + m_tInfo.vSize.x < 0)
		m_bDead = true;

	return OBJ_NOEVENT;
}

void CDownSword::Late_Update()
{
}

void CDownSword::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"MapObject", L"DownSword", m_iDrawID);
	if (nullptr == pTexInfo)
		return;
	float fCenterX = (float)(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = (float)(pTexInfo->tImageInfo.Height >> 1);
	D3DXMATRIX matScale, matTrans;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tInfo.vPos.y + CScrollMgr::Get_Instance()->Get_ScrollY(), 0.f);
	m_matWorld = matScale * matTrans;
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&m_matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
 
}

void CDownSword::Release()
{
}
