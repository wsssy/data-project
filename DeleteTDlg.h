#pragma once


// CDeleteTDlg �Ի���

class CDeleteTDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteTDlg)

public:
	CDeleteTDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeleteTDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETE_T_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
