
// wokerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "woker.h"
#include "wokerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CwokerDlg �Ի���



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


// CwokerDlg ��Ϣ�������

BOOL CwokerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��



	CListCtrl *plist = (CListCtrl*)GetDlgItem(IDC_LIST);

	plist->InsertColumn(0, _T("����"), LVCFMT_CENTER, 100);
	plist->InsertColumn(1, _T("����"), LVCFMT_CENTER, 100);
	plist->InsertColumn(2, _T("����"), LVCFMT_CENTER, 100);
	plist->InsertColumn(3, _T("����"), LVCFMT_CENTER, 100);

	plist->SetBkColor(RGB(205, 226, 252));

	plist->SetTextColor(RGB(255, 0, 255));
	plist->SetTextBkColor(RGB(255, 255, 0));



	plist->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	OnBnClickedLoad();

	m_bModify = FALSE;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CwokerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CwokerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// �������Ƿ����
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
		AfxMessageBox(_T("���벻��Ϊ��!"));
		return;
	}

	if (!CheckNumber(str))
	{
		AfxMessageBox(_T("�Ѿ����ڲ��ܻ������°�"));
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
		AfxMessageBox(_T("��������!"));
		return;
	}
	if (!plist->GetSelectedCount())
	{
		AfxMessageBox(_T("��ѡ����!"));
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
		if (IDNO == AfxMessageBox(_T("ȷ��ɾ�����Ϊ:") + str + _T("����Ϣ�� ��"), MB_YESNO))
		 
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
		AfxMessageBox(_T("��ѡ��һ�����޸�"));
		return;
	}


	POSITION posit = plist->GetFirstSelectedItemPosition();
 

	while (posit)
	{

		int nSel = plist->GetNextSelectedItem(posit);
		CString str = plist->GetItemText(nSel, 0);
		if (IDNO == AfxMessageBox(_T("ȷ���޸ı��Ϊ:") + str + _T("����Ϣ�� ��"), MB_YESNO))
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
	if (!cfile.Open(_T("./Worker.dat"), CFile::modeCreate | CFile::modeReadWrite))//�����ļ�
	{
		AfxMessageBox(_T("����ʧ��"));
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
	//AfxMessageBox(_T("����ɹ�"));
}




void CwokerDlg::OnBnClickedLoad()
{
	CFile cfile;
	if (!cfile.Open(_T("./Worker.dat"),  CFile::modeRead))//���ļ�
	{
		AfxMessageBox(_T("��ʧ��"));
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


			str = info.dDate.Format(_T("%Y��%m��%d��"));
			plist->SetItemText(i,3, str);
		++i;
	}



}


void CwokerDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (m_bModify)
	{
		if (IDYES == AfxMessageBox(_T("�Ƿ񱣴���?"), MB_YESNO | MB_ICONQUESTION))
		{
			OnBnClickedSave();
		}
	}
	CDialogEx::OnCancel();
}
