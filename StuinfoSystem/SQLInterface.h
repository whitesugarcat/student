#pragma once

#include"StuInfo.h"

#define SQL_MAX 256		// sql语句字符数组最大值


class SQLInterface
{
public:
	MYSQL_RES* res;  //result
	MYSQL_ROW row;
	MYSQL mysqlCon;  //connect
	char sql[SQL_MAX];	// SQL语句

	bool Connect_MySQL();  //连接数据库
	vector<StuInfo> Get_All_Info();   //获取全部信息
	bool Add_Info(StuInfo Info);   //添加学生信息
};

