#pragma once
#include <list>
#include "MyKOException.h"

typedef enum _LIMITATION {
	Minimum,
	Medium,
	Maximum
}LIMITATION;

typedef enum _LEVEL {
	LOW,
	HIGH
}LEVEL;

typedef enum _SIZING {
	SMALL,
	BIG
}SIZING;

typedef enum _VISIBILITY {
	SHOW,
	HIDE
}VISIBILITY;

typedef enum _OPACITY {
	NORMAL,
	GLASS
}OPACITY;

typedef enum _METERING {
	LOWER,
	FULLER
}METERING;

#define ENUM_TO_STRING(ENUM) TEXT(#ENUM) 


typedef struct _PARAMSERVER {
	int server_count;
	std::list<std::string> IPV4;
	int hpBar;
	int show_wings;
	size_t version_files;
	int list_files;

}PARAMSERVER, *PPARAMSERVER;

/// <summary>
/// Struct Configuration SOACSINI.ini
/// </summary>
typedef struct _SOACSINI {
	int HPBAR;
	int CAMERA_ANGLE;
	int VisibleWings;
}SOACSINI, *PSOACSINI;

/// <summary>
/// Struct Configuration SOACSINI.ini
/// </summary>
typedef struct _OPTIONINI {
	// character
	int LOD_Chr;
	int LOD_Shape;
	int LOD_Terrain;
	// [Shadow]
	int EnableShadow;
	//[ViewPort]
	int Width;
	int Height;
	int ColorDepth;
	int Distance;
	//[Sound]
	int SndAmbience;
	int Bgm;
	int Effect;
	int Duplicate;
	// [Effect]
	int Count;
	// [Cursor]
	int WindowCursor;
	//[Screen]
	int WindowMode;
	//[WeaponEffect]
	int EffectVisible;
	//Balon
	int BalloonVisible;

}OPTIONINI, *POPTIONINI;


/// <summary>
/// Display utility
/// 
/// </summary>
#pragma region Display

#define DISPLAY_NAME TEXT("%ws at Monitor %d")

typedef struct _RESOLUTION
{
	int Width;
	int Height;
	int Pixel;
}RESOLUTION, *PRESOLUTION;

class Display
{
public:
	explicit Display();

	virtual ~Display() {}

	std::list<PRESOLUTION> Resolutions() { return this->m_resolutions; }

	std::list<DISPLAY_DEVICE> DisplayName() { return this->m_displayDevices; }

	void SetCurrentDisplay(LPCWSTR lpDispName);

private:
	std::list<PRESOLUTION> m_resolutions;
	std::list<DISPLAY_DEVICE> m_displayDevices;


	void GetCurrentDisplay();
	void SetResolutions();
};

#pragma endregion 

#define CONFSERVER		TEXT("Server.ini")
#define CONFCAMERAINI	TEXT("camera.ini")
#define CONFOPTION		TEXT("option.ini")
#define CONFSOACS		TEXT("soacs.ini")
#define APPLAUNCHER		TEXT("launcher.exe")
#define DPLUGINS		TEXT("OptionPlugin")


#pragma region INIUTIL

class INIUtil
{
public:
	explicit INIUtil(LPCWSTR  ini_file)
	{
		WCHAR   cfg_IniName[256];

		if (GetCurrentDirectory(MAX_PATH, cfg_IniName) == 0)
			throw MyKOException(L"Application not in path.");

		wcscat(cfg_IniName, TEXT("\\"));
		wcscat(cfg_IniName, ini_file);

		file = std::wstring(cfg_IniName);

		if(!Available(std::string(file.begin(), file.end())))
			throw MyKOException(L"Application not in path.");

	}
	virtual ~INIUtil()
	{
	}

	std::string ReadString(const LPCWSTR section, const LPCWSTR key)
	{
		TCHAR berror[128];
		TCHAR rValue[256];

		ZeroMemory(berror, 0, 128);
		ZeroMemory(rValue, 0, 256);


		if (!GetPrivateProfileString(section, key, TEXT(""), rValue, 256, file.c_str()))
		{
			swprintf_s(berror, L"Read Parameter : within default key is %ws. ", rValue);
			throw MyKOException(berror);
		}

		std::wstring _v = rValue;

		return std::string(_v.begin(), _v.end());
	}

