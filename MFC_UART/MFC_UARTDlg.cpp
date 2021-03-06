
// MFC_UARTDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFC_UART.h"
#include "MFC_UARTDlg.h"
#include "afxdialogex.h"
#include "uart_control.h"
#include "dialog_data_control.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//定义串口
UART	uart_port;
DIALOG_DATA dialog_data;

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


// CMFCUARTDlg 对话框



CMFCUARTDlg::CMFCUARTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MFC_UART_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCUARTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COM_PORT, ctl_combox_portname);
	DDX_Control(pDX, IDC_COM_BAUD, ctl_combox_rate);
}

BEGIN_MESSAGE_MAP(CMFCUARTDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BT_UART_OPEN, &CMFCUARTDlg::OnBnClickedBtUartOpen)
	ON_BN_CLICKED(IDC_BT_UART_CLOSE, &CMFCUARTDlg::OnBnClickedBtUartClose)
	ON_CBN_SELCHANGE(IDC_COM_PORT, &CMFCUARTDlg::OnCbnSelchangeComPort)
END_MESSAGE_MAP()


// CMFCUARTDlg 消息处理程序

BOOL CMFCUARTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	CComboBox	*pcombox;
	pcombox	=	(CComboBox*)GetDlgItem( IDC_COM_PORT);
	dialog_data.InitPort(pcombox);
	pcombox = (CComboBox*)GetDlgItem(IDC_COM_BAUD);
	dialog_data.InitBaud(pcombox);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCUARTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCUARTDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCUARTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCUARTDlg::OnBnClickedBtUartOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CString 	portname,rate;
	int ratedata;
	ctl_combox_portname.GetLBText(ctl_combox_portname.GetCurSel(), portname);
	ctl_combox_rate.GetLBText(ctl_combox_rate.GetCurSel(), rate);
	ratedata	=	_wtoi(rate.GetBuffer(0));
	if (uart_port.InitComm(portname, ratedata)) {
		MessageBox(TEXT("success"), TEXT("remn"), MB_OK);

	}
	else {

		MessageBox(TEXT("error"), TEXT("remn"), MB_OK);
	}

}


void CMFCUARTDlg::OnBnClickedBtUartClose()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCUARTDlg::OnCbnSelchangeComPort()
{
	// TODO: 在此添加控件通知处理程序代码
}
