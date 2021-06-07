#include "CommercialLoan.h"
#include "PortfolioLoan.h"
#include "ProvidentFundLoan.h"
//wx����
#include "wx/grid.h"
#include "wx/choice.h"
#include"wx/combobox.h"
#include "wx/stattext.h" //������̬�ı�
#include"wx/textctrl.h"

wxBEGIN_EVENT_TABLE(cPanel, wxPanel)
EVT_BUTTON(ButtonCommercialLoan,    cPanel::OnClickButton_CommercialLoan)
EVT_BUTTON(ButtonPortfoioLoan,      cPanel::OnClickButton_PortfoioLoan)
EVT_BUTTON(ButtonProvidentFundLoan, cPanel::OnClickButton_ProvidentFundLoan)
END_EVENT_TABLE()

cPanel::cPanel(wxFrame* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition)
{
    this->Frame = parent;
    wxGridSizer* grid = new wxGridSizer(4, 1, 5, 10);


    /*ѡ���,ѡ��Ĭ��Ϊ0*/
  

    grid->Add(
        new wxStaticText(this, wxID_STATIC,
		wxT("��������"),
		wxDefaultPosition, wxDefaultSize),
		wxSizerFlags().Align(wxALIGN_CENTRE_HORIZONTAL).Border(wxALL & ~wxBOTTOM, 5));
    grid->Add(
        new wxButton(this, ButtonCommercialLoan, "CommercialLoan"),
        wxSizerFlags().Center());
    grid->Add(
        new wxButton(this, ButtonPortfoioLoan, "PortfoioLoan"),
        wxSizerFlags().Center());
    grid->Add(
        new wxButton(this, ButtonProvidentFundLoan, "ProvidentFundLoan"),
        wxSizerFlags().Center());


    //��grid��panel��������,���뵽panelsizer��
    grid->SetSizeHints(this);
    panelSizer->Add(grid, 1, wxEXPAND, 10);

    this->SetSizerAndFit(panelSizer);
}

cPanel::~cPanel()
{
}

void cPanel::OnClickButton_CommercialLoan(wxCommandEvent& event)
{
    CommercialLoan* Dialog_CommercialLoan = new CommercialLoan(Frame);
}

void cPanel::OnClickButton_PortfoioLoan(wxCommandEvent& event)
{
}

void cPanel::OnClickButton_ProvidentFundLoan(wxCommandEvent& event)
{
}

//void cPanel::GetChoice(wxCommandEvent& event)
//{
//    if (event.GetEventType() == wxEVT_CHOICE) {
//        if (event.GetSelection() == 0) {
//			CommercialLoan* CLPanel = new CommercialLoan(Frame, this, panelSizer);
//		}
//        else if (event.GetSelection() == 1) {
//            PortfolioLoan* PLPanel = new PortfolioLoan();
//        }
//        else if (event.GetSelection() == 2) {
//
//        }
//    }
//    event.Skip();
//}

