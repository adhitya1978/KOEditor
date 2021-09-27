#include "stdafx.h"
#include "MyKODlg.h"
#include "MyKO.h"
#include "afxdialogex.h"
//#include "ini.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};


CAboutDlg::CAboutDlg()
	: CDialogEx(IDD_ABOUTBOX)

{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE  unless you set the focus to a control
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


MyKODlg::MyKODlg(CWnd * pParent) : CDialogEx(IDD_MAIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	theApp.m_pSkin->ApplySkin();
}

void MyKODlg::SetupApplication()
{
	TCHAR _devicename[128];
	TCHAR A[32]; int  k = 0;

	TCHAR gLimitation[3][256] = {
		ENUM_TO_STRING(Minimum),
		ENUM_TO_STRING(Medium),
		ENUM_TO_STRING(Maximum)
	};

	TCHAR gLeveling[2][128] = {
		ENUM_TO_STRING(LOW),
		ENUM_TO_STRING(HIGH)
	};

	TCHAR gSizing[2][128] = {
		ENUM_TO_STRING(SMALL),
		ENUM_TO_STRING(BIG)
	};

	TCHAR gVisibility[2][128] = {
		ENUM_TO_STRING(SHOW),
		ENUM_TO_STRING(HIDE),
	};

	TCHAR gOpacity[2][128] = {
		ENUM_TO_STRING(NORMAL),
		ENUM_TO_STRING(GLASS)
	};


	//Resolution
	this->m_Display = new Display();

	std::list <DISPLAY_DEVICE > _displays = this->m_Display->DisplayName();

	for (std::list<DISPLAY_DEVICE>::const_iterator i = _displays.cbegin();
		i != _displays.cend(); ++i)
	{
		ZeroMemory(_devicename, 0, 128);

		swprintf_s(_devicename, TEXT("%ws"), (*i).DeviceString);

		::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO8), CB_ADDSTRING, static_cast<WPARAM>(0), (LPARAM)_devicename);
	}

	for (k = 0; k <= 1; k += 1)
	{
		wcscpy_s(A, sizeof(A) / sizeof(TCHAR), static_cast<TCHAR*>(gSizing[k]));
		::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO5), static_cast<UINT>(CB_ADDSTRING), static_cast<WPARAM>(0), reinterpret_cast<LPARAM>(A));
	}
	for (k = 0; k <= 1; k += 1)
	{
		wcscpy_s(A, sizeof(A) / sizeof(TCHAR), static_cast<TCHAR*>(gOpacity[k]));
		::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO6), static_cast<UINT>(CB_ADDSTRING), static_cast<WPARAM>(0), reinterpret_cast<LPARAM>(A));
	}
	for (k = 0; k <= 1; k += 1)
	{
		wcscpy_s(A, sizeof(A) / sizeof(TCHAR), static_cast<TCHAR*>(gLeveling[k]));
		::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO7), static_cast<UINT>(CB_ADDSTRING), static_cast<WPARAM>(0), reinterpret_cast<LPARAM>(A));
	}
	for (k = 0; k <= 1; k += 1)
	{
		wcscpy_s(A, sizeof(A) / sizeof(TCHAR), static_cast<TCHAR*>(gLeveling[k]));
		::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO2), static_cast<UINT>(CB_ADDSTRING), static_cast<WPARAM>(0), reinterpret_cast<LPARAM>(A));
		::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO3), static_cast<UINT>(CB_ADDSTRING), static_cast<WPARAM>(0), reinterpret_cast<LPARAM>(A));
		::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO4), static_cast<UINT>(CB_ADDSTRING), static_cast<WPARAM>(0), reinterpret_cast<LPARAM>(A));
	}

	// set to first index
	::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO2), CB_SETCURSEL, static_cast<WPARAM>(0), 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO3), CB_SETCURSEL, static_cast<WPARAM>(0), 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO4), CB_SETCURSEL, static_cast<WPARAM>(0), 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO5), CB_SETCURSEL, static_cast<WPARAM>(0), 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO6), CB_SETCURSEL, static_cast<WPARAM>(0), 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO7), CB_SETCURSEL, static_cast<WPARAM>(0), 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO8), CB_SETCURSEL, static_cast<WPARAM>(0), 0);

	OnCbnSelchangeCombo8();

	CButton *_Wing = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK6));
	_Wing->EnableWindow(FALSE);

	CComboBox * _chat = (CComboBox*)GetDlgItem(IDC_COMBO5);
	_chat->EnableWindow(FALSE);

	CComboBox * _inventory = (CComboBox*)GetDlgItem(IDC_COMBO6);
	_inventory->EnableWindow(FALSE);

	CComboBox * _effect = (CComboBox*)GetDlgItem(IDC_COMBO7);
	_effect->EnableWindow(FALSE);

	CButton * _Route = (CButton*)GetDlgItem(IDC_CHECK9);
	_Route->EnableWindow(FALSE);

	try {
		// Check plugin
		this->m_Plugin = new Plugins;

		std::list<std::string> cplug = m_Plugin->Get();

		for (std::list<std::string>::const_iterator i = cplug.begin(); i != cplug.end(); ++i)
		{
			if (strcmp((*i).c_str(), "Wing") == 0)
				_Wing->EnableWindow(TRUE);
			if (strcmp((*i).c_str(), "Pathos") == 0)
				_Route->EnableWindow(TRUE);
			if (strcmp((*i).c_str(), "Chat") == 0)
				_chat->EnableWindow(TRUE);
			if (strcmp((*i).c_str(), "Inventory") == 0)
				_inventory->EnableWindow(TRUE);
			if (strcmp((*i).c_str(), "Effect") == 0)
				_effect->EnableWindow(TRUE);
		}

		this->ReadConfiguration();
	}
	catch (MyKOException &ex)
	{
		MessageBox(ex.errorMessage(), TEXT("KO Editor"), MB_OKCANCEL);
		this->EndDialog(-1);
	}

}

