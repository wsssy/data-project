#pragma once


// CDeleteFDlg �Ի���

class CDeleteFDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteFDlg)

public:
	CDeleteFDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeleteFDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETE_F_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
