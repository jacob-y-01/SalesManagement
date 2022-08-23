// superuser.cpp: 实现文件
//

#include "pch.h"
#include "login.h"
#include "afxdialogex.h"
#include "superuser.h"


// superuser 对话框

IMPLEMENT_DYNAMIC(superuser, CDialogEx)

superuser::superuser(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
}

superuser::~superuser()
{
}

void superuser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO5, xialakuang);
	DDX_Control(pDX, IDC_LIST5, list1);
	DDX_Control(pDX, IDC_LIST3, list2);
	DDX_Control(pDX, IDC_EDIT1, inputbox);
	DDX_Control(pDX, IDC_BUTTON5, Buttonshuaxing);
}


BEGIN_MESSAGE_MAP(superuser, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST5, &superuser::OnLvnItemchangedList5)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST5, &superuser::OnNMDblclkList5)
	ON_WM_SIZE()
//	ON_WM_CHAR()
ON_EN_KILLFOCUS(IDC_EDIT1, &superuser::OnKillfocusEdit1)
ON_BN_CLICKED(IDC_BUTTON3, &superuser::OnBnClickedButton3)
ON_CBN_SELCHANGE(IDC_COMBO5, &superuser::OnSelchangeCombo5)
ON_BN_CLICKED(IDC_BUTTON5, &superuser::OnBnClickedButton5)
ON_BN_CLICKED(IDC_BUTTON4, &superuser::OnBnClickedButton4)
ON_NOTIFY(NM_DBLCLK, IDC_LIST3, &superuser::OnNMDblclkList3)
ON_BN_CLICKED(IDC_BUTTON1, &superuser::OnBnClickedButton1)
END_MESSAGE_MAP()


// superuser 消息处理程序


void superuser::OnDestroy()
{
	mysql_close(&superjacob);
	CDialogEx::OnDestroy();

	exit(0);
}

// 重绘事件
void superuser::OnPaint()
{
	CPaintDC dc(this);
	// 太频繁了，不适合
}


// 初始化
BOOL superuser::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置列表框的高
	CImageList   m_l;
	m_l.Create(1, 40, TRUE | ILC_COLOR32, 1, 0);
	list2.SetImageList(&m_l, LVSIL_SMALL);
	// TODO:  在此添加额外的初始化
	CRect rect;
	GetClientRect(&rect);//取客户区大小
	Old.x = rect.right - rect.left;
	Old.y = rect.bottom - rect.top;


			// 设置下拉框参数
	xialakuang.AddString("销售情况");
	xialakuang.AddString("商品");
	xialakuang.AddString("店铺");
	xialakuang.AddString("员工");
	xialakuang.SetCurSel(mode);
	// 设置列表框参数
	DWORD dwStyle = list2.GetExtendedStyle();                    //添加列表框的网格线！！！
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	list2.SetExtendedStyle(dwStyle);

	MYSQL_RES* result,*result1;
	MYSQL_ROW row,row1;

	CRect rectDlg;
	GetClientRect(rectDlg);						//获取窗口大小
	rectDlg.right = rectDlg.right - 40;			//边缘区大小

	// 设置字符编码，防止中文乱码
	mysql_query(&superjacob, "set names gbk");


	// 刷新列表框
	OnBnClickedButton5();


	// 为后续list1的插入做准备
	list1.InsertItem(0, TEXT(" "));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void superuser::OnLvnItemchangedList5(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


// 双击list1事件
void superuser::OnNMDblclkList5(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	// 获取鼠标位置
	CPoint point;
	GetCursorPos(&point);
	
	// 获取窗口位置
	CRect rectDlg;
	list1.GetClientRect(rectDlg);//获得list（客户区）的大小

	CRect rectDlg2;
	list1.GetWindowRect(rectDlg2);//获得list窗体的位置

	CRect rectDlg3;
	GetWindowRect(rectDlg3);//获得主窗体的位置
	// 不知道为什么会有-11的偏差
	rectDlg3.top = rectDlg3.top + 11;
	rectDlg3.left = rectDlg3.left + 11;

	int cols = list1.GetHeaderCtrl()->GetItemCount();//列数
			// 在窗口中相对位置						单列宽度					单列宽度				列表框位置
	int x = (((point.x - rectDlg3.left)/ ((rectDlg.right) / cols))* ((rectDlg.right) / cols)) + (rectDlg2.left-rectDlg3.left);
	int y = rectDlg2.top - rectDlg3.top;

	// 设置输入框的位置和大小                              
	inputbox.SetWindowPos(0,x,
							y,
							(rectDlg.right) / cols,						//输入框的宽
							40,											//输入框的高
							SWP_NOACTIVATE| SWP_SHOWWINDOW);			//激活 | 显示
	// 让list1显示于输入框的底下
	list1.ModifyStyle(0, WS_CLIPSIBLINGS);

	// 设为焦点，可以立即输入
	inputbox.SetFocus();
	*pResult = 0;
}


// 窗口大小发生变化
void superuser::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	static bool a=false;
	// 利用静态变量只会初始化一次的特性
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED) 
	{
		resize();
	}
	// 第一次不执行
	if(a)OnBnClickedButton5();
	a = true;
}