void MyKODlg::SetupConfiguration()
{
	m_OPTIONINI = new OPTIONINI;
	m_OPTIONINI->LOD_Chr = 0;
	m_OPTIONINI->LOD_Shape = 0;
	m_OPTIONINI->LOD_Terrain = 0;
	m_OPTIONINI->EnableShadow = 1;
	m_OPTIONINI->Width = 1920; // current resolution
	m_OPTIONINI->Height = 1080;
	m_OPTIONINI->ColorDepth = 32;
	m_OPTIONINI->Distance = 512;
	m_OPTIONINI->SndAmbience = 48;
	m_OPTIONINI->Bgm = 1;
	m_OPTIONINI->Effect = 1;
	m_OPTIONINI->Duplicate = 1;
	m_OPTIONINI->Count = 2000;
	m_OPTIONINI->WindowCursor = 1;
	m_OPTIONINI->WindowMode = 0;
	m_OPTIONINI->EffectVisible = 1;

	m_SOACSINI = new SOACSINI;

	m_SOACSINI->HPBAR = 1;
	m_SOACSINI->CAMERA_ANGLE = 23;
	m_SOACSINI->VisibleWings = 0;


	std::list<string> ip;
	ip.push_back("login.anarchyko.com");

	m_SERVERINI = new PARAMSERVER;
	m_SERVERINI->server_count = 1;
	m_SERVERINI->IPV4 = ip;
	m_SERVERINI->hpBar = 1;
	m_SERVERINI->show_wings = 0;
	m_SERVERINI->version_files = 1298;
	m_SERVERINI->list_files = 1298;
}

void MyKODlg::ResetConfiguration()
{
	this->SetupConfiguration();
	//Range visibility
	CSliderCtrl *_Visibility = reinterpret_cast<CSliderCtrl*>(GetDlgItem(IDC_SLIDER1));
	_Visibility->SetPos(this->m_OPTIONINI->Distance);

	//weapon effects
	CSliderCtrl *_TextureView = reinterpret_cast<CSliderCtrl*>(GetDlgItem(IDC_SLIDER4));
	_TextureView->SetPos(this->m_OPTIONINI->Count);

	CSliderCtrl *_SndAmbience = reinterpret_cast<CSliderCtrl*>(GetDlgItem(IDC_SLIDER4));
	_SndAmbience->SetPos(this->m_OPTIONINI->SndAmbience);

	CButton *_Bgm = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK2));
	_Bgm->SetCheck(this->m_OPTIONINI->Bgm);

	CButton *_Environment = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK3));
	_Environment->SetCheck(this->m_OPTIONINI->Effect);

	CButton *_Ambient = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK4));
	_Ambient->SetCheck(this->m_OPTIONINI->Duplicate);

	CButton *_WindowMode = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK1));
	_WindowMode->SetCheck(this->m_OPTIONINI->WindowMode);

	CButton *_ShowCursor = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK5));
	_ShowCursor->SetCheck(this->m_OPTIONINI->WindowMode);

	CButton *_ShowWings = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK6));
	_ShowWings->SetCheck(this->m_SERVERINI->show_wings);

	CButton *_ShowShadows = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK7));
	_ShowShadows->SetCheck(this->m_OPTIONINI->EnableShadow);

	// camera view / angle
	CSliderCtrl *_CameView = reinterpret_cast<CSliderCtrl*>(GetDlgItem(IDC_SLIDER2));
	_CameView->SetPos(this->m_SOACSINI->CAMERA_ANGLE);

	CButton *_AutoUpdated = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK8));
	_AutoUpdated->SetCheck(this->m_SOACSINI->HPBAR);

	CButton *_WeaponEffect = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK10));
	_WeaponEffect->SetCheck(m_OPTIONINI->EffectVisible);

	CString _DefRes;
	_DefRes.Format(TEXT("[%d x %d] (%d bit)"), this->m_OPTIONINI->Width, this->m_OPTIONINI->Height, this->m_OPTIONINI->ColorDepth);

	auto _resolution = reinterpret_cast<CComboBox*>(GetDlgItem(IDC_COMBO1));

	if (_resolution->FindString(_resolution->GetCount() - 1, _DefRes) == CB_ERR)
		_resolution->AddString(_DefRes);

	_resolution->SelectString(_resolution->GetCount() - 1, _DefRes);
}

