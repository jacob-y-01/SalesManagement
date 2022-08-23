#pragma once
#include "afxdialogex.h"


// Sell 对话框

class Sell : public CDialogEx
{
	DECLARE_DYNAMIC(Sell)

public:
	Sell(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Sell();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	POINT Old;
	void resize();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	CListCtrl list1;
	CListCtrl list2;
};
