#include "stdafx.h"
#include "TestMon.h"


CTestMon::CTestMon()
{
}


CTestMon::~CTestMon()
{
	Release();
}

HRESULT CTestMon::Initialize()
{
	m_tInfo.vPos = { 300.f, 300.f, 0.f };
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

int CTestMon::Update()
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
	return OBJ_NOEVENT;

}

void CTestMon::Late_Update()
{
}

void CTestMon::Render(HDC _DC)
{
	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	MoveToEx(_DC, m_vQ[0].x + ScrollX, m_vQ[0].y, nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(_DC, m_vQ[i].x + ScrollX, m_vQ[i].y);
	LineTo(_DC, m_vQ[0].x + ScrollX, m_vQ[0].y);
}

void CTestMon::Release()
{
}

CObj * CTestMon::Create()
{
	CTestMon* pInstance = new CTestMon;
	if (FAILED(pInstance->Initialize()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
