
// DBMSView.h : CDBMSView ��Ľӿ�
//

#pragma once


class CDBMSView : public CView
{
protected: // �������л�����
	CDBMSView();
	DECLARE_DYNCREATE(CDBMSView)

// ����
public:
	CDBMSDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CDBMSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DBMSView.cpp �еĵ��԰汾
inline CDBMSDoc* CDBMSView::GetDocument() const
   { return reinterpret_cast<CDBMSDoc*>(m_pDocument); }
#endif

