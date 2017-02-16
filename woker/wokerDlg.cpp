
// wokerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "woker.h"
#include "wokerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CwokerDlg 对话框



CwokerDlg::CwokerDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CwokerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CwokerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CwokerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, &CwokerDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELETE, &CwokerDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_EDIT, &CwokerDlg::OnBnClickedEdit)
	ON_BN_CLICKED(IDC_SAVE, &CwokerDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_LOAD, &CwokerDlg::OnBnClickedLoad)
	ON_BN_CLICKED(IDCANCEL, &CwokerDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CwokerDlg 消息处理程序

BOOL CwokerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标



	CListCtrl *plist = (CListCtrl*)GetDlgItem(IDC_LIST);

	plist->InsertColumn(0, _T("工号"), LVCFMT_CENTER, 100);
	plist->InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 100);
	plist->InsertColumn(2, _T("工资"), LVCFMT_CENTER, 100);
	plist->InsertColumn(3, _T("日期"), LVCFMT_CENTER, 100);

	plist->SetBkColor(RGB(205, 226, 252));

	plist->SetTextColor(RGB(255, 0, 255));
	plist->SetTextBkColor(RGB(255, 255, 0));



	plist->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	OnBnClickedLoad();

	m_bModify = FALSE;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CwokerDlg::OnPaint()
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
HCURSOR CwokerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 检查号码是否存在
BOOL CwokerDlg::CheckNumber(LPCTSTR szNumber)
{
	CListCtrl *plist = (CListCtrl*)GetDlgItem(IDC_LIST);
	int i = 0, nCount = plist->GetItemCount();

	while (i < nCount)
	{

		if (plist->GetItemText(i, 0) == szNumber)
		{
			return FALSE;
		}
		i++;
	}

	return TRUE;
}

void CwokerDlg::OnBnClickedAdd()
{
	CListCtrl *plist = (CListCtrl*)GetDlgItem(IDC_LIST);
	CString str;

	GetDlgItemText(IDC_Num, str);



	if (str.IsEmpty())
	{
		AfxMessageBox(_T("号码不能为空!"));
		return;
	}

	if (!CheckNumber(str))
	{
		AfxMessageBox(_T("已经存在不能换个试下吧"));
		this->SetFocus();
		return;
	}

	GetDlgItemText(IDC_Num, str);
	plist->InsertItem(0, str);

	GetDlgItemText(IDC_NAME, str);
	plist->SetItemText(0, 1, str);

	GetDlgItemText(IDC_SALA, str);
	plist->SetItemText(0, 2, str);

	GetDlgItemText(IDC_DATE, str);
	plist->SetItemText(0, 3, str);

	m_bModify = TRUE;
}


void CwokerDlg::OnBnClickedDelete()
{
	CListCtrl *plist = (CListCtrl*)GetDlgItem(IDC_LIST);



	if (plist->GetItemCount() <= 0)
	{
		AfxMessageBox(_T("请先新增!"));
		return;
	}
	if (!plist->GetSelectedCount())
	{
		AfxMessageBox(_T("请选中行!"));
		return;
	}

	POSITION posit = plist->GetFirstSelectedItemPosition();


	while (posit)
	{



		int nSel = plist->GetNextSelectedItem(posit);

		if (nSel!=0)
	{
			nSel = nSel- 1;
	}

		CString str = plist->GetItemText(nSel, 0);
		if (IDNO == AfxMessageBox(_T("确定删除编号为:") + str + _T("的信息吗 ？"), MB_YESNO))
		 
			continue;
		 



		//int nSel = plist->GetSelectionMark();

		m_bModify = TRUE;
		 
			plist->DeleteItem(nSel);
		 
	}

	

}


void CwokerDlg::OnBnClickedEdit()
{
	CListCtrl* plist = (CListCtrl*)GetDlgItem(IDC_LIST);
	if (!plist->GetSelectedCount())
	{
		AfxMessageBox(_T("请选中一行再修改"));
		return;
	}


	POSITION posit = plist->GetFirstSelectedItemPosition();
 

	while (posit)
	{

		int nSel = plist->GetNextSelectedItem(posit);
		CString str = plist->GetItemText(nSel, 0);
		if (IDNO == AfxMessageBox(_T("确定修改编号为:") + str + _T("的信息吗 ？"), MB_YESNO))
		{
			return;
		}
		GetDlgItemText(IDC_NAME, str);
		plist->SetItemText(nSel, 1, str);

		GetDlgItemText(IDC_SALA, str);
		plist->SetItemText(nSel, 2, str);

		GetDlgItemText(IDC_DATE, str);
		plist->SetItemText(nSel, 3, str);

	}


	m_bModify = TRUE;
}


void CwokerDlg::OnBnClickedSave()
{
	CFile cfile;
	if (!cfile.Open(_T("./Worker.dat"), CFile::modeCreate | CFile::modeReadWrite))//创建文件
	{
		AfxMessageBox(_T("保存失败"));
		return;
	}
	  SInfo info;
	CListCtrl* plist = (CListCtrl*)GetDlgItem(IDC_LIST);
	int i=0,nCount= plist->GetItemCount();
	while (i<nCount)
	{
		info.nNumber = _tstoi(plist->GetItemText(i, 0));
		_tcscpy(info.sName, plist->GetItemText(i, 1));
		info.FSala =(float) _tstof(plist->GetItemText(i, 2));
		info.dDate.ParseDateTime(   plist->GetItemText(i, 3),VAR_DATEVALUEONLY);
		cfile.Write(&info, sizeof(info));
		++i;
	}
	
	//cfile.Write(_T("xxxtest"), sizeof(_T("xxxtest")));
	cfile.Close();
	//AfxMessageBox(_T("保存成功"));
}




void CwokerDlg::OnBnClickedLoad()
{
	CFile cfile;
	if (!cfile.Open(_T("./Worker.dat"),  CFile::modeRead))//打开文件
	{
		AfxMessageBox(_T("打开失败"));
		return;
	}


	CListCtrl *plist = (CListCtrl*)GetDlgItem(IDC_LIST);



	SInfo info;
	int i = 0;
	CString str;
	while (cfile.Read(&info,sizeof(info))==sizeof(info))
	{
		str.Format(_T("%d"), info.nNumber);
			plist->InsertItem(i, str);

			plist->SetItemText(i, 1, info.sName);
			str.Format(_T("%0.2f"), info.FSala);
			plist->SetItemText(i, 2, str);


			str = info.dDate.Format(_T("%Y年%m月%d日"));
			plist->SetItemText(i,3, str);
		++i;
	}



}


void CwokerDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码

	if (m_bModify)
	{
		if (IDYES == AfxMessageBox(_T("是否保存呢?"), MB_YESNO | MB_ICONQUESTION))
		{
			OnBnClickedSave();
		}
	}
	CDialogEx::OnCancel();
}
