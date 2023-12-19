#include "pch.h"
#include "SQLInterface.h"

bool SQLInterface::Connect_MySQL()
{
	mysql_init(&mysqlCon);  //��ʼ��
	//mysqlCon ���ݿ�ṹ localhost ������ root �û��� "" ����Ϊ�� mytest ���ݿ� 3306 �˿�
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "LJZ2004311015", "stuinfo", 3306, NULL, 0))
	{
		AfxMessageBox(_T("�������ݿ�ʧ��!"));
		return FALSE;
	}
	else
	{
		AfxMessageBox(_T("�ɹ��������ݿ�!"));
		// �����ַ����� ʹ����֧�����ġ�
		mysql_query(&mysqlCon, "SET NAMES 'GB2312'");//��������ݿ��ж�ȡ���ݺ���������ʾ������ 

	}
	return TRUE;

}

vector<StuInfo> SQLInterface::Get_All_Info()
{
	vector<StuInfo> Info;

	// C��������ַ���
	snprintf(sql, SQL_MAX, "SELECT * FROM info1");
	//��ѯ����
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	//�жϲ�ѯ���
	if (ret) {
		AfxMessageBox(_T("��ѯʧ��!"));
		return Info;
	}
	// ��ȡ�����
	res = mysql_store_result(&mysqlCon);
	// ��ȡ��ѯ����һ������
	// ��row��ֵ���ж�row�Ƿ�Ϊ�գ���Ϊ�վʹ�ӡ���ݡ�
	while (row = mysql_fetch_row(res)) {
		StuInfo stuinfo= StuInfo(row[0],row[1],atoi(row[2]),stod(row[3]), stod(row[4]), stod(row[5]));
		Info.push_back(stuinfo);
	}
	// �ͷŽ����
	mysql_free_result(res);

	return Info;
}

bool SQLInterface::Add_Info(StuInfo Info)
{
	// C�����ַ������
	snprintf(sql, SQL_MAX, "INSERT INTO info1 VALUES('%s','%s',%d,%lf,%lf,%lf);",
		Info.m_name.c_str(), Info.m_sex.c_str(), Info.m_class_, Info.m_score1, Info.m_score2, Info.m_score3);
	//��ѯ����
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	//�жϲ�ѯ���
	if (ret) {
		AfxMessageBox(_T("���ʧ��!"));
		return false;
	}
	return true;
}
