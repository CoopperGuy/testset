
// MyEditorView.h : CMyEditorView Ŭ������ �������̽�
//

#pragma once


class CMyEditorView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMyEditorView();
	DECLARE_DYNCREATE(CMyEditorView)

// Ư���Դϴ�.
public:
	CMyEditorDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMyEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MyEditorView.cpp�� ����� ����
inline CMyEditorDoc* CMyEditorView::GetDocument() const
   { return reinterpret_cast<CMyEditorDoc*>(m_pDocument); }
#endif

