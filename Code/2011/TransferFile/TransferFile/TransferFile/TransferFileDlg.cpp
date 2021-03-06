
// TransferFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TransferFile.h"
#include "TransferFileDlg.h"
#include "afxdialogex.h"
#include "StrTrans.h"
#include "StdioFileEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTransferFileDlg dialog




CTransferFileDlg::CTransferFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTransferFileDlg::IDD, pParent)
	, m_strString(_T("金庸"))
	, m_strCode(_T(""))
	, m_strSelPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTransferFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_STRING, m_strString);
	DDX_Text(pDX, IDC_EDIT_UNICODE, m_strCode);
	DDX_Text(pDX, IDC_EDIT_SEL_PATH, m_strSelPath);
}

BEGIN_MESSAGE_MAP(CTransferFileDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_STR2CODE, &CTransferFileDlg::OnBnClickedButtonStr2code)
	ON_BN_CLICKED(IDC_BUTTON_CODE2STR, &CTransferFileDlg::OnBnClickedButtonCode2str)
	ON_BN_CLICKED(IDC_BUTTON_SEL_PATH, &CTransferFileDlg::OnBnClickedButtonSelPath)
	ON_BN_CLICKED(IDC_BUTTON_TRANS_PATH, &CTransferFileDlg::OnBnClickedButtonTransPath)
	ON_BN_CLICKED(IDC_BUTTON_TXT_FILE_ENTER, &CTransferFileDlg::OnBnClickedButtonTxtFileEnter)
	ON_BN_CLICKED(IDC_BUTTON_TXT_FILE_REMOVE_ENTER, &CTransferFileDlg::OnBnClickedButtonTxtFileRemoveEnter)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_SRT, &CTransferFileDlg::OnBnClickedButtonModifySrt)
END_MESSAGE_MAP()


// CTransferFileDlg message handlers

BOOL CTransferFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	m_lstSplitSign.push_back(_T(","));
	m_lstSplitSign.push_back(_T("."));
	m_lstSplitSign.push_back(_T("?"));
	m_lstSplitSign.push_back(_T("-"));
	m_lstSplitSign.push_back(_T(" — "));
	m_lstSplitSign.push_back(_T(":"));
	m_lstSplitSign.push_back(_T(";"));
	m_lstSplitSign.push_back(_T("–"));
	
	
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTransferFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTransferFileDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTransferFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTransferFileDlg::OnBnClickedButtonStr2code()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_strString.IsEmpty())
	{
		AfxMessageBox(_T("请输入字符串！"));
		return;
	}
	CStrTrans Trans;
	m_strCode = Trans.TransToCode(m_strString);
	UpdateData(FALSE);
}


void CTransferFileDlg::OnBnClickedButtonCode2str()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_strCode.IsEmpty())
	{
		AfxMessageBox(_T("请输入字符串！"));
		return;
	}
	CStrTrans Trans;
	m_strString = Trans.TransToString(m_strCode);
	UpdateData(FALSE);
}


void CTransferFileDlg::OnBnClickedButtonSelPath()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog dlg(TRUE);
	if(dlg.DoModal() != IDOK)
	{
		return;
	}
	m_strSelPath = dlg.GetPathName();
	m_strSelPath = m_strSelPath.Left(m_strSelPath.ReverseFind(_T('\\')) + 1);
	SetCurrentDirectory(_T("C:\\"));
	UpdateData(FALSE);
}


void CTransferFileDlg::OnBnClickedButtonTransPath()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_strSelPath.IsEmpty())
	{
		AfxMessageBox(_T("请选择一个文件夹！"));
		return;
	}
	std::list<std::pair<CString,CString>> lstTransFileAndPath;
	TransFileandPath(m_strSelPath,lstTransFileAndPath);
	for(auto itr = lstTransFileAndPath.rbegin();itr != lstTransFileAndPath.rend();++itr)
	{
		CString str;
		str.Format(_T("%s--->%s\n"),(*itr).first,(*itr).second);
		if(!MoveFile((*itr).first,(*itr).second))
		{
			DWORD dw = GetLastError();
			//ASSERT(FALSE);
		}
	}
	AfxMessageBox(_T("转换成功"));
	
}

