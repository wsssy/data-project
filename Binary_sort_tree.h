
// Binary_sort_tree.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBinary_sort_treeApp: 
// �йش����ʵ�֣������ Binary_sort_tree.cpp
//

class CBinary_sort_treeApp : public CWinApp
{
public:
	CBinary_sort_treeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBinary_sort_treeApp theApp;