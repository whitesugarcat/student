
// StuinfoSystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "StuinfoSystem.h"
#include "StuinfoSystemDlg.h"
#include "afxdialogex.h"

#include"InfoDlg.h"


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
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStuinfoSystemDlg 对话框



CStuinfoSystemDlg::CStuinfoSystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUINFOSYSTEM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStuinfoSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CStuinfoSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO2, &CStuinfoSystemDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON1, &CStuinfoSystemDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CStuinfoSystemDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CStuinfoSystemDlg 消息处理程序

BOOL CStuinfoSystemDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);	// 整行选择、网格线
	m_list.InsertColumn(0, _T("姓名"), LVCFMT_LEFT, 100);	// 插入第2列的列名
	m_list.InsertColumn(1, _T("性别"), LVCFMT_LEFT, 100);	// 插入第3列的列名
	m_list.InsertColumn(2, _T("班级"), LVCFMT_LEFT, 100);	// 插入第4列的列名
	m_list.InsertColumn(3, _T("语文"), LVCFMT_LEFT, 100);	// 插入第5列的列名
	m_list.InsertColumn(4, _T("数学"), LVCFMT_LEFT, 100);	// 插入第6列的列名
	m_list.InsertColumn(5, _T("英语"), LVCFMT_LEFT, 100);	// 插入第7列的列名

	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CStuinfoSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CStuinfoSystemDlg::OnPaint()
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
HCURSOR CStuinfoSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStuinfoSystemDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CStuinfoSystemDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	if (SQL.Connect_MySQL())
	{
		Info=SQL.Get_All_Info();
		UpdataList();
	}
	else
	{
		return;
	}
}


void CStuinfoSystemDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	InfoDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		if (SQL.Add_Info(StuInfo(dlg.m_name.GetBuffer(), dlg.m_sex.GetBuffer(), dlg.m_class, dlg.m_score1, dlg.m_score2, dlg.m_score3)))
		{
			MessageBox(TEXT("添加成功！"), TEXT("提示"));
			Info.push_back(StuInfo(dlg.m_name.GetBuffer(), dlg.m_sex.GetBuffer(), dlg.m_class, dlg.m_score1, dlg.m_score2, dlg.m_score3));
			UpdataList();
		}
	}

}

void CStuinfoSystemDlg::UpdataList()
{
	m_list.DeleteAllItems();
	CString str;
	for (int i = 0; i < Info.size(); i++)
	{
		m_list.InsertItem(i, Info[i].m_name.c_str());						// 插入行
		m_list.SetItemText(i, 1, Info[i].m_sex.c_str());
		str.Format(TEXT("%d"), Info[i].m_class_);
		m_list.SetItemText(i, 2, str);

		str.Format(TEXT("%.1lf"), Info[i].m_score1);
		m_list.SetItemText(i, 3, str);				// 设置第4列(性别)
		str.Format(TEXT("%.1lf"), Info[i].m_score2);
		m_list.SetItemText(i, 4, str);			// 设置第5列(语文)
		str.Format(TEXT("%.1lf"), Info[i].m_score3);
		m_list.SetItemText(i, 5, str);				// 设置第6列(数学)
	}
}