void MyKODlg::SaveConfiguration()
{
	CString buf;
	TCHAR Buffer[MAX_PATH];
	CString _PSrc, _PDest;

	if (GetCurrentDirectory(MAX_PATH, Buffer) == 0)
		throw MyKOException(TEXT("Application not in path."));

	//Range visibility
	CEdit *_Visibility = static_cast<CEdit*>(GetDlgItem(IDC_EDIT1));
	_Visibility->GetWindowText(buf);
	m_OPTIONINI->Distance = _wtoi(buf);

	//Camera angle 
	CEdit *_CAMERA_ANGLE = reinterpret_cast<CEdit *>(GetDlgItem(IDC_EDIT2));
	_CAMERA_ANGLE->GetWindowText(buf);
	this->m_SOACSINI->CAMERA_ANGLE = _wtoi(buf);

	//weapon effect
	CEdit *_GlowTerrain = reinterpret_cast<CEdit *>(GetDlgItem(IDC_EDIT4));
	_GlowTerrain->GetWindowText(buf);
	m_OPTIONINI->Count = _wtoi(buf);

	// audio
	auto _snd3d = reinterpret_cast<CEdit *>(GetDlgItem(IDC_EDIT5));
	_snd3d->GetWindowText(buf);
	m_OPTIONINI->SndAmbience = _wtoi(buf);

	// Background music
	CButton *_bgm = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK2));
	m_OPTIONINI->Bgm = _bgm->GetCheck();

	// environment
	CButton *_Env = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK3));
	m_OPTIONINI->Effect = _Env->GetCheck();

	// ambient
	CButton *_Ambient = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK4));
	this->m_OPTIONINI->Duplicate = _Ambient->GetCheck();

	// resolution
	CComboBox * _resolution = reinterpret_cast<CComboBox*>(GetDlgItem(IDC_COMBO1));
	_resolution->GetWindowText(buf);

	// resolution
	int nTokenPos = 0;
	CString SelectResolution = buf.Tokenize(TEXT("-"), nTokenPos);

	SelectResolution.TrimRight();

	std::list<PRESOLUTION> _ClassResolution = this->m_Display->Resolutions();

	for (std::list<PRESOLUTION>::const_iterator i = _ClassResolution.cbegin(); i != _ClassResolution.cend(); ++i)
	{
		CString fromClass;

		fromClass.Format(TEXT("[%d x %d]"), (*i)->Width, (*i)->Height);

		if (wcscmp(SelectResolution, fromClass) == 0)
		{
			m_OPTIONINI->Width = (*i)->Width; // current resolution
			m_OPTIONINI->Height = (*i)->Height;
			m_OPTIONINI->ColorDepth = (*i)->Pixel;
		}
	}

	CButton *_WinMode = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK1));
	m_OPTIONINI->WindowMode = _WinMode->GetCheck();

	CButton *_ShowCursor = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK5));
	m_OPTIONINI->WindowCursor = _ShowCursor->GetCheck();

	CButton *_WeaponEffect = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK10));
	m_OPTIONINI->EffectVisible = _WeaponEffect->GetCheck();
	// show shadows
	CButton *_ShowShadows = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK7));
	m_OPTIONINI->EnableShadow = _ShowShadows->GetCheck();
	// fast HP bar update
	CButton *_AutoUpdated = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK8));
	m_SOACSINI->HPBAR = _AutoUpdated->GetCheck();

	// character
	CComboBox * _Char = reinterpret_cast<CComboBox*>(GetDlgItem(IDC_COMBO2));
	m_OPTIONINI->LOD_Chr = _Char->GetCurSel();

	// obj
	CComboBox * _Obj = reinterpret_cast<CComboBox*>(GetDlgItem(IDC_COMBO3));
	m_OPTIONINI->LOD_Shape = _Obj->GetCurSel();

	// terrain
	CComboBox * _Terrain = reinterpret_cast<CComboBox*>(GetDlgItem(IDC_COMBO4));
	m_OPTIONINI->LOD_Terrain = _Terrain->GetCurSel();

	// Chat syle
	CComboBox * _Chat = reinterpret_cast<CComboBox*>(GetDlgItem(IDC_COMBO5));
	if (_Chat->IsWindowEnabled() == TRUE) {
		if (_Chat->GetCurSel() == BIG)
		{
			_PSrc.Format(TEXT("%s\\%s\\%s\\%s\\*"), Buffer, DPLUGINS, TEXT("Chat"), TEXT("Big"));

			_PDest.Format(TEXT("%s\\%s\\"), Buffer, TEXT("Zones"));

			this->m_Plugin->SetupDirectory(std::string(_PDest.GetString(), _PDest.GetString() + _PDest.GetLength()));

			std::list<std::string> files = this->m_Plugin->GetFiles(std::string(_PSrc.GetString(), _PSrc.GetString() + _PSrc.GetLength()));

			for (std::list<std::string>::const_iterator i = files.cbegin(); i != files.cend(); ++i)
			{
				_PSrc.Replace(L"*", L"");
				CString src = _PSrc + CString((*i).c_str());
				CString dst = _PDest + CString((*i).c_str());
				this->m_Plugin->Copying(std::string(src.GetString(), src.GetString() + src.GetLength()), std::string(dst.GetString(), dst.GetString() + dst.GetLength()));
			}
		}
		else
		{
			_PSrc.Format(TEXT("%s\\%s\\%s\\%s\\*"), Buffer, DPLUGINS, TEXT("Chat"), TEXT("Small"));

			_PDest.Format(TEXT("%s\\%s\\"), Buffer, TEXT("Zones"));

			this->m_Plugin->SetupDirectory(std::string(_PDest.GetString(), _PDest.GetString() + _PDest.GetLength()));

			std::list<std::string> files = this->m_Plugin->GetFiles(std::string(_PSrc.GetString(), _PSrc.GetString() + _PSrc.GetLength()));

			for (std::list<std::string>::const_iterator i = files.cbegin(); i != files.cend(); ++i)
			{
				_PSrc.Replace(L"*", L"");
				CString src = _PSrc + CString((*i).c_str());
				CString dst = _PDest + CString((*i).c_str());
				this->m_Plugin->Copying(std::string(src.GetString(), src.GetString() + src.GetLength()), std::string(dst.GetString(), dst.GetString() + dst.GetLength()));
			}
		}
	}
	// Inentory style
	CComboBox * _Inv = reinterpret_cast<CComboBox*>(GetDlgItem(IDC_COMBO6));
	if (_Inv->IsWindowEnabled()) {
		if (_Inv->GetCurSel() == GLASS)
		{
			_PSrc.Format(TEXT("%s\\%s\\%s\\%s\\*"), Buffer, DPLUGINS, TEXT("Inventory"), TEXT("Transparent"));

			_PDest.Format(TEXT("%s\\%s\\"), Buffer, TEXT("Misc"));

			this->m_Plugin->SetupDirectory(std::string(_PDest.GetString(), _PDest.GetString() + _PDest.GetLength()));

			std::list<std::string> files = this->m_Plugin->GetFiles(std::string(_PSrc.GetString(), _PSrc.GetString() + _PSrc.GetLength()));

			for (std::list<std::string>::const_iterator i = files.cbegin(); i != files.cend(); ++i)
			{
				_PSrc.Replace(L"*", L"");
				CString src = _PSrc + CString((*i).c_str());
				CString dst = _PDest + CString((*i).c_str());
				this->m_Plugin->Copying(std::string(src.GetString(), src.GetString() + src.GetLength()), std::string(dst.GetString(), dst.GetString() + dst.GetLength()));
			}
		}
		else
		{
			_PSrc.Format(TEXT("%s\\%s\\%s\\%s\\*"), Buffer, DPLUGINS, TEXT("Inventory"), TEXT("Standard"));

			_PDest.Format(TEXT("%s\\%s\\"), Buffer, TEXT("Misc"));

			this->m_Plugin->SetupDirectory(std::string(_PDest.GetString(), _PDest.GetString() + _PDest.GetLength()));

			std::list<std::string> files = this->m_Plugin->GetFiles(std::string(_PSrc.GetString(), _PSrc.GetString() + _PSrc.GetLength()));

			for (std::list<std::string>::const_iterator i = files.cbegin(); i != files.cend(); ++i)
			{
				_PSrc.Replace(L"*", L"");
				CString src = _PSrc + CString((*i).c_str());
				CString dst = _PDest + CString((*i).c_str());
				this->m_Plugin->Copying(std::string(src.GetString(), src.GetString() + src.GetLength()), std::string(dst.GetString(), dst.GetString() + dst.GetLength()));
			}
		}
	}
	
	//Effect
	CComboBox * _Cast = reinterpret_cast<CComboBox*>(GetDlgItem(IDC_COMBO7));
	if (_Cast->IsWindowEnabled() == TRUE) {
		if (_Cast->GetCurSel() == HIGH)
		{
			_PSrc.Format(TEXT("%s\\%s\\%s\\%s\\*"), Buffer, DPLUGINS, TEXT("Effect"), TEXT("Show"));

			_PDest.Format(TEXT("%s\\%s\\"), Buffer, TEXT("Data"));

			this->m_Plugin->SetupDirectory(std::string(_PDest.GetString(), _PDest.GetString() + _PDest.GetLength()));

			std::list<std::string> files = this->m_Plugin->GetFiles(std::string(_PSrc.GetString(), _PSrc.GetString() + _PSrc.GetLength()));

			for (std::list<std::string>::const_iterator i = files.cbegin(); i != files.cend(); ++i)
			{
				_PSrc.Replace(L"*", L"");
				CString src = _PSrc + CString((*i).c_str());
				CString dst = _PDest + CString((*i).c_str());
				this->m_Plugin->Copying(std::string(src.GetString(), src.GetString() + src.GetLength()), std::string(dst.GetString(), dst.GetString() + dst.GetLength()));
			}
		}
		else
		{
			_PSrc.Format(TEXT("%s\\%s\\%s\\%s\\*"), Buffer, DPLUGINS, TEXT("Effect"), TEXT("Hide"));

			_PDest.Format(TEXT("%s\\%s\\"), Buffer, TEXT("Data"));

			this->m_Plugin->SetupDirectory(std::string(_PDest.GetString(), _PDest.GetString() + _PDest.GetLength()));

			std::list<std::string> files = this->m_Plugin->GetFiles(std::string(_PSrc.GetString(), _PSrc.GetString() + _PSrc.GetLength()));

			for (std::list<std::string>::const_iterator i = files.cbegin(); i != files.cend(); ++i)
			{
				_PSrc.Replace(L"*", L"");
				CString src = _PSrc + CString((*i).c_str());
				CString dst = _PDest + CString((*i).c_str());
				this->m_Plugin->Copying(std::string(src.GetString(), src.GetString() + src.GetLength()), std::string(dst.GetString(), dst.GetString() + dst.GetLength()));
			}
		}
	}
	// wings
	CButton *_ShowWings = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK6));
	if (_ShowWings->IsWindowEnabled()) {
		if (_ShowWings->GetCheck() == BST_CHECKED)
		{
			_PSrc.Format(TEXT("%s\\%s\\%s\\%s\\*"), Buffer, DPLUGINS, TEXT("Wing"), TEXT("Show"));

			_PDest.Format(TEXT("%s\\%s\\"), Buffer, TEXT("Data"));

			this->m_Plugin->SetupDirectory(std::string(_PDest.GetString(), _PDest.GetString() + _PDest.GetLength()));

			std::list<std::string> files = this->m_Plugin->GetFiles(std::string(_PSrc.GetString(), _PSrc.GetString() + _PSrc.GetLength()));

			for (std::list<std::string>::const_iterator i = files.cbegin(); i != files.cend(); ++i)
			{
				_PSrc.Replace(L"*", L"");
				CString src = _PSrc + CString((*i).c_str());
				CString dst = _PDest + CString((*i).c_str());
				this->m_Plugin->Copying(std::string(src.GetString(), src.GetString() + src.GetLength()), std::string(dst.GetString(), dst.GetString() + dst.GetLength()));
			}
		}
		else
		{
			_PSrc.Format(TEXT("%s\\%s\\%s\\%s\\*"), Buffer, DPLUGINS, TEXT("Wing"), TEXT("Hide"));

			_PDest.Format(TEXT("%s\\%s\\"), Buffer, TEXT("Data"));

			this->m_Plugin->SetupDirectory(std::string(_PDest.GetString(), _PDest.GetString() + _PDest.GetLength()));

			std::list<std::string> files = this->m_Plugin->GetFiles(std::string(_PSrc.GetString(), _PSrc.GetString() + _PSrc.GetLength()));

			for (std::list<std::string>::const_iterator i = files.cbegin(); i != files.cend(); ++i)
			{
				_PSrc.Replace(L"*", L"");
				CString src = _PSrc + CString((*i).c_str());
				CString dst = _PDest + CString((*i).c_str());
				this->m_Plugin->Copying(std::string(src.GetString(), src.GetString() + src.GetLength()), std::string(dst.GetString(), dst.GetString() + dst.GetLength()));
			}
		}
	}

	CButton *_ShowRoute = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK9));
	if(_ShowRoute->IsWindowEnabled())
	{
		if(_ShowRoute->GetCheck() == BST_CHECKED)
		{
			_PSrc.Format(TEXT("%s\\%s\\%s\\%s\\*"), Buffer, DPLUGINS, TEXT("Pathos"), TEXT("Show"));

			_PDest.Format(TEXT("%s\\%s\\"), Buffer, TEXT("Data"));

			this->m_Plugin->SetupDirectory(std::string(_PDest.GetString(), _PDest.GetString() + _PDest.GetLength()));

			std::list<std::string> files = this->m_Plugin->GetFiles(std::string(_PSrc.GetString(), _PSrc.GetString() + _PSrc.GetLength()));

			for (std::list<std::string>::const_iterator i = files.cbegin(); i != files.cend(); ++i)
			{
				_PSrc.Replace(L"*", L"");
				CString src = _PSrc + CString((*i).c_str());
				CString dst = _PDest + CString((*i).c_str());
				this->m_Plugin->Copying(std::string(src.GetString(), src.GetString() + src.GetLength()), std::string(dst.GetString(), dst.GetString() + dst.GetLength()));
			}
		}
		else
		{
			_PSrc.Format(TEXT("%s\\%s\\%s\\%s\\*"), Buffer, DPLUGINS, TEXT("Pathos"), TEXT("Hide"));

			_PDest.Format(TEXT("%s\\%s\\"), Buffer, TEXT("Data"));

			this->m_Plugin->SetupDirectory(std::string(_PDest.GetString(), _PDest.GetString() + _PDest.GetLength()));

			std::list<std::string> files = this->m_Plugin->GetFiles(std::string(_PSrc.GetString(), _PSrc.GetString() + _PSrc.GetLength()));

			for (std::list<std::string>::const_iterator i = files.cbegin(); i != files.cend(); ++i)
			{
				_PSrc.Replace(L"*", L"");
				CString src = _PSrc + CString((*i).c_str());
				CString dst = _PDest + CString((*i).c_str());
				this->m_Plugin->Copying(std::string(src.GetString(), src.GetString() + src.GetLength()), std::string(dst.GetString(), dst.GetString() + dst.GetLength()));
			}
		}
	}

	this->m_ConfOption->Set(m_OPTIONINI);
	this->m_ConfServer->Set(m_SERVERINI);
	this->m_ConfSoacs->Set(m_SOACSINI);
}

