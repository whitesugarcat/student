#pragma once

#include"StuInfo.h"

#define SQL_MAX 256		// sql����ַ��������ֵ


class SQLInterface
{
public:
	MYSQL_RES* res;  //result
	MYSQL_ROW row;
	MYSQL mysqlCon;  //connect
	char sql[SQL_MAX];	// SQL���

	bool Connect_MySQL();  //�������ݿ�
	vector<StuInfo> Get_All_Info();   //��ȡȫ����Ϣ
	bool Add_Info(StuInfo Info);   //���ѧ����Ϣ
};

