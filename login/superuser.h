#pragma once
#include "afxdialogex.h"
#include<mysql.h>
// superuser 对话框

class superuser : public CDialogEx
{
	DECLARE_DYNAMIC(superuser)

public:
	superuser(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~superuser();
public:
	// 大小调整
	POINT Old;
	void resize();
	// 登录成功的mysql
	MYSQL superjacob;
	// 密码+用户名
	CString ps;
	CString un;
	// 四种模式
	int mode = 3;
	

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	
	afx_msg void OnPaint();
	CComboBox xialakuang;
	CListCtrl list1;
	CListCtrl list2;
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedList5(NMHDR* pNMHDR, LRESULT* pResult);
	CEdit inputbox;
	afx_msg void OnNMDblclkList5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnSelchangeCombo5();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	CButton Buttonshuaxing;
	afx_msg void OnNMDblclkList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton1();
};