void MyKODlg::ReadConfiguration()
{
	CString bERROR;

	//assert(m_OPTIONINI != NULL);
	//assert(m_SOACSINI != NULL);
	//assert(m_SERVERINI != NULL);


	if (m_OPTIONINI != NULL) m_OPTIONINI = NULL;
	if (m_SOACSINI != NULL) m_SOACSINI = NULL;
	if (m_SERVERINI != NULL) m_SERVERINI = NULL;

	m_OPTIONINI = new OPTIONINI;
	m_SOACSINI = new SOACSINI;
	m_SERVERINI = new PARAMSERVER;

	try
	{
		this->m_ConfOption = new OPTION;
		this->m_ConfSoacs = new SOACS;
		this->m_ConfServer = new ServerIni;
		
	}
	catch (MyKOException &ex)
	{
		int r = MessageBox(ex.errorMessage(), TEXT("KO Editor"), MB_OKCANCEL);
		if (r == IDOK)
		{
			// todo write new config
		}
	}

}

void MyKODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(MyKODlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO8, &MyKODlg::OnCbnSelchangeCombo8)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &MyKODlg::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &MyKODlg::OnNMCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER4, &MyKODlg::OnNMCustomdrawSlider4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &MyKODlg::OnNMCustomdrawSlider3)
	ON_BN_CLICKED(IDC_BUTTON3, &MyKODlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &MyKODlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK4, &MyKODlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK3, &MyKODlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK2, &MyKODlg::OnBnClickedCheck2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &MyKODlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO5, &MyKODlg::OnCbnSelchangeCombo5)
	ON_CBN_SELCHANGE(IDC_COMBO6, &MyKODlg::OnCbnSelchangeCombo6)
	ON_CBN_SELCHANGE(IDC_COMBO7, &MyKODlg::OnCbnSelchangeCombo7)
	ON_BN_CLICKED(IDC_CHECK1, &MyKODlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK5, &MyKODlg::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &MyKODlg::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK7, &MyKODlg::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &MyKODlg::OnBnClickedCheck8)
	ON_CBN_SELCHANGE(IDC_COMBO2, &MyKODlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &MyKODlg::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO4, &MyKODlg::OnCbnSelchangeCombo4)
	ON_BN_CLICKED(IDOK, &MyKODlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK9, &MyKODlg::OnBnClickedCheck9)
	ON_BN_CLICKED(IDC_CHECK10, &MyKODlg::OnBnClickedCheck10)
