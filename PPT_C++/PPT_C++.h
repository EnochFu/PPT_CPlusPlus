
// PPT_C++.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPPT_CApp: 
// �йش����ʵ�֣������ PPT_C++.cpp
//

class CPPT_CApp : public CWinApp
{
public:
	CPPT_CApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPPT_CApp theApp;