void CTransferFileDlg::TransFileandPath(CString _strPath,std::list<std::pair<CString,CString>> &_lstTransFileAndPath)
{
	CString strPath = _strPath;
	if(strPath.Right(1) != _T("\\"))
	{
		strPath += _T("\\");
	}
	strPath += _T("*.*");
	BOOL bChangeDir = FALSE;
	CFileFind finder;
	BOOL bWorking = finder.FindFile(strPath);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
			continue;
		else if (finder.IsDirectory())
		{
			CString sTemp = finder.GetFilePath();
			CStrTrans Trans;
			CString strAfertTrans = Trans.TransToString(sTemp);
			if(strAfertTrans.CompareNoCase(sTemp) != 0)
			{
				//修改文件夹名字
				//_lstTransFileAndPath.push_back(std::make_pair(sTemp,strAfertTrans));
				finder.Close();
				MoveFile(sTemp,strAfertTrans);
				bChangeDir = TRUE;
				break;
			}
			TransFileandPath(sTemp,_lstTransFileAndPath);
		}
		else
		{
			CString sTemp = finder.GetFilePath();
			CStrTrans Trans;
			CString strAfertTrans = Trans.TransToString(sTemp);
			if(strAfertTrans.CompareNoCase(sTemp) != 0)
			{
				//修改文件名字
				//_lstTransFileAndPath.push_back(std::make_pair(sTemp,strAfertTrans));
				finder.Close();
				MoveFile(sTemp,strAfertTrans);
				bChangeDir = TRUE;
				break;
			}
		}
	}
	
	if(bChangeDir)
	{
		TransFileandPath(_strPath,_lstTransFileAndPath);
	}
	else
	{
		finder.Close();
	}
}

void CTransferFileDlg::OnBnClickedButtonTxtFileEnter()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE);
	if(dlg.DoModal() != IDOK)
	{
		return;
	}
	CString strSrcFileName = dlg.GetPathName();
	CString strDestFileName = strSrcFileName + _T("1");
	try
	{
		CStdioFileEx fileSrc(strSrcFileName,CFile::modeRead);
		CStdioFileEx fileDest(strDestFileName,CFile::modeCreate|CFile::modeWrite);
		BOOL bHas = FALSE;
		do 
		{
			CString strTxt;
			bHas = fileSrc.ReadString(strTxt);
			strTxt.TrimLeft();
			strTxt.TrimRight();
			std::list<CString> lstSplitStr;
			SplitStringBySign(strTxt,lstSplitStr);
			for(auto itr = lstSplitStr.begin();itr !=lstSplitStr.end();++itr)
			{
				fileDest.WriteString(*itr);
				fileDest.WriteString(_T("\r\n"));
			}
		} while (bHas);

		fileSrc.Close();
		fileDest.Close();
	}
	catch (CFileException* /*e*/)
	{
		CString strMsg;
		strMsg.Format(_T("读取文件%s发生错误！"),strSrcFileName);
		AfxMessageBox(strMsg);

		return ;
	}
	catch (...)
	{
		CString strMsg;
		strMsg.Format(_T("读取文件%s发生错误！"),strSrcFileName);
		AfxMessageBox(strMsg);

		return ;
	}
	AfxMessageBox(_T("转换成功！"));
}

void CTransferFileDlg::SplitStringBySign(CString _str,std::list<CString> &_lstSplitString)
{
	int iFind = -1;
	BOOL bFind = FALSE;
	do 
	{
		bFind = FALSE;
		iFind = _str.GetLength();
		for(auto itr = m_lstSplitSign.begin();itr != m_lstSplitSign.end();++itr)
		{
			int iTempFind = _str.Find(*itr);
			if(iTempFind != -1)
			{
				if(iTempFind < iFind)
				{
					iFind = iTempFind;
				}
				bFind = TRUE;
			}
			
		}
		if(bFind )
		{
			CString strLeft = _str.Left(iFind+1);
			_lstSplitString.push_back(strLeft);
			_str = _str.Right(_str.GetLength() - iFind -1 );
		}
	} while (bFind);
	
}

