
// wokerDlg.h : ͷ�ļ�
//

#pragma once


// CwokerDlg �Ի���
class CwokerDlg : public CDialogEx
{
	struct SInfo 
	{
		int nNumber;
		TCHAR sName[20];//����ʹ��CString ����ֱ�Ӵ��� ����ʹ��char char�ǵ��ַ���
		float FSala;
		COleDateTime dDate;
	};

	BOOL m_bModify;

// ����
public:
	CwokerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WOKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedEdit();
	afx_msg void OnBnClickedSave();
	// �������Ƿ����
	BOOL CheckNumber(LPCTSTR szNumber);
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedCancel();
};