END_MESSAGE_MAP()

BOOL MyKODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
			pSysMenu->AppendMenu(MF_STRING, IDD_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	this->SetupApplication();

	return TRUE;  // return TRUE  unless you set the focus to a control

}

void MyKODlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void MyKODlg::OnPaint()
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

HCURSOR MyKODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAboutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


#pragma region DISPLAY
Display::Display()
{
	this->GetCurrentDisplay();
	//this->SetResolutions();
}

void Display::GetCurrentDisplay()
{
	DWORD numberofDeviceAdapters = 0;

	DISPLAY_DEVICE dd;

	dd.cb = sizeof(DISPLAY_DEVICE);

	while (EnumDisplayDevices(NULL, numberofDeviceAdapters, &dd, EDD_GET_DEVICE_INTERFACE_NAME))
	{
		if (dd.StateFlags & DISPLAY_DEVICE_ACTIVE)
		{

			this->m_displayDevices.push_back(dd); // Display string
		}
		numberofDeviceAdapters++; // update next display
	}

}

void Display::SetCurrentDisplay(LPCWSTR lpDispName)
{
	int available = 0;
	int iModeNum = ENUM_CURRENT_SETTINGS;
	DEVMODE dm;


	dm.dmSize = sizeof(DEVMODE);

	dm.dmDriverExtra = 1572864;

	if (this->m_resolutions.size() != 0) this->m_resolutions.clear();

	while (EnumDisplaySettingsEx(lpDispName, iModeNum, &dm, EDS_RAWMODE) != 0)
	{
		PRESOLUTION _resolution = new RESOLUTION;

		_resolution->Width = dm.dmPelsWidth;
		_resolution->Height = dm.dmPelsHeight;
		_resolution->Pixel = dm.dmBitsPerPel;

		for (std::list<PRESOLUTION>::const_iterator i = this->m_resolutions.cbegin(); i != this->m_resolutions.cend(); ++i)
		{
			if ((*i)->Width == _resolution->Width && (*i)->Height == _resolution->Height)
				available++;
			else
				available = 0;
		}

		if (available == 0)
			this->m_resolutions.push_back(_resolution);

		//	if (iModeNum == ENUM_CURRENT_SETTINGS) this->m_resolutions.push_back(_resolution);
		iModeNum++;
	}
}

void Display::SetResolutions()
{
	TCHAR B[128];
	int available = 0;
	int iModeNum = ENUM_CURRENT_SETTINGS;
	DEVMODE dm;

	dm.dmSize = sizeof(DEVMODE);

	dm.dmDriverExtra = 1572864;

	for (std::list<DISPLAY_DEVICE>::const_iterator i = this->m_displayDevices.cbegin(); i != this->m_displayDevices.cend(); ++i)
	{
		ZeroMemory(B, 0, 128);

		swprintf_s(B, TEXT("%ws"), (*i).DeviceName);

		while (EnumDisplaySettingsEx(B, iModeNum, &dm, EDS_RAWMODE) != 0)
		{
			PRESOLUTION _resolution = new RESOLUTION;

			_resolution->Width = dm.dmPelsWidth;
			_resolution->Height = dm.dmPelsHeight;
			_resolution->Pixel = dm.dmBitsPerPel;

			for (std::list<PRESOLUTION>::const_iterator i = this->m_resolutions.cbegin(); i != this->m_resolutions.cend(); ++i)
			{
				if ((*i)->Width == _resolution->Width && (*i)->Height == _resolution->Height)
					available++;
				else
					available = 0;
			}

			if (available == 0)
				this->m_resolutions.push_back(_resolution);

			if (iModeNum == ENUM_CURRENT_SETTINGS)
				this->m_resolutions.push_back(_resolution);
			iModeNum++;
		}

	}
}

#pragma endregion 

#pragma region SERVERINI
ServerIni::ServerIni() :m_IniUtil(new INIUtil(CONFSERVER))
{
	this->Load();
}

