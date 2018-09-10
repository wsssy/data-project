
// Binary_sort_treeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Binary_sort_tree.h"
#include "Binary_sort_treeDlg.h"
#include "afxdialogex.h"
#include"DeleteTDlg.h"
#include "DeleteFDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include<iostream>
#include<string>
#define    OK    1
#define    FALSE  0
#define MAXQSIZE   100;         //���г���
using namespace std;


typedef struct BiTNode {
	int data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
typedef struct Qnode        //������  
{
	BiTree Queue[100];   //M��ʾѭ��ָ����еĳ���  
	int nfront, nrear;        //ͷ��β  ���ڴ�����������int�Ϳ���  
}head;

int node[100];//�ڵ�����
int pre[100];
int inn[100];
int tree[31];

string str,str_tree;
string m_PreOrder = " ";
string m_InOrder = " ";

int num;
BiTree T;

int Inputnum();//���ؽڵ����
void Insert_BST(BiTree &T, BiTree S);//���ڵ�S���������T��
void Creat_BST(BiTree &T, int num);//�ø����Ľڵ㽨��һ�ö�����
int Delete(BiTree &p);//ɾ���ڵ�p
int DeleteBST(BiTree &T, int key);//�ҵ�key��ֵ��Ӧ�Ľڵ㲢ɾ��
void OutputNum(int num);//���ת��Ϊstring
int InOrderTraverse(BiTree T, int i);
int PreOrderTraverse(BiTree T, int i);
void OutputTree(string &str);
void Levelorder(BiTree T);
string str_kong(int ch);

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBinary_sort_treeDlg �Ի���



CBinary_sort_treeDlg::CBinary_sort_treeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BINARY_SORT_TREE_DIALOG, pParent)
	, m_inputnum(_T(""))
	, m_deletenum(0)
	, m_pre(_T(""))
	, m_inn(_T(""))
	, geshu(0)
	, m_tree(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBinary_sort_treeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INPUTNUM_EDIT, m_inputnum);

	str = (CW2A(m_inputnum.GetString()));
	//str = m_inputnum.GetString();

	DDX_Text(pDX, IDC_DELETENUM_EDIT, m_deletenum);

	DDX_Text(pDX, IDC_PRE_EDIT, m_pre);

	DDX_Text(pDX, IDC_INN_EDIT, m_inn);

	DDX_Text(pDX, IDC_EDIT1, geshu);
	DDX_Text(pDX, IDC_TREE_EDIT, m_tree);
}

BEGIN_MESSAGE_MAP(CBinary_sort_treeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &CBinary_sort_treeDlg::OnBnClickedDeleteButton)
	ON_BN_CLICKED(IDC_SORT_BUTTON, &CBinary_sort_treeDlg::OnBnClickedSortButton)
	
	ON_EN_CHANGE(IDC_EDIT1, &CBinary_sort_treeDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_DELETENUM_EDIT, &CBinary_sort_treeDlg::OnEnChangeDeletenumEdit)
END_MESSAGE_MAP()


// CBinary_sort_treeDlg ��Ϣ�������

BOOL CBinary_sort_treeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CBinary_sort_treeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBinary_sort_treeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBinary_sort_treeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBinary_sort_treeDlg::OnBnClickedDeleteButton()
{
	UpdateData(TRUE);
	INT_PTR nRes;
	int del,key;
	CDeleteTDlg dTDlg;
	CDeleteFDlg dFDlg;
	
	key = m_deletenum;
	
	del = DeleteBST(T, key);
	if (del) { nRes = dTDlg.DoModal(); num--; }
	else { nRes = dFDlg.DoModal(); }


	PreOrderTraverse(T, 0);
	InOrderTraverse(T, 0);
	OutputNum(num);
	Levelorder(T);
	OutputTree(str_tree);
	m_tree = str_tree.c_str();

	geshu = num + 1;

	m_pre = m_PreOrder.c_str();

	m_inn = m_InOrder.c_str();
	UpdateData(FALSE);
	
}




int Inputnum() {
	

	int i, str_n;
	int num;//����Ľڵ����
	
	str_n = str.length();///�������Ŀ��ַ���
	const char *shu = new char[str_n + 1];
	shu = str.c_str();



	
	int m = 0;
	for (i = 0; i <= str_n; i++) {
		if (shu[i] >= '0' && shu[i] <= '9') {
			if (i == 0)node[m] = shu[i] - '0';
			else if (shu[i - 1] >= '0' && shu[i - 1] <= '9') {
				node[m] = node[m] * 10 + (shu[i] - '0');
			}
			else node[m] = shu[i] - '0';
		}
		else {
			if (shu[i - 1] >= '0' && shu[i - 1] <= '9')m++;
			else m = m;
		}
	}
	m--;//�����һ��
	num = m;
	return num;

}

void Insert_BST(BiTree &T, BiTree S)
{
	BiTree p;
	BiTree q;
	if (!T) T = S;
	else
	{
		p = T;
		q = p;
		while (p)
		{
			q = p;
			if (S->data < p->data)p = p->lchild;
			else p = p->rchild;
		}
		if (S->data < q->data) q->lchild = S;
		else q->rchild = S;
	}
	return;
}

void Creat_BST(BiTree &T, int num)
{
	int i; BiTree S; T = NULL;
	for (i = 0; i <= num; i++)
	{
		S = (BiTNode *)malloc(sizeof(BiTNode));
		S->data = node[i];
		S->lchild = NULL;
		S->rchild = NULL;
		Insert_BST(T, S);
	}
	return;
}

