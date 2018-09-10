
// Binary_sort_treeDlg.cpp : 实现文件
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
#define MAXQSIZE   100;         //队列长度
using namespace std;


typedef struct BiTNode {
	int data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
typedef struct Qnode        //链队列  
{
	BiTree Queue[100];   //M表示循环指针队列的长度  
	int nfront, nrear;        //头和尾  用于处理数组所以int就可以  
}head;

int node[100];//节点数组
int pre[100];
int inn[100];
int tree[31];

string str,str_tree;
string m_PreOrder = " ";
string m_InOrder = " ";

int num;
BiTree T;

int Inputnum();//返回节点个数
void Insert_BST(BiTree &T, BiTree S);//将节点S插入二叉树T中
void Creat_BST(BiTree &T, int num);//用给定的节点建立一棵二叉树
int Delete(BiTree &p);//删除节点p
int DeleteBST(BiTree &T, int key);//找到key的值对应的节点并删除
void OutputNum(int num);//输出转换为string
int InOrderTraverse(BiTree T, int i);
int PreOrderTraverse(BiTree T, int i);
void OutputTree(string &str);
void Levelorder(BiTree T);
string str_kong(int ch);

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CBinary_sort_treeDlg 对话框



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


// CBinary_sort_treeDlg 消息处理程序

BOOL CBinary_sort_treeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBinary_sort_treeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
	int num;//输入的节点个数
	
	str_n = str.length();///不加最后的空字符串
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
	m--;//最后会多一个
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

int Delete(BiTree &p) {//算法9.8
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
	BiTree p;  // 建立一个 工作树指针p  
	BiTree kong;
	kong = (BiTNode *)malloc(sizeof(BiTNode));
	kong->data = 0;
	kong->lchild = NULL;
	kong->rchild = NULL;
	Qnode Q; Q.nrear = Q.nfront = 0;                                //初始化这个队列  
	if (T != NULL)
	{
		Q.Queue[Q.nrear] = T;                                         //如果T不空  
		Q.nrear = (Q.nrear + 1) % MAXQSIZE;              //加入一个尾尾部  
		for (int i = 0; i<31; i++)                         //如果这个 队列不空  也就是二叉树不结束  
		{
			p = Q.Queue[Q.nfront];                                        //p等于队列头  
			tree[i] = p->data;                                              //输出队列头部  
			Q.nfront = (Q.nfront + 1) % MAXQSIZE;           //front往后移动一个  
			if (p->lchild)                                                    //如果做左孩子不空  
			{
				Q.Queue[Q.nrear] = p->lchild;                     //那么尾部加上左孩子  
				Q.nrear = (Q.nrear + 1) % MAXQSIZE;                 //rear往后移动一个  
			}
			else {
				Q.Queue[Q.nrear] = kong;
				Q.nrear = (Q.nrear + 1) % MAXQSIZE;
			}
			if (p->rchild)                                              //然后是右孩子  
			{
				Q.Queue[Q.nrear] = p->rchild;             //同上  
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
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CBinary_sort_treeDlg::OnEnChangeDeletenumEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
