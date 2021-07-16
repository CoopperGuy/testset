#pragma once
#ifndef __GRAPHIC_DEVICE_H__
#define __GRAPHIC_DEVICE_H__

class CGraphic_Device final
{
	DECLARE_SINGLETON(CGraphic_Device)
private:
	CGraphic_Device();
	~CGraphic_Device();
public:
	LPDIRECT3DDEVICE9 Get_Device() { return m_pDevice; }
	LPD3DXSPRITE Get_Sprite() { return m_pSprite; }
	LPD3DXFONT Get_Font() { return m_pFont; }
public:
	HRESULT Ready_Graphic_Device();
	void Release_Graphic_Device();
	void Render_Begin();
	void Render_End(HWND hWnd = nullptr);
private:
	LPDIRECT3D9				m_pSDK;		// ��ġ�� ������ �����ϱ� ���� �İ�ü. 
	LPDIRECT3DDEVICE9		m_pDevice;	// ��ġ�� �����ϴ� �İ�ü. 
	LPD3DXSPRITE			m_pSprite;
	LPD3DXFONT				m_pFont;

};

#endif // !__GRAPHIC_DEVICE_H__