void CTransferFileDlg::OnBnClickedButtonTxtFileRemoveEnter()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE);
	if(dlg.DoModal() != IDOK)
	{
		return;
	}
	CString strSrcFileName = dlg.GetPathName();
	CString strContent;
	CString strDestFileName = strSrcFileName + _T(".txt");
	try
	{
		CStdioFileEx fileSrc(strSrcFileName,CFile::modeRead);
		CStdioFileEx fileDest(strDestFileName,CFile::modeCreate|CFile::modeWrite);
		BOOL bHas = FALSE;
		do 
		{
			CString strTxt;
			bHas = fileSrc.ReadString(strTxt);
			CString strTmpTxt = strTxt;
			strTmpTxt.TrimLeft();
			strTmpTxt.TrimRight();
			if(!strTxt.IsEmpty())
			{
				strContent += strTxt;
			}
		} while (bHas);
		std::list<CString> lstStr;
		SplitStringBySign(strContent,lstStr);
		CString strWrite;
		for(auto itr = lstStr.begin();itr != lstStr.end();++itr)
		{
			CString strTemp =(*itr);
			strTemp.TrimLeft();
			strTemp.TrimRight();
			if(strTemp.IsEmpty())
			{
				continue;
			}
			if((*itr).GetLength() > 40)
			{
				if(!strWrite.IsEmpty())
				{
					fileDest.WriteString(strWrite);
					fileDest.WriteString(_T("\r\n"));

				}
				strWrite = _T("");
				fileDest.WriteString(*itr);
				fileDest.WriteString(_T("\r\n"));

			}
			else
			{
				strWrite += *itr;
				if(strWrite.GetLength() > 40)
				{
					fileDest.WriteString(strWrite);
					fileDest.WriteString(_T("\r\n"));
					strWrite = _T("");
				}
			}
			
			
		}
		
		fileSrc.Close();
		fileDest.Close();
	}
	catch (CFileException* /*e*/)
	{
		CString strMsg;
		strMsg.Format(_T("读取文件%s发生错误！"),strSrcFileName);
		AfxMessageBox(strMsg);

		return ;
	}
	catch (...)
	{
		CString strMsg;
		strMsg.Format(_T("读取文件%s发生错误！"),strSrcFileName);
		AfxMessageBox(strMsg);

		return ;
	}
	AfxMessageBox(_T("转换成功！"));

}


void CTransferFileDlg::OnBnClickedButtonModifySrt()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE);
	if(dlg.DoModal() != IDOK)
	{
		return;
	}
	CString strSrcFileName = dlg.GetPathName();
	CString strContent;
	CString strDestFileName = strSrcFileName + _T(".txt");
	CString strLastTime;
	strLastTime = _T("00:00:00,000");
	try
	{
		CStdioFileEx fileSrc(strSrcFileName,CFile::modeRead);
		CStdioFileEx fileDest(strDestFileName,CFile::modeCreate|CFile::modeWrite);
		BOOL bHas = FALSE;
		do 
		{
			CString strTxt;
			bHas = fileSrc.ReadString(strTxt);
			int iFind = strTxt.Find(_T("00:00:00,000 --> "));
			if( iFind != -1)
			{ 
				strTxt.Replace(_T("00:00:00,000"),strLastTime);
				strLastTime = strTxt.Right(strTxt.GetLength() - iFind - 17);
			}
			fileDest.WriteString(strTxt);
			fileDest.WriteString(_T("\r\n"));
		} while (bHas);
		
		

		fileSrc.Close();
		fileDest.Close();
	}
	catch (CFileException* /*e*/)
	{
		CString strMsg;
		strMsg.Format(_T("读取文件%s发生错误！"),strSrcFileName);
		AfxMessageBox(strMsg);

		return ;
	}
	catch (...)
	{
		CString strMsg;
		strMsg.Format(_T("读取文件%s发生错误！"),strSrcFileName);
		AfxMessageBox(strMsg);

		return ;
	}
	AfxMessageBox(_T("转换成功！"));
}
