#include "stdafx.h"
#include "Melee.h"


CMelee::CMelee()
{
}


CMelee::~CMelee()
{
	Release();
}

HRESULT CMelee::Initialize()
{
	m_tInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(50.f, 100.f, 0.f);

	m_tObjInfo.hp = 1;
	m_tObjInfo.atk = 1;
	m_tObjInfo.spd = 0.f;
	m_tObjInfo.agl = 0.f;

	m_dwTime = GetTickCount();
	m_dwDelayTime = 40;


	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Bullet/Melee/Melee0%d.png", L"Bullet", L"Melee", 4)))
		return S_FALSE;
	m_tFrame.CurID = 0;
	m_tFrame.EndId = 4;
	m_tFrame.dwDelayTime = 10;
	m_tFrame.m_pFrameKey = L"Melee";
	return S_OK;

}

int CMelee::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}


	D3DXMATRIX matScale, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.f));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	matWorld = matScale * matRotZ * matTrans;



	return OBJ_NOEVENT;
}

void CMelee::Late_Update()
{
	if (m_dwTime + m_dwDelayTime < GetTickCount())
		m_bDead = OBJ_DEAD;
}

void CMelee::Render(HDC _DC)
{
	Update_State();
	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	D3DXMATRIX matScale, matTrans;
	D3DXMatrixScaling(&matScale, 1.0f, 1.0f, 0.f);
	D3DXMatrixTranslation(&matTrans, (m_tInfo.vPos.x + ScrollX), m_tInfo.vPos.y, 0.f);
	matWorld = matScale * matTrans;
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"Bullet", m_tFrame.m_pFrameKey, m_tFrame.CurID);
	float fCenterX = 0;
	float fCenterY = 0;
	if (pTexInfo != nullptr) {
		fCenterX = pTexInfo->tImageInfo.Width >> 1;
		fCenterY = pTexInfo->tImageInfo.Height;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
}

void CMelee::Release()
{
}

CObj * CMelee::Create(D3DXVECTOR3 _pos)
{
	CMelee* pInstance = new CMelee;
	pInstance->Set_vPos(_pos);
	if (FAILED(pInstance->Initialize()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
