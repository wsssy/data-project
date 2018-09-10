#pragma once


// CDeleteTDlg 对话框

class CDeleteTDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteTDlg)

public:
	CDeleteTDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeleteTDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETE_T_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