// 窗口变化响应函数
void superuser::resize()
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
		if (hwndChild == (HWND)xialakuang)
		{
			// 因为下拉框如果改变其宽高，会导致下拉功能失效，所以排除
			hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
			continue;
		}
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




// 输入框对回车输入的处理
BOOL superuser::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_EDIT1)//如果按下回车，且是在输入框控件上
		{
			this->OnKillfocusEdit1();
		}
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);


}


// 当输入框失去焦点，同样也要把数据写上列表框
void superuser::OnKillfocusEdit1()
{
	// 获取输入框内容
	CString str1;
	GetDlgItemText(IDC_EDIT1, str1);
	// 判断输入是否为空
	if (str1.Compare(""))
	{
		// 获取输入框的位置
		CRect rectDlg;
		inputbox.GetWindowRect(rectDlg);

		// 获取主窗口的位置
		CRect rectDlg2;
		GetWindowRect(rectDlg2);

		// 获得list（客户区）的大小
		CRect rectDlg3;
		list1.GetClientRect(rectDlg3);

		// 50是防止会有少量误差，我也不知道哪来的误差
		int sit = rectDlg.left - rectDlg2.left + 50;

		// list有几列内容
		int cols = list1.GetHeaderCtrl()->GetItemCount();


		CRect rectDlg4;
		list1.GetWindowRect(rectDlg4);
		// 根据输入框的位置不同，判断是在list1还是list2输入
		if (rectDlg.top < rectDlg4.bottom)
		{
			// 添加进list
			// 由于操作后清空列表导致失去头部
			if (!list1.SetItemText(0, sit / (rectDlg3.right / cols), str1))
			{
				list1.InsertItem(0, TEXT(""));
				list1.SetItemText(0, sit / (rectDlg3.right / cols), str1);
			}

		}
		else
		{
			list2.GetClientRect(rectDlg);
			CString tablename;
			int Case = xialakuang.GetCurSel();
			switch (Case)
			{
			case 0:tablename = "store"; break;				// 根据下拉框选则要操作的表名
			case 1:tablename = "goods"; break;
			case 2:tablename = "sales_status"; break;
			case 3:tablename = "user"; break;
			default:break;
			};
			CString sql;
			sql.Format("UPDATE %s SET ", tablename);

			// 获取滚动条滚动了几列
			int a = list2.GetScrollPos(SB_VERT);

			// 获取输入框位置
			CRect rectDlg;
			inputbox.GetWindowRect(rectDlg);

			// list2的位置
			CRect rectDlg1;
			list2.GetWindowRect(rectDlg1);

			// list2的大小
			CRect rectDlg2;
			list2.GetClientRect(rectDlg2);

			//			输入框在list2的位置
			int hang = (rectDlg.top + 20 - rectDlg1.top) / 40;


			// 获取列数
			int count = list2.GetHeaderCtrl()->GetItemCount();
			int lie = (rectDlg.left - rectDlg1.left + 40) / (rectDlg2.right / count);

			//list control控件的行列是从【0，0】开始 所以-1,行需要加上已被滚动条移走的行数
			hang = hang + a - 1;

			// 获取到要修改的表头
			LV_COLUMN lvColumn;
			char uin[20];
			lvColumn.pszText = uin;
			lvColumn.cchTextMax = 20;
			lvColumn.mask = LVCF_TEXT;
			CString df;
			// 获取到了表头，且输入框不为空
			if (list2.GetColumn(lie, &lvColumn) && (!str1.IsEmpty()))
			{
				df = lvColumn.pszText;
				sql.Format("%s %s = '%s' where", sql, df, str1);
				// 修改表格，避免频繁刷新
				list2.SetItemText(hang, lie, str1);
			}


			// 判断是不是第一个where条件
			static bool first = 1;
			for (int i = 0; i < count; i++)
			{
				// 已经被更改的列不需要改
				if (i != lie)
				{
					list2.GetColumn(i, &lvColumn);
					df = lvColumn.pszText;
					//获取列
					CString text = list2.GetItemText(hang, i);// WHERE 列名称 = 某值
					if (!text.IsEmpty() && first)
					{
						first = 0;
						sql.Format("%s  %s = '%s'", sql, df, text);
					}
					else if (!text.IsEmpty())
					{
						sql.Format("%s and %s = '%s'", sql, df, text);
					}
					else
					{
						// 是空值
					}
				}
			}
			if (0!=mysql_query(&superjacob, sql))
			{
				MessageBox("修改失败，请检查格式");
				return; first = 1;
			}
			first = 1;
		}
	}
	//OnBnClickedButton5();
	// 清空隐藏输入框
	inputbox.ShowWindow(false);
	SetDlgItemText(IDC_EDIT1, CA2CT(""));
	CString tm=
	list1.GetItemText(0, 4);
	// 在ondialog初始化中只初始化一行 list1.InsertItem(0,TEXT(" "));
}


