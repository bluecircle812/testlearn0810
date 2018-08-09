
// ttmfcDlg.h : 头文件
//

#pragma once
#include "HttpConnect.h"

// CttmfcDlg 对话框
class CttmfcDlg : public CDialogEx
{
// 构造
public:
	CttmfcDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TTMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	UINT32	wAccuracy;												//定时器分辨率
	int TimerID;
};
