
// Binary_sort_treeDlg.h : 头文件
//

#pragma once
#include<string>

// CBinary_sort_treeDlg 对话框
/*extern string str;
extern string m_PreOrder;
*/

class CBinary_sort_treeDlg : public CDialogEx
{
// 构造
public:
	CBinary_sort_treeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BINARY_SORT_TREE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