// 当下拉框发生改变的事件
// 增删改完数据调用一下
void superuser::OnSelchangeCombo5()
{
	//依据superuser中的mode和下拉框所选中的内容更新显示内容
	CString text; // 选定项的文本内容
	int cindex = xialakuang.GetCurSel(); // 获取选定项的序号
	xialakuang.GetLBText(cindex, text); // 获取选定项的文本内容
	//MessageBox(text);
	OnBnClickedButton5();
}

// 增加数据
void superuser::OnBnClickedButton3()
{
	int Case = xialakuang.GetCurSel();				//获取下拉框的情况
	//3店员，0店铺，1商品，2销售情况
	
	// 对sql进行规整
	CString sql, tablename,values;
	switch (Case)
	{
	case 0:tablename = "store"; break;				// 根据下拉框选则要操作的表名
	case 1:tablename = "goods"; break;
	case 2:tablename = "sales_status"; break;
	case 3:tablename = "user"; break;
	default:break;
	};
	
	// 对sql进行整值
	for (int i = 0; i < list1.GetHeaderCtrl()->GetItemCount(); i++)
	{
		if (!list1.GetItemText(0, i).IsEmpty() && i != 0)
		{
			values.Format("%s,'%s'", values, list1.GetItemText(0, i));
		}
		else if (!list1.GetItemText(0, i).IsEmpty() && i == 0)
		{
			values.Format("'%s'", list1.GetItemText(0, i));
		}
		else if (list1.GetItemText(0, i) == ""&&i==0)
		{
			values.Format("'NULL'", values);
		}
		else
		{
			values.Format("%s,'NULL'", values);
		}
	}
	sql.Format("INSERT INTO %s VALUES(%s)",tablename,values);
	if (0==mysql_query(&superjacob, sql))
	{
		// 刷新下列表格
		OnBnClickedButton5();
	}
	else
	{
		MessageBox("添加失败！请检查是否规范");
	}
	// 清空list1;
	list1.DeleteAllItems();
	// 开辟一下行，不然后续无法继续输入
	list1.InsertItem(0, TEXT(""));
	//while (n_list.DeleteColumn(0));	//清空所有表头
}

