
// wokerDlg.h : 头文件
//

#pragma once


// CwokerDlg 对话框
class CwokerDlg : public CDialogEx
{
	struct SInfo 
	{
		int nNumber;
		TCHAR sName[20];//不能使用CString 不能直接传输 不能使用char char是单字符的
		float FSala;
		COleDateTime dDate;
	};

	BOOL m_bModify;

// 构造
public:
	CwokerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WOKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedEdit();
	afx_msg void OnBnClickedSave();
	// 检查号码是否存在
	BOOL CheckNumber(LPCTSTR szNumber);
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedCancel();
};
