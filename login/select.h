#pragma once
#include<WinSock2.h>
#include<iostream>
#include<Windows.h>
#include"mysql.h"
#pragma comment(lib,"libmysql.lib")
#pragma comment(lib,"mysqlclient.lib")
#pragma comment(lib,"mysqlservices.lib")
using namespace std;
//���ԡ�>���ԡ�>����   PATH=D:\Desktop\login\mysql-8.0.28-linux-glibc2.12-x86_64\bin;
//����->c/c++��>���桪>���Ӱ���Ŀ¼��mysql�µ�include��
//����->��������>���桪>���������mysql�µ�lib��




MYSQL mysql,commonuser;										//һ�����ݿ�ṹ��
MYSQL_RES* res;										//һ��������ṹ��
MYSQL_ROW row;										//char** ��ά���飬���һ��ѯ��¼



// �����û��ĵ�¼
int superuser_login(CString username,CString password)
{
	//��ʼ��
	mysql_init(&mysql);										//��ʼ�����ݿ�����������ӷ����
															//�����ΪNULL,���Զ��ᴴ��һ�����󣬸ö���ֻ���ͷ�һ��
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");	//���ñ��뷽ʽ
	//�������ݿ�
	/*��Cstring ת��Ϊconst char* �ٵ�¼*/
	string s((CT2A)username);
	string s1((CT2A)password);
	const char* k = s.c_str();
	const char* k1 = s1.c_str();

	if (mysql_real_connect(&mysql, "172.21.201.20",k, k1, "SellGoodsSystem", 3306, NULL, 0) == NULL)
	{
		MessageBox(0,TEXT("��¼ʧ��!"), TEXT("��ʾ"), 0);
		return 1;
	}
	else
	{
		MessageBox(0, TEXT("��¼�ɹ�"), TEXT("��ʾ"), 0);
		MessageBox(NULL, TEXT("��������ԱȨ�޾޴�\n����ֱ�Ӷ����ݿ������ɾ�Ĳ�Ȳ���\n���С��"), TEXT("����"), 1);
		return 0;
	}
	/*
	//��ѯ����
	mysql_query(&mysql, "select * from user");


	//��ȡ�����
	res = mysql_store_result(&mysql);

	//��ʾ����
	//��ROW��ֵ���ж�ROW�Ƿ�Ϊ�գ���Ϊ�վʹ�ӡ���ݡ�
	int num = mysql_num_fields(res);        //�������������ŵ�num��

	CString c_str;
	while ((row = mysql_fetch_row(res)))  //�������һ�У�����ֹѭ��
	{
		for (int i = 0; i < num; i++)         //����forѭ����������е�ÿһ��
		{
			c_str = row[i];
			MessageBox(0,c_str, TEXT("��Ϣ"), 0);
		}
	}

	//�ͷŽ����
	mysql_free_result(res);
	//�ر����ݿ�
	mysql_close(&mysql);
	//ͣ���ȴ�
	system("pause");
	*/
	//���ŵ��ó�����Ա����
}

//�����û��ģ���ɾ�Ĳ�


// ��ͨ�û��ĵ�¼
int common_login(CString username,CString password)
{
	//��ʼ��
	mysql_init(&commonuser);										//��ʼ�����ݿ�����������ӷ����
															//�����ΪNULL,���Զ��ᴴ��һ�����󣬸ö���ֻ���ͷ�һ��
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");	//���ñ��뷽ʽ
	//�������ݿ�


	//����ֱ�Ӹĳ�����ֻ�ɲ�ѯ��Ȩ��
	if (mysql_real_connect(&mysql, "172.21.201.20","superjacob", "1234", "SellGoodsSystem", 3306, NULL, 0) == NULL)
	{
		MessageBox(0, TEXT("��¼ʧ��\n������������!"), TEXT("��ʾ"), 0);
		return 1;
	}
	else
	{
		//select ��ѯ�Ƿ���user����
		string select = "select password from user where username='jacob'";
		mysql_query(&commonuser,select.c_str());


		//��ȡ�����
		res = mysql_store_result(&mysql);
		
		return 0;
	}
}