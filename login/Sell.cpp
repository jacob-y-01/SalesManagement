// Sell.cpp: 实现文件
//

#include "pch.h"
#include "login.h"
#include "afxdialogex.h"
#include "Sell.h"


// Sell 对话框

IMPLEMENT_DYNAMIC(Sell, CDialogEx)

Sell::Sell(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

Sell::~Sell()
{
}

void Sell::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, list1);
	DDX_Control(pDX, IDC_LIST4, list2);
}


BEGIN_MESSAGE_MAP(Sell, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &Sell::OnBnClickedButton2)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// Sell 消息处理程序


// 初始化窗口
BOOL Sell::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	this->ShowWindow(SW_SHOWMAXIMIZED);

	CRect rectDlg;
	list1.GetClientRect(rectDlg);
	int len = rectDlg.right / 4;
	list1.InsertColumn(1, "编号", LVCFMT_CENTER,len);
	list1.InsertColumn(2, "商品名称", LVCFMT_CENTER, len);
	list1.InsertColumn(3, "数量", LVCFMT_CENTER, len);
	list1.InsertColumn(4, "价格", LVCFMT_CENTER, len);

	list1.InsertItem(0, "1");
	list1.SetItemText(0, 1, "饼干");
	list1.SetItemText(0, 2, "1/盒");
	list1.SetItemText(0, 3, "10元");

	// 图片链接到数据库下载下来，然后再更新到图库中
	list2.InsertItem(0, "text",0);
	list2.InsertItem(1, "text",1);
	list2.InsertItem(2, "text",1);
	list2.InsertItem(3, "text",1);
	list2.InsertItem(4, "text",1);
	list2.SetItemText(0, 1, "测试");
	list2.SetItemText(0, 2, "测试");
	list2.SetItemText(0, 3, "测试");

	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Sell::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Sell::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	exit(0);
	CDialogEx::OnClose();
}
void Sell::resize()
{
	float fsp[2];
	POINT Newp; //获取现在对话框的大小
	CRect recta;
	GetClientRect(&recta);     //取客户区大小  
	Newp.x = recta.right - recta.left;
	Newp.y = recta.bottom - recta.top;
	fsp[0] = (float)Newp.x / Old.x;
	fsp[1] = (float)Newp.y / Old.y;
	CRect Rect;
	int woc;
	CPoint OldTLPoint, TLPoint; //左上角
	CPoint OldBRPoint, BRPoint; //右下角
	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //列出所有控件  
	while (hwndChild)
	{
		woc = ::GetDlgCtrlID(hwndChild);//取得ID
		GetDlgItem(woc)->GetWindowRect(Rect);
		ScreenToClient(Rect);
		OldTLPoint = Rect.TopLeft();
		TLPoint.x = long(OldTLPoint.x * fsp[0]);
		TLPoint.y = long(OldTLPoint.y * fsp[1]);
		OldBRPoint = Rect.BottomRight();
		BRPoint.x = long(OldBRPoint.x * fsp[0]);
		BRPoint.y = long(OldBRPoint.y * fsp[1]);
		Rect.SetRect(TLPoint, BRPoint);
		GetDlgItem(woc)->MoveWindow(Rect, TRUE);
		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	}
	Old = Newp;
}





// 窗口大小发生变化
void Sell::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	static bool a = false;
	// 利用静态变量只会初始化一次的特性
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		resize();
	}
	// 第一次不执行
}



// 最大化，最小化，粘贴复制等等系统消息
void Sell::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 窗口最大化
	if (nID == SC_MAXIMIZE)
	{
		
		CFont* m_editFont;
		m_editFont = this->GetFont();
		LOGFONT LogFont;
		m_editFont->GetLogFont(&LogFont);
		LogFont.lfHeight = 460;


		m_editFont->Detach();
		m_editFont->CreateFontIndirect(&LogFont);
		this->SetFont(m_editFont);
		m_editFont->Detach();
		
	}
	// 还原
	else if (nID == SC_RESTORE)
	{
		CFont m_editFont;
		m_editFont.CreatePointFont(50, "宋体");
		this->SetFont(&m_editFont); // 设置新字体
	}
	else
	{

	}


	CDialogEx::OnSysCommand(nID, lParam);
}
