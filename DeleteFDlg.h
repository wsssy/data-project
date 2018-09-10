#pragma once


// CDeleteFDlg 对话框

class CDeleteFDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteFDlg)

public:
	CDeleteFDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeleteFDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETE_F_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
