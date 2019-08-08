
// TestDemoDlg.h : 头文件
//

#pragma once


// CTestDemoDlg 对话框
class CTestDemoDlg : public CDialogEx
{
// 构造
public:
	CTestDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
public:
public:
	static void __stdcall NetCallBack(unsigned int _socket, unsigned int msgType, unsigned char* msg, unsigned int bytes);
	static unsigned int clientid;
	static CTestDemoDlg *pMainPanel;
protected:
	afx_msg LRESULT OnUpdatelogwin(WPARAM wParam, LPARAM lParam);
public:
	CString mLog;
	DWORD dwServerIp;
	DWORD dwPort;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};

//自定义消息

#define WM_UPDATELOGWIN (WM_USER + 0x001)