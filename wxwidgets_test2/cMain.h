#include "wx\wx.h"

class cMain : public wxFrame
{
private:
public:
    cMain();
    ~cMain();

public:
    wxMenuBar *m_MenuBar = nullptr;
    wxToolBar *m_ToolBar = nullptr;
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
private:
    //file选项
    void OnMenuNew(wxCommandEvent &event);
    void OnMenuOpen(wxCommandEvent &event);
    void OnMenuSave(wxCommandEvent &event);
    void OnMenuExit(wxCommandEvent &event);

    //help选项
    void OnMeunAbout(wxCommandEvent &event);
    wxDECLARE_EVENT_TABLE();
};

