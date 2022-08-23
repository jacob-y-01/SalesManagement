#pragma once
#include<WinSock2.h>
#include<iostream>
#include<Windows.h>
#include"mysql.h"
#pragma comment(lib,"libmysql.lib")
#pragma comment(lib,"mysqlclient.lib")
#pragma comment(lib,"mysqlservices.lib")
using namespace std;
//属性—>调试—>环境   PATH=D:\Desktop\login\mysql-8.0.28-linux-glibc2.12-x86_64\bin;
//属性->c/c++—>常规—>附加包含目录（mysql下的include）
//属性->连接器—>常规—>附加依赖项（mysql下的lib）




MYSQL mysql,commonuser;										//一个数据库结构体
MYSQL_RES* res;										//一个结果集结构体
MYSQL_ROW row;										//char** 二维数组，存放一查询记录



// 超级用户的登录
int superuser_login(CString username,CString password)
{
	//初始化
	mysql_init(&mysql);										//初始化数据库对象，用于连接服务端
															//如参数为NULL,则自动会创建一个对象，该对象只能释放一次
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");	//设置编码方式
	//连接数据库
	/*由Cstring 转换为const char* 再登录*/
	string s((CT2A)username);
	string s1((CT2A)password);
	const char* k = s.c_str();
	const char* k1 = s1.c_str();

	if (mysql_real_connect(&mysql, "172.21.201.20",k, k1, "SellGoodsSystem", 3306, NULL, 0) == NULL)
	{
		MessageBox(0,TEXT("登录失败!"), TEXT("提示"), 0);
		return 1;
	}
	else
	{
		MessageBox(0, TEXT("登录成功"), TEXT("提示"), 0);
		MessageBox(NULL, TEXT("超级管理员权限巨大\n可以直接对数据库进行增删改查等操作\n务必小心"), TEXT("警告"), 1);
		return 0;
	}
	/*
	//查询数据
	mysql_query(&mysql, "select * from user");


	//获取结果集
	res = mysql_store_result(&mysql);

	//显示数据
	//给ROW赋值，判断ROW是否为空，不为空就打印数据。
	int num = mysql_num_fields(res);        //将结果集列数存放到num中

	CString c_str;
	while ((row = mysql_fetch_row(res)))  //遇到最后一行，则中止循环
	{
		for (int i = 0; i < num; i++)         //利用for循环，输出该行的每一列
		{
			c_str = row[i];
			MessageBox(0,c_str, TEXT("消息"), 0);
		}
	}

	//释放结果集
	mysql_free_result(res);
	//关闭数据库
	mysql_close(&mysql);
	//停留等待
	system("pause");
	*/
	//接着调用出管理员窗口
}

//超级用户的：增删改查


// 普通用户的登录
int common_login(CString username,CString password)
{
	//初始化
	mysql_init(&commonuser);										//初始化数据库对象，用于连接服务端
															//如参数为NULL,则自动会创建一个对象，该对象只能释放一次
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");	//设置编码方式
	//连接数据库


	//这里直接改成限制只可查询的权限
	if (mysql_real_connect(&mysql, "172.21.201.20","superjacob", "1234", "SellGoodsSystem", 3306, NULL, 0) == NULL)
	{
		MessageBox(0, TEXT("登录失败\n请检查网络设置!"), TEXT("提示"), 0);
		return 1;
	}
	else
	{
		//select 查询是否在user表中
		string select = "select password from user where username='jacob'";
		mysql_query(&commonuser,select.c_str());


		//获取结果集
		res = mysql_store_result(&mysql);
		
		return 0;
	}
}