
// MyEditor.h : MyEditor ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMyEditorApp:
// �� Ŭ������ ������ ���ؼ��� MyEditor.cpp�� �����Ͻʽÿ�.
//

class CMyEditorApp : public CWinApp
{
public:
	CMyEditorApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyEditorApp theApp;
