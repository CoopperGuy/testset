
// MyEditorView.cpp : CMyEditorView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MyEditor.h"
#endif

#include "MyEditorDoc.h"
#include "MyEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyEditorView

IMPLEMENT_DYNCREATE(CMyEditorView, CView)

BEGIN_MESSAGE_MAP(CMyEditorView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMyEditorView ����/�Ҹ�

CMyEditorView::CMyEditorView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMyEditorView::~CMyEditorView()
{
}

BOOL CMyEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMyEditorView �׸���

void CMyEditorView::OnDraw(CDC* /*pDC*/)
{
	CMyEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CMyEditorView �μ�

BOOL CMyEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMyEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMyEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMyEditorView ����

#ifdef _DEBUG
void CMyEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CMyEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyEditorDoc* CMyEditorView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyEditorDoc)));
	return (CMyEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyEditorView �޽��� ó����
