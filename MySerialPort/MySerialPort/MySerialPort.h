// MySerialPort.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMySerialPortApp:
// �йش����ʵ�֣������ MySerialPort.cpp
//

class CMySerialPortApp : public CWinApp
{
public:
	CMySerialPortApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMySerialPortApp theApp;