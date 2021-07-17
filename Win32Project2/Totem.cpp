#include "stdafx.h"
#include "Totem.h"


CTotem::CTotem()
	:m_bLoop(false)
{
}


CTotem::~CTotem()
{
}

HRESULT CTotem::Initialize()
{
	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_tInfo.vPos = { 0.f, 0.f, 0.f };
	m_tInfo.vSize = { 75.f, 120.f, 0.f };

	m_eID = EDITID::MAPTOTEM;

	m_dwTime = 0;
	m_dwDelayTime = 50;

	return S_OK;

}

int CTotem::Update()
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
			if (m_iDrawID == 4)
				m_bLoop = !m_bLoop;

			if (!m_bLoop)
				Set_Animation(0, 4);
			else
				Set_Animation(0, 2, true);

			m_dwTime = GetTickCount();
		}
	}

	// 죽습니다
	if (m_tInfo.vPos.x + CScrollMgr::Get_Instance()->Get_ScrollX() + m_tInfo.vSize.x < 0)
		m_bDead = true;

	return OBJ_NOEVENT;

}

void CTotem::Late_Update()
{
}

void CTotem::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	const TEXINFO* pTexInfo = nullptr;
	if (!m_bLoop)
		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"MapObject", L"Totem", m_iDrawID);
	else
		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"MapObject", L"Totemloop", m_iDrawID);

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

void CTotem::Release()
{
}
