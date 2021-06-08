#include "PortfolioLoan.h"


BEGIN_EVENT_TABLE(PortfolioLoan, wxDialog)

END_EVENT_TABLE()
PortfolioLoan::PortfolioLoan(wxFrame* parent)
	:wxDialog(parent, wxID_ANY, wxT("PortfolioLoan"))
{
	wxBoxSizer* rowSizer;
    /*���㷽ʽ*/
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    wxArrayString strings_CalculateType;
    strings_CalculateType.Add(wxT("������������ۼ���"));
    strings_CalculateType.Add(wxT("���ݴ����ܶ����"));
    wxComboBox* Choice_CalculateType = new wxComboBox(this, ID_CHOICE_CALCULATE_TYPE,
        wxT("������������ۼ���"),
        wxDefaultPosition, wxDefaultSize, strings_CalculateType, wxALIGN_RIGHT | wxCB_DROPDOWN | wxCB_READONLY);
    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("���㷽ʽ: "),
        wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    Choice_CalculateType->SetSelection(0);
    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(Choice_CalculateType, 1);

    Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    /*���ݵ���*/
    rowSizer = new wxBoxSizer(wxHORIZONTAL);

    InputPrice = new wxTextCtrl(this, ID_TEXTCTRL_HOUSE_PRICE,
        wxEmptyString, wxDefaultPosition, wxDefaultSize);//���������//InputPrice->SetExtraStyle(wxWS_EX_PROCESS_UI_UPDATES);//ǿ�ƶ��θ���
    InputPrice->SetHint("���뷿�ݵ���(Ԫ/ƽ��)");
    InputPrice->SetMaxLength(9);

    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("���ݵ���: "),
        wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(InputPrice, 1);

    Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    /*�������*/
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    InputSquare = new wxTextCtrl(this, ID_TEXTCTRL_HOUSE_SQUARE,
        wxEmptyString, wxDefaultPosition, wxDefaultSize);//InputSquare->SetExtraStyle(wxWS_EX_PROCESS_UI_UPDATES);//ǿ�ƶ��θ���
    InputSquare->SetHint("���뷿�����(ƽ����)");
    InputSquare->SetMaxLength(6);

    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("�������: "),
        wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(InputSquare, 1);

    Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    /*�����ܶ�*/
    rowSizer = new wxBoxSizer(wxHORIZONTAL);
    InputTotalLoan = new wxTextCtrl(this, ID_TEXTCRTL_TOTAL_LOAN,
        wxEmptyString, wxDefaultPosition, wxDefaultSize);
    InputTotalLoan->SetHint("����������ܶ�(��Ԫ)");

    StaticText = new wxStaticText(this, wxID_ANY,
        wxT("�����ܶ�: "),
        wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);

    rowSizer->SetMinSize(wxSize(200, StaticText->GetMinSize().y));
    rowSizer->Add(StaticText);
    rowSizer->Add(InputTotalLoan, 1);

    Sizer->Add(rowSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
	
}

PortfolioLoan::~PortfolioLoan()
{
}
