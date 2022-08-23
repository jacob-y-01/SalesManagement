
// loginDlg.h:头文件
//
#include"superuser.h"
#include "Sell.h"
#include<mysql.h>

//extern "C" MYSQL superjacob;
#pragma once


// CloginDlg 对话框
class CloginDlg : public CDialogEx
{
// 构造
public:
	CloginDlg(CWnd* pParent = nullptr);	// 标准构造函数


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
#endif

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
	afx_msg void OnBnClickedRadio1();
	CButton radio;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	CEdit inputbox;
	CEdit inputbox1;
	superuser super;
	Sell sell;
};