void ServerIni::Set(PPARAMSERVER conf)
{
	this->m_SERVERINI = conf;
	this->Save();
}

void ServerIni::Load()
{
	this->m_SERVERINI = new PARAMSERVER;

	TCHAR buf[10] = { 0 };
	std::list<std::string> ips;

	int count = m_IniUtil->ReadInt(TEXT("Server"), TEXT("Count"));
	m_SERVERINI->server_count = count;
	m_SERVERINI->hpBar = m_IniUtil->ReadInt(TEXT("Server"), TEXT("HPBAR"));
	m_SERVERINI->version_files = m_IniUtil->ReadInt(TEXT("Version"), TEXT("Files"));
	m_SERVERINI->list_files = m_IniUtil->ReadInt(TEXT("IncludeExe"), TEXT("Last"));

	for (int i = 0; i < count; i++)
	{
		swprintf_s(buf, L"IP%d", i);
		std::string b = m_IniUtil->ReadString(TEXT("Server"), buf);
		ips.push_back(b);
	}

	m_SERVERINI->IPV4 = ips;

}

void ServerIni::Save()
{
	TCHAR buf[128];
	TCHAR bIP[10];

	ZeroMemory(buf, 0, 128);
	ZeroMemory(bIP, 0, 128);

	//swprintf_s(buf, L"%d", m_SERVERINI->server_count);

	//m_IniUtil->Write(TEXT("Server"), TEXT("Count"), buf);

//	for (int i = 0; i < m_SERVERINI->server_count; i++)
//	{
//		swprintf_s(bIP, L"IP%d", i);

//		swprintf_s(buf, L"IP%d", m_SERVERINI->server_count);

//		m_IniUtil->Write(TEXT("Server"), bIP, buf);
//	}

	swprintf_s(buf, L"%d", m_SERVERINI->hpBar);
	m_IniUtil->Write(TEXT("Server"), TEXT("HPBAR"), buf);

	swprintf_s(buf, L"%d", m_SERVERINI->show_wings);
	m_IniUtil->Write(TEXT("Server"), TEXT("VisibleWings"), buf);

	swprintf_s(buf, L"%d", m_SERVERINI->version_files);
	m_IniUtil->Write(TEXT("Version"), TEXT("Files"), buf);

	swprintf_s(buf, L"%d", m_SERVERINI->list_files);
	m_IniUtil->Write(TEXT("IncludeExe"), TEXT("Last"), buf);
}

#pragma endregion 

#pragma  region OPTIONINI
OPTION::OPTION() :m_IniUtil(new INIUtil(CONFOPTION))
{
	this->Load();
}

void OPTION::Set(POPTIONINI conf)
{
	this->m_OPTIONINI = conf;
	this->Save();
}

void OPTION::Load()
{
	this->m_OPTIONINI = new OPTIONINI;
	m_OPTIONINI->LOD_Chr = m_IniUtil->ReadInt(TEXT("Texture"), TEXT("LOD_Chr"));
	m_OPTIONINI->LOD_Shape = m_IniUtil->ReadInt(TEXT("Texture"), TEXT("LOD_Shape"));
	m_OPTIONINI->LOD_Terrain = m_IniUtil->ReadInt(TEXT("Texture"), TEXT("LOD_Terrain"));
	m_OPTIONINI->EnableShadow = m_IniUtil->ReadInt(TEXT("Shadow"), TEXT("Use"));
	m_OPTIONINI->Width = m_IniUtil->ReadInt(TEXT("ViewPort"), TEXT("Width")); // current resolution
	m_OPTIONINI->Height = m_IniUtil->ReadInt(TEXT("ViewPort"), TEXT("Height"));
	m_OPTIONINI->ColorDepth = m_IniUtil->ReadInt(TEXT("ViewPort"), TEXT("ColorDepth"));
	m_OPTIONINI->Distance = m_IniUtil->ReadInt(TEXT("ViewPort"), TEXT("Distance"));
	m_OPTIONINI->SndAmbience = m_IniUtil->ReadInt(TEXT("Sound"), TEXT("Distance"));
	m_OPTIONINI->Bgm = m_IniUtil->ReadInt(TEXT("Sound"), TEXT("Bgm"));
	m_OPTIONINI->Effect = m_IniUtil->ReadInt(TEXT("Sound"), TEXT("Effect"));
	m_OPTIONINI->Duplicate = m_IniUtil->ReadInt(TEXT("Sound"), TEXT("Duplicate"));
	m_OPTIONINI->Count = m_IniUtil->ReadInt(TEXT("Effect"), TEXT("Count"));
	m_OPTIONINI->WindowCursor = m_IniUtil->ReadInt(TEXT("Cursor"), TEXT("WindowCursor"));
	m_OPTIONINI->WindowMode = m_IniUtil->ReadInt(TEXT("Screen"), TEXT("WindowMode"));;
	m_OPTIONINI->EffectVisible = m_IniUtil->ReadInt(TEXT("WeaponEffect"), TEXT("EffectVisible"));
	m_OPTIONINI->BalloonVisible = m_IniUtil->ReadInt(TEXT("MopBalloon"), TEXT("BalloonVisible"));

}

