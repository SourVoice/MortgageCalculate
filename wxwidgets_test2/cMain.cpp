#include "cMain.h"
#include "cPanel.h"

#include "wx/choice.h"   //创建choice
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_MENU(10001, cMain::OnMenuNew)
EVT_MENU(10002, cMain::OnMenuOpen)
EVT_MENU(10003, cMain::OnMenuSave)
EVT_MENU(10004, cMain::OnMenuExit)
EVT_MENU(10005, cMain::OnMeunAbout)
END_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, wxString("mg"), wxDefaultPosition)
{


    /*--------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    //添加menu
    //创建file,help菜单
    wxMenu *menuFile = new wxMenu();
    //file菜单选项
    menuFile->Append(10001, "New");
    menuFile->Append(10002, "Open");
    menuFile->Append(10003, "Save");
    menuFile->Append(10004, "Exit");
    //help菜单选项
    wxMenu* menuHelp = new wxMenu();
    menuHelp->Append(10005, "About");
	
    m_MenuBar = new wxMenuBar();
    this->SetMenuBar(m_MenuBar);
    //添加file,help至菜单
    m_MenuBar->Append(menuFile, "File");
    m_MenuBar->Append(menuHelp, "Help");

    //添加底部状态栏
    CreateStatusBar();
    SetStatusText("Welcome to my application for mortgage calculator!");





    //在子控件(容器窗口)上操作
    cPanel* panel = new cPanel(this);
    sizer->Add(panel, 1, wxEXPAND | wxALL, 5);






    this->SetSizerAndFit(sizer);

}
cMain::~cMain()
{
}
//file菜单选项的功能
void cMain::OnMenuNew(wxCommandEvent &event)
{
    //new后将创建新窗口,删除旧窗口
    Refresh();
}
void cMain::OnMenuOpen(wxCommandEvent &event) {}
void cMain::OnMenuSave(wxCommandEvent &event) {}
void cMain::OnMenuExit(wxCommandEvent &event)
{
    Close();
    event.Skip();
}
//help菜单选项功能
void cMain::OnMeunAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a mortgage calculator", "About the application", wxOK | wxICON_INFORMATION);
}
