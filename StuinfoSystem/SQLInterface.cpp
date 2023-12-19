#include "pch.h"
#include "SQLInterface.h"

bool SQLInterface::Connect_MySQL()
{
	mysql_init(&mysqlCon);  //初始化
	//mysqlCon 数据库结构 localhost 主机名 root 用户名 "" 密码为空 mytest 数据库 3306 端口
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "LJZ2004311015", "stuinfo", 3306, NULL, 0))
	{
		AfxMessageBox(_T("访问数据库失败!"));
		return FALSE;
	}
	else
	{
		AfxMessageBox(_T("成功连接数据库!"));
		// 设置字符集， 使程序支持中文。
		mysql_query(&mysqlCon, "SET NAMES 'GB2312'");//解决从数据库中读取数据后汉字乱码显示的问题 

	}
	return TRUE;

}

vector<StuInfo> SQLInterface::Get_All_Info()
{
	vector<StuInfo> Info;

	// C语言组合字符串
	snprintf(sql, SQL_MAX, "SELECT * FROM info1");
	//查询数据
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	//判断查询结果
	if (ret) {
		AfxMessageBox(_T("查询失败!"));
		return Info;
	}
	// 获取结果集
	res = mysql_store_result(&mysqlCon);
	// 获取查询到的一行数据
	// 给row赋值，判断row是否为空，不为空就打印数据。
	while (row = mysql_fetch_row(res)) {
		StuInfo stuinfo= StuInfo(row[0],row[1],atoi(row[2]),stod(row[3]), stod(row[4]), stod(row[5]));
		Info.push_back(stuinfo);
	}
	// 释放结果集
	mysql_free_result(res);

	return Info;
}

bool SQLInterface::Add_Info(StuInfo Info)
{
	// C语言字符串组合
	snprintf(sql, SQL_MAX, "INSERT INTO info1 VALUES('%s','%s',%d,%lf,%lf,%lf);",
		Info.m_name.c_str(), Info.m_sex.c_str(), Info.m_class_, Info.m_score1, Info.m_score2, Info.m_score3);
	//查询数据
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	//判断查询结果
	if (ret) {
		AfxMessageBox(_T("添加失败!"));
		return false;
	}
	return true;
}