void OPTION::Save()
{
	TCHAR buf[128];

	ZeroMemory(buf, 0, 128);

	swprintf_s(buf, L"%d", m_OPTIONINI->LOD_Chr);
	m_IniUtil->Write(TEXT("Texture"), TEXT("LOD_Chr"), buf);

	swprintf_s(buf, L"%d", m_OPTIONINI->LOD_Shape);
	m_IniUtil->Write(TEXT("Texture"), TEXT("LOD_Shape"), buf);

	swprintf_s(buf, L"%d", m_OPTIONINI->LOD_Terrain);
	m_IniUtil->Write(TEXT("Texture"), TEXT("LOD_Terrain"), buf);

	swprintf_s(buf, L"%d", m_OPTIONINI->EnableShadow);
	m_IniUtil->Write(TEXT("Shadow"), TEXT("Use"), buf);

	swprintf_s(buf, L"%d", m_OPTIONINI->Width);
	m_IniUtil->Write(TEXT("ViewPort"), TEXT("Width"), buf);

	swprintf_s(buf, L"%d", m_OPTIONINI->Height);
	m_IniUtil->Write(TEXT("ViewPort"), TEXT("Height"), buf);

	swprintf_s(buf, L"%d", m_OPTIONINI->ColorDepth);
	m_IniUtil->Write(TEXT("ViewPort"), TEXT("ColorDepth"), buf);

	swprintf_s(buf, L"%d", m_OPTIONINI->Distance);
	m_IniUtil->Write(TEXT("ViewPort"), TEXT("Distance"), buf);

	swprintf_s(buf, L"%d", m_OPTIONINI->SndAmbience);
	m_IniUtil->Write(TEXT("Sound"), TEXT("Distance"), buf);

	swprintf_s(buf, L"%d", m_OPTIONINI->Bgm);
	m_IniUtil->Write(TEXT("Sound"), TEXT("Bgm"), buf);

	swprintf_s(buf, L"%d", m_OPTIONINI->Effect);
	m_IniUtil->Write(TEXT("Sound"), TEXT("Effect"), buf);

	swprintf_s(buf, L"%d", m_OPTIONINI->Duplicate);
	m_IniUtil->Write(TEXT("Sound"), TEXT("Duplicate"), buf);

	swprintf_s(buf, L"%d", m_OPTIONINI->Count);
	m_IniUtil->Write(TEXT("Effect"), TEXT("Count"), buf);

	swprintf_s(buf, L"%d", m_OPTIONINI->WindowCursor);
	m_IniUtil->Write(TEXT("Cursor"), TEXT("WindowCursor"), buf);

	swprintf_s(buf, L"%d", m_OPTIONINI->WindowMode);
	m_IniUtil->Write(TEXT("Screen"), TEXT("WindowMode"), buf);

	swprintf_s(buf, L"%d", m_OPTIONINI->EffectVisible);
	m_IniUtil->Write(TEXT("WeaponEffect"), TEXT("EffectVisible"), buf);

}
#pragma endregion

#pragma  region SOACSINI
SOACS::SOACS() :m_IniUtil(new INIUtil(CONFSOACS))
{
	this->Load();
}

void SOACS::Set(PSOACSINI conf)
{
	this->m_SOACSINI = conf;
	this->Save();
}

void SOACS::Load()
{
	this->m_SOACSINI = new SOACSINI;
	
	m_SOACSINI->HPBAR = m_IniUtil->ReadInt(TEXT("Server"), TEXT("HPBar"));
	m_SOACSINI->CAMERA_ANGLE = m_IniUtil->ReadInt(TEXT("Server"), TEXT("CameraAngle"));
	m_SOACSINI->VisibleWings = m_IniUtil->ReadInt(TEXT("Server"), TEXT("VisibleWings"));
}

void SOACS::Save()
{
	TCHAR buf[128];

	ZeroMemory(buf, 0, 128);

	swprintf_s(buf, L"%d", m_SOACSINI->HPBAR);
	m_IniUtil->Write(TEXT("Server"), TEXT("HPBar"), buf);

	swprintf_s(buf, L"%d", m_SOACSINI->CAMERA_ANGLE);
	m_IniUtil->Write(TEXT("Server"), TEXT("CameraAngle"), buf);

	swprintf_s(buf, L"%d", m_SOACSINI->VisibleWings);
	m_IniUtil->Write(TEXT("Server"), TEXT("VisibleWings"), buf);
}
#pragma endregion 


Plugins::Plugins()
{
	this->Check();
}

void Plugins::Check()
{
	WCHAR   directory[MAX_PATH];
	HANDLE hFind;
	WIN32_FIND_DATA file_data;

	ZeroMemory(directory, 0, MAX_PATH);

	GetCurrentDirectory(MAX_PATH, directory);

	wcscat(directory, TEXT("\\"));
	wcscat(directory, DPLUGINS);
	wcscat(directory, TEXT("\\*"));

	if ((hFind = FindFirstFile(directory, &file_data)) == INVALID_HANDLE_VALUE)
	{
		// Invalid directory
		throw MyKOException(L"Application not in path.");
	}

	do
	{
		if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (wcscmp(file_data.cFileName, L".") != 0 && wcscmp(file_data.cFileName, L"..") != 0)
			{
				std::wstring b = file_data.cFileName;
				this->m_plugins.push_back(std::string(b.begin(), b.end()));
			}
		}
	} while (FindNextFile(hFind, &file_data) != 0);

	FindClose(hFind);
}

DWORD Plugins::SetupDirectory(const std::string dirName)
{
	// Create directory if not exists
	return CreateDirectory(std::wstring(dirName.begin(), dirName.end()).c_str(), NULL);
}

int Plugins::Copying(std::string src, std::string dest)
{
	FILE *fs, *ft;
	char ch;

	fopen_s(&fs, src.c_str(), "rb");
	fopen_s(&ft, dest.c_str(), "wb");

	if (fs == nullptr)return 0;
	if (ft == nullptr) return 0;

	ch = fgetc(fs);

	fseek(fs, 0, SEEK_END);

	long int size = ftell(fs);

	fseek(fs, 0, SEEK_SET);

	char *buf = new char[size + 1];

	fread(buf, size, 1, fs);

	buf[size] = 0;
	fclose(fs);

	for (int i = 0; i < size; i++)
	{
		fputc(buf[i], ft);
	}
	//while (ch != EOF)
	//{
	//	fputc(ch, ft);
	//	ch = fgetc(fs);
	//}

	fclose(ft);

	return 1;
}

std::list<std::string> Plugins::GetFiles(std::string dir)
{
	HANDLE hFind;
	WIN32_FIND_DATA file_data;
	std::list<std::string> _files;

	if ((hFind = FindFirstFile(std::wstring(dir.begin(), dir.end()).c_str(), &file_data)) == INVALID_HANDLE_VALUE)
	{
		// Invalid directory
		throw MyKOException(L"Application not in path.");
	}

	do
	{
		if (file_data.dwFileAttributes)
		{
			if (wcscmp(file_data.cFileName, L".") != 0 && wcscmp(file_data.cFileName, L"..") != 0)
			{
				std::wstring b = file_data.cFileName;
				_files.push_back(std::string(b.begin(), b.end()));
			}
		}
	} while (FindNextFile(hFind, &file_data) != 0);

	return _files;
}