int DeleteBST(BiTree &T, int key)
{
	if (!T) return FALSE;
	else {
		if (key == T->data) { return Delete(T); }
		else if (key < T->data)
			return DeleteBST(T->lchild, key);
		else return DeleteBST(T->rchild, key);
	}
}

int Delete(BiTree &p) {//�㷨9.8
	BiTree q, s;
	if (!p->rchild) {
		q = p; p = p->lchild; free(q);
	}
	else if (!p->lchild) {
		q = p; p = q->rchild; free(q);
	}
	else {
		q = p; s = p->lchild;
		while (s->rchild) { q = s; s = s->rchild; }
		p->data = s->data;
		if (q != p) q->rchild = s->lchild;
		else q->lchild = s->lchild;
		delete s;
	}
	return OK;
}

int PreOrderTraverse(BiTree T, int i) {
	if (T) {
		pre[i] = T->data;
		i++;
		i = PreOrderTraverse(T->lchild, i);
		i = PreOrderTraverse(T->rchild, i);
	}
	return i;
}

int InOrderTraverse(BiTree T, int i) {
	if (T) {
		i = InOrderTraverse(T->lchild, i);
		inn[i] = T->data; i++;
		i = InOrderTraverse(T->rchild, i);
	}
	return i;
}

void OutputNum(int num) {

	int i;
	m_PreOrder = to_string(pre[0]);
	m_InOrder = to_string(inn[0]);
	for (i = 1; i <= num; i++) {
		m_PreOrder += ","+to_string(pre[i]) ;
		m_InOrder += ","+to_string(inn[i]) ;
	}

}
void Levelorder(BiTree T)
{
	BiTree p;  // ����һ�� ������ָ��p  
	BiTree kong;
	kong = (BiTNode *)malloc(sizeof(BiTNode));
	kong->data = 0;
	kong->lchild = NULL;
	kong->rchild = NULL;
	Qnode Q; Q.nrear = Q.nfront = 0;                                //��ʼ���������  
	if (T != NULL)
	{
		Q.Queue[Q.nrear] = T;                                         //���T����  
		Q.nrear = (Q.nrear + 1) % MAXQSIZE;              //����һ��ββ��  
		for (int i = 0; i<31; i++)                         //������ ���в���  Ҳ���Ƕ�����������  
		{
			p = Q.Queue[Q.nfront];                                        //p���ڶ���ͷ  
			tree[i] = p->data;                                              //�������ͷ��  
			Q.nfront = (Q.nfront + 1) % MAXQSIZE;           //front�����ƶ�һ��  
			if (p->lchild)                                                    //��������Ӳ���  
			{
				Q.Queue[Q.nrear] = p->lchild;                     //��ôβ����������  
				Q.nrear = (Q.nrear + 1) % MAXQSIZE;                 //rear�����ƶ�һ��  
			}
			else {
				Q.Queue[Q.nrear] = kong;
				Q.nrear = (Q.nrear + 1) % MAXQSIZE;
			}
			if (p->rchild)                                              //Ȼ�����Һ���  
			{
				Q.Queue[Q.nrear] = p->rchild;             //ͬ��  
				Q.nrear = (Q.nrear + 1) % MAXQSIZE;
			}
			else {
				Q.Queue[Q.nrear] = kong;
				Q.nrear = (Q.nrear + 1) % MAXQSIZE;
			}
		}
	}
}

void OutputTree(string &str) {
	int i;
	
	str = "                                             ";
	str += str_kong(tree[0]);
	str += " \r\n"; str += " \r\n";
	str += "                     ";
	str += str_kong(tree[1]);
	str += "                                             ";
	str += str_kong(tree[2]);
	str += " \r\n"; str += " \r\n";
	str += "         ";
	for (int i = 3; i <= 5; i++) {
		str += str_kong(tree[i]);
		str += "                     ";
	}
	str += str_kong(tree[6]);
	str += " \r\n"; str += " \r\n";
	str += "   ";
	for (int i = 7; i <= 13; i++) {
		str += str_kong(tree[i]); str += "         ";
	}
	
	str += str_kong(tree[14]);
	str += " \r\n"; str += " \r\n";
	for (int i = 15; i <= 22; i++) {
		str += str_kong(tree[i]); str += "   ";
	}

	for (int i = 23; i <= 29; i++) {
		str += str_kong(tree[i]); str += "   ";
	}
	str += str_kong(tree[30]);
}

string str_kong(int ch) {

	return(ch == 0) ? "   " : (ch>99) ? to_string(ch) : (ch>9) ? (" " + to_string(ch)) : ("  " + to_string(ch));
}


void CBinary_sort_treeDlg::OnBnClickedSortButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);


	num = Inputnum();

	Creat_BST(T, num);
	
	PreOrderTraverse(T, 0);
	InOrderTraverse(T, 0);
	OutputNum(num);
	Levelorder(T);
	OutputTree(str_tree);
	geshu = num+1;
	
	m_pre = m_PreOrder.c_str();

	m_inn = m_InOrder.c_str();

	m_tree = str_tree.c_str();
	UpdateData(FALSE);
}






void CBinary_sort_treeDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CBinary_sort_treeDlg::OnEnChangeDeletenumEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