// 刷新列表显示内容（除了条件查询以外）
void superuser::OnBnClickedButton5()
{
	while (list1.DeleteColumn(0));	//清空所有表头
	while (list2.DeleteColumn(0));	//清空所有表头

	// 清空所有数据
	list2.DeleteAllItems();
	MYSQL_RES* result,*result1;
	MYSQL_ROW row,row1;

	// 设置字符编码，防止中文乱码
	if (0 != mysql_query(&superjacob, "set names gbk"))
	{
		MessageBox("设置字符失败");
	}

	// 查询列名
	CString tablename,colsname;
	int Case = xialakuang.GetCurSel();
	switch (Case)
	{
	case 0:tablename = "store"; break;				// 根据下拉框选则要操作的表名
	case 1:tablename = "goods"; break;
	case 2:tablename = "sales_status"; break;
	case 3:tablename = "user"; break;
	default:break;
	};

	// 查询列名
	colsname.Format("SELECT COLUMN_NAME FROM information_schema.columns WHERE table_name = '%s' AND table_schema = 'sellsystem' ORDER BY ordinal_position", tablename);
	if (0 != mysql_query(&superjacob, colsname))
	{
		MessageBox("刷新列表失败！");
	}
	result1 = mysql_store_result(&superjacob);	//列名结果集存储在result1

	// 查询表中数据
	tablename.Format("SELECT * FROM %s", tablename);
	if(0!=mysql_query(&superjacob, tablename))
	{
		MessageBox("刷新列表失败！");
	}
	result = mysql_store_result(&superjacob);	//查询结果结果集存储在result

	//int num = mysql_num_rows(result1);		//结果行数
	//int num = mysql_num_fields(result);        //将结果集列数


	// 动态布置列名
	int i = 1;
	CRect rectDlg;
	GetClientRect(rectDlg);			
	// 系统区偏差
	int list1lengh= rectDlg.right-43;
	rectDlg.right = rectDlg.right - 68;
	int num = mysql_num_fields(result);
	//将一整行内容取到row1中
	while (row1 = mysql_fetch_row(result1))
	{							//row[0]代表整行中第0个内容
		list1.InsertColumn(i, row1[0], LVCFMT_CENTER, list1lengh / num);
		bool temp=list2.InsertColumn(i, row1[0], LVCFMT_CENTER, rectDlg.right / num);
		i++;
	}

	// 布置内容
	int j = 0;
	while ((row = mysql_fetch_row(result)))  //遇到最后一行，则中止循环
	{
		list2.InsertItem(j, row[0]);
		for (int i = 0; i < num; i++)
		{
			list2.SetItemText(j, i, row[i]);
		}
		j++;
	}
	mysql_free_result(result);     //释放结果集所占用的内存
	mysql_free_result(result1);     //释放结果集所占用的内存
}


// 删除按钮
void superuser::OnBnClickedButton4()
{
	CString tablename,sql;
	int Case= xialakuang.GetCurSel();
	switch (Case)
	{
	case 0:tablename = "store"; break;				// 根据下拉框选则要操作的表名
	case 1:tablename = "goods"; break;
	case 2:tablename = "sales_status"; break;
	case 3:tablename = "user"; break;
	default:break;
	};
	sql.Format("DELETE FROM %s WHERE ", tablename);
	// 遍历每一行

	int iItem;
	BOOL flag;
	flag = false;
	for (iItem = list2.GetItemCount() - 1; iItem >= 0; iItem--)
	{
		if (LVIS_SELECTED == list2.GetItemState(iItem, LVIS_SELECTED))     //如果有选中行
		{
			flag = true;
			//int count = list2.GetSelectedCount();选中了多少行
			// 获取列数
			int count = list2.GetHeaderCtrl()->GetItemCount();
			for (int i=0; i<count;i++)
			{
				// 获取0-count的表头
				LV_COLUMN lvColumn;
				char uin[20];
				lvColumn.pszText = uin;
				lvColumn.cchTextMax = 20;
				lvColumn.mask = LVCF_TEXT;
				CString df;
				if (list2.GetColumn(i, &lvColumn))
				{
					df = lvColumn.pszText;
				}

				//获取iItem 行 0-count列的内容
				CString text = list2.GetItemText(iItem, i);
				if (text == "")
				{
					if (i == count - 1)
					{
						sql.Format("%s %s is NULL", sql, df);
					}
					else
					{
						sql.Format("%s %s is NULL AND", sql, df);
					}
				}
				else
				{
					// 规整sql语句
					if (i == count - 1)
					{
						// 最后的条件不需要加and
						sql.Format("%s %s = '%s'", sql, df, text);
					}
					else
					{
						sql.Format("%s %s = '%s' and", sql, df, text);
					}
				}
			}
			if (0!=mysql_query(&superjacob, sql))
			{
				MessageBox("删除失败，请重试");
			}
		}
	}
	// 刷新内容
	OnBnClickedButton5();
}

