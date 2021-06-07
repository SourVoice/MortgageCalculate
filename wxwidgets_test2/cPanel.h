#include "wx/wx.h"

#ifndef _CPANEL_H_
#define _CPANEL_H_
class cPanel : public wxPanel
{
public:
	cPanel(wxFrame* parent);
    ~cPanel();


	wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    wxFrame* Frame;

private:
    void OnClickButton_CommercialLoan(wxCommandEvent &event);
    void OnClickButton_PortfoioLoan(wxCommandEvent& event);
    void OnClickButton_ProvidentFundLoan(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
    
};
enum
{
    ButtonCommercialLoan = 101,
    ButtonPortfoioLoan,
    ButtonProvidentFundLoan
};

#endif