#include "cApp.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp() : wxApp()
{
}
bool cApp::OnInit()
{
    wxUpdateUIEvent::SetMode(wxUPDATE_UI_PROCESS_SPECIFIED);

    m_framel = new cMain();
    m_framel->Show();
    return true;
}
cApp::~cApp()
{
}