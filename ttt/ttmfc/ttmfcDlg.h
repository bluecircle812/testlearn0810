
// ttmfcDlg.h : ͷ�ļ�
//

#pragma once
#include "HttpConnect.h"

// CttmfcDlg �Ի���
class CttmfcDlg : public CDialogEx
{
// ����
public:
	CttmfcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TTMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	//int request(char* hostname, char* api, char* parameters);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	HttpConnect* http;
	int k;
	void step();
	UINT32	wAccuracy;												//��ʱ���ֱ���
	int TimerID;
};
