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
    : wxPanel(parent, wxID_ANY)
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
        new wxButton(this, ButtonProvidentFundLoan, "ProvidentFundLoan"),
		wxSizerFlags().Center());
    grid->Add(
        new wxButton(this, ButtonPortfoioLoan, "PortfoioLoan"),
        wxSizerFlags().Center());

    grid->SetSizeHints(this);
    this->SetSizer(grid);
    //panelSizer->Add(grid, 1, wxEXPAND, 10);
    //this->SetSizer(panelSizer);
    //this->SetSizerAndFit(panelSizer);
}

cPanel::~cPanel()
{
}

void cPanel::OnClickButton_CommercialLoan(wxCommandEvent& event)                        //��ҵ�ʹ���
{
    CommercialLoan* Dialog_CommercialLoan = new CommercialLoan(Frame);
}

void cPanel::OnClickButton_ProvidentFundLoan(wxCommandEvent& event)                     //���������
{
    ProvidentFundLoan* Dialog_ProvidentFundLoan = new ProvidentFundLoan(Frame);
}

void cPanel::OnClickButton_PortfoioLoan(wxCommandEvent& event)                          //����ʹ���
{
	PortfolioLoan* Dialog_PortfoioLoan = new PortfolioLoan(Frame);
}