	int ReadInt(const LPCWSTR section, const LPCWSTR key)
	{
		TCHAR berror[128];
		TCHAR rValue[128];
		int r = 0;

		ZeroMemory(berror, 0, 128);
		ZeroMemory(rValue, 0, 128);

		if (!GetPrivateProfileString(section, key, TEXT(""), rValue, 128, file.c_str()))
		{
			swprintf_s(berror, L"Read Key: %ws, Value: %ws. ", key, rValue);
			throw MyKOException(berror);
		}
		swscanf_s(rValue, TEXT("%d"), &r);

		return r;
	}

	void Read(std::wstring section, std::wstring key, std::wstring * value)
	{
		TCHAR berror[128];
		TCHAR rValue[256];

		ZeroMemory(berror, 0, 128);
		ZeroMemory(rValue, 0, 256);

		if (!GetPrivateProfileString(section.c_str(), key.c_str(), TEXT(""), rValue, 256, file.c_str()))
		{
			swprintf_s(berror, L"Read Parameter : within default key is %ws. ", rValue);
			throw MyKOException(berror);
		}

		*value = rValue;
	}

	void Write(const LPCWSTR section, const LPCWSTR key, const LPCWSTR value)
	{
		TCHAR berror[128];

		ZeroMemory(berror, 0, 128);

		if (!WritePrivateProfileString(section, key, value, file.c_str()))
		{
			swprintf_s(berror, L"Save Parameter :%ws within value %ws failed. ", key, value);
			throw MyKOException(berror);
		}
	}

private:
	std::wstring file;

	bool Available(const std::string& name) {

		FILE *ini_file;
		
		fopen_s(&ini_file, name.c_str(), "r");

		if (ini_file != nullptr) {
			fclose(ini_file);
			return true;
		}
		return false;
	}
};

#pragma endregion

#pragma region SERVERINI

class ServerIni
{

public:
	explicit ServerIni();
	virtual ~ServerIni() {}

	PPARAMSERVER Get() { return this->m_SERVERINI; }

	void Set(PPARAMSERVER conf);

private:
	PPARAMSERVER m_SERVERINI;
	INIUtil * m_IniUtil;
	FILE* conf_file;

	void Load();
	void Save();

};

#pragma endregion 

#pragma region OPTIONINI
class OPTION
{
public:
	explicit OPTION();
	virtual ~OPTION() {}

	POPTIONINI Get() { return this->m_OPTIONINI; }

	void Set(POPTIONINI conf);


private:
	POPTIONINI m_OPTIONINI;
	INIUtil * m_IniUtil;
	FILE* m_conf_file;

	void Load();
	void Save();

};
#pragma endregion 

#pragma  region SOACSINI
class SOACS
{
public:
	explicit SOACS();
	virtual ~SOACS() {}

	PSOACSINI Get() { return this->m_SOACSINI; }

	void Set(PSOACSINI conf);


private:
	PSOACSINI m_SOACSINI;
	INIUtil * m_IniUtil;
	FILE* m_conf_file;

	void Load();
	void Save();
};
#pragma endregion

class Plugins
{
public:
	explicit Plugins();
	virtual ~Plugins() {}

	std::list<std::string> Get() { return this->m_plugins; }

	DWORD SetupDirectory(std::string dirName);

	int Copying(std::string src, std::string dest);

	std::list<std::string> GetFiles(std::string dir);

private:
	std::list<std::string> m_plugins;

	void Check();
};


class MyKODlg : public CDialogEx
{
public:
	MyKODlg(CWnd* pParent = NULL);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_DIALOG };
#endif

private:
	void SetupApplication();

	// default configuration
	void SetupConfiguration();
	void ResetConfiguration();
	void SaveConfiguration();
	void ReadConfiguration();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	HICON m_hIcon;

	// resolution
	Display * m_Display;

	// main conf
	POPTIONINI		m_OPTIONINI;
	PSOACSINI		m_SOACSINI;
	PPARAMSERVER	m_SERVERINI;

	// plugin check
	Plugins *m_Plugin;

	// conf
	ServerIni * m_ConfServer;
	OPTION * m_ConfOption;
	SOACS * m_ConfSoacs;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnCbnSelchangeCombo8();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo5();
	afx_msg void OnCbnSelchangeCombo6();
	afx_msg void OnCbnSelchangeCombo7();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheck9();
	afx_msg void OnBnClickedCheck10();
};

