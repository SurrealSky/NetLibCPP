
// TestDemoDlg.h : ͷ�ļ�
//

#pragma once


// CTestDemoDlg �Ի���
class CTestDemoDlg : public CDialogEx
{
// ����
public:
	CTestDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

//�Զ�����Ϣ

#define WM_UPDATELOGWIN (WM_USER + 0x001)