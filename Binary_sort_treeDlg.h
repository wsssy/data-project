
// Binary_sort_treeDlg.h : ͷ�ļ�
//

#pragma once
#include<string>

// CBinary_sort_treeDlg �Ի���
/*extern string str;
extern string m_PreOrder;
*/

class CBinary_sort_treeDlg : public CDialogEx
{
// ����
public:
	CBinary_sort_treeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BINARY_SORT_TREE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_inputnum;
	int m_deletenum;
	CString m_pre;
	CString m_inn;
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnBnClickedSortButton();
	
	int geshu;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeDeletenumEdit();
	CString m_tree;
};
