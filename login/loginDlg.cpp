
// loginDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "login.h"
#include "loginDlg.h"

#include "afxdialogex.h"
#include <iostream>
#include <mysql.h>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
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
public:
	afx_msg void OnNMDblclkList5(NMHDR* pNMHDR, LRESULT* pResult);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST5, &CAboutDlg::OnNMDblclkList5)
END_MESSAGE_MAP()


// CloginDlg 对话框



CloginDlg::CloginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CloginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, radio);
	DDX_Control(pDX, IDC_EDIT3, inputbox);
	DDX_Control(pDX, IDC_EDIT2, inputbox1);
}

BEGIN_MESSAGE_MAP(CloginDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CloginDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_BUTTON2, &CloginDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CloginDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CloginDlg 消息处理程序

BOOL CloginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 自动补好密码
	SetDlgItemText(IDC_EDIT3, TEXT("jacob"));
	SetDlgItemText(IDC_EDIT2, TEXT("1234"));
	// 设置默认选中管理模式
	radio.SetCheck(BST_CHECKED);

	// 显示登录窗口，移动到合适位置
	ShowWindow(SW_SHOWNORMAL);
	MoveWindow(600,400,820,600);


	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CloginDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CloginDlg::OnPaint()
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
HCURSOR CloginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CloginDlg::OnBnClickedRadio1()
{
	if (IDCANCEL==MessageBox(TEXT("你正在使用超级管理员身份登录\n\n确定使用超级管理员身份登录？"), TEXT("警告"), 1))
	{
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	}
}


void CloginDlg::OnBnClickedButton2()
{
	exit(0);
}


void CloginDlg::OnBnClickedButton1()
{
	//1. 判断是否使用超级管理员？
	// 获取输入框内容
		//1.1 是：核对身份，成果与否
		//1.2 否：
			//核对身份

	//获取并且保存文本框内容
	CString username, password;
	GetDlgItemText(IDC_EDIT3, username);
	GetDlgItemText(IDC_EDIT2, password);



	
	
	if (radio.GetCheck())
	{
		//超级管理员身份

		MYSQL mysql;
		mysql_init(&mysql);
		string a1 = password.GetBuffer(0);
		string a2 =((LPCTSTR)username);
		// 连接数据库
		
		// 登录超时好长
		if (mysql_real_connect(&mysql, "150.158.25.142", a2.c_str(), a1.c_str(), "sellsystem", 3306, NULL, 0))
		{
			// 保存密码和mysql;
			super.superjacob = mysql;
			super.ps = password;
			super.un = username;



			// 显示管理窗口
			this->ShowWindow(SW_SHOW);
			this->ShowWindow(SW_HIDE);
			super.DoModal();

			//清空
			SetDlgItemText(IDC_EDIT2, TEXT(""));
			SetDlgItemText(IDC_EDIT3, TEXT(""));
			//要不然就返回mysql对象
		}
		else
		{
			MessageBox(TEXT("登录失败"), TEXT("提示"));
			return;
		}
	}
	else
	{
		
		this->ShowWindow(SW_SHOW);
		this->ShowWindow(SW_HIDE);
		sell.DoModal();
		//其他身份
		//其他身份进行数据库管理
		//对数据库只有查询功能
		return;
	}
	



}
void CAboutDlg::OnNMDblclkList5(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
