// MySerialPortDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "MySerialPort.h"
#include "serialport.h"
#include "tchart1.h"
#include "CSeries.h"
#include "afx.h"

#define PACK_MAX_SIZE 20
// CMySerialPortDlg �Ի���
class CMySerialPortDlg : public CDialog
{
	// ����
public:
	CSerialPort m_SerialPort;
	bool m_bSerialPortOpened;
	CMySerialPortDlg(CWnd* pParent = NULL);	// ��׼���캯��

	// �Ի�������
	enum { IDD = IDD_MYSERIALPORT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctrlComboComPort;
	CComboBox m_ctrlComboBaudRate;
	CComboBox m_ctrlComboData;
	CComboBox m_ctrlComboStop;
	CComboBox m_ctrlComboParity;
	UINT m_nPackData[PACK_MAX_SIZE];
	CString  m_strPackData[5];
public:
	afx_msg LONG OnComm(WPARAM ch, LPARAM port);
	afx_msg void OnButtonOpen();
	afx_msg void OnButtonClose();
	int m_nRecvCount;
	afx_msg void OnBnClickedButtonClearcount();
	afx_msg void OnBnClickedButtonCleardata();
	void DataReady();
	void DrawSeries(int iSeriesIndex,const CArray<double,double> &myDataArray);
	//double GetWindowAver(int iSeriesIndex);
	int m_nRecvPack;
	int m_nCorrectPack;
	int m_index;
	CTchart1 m_Chart;
	CSeries m_myECG;
	CSeries m_MyXSeries;	
	CSeries m_MyYSeries;	
	CSeries m_MyZSeries;
	CArray<double,double> m_ECGDataArray;
	CArray<double,double> m_XDataArray;
	CArray<double,double> m_YDataArray;	
	CArray<double,double> m_ZDataArray;
	COleSafeArray m_TValues;
	COleSafeArray m_YValues;
	//double m_fWindowData[3][10];
	//CString m_strAver[3];
	CFile m_ecgfile;
	CFile m_errfile;
	CFile m_accfile;
  CFile m_votfile;
  CFile m_ecgcsfile;
	//CArchive m_ar;
  afx_msg void OnEnChangeEdit1();
};
