#include "stdafx.h"
#include "SettingsUI.h"
#include "General.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(General, CPropertyPage)

General::General(Settings *settings) :
CPropertyPage(General::IDD),
_settings(settings) {

}

General::~General()
{
}

void General::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, CHK_STARTUP, _startup);
    DDX_Control(pDX, CHK_NOTIFY, _notify);
    DDX_Control(pDX, CHK_SOUNDS, _sounds);
    DDX_Control(pDX, CMB_LANG, _lang);
    DDX_Control(pDX, GRP_SKIN, _skinGrp);
    DDX_Control(pDX, GRP_BEHAVIOR, _behaviorGrp);
    DDX_Control(pDX, GRP_LANGUAGE, _languageGrp);
    DDX_Control(pDX, LBL_AUTHOR, _author);
}

BOOL General::OnInitDialog() {
    CPropertyPage::OnInitDialog();

    LoadSettings();

    return TRUE;
}

std::list<CString> General::FindSkins(CString dir) {
    std::list<CString> skins;

    CFileFind ff;
    dir += L"\\*";
    BOOL result = ff.FindFile(dir);
    while (result) {
        result = ff.FindNextFile();
        if (ff.IsDots()) {
            continue;
        }

        if (ff.IsDirectory()) {
            CFileFind inDir;
            CString dirPath = ff.GetFilePath();
            dirPath += L"\\skin.xml";
            if (inDir.FindFile(dirPath)) {
                /* We found a skin XML file; add the skin dir to our list. */
                skins.push_back(ff.GetFileName());
            }
        }
    }

    return skins;
}
void General::LoadSettings() {
    _notify.SetCheck(_settings->IsEnabled("notifyIcon"));
    _sounds.SetCheck(_settings->IsEnabled("soundEffects"));

    std::wstring w = _settings->GetText("skin");
    _author.SetWindowTextW(w.c_str());
}

BEGIN_MESSAGE_MAP(General, CPropertyPage)
END_MESSAGE_MAP()