void MyKODlg::OnCbnSelchangeCombo8()
{
	TCHAR _devicename[128];

	TCHAR _R[128];

	::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO1), static_cast<UINT>(CB_RESETCONTENT), static_cast<WPARAM>(0), LPARAM(0));

	std::list <DISPLAY_DEVICE > _displays = this->m_Display->DisplayName();

	const UINT length = ::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO8), WM_GETTEXTLENGTH, 0, 0);

	WCHAR pszText[128];

	ZeroMemory(pszText, 0, 128);

	::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO8), WM_GETTEXT, length + 1, (LPARAM)pszText);

	for (std::list<DISPLAY_DEVICE>::const_iterator i = _displays.cbegin();
		i != _displays.cend(); ++i)
	{
		if (wcscmp((*i).DeviceString, pszText) == 0)
		{
			ZeroMemory(_devicename, 0, 128);

			swprintf_s(_devicename, TEXT("%ws"), (*i).DeviceName);
		}
	}

	this->m_Display->SetCurrentDisplay(_devicename);

	std::list<PRESOLUTION> _resolution = this->m_Display->Resolutions();

	for (std::list<PRESOLUTION>::const_iterator i = _resolution.cbegin();
		i != _resolution.cend(); ++i)
	{
		ZeroMemory(_R, 0, 128);

		swprintf_s(_R, TEXT("[%d x %d] - (%d bit)"), (*i)->Width, (*i)->Height, (*i)->Pixel);

		::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO1), CB_ADDSTRING, static_cast<WPARAM>(0), (LPARAM)_R);
	}

	::SendMessage(::GetDlgItem(m_hWnd, IDC_COMBO1), CB_SETCURSEL, static_cast<WPARAM>(0), 0);
}

void MyKODlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	CString str;

	CSliderCtrl *psli = reinterpret_cast<CSliderCtrl*>(GetDlgItem(IDC_SLIDER1));

	psli->SetRange(0, 512, false); //Set the range of values

	int num = psli->GetPos(); //Get the current value

	str.Format(TEXT("%d"), num);

	::SetDlgItemText(m_hWnd, IDC_EDIT1, str);

	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);

	*pResult = 0;
}

void MyKODlg::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here

	CString str;

	CSliderCtrl *psli = reinterpret_cast<CSliderCtrl*>(GetDlgItem(IDC_SLIDER2));

	psli->SetRange(10, 25, false); //Set the range of values

	int num = psli->GetPos(); //Get the current value

	str.Format(TEXT("%d"), num);

	::SetDlgItemText(m_hWnd, IDC_EDIT2, str);

	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
	*pResult = 0;
}

void MyKODlg::OnNMCustomdrawSlider4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	CString str;

	CSliderCtrl *psli = reinterpret_cast<CSliderCtrl*>(GetDlgItem(IDC_SLIDER4));

	psli->SetRange(1000, 6000, false); //Set the range of values

	int num = psli->GetPos(); //Get the current value

	str.Format(TEXT("%d"), num);

	::SetDlgItemText(m_hWnd, IDC_EDIT4, str);
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
	*pResult = 0;
}

void MyKODlg::OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	CString str;

	CSliderCtrl *psli = reinterpret_cast<CSliderCtrl*>(GetDlgItem(IDC_SLIDER3));

	psli->SetRange(20, 48, false); //Set the range of values

	int num = psli->GetPos(); //Get the current value

	str.Format(TEXT("%d"), num);

	::SetDlgItemText(m_hWnd, IDC_EDIT5, str);

	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
	*pResult = 0;
}

void MyKODlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	int r = MessageBox(TEXT("All configuration will be reset to default, are u sure ?"),
		TEXT("KO Editor"), MB_OKCANCEL);
	if (r == IDOK) {
		try
		{
			this->ResetConfiguration();
		}
		catch (MyKOException &ex)
		{
			MessageBox(ex.errorMessage(), TEXT("KO Editor"), MB_OK);
		}
	}
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
}

void MyKODlg::OnBnClickedButton1()
{
	try
	{
		this->SaveConfiguration();
	}
	catch (MyKOException &ex)
	{
		MessageBox(ex.errorMessage(), TEXT("KO Editor"), MB_OK);
	}
	
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(FALSE);
	MessageBox(TEXT("Configuration Saved."), TEXT("KO Editor"), MB_OKCANCEL);
}

void MyKODlg::OnBnClickedCheck4()
{
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
}

void MyKODlg::OnBnClickedCheck3()
{
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
}

void MyKODlg::OnBnClickedCheck2()
{
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
}

void MyKODlg::OnCbnSelchangeCombo1()
{
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
}

void MyKODlg::OnCbnSelchangeCombo5()
{
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
}

void MyKODlg::OnCbnSelchangeCombo6()
{
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
}

void MyKODlg::OnCbnSelchangeCombo7()
{
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
}

void MyKODlg::OnBnClickedCheck1()
{
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
}

void MyKODlg::OnBnClickedCheck5()
{
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
}

void MyKODlg::OnBnClickedCheck6()
{
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
}

void MyKODlg::OnBnClickedCheck7()
{
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
}

void MyKODlg::OnBnClickedCheck8()
{
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
}

void MyKODlg::OnCbnSelchangeCombo2()
{
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
}

void MyKODlg::OnCbnSelchangeCombo3()
{
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
}

void MyKODlg::OnCbnSelchangeCombo4()
{
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
}

void MyKODlg::OnBnClickedOk()
{
	TCHAR Buffer[MAX_PATH];
	CString _PLoader;
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION psInfo;

	ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
	ZeroMemory(&psInfo, sizeof(PROCESS_INFORMATION));

	GetCurrentDirectory(MAX_PATH, Buffer);

	_PLoader.Format(TEXT("%s\\%s"), Buffer, APPLAUNCHER);

	int r = MessageBox(TEXT("Configuration automatic saved & Launch The Game"), TEXT("KO Editor"), MB_OKCANCEL);
	if (r == IDOK)
	{
		try
		{
			this->SaveConfiguration();
			if (CreateProcess(_PLoader,
				nullptr/*(LPWSTR) input.c_str()*/, nullptr, nullptr, FALSE, CREATE_SUSPENDED, nullptr, nullptr,
				&startupInfo, &psInfo) == 0)
			{
				swprintf_s(Buffer, L"Failed to execute. code: (%d)", GetLastError());
				throw MyKOException(Buffer);
			}
		}
		catch (MyKOException &ex)
		{
			MessageBox(ex.errorMessage(), TEXT("KO Editor"), MB_OK);
		}
	}

	CDialogEx::OnOK();
}


void MyKODlg::OnBnClickedCheck9()
{
	// TODO: Add your control notification handler code here
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
}


void MyKODlg::OnBnClickedCheck10()
{
	// TODO: Add your control notification handler code here
	CButton *_SaveButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_BUTTON1));
	_SaveButton->EnableWindow(TRUE);
}