// list2的双击处理事件，主要是用于更改数据
void superuser::OnNMDblclkList3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	// 获取鼠标位置
	CPoint point;
	GetCursorPos(&point);

	// 获取窗口位置
	CRect rectDlg;
	list2.GetClientRect(rectDlg);//获得list2的大小

	CRect rectDlg2;
	list2.GetWindowRect(rectDlg2);//获得list窗体在大屏幕的位置

	CRect rectDlg3;
	GetWindowRect(rectDlg3);     //获得主窗体的位置
	// 不知道为什么会有-11的偏差
	rectDlg3.top = rectDlg3.top + 11;
	rectDlg3.left = rectDlg3.left + 11;

	int cols = list2.GetHeaderCtrl()->GetItemCount();//列数
											//抹去小数部分，取整
			// list2在窗体中的位置			(鼠标在窗体中点击的位置/每个单元格的宽度)*每个单元格的宽度
	int x = (rectDlg2.left - rectDlg3.left)+((point.x-rectDlg2.left)/(rectDlg.right/cols))* ((rectDlg.right) / cols);
											// -40是为了防止遮盖住表头部分
	int y = (rectDlg2.top - rectDlg3.top)+((point.y-40-rectDlg2.top)/41)*41;


	// 设置输入框的位置和大小                              
	inputbox.SetWindowPos(0, x+2,
		y,
		((rectDlg.right)) / cols,						//输入框的宽
		40,											//输入框的高
		SWP_NOACTIVATE | SWP_SHOWWINDOW);			//激活 | 显示

// 让list1显示于输入框的底下
	list1.ModifyStyle(0, WS_CLIPSIBLINGS);

	// 设为焦点，可以立即输入
	inputbox.SetFocus();
	*pResult = 0;
}

// 查询功能模块
void superuser::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 根据list1的内容，进行查找，更新list2，全为空则查询全部
	CString tablename;
	int Case = xialakuang.GetCurSel();
	switch (Case)
	{
	case 0:tablename = "store"; break;				// 根据下拉框选则要操作的表名
	case 1:tablename = "goods"; break;
	case 2:tablename = "sales_status"; break;
	case 3:tablename = "user"; break;
	default:break;
	};

	static bool first=1;
	int cols = list1.GetHeaderCtrl()->GetItemCount();//列数
	
	CString sql;
	sql.Format("select * from %s where",tablename);

	for (int i = 0; i < cols; i++)
	{
		// 获取到要修改的表头
		LV_COLUMN lvColumn;
		char uin[20]={"\0"};
		lvColumn.pszText = uin;
		lvColumn.cchTextMax = 20;
		lvColumn.mask = LVCF_TEXT;
		
		// df用于存储表头
		CString df;
		//str存储list1内容
		CString str = list1.GetItemText(0, i);

		// 如果list1的内容是空的，则不进行指定字段的整形
		if ((str.Compare("")) && (str.Compare(" ")))
		{
			list1.GetColumn(i, &lvColumn);
			// 判断是否第一次
			if (first)
			{
				df = lvColumn.pszText;
				sql.Format("%s %s = '%s'", sql,df , str);
				first = 0;
			}
			else
			{
				df = lvColumn.pszText;
				sql.Format("%s and %s = '%s'", sql,df, str);
			}
		}
	}
	bool a;
	if (a=mysql_query(&superjacob, sql))
	{
		MessageBox("查询失败，语句结构错误");
		first = 1;
		return;
	}
	first = 1;

	// 存储结果集
	if (mysql_error(&superjacob)=="")
	{
		MessageBox("查询结果为空！");
		return;
	}
	MYSQL_RES* result = mysql_store_result(&superjacob);
	

	// 清空内容
	list2.DeleteAllItems();
	list1.DeleteAllItems();

	
	// 布置内容
	int j = 0;	MYSQL_ROW row;
	while ((row = mysql_fetch_row(result)))  //遇到最后一行，则中止循环
	{
		list2.InsertItem(j, row[0]);
		for (int i = 0; i < cols; i++)
		{
			list2.SetItemText(j, i, row[i]);
		}
		j++;
	}
	mysql_free_result(result);     //释放结果集所占用的内存
	list1.DeleteAllItems();
}






