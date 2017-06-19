
// DBMSView.cpp : CDBMSView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "DBMS.h"
#endif

#include "DBMSDoc.h"
#include "DBMSView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDBMSView

IMPLEMENT_DYNCREATE(CDBMSView, CView)

BEGIN_MESSAGE_MAP(CDBMSView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CDBMSView ����/����

CDBMSView::CDBMSView()
{
	// TODO:  �ڴ˴���ӹ������

}

CDBMSView::~CDBMSView()
{
}

BOOL CDBMSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CDBMSView ����

void CDBMSView::OnDraw(CDC* /*pDC*/)
{
	CDBMSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CDBMSView ��ӡ

BOOL CDBMSView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CDBMSView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CDBMSView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CDBMSView ���

#ifdef _DEBUG
void CDBMSView::AssertValid() const
{
	CView::AssertValid();
}

void CDBMSView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDBMSDoc* CDBMSView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDBMSDoc)));
	return (CDBMSDoc*)m_pDocument;
}
#endif //_DEBUG


// CDBMSView ��Ϣ�������
